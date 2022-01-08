/***************************************************************************
                          string.h  -  description
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

 #ifndef __STRING_H
 #define __STRING_H

   #include "ktypes.h"
   #define MAX_BUFFER 0x2000


   DW strlen(const char *);                 //unsigned result
   SDB strcmp(const char *,const char *);   // 1 0 -1 KR add stricmp
   SDB stricmp(const char *,const char *);
   void strcpy(void *dest,const void *src);
   void strcat(void *dest,const void *src);

   void* memcpy(void *dest, const void *src, size_t n);
	 void* kmemcpy(void *dest, const void *src, size_t n);
   void* memset(void *dest, DB val, DD times);
   void* strmncpy(void* dest,void *src,DD m, DD n);
   void* strncpy(void* dest,void *src,DD n);   
   unsigned char toupper(unsigned char s);
   unsigned char tolower(unsigned char s);
   char is_lower(unsigned char s);
   char is_upper(unsigned char s);
   char isnum(unsigned char c);
   unsigned char toggle_shift(unsigned char s);

 #endif
