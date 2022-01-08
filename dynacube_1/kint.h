/***************************************************************************
                          kint.h  -  description
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

#ifndef __KINT_H
#define __KINT_H

  #include "ktypes.h"
  
	#define DIVIDE_ERROR							0
	#define DEBUG_EXCEPTION   				1
  #define NMI               				2
  #define INT3              				3
	#define INTO              				4
	#define BOUND_EXCEPTION   				5
	#define INVALID_OPCODE    				6
	#define NO_COPROCESSOR						7
	#define DOUBLE_FAULT							8
	#define CO_PROCESSOR_SEG_OVERRUN  9
	#define BAD_TSS									 10
	#define SEG_NOT_PRESENT					 11
	#define STACK_FAULT							 12
	#define GPF											 13
	#define PAGE_FAULT							 14
	#define RESERVED								 15
	#define CO_PROCESSOR_ERROR			 16
	#define ALIGNMENT_CHECK					 17


  #define FLOPPY_INT  0x26
  	
  #define sti() __asm__ __volatile__ ("sti");
  #define cli() __asm__ __volatile__ ("cli");
  
   
	typedef struct
	{
		DD edi, esi, ebp, esp, ebx, edx, ecx, eax;
		DD ds, es, fs, gs;
		DD which_int;
    DD _ss, _esp;
		DD err_code, eip, cs, eflags, user_esp, user_ss;
	} REGS;

	
 extern DW floppy_int_pending;
 extern DB which_int;
 
 void fault(REGS *regs);
 
 void handle_timer();
 void handle_KBD();
 void eoi();

#endif

