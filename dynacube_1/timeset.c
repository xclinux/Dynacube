 #include "string.h"
 #include "client_gui.h"
typedef struct
{
	char mm,dd;
	int yy;
}DATE;
typedef struct
{
	int hour,min,sec;
}TIME;

 int main()
 {
  volatile MSG msg;
  volatile MSG msg1;
  DATE dt;
  TIME tm;
  CREATE_INFO cr;
  COMP_CREATE_INFO cmp;
  RESIZE_INFO rs;
  SDD ret_val = -1;
  DB i;
  volatile char text[4096];

     msg.length = sizeof(cr) + 1;
     msg.type   = CREATE;
     msg.sub_type = WINDOW;
     cr.alias_id = 101;
     cr.cntr_id = 0;
     cr.height = 125;
     cr.width = 210;
     cr.style  = W_NORESIZE;
     cr.x = 500;
     cr.y = 330;
     strcpy(cr.title,"Time-Date");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.type   = CREATE;
     msg.sub_type = DIALOG;
     msg.length = sizeof(cr);
     cr.alias_id = 102;
     cr.cntr_id = 101;
     cr.height = 80;
     cr.width = 180;
     cr.style  = 0;
     cr.x = 515;
     cr.y = 350;
     strcpy(cr.title,"Error");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.length = sizeof(cmp) + 1;
     msg.sub_type = LABEL;
     cmp.alias_id = 301;
     cmp.cntr_id = 102;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 10;
     cmp.width = 70;
     cmp.x = 2;
     cmp.y = 10;
     cmp.style = 0;
     strcpy(cmp.label,"Error in values entered.");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = BUTTON;
     cmp.alias_id = 302;
     cmp.cntr_id = 102;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 20;
     cmp.x = 60;
     cmp.y = 30;
     cmp.style = 0;
     strcpy(cmp.label,"OK");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));



     msg.length = sizeof(cmp) + 1;
     msg.sub_type = LABEL;
     cmp.alias_id = 201;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 10;
     cmp.x = 5;
     cmp.y = 10;
     cmp.style = 0;
     strcpy(cmp.label,"DATE(dd/mm/yy)");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = LABEL;
     cmp.alias_id = 202;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 10;
     cmp.x = 5;
     cmp.y = 40;
     cmp.style = 0;
     strcpy(cmp.label,"TIME(hh/mm/ss)");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));


     msg.sub_type = BUTTON;
     cmp.alias_id = 203;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 120;
     cmp.x = 40;
     cmp.y = 70;
     cmp.style = 0;
     strcpy(cmp.label,"SET TIME-DATE");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 204;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 15;
     cmp.width = 25;
     cmp.x = 110;
     cmp.y = 10;
     strcpy(cmp.label,"");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 205;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 15;
     cmp.width = 25;
     cmp.x = 140;
     cmp.y = 10;
     strcpy(cmp.label,"");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 206;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 15;
     cmp.width = 25;
     cmp.x = 170;
     cmp.y = 10;
     strcpy(cmp.label,"");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 207;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 15;
     cmp.width = 25;
     cmp.x = 110;
     cmp.y = 40;
     strcpy(cmp.label,"");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 208;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 15;
     cmp.width = 25;
     cmp.x = 140;
     cmp.y = 40;
     strcpy(cmp.label,"");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 209;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 15;
     cmp.width = 25;
     cmp.x = 170;
     cmp.y = 40;
     strcpy(cmp.label,"");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 101;

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     __asm__ __volatile__("pushl %eax");
     __asm__ __volatile__("popl %0"::"r"(ret_val));

     i = 0;

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
			case 203:
				msg.type     = FINISHED;
				msg.sub_type = BUT_TYPE;
				msg.length   = sizeof(DD);
				msg.msg_buf[0] = 203;

				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				msg.type     = GET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				msg.msg_buf[0] = 204;
				*(DD*)(msg.msg_buf+2) = text;


				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				dt.dd = atoi(text);

				msg.type     = GET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				msg.msg_buf[0] = 205;
				*(DD*)(msg.msg_buf+2) = text;


				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				dt.mm = atoi(text);

				msg.type     = GET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				msg.msg_buf[0] = 206;
				*(DD*)(msg.msg_buf+2) = text;


				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				dt.yy = atoi(text);

				msg.type     = GET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				msg.msg_buf[0] = 207;
				*(DD*)(msg.msg_buf+2) = text;


				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				tm.hour = atoi(text);

				msg.type     = GET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				msg.msg_buf[0] = 208;
				*(DD*)(msg.msg_buf+2) = text;


				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				tm.min = atoi(text);

				msg.type     = GET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				msg.msg_buf[0] = 209;
				*(DD*)(msg.msg_buf+2) = text;


				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				tm.sec = atoi(text);
				if(dt.dd > 0 && dt.dd < 32 && dt.mm > 0 && dt.mm < 13 && dt.yy > 0 && dt.yy < 100 && tm.hour > 0 && tm.hour < 25 && tm.min > 0 && tm.min < 61 && tm.sec > 0 && tm.sec < 61)
				{
				__asm__ __volatile__("pushl %%eax"::"a"(&dt));
				__asm__ __volatile__("int $0x30"::"a"(31));

				__asm__ __volatile__("pushl %%eax"::"a"(&tm));
				__asm__ __volatile__("int $0x30"::"a"(33));
				//exit
				__asm__ __volatile__("int $0x30"::"a"(0));
				}
				else
				{
				  	msg.type     = SHOW;
     					msg.sub_type = DIALOG;
     					msg.length   = sizeof(DW);
     					msg.msg_buf[0] = 102;

					asm("pushl %0"::"r"(&msg));
     					asm("pushl %0"::"r"(GUI_PID));
     					asm("int $0x30"::"a"(3));
				}

			        break;
			case 302 :
				msg.type     = FINISHED;
				msg.sub_type = BUT_TYPE;
				msg.length   = sizeof(DD);
				*(DW*)msg.msg_buf = 302;


				__asm__ __volatile__("pushl %0"::"r"(&msg));
				__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
				__asm__ __volatile__("int $0x30"::"a"(3));

				msg.type     = HIDE;
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
