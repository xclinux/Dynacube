/***************************************************************************
                          cursor.h  -  description
                             -------------------
    begin                : Sat Mar 6 2004
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

 #ifndef __CURSOR_H
 #define __CURSOR_H

 #include "ktypes.h"
 #include "gui_common.h"

 extern "C"
 {
  #include "graphics.h"
 }
 
 #define VISIBLE  0
 #define HIDDEN   1
 
 #define CURSOR_HEIGHT 11


 class cursor
 {
   public:
    DW x,y;
    DW state;
    DB no_times;

    void cursor_init();
    void setCursor(POINT pt);
    POINT getCursor();

    void show();
    void hide();
    void paint();
    void erase();
 };

 extern cursor csr;
 
 #endif

 