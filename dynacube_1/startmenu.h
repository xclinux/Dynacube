/***************************************************************************
                          startmenu.h  -  description
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
 #ifndef __STARTMENU_H
 #define __STARTMENU_H

 #include "gui_common.h"

 #ifdef __cplusplus
 extern "C"
 {
   #include "graphics.h"
 }
 #else
   #include "graphics.h"
 #endif

 #define MENU_X_OFFSET 10
 #define MENU_Y_OFFSET 30

 
 
 class startmenu
 {
   public:
      boolean start_opened;
      DW x, y, width, height;
      COLOR *bk_buf;
      COLOR skincolor;
      DW no_option;

   void startmenu_init();
   void draw();
   SDB processClick(DW _x, DW _y);
   
 };

 #endif
