/***************************************************************************
                          stdlib.c  -  description
                             -------------------
    begin                : Sat Dec 13 2003
    copyright            : (C) 2003 by Dynacube Team
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
 
 #include "ktypes.h"
 #include "kconst.h"
 #include "kstdio.h"

 #include "stdlib.h"
 
 char* itoa(DD num,DB base)
 {
  DB* ptr_num = NULL;
  DB _num[32] = {0}, temp;
  DW index = 0, i = 0, val;

  do
  {
    val = num%base;

    if(val >= 10)
    {
     //Works only for Hex
     _num[index++] = 'F'-(base-val-1);
    }
    else
    {
     _num[index++] = '0'+val;
    }

    num/=base;

  }while(num);


  switch(base)
  {
   case 16:
  	base = 8;
   	break;
    
   case 2:
  	base = 32;
  	break;
   
   case 10: //For Decimal
    base = 0; //Don't want zeroes
  	break;
   
   default:
//change	
//   	kprint("\nBase not known\tFile Name : \t");
//  	kprint(__FILE__);
  	return NULL;
   	break; //Useless but just for safety
  }

  while(index < base)
  {
   _num[index++] = '0';
  }

  index--;

  i = 0;

  while(i <= (int)(index/2))
  {
   temp = _num[i];
   _num[i] = _num[index-i];
   _num[index-i] = temp;
   i++;
  }

  index++;

  _num[index] = '\0';

  ptr_num = &_num[0];
  return ptr_num;
 }

 SDD atoi(char *num)
  {
    SDD no;
    DW i;
    no = 0;
    i = 0;
    if(num[0] == '-')
     {
      i++;
     }
    for(;i<strlen(num);i++)
     {
      if(!isnum(num[i]))
        return 0;
      no = no * 10 + num[i] - '0';
     }
     if(num[0] == '-')
     {
      no = no * -1;
     }
    return no;
  }
 DD abs(SDD num)
 {
   if(num >= 0) return num;
   else return -num;
 }

