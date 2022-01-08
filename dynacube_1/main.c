/***************************************************************************
                          main.c  -  description
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
#include "stdlib.h"
#include "string.h"
#include "mm.h"
#include "proc.h"
#include "ktask.h"
#include "queue.h"
#include "kpic.h"
#include "floppy.h"

#include "zorder.h"
#include "vm86.h"
#include "svga.h"
#include "fat12.h"


#include "stack.h"

#include "gui.h"
#include "hashmap.h"

//#include "client_gui.h"

extern void _Z6runGUIv();
extern void _Z9list_initv();
void callGUI();
void testFS();

//#define VMWARE 1

int main(void)
{
 //Global Initialization
 //Perhaps should replace it with some init()
 row = 0, col = 0;
 char buf[512];
 int temp = 123;
 int temp1, temp2;
 char val;
 DD i,j;
 char *_data;
 DW seg;
 DD offset;
 DD linear, phy;

 cli();
 cls();

 kprint("Dynacube\t1.0\tLoading [dd/mm/yyyy]\n");
 kprint("------------------------------------------------------\n");

 printf("\n\n\n\t\tHELLO WORLD !!!\n\n");
 kdump();

// BLOCK
 gdt_init();

 kprint("\nSystem Descriptors Loaded................ ");

 pic_init();

 kprint("\nPIC remapped................ \n");

 printf("\nkrnl_size %x val: %d",KERNEL_SIZE,(PHYS_MEM/_4MB));

 task_init();
 proc_init();


 memcpy((void *)(KERNEL_SIZE),(void *)null_proc,512);

 q_init(&ready_q);
 q_init(&message_q);
 q_init(&timer_q);
 q_init(&intr_q);
 q_init(&gui_q);
 q_init(&fs_q);

 for(i = 0 ; i < 3 ; i++)
   q_init(&device_q[i]);

 z_init();
 hash_init();

 _Z9list_initv();

 cls();

  vbe_mode = *((VBE_ModeInfo *) (0x91000));
  printf("\nPhys addr: %x xRes %d yRes %d bpp %d",vbe_mode.PhysBasePtr,vbe_mode.XResolution,vbe_mode.YResolution,vbe_mode.BitsPerPixel);
  printf("\nModeAttributes : %x",vbe_mode.ModeAttributes);

//  initgraphics(800,600,16,vbe_mode.PhysBasePtr);
//  setScreen(SCREEN_COLOR);

//  startVM86();

  post_vm86();

// read_sector(0,buf);
// read_file_sample();
// BLOCK

 //NULL PROC

 while(1);

 return 0;
}


void startGUI()
{
  _proc[GUI_PID].avl = _false;

  _proc[GUI_PID].cr3 = _system.cr3;

  _proc[GUI_PID].cs = _system.cs;
  _proc[GUI_PID].ds = _system.ds;
  _proc[GUI_PID].ss = GUI_STACK_SEL * 8; //_system.ss;//
  _proc[GUI_PID].es = _system.es;
  _proc[GUI_PID].fs = _system.fs;
  _proc[GUI_PID].gs = _system.gs;

  _proc[GUI_PID].eax = 0;
  _proc[GUI_PID].ebx = 0;
  _proc[GUI_PID].ecx = 0;
  _proc[GUI_PID].edx = 0;
  _proc[GUI_PID].esi = 0;
  _proc[GUI_PID].edi = 0;
  _proc[GUI_PID].ebp = 0;

  _proc[GUI_PID].esp = (KERNEL_SIZE - 2 *_4MB/4); //Set ESP
  _proc[GUI_PID].eip = _Z6runGUIv;
  _proc[GUI_PID].eflags = _system.eflags | (1<<9);

  _proc[GUI_PID].ss0 = _system.ss;
  _proc[GUI_PID].ss1 = NULL1_SEL;
  _proc[GUI_PID].ss2 = NULL1_SEL;   
  
  _proc[GUI_PID].ldt_sel = LDT_USR_SEL * 8; //_system.ldt_sel;
  
   enq(&ready_q,GUI_PID);    
}

void startFloppy()
{
  _proc[FLOPPY_PID].avl = _false;

  _proc[FLOPPY_PID].cr3 = _system.cr3;

  _proc[FLOPPY_PID].cs = _system.cs;
  _proc[FLOPPY_PID].ds = _system.ds;
  _proc[FLOPPY_PID].ss = FLOPPY_STACK_SEL * 8; //_system.ss;//
  _proc[FLOPPY_PID].es = _system.es;
  _proc[FLOPPY_PID].fs = _system.fs;
  _proc[FLOPPY_PID].gs = _system.gs;

  _proc[FLOPPY_PID].eax = 0;
  _proc[FLOPPY_PID].ebx = 0;
  _proc[FLOPPY_PID].ecx = 0;
  _proc[FLOPPY_PID].edx = 0;
  _proc[FLOPPY_PID].esi = 0;
  _proc[FLOPPY_PID].edi = 0;
  _proc[FLOPPY_PID].ebp = 0;

  _proc[FLOPPY_PID].esp = (KERNEL_SIZE - _4MB/4); //Set ESP
  _proc[FLOPPY_PID].eip =  runFloppy; // callGUI; 
  _proc[FLOPPY_PID].eflags = _system.eflags | (1<<9);

  _proc[FLOPPY_PID].ss0 = _system.ss;
  _proc[FLOPPY_PID].ss1 = NULL1_SEL;
  _proc[FLOPPY_PID].ss2 = NULL1_SEL;

  _proc[FLOPPY_PID].ldt_sel = LDT_USR_SEL * 8; //_system.ldt_sel;

   enq(&ready_q,FLOPPY_PID);
}
void startFS()
{
  _proc[FS_PID].avl = _false;

  _proc[FS_PID].cr3 = _system.cr3;

  _proc[FS_PID].cs = _system.cs;
  _proc[FS_PID].ds = _system.ds;
  _proc[FS_PID].ss = FS_STACK_SEL * 8; //_system.ss;//
  _proc[FS_PID].es = _system.es;
  _proc[FS_PID].fs = _system.fs;
  _proc[FS_PID].gs = _system.gs;

  _proc[FS_PID].eax = 0;
  _proc[FS_PID].ebx = 0;
  _proc[FS_PID].ecx = 0;
  _proc[FS_PID].edx = 0;
  _proc[FS_PID].esi = 0;
  _proc[FS_PID].edi = 0;
  _proc[FS_PID].ebp = 0;

  _proc[FS_PID].esp = (KERNEL_SIZE - _4MB); //Set ESP
  _proc[FS_PID].eip =  runFS;
  _proc[FS_PID].eflags = _system.eflags | (1<<9);

  _proc[FS_PID].ss0 = _system.ss;
  _proc[FS_PID].ss1 = NULL1_SEL;
  _proc[FS_PID].ss2 = NULL1_SEL;

  _proc[FS_PID].ldt_sel = LDT_USR_SEL * 8; //_system.ldt_sel;

   enq(&ready_q,FS_PID);
}


void startVM86()
{
   memcpy(0x90000,svgainit,0x10000);
   
  _proc[VM86_PID].avl = _false;

  _proc[VM86_PID].cr3 = _system.cr3;

  _proc[VM86_PID].cs = 0x9000;
  _proc[VM86_PID].ds = 0x9000;
  _proc[VM86_PID].ss = 0x8000; //_system.ss;//
  _proc[VM86_PID].es = 0x9000;
  _proc[VM86_PID].fs = 0x9000;
  _proc[VM86_PID].gs = 0x9000;

  _proc[VM86_PID].eax = 0;
  _proc[VM86_PID].ebx = 0;
  _proc[VM86_PID].ecx = 0;
  _proc[VM86_PID].edx = 0;
  _proc[VM86_PID].esi = 0;
  _proc[VM86_PID].edi = 0x1000;
  _proc[VM86_PID].ebp = 0;

  _proc[VM86_PID].esp = 0xFFFF; //Set ESP
  _proc[VM86_PID].eip = 0;
  _proc[VM86_PID].eflags = 0x2 | (1<<17);

  _proc[VM86_PID].ss0 = _system.ss;
  _proc[VM86_PID].ss1 = NULL1_SEL;
  _proc[VM86_PID].ss2 = NULL1_SEL;

  _proc[VM86_PID].ldt_sel = LDT_USR_SEL * 8; //_system.ldt_sel;
  
   enq(&ready_q,VM86_PID);
   schedule();
}

void post_vm86()
{
 DD i,j; 

 mouse_init1();

 mm_init();
 task_init();
 proc_init();
 fs_init();

 forkNULL();
 startGUI();
 startFloppy();
 startFS();
 create("\\editor");
// create("\\calc");
// create("\\run");
// create("\\timeset");

// create("\\explorer");
 printQ(&ready_q);
// BLOCK

 cls();
 pit0_init(1);
 pic_enable(TIMER);
 pic_enable(KEYBOARD);
 pic_enable(FLOPPY);
 pic_enable(PS2_MOUSE);
 
 sti();

 BLOCK
}

char fname[255];
char buf[512];
SDD p,i,q;
void testFS()
{
 SDD res;
 DIRENT ds;
 MSG msg;

 asm("pushl %0"::"r"(&msg));
 asm("int $0x30"::"a"(4));


// rename("\\source1\\s6","\\source1\\s7");
// BLOCK
// fs_remove("\\source1");
// BLOCK


//  p = opendir("\\");
//  if(p != -1)
//  {
//   while(readdir(p,&ds) == 0)
//   {
//     cli();
//	  print_dirent(&ds);
//    delay(0xFFFF);
//    sti();
//   }
//   closedir(p);
//  }
//BLOCK

// BLOCK
 cli();
// cls();
 printf("\n create res :%d",creat("\\source1\\s5"));

 delay(0xFFF);
 sti();
  buf[0] = 'b';
  buf[1] = 'y';
  buf[2] = 'e';
  buf[3] = ' ';

  p = open("\\source1\\s5",O_RDWR);
  printf("p = %d",p);
  if(p >= 0)
  {
    write(p,buf,4);
    close(p);
  }  


BLOCK

 
// createdir("\\source1\\s1");
// createdir("\\source1\\s1\\s3");
// createdir("\\source1\\s1\\s4");
// creat("\\source1\\s1\\s5");
// BLOCK
// strcpy(fname,"\\source1\\s5");
//  q = open(fname,O_RDWR);
 strcpy(fname,"\\test");
 p = open(fname,O_RDONLY);

// cli();
// cls();
 printf("\nopen ret : %d",p);
// printf("\nopen ret1 : %d",q);
// delay(0xFFF);
// sti();
 if(p >= 0)// && q>= 0)
 {
   while((res = read(p,buf,512)) > 0)
   {
    cli();
//    cls();
    printf("\n\nread in client res : %d\n",res);
 	  for(i=0;i<res;i++)
		  putch(buf[i]);
//   printf("write out : %d",write(q,buf,res));
    delay(0xFFFF);
    sti();
   }
  cls();
  printf("\nopen ret : %d",p);
  res = close(p);
  cli();
  printf("\close ret : %d",res);
  delay(0xFFFF);
  sti();
//   res = close(q);
//  cli();
//  printf("\close ret : %d",res);
//  delay(0xFFF);
//  sti();

 }
 BLOCK;
}

/* void callGUI()
{
  volatile MSG msg;
  CREATE_INFO cr;
  COMP_CREATE_INFO cmp;
  RESIZE_INFO rs;
  SDD ret_val = -1;
  DB i;
  
       
     msg.length = sizeof(cr);
     msg.type   = CREATE;
     msg.sub_type = WINDOW;
     cr.alias_id = 101;
     cr.cntr_id = 0;
     cr.height = 200;
     cr.width = 400;
     cr.style  = 0;
     cr.x = 100;
     cr.y = 50;
     strcpy(cr.title,"Explorer");
     
     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));

     asm("int $0x30"::"a"(3));

     cr.alias_id = 102;
     cr.cntr_id = 0;
     cr.height = 200;
     cr.width = 200;
     cr.style  = 0;
     cr.x = 150;
     cr.y = 75;
     strcpy(cr.title,"Explorer 2");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     
     msg.sub_type = BUTTON;
     cmp.alias_id = 201;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 70;
     cmp.x = 200;
     cmp.y = 30;
     strcpy(cmp.label,"BUTTON 1");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = TEXT;
     cmp.alias_id = 202;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 50;
     cmp.x = 100;
     cmp.y = 30;
     strcpy(cmp.label,"TEXT1 sdfkjdkgjkhldsgklh dklg 2");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));     
     asm("int $0x30"::"a"(3));

     
     msg.sub_type = LABEL;
     cmp.alias_id = 203;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 20;
     cmp.width = 50;
     cmp.x = 50;
     cmp.y = 30;
     strcpy(cmp.label,"LABEL");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     
     msg.sub_type = TEXTAREA;
     cmp.alias_id = 206;
     cmp.cntr_id = 101;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 50;
     cmp.width = 100;
     cmp.x = 100;
     cmp.y = 70;
     strcpy(cmp.label,"TEXTAREA 1");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

          
     msg.sub_type = FOLDERVIEW;
     cmp.alias_id = 258;
     cmp.cntr_id = 102;
     cmp.cnt_type = WIND_TYPE;
     cmp.height = 150;
     cmp.width = 150;
     cmp.x = 0;
     cmp.y = 0;
     strcpy(cmp.label,"/root");

     memcpy(msg.msg_buf,&cmp,sizeof(cmp));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     msg.sub_type = WINDOW; 
     cr.alias_id = 103;
     cr.cntr_id = 0;
     cr.height = 0;
     cr.width = 0;
     cr.style  = 0;
     cr.x = 300;
     cr.y = 130;
     strcpy(cr.title,"Explorer 3");

     memcpy(msg.msg_buf,&cr,sizeof(cr));

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));
                                        
     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 101;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));

     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 102;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));

     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 103;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     asm("pushl %eax");
     asm("popl %0"::"r"(ret_val));

     i = 0;

     while(1)
     {
       asm("pushl %0"::"r"(&msg));
       asm("int $0x30"::"a"(4));
    
       switch(msg.type)
       {
         case WM_CLICKED:

                switch(msg.sub_type)
                {                  
                 case BUT_TYPE:
//                        ginfo(400,300,itoa(msg.type,10));
//                        ginfo(400,350,itoa(msg.sub_type,10));
//                        ginfo(400,400,itoa(*(DW*)msg.msg_buf,10));

                        msg.type     = FINISHED;
                        msg.sub_type = BUT_TYPE;
                        msg.length   = sizeof(DD);

                        asm("pushl %0"::"r"(&msg));
                        asm("pushl %0"::"r"(GUI_PID));
                        asm("int $0x30"::"a"(3));

                      break; 
                }
                break;
                
         case WM_KEYPRESS:
                break;
                
         case WM_DESTROY:
                break;
       }

     }
}


/*
     while(1)
     {
       asm("pushl %0"::"r"(&msg));
       asm("int $0x30"::"a"(4));

       printf("\n\n\nfrom_pid %d ",msg.from_pid);
       printf("\nbuffer %s",msg.msg_buf);

       if(msg.type == WM_DESTROY)
       {
         cli();
         ginfo(400,300,itoa(*(DW*)msg.msg_buf,10));
         delay(0xFFFF);
         sti();

       rs.alias_id = 101;
       rs.x = 0;
       rs.y = 0;
       rs.width = 500;
       rs.height = 200;

       memcpy(msg.msg_buf,&rs,sizeof(rs));
       msg.type     = RESIZE;
       msg.sub_type = WINDOW;
       msg.length   = sizeof(rs);

       asm("pushl %0"::"r"(&msg));
       asm("pushl %0"::"r"(GUI_PID));
       asm("int $0x30"::"a"(3));
       }

     }

     while(1);

//     while(1)
     {
//       delay(0x5FFF);

     msg.type     = HIDE;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 101+i;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     delay(0x0);

     msg.type     = SHOW;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(DW);
     msg.msg_buf[0] = 101+i;

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     delay(0x0);
     rs.alias_id = 101;
     rs.x = 0;
     rs.y = 0;
     rs.width = 500;
     rs.height = 200;

     memcpy(msg.msg_buf,&rs,sizeof(rs));
     msg.type     = RESIZE;
     msg.sub_type = WINDOW;
     msg.length   = sizeof(rs);

     asm("pushl %0"::"r"(&msg));
     asm("pushl %0"::"r"(GUI_PID));
     asm("int $0x30"::"a"(3));

     i++;
     i %= 3;
     }

     BLOCK


//     VM_DELAY( "\n HELLO FROM Client");

//     if(ret_val == 0)
//     {
//       printf("Success");
//     }
//     else
//       printf("Failure");

     }

//     msg.type     = DESTROY;
//     msg.sub_type = WINDOW;
//     msg.length   = sizeof(DW);
//     msg.msg_buf[0] = 101;
//
//     asm("pushl %0"::"r"(&msg));
//     asm("pushl %0"::"r"(GUI_PID));
//     asm("int $0x30"::"a"(3));
//
//     fillrect(300,100,100,100,0xCFCF);

//     printf("\nMesg from GUI client");


  }
//  msg.type = CREATE;

//  send(GUI_PID,);
*/
