/***************************************************************************
                          button.h  -  description
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

 #ifndef __BUTTON_H
 #define __BUTTON_H

 #ifdef __cplusplus
   extern "C"
   {
     #include "ktypes.h"
     #include "stdlib.h"
     #include "graphics.h"
     #include "string.h"
   }
 #else
      #include "ktypes.h"
      #include "stdlib.h"
      #include "graphics.h"
      #include "string.h"
 #endif

 #include "component.h"
 #include "window.h"
 #include "frame.h"

 #define MIN_BUT_WIDTH 20
 #define MIN_BUT_HEIGHT 10
 #define BUTTON_COLOR   0xDE99 //0x8BF1 //0xB577 //0xD5F7

 class button:public component
 {
   public :   
   char label[15];
   bool state;

   void but_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_label);
   void paint();
   void react();   
 };



 #endif
