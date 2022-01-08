/***************************************************************************
                          queue.h  -  description
                             -------------------
    begin                : Wed Jan 14 2004
    copyright            : (C) 2004 by Dynacube Team
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

 #ifndef __QUEUE_H
 #define __QUEUE_H

  #include "ktypes.h"
  #include "proc.h"
  #include "kconst.h"
  
  #define E_UNDERFLOW -1
  #define E_OVERFLOW  -1
  #define E_EXISTS    -1
  #define E_FAILURE   -1

  typedef struct
  {
    DW front;
    DW end;
    DW q[MAX_PROC];
    DW max; //MAX_PROC
    DW n; //Current member count
  } QUEUE;

  extern QUEUE ready_q;
  extern QUEUE device_q[MAX_DEVICE];
  extern QUEUE message_q;
  extern QUEUE intr_q;
  extern QUEUE timer_q;
  extern QUEUE gui_q;
  extern QUEUE fs_q;
    
  void q_init(QUEUE *q_ptr);
  SDW enq(QUEUE *q_ptr,DW pid);
  SDW deq(QUEUE *q_ptr);
  SDW remove(QUEUE *q_ptr, DW pid);
  SDW findq(QUEUE *q_ptr, DW pid);
  void printQ(QUEUE *q_ptr);
  SDW get_first(QUEUE *q_ptr);

 #endif