/***************************************************************************
                          kconst.h  -  description
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

#ifndef __KCONST_H
#define __KCONST_H

  #define VM_DELAY(x) cli(); cls(); x; delay(0xFFFF); sti();
  
  #define UNAVL 0x0
  #define AVL   0x1
  
  #define WINDOW_MAX    0xA
  #define FRAME_MAX     0xA
  #define COMPONENT_MAX 100
    
  #define MINI_BUFFER 100
 
  #define GDT_BASE ((DD)gdt_array)           //0xFFFF
  
  #define IDT_BASE  0x0

  #define BLOCK while(1);

  #define PHYS_MEM 0x10000000         //256 Mb
  #define KERNEL_SIZE 0x1400000        //0xA00000  
  #define NUM_PAGES (PHYS_MEM/0x1000)

  #define _4MB 0x400000
  #define _4KB 0x1000

  #define NULL1_SEL       0    
  #define NULL2_SEL       1
  
  #define SYS_DATA_SEL    2  
  #define SYS_CODE_SEL    3
  #define SYS_STACK_SEL   4
       
  #define GUI_STACK_SEL      5
  #define FLOPPY_STACK_SEL   6
  #define FS_STACK_SEL       7
    
  #define LDT_SYS_SEL     8
  #define LDT_USR_SEL     9        
  #define SYS_TSS_SEL     10
  #define TASK1_TSS_SEL   11            
  #define TASK2_TSS_SEL   12
  #define INT_TSS_SEL     13
  #define CALL_GATE_SEL   14

  #define SVGA_CODE_16_SEL    15  
  #define SVGA_DATA_16_SEL    16
  #define SVGA_STACK_16_SEL   17  

  #define A000_SEL            18
  #define B000_SEL            19    
  #define B800_SEL            20
  #define BIOS_DATA_SEL       21

  #define VM86_CODE_SEL       22
  #define VM86_DATA_SEL       23
  #define VM86_STACK_SEL      24
  
  #define END_SEL             25

  //Proc  
  #define MAX_PROC 32
  #define MAX_Q  0x1000//0x9C800
  #define MAX_FILENAME 0x100
  #define MAX_PATHNAME 512
  #define MAX_OPEN_FILES 0xA

  #define BUF_SIZE 0x200

  #define MAX_PROC_SIZE 0x32000     //200Kb
  #define MAX_DEVICE 5

  #define KERNEL_PID  (MAX_PROC+1) //-1
  #define NULL_PID    0
  #define GUI_PID     1
  #define FLOPPY_PID  2
  #define FS_PID      3
  #define VM86_PID    4
  
#endif
