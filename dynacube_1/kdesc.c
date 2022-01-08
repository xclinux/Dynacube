/***************************************************************************
                          kdesc.c  -  description
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

#include "kmaster.h"

void clearDESC(SEG_DESC *in)
{
 in->base_0_15  = 0x0;
 in->base_16_23 = 0x0;
 in->base_24_31 = 0x0;
 in->lt_0_15    = 0x0;
 in->lt_16_19   = 0x0;
 in->flags_8_15 = 0x0;
 in->flags_20_23= 0x0;
}

void createDESC(SEG_DESC *in, DD base, DD limit, DW flags)
{
 clearDESC(in);
 flags &=  0x0FFF;
 in->lt_0_15 = (DW)(limit & 0xFFFF);
 in->lt_16_19 = (limit>>16) & 0xF;

 in->base_0_15  = (DW)(base & 0xFFFF);
 in->base_16_23 = (DB)((base>>16) & 0xFF);
 in->base_24_31 = (DB)((base>>24) & 0xFF);

 in->flags_8_15 = (DB)(flags & 0xFF);
 in->flags_20_23= (DB)((flags>>8) & 0xF);
}

void createTG(TG_DESC *in, DW tss_sel, boolean p, DPL dpl)
{
  clearDESC((SEG_DESC *)in);  
}

void createIG(IG_DESC *in, DW seg_sel, DD offset, boolean p, DPL dpl)
{
  clearDESC((SEG_DESC *)in);

  in->segsel_16_31 = seg_sel;

  in->off_0_15 = offset & 0xFFFF;
  in->off_16_31 = offset >> 16;

  in->flags_0_15 = F_IG | (p?F_IG_P:0) | (dpl<<13);
}

void createTRG(TRG_DESC *in, DW sel_sel, DD offset, boolean p, DPL dpl)
{
  clearDESC((SEG_DESC *)in);  
}

void printDESC(SEG_DESC *in)
{
 DD base, limit;
 DW flags;

 base = in->base_24_31<<24 | in->base_16_23<<16 | in->base_0_15;
 limit = in->lt_16_19<<16 | in->lt_0_15;
 flags = in->flags_20_23<<8 | in->flags_8_15;

 printf("\nBase:%x\tLimit:%x\tFlags:%x",base,limit,flags); 
}


void printIG(IG_DESC *in)
{
  printf("\nSelector:%x\tOffset:%x\tFlags:%x",in->segsel_16_31,(in->off_16_31<<16)|in->off_0_15,in->flags_0_15);
}








