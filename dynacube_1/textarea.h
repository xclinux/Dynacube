                /***************************************************************************
                          textarea.h  -  description
                             -------------------
    begin                : Mon Mar 1 2004
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
 #ifndef __TEXTAREA_H
 #define __TEXTAREA_H

 #ifdef __cplusplus
   extern "C"
   {
     #include "ktypes.h"
     #include "stdlib.h"
     #include "graphics.h"
     #include "string.h"
     #include "keyboard.h"
   }
 #else
      #include "ktypes.h"
      #include "stdlib.h"
      #include "graphics.h"
      #include "string.h"
      #include "keyboard.h"
 #endif

 #include "component.h"
 #include "window.h"
 #include "frame.h"

 #define MIN_TEXTAREA_WIDTH 20
 #define MIN_TEXTAREA_HEIGHT 60
 #define TEXTAREA_COLOR   0xFFFF

 #define TEXTAREA_ROWS  100
 #define TEXTAREA_COLS  400

 #define Y_OFFSET 3
 #define X_OFFSET 2

 class textarea:public component
 {
   public :
   char txt[TEXTAREA_ROWS][TEXTAREA_COLS+1];
   DW st_row;
   DW st_col;
   DW visi_rows;
   DW visi_cols;
   DW cur_x,cur_y;
   DW sel_stx,sel_sty,sel_enx,sel_eny;
   DW max_row;
   bool is_sel;

   void textarea_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_txt);
   void setText(char *text);
   void getText(char *text);
   void paint();
   void react(DW _x,DW _y);
   SDW  ptcmp(DW x1,DW y1,DW x2,DW y2);
   void keyPress(DW state,DW ch);
   void updateCursor();
   void copy();
   void cut();
   void paste();
 };


 #endif
