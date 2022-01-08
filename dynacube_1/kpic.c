/***************************************************************************
                          kpic.c  -  description
                             -------------------
    begin                : Fri Jan 2 2004
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

 #include "kpic.h"

 void pic_init()
 {
	DB a1, a2;

	a1=inb(PIC1_DATA);
	a2=inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	outb(PIC1_DATA, 0x20);
	outb(PIC2_DATA, 0x28);
	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);
	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, a1|TIMER|KEYBOARD);
//	outb(PIC2_DATA, a2);
 	outb(PIC2_DATA, a2 & ~2);
 }

 void pic_enable(DW dev_code)
 {
	DB flags1 = inb(0x21), flags2 = inb(0xA1);

  if(dev_code & 0xFF)
  {
    dev_code &= 0xFF;
    outb(0x21,flags1 & ~dev_code); // | TIMER); //Enable Keyboard & Disable Timer | TIMER
  }
  else if(dev_code & 0xFF00)
  {
    dev_code >>= 8;
    outb(0xA1,flags2 & ~dev_code);
  }
  else
    printf("\nUnknown Device number %d",dev_code);
 }

 void pic_disable(DW dev_code)
 {
	DB flags1 = inb(0x21), flags2 = inb(0xA1);

  if(dev_code & 0xFF)
  {
    dev_code &= 0xFF;
    outb(0x21,flags1 | dev_code);
  }
  else if(dev_code & 0xFF00)
  {
    dev_code >>= 8;
    outb(0xA1,flags2 | dev_code);
  }
  else
    printf("\nUnknown Device number %d",dev_code);
 }
 
// void pic_enable(DB dev_code)
// {
//	DB flags1 = inb(0x21), flags2 = inb(0xA1);
//  outb(0x21,flags1 & ~dev_code); // | TIMER); //Enable Keyboard & Disable Timer | TIMER
//  outb(0xA1,flags2);
////  outb(0xA1,~0);
// }
//
// void pic_disable(DB dev_code)
// {
//	DB flags1 = inb(0x21), flags2 = inb(0xA1);
//	outb(PIC1_DATA,flags1 | dev_code);
//	//Add code for slave
// }
 