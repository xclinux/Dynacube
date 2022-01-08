/***************************************************************************
                          list.cpp  -  description
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

 #include "list.h"

 struct
 {
   DB avl;
   window *wind_ptr;
 } wind_list[MAX_PROC][WINDOW_MAX];

 struct
 {
   DB avl;
   frame *frm_ptr;
 }frm_list[MAX_PROC][FRAME_MAX];

 struct
 {
   DB avl;
   component *comp_ptr;
 } comp_list[MAX_PROC][COMPONENT_MAX];

  DW win_max[MAX_PROC] = {0};
  DW frm_max[MAX_PROC] = {0};
  DW comp_max[MAX_PROC]= {0};

  void list_init()
  {
    DW i, j;

    for(i = 0 ; i < MAX_PROC ; i++)
    {
      for(j = 0 ; j < WINDOW_MAX ; j++)
      {
       wind_list[i][j].avl  =  AVL;
      }

      for(j = 0 ; j < FRAME_MAX ; j++)
      {
        frm_list[i][j].avl = AVL;
      }

      for(j = 0 ; j < COMPONENT_MAX ; j++)
      {
        comp_list[i][j].avl = AVL;
      }
    }
  }

  SDW ladd(DW pid, DB type, void *ptr)
  {
   DW max1 = 0, *max2;
   DW i;

   switch(type)
   {
    case WIND_TYPE:
          max1 = WINDOW_MAX;
          max2 = &win_max[pid];
          
              if(*max2 < max1)
              {
                wind_list[pid][*max2].avl = UNAVL;
                wind_list[pid][*max2].wind_ptr = (window*)ptr;
                *max2 = *max2 + 1;
                return (*max2-1);
              }
              else
              {
                for(i = 0 ; i < max1 ; i++)
                {
                 if(wind_list[pid][i].avl == AVL)
                 {
                  wind_list[pid][i].avl = UNAVL;
                  wind_list[pid][i].wind_ptr = (window*)ptr;
                  return i;
                 }
                }

                if( i == max1)
                  return -1;
              }
          
          break;

    case FRM_TYPE:
          max1 = FRAME_MAX;
          max2 = &frm_max[pid];

              if(*max2 < max1)
              {
                frm_list[pid][*max2].avl = UNAVL;
                frm_list[pid][*max2].frm_ptr = (frame*)ptr;
                *max2 = *max2 + 1;
                return (*max2-1);
              }
              else
              {
                for(i = 0 ; i < max1 ; i++)
                {
                 if(frm_list[pid][i].avl == AVL)
                 {
                  frm_list[pid][i].avl = UNAVL;
                  frm_list[pid][i].frm_ptr = (frame*)ptr;
                  return i;
                 }
                }

                if( i == max1)
                  return -1;
              }

          break;

    case COMP_TYPE:
          max1 = COMPONENT_MAX;
          max2 = &comp_max[pid];

              if(*max2 < max1)
              {
                comp_list[pid][*max2].avl = UNAVL;
                comp_list[pid][*max2].comp_ptr = (component*)ptr;
                *max2 = *max2 + 1;
                return (*max2-1);                
              }
              else
              {
                for(i = 0 ; i < max1 ; i++)
                {
                 if(comp_list[pid][i].avl == AVL)
                 {
                  comp_list[pid][i].avl = UNAVL;
                  comp_list[pid][i].comp_ptr = (component*)ptr;
                  return i;
                 }
                }

                if( i == max1)
                  return -1;
              }
          break;

    default:
          return -1;          
   }
   
  }

  SDW lremove(DW pid, DB type, DW index)
  {
   switch(type)
   {
    case WIND_TYPE:
          if(wind_list[pid][index].avl == UNAVL)
          {
            wind_list[pid][index].avl = AVL;
            return 0;
          }
          else
            return -1;
          break;

    case FRM_TYPE:
          if(frm_list[pid][index].avl == UNAVL)
          {
            frm_list[pid][index].avl = AVL;
            return 0;
          }
          else
            return -1;
          break;

    case COMP_TYPE:
          if(comp_list[pid][index].avl == UNAVL)
          {
            comp_list[pid][index].avl = AVL;
            return 0;
          }
          else
            return -1;
          break;

    default:
          return -1;
   }
  }

  void lremoveAll(DW pid)
  {
    DW j;

      for(j = 0 ; j < WINDOW_MAX ; j++)
      {
//change      
       if(wind_list[pid][j].avl == UNAVL)
        {
        wind_list[pid][j].wind_ptr->freeAll();
        free((void *)wind_list[pid][j].wind_ptr);
	}
       wind_list[pid][j].avl  =  AVL;
      }
      win_max[pid] = 0;

      for(j = 0 ; j < FRAME_MAX ; j++)
      {
        frm_list[pid][j].avl = AVL;
      }
      frm_max[pid] = 0;

      for(j = 0 ; j < COMPONENT_MAX ; j++)
      {
        comp_list[pid][j].avl = AVL;
      }
      comp_max[pid] = 0;
  }

  void* lfind(DW pid, DB type, DW index) //Return read_id or -1
  {
   switch(type)
   {
    case WIND_TYPE:
          if(wind_list[pid][index].avl == UNAVL)
            return (void *)wind_list[pid][index].wind_ptr;
          else
            return NULL;
          break;

    case FRM_TYPE:
          if(frm_list[pid][index].avl == UNAVL)
            return (void *)frm_list[pid][index].frm_ptr;
          else
            return NULL;
          break;

    case COMP_TYPE:
          if(comp_list[pid][index].avl == UNAVL)
            return (void *)comp_list[pid][index].comp_ptr;
          else
            return NULL;
          break;

    default:
          return NULL;
   }    
  }


  void printList(DW pid, DB type)
  {
   DW i;

   printf("\n PID %d type %d",pid,type);
   
   switch(type)
   {
    case WIND_TYPE:
          for(i = 0 ; i < win_max[pid] ; i++)
          {
            if(wind_list[pid][i].avl == UNAVL)
            {
              printf("\n (%d) ptr= %x ",i,wind_list[pid][i].wind_ptr);
            }            
          }
          break;

    case FRM_TYPE:
          for(i = 0 ; i < frm_max[pid] ; i++)
          {
            if(frm_list[pid][i].avl == UNAVL)
            {
              printf("\n (%d) ptr= %x ",i,frm_list[pid][i].frm_ptr);
            }
          }
          break;

    case COMP_TYPE:
          for(i = 0 ; i < comp_max[pid] ; i++)
          {
            if(comp_list[pid][i].avl == UNAVL)
            {
              printf("\n (%d) ptr= %x ",i,comp_list[pid][i].comp_ptr);
            }
          }
          break;

    default:
          return;
   }
    
  }
