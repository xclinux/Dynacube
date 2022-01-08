/***************************************************************************
                          proc.h  -  description
                             -------------------
    begin                : Wed Dec 24 2003
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

 #ifndef __PROC_H
 #define __PROC_H

// DW pg_dir; - Global
 #include "ktypes.h"
 #include "kconst.h"
 
// typedef enum{ O_RDONLY, O_WRONLY, O_RDWR} FILE_FLAGS;

 //Process Init - Lazy initialize
 
 typedef struct
 {
   boolean avl;
   DW ppid;

	 DW pre_task_link;

   DD esp0;
	 DW ss0;

	 DD esp1;
	 DW ss1;

	 DD esp2;
	 DW ss2;

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

   DW cs;

   DW ss;

   DW ds;

	 DW fs;

	 DW gs;

   DW ldt_sel;

   DW flags; //T
   DW io_map;

   DW msg_q_delim; //Size of q = 2^16

   DD recv_addr;    // to store the address from the recv call when blocked
   DD wait_int_num; //The interrupt that the process wants to receive
   DD time_out;     //The timeout registered with the TIMER

 } PROC; //Create array of PROC 

// typedef struct
// {
//   boolean avl;
//   char abs_fname[MAX_PATHNAME]; //Absolute File Name
//   FILE_FLAGS flags;
//   DD file_offset;
//   DW buff_tbl_index; //global within procs
// } FILE_DESC;
 
// extern DB fbuffer[MAX_BUF][BUF_SIZE];



 //Use loop to init boolean avl in fdesc & proc_t
// extern FILE_DESC fdesc[MAX_PROC][MAX_OPEN_FILES];
 
 extern LDT _ldt[MAX_PROC];
 extern SEG_DESC _ldte[MAX_PROC][3] __attribute__((aligned (8)));
 
 extern PROC _proc[MAX_PROC];

 void proc_init(); 
 SDB fork(); //Negative returns allowed
 void do_exit(DW pid);
 void forkNULL();
 SDB create(char *fname);

 //Sample Processes
 void reti();
 void null_proc();
 void rogue();
 SDW load(char *fname,DW pid);
 #endif
 
