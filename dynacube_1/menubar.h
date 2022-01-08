/***************************************************************************
                          menubar.h  -  description
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

 #ifndef __MENUBAR_H
 #define __MENUBAR_H

 #ifdef __cplusplus
   extern "C"
   {
     #include "ktypes.h"
     #include "stdlib.h"
     #include "graphics.h"
     #include "string.h"
     #include "keyboard.h"
		 #include "gui_common.h"
   }
 #else
      #include "ktypes.h"
      #include "stdlib.h"
      #include "graphics.h"
      #include "string.h"
      #include "keyboard.h"
 #endif

 #define MB_TEXT_COLOR   0x0
 #define MENUBAR_COLOR   0xFF7D //0x9CD1
 #define MENUBAR_HEIGHT  TITLE_HEIGHT

 #define MB_MAX_CHAR	10
 #define MB_MAX_MENU	6

 #include "menu.h"

 class menubar
 {
   public :
	  DW x, y, width, height;
    void *cnt_ptr;
   	DB no_menu;
    SDB cur_menu;
    DD user_menu_addr;

	  struct
	  {
     char label[MB_MAX_CHAR];
     menu *menu_ptr;
	  }mnu[MB_MAX_MENU];


   void menubar_init(void *_cnt_ptr,DW _x,DW _y,DW _width,DW _height,DD _usr_menu_addr, DW _pid);
   void paint();
   SDB process(DW _x,DW _y);
   void keyPress(DW state,DW ch);
	 void freeAll();   
 };


 #endif 
