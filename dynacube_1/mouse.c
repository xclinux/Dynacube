/***************************************************************************
                          mouse.c  -  description
                             -------------------
    begin                : Fri Jan 23 2004
    copyright            : (C) 2004 by Dynacube Team
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

 #include "mouse.h"

 //This is to remove all printf's to improve performance
 //#define printf

 DB mbyte[3];
 DW mcurx = TOTAL_WIDTH/2, mcury = TOTAL_HEIGHT/2;
 boolean mouse_inited = _false;

 #define SAMPLE_MOVE 10

 DB sample_no = 0;

 void w64(DB val)
 {
   printf("\nIn w64->%x",val);
   printStatus();

   while(readStatus() & IBF)
    ;

   outb(0x64,val);
   printStatus();
 }

 DB r60()
 {
   DB data;
   printf("\nIn r60");

   printStatus();
   if(readStatus() & OBF)
   {
    data = inb(0x60);
    printf("\t %x",data);
    printStatus();
    return data;
   }
   else
    return 0xFC;
 }

 void w60(DB val)
 {
   printf("\nIn w60->%x",val);
   printStatus();

   while(readStatus() & OBF || readStatus() & MOBF)
   {
    printf("\n%x ",inb(0x60));
   }

   if(!(readStatus() & OBF) && !(readStatus() & MOBF))
   {
     printf("\nIn w60: Writing %x",val);
     outb(0x60,val);
   }
   else
   {
     printf("\nIn w60: 0x60 Full");
   }

   printStatus();
 }

 void mouse_init1()
 {
   DB cmdByte;

   cls();
   printf("\nMouse Init 2");

   //Controller Self Test
   w64(0xAA);
   r60();

   //Enable PS/2 I/F
   w64(0xA8);
   r60();

   w64(0x60);
   w60(0x47);
   r60();

   w64(0x20);
   cmdByte = r60();
   printf("\nCMDBYTE %x %b",cmdByte,cmdByte);

   //Send Reset 2 Mouse
   w64(0xD4);
   w60(0xFF);
   while(readStatus() & OBF && readStatus() & MOBF)
   {
     r60();
   }

   //Stream Mode
   w64(0xD4);
   w60(0xEA);
   while(readStatus() & OBF || readStatus() & MOBF)
   {
     r60();
   }

   //Enable Data Reporting
   w64(0xD4);
   w60(0xF4);
   while(readStatus() & OBF)
   {
     r60();
   }

   printf("\nPS/2 Mouse Initialized");
 }



 void handle_mouse1()
 {
   static int first;
   DB i = 0;
   DD count;

   printf("\nIn handle_mouse1");

   while(readStatus() & OBF && readStatus() & MOBF && i<3)
   {
       printStatus();
       mbyte[i] = inb(0x60);
       printf(" %x ",mbyte[i]);
       i++;

//       //Wait till O/P avl
       for(count=0 ; !(readStatus() & OBF) && count < PS2_TIMEOUT && i < 3; count++)
          ;
       printf(" %d ",count);
   }

   printStatus();

   if(i == 3)
	   processData();

   eoi();

   return;
 }

 void processData()
 {
  MSG mymsg;
  DW _x = 0, _y = 0;
  DW xdel = 0, ydel = 0;
  static DB mleft = 0;

//   if((mbyte[0] & (XOVR|YOVR)) && mbyte[0] != 0xFA && mbyte[0] != 0xAA)
//   {
//    printf("\nHey Mouse Reset !!!");
//    ginfo(600,500,"\nHey Mouse Reset !!!");
//    mouse_reset();
//    eoi();
//    return;
//   }

   //Taking care of 2's complement
   if(mbyte[0] & XSGN)
      mbyte[1] = ~mbyte[1] + 1;

   if(mbyte[0] & YSGN)
      mbyte[2] = ~mbyte[2] + 1;

   printf("\nm[0] %b m[1] %d m[2] %d ",mbyte[0],mbyte[1],mbyte[2]);

    xdel = 4 * mbyte[1];
    ydel = 3 * mbyte[2];

   if(mbyte[0] & XSGN)
      _x = mcurx - xdel;
   else
      _x = mcurx + xdel;

   if(mbyte[0] & YSGN)
      _y = mcury + ydel;
   else
      _y = mcury - ydel;

    if( _x & 0x8000)
       _x = 1;

    if( _x > TOTAL_WIDTH - 16)
       _x =  TOTAL_WIDTH - 16;

    if( _y & 0x8000)
       _y = 1;

    if( _y > TOTAL_HEIGHT - 16)
       _y = TOTAL_HEIGHT - 16;

    //  Call it here
    if(graphics)
    {
      if(!mouse_inited)
      {
        getimage(mcurx,mcury,16,16,mouseimg);
        gcls_delay = 0x5FFF;
        mouse_inited = _true;
      }

//     if(!(mbyte[0] & LBTN))
	     drawMousePtr(_x,_y);
//	   else
//        getimage(mcurx,mcury,16,16,mouseimg);
	   
     
     if(mbyte[0] & LBTN)
     {
			 if(mleft == 0)
			 {
				 sample_no = 0;
				 				 
	       mymsg.type     = ACTION;
	       mymsg.sub_type = MOUSE;
	       mymsg.length   = 10;
	       *(DW*)mymsg.msg_buf = _x + 3; //Three Pixels for Mouse_ptr x offset
	       *(DW*)(mymsg.msg_buf+2) = _y + 1; //One Pixel for Mouse_ptr y offset
	       *(DW*)(mymsg.msg_buf+4) = CLICK;
	       
	       printf("\n KSEND CALLED ");

	//       ginfo(550,300,itoa(_x,10));
	//       ginfo(550,350,itoa(_y,10));

	       if(ksend(GUI_PID,&mymsg) == -1)
	        panic("from mouse message overflow");

	       printf("\n AFTER KSEND CALLED ");
	       mleft = 1;
			 }//if(mleft == 0)
			 else //Send MOVE Data
			 {
				 sample_no++;

				 if(sample_no > SAMPLE_MOVE)
				 {
					 sample_no = 0;
					 
		       mymsg.type     = ACTION;
		       mymsg.sub_type = MOUSE;
		       mymsg.length   = 10;
		       *(DW*)mymsg.msg_buf = _x + 3; //Three Pixels for Mouse_ptr x offset
		       *(DW*)(mymsg.msg_buf+2) = _y + 1; //One Pixel for Mouse_ptr y offset
		       *(DW*)(mymsg.msg_buf+4) = MOVE;

		       if(ksend(GUI_PID,&mymsg) == -1)
		        panic("From mouse message overflow");
		     }//if(sample_no > SAMPLE_MOVE)
	     }//else //Send MOVE Data
	     
     }//if(mbyte[0] & LBTN)
     else if(mleft == 1) //Release
     {
//       putimage(mcurx,mcury,16,16,mouseimg);
			 mleft = 0;
		 }

     mcurx = _x;
     mcury = _y;
     
   }//if(graphics)
   else //For Non-GUI mode
   {
    mcurx = _x;
    mcury = _y;
   }

   //Remove these
   printf("\n _x: %d _y %d",_x,_y);

   printf("\n x: %d y %d",mcurx,mcury);

   if(mbyte[0] & MBTN)
   {
    printf("\nMBtn Pressed");
   }

   if(mbyte[0] & LBTN)
   {
    printf("\nLBtn Pressed");
   }

   if(mbyte[0] & RBTN)
   {
    printf("\nRBtn Pressed");
   }

 }

 void printStatus()
 {
//  printf("\nPERR TO MOBF INH A2 SYS IBF OBF");
  printf("\nStatus %x %b",readStatus(),readStatus());
 }

 DB readData()
 {
   DD i = 0;

   printf("\nIn readData()");
   printStatus();

   while(i < PS2_TIMEOUT)
   {
    i++;
    if(readStatus() & OBF)
        break;  //Till there is something to read
   }

   if(i == PS2_TIMEOUT)
    return 0xFC;

   return inb(0x60);
 }

 void mouse_restore()
 {
	 DB i, j;

			    if(graphics)
			    {
			      getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
			    }
 }
