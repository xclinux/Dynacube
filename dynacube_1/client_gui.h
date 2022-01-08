/***************************************************************************
                          client_gui.h  -  description
                             -------------------
    begin                : Fri Feb 27 2004
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

#ifndef __CLIENT_GUI_H
#define __CLIENT_GUI_H

  #define GUI_PID 1
  #define W_MINIMIZE  0x2
  #define W_MAXIMIZE  0x4
  #define W_DISABLED  0x8
  #define W_NORESIZE  0x10

  #define DISABLED  1

  #define NO_TYPE   0
  #define WIND_TYPE 1
  #define FRM_TYPE  2
  #define COMP_TYPE 3


 #define BUT_TYPE        1
 #define TEXT_TYPE       2
 #define TEXTAREA_TYPE   3
 #define LABEL_TYPE      4
 #define SCROLLBAR       5
 #define MENU_TYPE			 6

  #define CREATE  0x0
  #define ADD     0x1
  #define SHOW    0x2
  #define HIDE    0x3
  #define RESIZE  0x4
  #define ENABLE  0x5
  #define DISABLE 0x6
  #define DESTROY 0x7
  //Kernel & DD's
  #define ACTION  0x8

  //To send FINISHED message to the GUI Server after completing an event
  #define FINISHED 0x9

  //TEXT and TEXTAREA
  #define SET	  0x10
  #define GET 	  0x11
  #define CUT	  0x12
  #define COPY    0x13
  #define PASTE   0x14


 // SubType
  #define WINDOW      0x0
  #define BUTTON      0x1
  #define TEXT        0x2
  #define TEXTAREA    0x3
  #define LIST        0x4
  #define HSCROLLBAR  0x5
  #define VSCROLLBAR  0x6
  #define CHECKBOX    0x7
  #define RADIOBUTTON 0x8
  #define MENU        0x9
  #define TOOLBAR     0xA
  #define FRAME       0xB
  #define ICON        0xC
  #define LABEL       0xD
  #define FOLDERVIEW  0xE
  #define DIALOG      0xF


  #define WM_DESTROY  0x1
  #define WM_CLICKED  0x2
  #define WM_KEYPRESS 0x3

  #define FINISHED 0x9
  #define MAX_MSG_BUF 64
    typedef struct  {
        DW from_pid;
        DW type;
        DW sub_type;
        DD length;
        volatile DB msg_buf[MAX_MSG_BUF];
      }MSG;

   typedef struct
  {
    DD cntr_id;
    DW x, y;
    DW width, height;
    DD style;
    DW alias_id; //To send info to client
    char title[15];
  } CREATE_INFO;

  typedef struct
  {
    DD cntr_id;
    DW cnt_type;
    DW x, y;
    DW width, height;
    DD style;
    DW alias_id; //To send info to client
    char label[40];
  } COMP_CREATE_INFO;

  typedef struct
  {
    DW alias_id; //To send info to client
    DW x, y;
    DW width, height;
  } RESIZE_INFO;


  //Menu GUI
  #define MN_MAX_CHAR 10
  #define MN_MAX_ITEM 10
  #define MB_MAX_CHAR	10
  #define MB_MAX_MENU	6

  /*
	typedef struct
	{
		char lbl[MN_MAX_CHAR];
		DB cmdCode; //To be sent to the client
	} _MENUITEM;

  typedef struct
  {
		DB no_item;
		_MENUITEM mnuitem[MN_MAX_ITEM];
	} _MENU;

  typedef struct 
  {
   	DB no_menu;
	  struct
	  {
     char label[MB_MAX_CHAR];
     _MENU *menu_ptr;
	  }mnu[MB_MAX_MENU];
	  
  } _MENUBAR; */

#endif
