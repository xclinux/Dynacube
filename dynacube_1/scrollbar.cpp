/***************************************************************************
                          scrollbar.cpp  -  description
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
 #include "scrollbar.h"
 
 void scrollbar::scrollbar_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height)
 {
    scroll_offset = 0;
    scaling = 1;
    comp_init(SCROLLBAR_TYPE,_id,_parent_id,_cnt_type,_cnt_ptr,_alias_id,_x,_y,_width,_height);   
 }
 
 void scrollbar::paint()
 {
    window *win_ptr;
    frame *frm_ptr;
    DW _x,_y,_width,_height;

    switch(cnt_type)
    {
      case WIND_TYPE :
                      win_ptr = (window *) cnt_ptr;
                      if(win_ptr->style & W_MAXIMIZE)
                       {
                         _x = BORDER_WIDTH;
                         _y = TITLE_HEIGHT + BORDER_HEIGHT ;
                         _width  = SCREEN_WIDTH;
                         _height = SCREEN_HEIGHT;
                       }
                      else
                       {
                         _x = win_ptr->x + BORDER_WIDTH;
                         _y = win_ptr->y + TITLE_HEIGHT + BORDER_HEIGHT ;
                         _width = win_ptr->width;
                         _height = win_ptr->height;
                       }

                      if((x + width < _width) && (y + height < _height))
                      {
                          drawstring(x,y,"SCROLLBAR");
//                         fillrect(x+_x, y+_y, width, height,BUTTON_COLOR);
//                         drawstring(x+_x+width/8,y+_y+height/4,label);
//                         emboss3D(x+_x, y+_y, width, height,0,_false,2);
                      }
                      else
                      {
//                         rect(x+_x, y+_y, width, height);
//                         emboss3D(x+_x, y+_y, width, height,0,_false,2);
                      }
                      break;
//      case FRM_TYPE :
//                      frm_ptr = (frame *) cnt_ptr;
//                      if((x + width <  frm_ptr->width) && (y + height < frm_ptr->height))
//                         rect(x+frm_ptr->x,y+frm_ptr->y,width,height);

    }
  }
