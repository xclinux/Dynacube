/***************************************************************************
                          kint.c  -  description
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

#include "kint.h"
#include "keyboard.h"
#include "ktime.h"
#include "kconst.h"
#include "proc.h"
#include "mm.h"

#include "queue.h"
#include "device.h"
#include "floppy.h"
#include "fat12.h"


#include "message.h"
#include "kstdio.h"
#include "mouse.h"
#include "svga.h"

#include "ktask.h"

extern void post_vm86();

DB which_int;
DW floppy_int_pending = 0;

 void fault(REGS *regs)
 {
	DD i;
  DW j;
  DD temp;
	DD cr2 = 0, cr3;

  cli();

  //Setting the Kernel Pgde to cr3 -- IMPORTANT
	cr3 = (cr3 & 0xFFF) | (((DD)_kpgde) & 0xFFFFF000);
  __asm__ __volatile__ ("movl %%eax,%%cr3"::"a"(cr3));

  which_int = regs->which_int;

//  outb(0x3F2,1<<4);
//  delay(0xFFFF);
//  outb(0x3F2,0);

  //printf("\npid %d",cur_pid);
//  printQ(&ready_q);
//  printQ(&gui_q);

//  delay(0xFFFFF);

//  delay(0xFFFFFFFF);
//  printf("\n _esp %x esp %x _ss %x",regs->_esp,regs->esp ,regs->_ss);
//  cls();
//  printf("which_int %d",regs->which_int);
//   printRegs(regs);
//   kdump();
//   printf("\neip : %x",regs->eip);

  if(cur_pid != MAX_PROC+1)
  {
    _proc[cur_pid].eax      = regs->eax;
    _proc[cur_pid].ebx      = regs->ebx;
    _proc[cur_pid].ecx      = regs->ecx;
    _proc[cur_pid].edx      = regs->edx;
    _proc[cur_pid].esi      = regs->esi;
    _proc[cur_pid].edi      = regs->edi;
    _proc[cur_pid].ebp      = regs->ebp;

    _proc[cur_pid].eip      = regs->eip;

    _proc[cur_pid].cs       = regs->cs;
    _proc[cur_pid].ds       = regs->ds;
    _proc[cur_pid].ss       = regs->user_ss;
    _proc[cur_pid].es       = regs->es;
    _proc[cur_pid].esp      = regs->user_esp;

    _proc[cur_pid].fs       = regs->fs;
    _proc[cur_pid].gs       = regs->gs;

    _proc[cur_pid].ldt_sel  = LDT_USR_SEL * 8;
    _proc[cur_pid].eflags   = regs->eflags;

    if(cur_pid == GUI_PID || cur_pid == FLOPPY_PID || cur_pid == FS_PID) //Special Case - Same privilege as the Kernel
    {
      _proc[cur_pid].ss       = regs->_ss;
      //4 for eip & for cs  & eflags - regs pushed by the processor
      _proc[cur_pid].esp      = regs->_esp + 4 + 4 + 4 + 4;

//      regs->user_esp          = _proc[cur_pid].esp;
//      regs->user_ss           = _proc[cur_pid].ss;
    }

  }
  else
  {
    cur_pid = 0;
  }

	i = regs->which_int;
  if(i != 0x20)
   {
   if(i == FLOPPY_INT && floppy_int_pending == 0)
      	floppy_int_pending = 1;
//     printf("intr : %d",i);
     for(j=0;j<intr_q.n;j++)
     {
       temp = get_element(&intr_q,j);
     if(temp != E_FAILURE)
      {
//        printf("temp = %d",temp);
       if(_proc[temp].wait_int_num == i)
         {
	   printf("temp = %d",temp);
           remove(&intr_q,temp);
           remove(&timer_q,temp);
           enq(&ready_q,temp);
	   _proc[temp].wait_int_num ==0;
	   _proc[temp].eax = 0;
	   if(i == FLOPPY_INT)
      		floppy_int_pending = 0;
//	   delay(0xFFFF);
         }
      }
     }
//     delay(0x1ff);
   }

	if(i == 0xE)//Pg fault'
	{
  		asm("movl %%cr2, %%eax":"=a"(cr2));
		printf("\nPg Fault: %x",cr2);
	}

	if(i != 0x21 && i != 0x20)
		printf("\nAsm exception %x", i);
//	printf("\nfloppy int pending : %d",floppy_int_pending);
	if(i < 0x20)
	{
    asm __volatile__("pushf");
    asm __volatile__("popl %%eax":"=a"(temp));
		printf("\nRogue pid %d eflags : %x",cur_pid,temp);
//		delay(0xFFFFFFFF);

		switch(i) //Handle Exceptions
		{
			case DIVIDE_ERROR:
			case INVALID_OPCODE:
			case DOUBLE_FAULT:
			case BAD_TSS:
			case GPF:
			case PAGE_FAULT:
              printf("\n_proc[].cr3 %x sys.cr3 %x",_proc[cur_pid].cr3,_system.cr3);
              if(graphics)
              {
                drawstring(50,200,"Sys Exception");
                drawstring(50,230,itoa(cur_pid,10));
                drawstring(50,240,itoa(i%10,10));
                mvBuf2Svga();
              }

//              delay(0xFFFFFFFF);
              if(_proc[cur_pid].eflags & (1<<17))
              {
                handleVM86(regs);
              }
              else
              {
//                mvBuf2Svga();
//                delay(0xFFFF);
					      remove(&ready_q,cur_pid);
  					    do_exit(cur_pid);
              }
 					    schedule();
							break;

			default:
							kdump();
							panic(itoa(which_int,10));
							break;
		}
//							kdump();
//							panic();

	}

	//EOI

//
// We could use this point to check whether a process is waiting
// for KBD input. If so buffer the character.
//
//	putch(decode(inb(0x60)));


//	delay(0x1FF);

	switch(which_int)
	{
		case 0x20: //Timer
//				printf("\nHandle Timer");
				handle_timer();
        eoi();
        schedule();
				break;

		case 0x21: // KBD
				handle_KBD();
        eoi();  
			  schedule();
				break;

    case 0x26:
          printf("\FLOPPY Interrupt");
          eoi();
          schedule();
          break;


		case 0x30: //SysCall
        handle_syscall(regs);
			  schedule();
				break;

    case 0x2C:
        printf("\nMouse Interrupt\n");
        handle_mouse1();
//        eoi();
        schedule();
        break;

		default:
				panic("y");
	}//switch(i)
  sti();
 }

 DD timer_i = 0;

 extern void _Z12cursor_paintv();
 
 void handle_timer()
 {
   DW i,temp;
   SEG_DESC *t;

   timer_i++;

  if(graphics)
   _Z12cursor_paintv();

//change

  if(timer_i%2000 == 0)
   {
//    ginfo(400,500,"in timer");
    _Z9draw_timeh(1);
   }

   if(timer_i%500 ==0) //For 1 second checks - Clock speed = 2ms
   {
// 	  printf("\nTimer Called : %d",timer_i);
    for(i=0;i<timer_q.n;i++)
     {
       temp = get_element(&timer_q,i);
     if(temp != E_FAILURE)
      {
//        printf("temp = %d",temp);
       if(_proc[temp].time_out == timer_i/500)
         {
//           printf("temp = %d",temp);
           if(remove(&intr_q,temp) != -1)
              _proc[temp].eax = -1;
           else
              _proc[temp].eax = 0;
           remove(&timer_q,temp);
           enq(&ready_q,temp);
         }
      }

     }
//    delay(0xFFF);
   }
//   schedule();
 }

 void handle_syscall(REGS * regs)
  {
		  DW i,num;
		  DD linear, phy;
   	  DD linear1, phy1;
      DD str_addr;
      DD msg_ptr;
      DW pid;
      SDW index;
      DD offs;
      DD buf;
      request r;
  	  fs_request fs_r;
      DD base;
      DD u_esp,u_ss;
      u_esp = regs->user_esp;
      u_ss = regs->user_ss;
      if(cur_pid == FLOPPY_PID || cur_pid == GUI_PID || cur_pid == FS_PID)
      {
         u_esp          = _proc[cur_pid].esp;
         u_ss           = _proc[cur_pid].ss;
      }
  //    printf(" esp : %x\n",u_esp);
      linear = logi_to_lin(cur_pid,u_ss,u_esp);
      phy = lin_to_phy(cur_pid,linear);
//      cls();
    //  printf("\nphy %x",phy);
//      printf("eax : %x",regs->eax);

	    switch(regs->eax)
      {
         case 0:
                 do_exit(cur_pid);
                 break;
         case 1://change
                 printf("\n\nCreate called");
		 linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
		 phy1 = lin_to_phy(cur_pid,linear1);
                 create(phy1);
//                 delay(0x1FF);
//                 create();
                 break;
         case 2:
                 printf("\n\nFork called");
                 delay(0x1FF);
//                 fork();
                 break;
         case 3: //send
                pid = *(DD *) phy;

//                cls();
//                for(index = -32 ; index < 36 ; index+=4)
//                {
//                 printf("\n phy-%d %x",index,*((DD*)phy+index));
//                }
//                BLOCK

                msg_ptr = *(DD *) (phy + 4);

//                linear = logi_to_lin(cur_pid,regs->cs,msg_ptr);
//                phy = lin_to_phy(cur_pid,linear);
//                printf("\npid = %d msg = %s",pid,(DB*)phy);

                if(pid == GUI_PID)
                {
                  printf("\nSEND:GUI:rem");
                  remove(&ready_q,cur_pid);
//                  printQ(&ready_q);
                  enq(&gui_q,cur_pid);
//                  printQ(&gui_q);
//                  delay(0xFFFFFF);
                }

                send(pid,(MSG *) msg_ptr);

                break;

         case 4://receive
                msg_ptr = *(DD *) phy;
                recv((MSG *) msg_ptr);

                break;
         case 5://sleep
                _proc[cur_pid].time_out = *(DD *) phy + timer_i/500;
                printf("time out %d,cur_time %d",_proc[cur_pid].time_out,timer_i);
                remove(&ready_q,cur_pid);
                enq(&timer_q,cur_pid);
//                printf("element = %d",get_element(&timer_q,0));

                break;
         case 6: //wait_for_interrupt
//         				ginfo(400,100,"wait_for_interrupt");
//         				ginfo(400,120,itoa(pid,10));
//         				ginfo(400,120,itoa(*(DD *) phy,10));

                _proc[cur_pid].wait_int_num = *(DD *) phy;
                printf("wait %d",_proc[cur_pid].wait_int_num);
                remove(&ready_q,cur_pid);
                enq(&intr_q,cur_pid);
                break;
         case 7://wait for interrupt and timer
                printf("\nwaiting for both int and timer");
            		if(*(DD *) phy == FLOPPY_INT && floppy_int_pending)
              	{
            			_proc[cur_pid].eax = 0;
              		floppy_int_pending = 0;
            		}
            		else
            		{

                _proc[cur_pid].wait_int_num = *(DD *) phy;
                _proc[cur_pid].time_out = *(DD *) (phy+4) + timer_i/500;
                remove(&ready_q,cur_pid);
                enq(&timer_q,cur_pid);
                enq(&intr_q,cur_pid);
                printf("\ntimer %x intr %x",_proc[cur_pid].time_out,_proc[cur_pid].wait_int_num);
            		}
                //delay(0xFFFF);
                break;
          case 8: //read floppy sector
                   printf("floppy");
                   offs = *(DD*)phy;
                   buf = *(DD *) (phy + 4);
                   r.r_count = 512;
                   r.offset = offs*512;
                   r.opcode = 1;
                   r.r_dma = buf;
                   r.pid = cur_pid;
                   if(addreq(&r) == -1)
                   {
                     _proc[cur_pid].eax = -1;
                   }
                   else
                   {
                     remove(&ready_q,cur_pid);
                     enq(&device_q[FLOPPY_DEV],cur_pid);
                   }
                  //		   cls();
                   printf("offs %d buf %x no_req %d",offs,buf,no_req);
//                   delay(0xFFFF);
                   break;
		 case 9: //write floppy sector(offs,a)
        				   printf("floppy");
                   offs = *(DD*)phy;
                   buf = *(DD *) (phy + 4);
                   r.r_count = 512;
                   r.offset = offs*512;
                   r.opcode = 2;
                   r.r_dma = buf;
                   r.pid = cur_pid;
                   if(addreq(&r) == -1)
                   {
                     _proc[cur_pid].eax = -1;
                   }
                   else
                   {
                     remove(&ready_q,cur_pid);
                     enq(&device_q[FLOPPY_DEV],cur_pid);
                   }
                   printf("write offs %d buf %x no_req %d",offs,buf,no_req);
//                   delay(0xFFFF);
        				   break;
         case 10: // printnum
                   num = *(DD*)phy;
                   base = *(DD *) (phy + 4);
                   printf("\nnum : %x %d",num,base);
//                   kprintnum(num,base);
                   delay(0xFFFF);
            		   break;

         case 11: //GUI processing over
                printf("\nsyscall:11");
                if(*(DW*)phy >= MAX_PROC)
                    panic("y");

                remove(&gui_q, *(DW*)phy);
                _proc[*(DW*)phy].eax = *(DW*)(phy+4);
                enq(&ready_q, *(DW*)phy);
                printf("\n pid %d retval %d",*(DW*)phy,*(DW*)(phy+4));
//                delay(0xFFFFF);
                break;
  	  case 12: // FS processing over(pid,ret_val)
      				printf("\nfs processing over");
			      	if(*(DW*)phy >= MAX_PROC)
                    panic("y");
      				remove(&fs_q, *(DW*)phy);

              _proc[*(DW*)phy].eax = *(DW*)(phy+4);
              enq(&ready_q, *(DW*)phy);

              printf("\n pid %d retval %d",*(DW*)phy,*(DW*)(phy+4));
              if(*(SDW*)(phy+4) == -1 && *(DW*)(phy+8) == LOAD)
              {
                printf("\n\ninside exit :");
                do_exit(*(DW*)phy);
              }
//              delay(0xFFF);
              break;
              
		 case 13: //open file(fname,mode)
      			  fs_r.type = OPEN;

			    	  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
				      phy1 = lin_to_phy(cur_pid,linear1);

	    			  fs_r.op.fname = (DB *)phy1;
  		  		  fs_r.op.mode = *(DW *) (phy + 4);
              fs_r.from_pid = cur_pid;
				      if(addfsreq(&fs_r) != 0)
    				  {
          			_proc[cur_pid].eax = -1;
              }
              else
              {
               remove(&ready_q,cur_pid);
               enq(&fs_q,cur_pid);
              }
  				  printf("\n fname %s, mode %d",fs_r.op.fname,fs_r.op.mode);
//            delay(0xFFFF);
	  			  break;
		 case 14: // close(fd_in)
            fs_r.type = CLOSE;

	    		  fs_r.cl.fd_in = *(DW *) (phy);
            fs_r.from_pid = cur_pid;
				    if(addfsreq(&fs_r) != 0)
				    {
  					_proc[cur_pid].eax = -1;
            }
            else
            {
              remove(&ready_q,cur_pid);
              enq(&fs_q,cur_pid);
            }
            printf("close : fd_in %d\n",fs_r.cl.fd_in);
	  			  break;
		 case 15: //read(int fd_in,char *buf,int length)
				  fs_r.type = READ;
          fs_r.from_pid = cur_pid;
				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)(phy+4));
				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.re.buf = (DB *)phy1;
				  fs_r.re.fd_in = *(DW *) (phy);
				  fs_r.re.len = *(DW *) (phy+8);
				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
           }
          else
           {
            remove(&ready_q,cur_pid);
            enq(&fs_q,cur_pid);
           }
//          delay(0xFFFF);        
				  break;
          
		case 16: //write(int fd_in,char *buf,int length)
				  fs_r.type = WRITE;
          fs_r.from_pid = cur_pid;
				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)(phy+4));
				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.wr.buf = (DB *)phy1;
				  fs_r.wr.fd_in = *(DW *) (phy);
				  fs_r.wr.len = *(DW *) (phy+8);
				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
                  }
                  else
                  {
                    remove(&ready_q,cur_pid);
                    enq(&fs_q,cur_pid);
                  }
				  break;
		case 17: //create(fname)
				  fs_r.type = CREATE;
          fs_r.from_pid = cur_pid;
				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.cr.name = (DB *)phy1;

				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
                  }
                  else
                  {

                    remove(&ready_q,cur_pid);
                    enq(&fs_q,cur_pid);
                  }
				  break;
		case 18 : //opendir(name)
				  fs_r.type = OPENDIR;
          fs_r.from_pid = cur_pid;
				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.opd.dir_name = (DB *)phy1;

				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
                  }
                  else
                  {
                    remove(&ready_q,cur_pid);
                    enq(&fs_q,cur_pid);
                  }
				  break;
		case 19: //createdir(name)
				  fs_r.type = CREATEDIR;
          fs_r.from_pid = cur_pid;
				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.crd.name = (DB *)phy1;

				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
                  }
                  else
                  {
                    remove(&ready_q,cur_pid);
                    enq(&fs_q,cur_pid);
                  }
				  break;
		case 20: //closedir(dd_in)
				  fs_r.type = CLOSEDIR;
          fs_r.from_pid = cur_pid;
				  fs_r.cld.dd_in = *(DW *) (phy);
				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
                  }
                  else
                  {
                    remove(&ready_q,cur_pid);
                    enq(&fs_q,cur_pid);
                  }
				  break;
		case 21: //readdir(dd_in,dirent*)
				  fs_r.type = READDIR;
          fs_r.from_pid = cur_pid;
				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)(phy+4));
				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.red.dir = (DIRENT *)phy1;
				  fs_r.red.dd_in = *(DW *) (phy);
				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
                  }
                  else
                  {
                    remove(&ready_q,cur_pid);
                    enq(&fs_q,cur_pid);
                  }
				  break;
		case 22: //remove(name)
				  fs_r.type = REMOVE;
          fs_r.from_pid = cur_pid;

				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);

				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.rem.name = (DB *)phy1;

				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
          }
           else
            {
              remove(&ready_q,cur_pid);
              enq(&fs_q,cur_pid);
            }
				  break;
		case 23: // rename(old_name,new_name)
				  fs_r.type = RENAME;
          fs_r.from_pid = cur_pid;
				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.ren.old_name = (DB *)phy1;

				  linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)(phy+4));
				  phy1 = lin_to_phy(cur_pid,linear1);

				  fs_r.ren.new_name = (DB *)phy1;

				  if(addfsreq(&fs_r) != 0)
				  {
					_proc[cur_pid].eax = -1;
                  }
                  else
                  {
                    remove(&ready_q,cur_pid);
                    enq(&fs_q,cur_pid);
                  }
		break;
//change
		case 30: //getdate(DATE *)
			linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
			phy1 = lin_to_phy(cur_pid,linear1);
			getdate((DATE *)phy1);
			break;
		case 31: //setdate(DATE *)
			linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
			phy1 = lin_to_phy(cur_pid,linear1);
			setdate((DATE *)phy1);
			break;
		case 32: //gettime(TIME *)
			linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
			phy1 = lin_to_phy(cur_pid,linear1);
			gettime((TIME *)phy1);
			break;
		case 33: //settime(TIME *)
			linear1 = logi_to_lin(cur_pid,_proc[cur_pid].cs,*(DD*)phy);
			phy1 = lin_to_phy(cur_pid,linear1);
			settime((TIME *)phy1);
			break;

         case 255://string passing
         				 printf("\n2^X");

              	 delay(0x1FF);
//                 do_pow((regs->eax>>16)&0xFFFF);
//                 cls();

//						   for(i = 0 ; i < 4 ; i++)

//						   {
                 linear = logi_to_lin(cur_pid,u_ss,u_esp);
                 phy = lin_to_phy(cur_pid,linear);
//								 printf("\nlogi %x:%x lin %x phys %x\n",u_ss,u_esp,linear,phy);

                 str_addr = *(DD *)phy;
//								 printf("\t%x",str_addr);

                 linear = logi_to_lin(cur_pid,_proc[cur_pid].cs,str_addr);
                 phy = lin_to_phy(cur_pid,linear);
//								 printf("\nlogi %x:%x lin %x phys %x\n",_proc[cur_pid].cs,str_addr,linear,phy);
//                 printf("%s",(DB *)phy);

                 for(i = 0 ; i < 10 ; i++)
						      {
                     printf("%x",*(DB *) (phy + i));
//     								 delay(0x5FF);
                  }
//								 regs->user_esp++;

//						   }
                 break;

         default:
         				 printf("\n\nUnknown SysCall Interface invoked.");
              	 delay(0xFFF);
         				 break;
      }
  }

void do_pow(DW val)
{
	_proc[cur_pid].eax = 2*val;
	printf("\ndo_pow %d",	_proc[cur_pid].eax);
}
void eoi()
{
 if(which_int >= 0x28 && which_int <= 0x2F)
	{
  	outb(0xA0,0x20);
	  outb(0x20,0x20);
	}
	else if(which_int >= 0x20 && which_int < 0x28)
	{
	   outb(0x20,0x20);
	}

}
