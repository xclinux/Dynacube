/***************************************************************************
                          kinit.c  -  description
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
 #include "proc.h"

 #include "svga.h"

// GDT *gdt = (GDT *)(GDT_BASE);
// IDT *idt = (IDT *)(IDT_BASE);

 DB gdt_array[256*8] __attribute__((aligned (8)));
 
 
 extern int main(void);


 void gdt_init()
 {
   DB i;
   DW flags;
   SEG_DESC sys;
   GDT _gdt;
   CALL_GATE _call_gate;

   createDESC(&sys,0,0,0);
   addDesc(NULL1_SEL,&sys);
   addDesc(NULL2_SEL,&sys);
   
   flags = ((F_G|F_D_B)<<8)|F_P|F_S|F_TYPE_DATA|F_TYPE_W;      //DATA
   createDESC(&sys,0,0xFFFFFFFF,flags);
   addDesc(SYS_DATA_SEL,&sys);

   flags = ((F_G|F_D_B)<<8)|F_P|F_S|F_TYPE_CODE|F_TYPE_R;			 //CODE
   createDESC(&sys,0,0xFFFFFFFF,flags);
   addDesc(SYS_CODE_SEL,&sys);

//   flags = ((F_D_B)<<8)|F_P|F_S|F_TYPE_DATA|F_TYPE_W|F_TYPE_E;      //STACK SPACE
//   createDESC(&sys,0x0,0x10800,flags);
//   addDesc(SYS_STACK_SEL,&sys);

   flags = ((F_G|F_D_B)<<8)|F_P|F_S|F_TYPE_DATA|F_TYPE_W|F_TYPE_E;      //STACK SPACE
//   createDESC(&sys,0x0,0x800,flags); //0x800000
   createDESC(&sys,0x0,((KERNEL_SIZE - _4MB)<< 12) ,flags); //0x800000
   addDesc(FS_STACK_SEL,&sys);

   printDESC(&sys);

   flags = ((F_G|F_D_B)<<8)|F_P|F_S|F_TYPE_DATA|F_TYPE_W|F_TYPE_E;      //STACK SPACE
//   createDESC(&sys,0x0,0x800,flags); //0x800000
   createDESC(&sys,0x0,((KERNEL_SIZE - 3*_4MB/4)<< 12) ,flags); //0x800000
   addDesc(SYS_STACK_SEL,&sys);

   printDESC(&sys);

   flags = ((F_G|F_D_B)<<8)|F_P|F_S|F_TYPE_DATA|F_TYPE_W|F_TYPE_E;      //GUI STACK SPACE
//   createDESC(&sys,0x0,0x900,flags); //0x900000
   createDESC(&sys,0x0,((KERNEL_SIZE - 2*_4MB/4)<< 12) ,flags); //0x800000
   addDesc(GUI_STACK_SEL,&sys);

   printDESC(&sys);

   flags = ((F_G|F_D_B)<<8)|F_P|F_S|F_TYPE_DATA|F_TYPE_W|F_TYPE_E;      //GUI STACK SPACE
//   createDESC(&sys,0x0,0xA00,flags); //0xA00000
   createDESC(&sys,0x0,((KERNEL_SIZE - _4MB/4)<< 12) ,flags); //0x800000
   addDesc(FLOPPY_STACK_SEL,&sys);

   printDESC(&sys);

//   flags = (F_D_B<<8)|F_P|F_S|F_TYPE_DATA|F_TYPE_W;      //VM86 DATA
//   createDESC(&sys,0,0xFFFFFFFF,flags);
//   addDesc(VM86_DATA_SEL,&sys);
//
//   flags = (F_D_B<<8)|F_P|F_S|F_TYPE_CODE|F_TYPE_R; //VM86 CODE
//   createDESC(&sys,0,0xFFFFFFFF,flags);
//   addDesc(VM86_CODE_SEL,&sys);
//
//   flags = (F_D_B<<8)|F_P|F_S|F_TYPE_DATA|F_TYPE_W|F_TYPE_E; //VM86 STACK
//   createDESC(&sys,0x0,0xA00,flags); //0xA00000
//   addDesc(VM86_STACK_SEL,&sys);

                       
   flags = 0x882;
   createDESC(&sys,0,0xFFFFFFFF,flags);
   addDesc(LDT_SYS_SEL,&sys);

   flags = 0;
   createDESC(&sys,0,0xFFFFFFFF,flags);
   addDesc(LDT_USR_SEL,&sys);
      
   flags = 0;
   createDESC(&sys,0,0xFFFFFFFF,flags);
   addDesc(SYS_TSS_SEL,&sys);
         
   flags = 0;
   createDESC(&sys,0,0x6C,flags); //
   addDesc(TASK1_TSS_SEL,&sys);
   
   flags = 0;
   createDESC(&sys,0,0x6C,flags);
   addDesc(TASK2_TSS_SEL,&sys);

   _call_gate.off_0_15        = (DD)do_exit & 0xFFFF;
   _call_gate.off_16_31       = ((DD)do_exit >> 16) & 0xFFFF;
   _call_gate.segsel_16_31    = SYS_CODE_SEL * 8;
   _call_gate.param_count     = 0;
   _call_gate.flags           = 0xEC;
   
   addCallDesc(CALL_GATE_SEL,&_call_gate);


   flags = 0x09E;
   createDESC(&sys,vgabios_buffer,0x8000,flags);
   addDesc(SVGA_CODE_16_SEL,&sys);

   flags = 0x092;
   createDESC(&sys,vgabios_buffer,0x8000,flags);
   addDesc(SVGA_DATA_16_SEL,&sys);

   flags = 0x092; //Expand Up Stack
   createDESC(&sys,svga_stack,0x400,flags);
   addDesc(SVGA_STACK_16_SEL,&sys);

   flags = 0x092;
   createDESC(&sys,0xA0000,0x10000,flags);
   addDesc(A000_SEL,&sys);
      
   flags = 0x092;
   createDESC(&sys,0xB0000,0x10000,flags);
   addDesc(B000_SEL,&sys);

   flags = 0x092;
   createDESC(&sys,0xB8000,0x8000,flags);
   addDesc(B800_SEL,&sys);

   flags = 0x092;
   createDESC(&sys,BIOSData,0x600,flags);
   addDesc(BIOS_DATA_SEL,&sys);
                                    
//   printf("\n");
//   printTable((SEG_DESC *)GDT_BASE,END_SEL);
//   BLOCK
      
//   printDESC(&sys);
//   BLOCK
   
   for(i=END_SEL;i<255;i++)
   {   
    createDESC(&sys,0,0,0);
    addDesc(i,&sys);
   }

   _gdt.hibase = GDT_BASE >> 16;
   _gdt.lobase = GDT_BASE & 0xFFFF;
   _gdt.limit = (i+1)*8-1;
     
   lgdt(&_gdt);
 
   lds(SYS_DATA_SEL * 8);   
   lss(SYS_STACK_SEL * 8);   
   //kdump();
 }

 void getDesc(DB index,SEG_DESC *ret)
 {
	 SEG_DESC *tmp = (SEG_DESC*)(GDT_BASE + index*8);
	 
	 ret->base_0_15 = tmp->base_0_15;
	 ret->base_16_23 = tmp->base_16_23;
	 ret->base_24_31 = tmp->base_24_31;

   ret->flags_20_23 = tmp->flags_20_23;
   ret->flags_8_15  = tmp->flags_8_15;

   ret->lt_0_15     = tmp->lt_0_15;
   ret->lt_16_19    = tmp->lt_16_19;	 
 }
 
 void addDesc(DB index, SEG_DESC *tmp)
 {
  SEG_DESC *item = (SEG_DESC*)(GDT_BASE + index*8);

  item->base_0_15   = tmp->base_0_15;
  item->base_16_23  = tmp->base_16_23;
  item->base_24_31  = tmp->base_24_31;

  item->flags_20_23 = tmp->flags_20_23;
  item->flags_8_15  = tmp->flags_8_15;

  item->lt_0_15     = tmp->lt_0_15;
  item->lt_16_19    = tmp->lt_16_19;
 }
 
 void addCallDesc(DB index, CALL_GATE *tmp)
 {
  CALL_GATE *item = (CALL_GATE*)(GDT_BASE + index*8);

  item->off_0_15      = tmp->off_0_15;
  item->off_16_31     = tmp->off_16_31;
  item->segsel_16_31  = tmp->segsel_16_31;

  item->flags         = tmp->flags;
  item->param_count   = tmp->param_count;  
 }
 

 void printTable(SEG_DESC *tab,int num_of_sel)//Both GDT & LDT
 {
   SEG_DESC *t;   
   DW index = 0;
   
   while(index < num_of_sel)
   {
    t = (SEG_DESC*)(tab + index);
    printf(" %d ",index);
    printDESC(t);
		index++;
   }   
 }
  

 /*
 void idt_init()
 {
   TG_DESC tg;
   TRG_DESC trg;
   IG_DESC ig;

   GDT _gdt;
   IDT _idt;

   DW i;

   for(i=0;i<256;i++)
   {
    createIG(&ig,0x20,main,_true,dpl_0);
    addIG(i,&ig);
    //printIG(&ig);
   }

   idt->hibase = IDT_HIGH;
   idt->lobase = IDT_LOW;
   idt->limit  = 256*8-1; //Just For the time being

   lidt(idt);

   _gdt.hibase  = 0;
   _gdt.lobase  = 0;
   _gdt.limit   = 0;
   
	 sgdt(&_gdt);	 
   sidt(&_idt);
   printf("\nIDT\t%x\t%x\t%x",_idt.hibase,_idt.lobase,_idt.limit);

   kdump();

 }
 */
 
 void addIG(DB index, IG_DESC *tmp)
 {
   IG_DESC *item = (IG_DESC*)(IDT_BASE + index*8);
 }

 void addTG(DB index, TG_DESC *tmp)
 {   
 }
 
 void addTRG(DB index, TRG_DESC *tmp)
 {   
 }
 