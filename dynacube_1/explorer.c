 #include "string.h"
 #include "client_gui.h"

 typedef struct
 {
  char lbl[MN_MAX_CHAR];
  DB cmdCode; //To be sent to the client
 } _MENUITEM;

  typedef struct
  {
   DB no_item;
   _MENUITEM mnuitem[MN_MAX_ITEM];
  } _MENU;

  typedef struct
  {
   DB no_menu;

   struct
   {
    char label[MB_MAX_CHAR];
    _MENU menu_ptr;
   }mnu[MB_MAX_MENU];

  } _MENUBAR;

 int main()
 {
  volatile MSG msg;
  CREATE_INFO cr;
  COMP_CREATE_INFO cmp;
  RESIZE_INFO rs;
  SDD ret_val = -1;
  DB i, j;
  _MENUBAR mybar;
  _MENU mymenu[5];

  char *menubar[] = {"File","Edit","View"};
  char *menuitem[] = {"New","Open","Exit","Cut","Copy","Paste","100%","200%","500%"};

  volatile char text[4096];

     strcpy(text,"hi hello");

     msg.length = sizeof(cr);
     msg.type   = CREATE;
     msg.sub_type = WINDOW;
     cr.alias_id = 101;
     cr.cntr_id = 0;
     cr.height = 200;
     cr.width = 400;
     cr.style  = 0;
     cr.x = 100;
     cr.y = 50;
     strcpy(cr.title,"Explorer");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));

     asm("int $0x30"::"a"(3));

     cr.alias_id = 102;
     cr.cntr_id = 0;
     cr.height = 200;
     cr.width = 200;
     cr.style  = 0;
     cr.x = 150;
     cr.y = 75;
//     cr.style = W_DISABLED;
     strcpy(cr.title,"Explorer 2");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));


     msg.sub_type = BUTTON;
     cmp.alias_id = 201;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 70;
     cmp.x = 200;
     cmp.y = 30;
     cmp.style = 0;
     strcpy(cmp.label,"BUTTON 1");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 202;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 50;
     cmp.x = 100;
     cmp.y = 30;
//     cmp.style = DISABLED;
     strcpy(cmp.label,"TEX");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));


     msg.sub_type = TEXT;
     cmp.alias_id = 207;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 50;
     cmp.x = 100;
     cmp.y = 5;
//     cmp.style = DISABLED;
     strcpy(cmp.label,"TEXT2");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = LABEL;
     cmp.alias_id = 203;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 50;
     cmp.x = 50;
     cmp.y = 30;
     cmp.style = 0;
     strcpy(cmp.label,"LABEL");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));


     msg.sub_type = TEXTAREA;
     cmp.alias_id = 206;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 50;
     cmp.width = 100;
     cmp.x = 100;
     cmp.y = 70;
     cmp.style = 0;
     strcpy(cmp.label,"TEXT1");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = TEXTAREA;
     cmp.alias_id = 208;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 50;
     cmp.width = 100;
     cmp.x = 210;
     cmp.y = 70;
     cmp.style = 0;
     strcpy(cmp.label,"TEXT2");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     strcpy(text,"TEXT1\nhai2all hello when is ur\n so howz it?my mummy how nice\nso that'all\n");
     msg.type     = SET;
     msg.sub_type = TEXTAREA;
     msg.length   = 10;//sizeof(DW) + sizeof(DD);
     msg.msg_buf[0] = 206;
     *(DD*)(msg.msg_buf+2) = text;


     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));



/*     msg.sub_type = FOLDERVIEW;
     cmp.alias_id = 258;
     cmp.cntr_id = 102;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 150;
     cmp.width = 150;
     cmp.x = 0;
     cmp.y = 0;
     cmp.style = 0;
     strcpy(cmp.label,"\\boot");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3)); */

     msg.type   = CREATE;
     msg.sub_type = WINDOW;
     msg.length = sizeof(cr);
     cr.alias_id = 103;
     cr.cntr_id = 0;
     cr.height = 0;
     cr.width = 0;
     cr.style  = 0;
     cr.x = 300;
     cr.y = 130;
     strcpy(cr.title,"Explorer 3");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 101;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));

/*
     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 102;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
//     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));

     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 103;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
//     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));
*/

     mybar.no_menu = 3;
     for(i = 0 ; i < mybar.no_menu ; i++)
     {
	strcpy(mybar.mnu[i].label, menubar[i]);
     }

     /*
     strcpy(mybar.mnu[0].label, "File");
     strcpy(mybar.mnu[1].label, "Edit");
     strcpy(mybar.mnu[2].label, "View");
     */

     for(i = 0 ; i < mybar.no_menu ; i++)
     {
     	mybar.mnu[i].menu_ptr.no_item = 3;

	for(j = 0 ; j < mybar.mnu[i].menu_ptr.no_item ; j++)
	{
	 mybar.mnu[i].menu_ptr.mnuitem[j].cmdCode = i*10+j;
	 strcpy(mybar.mnu[i].menu_ptr.mnuitem[j].lbl,menuitem[i*3+j]);//itoa(i*10+j,10));
	}
     }



     msg.type     = CREATE;
     msg.sub_type = MENU;
     msg.length   = 10;
     msg.msg_buf[0] = 101;
     *(DD*)(msg.msg_buf+2) = &mybar;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));

     /*
     msg.type     = CREATE;
     msg.sub_type = MENU;
     msg.length   = 10;

     for(i = 0 ; i < 10 ; i++)
     	msg.msg_buf[i] = 0;

     msg.msg_buf[0] = 101;
     *(DD*)(msg.msg_buf+2) = &i;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));
     */
     i = 0;

     while(1)
     {
       asm("pushl %0"::"r"(&msg));
       asm("int $0x30"::"a"(4));

       switch(msg.type)
       {
         case WM_CLICKED:

                switch(msg.sub_type)
		{
                 case BUT_TYPE:
//                        ginfo(400,300,itoa(msg.type,10));
//                        ginfo(400,350,itoa(msg.sub_type,10));
//                        ginfo(400,400,itoa(*(DW*)msg.msg_buf,10));
			msg.type     = GET;
     			msg.sub_type = TEXT;
     			msg.length   = 10;//sizeof(DW) + sizeof(DD);
     			msg.msg_buf[0] = 202;
			*(DD*)(msg.msg_buf+2) = text;


			asm("pushl %0"::"r"(&msg));
     			asm("pushl %0"::"r"(GUI_PID));
  			asm("int $0x30"::"a"(3));

			msg.type     = SET;
     			msg.sub_type = TEXT;
     			msg.length   = 10;//sizeof(DW) + sizeof(DD);
     			msg.msg_buf[0] = 207;
			*(DD*)(msg.msg_buf+2) = text;


			asm("pushl %0"::"r"(&msg));
     			asm("pushl %0"::"r"(GUI_PID));
     			asm("int $0x30"::"a"(3));

                        msg.type     = FINISHED;
                        msg.sub_type = BUT_TYPE;
                        msg.length   = sizeof(DD);
			msg.msg_buf[0] = 201;


                        asm("pushl %0"::"r"(&msg));
                        asm("pushl %0"::"r"(GUI_PID));
                        asm("int $0x30"::"a"(3));

                      break;

	       	      case MENU_TYPE:
			msg.type     = SET;
     			msg.sub_type = TEXT;
     			msg.length   = 10;//sizeof(DW) + sizeof(DD);
			*(DD*)(msg.msg_buf+2) = itoa(*(DW*)msg.msg_buf,10);
     			msg.msg_buf[0] = 207;

			asm("pushl %0"::"r"(&msg));
     			asm("pushl %0"::"r"(GUI_PID));
     			asm("int $0x30"::"a"(3));
				break;
                }
                break;

         case WM_KEYPRESS:
                break;

         case WM_DESTROY:
                break;
       }

     }
     while(1);
}
