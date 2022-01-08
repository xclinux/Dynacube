/***************************************************************************
                          svga.h  -  description
                             -------------------
    begin                : Sat Feb 7 2004
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


 #ifndef __SVGA_H
 #define __SVGA_H

 #include "ktypes.h"
 #include "kconst.h"
 #include "kasm.h"

 typedef struct
 {
	DB VbeSignature[4];
	DW VbeVersion;
	DD OemStringPtr;
	DB Capabilities[4];
	DD VideoModePtr;
	DW TotalMemory;
	DW OemSoftwareRev;
	DD OemVendorNamePtr;
	DD OemProductNamePtr;
	DD OemProductRevPtr;
	DB Reserved[222];
	DB OemData[256];
 } VBEINFO;

 typedef struct {
  short   ModeAttributes  ;         /* Mode attributes                  */
  char    WinAAttributes  ;         /* Window A attributes              */
  char    WinBAttributes  ;         /* Window B attributes              */
  short   WinGranularity  ;         /* Window granularity in k          */
  short   WinSize  ;                /* Window size in k                 */
  short   WinASegment  ;            /* Window A segment                 */
  short   WinBSegment  ;            /* Window B segment                 */
  void    *WinFuncPtr  ;            /* Pointer to window function       */
  short   BytesPerScanLine  ;       /* Bytes per scanline               */
  short   XResolution  ;            /* Horizontal resolution            */
  short   YResolution  ;            /* Vertical resolution              */
  char    XCharSize  ;              /* Character cell width             */
  char    YCharSize  ;              /* Character cell height            */
  char    NumberOfPlanes  ;         /* Number of memory planes          */
  char    BitsPerPixel  ;           /* Bits per pixel                   */
  char    NumberOfBanks  ;          /* Number of CGA style banks        */
  char    MemoryModel  ;            /* Memory model type                */
  char    BankSize  ;               /* Size of CGA style banks          */
  char    NumberOfImagePages  ;     /* Number of images pages           */
  char    res1  ;                   /* Reserved                         */
  char    RedMaskSize  ;            /* Size of direct color red mask    */
  char    RedFieldPosition  ;       /* Bit posn of lsb of red mask      */
  char    GreenMaskSize  ;          /* Size of direct color green mask  */
  char    GreenFieldPosition  ;     /* Bit posn of lsb of green mask    */
  char    BlueMaskSize  ;           /* Size of direct color blue mask   */
  char    BlueFieldPosition  ;      /* Bit posn of lsb of blue mask     */
  char    RsvdMaskSize  ;           /* Size of direct color res mask    */
  char    RsvdFieldPosition  ;      /* Bit posn of lsb of res mask      */
  char    DirectColorModeInfo  ;    /* Direct color mode attributes     */

  /* VESA 2.0 variables */
  long    PhysBasePtr;           /* physical address for flat frame buffer */
  long    OffScreenMemOffset;		 /* pointer to start of off screen memory */
  short   OffScreenMemSize;	 /* amount of off screen memory in 1k units */
  char    res2[206]  ;              /* Pad to 256 byte block size       */
}VBE_ModeInfo;

  extern VBEINFO* VbeInfoBlock;
  extern VBE_ModeInfo vbe_mode;
  extern DB vgabios_buffer[0x8000]; //32Kb
  extern DB svga_stack[1024];

  extern DB BIOSData[0x600];

  
 void PMID_detect();
 void VBE_getmodeinfo(unsigned short mode, VBE_ModeInfo *modeinfo);
  int init_mode(unsigned short mode);
  void setbank(int bank);
  void putpixel(short x, short y, char c); /* for 8 bit, 256 color modes */
 
 #endif