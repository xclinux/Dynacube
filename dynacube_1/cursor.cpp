/***************************************************************************
                          cursor.cpp  -  description
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

 #include "cursor.h"

  void cursor::cursor_init()
  {
    no_times = 0;
    x = 400;
    y = 300;
    state = HIDDEN;
  }
  
  void cursor::setCursor(POINT pt)
  {
    erase();
    x = pt.x;
    y = pt.y;
  }

  void cursor::erase()
  {
    if(state == VISIBLE)
    {
        line(x,y,x,y+CURSOR_HEIGHT,0xFFFF);
        mvMini2Svga(x,y,1,CURSOR_HEIGHT);
    }    
  }
  
  POINT cursor::getCursor()
  {
    POINT pt;
    pt.x = x;
    pt.y = y;
    return pt;
  }
  

  void cursor::show()
  {
    state = VISIBLE;
    paint();
  }
  
  void cursor::hide()
  {
    erase();
    state = HIDDEN;
  }

  void cursor::paint()
  {
    if(!graphics)
      return;
      
    if(state == VISIBLE)
    {
      if(no_times < 20)
      {
        line(x,y,x,y+CURSOR_HEIGHT,0x0);
        no_times++;        
      }
      else if(no_times < 23)
      {
        line(x,y,x,y+CURSOR_HEIGHT,0xFFFF);
        no_times++;        
      }
      else
        no_times = 0;
      
      mvMini2Svga(x,y,1,CURSOR_HEIGHT);      
    }
    
  }
  