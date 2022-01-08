/***************************************************************************
                          keyboard.h  -  description
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

/*
====================================================================
SCANCODES FOR SCANCODE SET 1 (XT)
====================================================================
US 104-key keyboard, set 1 scancodes


"Make" code is generated when key is pressed.
"Break" code is generated when key is released.
Hex value of make code for each key is shown.

Most keys:
        one-byte make code      = nn
        one-byte repeat code    = nn
        one-byte break code     = 80h + nn

"Gray" keys (not on original 84-key keyboard):
        two-byte make code      = E0nn
        two-byte repeat code    = E0nn
        two-byte break code     = E0 followed by 80h + nn

"Gray" keys noted by [1] are NumLock-sensitive.
When the keyboard's internal NumLock is active:
        four-byte make code     = E02AE0nn
        two-byte repeat code    = E0nn
        four-byte break code    = E0 followed by 80h + nn followed by E0AA

 ____    ___________________    ___________________    ___________________
|    |  |    |    |    |    |  |    |    |    |    |  |    |    |    |    |
|Esc |  |F1  |F2  |F3  |F4  |  |F5  |F6  |F7  |F8  |  |F9  |F10 |F11 |F12 |
|    |  |    |    |    |    |  |    |    |    |    |  |    |    |    |    |
|  01|  |  3B|  3C|  3D|  3E|  |  3F|  40|  41|  42|  |  43|  44|  57|  58|
|____|  |____|____|____|____|  |____|____|____|____|  |____|____|____|____|

 __________________________________________________________________________
|    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
|~   |!   |@   |#   |$   |%   |^   |&   |*   |(   |)   |_   |+   ||   |bksp|
|`   |1   |2   |3   |4   |5   |6   |7   |8   |9   |0   |-   |=   |\   |    |
|  29|  02|  03|  04|  05|  06|  07|  08|  09|  0A|  0B|  0C|  0D|  2B|  0E|
|____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|
|    |    |    |    |    |    |    |    |    |    |    |    |    |         |
|Tab |Q   |W   |E   |R   |T   |Y   |U   |I   |O   |P   |{   |}   |         |
|    |    |    |    |    |    |    |    |    |    |    |[   |]   |         |
|  0F|  10|  11|  12|  13|  14|  15|  16|  17|  18|  19|  1A|  1B|         |
|____|____|____|____|____|____|____|____|____|____|____|____|____|         |
|    |    |    |    |    |    |    |    |    |    |    |    |              |
|Caps|A   |S   |D   |F   |G   |H   |J   |K   |L   |:   |"   |     Enter    |
|    |    |    |    |    |    |    |    |    |    |;   |'   |              |
|  3A|  1E|  1F|  20|  21|  22|  23|  24|  25|  26|  27|  28|            1C|
|____|____|____|____|____|____|____|____|____|____|____|____|______________|
|         |    |    |    |    |    |    |    |    |    |    |              |
| L Shift |Z   |X   |C   |V   |B   |N   |M   |<   |>   |?   |   R Shift    |
|         |    |    |    |    |    |    |    |,   |.   |/   |              |
|       2A|  2C|  2D|  2E|  2F|  30|  31|  32|  33|  34|  35|            36|
|_________|____|____|____|____|____|____|____|____|____|____|______________|
|       |       |       |                  |       |       |       |       |
|L Ctrl | L win | L Alt |       space      | R Alt | R win | menu  |R Ctrl |
|       |[1]    |       |                  |       |[1]    |[1]    |       |
|     1D|   E05B|     38|                39|   E038|   E05C|   E05D|   E01D|
|_______|_______|_______|__________________|_______|_______|_______|_______|


[2] For PrintScreen/SysRq key: make code = E02AE037,
repeat code = E037, break code = E0B7E0AA

[3] The Pause/Break key does not repeat, and it does not
generate a break code. Its make code is E11D45E19DC5

 ____ ____ ____
|    |    |    |
|Prt |Scrl|Paus|
|Scrn|Lock|Brk |
| [2]|  46| [3]|
|____|____|____|

 ____ ____ ____   ____ ____ ____ ____
|    |    |    | |    |    |    |    |
|Ins |Home|PgUp| |Num |/   |*   |-   |
|[1] |[1] |[1] | |Lock|    |    |    |
|E052|E047|E049| |  45|E035|  37|  4A|
|____|____|____| |____|____|____|____|
|    |    |    | |    |    |    |    |
|Del |End |PgDn| |7   |8   |9   |    |
|[1] |[1] |[1] | |Home|(U) |PgUp|    |
|E053|E04F|E051| |  47|  48|  49|    |
|____|____|____| |____|____|____|    |
                 |    |    |    |+   |
                 |4   |5   |6   |    |
                 |(L) |    |(R) |    |
                 |  4B|  4C|  4D|  4E|
      ____       |____|____|____|____|
     |    |      |    |    |    |    |
     |(U) |      |1   |2   |3   |    |
     |[1] |      |End |(D) |PgDn|    |
     |E048|      |  4F|  50|  51|Ent |
 ____|____|____  |____|____|____|    |
|    |    |    | |         |    |    |
|(L) |(D) |(R) | |0        |.   |    |
|[1] |[1] |[1] | |Ins      |Del |    |
|E04B|E050|E04D| |       52|  53|E01C|
|____|____|____| |_________|____|____|


code key        code key        code key        code key
---- ---        ---- ---        ---- ---        ---- ---
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

code key        code key        code key        code key
---- ---        ---- ---        ---- ---        ---- ---
39   Space      41   F7         49   PageUp 9   51   PageDown 3
3A   CapsLock   42   F8         4A   -          52   Insert 0
3B   F1         43   F9         4B   (left) 4   53   Del .
3C   F2         44   F10        4C   5
3D   F3         45   NumLock    4D   (right) 6  57   F11
3E   F4         46   ScrollLock 4E   +          58   F12
3F   F5         47   Home  7    4F   End 1
40   F6         48   (up) 8     50   (down) 2



code            key
----            ---
E01C            Enter (on numeric keypad)
E01D            R Ctrl
E02A            make code prefix for keyboard internal numlock
E02AE037        PrintScreen make code
E035            /
E037            PrintScreen repeat code
E038            R Alt
E047            Home
E048            (up)
E049            PageUp
E04B            (left)
E04D            (right)
E04F            End
E050            (down)
E051            PageDown
E052            Insert
E053            Del
E05B            L Win
E05C            R Win
E05D            Menu
E0AA            break code suffix for keyboard internal numlock
E0B7E0AA        PrintScreen break code
E11D45E19DC5    Pause

*/


#ifndef __KEYBOARD_H
#define __KEYBOARD_H

 #include "ktypes.h"

#define ESC 0x80
#define CTRL 0//(ESC + 1)
#define SHIFT 0 //(ESC + 2)
#define ALT   0//(ESC + 3)
#define CAPS_LOCK 0//(ESC + 4)
#define F1 (ESC+5)
#define F2 (ESC + 6)
#define F3 (ESC + 7)
#define F4 (ESC + 8)
#define F5 (ESC + 9)
#define F6 (ESC + 10)
#define F7 (ESC + 11)
#define F8 (ESC + 12)
#define F9 (ESC + 13)
#define F10 (ESC + 14)
#define F11 (ESC + 15)
#define F12 (ESC + 16)
#define NUM_LOCK (ESC + 17)
#define SCROLL_LOCK (ESC + 18)
#define HOME (ESC + 19)
#define UP (ESC + 20)
#define DOWN (ESC + 21)
#define LEFT_A (ESC + 22)
#define RIGHT_A (ESC + 23)
#define PAGE_UP (ESC + 24)
#define PAGE_DOWN (ESC + 25)
#define INS (ESC + 26)
#define DEL (ESC + 27)
#define END (ESC + 28)

#define VK_ENTER			0xA
#define VK_TAB				0x9
#define VK_BACKSPACE			0x8

#define _CTRL_PUSH   	0x1D
#define _CTRL_PULL   	0x9D
#define _SHIFT_PUSH   	0x2A
#define _SHIFT_PULL   	0xAA
#define _R_SHIFT_PUSH	0x36
#define _R_SHIFT_PULL	0xB6
#define _ALT_PUSH    	0x38
#define _ALT_PULL    	0xB8
#define _CAPS_TOGGLE 	0x3A

#define ST_SHIFT  0x1
#define ST_CAPS   (0x1<<1)
#define ST_CNTL   (0x1<<2)
#define ST_ALT    (0x1<<3)

 void handle_KBD();
 DB decode(DB);

 extern boolean _ctrl, _alt, _shift, _caps;
#endif
