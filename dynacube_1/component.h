/***************************************************************************
                          component.h  -  description
                             -------------------
    begin                : Sat Jan 31 2004
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

 #ifndef __COMPONENT_H
 #define __COMPONENT_H

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
 
 #define WIND_TYPE 1
 #define FRM_TYPE  2

 //styles
 #define DISABLED 1

 //component types
 
 #define BUT_TYPE          1
 #define TEXT_TYPE         2
 #define TEXTAREA_TYPE     3
 #define LABEL_TYPE        4
 #define SCROLLBAR         5
 #define FOLDERVIEW_TYPE  20
 
 #define BORDER_WIDTH  2
 #define BORDER_HEIGHT 2
 #define TITLE_HEIGHT  20

 #define ST_SHIFT  0x1
 #define ST_CAPS   (0x1<<1)
 #define ST_CNTL   (0x1<<2)
 #define ST_ALT    (0x1<<3)
 
 
 class component
 {
   public:
   DW type;
   DW id, parent_id,alias_id;
   DW x, y, width, height;
   void *cnt_ptr;
   DB cnt_type;
   DD style;

   void comp_init(DW _type,DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style);
   void activate();
   void deactivate();
 };

 #endif
