/***************************************************************************
                          stack.c  -  description
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

 #include "stack.h"
 
 DD stack[STCK_SIZE];

 DW stck_ptr = 0;

 SDB push(DD val)
 {
	if(stck_ptr == STCK_SIZE)
		return -1;
	else
		stack[stck_ptr++] = val;
 }
 
 SDD pop()
 {
	 if(stck_ptr == 0)
		 return -1;
	return stack[--stck_ptr];
 }

 void printStack()
 {
	 DW i = stck_ptr;
	 printf("\nStack Print\n");	 
	 while(i > 0)
	 {
		 printf("(%d) %x ",i-1,stack[i-1]);
		 i--;
	 }
 }
 