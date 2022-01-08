/***************************************************************************
                          ktask.h  -  description
                             -------------------
    begin                : Sat Jan 3 2004
    copyright            : (C) 2004 by Dynacube Team
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

 #ifndef __KTASK_H
 #define __KTASK_H

 #include "ktypes.h"
 #include "kconst.h"
 #include "kasm.h"
 #include "kstdio.h"

        
 typedef struct
 {
	 DW pre_task_link;
	 DW resv0;
	 DD esp0;
	 DW ss0;
	 DW resv1;
	 DD esp1;
	 DW ss1;
	 DW resv2;
	 DD esp2;
	 DW ss2;
	 DW resv3;
	 DD cr3;
	 DD eip;
	 DD eflags;
	 DD eax;
	 DD ecx;
	 DD edx;
	 DD ebx;
	 DD esp;
	 DD ebp;
	 DD esi;
	 DD edi;
   DW es;
   DW resv4;
   DW cs;
   DW resv5;   
   DW ss;
   DW resv6;   
   DW ds;
   DW resv7;   
	 DW fs;
   DW resv8;	 
	 DW gs;
   DW resv9;
   DW ldt_sel;
   DW resv10;
   DW flags;  //0 -  No Trap
   DW io_map; //0  
 } TSS;

 void printTSS(const TSS *tmp);

 extern TSS _system, _task[2];
 
 #endif