
/***************************************************************************
                          folderview.cpp  -  description
                             -------------------
    begin                : Sun Feb 8 2004
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

 #include "folderview.h"
 

   void folderview::folderview_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_dirname)
   {
    strcpy(dirname,_dirname);
    
    if(_width < MIN_FV_WIDTH)
      _width = MIN_FV_WIDTH;
      
    if(_height < MIN_FV_HEIGHT)
      _height = MIN_FV_HEIGHT;

    comp_init(FOLDERVIEW_TYPE,_id,_parent_id,_cnt_type,_cnt_ptr,_alias_id,_x,_y,_width,_height,_style);
   }
   
   void folderview::paint()
   {
    window *win_ptr;
    frame *frm_ptr;
    DW _x,_y,_width,_height;
    DB tmp[255];

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
                         fillrect(x+_x, y+_y, width, height,FV_BASE);
                         emboss3D(x+_x, y+_y, width, height,0,_true,1);
//                         drawstring(x+_x+X_OFFSET,x+_x+Y_OFFSET,dirname);
                         drawFiles(x+_x,y+_y);
                      }
                      else
                      {
//                         fillrect(x+_x, y+_y, width, height,FV_BASE);
//                         emboss3D(x+_x, y+_y, width, height,0,_true,1);
                      }
                      break;
//      case FRM_TYPE :
//                      frm_ptr = (frame *) cnt_ptr;
//                      if((x + width <  frm_ptr->width) && (y + height < frm_ptr->height))
//                         rect(x+frm_ptr->x,y+frm_ptr->y,width,height);
    }

   }

   void folderview::drawFiles(DW x, DW y)
   {
    SDW p,res;
    DIRENT ds;
    DW curx, cury;

    curx = x;
    cury = y;

    /*
     Things to do
     ============
     draw folder/file @ (curx+X_OFFSET,cury+Y_OFFSET)
     print name @ (curx+X_OFFSET,cury+Y_OFFSET+ICON_HEIGHT)
    */

    //opendir(dirname);   
    //asm("pushw %eax");
    //asm("popw %0"::"r"(p));

    //Summa

    p = opendir(dirname);
    
    if(p != -1)
    {

     while((res = readdir(p,&ds)) == 0)//== 0)
     {
        drawIcon(curx + X_OFFSET, cury + Y_OFFSET, &folder[0][0]);
        drawstring(curx + X_OFFSET,cury + 2*Y_OFFSET + ICON_HEIGHT,ds.name);
//        curx += X_OFFSET + ICON_WIDTH;
        cury += 3*Y_OFFSET + ICON_HEIGHT;
        
//        res--;
        
     	  //do_readdir(p,&ds);
  	    //asm("pushw %eax");
     	  //asm("popw %0"::"r"(res));        
     }
     closedir(p);
    }
     
   }

   
   void folderview::react(DW _x,DW _y)
   {
   }

