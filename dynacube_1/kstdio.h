/***************************************************************************
                          kstdio.h  -  description
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

#ifndef __KSTDIO_H
#define __KSTDIO_H

  #include "graphics.h"

	#define ROWSIZE 25
	#define COLSIZE 80

  #define GROWSIZE 40
	#define GCOLSIZE 50
  #define DEBUGGER_X 400
  #define DEBUGGER_OFFSET 10

	#define TABSIZE 4
  
	extern int row, col, grow, gcol;

  extern DD gcls_delay;

	void cls();
  void gcls();
  
	void kprint(char *);
	void kprintnum(long,int);
	void kprintln();
	void panic(DB *);
  void updateCursor();
  void printf(char *fmt,...);
  void putch(char );
  void gprint(char *str);
  void ginfo(DW x, DW y, char *info );
  
#endif
