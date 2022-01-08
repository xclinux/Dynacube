/***************************************************************************
                          hashmap.h  -  description
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


 #ifndef __HASHMAP_H
 #define __HASHMAP_H

  #include "ktypes.h"
  #include "kconst.h"

  #define WIND_TYPE 1
  #define FRM_TYPE  2
  #define COMP_TYPE 3

  typedef struct
  {
    DB avl;
    DW key; //alias_id
    DW val; //real id
  } PAIR;

  extern PAIR win_map[MAX_PROC][WINDOW_MAX];
  extern PAIR frm_map[MAX_PROC][FRAME_MAX];
  extern PAIR comp_map[MAX_PROC][COMPONENT_MAX];

  extern DW win_map_max[MAX_PROC];
  extern DW frm_map_max[MAX_PROC];
  extern DW comp_map_max[MAX_PROC];

  void hash_init();
  
  SDW hadd(DW pid, DB type, DW key, DW val);
  SDW hremove(DW pid, DB type, DW key);
  void hremoveAll(DW pid);
  SDW hfind(DW pid, DB type, DW key); //Return read_id or -1
  SDW  afind(DW pid, DB type, DW val); //Return alias_id or -1

  void printHash(DW pid, DB type);

 #endif