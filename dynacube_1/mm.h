/***************************************************************************
                          mm.h  -  description
                             -------------------
    begin                : Thu Dec 25 2003
    copyright            : (C) 2003 by Dynacube Team
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


#ifndef __MM_H
#define __MM_H

  #include "ktypes.h"
  #include "kconst.h"
  #include "proc.h"

  
  typedef struct
  {
    DB p:1;
    DB r_w:1;
    DB u_s:1; //S = 1 U = 0
    DB pwt:1;
    DB pcd:1;
    DB a:1;
    DB d:1; //Dirty = 0
    DB ps:1;
    DB g:1;
    DB avl:3;
    DW base_low;
    DB base_hi:4;
  } PGDE; //Page Directory Entry

  typedef struct
  {
    DB p:1;
    DB r_w:1;
    DB u_s:1;
    DB pwt:1;
    DB pcd:1;
    DB a:1;
    DB d:1; //Dirty
    DB pat:1;
    DB g:1;
    DB avl:3;
    DW base_low;
    DB base_hi:4;
  } PGTE; //Page Table Entry

  extern DD _kpgde[1024];
  extern DD _kpgte[PHYS_MEM/_4MB][1024]; //PHYS_MEM/4Mb
    
  extern DD _pgde[1024];
  extern DD _pgte[MAX_PROC][1024]; //MAX_PROC

  extern DD _svgapgte[1024]; //PHYS_MEM/4Mb

  extern DD frmlist[PHYS_MEM/(0x20*_4KB)];

 struct MHEADER
  {
    struct MHEADER *ptr;
    size_t size;    
  };
  
  extern struct MHEADER base;
  extern struct MHEADER *freep;
  
    
  void mm_init();
  SDD findpage();
  void freepage(DD index);
  DD lin_to_phy(SDW pid ,DD linear_addr);
  DD logi_to_lin(SDW pid ,DW seg_sel, DD offset);
  void *kmalloc(size_t s);
  void free(void *ptr);
  void map_linear(DD addr);
  DD get_phys(DW pid,DD ptr);

#endif
