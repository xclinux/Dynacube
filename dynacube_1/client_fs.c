/***************************************************************************
                          client_fs.c  -  description
                             -------------------
    begin                : Sun Feb 8 2004
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
 #include "client_fs.h"

 SDW open(char *fname,DW mode)
 {
   SDD res;
  __asm__ __volatile__("pushl %%eax"::"a"(mode));
  __asm__ __volatile__("pushl %%eax"::"a"(fname));
  __asm__ __volatile__("int $0x30"::"a"(13));
  __asm__ __volatile__("popl %ebx");
  __asm__ __volatile__("popl %ebx");
  __asm__ __volatile__("pushl %eax");
  __asm__ __volatile__("popl %0":"=r"(res));
  return res;
 }

 SDW close(DW fd_in)
 {
      SDD res;
     __asm__ __volatile__("pushl %%eax"::"a"(fd_in));
     __asm__ __volatile__("int $0x30"::"a"(14));
     __asm__ __volatile__("popl %ebx");
     __asm__ __volatile__("pushl %eax");
     __asm__ __volatile__("popl %0":"=r"(res));
    return res;

 }

  SDW read(DW fd_in,char *buf,DW length)
  {
     SDD res;
     __asm__ __volatile__("pushl %%eax"::"a"(length));
     __asm__ __volatile__("pushl %%eax"::"a"(buf));
     __asm__ __volatile__("pushl %%eax"::"a"(fd_in));
     __asm__ __volatile__("int $0x30"::"a"(15));
     __asm__ __volatile__("popl %ebx");
     __asm__ __volatile__("popl %ebx");
     __asm__ __volatile__("popl %ebx");
     __asm__ __volatile__("pushl %eax");
     __asm__ __volatile__("popl %0":"=r"(res));
     return res;
  }

 SDW write(DW fd_in,char *buf,DW length)
 {
   SDD res;
    __asm__ __volatile__("pushl %%eax"::"a"(length));
    __asm__ __volatile__("pushl %%eax"::"a"(buf));
    __asm__ __volatile__("pushl %%eax"::"a"(fd_in));

    __asm__ __volatile__("int $0x30"::"a"(16));

    __asm__ __volatile__("popl %ebx");
    __asm__ __volatile__("popl %ebx");
    __asm__ __volatile__("popl %ebx");

     __asm__ __volatile__("pushl %eax");
     __asm__ __volatile__("popl %0":"=r"(res));
     return res;

 }

 SDW creat(char *fname)
 {
    SDD res;
   __asm__ __volatile__("pushl %%eax"::"a"(fname));
   __asm__ __volatile__("int $0x30"::"a"(17));
   __asm__ __volatile__("popl %ebx");

   __asm__ __volatile__("pushl %eax");
   __asm__ __volatile__("popl %0"::"r"(res));
   return res;

 }

  SDW opendir(char *name)
  {
   SDD res;
    __asm__ __volatile__("pushl %%eax"::"a"(name));
    __asm__ __volatile__("int $0x30"::"a"(18));
    __asm__ __volatile__("popl %ebx");

    __asm__ __volatile__("pushl %eax");
    __asm__ __volatile__("popl %0":"=r"(res));
    return res;
  }

 SDW createdir(char *name)
 {
    SDD res;
    __asm__ __volatile__("pushl %%eax"::"a"(name));
    __asm__ __volatile__("int $0x30"::"a"(19));
    __asm__ __volatile__("popl %ebx");

     __asm__ __volatile__("pushl %eax");
     __asm__ __volatile__("popl %0":"=r"(res));
     return res;
 }

 SDW closedir(DW dd_in)
 {
   SDD res;
   __asm__ __volatile__("pushl %%eax"::"a"(dd_in));
   __asm__ __volatile__("int $0x30"::"a"(20));
   __asm__ __volatile__("popl %ebx");

   __asm__ __volatile__("pushl %eax");
   __asm__ __volatile__("popl %0":"=r"(res));
   return res;
 }

 SDW readdir(DW dd_in,DIRENT *dir)
 {
    SDD res;
   __asm__ __volatile__("pushl %%eax"::"a"(dir));
   __asm__ __volatile__("pushl %%eax"::"a"(dd_in));
   __asm__ __volatile__("int $0x30"::"a"(21));
   __asm__ __volatile__("popl %ebx");
   __asm__ __volatile__("popl %ebx");

   __asm__ __volatile__("pushl %eax");
   __asm__ __volatile__("popl %0":"=r"(res));
   return res;
 }

 SDW fs_remove(char *name)
 {
   SDD res;
    __asm__ __volatile__("pushl %%eax"::"a"(name));
    __asm__ __volatile__("int $0x30"::"a"(22));
    __asm__ __volatile__("popl %ebx");

   __asm__ __volatile__("pushl %eax");
   __asm__ __volatile__("popl %0":"=r"(res));
   return res;
 }


 SDW rename(char *old_name,char *new_name)
 {
   SDD res;
   __asm__ __volatile__("pushl %%eax"::"a"(new_name));
   __asm__ __volatile__("pushl %%eax"::"a"(old_name));
   __asm__ __volatile__("int $0x30"::"a"(23));
   __asm__ __volatile__("popl %ebx");
   __asm__ __volatile__("popl %ebx");

   __asm__ __volatile__("pushl %eax");
   __asm__ __volatile__("popl %0":"=r"(res));
   return res;
 }


