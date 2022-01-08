/***************************************************************************
                          kinit.h  -  description
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

#ifndef __KINIT_H
#define __KINIT_H

        #include "ktypes.h"
        
        extern GDT *gdt;
        extern DB gdt_array[256*8];

        void gdt_init();
      	void idt_init();
        
        void addDesc(DB index, SEG_DESC *tmp);
        void addIG(DB index, IG_DESC *tmp);
        void addTG(DB index, TG_DESC *tmp);
        void addTRG(DB index, TRG_DESC *tmp);
        
        void printTable(SEG_DESC *tab,int num_of_sel);
        
        void getDesc(DB index,SEG_DESC *ret);

#endif
