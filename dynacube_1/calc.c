 #include "string.h"
 #include "client_gui.h"
 #include "stdlib.h"


/* void num(DW in)
	{
			volatile MSG msg;
			msg.type     = GET;
  			msg.sub_type = TEXT;
     			msg.length   = 10;//sizeof(DW) + sizeof(DD);
     			*(DW*)msg.msg_buf = 15;
			*(DD*)(msg.msg_buf+2) = text;


			asm("pushl %0"::"r"(&msg));
     			asm("pushl %0"::"r"(GUI_PID));
  			asm("int $0x30"::"a"(3));

		char temp[2];
		if(!oppres)
		{
			v1= v1*10+in-1;
			v1pres = _true;
		}
		else
		{
			v2 = v2 *10 +in-1;
			v2pres = _true;
		}
	  temp[0] = in -1 +'0';
	  temp[1] = '\0';
	  if(strcmp(text,"0"))
		strcat(text,temp);
	  else
		strcpy(text,temp);

	msg.type     = SET;
	msg.sub_type = TEXT;
     	msg.length   = 10;//sizeof(DW) + sizeof(DD);
     	*(DW*)msg.msg_buf = 15;
	*(DD*)(msg.msg_buf+2) = text;


	asm("pushl %0"::"r"(&msg));
     	asm("pushl %0"::"r"(GUI_PID));
  	asm("int $0x30"::"a"(3));
}
	void operate(DW n)
	{
		if(!v1pres)
			if(respres)
			  v1 = res;
			else
			  v1 = 0;
		v1pres = _true;
		oper = n - 11;
		oppres = _true;
		strcpy(text,"");
	}
void cal()
	{
 	volatile MSG msg;
	if(v2pres)
	{
      	switch(oper)
	  {
	  case 0:
			 res = v1+v2;
			 break;
	  case 1:
		     res = v1-v2;
			 break;
	  case 2:
			 res = v1 *v2;
			 break;
	  case 3:
			 if(v2 != 0)
		      res = v1 / v2;
			 else
			  res = 0;
			 break;
	  }
	}
	else
	{
	if(v1pres)
	 res = v1;
	else if(respres)
	  res = res;
	else
	  res = 0;
	}

	if(res < 0)
	 strcpy(text,"-");
	else
	 strcpy(text,"");

	strcat(text,itoa(abs(res),10));

	msg.type     = SET;
	msg.sub_type = TEXT;
     	msg.length   = 10;//sizeof(DW) + sizeof(DD);
     	*(DW*)msg.msg_buf = 15;
	*(DD*)(msg.msg_buf+2) = text;


	asm("pushl %0"::"r"(&msg));
     	asm("pushl %0"::"r"(GUI_PID));
  	asm("int $0x30"::"a"(3));

	v1=v2=0;
	respres = _true;
	v1pres = v2pres = _false;
        oppres= _false;
	strcpy(text,"");
}*/

 int main()
 {
  volatile char text[4096];
  SDD v1,v2;
  boolean oppres,v1pres,v2pres,respres;
  DW oper,len;
  SDD res;
  volatile MSG msg;
  CREATE_INFO cr;
  COMP_CREATE_INFO cmp;
  RESIZE_INFO rs;
  SDD ret_val = -1;
  DB i,j,k;
  DW but_id;
  char op[] = "+-*/";
  char temp[2];

  	v1=v2=0;
	oppres= _false;
	v1pres = _false;
	v2pres = _false;
	respres = _true;
  //Creating the window

     msg.length = sizeof(cr);
     msg.type   = CREATE;
     msg.sub_type = WINDOW;
     cr.alias_id = 101;
     cr.cntr_id = 0;
     cr.height = 250;
     cr.width = 160;
     cr.style  = W_NORESIZE;
     cr.x = 300;
     cr.y = 200;
     strcpy(cr.title,"Calculator");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));

     asm("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 16;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 25;
     cmp.width = 130;
     cmp.x = 10;
     cmp.y = 10;
     cmp.style = DISABLED;
     strcpy(cmp.label,"0");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = BUTTON;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.style = 0;
     cmp.height = 30;
     cmp.width = 30;


	k=9;
	for(i=0;i<3;i++)
	 {
	  for(j=0;j<3;j++)
	   {
	    cmp.label[0] = ' ';
	    cmp.label[1] = k +'0';
	    cmp.label[2] = '\0';

	    cmp.alias_id = k+1;
            cmp.x = j*35 + 10;
            cmp.y = i*35 + 50;

	    memcpy(msg.msg_buf,&cmp,sizeof(cmp));

	    asm("pushl %0"::"r"(&msg));
            asm("pushl %0"::"r"(GUI_PID));
            asm("int $0x30"::"a"(3));

	    k--;
	   }
	 }
	    cmp.label[0] = ' ';
	    cmp.label[1] = k +'0';
	    cmp.label[2] = '\0';

	    cmp.alias_id = k+1;
            cmp.x = 10;
            cmp.y = 3*35 + 50;

	    memcpy(msg.msg_buf,&cmp,sizeof(cmp));

	    asm("pushl %0"::"r"(&msg));
            asm("pushl %0"::"r"(GUI_PID));
            asm("int $0x30"::"a"(3));

	    k = 11;
	    cmp.x = 3*35 + 10;

	 for(i=0;i<4;i++)
	 {
	    cmp.label[0] = ' ';
	    cmp.label[1] = op[i];
	    cmp.label[2] = '\0';

	    cmp.alias_id = k;
            cmp.y = i*35 + 50;

	    memcpy(msg.msg_buf,&cmp,sizeof(cmp));

	    asm("pushl %0"::"r"(&msg));
            asm("pushl %0"::"r"(GUI_PID));
            asm("int $0x30"::"a"(3));

	    k++;
	  }

	    cmp.label[0] = ' ';
	    cmp.label[1] ='=';
	    cmp.label[2] = '\0';

	    cmp.alias_id = 15;
            cmp.x = 45;
            cmp.y = 3*35 + 50;

	    memcpy(msg.msg_buf,&cmp,sizeof(cmp));

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
		  	but_id = *(DW *)msg.msg_buf;
			if(but_id >= 1 && but_id <= 10)
			 {
/*				msg.type     = GET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				*(DW*)msg.msg_buf = 16;
				*(DD*)(msg.msg_buf+2) = text;


				asm("pushl %0"::"r"(&msg));
				asm("pushl %0"::"r"(GUI_PID));
				asm("int $0x30"::"a"(3));*/

				if(!oppres)
				{
					v1= v1*10+but_id-1;
					v1pres = _true;
				}
				else
				{
					v2 = v2 *10 +but_id-1;
					v2pres = _true;
				}
				temp[0] = but_id -1 +'0';
				temp[1] = '\0';
				if(strcmp(text,"0") == 0)
					strcpy(text,temp);
				else
	 				strcat(text,temp);
/*				len = 0;
				while(text[len] != '\0')
				  len++;
    				text[len] = temp[0];
				text[len+1] = '\0';*/


				msg.type     = SET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				*(DW*)msg.msg_buf = 16;
				*(DD*)(msg.msg_buf+2) = text;


				asm("pushl %0"::"r"(&msg));
				asm("pushl %0"::"r"(GUI_PID));
				asm("int $0x30"::"a"(3));
			 }
		 	else if(but_id >= 11 && but_id <= 14)
			 {
			  if(!v1pres)
			   if(respres)
			    v1 = res;
			  else
			    v1 = 0;
			 v1pres = _true;
			 oper = but_id - 11;
			 oppres = _true;
			 strcpy(text,"");
			 }
			else if(but_id == 15)
			 {
				if(v2pres)
				{
				switch(oper)
				{
				case 0:
						res = v1+v2;
						break;
				case 1:
						res = v1-v2;
						break;
				case 2:
						res = v1 *v2;
						break;
				case 3:
						if(v2 != 0)
						res = v1 / v2;
						else
						res = 0;
						break;
				}
				}
				else
				{
				if(v1pres)
				res = v1;
				else if(respres)
				res = res;
				else
				res = 0;
				}

				if(res < 0)
				strcpy(text,"-");
				else
				strcpy(text,"");

				strcat(text,itoa(abs(res),10));

				msg.type     = SET;
				msg.sub_type = TEXT;
				msg.length   = 10;//sizeof(DW) + sizeof(DD);
				*(DW*)msg.msg_buf = 16;
				*(DD*)(msg.msg_buf+2) = text;


				asm("pushl %0"::"r"(&msg));
				asm("pushl %0"::"r"(GUI_PID));
				asm("int $0x30"::"a"(3));

				v1=v2=0;
				respres = _true;
				v1pres = v2pres = _false;
				oppres= _false;
				strcpy(text,"");
			 }
			msg.type     = FINISHED;
                        msg.sub_type = BUT_TYPE;
                        msg.length   = sizeof(DD);
			*(DW *)msg.msg_buf = but_id;


                        asm("pushl %0"::"r"(&msg));
                        asm("pushl %0"::"r"(GUI_PID));
                        asm("int $0x30"::"a"(3));
			break;
		}
 	}
     }
}

