/***************************************************************************
                          vm86.c  -  description
                             -------------------
    begin                : Tue Feb 10 2004
    copyright            : (C) 2004 by Dynacube Team
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

 #include "vm86.h"
 #include "proc.h"
 #include "svga.h"
 #include "queue.h"

  PROC vm86_bk;
  VBEINFO *VbeInfoBlock;
  VBE_ModeInfo vbe_mode;
 
  void svgainit() //Task that would be copied to < 1Mb space
  {
//    asm("int $0x10"::"a"(0x4F03),"b"(0x0),"c"(0x0));
//    asm("int $0x10"::"a"(0x0941),"b"(0x0007),"c"(0xFFFF)); //-- This works in VMware
//    asm("int $0x10"::"a"(0x0000),"b"(0x0007),"c"(0xFFFF));
//		asm("int $0x10"::"a"(0x4F02),"b"(0x8100));

// 		asm("int $0x10"::"a"(0x4F02),"b"(0xC114));

    asm("int $0x10"::"a"(0x4F01),"c"(0x114),"D"(0x1000));
    asm("int $0x10"::"a"(0x4F02),"b"(0x4114),"c"(0x0));
    
//    asm("int $0x10"::"a"(0x4F06),"b"(0x0),"c"(800));
//    asm("int $0x10"::"a"(0x4F07),"b"(0x0),"c"(0x0),"d"(0x0));
        
//    asm("int $0x10"::"a"(0x4F01),"c"(0x114),"D"(0x1000));
// 		asm("int $0x10"::"a"(0x4F02),"b"(0xC114));

//		asm("int $0x10"::"a"(0x4F02),"b"(0x8100));

    asm("int $0xFF");
		while(1);
  }

  void handleVM86(REGS *regs)
  {
    DD i;
    DB opcode, opr1, opr2, opr3;
    DD stck_ret, vid_modes;
    DD temp;

		DW *vid = (DW *)0xA0000;
    
    memcpy((void *)&vm86_bk,(void *)&_proc[cur_pid],sizeof(PROC));
    
    VM86REGS *vmregs = (VM86REGS *) regs;
    DD phy;
//    cls();
    printf("\nInside handleVM86");
    printRegs(regs);
    printf("\nVMREGS cs %x ds %x es %x \n fs %x gs %x",vmregs->cs,vmregs->_ds,vmregs->_es,vmregs->_fs,vmregs->_gs);
    _proc[cur_pid].ds = vmregs->_ds;
    _proc[cur_pid].es = vmregs->_es;
    _proc[cur_pid].fs = vmregs->_fs;
    _proc[cur_pid].gs = vmregs->_gs;
    phy = ((vmregs->cs)<<4) + vmregs->eip;
    printf("\n phy_val(%x) %x",phy,*(DD *)phy);

    opcode = *(DB *)phy;
    opr1    = *(DB *)(phy+1);
    opr2    = *(DB *)(phy+2);
    opr3    = *(DB *)(phy+3);
    
		printf("\nEAX %x EBX %x ECX %x  DI %x",regs->eax,regs->ebx,regs->ecx,regs->edi);

    switch(opcode)
    {
      case 0xCD:
              if(opr1 == 0xFF)
               {
                 remove(&ready_q,cur_pid);
              	 do_exit(cur_pid);
                 post_vm86();
               }
              else
              { 
                printf("\nInterrupt %x",opr1);
                printf("\ncs %x ip %x",*(DW*)((opr1*4)+2),*(DW*)opr1*4);
                _proc[cur_pid].cs = (*(DW*)((opr1*4)+2)) & 0xFFFF;
                _proc[cur_pid].eip = (*(DW*)(opr1*4)) & 0xFFFF;

                //Backup needed for IRET
                push(vmregs->eflags);
                push(vmregs->cs);
                push(vmregs->eip+2); //For 0xCDxx
                printStack();                            
              }
              break;
      case 0xFA: //CLI
            printf("\nCLI called");
            _proc[cur_pid].eflags &= ~(1<<9); //IFlag
            _proc[cur_pid].eip += 2;
            break;

      case 0xFB: //STI
            printf("\nSTI called");
            _proc[cur_pid].eflags |= (1<<9); //IFlag
            _proc[cur_pid].eip += 2;            
            break;
            
      case 0xCF: //IRET      
            printf("\nIRET called");
            stck_ret = pop();
            _proc[cur_pid].eip = (stck_ret > 0)?stck_ret:0;
            stck_ret = pop();
            _proc[cur_pid].cs = (stck_ret > 0)?stck_ret:0x9000;
            stck_ret = pop();
            _proc[cur_pid].eflags = (stck_ret > 0)?stck_ret:0;

            printf("\ncs %x eip %x eflags %x",_proc[cur_pid].cs,_proc[cur_pid].eip,_proc[cur_pid].eflags);


            if(vbe_mode.PhysBasePtr == 0)
              vbe_mode = *((VBE_ModeInfo *) (0x91000));

            printf("\nPhys addr: %x xRes %d yRes %d bpp %d",vbe_mode.PhysBasePtr,vbe_mode.XResolution,vbe_mode.YResolution,vbe_mode.BitsPerPixel);
            printf("\nModeAttributes : %x",vbe_mode.ModeAttributes);
            break;
            
      default:
            printf("\nDefault %x",opcode);
            break;
    }
//    delay(0xFFFF);
  }

//
//            cls();
//            printf("\nVBE info\n");
//            VbeInfoBlock = (VBEINFO *)(0x91000);
//
//						vid_modes = VbeInfoBlock->OemStringPtr & 0x0000FFFF;
//						printf("\nVid1 %x vid2 %x", VbeInfoBlock->OemStringPtr, vid_modes);
//						vid_modes = vid_modes<<4;
//						printf("\nVid1 %x vid2 %x", VbeInfoBlock->OemStringPtr, vid_modes);
//						vid_modes |= (VbeInfoBlock->OemStringPtr & 0xFFFF0000)>>16;
//						printf("\nVid1 %x vid2 %x", VbeInfoBlock->OemStringPtr, vid_modes);
//
//            printf("\n%s",VbeInfoBlock->VbeSignature);
//            printf("\n%s",(DB *)vid_modes);
//            printf("\nMem %d",VbeInfoBlock->TotalMemory);
//
//						vid_modes = VbeInfoBlock->VideoModePtr & 0x0000FFFF;
//						printf("\nVid1 %x vid2 %x", VbeInfoBlock->VideoModePtr, vid_modes);
//						vid_modes = vid_modes<<4;
//						printf("\nVid1 %x vid2 %x", VbeInfoBlock->VideoModePtr, vid_modes);
//						vid_modes |= (VbeInfoBlock->VideoModePtr & 0xFFFF0000)>>16;
//
//
//						printf("\nVid1 %x vid2 %x", VbeInfoBlock->VideoModePtr, vid_modes);
//
//						i = 0;
//						while(1)
//            {
//							if(/* *(SDW*)(vid_modes) == -1  || */i++ > 0xF)
//								break;
//							printf("\tMode %x",*(DW*)(vid_modes));
//							vid_modes += 2;
//						}
  