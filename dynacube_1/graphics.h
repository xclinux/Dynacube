/***************************************************************************
                          graphics.h  -  description
                             -------------------

    begin                : Mon Feb 16 2004
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


 #ifndef __GRAPHICS_H
 #define __GRAPHICS_H

 #include "stdlib.h"
 #include "ktypes.h"
 #include "font.h"
 #include "gui.h"
 #include "mouse.h"

 #define LIGHT_COLOR  0xFFFF //WHITE
 #define DARK_COLOR   0xABCD

 #define DEFAULT_EMBOSS_SIZE  2
 #define TOP    1<<0
 #define LEFT   1<<1
 #define BOTTOM 1<<2
 #define RIGHT  1<<3
 
// #define chkGraphicsInited()  (xRes != 0 && yRes != 0 && bpp != 0 && svgabuf != 0)
 #define chkGraphicsInited()  (graphics)
 #define normalize(x,y) x=abs(x); y=abs(y); x %= xRes; x *= (bpp/8); y %= yRes; y *= (bpp/8);
  
  extern DW xRes, yRes, bpp; //bpp = Bits Per Pixel
  extern boolean graphics;
  
  extern DW svga_buf[] __attribute__((aligned (_4KB)));   //600*800
  extern DD svgabuf;  //DBLBUffer
  extern DD physvgabuf; //pointer to mode_info.PhyAddrBase

  typedef DW COLOR;
  extern COLOR mouseimg[16][16];
    
  void initgraphics(DW _xRes, DW _yRes, DW _bpp, DD _svgabuf);
  void setScreen(COLOR c);
  void drawChar(DW x, DW y, DW index);
  
  //Generic Dynacube Drawing routines
  void setPixel(DW x, DW y, COLOR c);
  COLOR getPixel(DW x, DW y);

  void drawChar(DW x, DW y, DW index);
  void drawstring(DW x,DW y,char *title);
  void drawMousePtr(DW x,DW y);
  
  void rect(DW x, DW y, DW width, DW height);
  void charrect(DW x,DW y,DW width,DW height,DB ch);
  void fillrect(DW x,DW y,DW width,DW height,COLOR fill);
  
  void restoreImage(DW x, DW y);
  void getimage(DW x, DW y,DW width, DW height, COLOR *buffer);
  void putimage(DW x, DW y,DW width, DW height, COLOR *buffer);

  void mvBuf2Svga();
  void mvMini2Svga(DW _x, DW _y, DW _width, DW _height);
   
  void line(SDW x0, SDW y0, SDW x1, SDW y1, COLOR color);
  void push3D(DW x, DW y, DW width, DW height);
  void emboss3D(DW x, DW y, DW width, DW height,DB flags,boolean in_or_out, DB emboss_size);

  boolean iswithin(DW x,DW y,DW stx,DW sty,DW width,DW height);
  void cprint(DW x,DW y,char *title,COLOR c);
 
 #endif
