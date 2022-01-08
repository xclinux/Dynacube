/***************************************************************************
                          queue.c  -  description
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

 #include "queue.h"

  QUEUE ready_q;
  QUEUE device_q[MAX_DEVICE];
  QUEUE message_q;
  QUEUE intr_q;
  QUEUE timer_q;
  QUEUE gui_q;
  QUEUE fs_q;
  
  void q_init(QUEUE *q_ptr)
  {
    q_ptr->front = 0;
    q_ptr->end   = 0;
    q_ptr->max   = MAX_PROC;
    q_ptr->n     = 0;
  }
  
  SDW enq(QUEUE *q_ptr,DW pid)
  {
    DB i, j;
    
    for(i = q_ptr->front, j = 0 ; j < q_ptr->n ; j++)
    {
      if(q_ptr->q[i] == pid)
          return E_EXISTS;
          
      i = (i+1) % q_ptr->max;
    }
    
    if(q_ptr->n < q_ptr->max)
    {      
     q_ptr->q[q_ptr->end] = pid;
     q_ptr->end++;
     q_ptr->end %= q_ptr->max;
     q_ptr->n++;
    }
    else
      return E_OVERFLOW;    
  }
  
  SDW deq(QUEUE *q_ptr)
  {
    DW temp;
    
    if(q_ptr->n != 0)
    {
     temp = q_ptr->q[q_ptr->front];
     q_ptr->front++;
     q_ptr->front %= q_ptr->max;
     q_ptr->n--;
     enq(q_ptr,temp);
     return temp;
    }
    else
      return 0;        
  }

  SDW get_element(QUEUE *q_ptr, DW index)
  {
    if(index >= q_ptr->n)
      return E_FAILURE;
    else
    {
      return q_ptr->q[(q_ptr->front + index)%q_ptr->max];
    }
  }

  SDW get_first(QUEUE *q_ptr)
  {
    DW temp;

    if(q_ptr->n != 0)
    {
     temp = q_ptr->q[q_ptr->front];
     return temp;
    }
    return -1;
  }

  SDW remove(QUEUE *q_ptr, DW pid)
  {
   DB i, j;
   
   if(q_ptr->q[q_ptr->front] == pid && q_ptr->n > 0)
   {
     q_ptr->front = (q_ptr->front+1) % q_ptr->max;
     q_ptr->n--;
     return 0;
   }
   else
   {
    for(i = q_ptr->front, j = 0 ; j < q_ptr->n ; j++)
    {
      if(q_ptr->q[i] == pid)
      {
        for(;j < q_ptr->n-1;j++)
        {
         q_ptr->q[i] = q_ptr->q[(i+1)%q_ptr->max];
         i = (i+1) % q_ptr->max;         
        }
        q_ptr->n--;
        if(q_ptr->end != 0)
           q_ptr->end--;
        else
           q_ptr->end = q_ptr->max-1; 
        return 0;
      }
      
      i = (i+1) % q_ptr->max;
    }
   }
   
   return E_FAILURE;
  }
  
  SDW findq(QUEUE *q_ptr, DW pid)
  {
   DB i, j;

   for(i = q_ptr->front, j = 0 ; j < q_ptr->n ; j++)
    {
      if(q_ptr->q[i] == pid)
      {
        return 0;
      }
      i = (i+1) % q_ptr->max;
    }
    
    return E_FAILURE;   
  }

  void printQ(QUEUE *q_ptr)
  {
    DW i,j;

    for(i = q_ptr->front, j = 0 ; j < q_ptr->n ; j++)
    {
      if(j%10 == 0)
         printf("\n");
      printf(" %d",q_ptr->q[i]);
      i = (i+1) % q_ptr->max;      
    }    
  }
