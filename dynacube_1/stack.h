/***************************************************************************
                          stack.h  -  description
                             -------------------
    begin                : Sat Feb 14 2004
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

 #ifndef __STACK_H
 #define __STACK_H

 #include "ktypes.h"
 
 #define STCK_SIZE 3*100

 extern DD stack[STCK_SIZE];

 SDB push(DD val);
 SDD pop();

 #endif