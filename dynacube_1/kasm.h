/***************************************************************************
                          kasm.h  -  description
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
/*
File Contains asm generic level functions
*/

#ifndef __ASM_H
#define __ASM_H

        #include "ktypes.h"
                
        #define lds(desc_sel) __asm__ __volatile__("movl %0, %%ds"::"r"(desc_sel));
        #define lss(desc_sel) __asm__ __volatile__("movl %0, %%ss"::"r"(desc_sel));
        #define les(desc_sel) __asm__ __volatile__("movl %0, %%es"::"r"(desc_sel));
        #define lfs(desc_sel) __asm__ __volatile__("movl %0, %%fs"::"r"(desc_sel));
        #define lgs(desc_sel) __asm__ __volatile__("movl %0, %%gs"::"r"(desc_sel));

        #define cli()	__asm__ __volatile__("cli");
        #define sti() __asm__ __volatile__("sti");

        #define setCR0(val) __asm__ __volatile__ ("movl %%eax, %%cr0"::"a"(val));
        #define getCR0(var) __asm__ __volatile__ ("movl %%cr0,%%eax":"=a"(var));

        #define setCR3(val) __asm__ __volatile__ ("movl %%eax, %%cr3"::"a"(val));
        #define getCR3(var) __asm__ __volatile__ ("movl %%cr3,%%eax":"=a"(var));
        #define intr_wait(intr) __asm__ __volatile__("pushl %%eax"::"a"(intr)); \
                                __asm__ __volatile__("int $0x30"::"a"(6));        

       #define sleep(time_out) __asm__ __volatile__("pushl %%eax"::"a"(time_out)); \
                               __asm__ __volatile__("int $0x30"::"a"(5));
       #define wait_intr_timer(intr,time_out) __asm__ __volatile__("pushl %%eax"::"a"(time_out)); \
                                              __asm__ __volatile__("pushl %%eax"::"a"(intr)); \
                                              __asm__ __volatile__("int $0x30"::"a"(7));
                
  void lidt(IDT *);
  void lgdt(GDT *gdt);
  void sgdt(GDT *gdt);
  void kdump();
#endif


