/***************************************************************************
                          gui_common.h  -  description
                             -------------------
    begin                : Sat Feb 28 2004
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

 #ifndef __GUI_COMMON_H
 #define __GUI_COMMON_H

  #include "ktypes.h"

  #define TOTAL_WIDTH  800
  #define TOTAL_HEIGHT 600

  #define TASKBAR_HEIGHT 30
  #define TASKBAR_WIDTH  TOTAL_WIDTH

  #define START_X       5
  #define START_Y       2
  #define START_WIDTH   75
  #define START_HEIGHT  26

  #define TIME_X       5
  #define TIME_Y       2
  #define TIME_WIDTH   110
  #define TIME_HEIGHT  26

  #define TASKBAR_COLOR   0xFED4
  #define TASK_AC_COLOR   0xE5F1
  #define TASK_INAC_COLOR 0xF52D //0xBC4D

  #define ACTIVE_WINDOW  0xB577
  
  #define SCREEN_WIDTH   TOTAL_WIDTH
  #define SCREEN_HEIGHT  (TOTAL_HEIGHT - TASKBAR_HEIGHT)
  #define SCREEN_COLOR   0xAE1F//0xFF1F //0F
 
  typedef struct
  {
    DW type;    // window , frame , specific component types
    DW alias_id;
    DW id;
    DW pid;
  } ENTITY;

  typedef struct
  {
    DW x;
    DW y;    
  } POINT;

  #define MN_MAX_CHAR 10
  #define MN_MAX_ITEM 10

	typedef struct
	{
		char lbl[MN_MAX_CHAR];
		DW cmdCode; //To be sent to the client
	} MENUITEM;

#endif
