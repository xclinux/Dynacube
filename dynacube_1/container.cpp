/***************************************************************************
                          container.cpp  -  description
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

 #include "container.h"
 #include "component.h"
 #include "cursor.h"
 #include "utility.h"

      void container::cntr_init(DW _id, DW _parent_id, DW _x, DW _y, DW _width, DW _height)
      {
       id = _id;
       parent_id = _parent_id;
       x = _x;
       y = _y;
       width = _width;
       height = _height;
       num_comps = 0;
       num_conts = 0;
      }

      void container::attachComponent(component *cmp)
      {
        comp[num_comps] = cmp;
        comp_focus = comp[num_comps];            
        num_comps++;
      }

