/***************************************************************************
                          kio.h  -  description
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

 #ifndef __KIO_H
 #define __KIO_H

 #include "ktypes.h"
  DB inb(DW port);
  DW inw(DW port);

  void outb(DW port, DB data);
  void outw(DW port, DW data);
  
 #endif