/***************************************************************************
                          kio.c  -  description
                             -------------------
    begin                : Sat Dec 13 2003
    copyright            : (C) 2003 by Dynacube Team
    email                : mdshah82@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "kmaster.h"
 
  DB inb(DW port)
  {
    DB data;
    __asm__ ("inb %1, %0":"=a"(data):"d"(port));
    return data;
  }

  DW inw(DW port)
  {
    DW data;
    __asm__ ("inw %1, %0":"=a"(data):"d"(port));
    return data;
  }
  
  void outb(DW port, DB data)
  {
    __asm__ ("outb %1, %0"::"d"(port),"a"(data));
  }

  void outw(DW port, DW data)
  {
    __asm__ ("outw %1, %0"::"d"(port),"a"(data));
  }
