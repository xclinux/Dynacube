/***************************************************************************
                          button.cpp  -  description
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

 #include "button.h"

 void button::but_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_label)
 {
    state = true; // Projecting out
    memcpy(label,_label,strlen(_label));
    comp_init(BUT_TYPE,_id,_parent_id,_cnt_type,_cnt_ptr,_alias_id,_x,_y,_width,_height,_style);
 }

 void button::paint()
  {
    window *win_ptr;
    frame *frm_ptr;
    DW _x,_y,_width,_height;
    DW i;

    COLOR color[] = {0xE5F1, 0xBC4D, 0xE637, 0xDE99, 0xCDE7, 0xB5DD, 0xAD57, 0xA537, 0x9D53, 0x9CD1, 0x9533, 0x94D9, 0x8557, 0x6C75};

    switch(cnt_type)
    {
      case WIND_TYPE :
                      win_ptr = (window *) cnt_ptr;
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

                      if((x + width < _width) && (y + height < _height))
                      {
//                        for(i = 0 ; i < 14 ;i++)
//                        {
                         fillrect(x+_x, y+_y, width, height,BUTTON_COLOR);//color[i]);
                         drawstring(x+_x+width/8,y+_y+height/4,label);
                         if(state)
                           emboss3D(x+_x, y+_y, width, height,0,_false,1);
                         else
                           emboss3D(x+_x, y+_y, width, height,0,_true,1);
//                         mvBuf2Svga();
//                         delay(0xFFFF);
//                        }

                      }
//                      else
//                      {
//                         rect(x+_x, y+_y, width, height);
//                         emboss3D(x+_x, y+_y, width, height,0,_false,2);
//                      }
                      break;
//      case FRM_TYPE :
//                      frm_ptr = (frame *) cnt_ptr;
//                      if((x + width <  frm_ptr->width) && (y + height < frm_ptr->height))
//                         rect(x+frm_ptr->x,y+frm_ptr->y,width,height);

    }
  }


  void button::react()
  {
    window *win_ptr = (window *)cnt_ptr;
    DW i,j;

    if(state)
    {
      state = false;
      win_ptr->deactivate();
    }
    else
    {
      state = true;
      win_ptr->activate();            
    }

    restoreImage(mcurx,mcury);
    
    paint();
      
    if(mouse_inited)
    {
      getimage(mcurx,mcury,16,16, &mouseimg[0][0]);

      for(i = mcurx ; i < mcurx+16 ; i++)
      {
        for(j = mcury ; j < mcury+16 ; j++)
        {
          if(mouseptr[j-mcury][i-mcurx])
          {
            setPixel(i,j,0x0);
          }
        }
      }
    }
      
    mvBuf2Svga();      
  }
 
 
