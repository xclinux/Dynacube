/***************************************************************************
                          mouse.h  -  description
                             -------------------
    begin                : Fri Jan 23 2004
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

 #ifndef __MOUSE_H
 #define __MOUSE_H

  #include "ktypes.h"
  #include "kconst.h"
  #include "gui.h"
  #include "message.h"

  /*
    3 Byte Format:
    -------------
    Y overflow | X overflow | Y signbit | X signbit | Always 1  | Mid Btn | Right Btn | Left Btn
    X movement - in 2s complement
    Y movement - in 2s complement

    scaling: 0 => 1->1 i.e. 4 counts/mm
  */

  // 3 Byte Decoding info
  #define XOVR  1<<7
  #define YOVR  1<<6
  #define YSGN  1<<5
  #define XSGN  1<<4

  #define MBTN  1<<2
  #define RBTN  1<<1
  #define LBTN  1<<0

  //PS/2 Status
  #define OBF       1<<0
  #define IBF       1<<1

  #define SYS       1<<2
  #define A2        1<<3
  #define INH       1<<4
  #define MOBF      1<<5
  #define TO        1<<6
  #define PERR      1<<7

  #define INT   1<<0
  #define INT2  1<<1
  #define SYS   1<<2
  #define RESV  1<<3
  #define _EN   1<<4
  #define _EN2  1<<5
  #define XLAT  1<<6
  #define RESV2 1<<7


  // Mouse Data Info
  #define CLICK			1
  #define MOVE			1<<1
  #define DBLCLICK	1<<2 

  #define PS2_TIMEOUT 8192

  //Pseudo Functions (or) Macros
  #define readStatus() inb(0x64)

  extern DW mcurx, mcury;
  extern DB mbyte[];
  extern boolean mouse_inited;

  //Real Functions
  void mouse_init();
  void handle_mouse();
  void processData();
  void mouse_reset();
  void mouse_restore();

  DB readData();
  void writeData(DB data);
  void sendCommand(DB cmd);
  void setCmdByte(DB cmdByte);
  DB getCmdByte();
  void printStatus();

  void dump();


 #endif
