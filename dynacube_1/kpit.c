/***************************************************************************
                          kpit.c  -  description
                             -------------------
    begin                : Sat Jan 2 2004
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

#include "kpit.h"
#include "ktypes.h"

void pit0_init(DD num_of_times)
{
 DW pit_data = 1; //65536

 if(num_of_times > 0)
 {
  pit_data = (PIT_FREQ/num_of_times);
 }

 outb(PIT_MCR_PORT, PIT_COUNTER_0|RW_LSB_MSB|MODE_3|BINARY);
 asm("jmp .+2");
 outb(PIT_PORT_0, pit_data & 0xFF);
 asm("jmp .+2"); 
 outb(PIT_PORT_0, (pit_data>>8) & 0xFF);
 
 printf("\nPIT 0 Initialized @ %d Hz",num_of_times); 
}
