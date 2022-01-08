/***************************************************************************
                          zorder.c  -  description
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

 #include "zorder.h"
 

  ZORDER zorder[MAX_PROC * WINDOW_MAX];

  DD z_endptr = 0;

  DW max_gtask = 0;

  DB gtask_avl[MAX_PROC * WINDOW_MAX] = {1};


  void z_init()
  {
   DD i;

   for(i=0 ; i < MAX_PROC * WINDOW_MAX ; i++)
      zorder[i].pid = MAX_PROC;
  }

  void z_enq(DW _pid, DW _window_id,DW _task_id)
  {
    DD i;

    for(i = 0 ; i < z_endptr ; i++)
    {
      if(zorder[i].pid == _pid && zorder[i].window_id == _window_id)
      {
        return;
      }
    }

    zorder[z_endptr].pid = _pid;
    zorder[z_endptr].window_id = _window_id;
    zorder[z_endptr].task_id = _task_id;
    z_endptr++;
  }


  SDB z_remove(DW _pid, DW _window_id)
  {
    DD i;
    DB task_id;

    for(i = 0 ; i < z_endptr ; i++)
    {
      if(zorder[i].pid == _pid && zorder[i].window_id == _window_id)
      {
        gtask_avl[zorder[i].task_id] = AVL;
        task_id = zorder[i].task_id;
        z_move(i);
        return (task_id);
      }
    }

    return -1;
  }

  void z_removeAll(DW _pid)
  {
    DD i;

    for(i = 0 ; i < z_endptr ; )
    {
      if(zorder[i].pid == _pid)
      {
 //change
        gtask_avl[zorder[i].task_id] = AVL;
        z_move(i);
        i--;
      }
      i++;
    }

  }

  void z_moveTop(DW _pid, DW _window_id)
  {
    SDW task_id;
    if(zorder[z_endptr-1].pid == _pid && zorder[z_endptr-1].window_id == _window_id)
      return;
      
    if((task_id = z_remove(_pid,_window_id)) != -1)
    {
      gtask_avl[task_id] = AVL;
      z_enq(_pid,_window_id,task_id);
    }
  }


  void z_move(DW dest)
  {
    DD i;

    if(dest >= z_endptr)
      return;

    for(i = dest ; i < z_endptr-1 ; i++)
    {
      zorder[i] = zorder[i+1];
    }

    z_endptr--;
//    printf("\n ep %d ",z_endptr);
//    delay(0x5FF);
  }

  void printZ()
  {
   SDD i;

   printf("\n");
   for(i=z_endptr-1 ; i >= 0 ; i--)
      printf("\n %d %d ",zorder[i].pid,zorder[i].window_id);
  }

  SDW z_get_max()
  {
    DW *max2 = &max_gtask;
    DW max1 = MAX_PROC * WINDOW_MAX;
    DW i;
    
    if(*max2 < max1)
     {
      gtask_avl[*max2] = UNAVL;
      *max2 = *max2 + 1;
      return (*max2-1);
     }
     else
      {
       for(i = 0 ; i < max1 ; i++)
         {
          if(gtask_avl == AVL)
          {
           gtask_avl[i] = UNAVL;
           return i;
          }
         }
       if( i == max1)
        return -1;
     }   
  }
