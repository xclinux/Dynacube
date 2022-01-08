/***************************************************************************
                          client_fs.h  -  description
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
 *   (at iiyour option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __CLIENT_FS_H
#define __CLIENT_FS_H

 #include "ktypes.h"
 #include "fat12.h"
 
 #define E_DISK		  -1
 #define E_FS_NEXISTS 	  -2
 #define E_FS_EXISTS   	  -3
 #define E_FS_FNAME    	  -4
 #define E_FS_SPACE	  -5
 #define E_FS_BUSY	  -6

 #define O_RDONLY 1
 #define O_RDWR   2
 
 SDW open(char *fname,DW mode);
 SDW close(DW fd_in);
 SDW read(DW fd_in,char *buf,DW length);
 SDW write(DW fd_in,char *buf,DW length);
 SDW creat(char *fname);
 SDW opendir(char *name);
 SDW createdir(char *name);
 SDW closedir(DW dd_in);
 SDW readdir(DW dd_in,DIRENT *dir);
 SDW fs_remove(char *name);
 SDW rename(char *old_name,char *new_name);

#endif
