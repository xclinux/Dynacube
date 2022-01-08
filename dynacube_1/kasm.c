/***************************************************************************
                          kasm.c  -  description
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

void lidt(IDT *idt)
{
	__asm__ __volatile__ ("lidt (%0)"::"p"(idt));
}


void sidt(IDT *idt)
{
	__asm__ __volatile__ ("sidt %0"::"m"(*idt));
}

void lgdt(GDT *gdt)
{
	__asm__ __volatile__ ("lgdt (%0)"::"p"(gdt));
}

void sgdt(GDT *gdt)
{
	__asm__ __volatile__ ("sgdt %0"::"m"(*gdt));
}

void kdump()
{
 int i;
 DD _addr[9];
 char *regs[] = {"EAX:","EBX:","ECX:","EDX:","ESI:","EDI:","ESP:","EBP:","EIP:"};
 char *sregs[] = {" CS:"," DS:"," SS:"," ES:"," FS:"," GS:"};

 __asm__ __volatile__ ("":"=a"(_addr[0]),"=b"(_addr[1]),"=c"(_addr[2]), \
 "=d"(_addr[3]),"=S"(_addr[4]),"=D"(_addr[5]));

 __asm__ __volatile__ ("movl %%esp, %0":"=m"(_addr[6]));
 __asm__ __volatile__ ("movl %%ebp, %0":"=m"(_addr[7]));
 __asm__ __volatile__ ("movl 8(%%esp), %%eax":"=a"(_addr[8]));

 kprintln();

 for(i=0; i<6;i++)
 {
  kprint("\t");
  kprint(regs[i]);
  kprint("\t");
 }

 kprintln();

 for(i=0; i<6;i++)
 {
  kprint("  ");
  kprintnum(_addr[i],16);
  _addr[i] = 0;
 }

 kprintln();

 for(i=6; i<9;i++)
 {
  kprint("\t");
  kprint(regs[i]);
  kprint("\t");
 }

 kprintln();

 for(i=6; i<9;i++)
 {
  kprint("  ");
  kprintnum(_addr[i],16);
  _addr[i] = 0;
 }

 kprintln();

 for(i=0; i<6;i++)
 {
  kprint("\t");
  kprint(sregs[i]);
  kprint("\t");
 }

 kprintln();

 __asm__ __volatile__ ("mov %%cs, %0":"=m"(_addr[0]));
 __asm__ __volatile__ ("mov %%ds, %0":"=m"(_addr[1]));
 __asm__ __volatile__ ("mov %%ss, %0":"=m"(_addr[2]));
 __asm__ __volatile__ ("mov %%es, %0":"=m"(_addr[3]));
 __asm__ __volatile__ ("mov %%fs, %0":"=m"(_addr[4]));
 __asm__ __volatile__ ("mov %%gs, %0":"=m"(_addr[5]));

 for(i=0; i<6;i++)
 {
  kprint("  ");
  kprintnum(_addr[i],16);
 }

 kprintln();
}






