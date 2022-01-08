/***************************************************************************
                          text.h  -  description
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

 #ifndef __TEXT_H
 #define __TEXT_H

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
 #include "utility.h"
 #include "cursor.h"
 #include "clipboard.h"

 #define MIN_TEXT_WIDTH 10
 #define MIN_TEXT_HEIGHT 12
 #define TEXT_COLOR   0xFFFF

 #define CHAR_WIDTH   5
 #define CHAR_HEIGHT  7
 
 #define Y_OFFSET 3
 #define X_OFFSET 2
 
 #define TEXT_MAX 1024

 class text:public component
 {
   public :
   char txt[TEXT_MAX];
   DW total_chars, allow_chars;
   DW start;
   DW curs;   
   DW sel_st,sel_en;
   bool is_sel;

   void text_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_txt);
   void setText(char *text);
   void getText(char *text);
   void paint();
   void update_cursor(DW no);
   void react(DW _x,DW _y);
   void keyPress(DW state,DW ch);
   void copy();
   void cut();
   void paste();
 };


 #endif
