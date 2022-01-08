/***************************************************************************
                          stdarg.h  -  description
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

#ifndef __STDARG_H
#define __STDARG_H

  typedef char *va_list;
  #define va_start(ap, p)	(ap = (char *) (&(p)+1))
  #define va_arg(ap, type) ((type *) (ap += sizeof(type)))[-1]
  #define va_end(ap)

#endif

