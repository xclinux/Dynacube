 #include "string.h"
 #include "client_gui.h"
 #include "client_fs.h"

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
  volatile MSG msg1;
  CREATE_INFO cr;
  COMP_CREATE_INFO cmp;
  RESIZE_INFO rs;
  volatile SDD ret_val = -1;
  char filename[256];
  DB has_name=0,saved=0;
  DB i, j;
  SDW p,res;
  _MENUBAR mybar;
  _MENU mymenu[5];

  char *menubar[] = {"File","Edit"};
  char *menuitem[] = {"New","Open","Save","Save As","Close","Exit","Cut","Copy","Paste"};

  volatile char text[4096];


     msg.length = sizeof(cr);
     msg.type   = CREATE;
     msg.sub_type = WINDOW;
     cr.alias_id = 101;
     cr.cntr_id = 0;
     cr.height = 569;
     cr.width = 799;
     cr.style  = 0;
     cr.x = 0;
     cr.y = 0;
     strcpy(cr.title,"Editor");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = TEXTAREA;
     cmp.alias_id = 201;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 520;
     cmp.width = 790;
     cmp.x = 2;
     cmp.y = 2;
     cmp.style = 0;
     strcpy(cmp.label,"");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

//open dialog

     msg.type   = CREATE;
     msg.sub_type = DIALOG;
     msg.length = sizeof(cr);
     cr.alias_id = 102;
     cr.cntr_id = 101;
     cr.height = 90;
     cr.width = 150;
     cr.style  = 0;
     cr.x = 200;
     cr.y = 130;
     strcpy(cr.title,"Open File");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0":"=r"(ret_val));

     msg.type = CREATE;
     msg.sub_type = TEXT;
     cmp.alias_id = 301;
     cmp.cntr_id = 102;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 15;
     cmp.width = 130;
     cmp.x = 10;
     cmp.y = 10;
     strcpy(cmp.label,"");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));


     msg.sub_type = BUTTON;
     msg.length = sizeof(cmp);
     cmp.alias_id = 302;
     cmp.cntr_id = 102;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 35;
     cmp.x = 30;
     cmp.y = 40;
     cmp.style = 0;
     strcpy(cmp.label,"Open");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0":"=r"(ret_val));

     msg.sub_type = BUTTON;
     msg.length = sizeof(cmp);
     cmp.alias_id = 303;
     cmp.cntr_id = 102;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 50;
     cmp.x = 70;
     cmp.y = 40;
     cmp.style = 0;
     strcpy(cmp.label,"Cancel");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0":"=r"(ret_val));

//save as dialog

     mybar.no_menu = 2;
     for(i = 0 ; i < mybar.no_menu ; i++)
     {
	strcpy(mybar.mnu[i].label, menubar[i]);
     }

     mybar.mnu[0].menu_ptr.no_item = 6;
     mybar.mnu[1].menu_ptr.no_item = 3;

     for(i = 0 ; i < mybar.no_menu ; i++)
     {
	for(j = 0 ; j < mybar.mnu[i].menu_ptr.no_item ; j++)
	{
	 mybar.mnu[i].menu_ptr.mnuitem[j].cmdCode = i*10+j;
	 strcpy(mybar.mnu[i].menu_ptr.mnuitem[j].lbl,menuitem[i*6+j]);//itoa(i*10+j,10));
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

     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 101;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));


     while(1)
     {
      recv(&msg1);

       switch(msg1.type)
       {
         case WM_CLICKED:

                switch(msg1.sub_type)
		{
                 case BUT_TYPE:
			switch(*(DW*)msg1.msg_buf)
			{
			case 302 :
				msg.type     = GET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				*(DW*)msg.msg_buf = 301;
				*(DD*)(msg.msg_buf+2) = text;

				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				 p = open(text,O_RDONLY);
				 if(p >= 0)
  				 {
				  i = 0;
  				  while((res = read(p,text+i*512,512)) > 0)
   				  {
	 			   i++;
   				  }
				  close(p);
				  msg.type     = FINISHED;
				  msg.sub_type = BUT_TYPE;
				  msg.length   = sizeof(DD);
				  *(DW *)msg.msg_buf = 302;


				  asm("pushl %0"::"r"(&msg));
				  asm("pushl %0"::"r"(GUI_PID));
				  asm("int $0x30"::"a"(3));


  				  msg.type     = HIDE;
	     			  msg.sub_type = DIALOG;
     				  msg.length   = sizeof(DD);
     				  *(DW*)msg.msg_buf = 102;

				  asm("pushl %0"::"r"(&msg));
     				  asm("pushl %0"::"r"(GUI_PID));
     				  asm("int $0x30"::"a"(3));

				  msg.type     = SET;
				  msg.sub_type = TEXTAREA;
				  msg.length   = 10; //sizeof(DW) + sizeof(DD);
				  msg.msg_buf[0] = 201;
				 *(DD*)(msg.msg_buf+2) = text;

				 __asm__ __volatile__("pushl %0"::"r"(&msg));
				 __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				 __asm__ __volatile__("int $0x30"::"a"(3));

  				}


				if(p < 0)
				 {
				  msg.type     = FINISHED;
				  msg.sub_type = BUT_TYPE;
				  msg.length   = sizeof(DD);
				  *(DW *)msg.msg_buf = 302;


				  asm("pushl %0"::"r"(&msg));
				  asm("pushl %0"::"r"(GUI_PID));
				  asm("int $0x30"::"a"(3));

				  msg.type     = HIDE;
	     			  msg.sub_type = DIALOG;
     				  msg.length   = sizeof(DD);
     				  *(DW*)msg.msg_buf = 102;

				  asm("pushl %0"::"r"(&msg));
     				  asm("pushl %0"::"r"(GUI_PID));
     				  asm("int $0x30"::"a"(3));

				  if(p == E_FS_NEXISTS)
				   {
				   }
				  else
				   {
				   }
				 }

				break;
			case 303 :
				msg.type     = FINISHED;
				msg.sub_type = BUT_TYPE;
				msg.length   = sizeof(DD);
				*(DW *)msg.msg_buf = 303;


				asm("pushl %0"::"r"(&msg));
				asm("pushl %0"::"r"(GUI_PID));
				asm("int $0x30"::"a"(3));

				msg.type     = HIDE;
	     			msg.sub_type = DIALOG;
     				msg.length   = sizeof(DD);
     				*(DW*)msg.msg_buf = 102;

				asm("pushl %0"::"r"(&msg));
     				asm("pushl %0"::"r"(GUI_PID));
     				asm("int $0x30"::"a"(3));
			}

                      break;

       	      case MENU_TYPE:
/*     			msg.type     = SET;
     			msg.sub_type = TEXTAREA;
     			msg.length   = 10;//sizeof(DW) + sizeof(DD);
			*(DD*)(msg.msg_buf+2) = itoa(*(DW*)msg1.msg_buf,10);
     			*(DW*)msg.msg_buf = 201;

			asm("pushl %0"::"r"(&msg));
     			asm("pushl %0"::"r"(GUI_PID));
     			asm("int $0x30"::"a"(3));*/

	      		switch(*(DW*)msg1.msg_buf)
			{
			case 1: //open
			strcpy(text,"");
			msg.type     = SET;
			msg.sub_type = TEXT;
			msg.length   = 10;//sizeof(DW) + sizeof(DD);
			*(DW*)msg.msg_buf = 301;
			*(DD*)(msg.msg_buf+2) = text;

			__asm__ __volatile__("pushl %0"::"r"(&msg));
			__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
			__asm__ __volatile__("int $0x30"::"a"(3));

			msg.type     = SHOW;
			msg.sub_type = DIALOG;
			msg.length   = sizeof(DD);
			*(DW*)msg.msg_buf = 102;

			asm("pushl %0"::"r"(&msg));
			asm("pushl %0"::"r"(GUI_PID));
			asm("int $0x30"::"a"(3));
			break;
			}
			break;
                }
                break;

         case WM_KEYPRESS:
                break;

         case WM_DESTROY:
	 	__asm__ __volatile__("int $0x30"::"a"(0));
                break;
       }

     }
     while(1);
}

 void recv(MSG *msg)
  {
   __asm__ __volatile__("pushl %0"::"r"(msg));
   __asm__ __volatile__("int $0x30"::"a"(4));
  }
