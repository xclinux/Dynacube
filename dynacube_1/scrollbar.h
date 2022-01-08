/***************************************************************************
                          scrollbar.h  -  description
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
 #ifndef __SCROLLBAR_H
 #define __SCROLLBAR_H

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

 #define MIN_SCROLLBAR_WIDTH 20
 #define MIN_SCROLLBAR_HEIGHT 10

 #define VERTICAL   0
 #define HORIZONTAL 1

 #define SCRL_THICKNESS  10
 
 class scrollbar:public component
 {
   public :
     DB style;
     DB scroll_offset;
     DB scaling;

   void scrollbar_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DW _style);
   void paint();
 };



 #endif