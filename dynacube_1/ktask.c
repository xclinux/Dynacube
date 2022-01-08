/***************************************************************************
                          ktask.c  -  description
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

 #include "ktask.h"

 extern void isr20h();
  
 TSS _system  __attribute__((aligned(_4KB))), _task[2]   __attribute__((aligned(_4KB))); //, _task2   __attribute__((aligned(_4KB)));
 TSS _int_tss  __attribute__((aligned(_4KB)));

 DB blank[sizeof(TSS)] = {0};

 SEG_DESC _sys_tss;
 DW _tss_flags;
 
 void task_init()
 {
	SEG_DESC tmp;
  DD cr3;
	
	 memcpy(&_system,blank,sizeof(TSS));
	 memcpy(&_task[0],blank,sizeof(TSS));
   memcpy(&_task[1],blank,sizeof(TSS));

	 asm __volatile__("movl %%cr3,%%eax":"=a"(_system.cr3));
	 asm __volatile__("movw %%cs,%%ax":"=a"(_system.cs));
	 asm __volatile__("movw %%ds,%%ax":"=a"(_system.ds));
	 asm __volatile__("movw %%ss,%%ax":"=a"(_system.ss));
	 asm __volatile__("movw %%es,%%ax":"=a"(_system.es));
	 asm __volatile__("movw %%fs,%%ax":"=a"(_system.fs));
	 asm __volatile__("movw %%gs,%%ax":"=a"(_system.gs));

	 _system.eflags = 0x2|(1<<9);
   
	 asm __volatile__("movl %%esp,%%eax":"=a"(_system.esp0));	 
	 asm __volatile__("movw %%ss,%%ax":"=a"(_system.ss0));

	 clearDESC(&tmp);
	 createDESC(&tmp,0x0,0xF,0x882);
	 addDesc(LDT_SYS_SEL,&tmp);
   printDESC(&tmp);
	 
   _system.ldt_sel = LDT_SYS_SEL*8;

   _tss_flags = 0x889;

   _int_tss = _system;
   _int_tss.eip = isr20h;
   _int_tss.esp = KERNEL_SIZE;
   printTSS(&_int_tss);   
   
	 printf("\n%x %d",&_system,sizeof(TSS));
	 clearDESC(&_sys_tss);
	 createDESC(&_sys_tss,&_system,sizeof(TSS),_tss_flags);
	 addDesc(SYS_TSS_SEL,&_sys_tss);
	 printDESC(&_sys_tss);

	 clearDESC(&_sys_tss);
	 createDESC(&_sys_tss,&_task[0],sizeof(TSS),_tss_flags);
	 addDesc(TASK1_TSS_SEL,&_sys_tss);
	 printDESC(&_sys_tss);

	 clearDESC(&_sys_tss);
	 createDESC(&_sys_tss,&_task[1],sizeof(TSS),_tss_flags);
	 addDesc(TASK2_TSS_SEL,&_sys_tss);
	 printDESC(&_sys_tss);

	 clearDESC(&_sys_tss);
	 createDESC(&_sys_tss,&_int_tss,sizeof(TSS),_tss_flags);
	 addDesc(INT_TSS_SEL,&_sys_tss);
	 printDESC(&_sys_tss);
         	   	 	 
//	 asm("ltr %%ax"::"a"(SYS_TSS_SEL*8));
	 asm("lldt %%ax"::"a"((LDT_SYS_SEL*8)));
	 printf("Addr: %x\n",&_task[0]);

	 //asm("lcall $0x20,$0");
	 //asm("call %0,%1"::"a"(4*8),"r"(0));
 }

 void printTSS(const TSS *tmp)
 {
   printf("\ncs %x ds %x ss %x esp %x eip %x",tmp->cs,tmp->ds,tmp->ss,tmp->esp,tmp->eip);
   printf("\nss0 %x esp0 %x eflags %x ebp %x",tmp->ss0,tmp->esp0,tmp->eflags,tmp->ebp);
   printf("\nldtsel %x cr3 %x prev_link %x\n",tmp->ldt_sel,tmp->cr3,tmp->pre_task_link);
 }



















 