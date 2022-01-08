/***************************************************************************
                          menu.cpp  -  description
                             -------------------
    begin                : Mon Mar 29 2004
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

 #include "menu.h"
 #include "menubar.h"

 #include "window.h"

 extern "C"
 {
	 #include "gui_common.h"
 }

 #define MENU_COLOR	MENUBAR_COLOR
 DB mn_summa_x_offset = 5, mn_summa_y_offset = 5;

 void menu::paint()
 {
	 DB i;

	 getimage(x,y,width+2,height+2,buf);
//	 putimage(10,10,width+2,height+2,buf);
   fillrect(x,y,width,height,MENU_COLOR);

   for(i = 0 ; i < no_item ; i++)
   {
		 cprint(x+mn_summa_x_offset,y+mn_summa_y_offset*(i+1)+i*10,mnuitem[i].lbl,0x0);
	 }

	 emboss3D(x,y,width,height,0/*LEFT|BOTTOM|RIGHT*/,_false,1);
 }

 SDB menu::process(DW _x, DW _y)
 {
	 DB i;
	 MSG msg;

	 if(iswithin(_x,_y,x,y,width,height))
	 {
	   for(i = 0 ; i < no_item ; i++)
	   {
			 if(iswithin(_x,_y,x,y+mn_summa_y_offset*(i+1)+i*10,width,mn_summa_y_offset+10))
       {
//				 rect(390,390,50,50);
//				 ginfo(400,400,itoa(mnuitem[i].cmdCode,10));
//				 ginfo(400,410,itoa(__pid,10));
		     msg.type     = WM_CLICKED;
    		 msg.sub_type = MENU_TYPE;
		     msg.length   = sizeof(DD);
		     *(DW*)msg.msg_buf = mnuitem[i].cmdCode;

		     asm("pushl %0"::"r"(&msg));
		     asm("pushl %0"::"r"(__pid));
		     asm("int $0x30"::"a"(3));
			 }
		 }
	   return 0;
	 }
	 else
	 {
		restoreImage(mcurx,mcury);
	 	return -1;
	 }
 }

 void menu::menu_restore()
 {
	 putimage(x,y,width+2,height+2,buf);
 }

 void menu::menu_init(void *_cnt_ptr, DB _no_item, MENUITEM *_mnuitem, DW _pid)
 {
	DB i;

	cnt_ptr = _cnt_ptr;
	no_item = _no_item;
	__pid 	= _pid;

	width = MN_MAX_CHAR*7;
	height = (no_item) * (10 + mn_summa_y_offset);

//	ginfo(500,400,itoa(no_item,10));
//	ginfo(500,420,_mnuitem[0].lbl);
	
	for(i = 0 ; i < no_item ; i++)
	{
		strcpy(mnuitem[i].lbl,_mnuitem[i].lbl);
		mnuitem[i].cmdCode = _mnuitem[i].cmdCode;
	}

	buf	= (COLOR *)kmalloc((width+2)*(height+2)*2);
 }
