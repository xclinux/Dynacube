/***************************************************************************
                          folderview.h  -  description
                             -------------------
    begin                : Sun Feb 8 2004
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

 #ifndef __FOLDERVIEW_H
 #define __FOLDERVIEW_H

  #ifdef __cplusplus
   extern "C"
   {
     #include "ktypes.h"
     #include "stdlib.h"
     #include "graphics.h"
     #include "string.h"
     #include "icon.h"
     #include "fat12.h"
     #include "client_fs.h"
   }
 #else
      #include "ktypes.h"
      #include "stdlib.h"
      #include "graphics.h"
      #include "string.h"
      #include "icon.h"
      #include "fat12.h"
      #include "client_fs.h"
 #endif

 #include "component.h"
 #include "window.h"
 #include "frame.h"
 #include "utility.h"
 
 #define MIN_FV_WIDTH  50
 #define MIN_FV_HEIGHT 50
 
 #define Y_OFFSET 3
 #define X_OFFSET 5

 #define FV_BASE  0xF0F0

// typedef struct
// {
//	char mm,dd;
//	int yy;
// }DATE;
//
// typedef struct
// {
//	int hour,min,second;
// }TIME;
//
// typedef struct
// {
//	char name[256];
//	char attribute;
//	DATE crt_dt;
//	TIME crt_time;
//	DATE acc_dt;
//	long clu;
//	long size;
//	DATE mod_dt;
//	TIME mod_time;
// } DIRENT;


 class folderview:public component
 {
   public :
    char dirname[1024]; //MAX PATH LENGTH

   void folderview_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_dirname);

   void paint();
   void drawFiles(DW x, DW y);
      
   void react(DW _x,DW _y);
 };
 
 #endif
