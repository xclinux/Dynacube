/***************************************************************************
                          hd.c  -  description
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

 #include "hd.h"


 void hdtest()
 {
   printf("\nHD %x %b\n",inb(0x1F7));
   outb(0x1F6,0xA0);
   printf("\nHD %x %b\n",inb(0x1F7));   
 }