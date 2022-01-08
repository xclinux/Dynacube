/***************************************************************************
                          message.h  -  description
                             -------------------
    begin                : Wed Jan 21 2004
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
#ifndef __MESSAGE_H
#define __MESSAGE_H

    #include "kconst.h"
    #include "ktypes.h"
    #include "proc.h"
    #include "mm.h"
    #include "queue.h"

    #define MAX_MSG_BUF 64
    typedef struct  {
        DW from_pid;
        DW type;
        DW sub_type;
        DD length;
        DB msg_buf[MAX_MSG_BUF];        
      }MSG;
      
 extern DB _msg[MAX_PROC][MAX_Q];
// extern DD recv_addr[MAX_PROC]; 
 SDW send(DW pid,MSG *msg);
 SDW recv(MSG *msg);
 SDW ksend(DW pid, MSG *m);

#endif