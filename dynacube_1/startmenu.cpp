/***************************************************************************
                          startmenu.cpp  -  description
                             -------------------
    begin                : Sat Feb 28 2004
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

 #include "startmenu.h"
//change
 char *menu[] = {"Game - X","Calculator","Editor","Run Command","Shut Down"};
 char *file[] = {"\\explorer","\\calc","\\editor","\\run",""};

 void startmenu::startmenu_init()
 {
   start_opened  = _false;

   no_option = 5;
   width = 120;
   height = (no_option +1) * MENU_Y_OFFSET + DEFAULT_EMBOSS_SIZE;
   x = START_X;
   y = SCREEN_HEIGHT - height;

   skincolor = TASKBAR_COLOR;

   bk_buf = (COLOR *)kmalloc((width+2) * (height+2) * 2);
 }

 void startmenu::draw()
 {
   DW i, j;

   restoreImage(mcurx,mcury);
   
   if(start_opened == _true)
   {
    //Image Saving
    getimage(x,y,width+2,height+2,bk_buf);
    
    fillrect(x,y,width,height,skincolor);
    emboss3D(x,y,width,height,LEFT|TOP|RIGHT,_false,2);

    for(i=0;i<no_option;i++)
     {
//       ginfo(x+MENU_X_OFFSET,y+(i+1)*MENU_Y_OFFSET,menu[i]);
       cprint(x+MENU_X_OFFSET,y+(i+1)*MENU_Y_OFFSET,menu[i],0x0);       
     }

    //StartMenu
    emboss3D(START_X,SCREEN_HEIGHT + START_Y,START_WIDTH,START_HEIGHT,0,_true,2);
   }
   else
   {
    putimage(x,y,width+2,height+2,bk_buf);
    emboss3D(START_X,SCREEN_HEIGHT + START_Y,START_WIDTH,START_HEIGHT,0,_false,2);    
   }
   
    if(mouse_inited)
    {
      getimage(mcurx,mcury,16,16, &mouseimg[0][0]);

      for(i = mcurx ; i < mcurx+16 ; i++)
      {
        for(j = mcury ; j < mcury+16 ; j++)
        {
          if(mouseptr[j-mcury][i-mcurx])
          {
            setPixel(i,j,0x0);
          }
        }
      }
    }
   
 }


 SDB startmenu::processClick(DW _x, DW _y)
 {

   DW i;

   if(iswithin(_x,_y,START_X,SCREEN_HEIGHT + START_Y,START_WIDTH,START_HEIGHT))
   {
     if(start_opened == _true)
     {
      start_opened = _false;
     }
     else
      start_opened = _true;

    draw();
    return 0;
   }

   if(start_opened == _true)
   {
    if(iswithin(_x,_y,x,y,width,height))
    {
    for(i=0;i<no_option;i++)
     {
       if(iswithin(_x,_y,x+MENU_X_OFFSET,y+(i+1)*MENU_Y_OFFSET,width,MENU_Y_OFFSET))
        {
          if(i == 4)
          {
            //Sync evrythng
            asm("hlt");
          }
           ginfo(500,100,menu[i]);
//change
	   __asm__ __volatile__("pushl %%eax"::"a"(file[i]));
           asm("movl $0x1, %eax");
           asm("int $0x30");
        }
     }
     start_opened = _false;
     draw();
     return 0;
    }
    else
    {
     start_opened = _false;
     draw();
     return -1;
    }
   }
   return -1;
 }
