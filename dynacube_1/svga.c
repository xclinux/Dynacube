/***************************************************************************
                          svga.c  -  description
                             -------------------
    begin                : Sat Feb 7 2004
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

 #include "svga.h"


 DB vgabios_buffer[0x8000]; //32Kb
 DB svga_stack[1024];
 DB BIOSData[0x600];

 struct
 {
   DD addr;
   DD entry_off;
   DD init_off;
   
   DD bk_ss, bk_esp, bk_ds;
 }pm_info;

 void svga_init()
 {
  DB *pm = (DB *)(vgabios_buffer + pm_info.addr);
  memcpy(vgabios_buffer,0xC0000,0x8000);

  //Bios Data Sel
  *(pm + 8) = BIOS_DATA_SEL*8;
  *(pm + 9) = 0;

  //A000 Data Sel
  *(pm + 10) = A000_SEL * 8;
  *(pm + 11) = 0;

  //B000 Data Sel
  *(pm + 12) = B000_SEL * 8;
  *(pm + 13) = 0;

  //B800 Data Sel
  *(pm + 14) = B800_SEL * 8;
  *(pm + 15) = 0;

  //SVGA Data Sel
  *(pm + 16) = SVGA_DATA_16_SEL * 8;
  *(pm + 17) = 0;

  //In Protect Mode
  *(pm + 18) = 1;
    
  asm("movl %%ss,%%eax":"=a"(pm_info.bk_ss));
  asm("movl %%ds,%%eax":"=a"(pm_info.bk_ds));
  asm("movl %%esp,%%eax":"=a"(pm_info.bk_esp));
    
  lds(SVGA_DATA_16_SEL * 8);
  lss(SVGA_STACK_16_SEL * 8);
  asm("movl %%eax, %%esp"::"a"(0x0));

  asm("lcall %0, $0x0"::"i"(SVGA_CODE_16_SEL * 8));
 }

 
 void PMID_detect()
 {
   DD temp, temp1 ,temp2, i;
   
   for( temp2=0,temp1 = 0,temp = 0xA0000 ; temp < 0xFFFFF ; temp++)
   {
    if(*(DB *)(temp) == 'P' && *(DB *)(temp+1) == 'M' && *(DB *)(temp+2) == 'I' && *(DB *)(temp+3) == 'D')
    {
      temp1++;
      cls();
      printf("\nPMID Addr: %x",temp);
      
      pm_info.addr      = temp;
      pm_info.entry_off = *(DW *)(temp+4);
      pm_info.init_off =  *(DW *)(temp+6);

      printf("\naddr %x entry %x init %x",pm_info.addr,pm_info.entry_off,pm_info.init_off);
      delay(0xFFFFFFFF);
      
      for(i = 0 ; i < 20 ; i++)
      {
        printf("\ni: %d %x",i,*(DB *)(temp+i));
        delay(0xFFFFFFFF);
      }

      break;  
    }
    else if(*(DB *)(temp) == '_' && *(DB *)(temp+1) == '3' && *(DB *)(temp+2) == '2' && *(DB *)(temp+3) == '_')
    {
      temp2++;
      cls();
      printf("\n_32_ Addr: %x",temp);
      for(i = 0 ; i < 16 ; i++)
      {
        printf("\ni: %d %x",i,*(DB *)(temp+i));
        delay(0xFFFFFFFF);
      }
    }
    else
     printf("\n temp:%x %x",temp,*(DB *)temp);
   }
   printf("\nOut of PMID detect %d %d",temp1,temp2);
   
  }