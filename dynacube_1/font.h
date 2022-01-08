/***************************************************************************
                          font.h  -  description
                             -------------------
    begin                : Mon Feb 16 2004
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

 #ifndef __FONT_H
 #define __FONT_H

  #include "ktypes.h"

  #define CHARSET_SIZE 256
  
  #define CHARROWS 7
  #define CHARCOLS 5
  //Now the only type font supported in Dynacube

  extern DB charset[128][CHARROWS][CHARCOLS];
  extern DB mouseptr[16][16];

 #endif