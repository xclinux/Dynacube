/***************************************************************************
                          icon.h  -  description
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

 #ifndef __ICON_H
 #define __ICON_H
 
  #include "graphics.h"
 
  #define ICON_WIDTH  12
  #define ICON_HEIGHT 12
  
  extern COLOR folder[ICON_HEIGHT][ICON_WIDTH];
  extern COLOR file[ICON_HEIGHT][ICON_WIDTH];


  void drawIcon(DW x, DW y, COLOR *icon_ptr);

 #endif