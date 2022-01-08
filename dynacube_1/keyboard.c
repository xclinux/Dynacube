/***************************************************************************
                          keyboard.c  -  description
                             -------------------
    begin                : Fri Dec 26 2003
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
#include "keyboard.h"
#include "ktypes.h"
#include "kio.h"
#include "kstdio.h"
#include "kint.h"
#include "string.h"

/*
01   Esc        0F   Tab        1D   L Ctrl     2B   \|
02   1!         10   Q          1E   A          2C   Z
03   2"         11   W          1F   S          2D   X
04   3#         12   E          20   D          2E   C
05   4$         13   R          21   F          2F   V
06   5%         14   T          22   G          30   B
07   6^         15   Y          23   H          31   N
08   7&         16   U          24   J          32   M
09   8*         17   I          25   K          33   ,<
0A   9(         18   O          26   L          34   .>
0B   0)         19   P          27   ;:         35   /?
0C   -_         1A   [{         28   '"         36   R Shift
0D   =+         1B   ]}         29   `~         37   *
0E   BackSpace  1C   Enter      2A   L Shift    38   L Alt

39   Space      41   F7         49   PageUp 9   51   PageDown 3
3A   CapsLock   42   F8         4A   -          52   Insert 0
3B   F1         43   F9         4B   (left) 4   53   Del .
3C   F2         44   F10        4C   5
3D   F3         45   NumLock    4D   (right) 6  57   F11
3E   F4         46   ScrollLock 4E   +          58   F12
3F   F5         47   Home  7    4F   End 1
40   F6         48   (up) 8     50   (down) 2

*/

 boolean _ctrl = _false, _alt = _false, _shift = _false, _caps = _false;

 // This Handler will evolve into a buffering method and the remaining
 // code will be stripped from it to make a shell
 boolean make = _true;

 void handle_KBD()
 {
  DB scan, ch, i;
  MSG mymsg;
  static DW state;
  static DW prev;

//  rect(500,200,100,300);

  scan = readData();
//  printf("\n KBD mouse : %x %d",scan,scan);

//  while(inb(0x64) & 0x1)
//  {
//   readData();
//  }

	ch = decode(scan);

//  printf("\n KSEND CALLED ");

	switch(scan)
	{
		case _CTRL_PUSH:
//      fillrect(200,200,100,50,0xFFFF);
//      ginfo(200,200,"CNTL PUSH");
			_ctrl = _true;
		       state |= ST_CNTL;
			break;

		case _CTRL_PULL:
//      fillrect(200,200,100,50,0xFFFF);
//      ginfo(200,200,"CNTL PULL");
			_ctrl = _false;
      			state &= ~ST_CNTL;
			break;

		case _ALT_PUSH:
      			state |= ST_ALT;
			_alt = _true;
			break;

		case _ALT_PULL:
      			state &= ~ST_ALT;
			_alt = _false;
			break;

		case _SHIFT_PUSH:
      			state |= ST_SHIFT;
			_shift = _true;
			break;
		case _R_SHIFT_PUSH :
			state |= ST_SHIFT;
			_shift = _true;
			break;

		case _SHIFT_PULL:
			if(prev != 0xE0)
			{
      			state &= ~ST_SHIFT;
			_shift = _false;
			}
			break;
		case _R_SHIFT_PULL:
			if(prev != 0xE0)
			{
      			state &= ~ST_SHIFT;
			_shift = _false;
			}
			break;
		case _CAPS_TOGGLE:
			_caps = !_caps;
			break;

		default:
			break;
	}

  if(ch == DEL && _ctrl == _true && _alt == _true)
  {
    //Call Sys_Sync to Sync the System
    //Then lidt(SomeLoc);
    ginfo(40,200,"RESTART");
    lidt((IDT*)0x0);
  }

//	if(ch < ESC)
//	{
			//printf("%x\n",ch);
			switch(ch)
			{
				case 0:
					break;
//				case VK_ENTER:
//				  	printf("\n");
//					break;
				case VK_TAB:
				  	printf("\t");
					break;
//				case VK_BACKSPACE:
//					break;

				default:

  mymsg.type     = ACTION;
  mymsg.sub_type = KBD;
  mymsg.length   = 6;


  if(_caps)
  	state |=  ST_CAPS;
  else
  	state &= ~ST_CAPS;


  *((DW*)mymsg.msg_buf) = state;
  *((DW*)mymsg.msg_buf+1) = ch;
  //printf("%c",ch);


//  if(make == _true)
//  {
    if(ksend(GUI_PID,&mymsg) == -1)
      panic("from mouse message overflow");
//    charrect(400,70,20,20,ch+(_shift?-32:0));
//    mvMini2Svga(400,70,20,20);

//    make = _false;
//  }
//  else
//  {
//    make = _true;
//  }

//          rect(300,200,50,50);
//          drawChar(300,200,ch+(_shift?-32:0));
//					putch(ch+(_shift?-32:0));
					break;

			}
//  }

  updateCursor();
  prev = scan;
  eoi();
 }

  DB decode(DB in)
  {
			DB map[] = {
			         /* 00 */ 0,ESC,'1','2','3','4','5','6','7','8',  						    \
	             /* 0A */ '9','0','-','=','\b','\t','q','w','e','r',  						\
	             /* 14 */ 't','y','u','i','o','p','[',']','\n',CTRL,  						\
	             /* 1E */ 'a','s','d','f','g','h','j','k','l',';',    						\
	             /* 28 */ '\'','`',SHIFT,'\\','z','x','c','v','b','n',            \
	             /* 32 */ 'm',',','.','/',SHIFT,'*',ALT,' ',CAPS_LOCK,F1,         \
	             /* 3c */  F2,F3,F4,F5,F6,F7,F8,F9,F10,NUM_LOCK,                  \
	             /* 46 */ SCROLL_LOCK,HOME,UP,PAGE_UP,'-',LEFT_A,'5',RIGHT_A,'+',END, \
	             /* 50 */  DOWN,PAGE_DOWN,INS,DEL,0,0,0,F11,F12};

	    if(in > 0x80)
	      return 0;
	    if(in >= (sizeof(map) / sizeof(map[0])))
	       return 0;
	    return map[in];
	}
