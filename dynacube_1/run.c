 #include "string.h"
 #include "client_gui.h"

 int main()
 {
  volatile MSG msg;
  CREATE_INFO cr;
  COMP_CREATE_INFO cmp;
  RESIZE_INFO rs;
  SDD ret_val = -1;
  DB i;
  volatile char text[4096];

     msg.length = sizeof(cr);
     msg.type   = CREATE;
     msg.sub_type = WINDOW;
     cr.alias_id = 101;
     cr.cntr_id = 0;
     cr.height = 100;
     cr.width = 200;
     cr.style  = 0;
     cr.x = 5;
     cr.y = 465;
     strcpy(cr.title,"Run Command");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.sub_type = LABEL;
     cmp.alias_id = 201;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 50;
     cmp.x = 5;
     cmp.y = 10;
     cmp.style = 0;
     strcpy(cmp.label,"COMMAND");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));


     msg.sub_type = BUTTON;
     cmp.alias_id = 202;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 100;
     cmp.x = 50;
     cmp.y = 40;
     cmp.style = 0;
     strcpy(cmp.label,"RUN COMMAND");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     __asm__ __volatile__("pushl %0"::"r"(&msg));
     __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
     __asm__ __volatile__("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 203;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 110;
     cmp.x = 70;
     cmp.y = 10;
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
       __asm__ __volatile__("pushl %0"::"r"(&msg));
       __asm__ __volatile__("int $0x30"::"a"(4));

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
     			msg.msg_buf[0] = 203;
			*(DD*)(msg.msg_buf+2) = text;


			__asm__ __volatile__("pushl %0"::"r"(&msg));
     			__asm__ __volatile__("pushl %0"::"r"(GUI_PID));
  			__asm__ __volatile__("int $0x30"::"a"(3));

			__asm__ __volatile__("pushl %%eax"::"a"(text));
           		__asm__ __volatile__("movl $0x1, %eax");
           		__asm__ __volatile__("int $0x30");


                        msg.type     = FINISHED;
                        msg.sub_type = BUT_TYPE;
                        msg.length   = sizeof(DD);
			msg.msg_buf[0] = 202;


                        __asm__ __volatile__("pushl %0"::"r"(&msg));
                        __asm__ __volatile__("pushl %0"::"r"(GUI_PID));
                        __asm__ __volatile__("int $0x30"::"a"(3));
			
			//exit
	                __asm__ __volatile__("int $0x30"::"a"(0));

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
