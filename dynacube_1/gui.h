/***************************************************************************
                          gui.h  -  description
                             -------------------
    begin                : Wed Jan 28 2004
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

 #ifndef __GUI_H
 #define __GUI_H


 #ifdef __cplusplus
   extern "C"
   {
    #include "kasm.h"     
    #include "message.h"
    #include "kstdio.h"
    #include "zorder.h"
    #include "ktime.h"
    #include "kconst.h"
    #include "hashmap.h"
    #include "stdlib.h"
//    #include "client_gui.h"
    #include "gui_common.h"
   }
 #else
   #include "kasm.h" 
   #include "message.h"
   #include "kstdio.h"
   #include "zorder.h"
   #include "kconst.h"
   #include "ktime.h"   
   #include "hashmap.h"
   #include "stdlib.h"
//   #include "client_gui.h"
   #include "gui_common.h"
 #endif

  #define WM_DESTROY  0x1
  #define WM_CLICKED  0x2
  #define WM_KEYPRESS 0x3

 // Main Types
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

  #define MOUSE       0x10
  #define KBD         0x11


  #define ALIAS_MAX     WINDOW_MAX+FRAME_MAX+COMPONENT_MAX

  //Styles
  //Common to all
  #define HIDDEN   0x1

  //For Windows

  #define W_MINIMIZE  0x2
  #define W_MAXIMIZE  0x4
  #define W_DISABLED  0x8
  #define W_NORESIZE  0x10

  #define NO_TYPE   0
  #define WIND_TYPE 1
  #define FRM_TYPE  2
  #define COMP_TYPE 3

  #define MENU_TYPE	6
//Structs for type-casting Buffer of msgs
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

 void runGUI();

 SDW processMessage(MSG *msg);

 SDW processCreate(MSG *msg);
 SDW processShow(MSG *msg);
 SDW processHide(MSG *msg);
 SDW processResize(MSG *msg);

 SDW processDestroy(MSG *msg);

 SDW processDisable(MSG *msg);
 SDW processEnable(MSG *msg);
 SDW processMouse(MSG *msg);
 SDW processKBD(MSG *msg);
 SDW processSet(MSG *msg);
 SDW processGet(MSG *msg);
 SDW processPaste(MSG *msg);
 SDW processCopy(MSG *msg);
 SDW processCut(MSG *msg);
 ENTITY findEntity(DW x,DW y);


 void repaint();
 void drawDesktop();
 void drawTaskbar();
 SDB processStartMenu(DW x,DW y);
 void draw_time(DB flush);
 void destroy_win(DW pid);

 void sys_init_info();
 
 #endif
