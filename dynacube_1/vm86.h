/***************************************************************************
                          vm86.h  -  description
                             -------------------
    begin                : Tue Feb 10 2004
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

 #ifndef __VM86_H
 #define __VM86_H
 
  #include "proc.h"
  #include "kint.h"


  typedef struct
  {
		DD edi, esi, ebp, esp, ebx, edx, ecx, eax;
		DD ds, es, fs, gs;
		DD which_int;
    DD _ss, _esp;
		DD err_code, eip, cs, eflags, user_esp, user_ss;
    DD _es, _ds, _fs, _gs;
  } VM86REGS;
 
  void svgainit();
  void handleVM86(REGS *regs);

  
 #endif