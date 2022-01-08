/***************************************************************************
                          frame.h  -  description
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

 #ifndef __FRAME_H
 #define __FRAME_H

 #ifdef __cplusplus
   extern "C"
   {
     #include "string.h"
     #include "graphics.h"
   }
 #else
      #include "string.h"
      #include "graphics.h"
 #endif

 #include "container.h"
 
  class frame: public container
  {
    public:
      DD style;
      char title[20];

    void frm_init(DW _id, DW _parent_id, DW _alias_id, DW _x, DW _y, DW _width, DW _height, DD _style,char *_title);
    void paint();
    void freeAll();
  };


 #endif