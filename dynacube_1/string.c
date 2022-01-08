/***************************************************************************
                          string.c  -  description
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
#include "ktime.h"
#include "kconst.h"
 
#include "string.h"

  
  DW strlen(const char *str)
  {
    //Function Tested @ 11:00 12/12/2003 - Frozen    
    DW len = 0;

	  while(*str++ && len < MAX_BUFFER)
	    len++;

  	return len;           
  }

  SDB strcmp(const char *str1,const char *str2)
  {
    //Function Tested @ 12:30 12/12/2003 - Frozen
    DW index = 0;
    DB ch1 = *(str1+index), ch2 = *(str2+index);

    while(ch1 && ch2)
    {
      if(ch1 != ch2)
      {
        if(ch1 > ch2)
	        return 1;
        else
	        return -1;
      }
      index++;
      ch1 = *(str1+index), ch2 = *(str2+index);
    }

    if( ch1 == '\0' && ch2 == '\0' )
    {
      return 0;
    }
    else if(ch1 == '\0')
    {
        return -1;
    }
    else
        return 1;
  }

  SDB stricmp(const char *str1,const char *str2)
  {
    //Function Tested @ 12:30 12/12/2003 - Frozen
    DW index = 0;
    DB ch1 = *(str1+index), ch2 = *(str2+index);

    while(ch1 && ch2)
    {
      if(ch1 >=65 && ch1 <= 90)
       ch1 = ch1 +32;
      if(ch2 >=65 && ch2 <= 90)
       ch2 = ch2 +32;
      if(ch1 != ch2)
      {
        if(ch1 > ch2)
	        return 1;
        else
	        return -1;
      }
      index++;
      ch1 = *(str1+index), ch2 = *(str2+index);
    }

    if( ch1 == '\0' && ch2 == '\0' )
    {
      return 0;
    }
    else if(ch1 == '\0')
    {
        return -1;
    }
    else
        return 1;
  }

  void strcpy(void *dest,const void *src)
  {
    memcpy(dest,src,strlen(src));
  }

  void strcat(void *dest,const void *src)
  {
   memcpy(dest+strlen(dest),src,strlen(src));
  }

  void* memcpy(void *dest, const void *src, size_t n)
  {
   //Function Tested @ 11:45 13/12/2003 - Got to Test a bit
   char *_dest = (char *)dest;
   const char *_src = (const char *)src;

   *_dest = *_src; //Just the first entry

   while(n)
   {
     *(_dest+n) = *(_src+n);
     n--;
   }

   return _dest;
  }

  void* kmemcpy(void *dest, const void *src, size_t n)
  {
   //Function Tested @ 11:45 13/12/2003 - Got to Test a bit
   char *_dest = (char *)dest;
   const char *_src = (const char *)src;

//   printf("\ndest %x src %x n %d",dest,src,n);
//   delay(0x5FF);
   *_dest = *_src; //Just the first entry
//   printf("\nJust the first entry");
//   delay(0x5FF);

   while(n)
   {
     *(_dest+n) = *(_src+n);
     n--;
   }

   return _dest;
  }

  void* strmncpy(void* dest,void *src,DD m, DD n)
  {
    DD i;
    i = m;
    if(m < strlen(src))
    {
     for(i = m; i < m + n ; i++)
      *(DB *)(dest + i - m) = *(DB *)(src + i);
    }
    *(DB *)(dest + i - m) = '\0';
    return dest;
  }

   void* strncpy(void* dest,void *src,DD n)
   {
    DD i;
    for(i = 0; i < n ; i++)
     *(DB *)(dest + i) = *(DB *)(src + i);

    *(DB *)(dest + i) = '\0';
    return dest;
	 }
  
  void* memset(void *dest, DB val, DD times)
  {
    DD i;
    for(i = 0 ; i < times ; i++)
    {
      *(DB *)(dest+i) = val;
    }

    return dest;
  }

 unsigned char toupper(unsigned char s)
  {
  DW i;
  if(is_lower(s))
	 {
		 return (s + 'A' - 'a');
	 }
  return s;
  }
 unsigned char tolower(unsigned char s)
  {
  DW i;
  if(is_upper(s))
	 {
		 return (s - ('A' - 'a'));
	 }
  return s;
  }
  char is_lower(unsigned char s)
   {
    if(s >= 'a' && s <= 'z')
    	return 1;
    return 0;
   }
  char is_upper(unsigned char s)
   {
    if(s >= 'A' && s <= 'Z')
    	return 1;
    return 0;
   }
   char isnum(unsigned char c)
   {
	 if(c >= '0' && c <= '9')
		 return 1;
	 else
		return 0;
   }
 unsigned char toggle_shift(unsigned char s)
 {

  char a[][2] =  {"1!","2@","3#","4$","5%","6^",
	 	"7&","8*","9(","0)","-_","=+",
		"\\|","[{","]}",";:","'\"",",<",
		".>","/?","`~"
		};
  int i;
  for(i = 0; i < 21; i++)
   if(s == a[i][0])
    return a[i][1];
  if(is_lower(s))
   return toupper(s);
  if(is_upper(s))
   return tolower(s);
  return s;
 }
