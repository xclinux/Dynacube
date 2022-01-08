/***************************************************************************
                          component.cpp  -  description
                             -------------------
    begin                : Thu Feb 19 2004
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

 #include "component.h"

 void component::comp_init(DW _type,DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style)
 {
       type = _type;
       id = _id;
       parent_id = _parent_id;
       cnt_type = _cnt_type;
       cnt_ptr = _cnt_ptr;
       alias_id  = _alias_id;
       x = _x;
       y = _y;
       width = _width;
       height = _height;
       style = _style;
 }


   void component::deactivate()
    {
     style |= DISABLED;
    }

   void component::activate()
    {
     style &= DISABLED;
    }
