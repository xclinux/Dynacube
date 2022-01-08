/***************************************************************************
                          frame.cpp  -  description
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

 #include "frame.h"


 void frame::frm_init(DW _id, DW _parent_id, DW _alias_id, DW _x, DW _y, DW _width, DW _height, DD _style,char *_title)
 {
  this->cntr_init(_id,_parent_id,_x,_y,_width,_height);

  this->style = _style;
  memcpy(this->title,_title,strlen(_title));
 }

 void frame::paint()
 {
 }

 void frame::freeAll()
 {
       DW i;

         for(i = 0;i<num_comps;)
         {
            if(comp[i] != NULL)
            {
              free((void*)comp[i]);
              i++;
            }
         }
        for(i = 0;i<num_conts;)
         {
            if(cont[i] != NULL)
            {
              ((frame *)cont[i])->freeAll();
              free((void *)cont[i]);
              i++;
            }
         }   
 }

