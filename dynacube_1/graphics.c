/***************************************************************************
                          graphics.c  -  description
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

 #include "graphics.h"
  DW svga_buf[600*800] __attribute__((aligned (_4KB))); //600*800

  DW xRes = 0, yRes = 0, bpp = 0; //bpp = Bits Per Pixel
  DD svgabuf = (DD)&svga_buf[0]; 
  DD physvgabuf = 0; //pointer to mode_info.PhyAddrBase

  boolean graphics = _false;
  
  COLOR mouseimg[16][16];
 
  void initgraphics(DW _xRes, DW _yRes, DW _bpp, DD _svgabuf)
  {
   DB i, j ;
   if(_xRes == 0 || _yRes == 0 || _bpp == 0 || _svgabuf == 0)
      return;
    
   xRes = _xRes;
   yRes = _yRes;
   bpp  = _bpp;
   svgabuf = (DD)&svga_buf[0];  // //  _svgabuf;
   physvgabuf = _svgabuf;

   graphics = _true;
  }
  
  void setScreen(COLOR c)
  {
    DD i, j;
    
   if(!chkGraphicsInited())
    return;

//   for(i = 0 ; i < 800 * 600 * 2 ;i+=2) //800*600*2
//       *(DW *)(svgabuf+i) = c;
//   return;
   
            
   for(i = 0 ; i < xRes ; i++)
   {
     for(j=0 ;j< yRes  ; j++) //800*600*2
     {
          setPixel(i,j,c);
//        *((DW *)(svgabuf + j + (bpp/8)*xRes*i)) = c;
//        //(0xFFFF-i);//0x00F8;
     }
   }    
 }

 void setPixel(DW x, DW y, COLOR c)
 {
    normalize(x,y);
    *((DW *)(svgabuf + x + xRes*y)) = c;
 }

 COLOR getPixel(DW x, DW y)
 {
    normalize(x,y);
    return *((DW *)(svgabuf + x + xRes*y));
 }
 
 void drawChar(DW x, DW y, DW index)
 {
   DW i = 0, j = 0;
   COLOR c;

   x %= xRes;
   y %= yRes;
      
   for(i = 0 ; i < CHARROWS ; i++)
   {
     for(j = 0 ; j < CHARCOLS ; j++)
     {
       c = charset[index-32][i][j];
       if(c)
        setPixel(x+j,y+i,0x0);//0xF800);
     }
   }
   
 }


 void rect(DW x, DW y, DW width, DW height)
 {
   DD i, j;

   if(!chkGraphicsInited())
       return;

   for(i = x ; i < (x+width) ; i++)
   {
     for(j = y ; j < (y+height)  ; j++) //800*600*2
     {
       setPixel(i,j,0xFFFF);
     }
   }                  
 }

 void charrect(DW x,DW y,DW width,DW height,DB ch)
 {
   //rect(x,y,width,height);
   fillrect(x,y,width,height,0xFFFF);//0x8BF1); //0xF0F0);
   drawChar(x+2,y+2,ch);
 }

 void drawMousePtr(DW x,DW y)
 {
  DW i,j;

  if(!graphics)
    return;

  x %= xRes;
  y %= yRes;
    
  restoreImage(mcurx,mcury);
  mvMini2Svga(mcurx,mcury,16,16);
  
  getimage(x,y,16,16,mouseimg);

// Don't Change it here 
// Let the MDriver change it after calling this function
//  mcurx = x, mcury = y;
  
  for(i = x ; i < x+16 ; i++)
  {
    for(j = y ; j < y+16 ; j++)
    {
      if(mouseptr[j-y][i-x])
      {
        setPixel(i,j,0x0);
      }
    }    
  }
  
//   mvBuf2Svga();
  mvMini2Svga(x,y,16,16);
 }

 void restoreImage(DW x, DW y)
 {
  putimage(x,y,16,16,mouseimg); 
 }

 void getimage(DW x, DW y,DW width, DW height, COLOR *buffer)
 {
  DW i, j;

  for(i = x ; i < x+width ; i++)
  {
    for(j = y; j < y+height ; j++)
    {
      buffer[(i-x)+(j-y)*width] = getPixel(i,j);
    }
  } 
 }

 void putimage(DW x, DW y,DW width, DW height, COLOR *buffer)
 {
  DW i, j;

  for(i = x ; i < x+width ; i++)
  {
    for(j = y; j < y+height ; j++)
    {
      setPixel(i,j,buffer[(i-x)+(j-y)*width]);
    }
  }
 }
 
 void drawstring(DW x,DW y,char *title)
 {
   SDB i;
   for(i = 0 ; i < strlen(title) ; i++)
     drawChar(x+i*7,y,title[i]);
 }

 void fillrect(DW x,DW y,DW width,DW height,COLOR fill)
 {
   DD i, j;

   if(!chkGraphicsInited())
       return;

   for(i = x ; i < (x+width) ; i++)
   {
     for(j = y ; j < (y+height)  ; j++) //800*600*2
     {
       setPixel(i,j,fill);
     }
   }   
 } 
 

  void mvBuf2Svga()
  {
    DD i;

    if(!graphics)
       return;
        
//    for(i = 0 ; i < 800*600 ; i++)
//    {
//     memset((void *)(physvgabuf+i),*(DB*)(svga_buf+i),1);
////     memset((void *)(physvgabuf+800*600+i),*(DB*)(svgabuf+800*600+i),1);
//    }


//    gcls();
//    for(i = 0 ; i < 100 ; i++)
//    {
//      printf(" %d ",svga_buf[800*1100-100+i]);
//    }

    memcpy((void *)physvgabuf,(void *)svgabuf,(DD)800*1200);
  }


  void mvMini2Svga(DW _x, DW _y, DW _width, DW _height)
  {
    DW i, j;

    for(j = 0 ; j < _height ; j++)
    {    
      for(i = 0 ; i < _width ; i++)
      {
        *(DW *)(physvgabuf + (j+_y) * xRes * 2 + (i+_x) * 2 ) = *(DW *)(svgabuf + (j+_y) * xRes * 2 + (i+_x) * 2 );
      }
    }
    
  }

  void emboss3D(DW x, DW y, DW width, DW height,DB flags,boolean in_or_out, DB emboss_size)
  {
    DB i;
    COLOR c1, c2;

    if(emboss_size == 0)
      emboss_size = DEFAULT_EMBOSS_SIZE;
      
    switch(in_or_out)
    {
      case _false: //out
                c1 = LIGHT_COLOR;
                c2 = DARK_COLOR;
                break;
                
      case _true: //in
                c1 = DARK_COLOR;
                c2 = LIGHT_COLOR;      
                break;
    }

    if(flags == 0) //Default case
    {
      flags = TOP|LEFT|BOTTOM|RIGHT;
    }

    for(i = 0 ; i < emboss_size ; i++)
    {
      //Top
      if(flags & TOP)
        line(x+i,y+i,x+width-i,y+i,c1);

      //Left Side
      if(flags & LEFT)
        line(x+i,y+i,x+i,y+height-i,c1);

      //Bottom
      if(flags & BOTTOM)
        line(x+i,y+height-i,x+width-i,y+height-i,c2);
      
      //Right
      if(flags & RIGHT)
        line(x+width-i,y+i,x+width-i,y+height-i,c2);
    }
    
  }

    void line(SDW x0, SDW y0, SDW x1, SDW y1, COLOR color)
    {
        SDW dy = y1 - y0;
        SDW dx = x1 - x0;
        SDW stepx, stepy;
        SDW i;

        if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
        if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }

        setPixel( x0, y0, color);
        setPixel( x1, y1, color);
        if (dx > dy) {
            SDW length = (dx - 1) >> 2;
            SDW extras = (dx - 1) & 3;
            SDW incr2 = (dy << 2) - (dx << 1);
            if (incr2 < 0) {
                SDW c = dy << 1;
                SDW incr1 = c << 1;
                SDW d =  incr1 - dx;
                for (i = 0; i < length; i++) {
                    x0 += stepx;
                    x1 -= stepx;
                    if (d < 0) {                                         // Pattern:
                        setPixel( x0, y0, color);                   //
                        setPixel( x0 += stepx, y0, color);  //  x o o
                        setPixel( x1, y1, color);                   //
                        setPixel( x1 -= stepx, y1, color);
                        d += incr1;
                    } else {
                        if (d < c) {                                                     // Pattern:
                            setPixel( x0, y0, color);                               //      o
                            setPixel( x0 += stepx, y0 += stepy, color);             //  x o
                            setPixel( x1, y1, color);                               //
                            setPixel( x1 -= stepx, y1 -= stepy, color);
                        } else {
                            setPixel( x0, y0 += stepy, color);                      // Pattern:
                            setPixel( x0 += stepx, y0, color);                      //    o o
                            setPixel( x1, y1 -= stepy, color);                      //  x
                            setPixel( x1 -= stepx, y1, color);                      //
                        }
                        d += incr2;
                    }
                }
                if (extras > 0) {
                    if (d < 0) {
                        setPixel( x0 += stepx, y0, color);
                        if (extras > 1) setPixel( x0 += stepx, y0, color);
                        if (extras > 2) setPixel( x1 -= stepx, y1, color);
                    } else
                    if (d < c) {
                        setPixel( x0 += stepx, y0, color);
                        if (extras > 1) setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 2) setPixel( x1 -= stepx, y1, color);
                    } else {
                        setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 1) setPixel( x0 += stepx, y0, color);
                        if (extras > 2) setPixel( x1 -= stepx, y1 -= stepy, color);
                    }
                }
            } else {
                SDW c = (dy - dx) << 1;
                SDW incr1 = c << 1;
                SDW d =  incr1 + dx;
                for (i = 0; i < length; i++) {
                    x0 += stepx;
                    x1 -= stepx;
                    if (d > 0) {
                        setPixel( x0, y0 += stepy, color);                  // Pattern:
                        setPixel( x0 += stepx, y0 += stepy, color);         //      o
                        setPixel( x1, y1 -= stepy, color);                  //    o
                        setPixel( x1 -= stepx, y1 -= stepy, color);         //  x
                        d += incr1;
                    } else {
                        if (d < c) {
                            setPixel( x0, y0, color);                               // Pattern:
                            setPixel( x0 += stepx, y0 += stepy, color);       //      o
                            setPixel( x1, y1, color);                         //  x o
                            setPixel( x1 -= stepx, y1 -= stepy, color);       //
                        } else {
                            setPixel( x0, y0 += stepy, color);                      // Pattern:
                            setPixel( x0 += stepx, y0, color);                      //    o o
                            setPixel( x1, y1 -= stepy, color);                      //  x
                            setPixel( x1 -= stepx, y1, color);                      //
                        }
                        d += incr2;
                    }
                }
                if (extras > 0) {
                    if (d > 0) {
                        setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 1) setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 2) setPixel( x1 -= stepx, y1 -= stepy, color);
                    } else
                    if (d < c) {
                        setPixel( x0 += stepx, y0, color);
                        if (extras > 1) setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 2) setPixel( x1 -= stepx, y1, color);
                    } else {
                        setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 1) setPixel( x0 += stepx, y0, color);
                        if (extras > 2) {
                            if (d > c)
                                setPixel( x1 -= stepx, y1 -= stepy, color);
                            else
                                setPixel( x1 -= stepx, y1, color);
                        }
                    }
                }
            }
        } else {
            SDW length = (dy - 1) >> 2;
            SDW extras = (dy - 1) & 3;
            SDW incr2 = (dx << 2) - (dy << 1);
            if (incr2 < 0) {
                SDW c = dx << 1;
                SDW incr1 = c << 1;
                SDW d =  incr1 - dy;
                for (i = 0; i < length; i++) {
                    y0 += stepy;
                    y1 -= stepy;
                    if (d < 0) {
                        setPixel( x0, y0, color);
                        setPixel( x0, y0 += stepy, color);
                        setPixel( x1, y1, color);
                        setPixel( x1, y1 -= stepy, color);
                        d += incr1;
                    } else {
                        if (d < c) {
                            setPixel( x0, y0, color);
                            setPixel( x0 += stepx, y0 += stepy, color);
                            setPixel( x1, y1, color);
                            setPixel( x1 -= stepx, y1 -= stepy, color);
                        } else {
                            setPixel( x0 += stepx, y0, color);
                            setPixel( x0, y0 += stepy, color);
                            setPixel( x1 -= stepx, y1, color);
                            setPixel( x1, y1 -= stepy, color);
                        }
                        d += incr2;
                    }
                }
                if (extras > 0) {
                    if (d < 0) {
                        setPixel( x0, y0 += stepy, color);
                        if (extras > 1) setPixel( x0, y0 += stepy, color);
                        if (extras > 2) setPixel( x1, y1 -= stepy, color);
                    } else
                    if (d < c) {
                        setPixel( stepx, y0 += stepy, color);
                        if (extras > 1) setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 2) setPixel( x1, y1 -= stepy, color);
                    } else {
                        setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 1) setPixel( x0, y0 += stepy, color);
                        if (extras > 2) setPixel( x1 -= stepx, y1 -= stepy, color);
                    }
                }
            } else {
                SDW c = (dx - dy) << 1;
                SDW incr1 = c << 1;
                SDW d =  incr1 + dy;
                for (i = 0; i < length; i++) {
                    y0 += stepy;
                    y1 -= stepy;
                    if (d > 0) {
                        setPixel( x0 += stepx, y0, color);
                        setPixel( x0 += stepx, y0 += stepy, color);
                        setPixel( x1 -= stepy, y1, color);
                        setPixel( x1 -= stepx, y1 -= stepy, color);
                        d += incr1;
                    } else {
                        if (d < c) {
                            setPixel( x0, y0, color);
                            setPixel( x0 += stepx, y0 += stepy, color);
                            setPixel( x1, y1, color);
                            setPixel( x1 -= stepx, y1 -= stepy, color);
                        } else {
                            setPixel( x0 += stepx, y0, color);
                            setPixel( x0, y0 += stepy, color);
                            setPixel( x1 -= stepx, y1, color);
                            setPixel( x1, y1 -= stepy, color);
                        }
                        d += incr2;
                    }
                }
                if (extras > 0) {
                    if (d > 0) {
                        setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 1) setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 2) setPixel( x1 -= stepx, y1 -= stepy, color);
                    } else
                    if (d < c) {
                        setPixel( x0, y0 += stepy, color);
                        if (extras > 1) setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 2) setPixel( x1, y1 -= stepy, color);
                    } else {
                        setPixel( x0 += stepx, y0 += stepy, color);
                        if (extras > 1) setPixel( x0, y0 += stepy, color);
                        if (extras > 2) {
                            if (d > c)
                                setPixel( x1 -= stepx, y1 -= stepy, color);
                            else
                                setPixel( x1, y1 -= stepy, color);
                        }
                    }
                }
            }
        }
    }

  boolean iswithin(DW x,DW y,DW stx,DW sty,DW width,DW height)
  {
    if( (x >= stx) && ( x <= stx + width) )
     {
       if((y >= sty) && ( y <= sty + height))
        return _true;
       else
        return _false;
     }
    else
      return _false;
  }    

 void cprint(DW x,DW y,char *title,COLOR c)
 {
   DW i = 0, j = 0, k = 0;

   x %= xRes;
   y %= yRes;

   for(i = 0 ; i < strlen(title) ; i++)
   {
     for(j = 0 ; j < CHARROWS ; j++)
     {
       for(k = 0 ; k < CHARCOLS ; k++)
       {
         if(charset[title[i]-32][j][k])
          setPixel(x+i*7+k,y+j,c);
       }
     }
   }
 }
    
