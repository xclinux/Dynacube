/***************************************************************************
                          stdlib.h  -  description
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

 #ifndef __STDLIB_H
 #define __STDLIB_H

    #include "ktypes.h"

    #define NULL ((void*)0)

    char* itoa(DD num,DB base);
    char* ftoa(float num, DB base);
    SDD atoi(char *num);

    DD abs(SDD num);
    
 
 #endif
