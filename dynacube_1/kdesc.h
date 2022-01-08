/***************************************************************************
                          kdesc.h  -  description
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

#ifndef __KDESC_H
#define __KDESC_H

#include "ktypes.h"
#include "stdlib.h"

  extern GDT *gdt;
  extern IDT *idt;

  void clearDESC(SEG_DESC *in);

	void printDESC(SEG_DESC *in);
  
	void createDESC(SEG_DESC *in, DD base, DD limit, DW flags);

	void createTG(TG_DESC *in, DW tss_sel, boolean p, DPL dpl);

  void createIG(IG_DESC *in, DW seg_sel, DD offset, boolean p, DPL dpl);
  void printIG(IG_DESC *in);

	void createTRG(TRG_DESC *in, DW sel_sel, DD offset, boolean p, DPL dpl);
#endif
