/***************************************************************************
                          window.h  -  description
                             -------------------
    begin                : Wed Jan 28 2004
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
#ifndef __WINDOW_H
#define __WINDOW_H

 #ifdef __cplusplus
   extern "C"
   {
     #include "stdlib.h"
     #include "graphics.h"
     #include "string.h"
   }   
 #else
      #include "stdlib.h"
      #include "graphics.h"
      #include "string.h"
 #endif

  #include "gui_common.h"
  #include "container.h"
  #include "paintcomp.h"
  #include "menubar.h"

  #define FILL_COLOR    0xBE19

  #define BORDER_COLOR  0xBAF7 //0x9A73 //0x79EF //0x1863 //0x07E0
  #define BORDER_WIDTH  2
  #define BORDER_HEIGHT 2
  
  #define TITLE_HEIGHT  20
  #define TITLE_COLOR   0xC599 //0xA4D5 //0xF52D //0x4
  #define SUMMA_HEIGHT  10
  #define SUMMA_WIDTH   10
  #define MIN_WIDTH     100
  #define MIN_HEIGHT    50
  


  class window: public container
  {
    public:
      DD style;
      char title[50];
      bool hasMenu;
      menubar *MenuBar;
      COLOR *buf;
      window *diag;
      DB is_diag;

    void win_init(DW _id, DW _parent_id, DW _x, DW _y, DW _width, DW _height, DD _style,DW _is_diag, char * _title);
    void paint_win();
    void freeAll();
    ENTITY findEntity(DW x,DW y);

    void activate();
    void deactivate();
    void keyPress(DW state, DW ch);
    void menuInit(DD _user_menu_addr, DW _pid);
    SDB processMenu(DW x,DW y);
    void move(SDW del_x, SDW del_y);
    void attachDialog(window *diag_ptr);
    void detachDialog();
  };



#endif
