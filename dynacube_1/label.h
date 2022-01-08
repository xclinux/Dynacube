/***************************************************************************
                          label.h  -  description
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
 #ifndef __LABEL_H
 #define __LABEL_H

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

 #define MIN_LABEL_WIDTH 20
 #define MIN_LABEL_HEIGHT 10

 class label:public component
 {
   public :
   char lbl[15];

   void label_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_label);
   void setLabel(char *text);
   char* getLabel();
   void paint();
 };


 #endif
