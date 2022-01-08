/***************************************************************************
                          menu.h  -  description
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

 #ifndef __MENU_H
 #define __MENU_H

 extern "C"
 {
	 #include "graphics.h"
 }

 	class menu
  {
		public:
			void *cnt_ptr;
			DW x, y, width, height;
			DB no_item;
			DW __pid;

			MENUITEM mnuitem[MN_MAX_ITEM];
			COLOR *buf;

			void paint();
			void menu_init(void *_cnt_ptr, DB _no_item, MENUITEM *_mnuitem, DW _pid);
			SDB process(DW,DW);
			void menu_restore();
	};

 #endif
