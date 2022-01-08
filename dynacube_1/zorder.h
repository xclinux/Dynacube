/***************************************************************************
                          zorder.h  -  description
                             -------------------
    begin                : Sat Jan 31 2004
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

 #ifndef __ZORDER_H
 #define __ZORDER_H

 #include "proc.h"
 #include "ktypes.h"
 #define WINDOW_MAX 10
 

    typedef struct
    {
     DW pid;
     DW window_id;
     DW task_id;
    }ZORDER;

    extern ZORDER zorder[MAX_PROC * WINDOW_MAX];
  
    extern DD z_endptr;
    
    extern DW max_gtask;

    extern DB gtask_avl[MAX_PROC * WINDOW_MAX];
   
    void z_init();
    void z_enq(DW _pid, DW _window_id, DW _task_id);
    SDB  z_remove(DW _pid, DW _window_id);
    void z_removeAll(DW _pid);
    void z_move(DW dest);
    void z_moveTop(DW _pid, DW _window_id);

    void printZ();
    SDW z_get_max();
  
 #endif
 