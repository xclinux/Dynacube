/***************************************************************************
                          kpit.h  -  description
                             -------------------
    begin                : Sat Jan 2 2004
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

#ifndef __KPIT_H
#define __KPIT_H

	#include "ktypes.h"
	
/*
8253/8254 PIT - Programmable Interval Timer 
	Port 40h, 8253 Counter 0 Time of Day Clock (normally mode 3)
	Port 41h, 8253 Counter 1 RAM Refresh Counter (normally mode 2)
	Port 42h, 8253 Counter 2 Cassette and Speaker Functions
	Port 43h, 8253 Mode Control Register, data format:

	|7|6|5|4|3|2|1|0|  Mode Control Register
	 | | | | | | | +---- 0=16 binary counter, 1=4 decade BCD counter
	 | | | | +--------- counter mode bits
	 | | +------------ read/write/latch format bits
	 +--------------- counter select bits (also 8254 read back command)
Bits 
	 76 Counter Select Bits
	 00  select counter 0
	 01  select counter 1
	 10  select counter 2
	 11  read back command (8254 only, illegal on 8253, see below)
Bits 
	 54  Read/Write/Latch Format Bits
	 00  latch present counter value
	 01  read/write of MSB only
	 10  read/write of LSB only
	 11  read/write LSB, followed by write of MSB
Bits 
	321  Counter Mode Bits
	000  mode 0, interrupt on terminal count;  countdown, interrupt,
	     then wait for a new mode or count; loading a new count in the
	     middle of a count stops the countdown
	001  mode 1, programmable one-shot; countdown with optional
	     restart; reloading the counter will not affect the countdown
	     until after the following trigger
	010  mode 2, rate generator; generate one pulse after 'count' CLK
	     cycles; output remains high until after the new countdown has
	     begun; reloading the count mid-period does not take affect
	     until after the period
	011  mode 3, square wave rate generator; generate one pulse after
	     'count' CLK cycles; output remains high until 1/2 of the next
	     countdown; it does this by decrementing by 2 until zero, at
	     which time it lowers the output signal, reloads the counter
	     and counts down again until interrupting at 0; reloading the
	     count mid-period does not take affect until after the period
	100  mode 4, software triggered strobe; countdown with output high
	     until counter zero;  at zero output goes low for one CLK
	     period;  countdown is triggered by loading counter;  reloading
	     counter takes effect on next CLK pulse
	101  mode 5, hardware triggered strobe; countdown after triggering
	     with output high until counter zero; at zero output goes low
	     for one CLK period
*/	

	#define PIT_FREQ	    0x12378E  //In Hertz (equal 1.19318 MHz)

	#define PIT_PORT_0    0x40
	#define PIT_PORT_1    0x41
	#define PIT_PORT_2    0x42
	#define PIT_MCR_PORT  0x43

	//Counter Selection Bits
	#define PIT_COUNTER_0 0x00
	#define PIT_COUNTER_1 0x40
	#define PIT_COUNTER_2 0x80

	//Read/Write/Latch Format Bits 
	#define LATCH 		0x00
	#define RW_MSB_ONLY	0x10
	#define RW_LSB_ONLY	0x20
	#define RW_LSB_MSB	0x30	

	//Counter Mode Bits
	#define MODE_0		0x0
	#define MODE_1		0x2
	#define MODE_2		0x4
	#define MODE_3		0x6
	#define MODE_4		0x8
	#define MODE_5		0x10
	
	//Counter Base Type
	#define BINARY	0x0
	#define BCD		0x1

	void pit0_init(DD num_of_times);
	void pit1_init();
	void pit2_init();

#endif