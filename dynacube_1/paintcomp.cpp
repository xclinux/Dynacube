/***************************************************************************
                          paintcomp.cpp  -  description
                             -------------------
    begin                : Wed Jan 28 2004
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

 #include "paintcomp.h"
 
 void paint_component(component *comp)
  {
    button *but;
    text *txt;
    textarea *txtarea;
    label *lbl;
    folderview *fv;
    
    switch(comp->type)
    {
      case BUT_TYPE :
                      but = (button *)comp;
                      but->paint();
                      break;

      case TEXT_TYPE:
                      txt = (text *)comp;
                      txt->paint();
                      break;
                      
      case TEXTAREA_TYPE:
                      txtarea = (textarea *)comp;
                      txtarea->paint();
                      break;

      case LABEL_TYPE:
                      lbl = (label *)comp;
                      lbl->paint();
                      break;      

      case FOLDERVIEW_TYPE:
                      fv = (folderview *)comp;
                      fv->paint();
                      break;
    }
  }  