/***************************************************************************
                          icon.c  -  description
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

 #include "icon.h"


  COLOR folder[ICON_HEIGHT][ICON_WIDTH] = {

  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0xFF,0xFF,0,0,0,0,0},
  {0,0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0},
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0,0,0,0,0,0,0,0,0,0,0,0}

  };


  COLOR file[ICON_HEIGHT][ICON_WIDTH];

  void drawIcon(DW x, DW y, COLOR *icon_ptr)
  {
    DW i, j;
    for(i = 0; i < ICON_WIDTH ; i++)
    {
      for(j = 0 ; j < ICON_HEIGHT ; j++)
      {
        if(*(COLOR*)((COLOR*)icon_ptr+j*ICON_WIDTH+i))
          setPixel(x+i,y+j,*(COLOR*)((COLOR*)icon_ptr+j*ICON_WIDTH+i));
      }
    }
  }   