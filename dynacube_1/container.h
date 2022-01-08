/***************************************************************************
                          container.h  -  description
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

#ifndef __CONTAINER_H
#define __CONTAINER_H

  #include "gui.h"
  #include "component.h"
  
  #define MAX_COMPONENT 40
  #define MAX_CONTAINER 10

   
  class container
  {
    public:      
      DW id, parent_id;
      
      DW x, y, width, height;

      component *comp_focus;
      
      DW num_comps;
      component *comp[MAX_COMPONENT];
      
      DW num_conts;
      container *cont[MAX_CONTAINER];

      void cntr_init(DW _id, DW _parent_id, DW _x, DW _y, DW _width, DW _height);
      void attachComponent(component *cmp);      
 };


#endif 