/***************************************************************************
                          kstdio.c  -  description
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

//Master Header
#include "kmaster.h"
//Generic dlib (Dynacube Lib)
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"
#include "proc.h"

int row = 0;
int col = 0;
int grow = 0;
int gcol = 0;

DD gcls_delay = 0x1FFF; //The delay for gcls - Just a crap to handle GUI Dbgr

#define NEED_DBG 1
#undef NEED_DBG


  void printRegs(REGS* regs)
  {
		#ifdef __DEBUG__

    printf("\nprintRegs");
    printf("\n cur_pid %d int %x ecode %x",cur_pid,regs->which_int,regs->err_code);
    printf("\ncs %x ds %x eip %x",regs->cs,regs->ds,regs->eip);
    printf("\nes %x fs %x gs %x",regs->es,regs->fs,regs->gs);
    printf("\neflag %x u_esp %x u_ss %x",regs->eflags,regs->user_esp, regs->user_ss);
    printf("\n_esp %x _ss %x",regs->_esp, regs->_ss);
    printf("\nesi %x edi %x",regs->esi,regs->edi);

    #endif
  }

void cls()
{
 #ifdef __DEBUG__	
 unsigned char *vidmem = (unsigned char *)0xB8000;
 long size = COLSIZE * ROWSIZE * 2;

 #ifdef NEED_DBG
 if(graphics)
 {
  gcls();
  return;
 }
 #endif

 while(size >= 0)
 {
   *(vidmem+size) = ' ';
    size-=2;
 }
 row=0;
 col=0;

 #endif
}

void kprint(char *str)
{
  #ifdef __DEBUG__
  unsigned char *vidmem = (unsigned char *)0xB8000;
  char ch;
  int i;

  #if NEED_DBG
  if(chkGraphicsInited())
    {
      gprint(str);
      return;
    }
  #endif

  if(row > ROWSIZE)
  {
  	row = 0;
  	col = 0;
	  cls();
  }

  vidmem += row*2*COLSIZE+2*col;

  while(*str != '\0')
  {
  	ch = *str++;

	switch(ch)
	{
	 case '\n':
		row++;
	  	col = 0;
	  	vidmem = (unsigned char *)0xB8000 + row*2*COLSIZE;
	 	break;

	 case '\t':
	 	for(i=0;i<TABSIZE;i++)
		{
	         *vidmem++ = ' ';
		 *vidmem++ = 0x0A;
         	 col++;
		}
	 	break;

	 default:
	        *vidmem++ = ch;
	        *vidmem++ = 0x0A;
         	col++;
	 	break;
	}

    if(col > COLSIZE)
    {
    	row++;
  	col = 0;
    }

  }

  updateCursor();
  #endif
}

void gcls()
{
  #ifdef __DEBUG__
    delay(gcls_delay);
  	grow = 0;
  	gcol = 0;
	  rect(DEBUGGER_X,0,400,600);
  #endif
}

void gprint(char *str)
{
  #ifdef __DEBUG__	
  static DB count = 0;
  char ch;
  int i;

  if(!graphics)
      return;

  if(grow > GROWSIZE)
  {
    gcls();
  }

  while(*str != '\0')
  {
  	ch = *str++;


  	switch(ch)
  	{
  	 case '\n':
          		grow++;
         	  	gcol = 0;
          	 	break;

  	 case '\t':
          	 	for(i=0;i<TABSIZE;i++)
          		{
               drawChar(DEBUGGER_X+DEBUGGER_OFFSET+gcol*7,grow*9,0);
             	 gcol++;
          		}
          	 	break;

  	 default:
            drawChar(DEBUGGER_X+DEBUGGER_OFFSET+gcol*7,grow*9,ch);
           	gcol++;
        	 	break;
  	}

    if(gcol > GCOLSIZE)
    {
    	grow++;
    	gcol = 0;
    }

   }
   if(count % 100 ==0)
      mvBuf2Svga();
   count++;

 #endif
}


void kprintln()
{
 #ifdef __DEBUG__
 if(row > ROWSIZE)
 {
  cls();
  row = 0;
 }
 else
 {
  row++;
 }
 col = 0;
 #endif
}


extern boolean graphics;

void panic(DB *info)
{
  unsigned char *vidmem = (unsigned char *)0xB8000 + 2*row*COLSIZE + 2*col;
  char *str = "PANIC_MODE: System in panic mode";

  //cls();

  if(graphics)
  {
    drawstring(50,200,str);
    drawstring(50,230,info);
    mvBuf2Svga();
  }

  while(*str != '\0')
  {
       *vidmem++ = *str++;
       *vidmem++ = 0x0C;
  }
  printf(info);

  for(;;)
    ;
}

void ginfo(DW x, DW y, char *info )
{
//	#ifdef __DEBUG__
  if(graphics)
  {
    drawstring(x,y,info);
    mvBuf2Svga();
  }
//  #endif
}

void updateCursor()
{
  #ifdef __DEBUG__
  DW position=(row*COLSIZE) + col;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (DB)(position&0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (DB)((position>>8)&0xFF));
  #endif
}


void printf(char fmt[],...)
{
  #ifdef __DEBUG__
  DB index = 0, len = 0;  
  DB temp[MINI_BUFFER]={0};
  DB *tmp = NULL;
  va_list ap;

  va_start(ap,fmt);

  while(*fmt)
  {
    if(*fmt == '%')
    {
      switch(*(fmt+1))
      {
        case 'd': //Decimal Numbers
            tmp = itoa(va_arg(ap,int),10);
            len = strlen(tmp);
            memcpy(temp+index,tmp,len);
            index+=len;
            fmt++;
            break;

        case 'x': //Decimal Numbers
            tmp = itoa(va_arg(ap,int),16);
            len = strlen(tmp)+2; //For 0x
            memcpy(temp+index,"0x",2);
            memcpy(temp+index+2,tmp,len);
            index+=len;
            fmt++;
            break;

       case 'b': //Binary added on 26/12/2003
       			tmp = itoa(va_arg(ap,int),2);
            len = strlen(tmp)+1; //For b for BINARY
            memcpy(temp+index,"b",1);
            memcpy(temp+index+1,tmp,len);
            index+=len;
            fmt++;
            break;

        case 's': //char *
            tmp = va_arg(ap,char*);
            len = strlen(tmp);
            memcpy(temp+index,tmp,len);
            index+=len;
            fmt++;
            break;
         case 'c' :
       			*tmp = va_arg(ap,char);
            memcpy(temp+index,tmp,1);
            index+=1;
            fmt++;
            break;

        default:
            temp[index++] = '%';
            break;
      }
      fmt++;
    }
    else
      temp[index++] = *fmt++;
  }

  kprint(temp);
  va_end(ap);

  #endif
}


void kprintnum(long num,int base)
{
  #ifdef __DEBUG__
  switch(base)
  {
   case 16:
   	kprint("0x");
    kprint(itoa(num,base));
   	break;

   case 2:
   	kprint("b");
    kprint(itoa(num,base));
  	break;

   case 10: //For Decimal
    kprint(itoa(num,base));
  	break;

   default:
   	kprint("\nBase not known\tFile Name : \t");
  	kprint(__FILE__);
  	return;
  	break;
  }
  #endif
}


  void putch(char ch)
  {
    #ifdef __DEBUG__		
    unsigned char *vidmem = (unsigned char *)0xB8000;
	  vidmem += row*2*COLSIZE+2*col;

	  *vidmem = ch;
	  *(vidmem+1) = 0x0A;
	  col += 1;

	  if(col > COLSIZE)
	  {
			row++;
			col = 0;
		}

		updateCursor();
	  #endif
  }


