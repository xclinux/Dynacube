/***************************************************************************
                          utility.cpp  -  description
                             -------------------
    begin                : Sat Mar 6 2004
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

 #include "utility.h"
 
 POINT getAbsLoc(component *comp)
 {
    POINT pt;
    window *win_ptr;
    frame *frm_ptr;
    DW _x,_y,_width,_height;

    pt.x = 0;
    pt.y = 0;

    switch(comp->cnt_type)
    {
      case WIND_TYPE :
                      win_ptr = (window *) comp->cnt_ptr;
                      if(win_ptr->style & W_MAXIMIZE)
                       {
                         _x = BORDER_WIDTH;
                         _y = TITLE_HEIGHT + BORDER_HEIGHT + ((win_ptr->hasMenu) ? MENUBAR_HEIGHT : 0);
                         _width  = SCREEN_WIDTH;
                         _height = SCREEN_HEIGHT;
                       }
                      else
                       {
                         _x = win_ptr->x + BORDER_WIDTH;
                         _y = win_ptr->y + TITLE_HEIGHT + BORDER_HEIGHT + ((win_ptr->hasMenu) ? MENUBAR_HEIGHT : 0);
                         _width = win_ptr->width;
                         _height = win_ptr->height;
                       }

                      if((comp->x + comp->width < _width) && (comp->y + comp->height < _height))
                      {
                         pt.x = comp->x+_x;
                         pt.y = comp->y+_y;
                      }
                      break;
    }


    return pt;

 }
