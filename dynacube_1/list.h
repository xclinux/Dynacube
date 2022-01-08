/***************************************************************************
                          list.h  -  description
                             -------------------
    begin                : Fri Feb 20 2004
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

 #ifndef __LIST_H
 #define __LIST_H

// #include "kconst.h"
 #include "window.h"
 #include "component.h"
 #include "frame.h"

 #ifdef __cplusplus
   extern "C"
   {
     #include "stdlib.h"
   }
 #else
     #include "stdlib.h" 
 #endif

  #define WIND_TYPE 1
  #define FRM_TYPE  2
  #define COMP_TYPE 3
  
  void list_init();
  
  SDW ladd(DW pid, DB type, void *ptr);
  SDW lremove(DW pid, DB type, DW index);
  void lremoveAll(DW pid);
  void* lfind(DW pid, DB type, DW index); //Return read_id or -1

  void printList(DW pid, DB type);
  
 #endif