/***************************************************************************
                          hashmap.c  -  description
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

 #include "hashmap.h"
 
  PAIR win_map[MAX_PROC][WINDOW_MAX];
  PAIR frm_map[MAX_PROC][FRAME_MAX];
  PAIR comp_map[MAX_PROC][COMPONENT_MAX];

  DW win_map_max[MAX_PROC] = {0};
  DW frm_map_max[MAX_PROC] = {0};
  DW comp_map_max[MAX_PROC]= {0};

  void hash_init()
  {
    DW i, j;

    for(i = 0 ; i < MAX_PROC ; i++)
    {
      for(j = 0 ; j < WINDOW_MAX ; j++)
      {
       win_map[i][j].avl  =  AVL;
      }

      for(j = 0 ; j < FRAME_MAX ; j++)
      {
        frm_map[i][j].avl = AVL;
      }
      
      for(j = 0 ; j < COMPONENT_MAX ; j++)
      {
        comp_map[i][j].avl = AVL;
      }      
    }
    
  }
  
  SDW hadd(DW pid, DB type, DW key, DW val)
  {
   PAIR *p;
   DW max1;
   DW *max2;  
   DW i;
   
   switch(type)
   {
    case WIND_TYPE:
          max1 = WINDOW_MAX;
          max2 = &win_map_max[pid];
          p = win_map[pid];
          break;
          
    case FRM_TYPE:
          max1 = FRAME_MAX;
          max2 = &frm_map_max[pid];
          p = frm_map[pid];    
          break;
          
    case COMP_TYPE:
          max1 = COMPONENT_MAX;
          max2 = &comp_map_max[pid];
          p = comp_map[pid];    
          break;
          
    default:
          return -1;
   }

              if(*max2 < max1)
              {
                p[*max2].avl = UNAVL;
                p[*max2].key = key;
                p[*max2].val = val;
                *max2 = *max2 + 1;
                return 0;
              }
              else
              {
                for(i = 0 ; i < max1 ; i++)
                {
                 if(p[i].avl == AVL)
                 {
                  p[i].avl = UNAVL;
                  p[i].key = key;
                  p[i].val = val;
                  return 0;
                 }
                }
                
                if( i == max1)
                  return -1;
              }
    
  }
  
  SDW hremove(DW pid, DB type, DW key)
  {
   PAIR *p;
   DW *max2;
   DW i;
    
   switch(type)
   {
    case WIND_TYPE:
          max2 = &win_map_max[pid];
          p = win_map[pid];
          break;

    case FRM_TYPE:
          max2 = &frm_map_max[pid];
          p = frm_map[pid];
          break;

    case COMP_TYPE:
          max2 = &comp_map_max[pid];
          p = comp_map[pid];
          break;
   }

   for(i = 0 ; i < *max2 ; i++)
   {
     if(p[i].avl == UNAVL)
     {
       if(p[i].key == key)
       {
        p[i].avl = AVL;
        return 0;
       }
     }
   }

   return -1;    
  }
  
  SDW  hfind(DW pid, DB type, DW key) //Return read_id or -1
  {
   PAIR *p;
   DW *max2;
   DW i;
    
   switch(type)
   {
    case WIND_TYPE:
          max2 = &win_map_max[pid];
          p = win_map[pid];
          break;

    case FRM_TYPE:
          max2 = &frm_map_max[pid];
          p = frm_map[pid];
          break;

    case COMP_TYPE:
          max2 = &comp_map_max[pid];
          p = comp_map[pid];
          break;
   }

   for(i = 0 ; i < *max2 ; i++)
   {
     if(p[i].avl == UNAVL)
     {
       if(p[i].key == key)
        return p[i].val;
     }
   }
   
   return -1;
       
  }

  SDW  afind(DW pid, DB type, DW val) //Return alias_id or -1
  {
   PAIR *p;
   DW *max2;
   DW i;

   switch(type)
   {
    case WIND_TYPE:
          max2 = &win_map_max[pid];
          p = win_map[pid];
          break;

    case FRM_TYPE:
          max2 = &frm_map_max[pid];
          p = frm_map[pid];
          break;

    case COMP_TYPE:
          max2 = &comp_map_max[pid];
          p = comp_map[pid];
          break;
   }

   for(i = 0 ; i < *max2 ; i++)
   {
     if(p[i].avl == UNAVL)
     {
       if(p[i].val == val)
        return p[i].key;
     }
   }

   return -1;

  }
  
  void printHash(DW pid, DB type)
  {
    PAIR *p;
    DW *max2;
    DW i;

   printf("\n");
    
   switch(type)
   {
    case WIND_TYPE:
          max2 = &win_map_max[pid];
          p = win_map[pid];
          break;

    case FRM_TYPE:
          max2 = &frm_map_max[pid];
          p = frm_map[pid];
          break;

    case COMP_TYPE:
          max2 = &comp_map_max[pid];
          p = comp_map[pid];
          break;
   }
   
   for(i = 0 ; i < *max2 ; i++)
   {
     if(p[i].avl == UNAVL)
     {
       printf(" (%d) %d ",p[i].key,p[i].val);
     }
   }
        
  }

  void hremoveAll(DW pid)
  {
    win_map_max[pid] = 0;
    frm_map_max[pid] = 0;
    comp_map_max[pid] = 0;    
  }
  
