/***************************************************************************
                          text.cpp  -  description
                             -------------------
    begin                : Mon Mar 1 2004
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
 #include "text.h"

 void text::text_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_txt)
 {
    memcpy(txt,_txt,strlen(_txt));
    comp_init(TEXT_TYPE,_id,_parent_id,_cnt_type,_cnt_ptr,_alias_id,_x,_y,_width,_height,_style);
    start = 0;
    curs = 0;
    allow_chars = (width/(CHAR_WIDTH+X_OFFSET)) - 1;
    total_chars = strlen(_txt);
    is_sel = false;
    sel_st = 0;
    sel_en = 0;
 }

 void text::paint()
  {
    window *win_ptr;
    frame *frm_ptr;
    DW _x,_y,_width,_height;
    DB tmp[255];

    switch(cnt_type)
    {
      case WIND_TYPE :
                      win_ptr = (window *) cnt_ptr;
                      if(win_ptr->style & W_MAXIMIZE)
                       {
                         _x = BORDER_WIDTH;
                         _y = TITLE_HEIGHT + BORDER_HEIGHT + ((win_ptr->hasMenu) ? MENUBAR_HEIGHT : 0);
                         _width  = SCREEN_WIDTH;
                         _height = SCREEN_HEIGHT;
                       }
                      else
                       {
                         _x = win_ptr->x + BORDER_WIDTH;
                         _y = win_ptr->y + TITLE_HEIGHT + BORDER_HEIGHT + ((win_ptr->hasMenu) ? MENUBAR_HEIGHT : 0);
                         _width = win_ptr->width;
                         _height = win_ptr->height;
                       }

                      if((x + width < _width) && (y + height < _height))
                      {

       fillrect(x+_x, y+_y, width, height,TEXT_COLOR);
       
			 if(is_sel)
			  {
			   if(sel_st >=start && sel_st <= start + allow_chars)
			    {
			     if(sel_en <= start + allow_chars)
				 fillrect(x+_x + X_OFFSET + (sel_st - start) * 7,y + _y + Y_OFFSET,(sel_en - sel_st) * 7,9,0x3E0);
			     else
 				 fillrect(x+_x + X_OFFSET + (sel_st - start) * 7,y + _y + Y_OFFSET,(allow_chars + start - sel_st) * 7,9,0xE300);
			    }
			   else if(sel_en >=start && sel_en <= start + allow_chars)
			    {
				 fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET,(sel_en - start) * 7,9,0x1F);
			    }
			  }
                         drawstring(x+_x + X_OFFSET ,y+_y+ Y_OFFSET, (char *)strmncpy( (void *)tmp,(void *)txt,start,allow_chars));
			 emboss3D(x+_x, y+_y, width, height,0,_true,1);
                      }
                      else
                      {
                         rect(x+_x, y+_y, width, height);
                         emboss3D(x+_x, y+_y, width, height,0,_true,1);
                      }
                      break;
//      case FRM_TYPE :
//                      frm_ptr = (frame *) cnt_ptr;
//                      if((x + width <  frm_ptr->width) && (y + height < frm_ptr->height))
//                         rect(x+frm_ptr->x,y+frm_ptr->y,width,height);

    }
  }


   void text::react(DW _x,DW _y) //Absolute x, y
   {
    POINT pt, loc;
    DW visi_chars;
    pt = getAbsLoc(this);

    visi_chars = total_chars - start;
    is_sel = false;

    if(iswithin(_x,_y,pt.x,pt.y,visi_chars*(CHAR_WIDTH+X_OFFSET)+X_OFFSET,height))
    {
     curs = (_x - pt.x - X_OFFSET)/(CHAR_WIDTH+X_OFFSET);
     loc.x = pt.x + curs * (CHAR_WIDTH + X_OFFSET) + X_OFFSET;
     loc.y = pt.y + Y_OFFSET;

     csr.setCursor(loc);
     csr.show();
    }
    else
    {
        curs = visi_chars;
        loc.x = pt.x + (curs * (CHAR_WIDTH + X_OFFSET)) + X_OFFSET;
        loc.y = pt.y + Y_OFFSET;

        csr.setCursor(loc);
        csr.show();
    }
    curs = curs + start;

   }

  void text::update_cursor(DW no)
  {
     POINT pt;
     pt = getAbsLoc(this);

     DW visi_chars = total_chars - start;

//     (200,100,itoa(visi_chars,10));
//     ginfo(200,110,itoa(allow_chars,10));
//     delay(0xFFFF);

     if(visi_chars > allow_chars)
     {
      visi_chars = allow_chars;
     }
     if(no > start + allow_chars)
     	start = no - allow_chars;
     if(no < start)
     	start = no;

     if(width > visi_chars*(CHAR_WIDTH+X_OFFSET) + X_OFFSET)
     {
      pt.x += X_OFFSET + (DW)((no-start)*(CHAR_WIDTH+X_OFFSET));
      pt.y += Y_OFFSET;
      csr.setCursor(pt);
      csr.show();
     }
  }

   void text::keyPress(DW state,DW ch)
   {
     DW i;
     POINT pt;
     DW len;

     pt = getAbsLoc(this);

    if(state & ST_ALT)
     return;
    if(state & ST_CAPS)
     	ch = toupper(ch);
	
     if(state & ST_SHIFT)
        ch = toggle_shift(ch);
    if(state & ST_CNTL)
    {
      switch(ch)
       {
         case 'c' :
	 	    if(is_sel)
		    	{
			 copy();
			}
	 	    break;
	 case 'x' :
	 	    if(is_sel)
		    	{
		 	  cut();
			}
		    break;
	 case 'v' :
		    if(cl_pres)
		     {
			paste();
			is_sel = false;
		     }
		    break;
       }
      return;
    }

    if(ch > ESC)
     {
     if(!(state & ST_SHIFT))
     {

      switch(ch)
       {
        case DEL 	:
			 if(!is_sel)
			 {
			 if(total_chars > 0 && curs < total_chars)
			 {
			 for(i=curs;i<total_chars - 1;i++)
			  txt[i] = txt[i+1];

			 txt[total_chars-1] = '\0';
			 total_chars--;
    			 }
			 }
			 else
			  {
			   len =  sel_en - sel_st;

			   for(i = sel_st;i<total_chars;i++)
     				txt[i] = txt[i + len];

   			   total_chars -= len;
   			   txt[total_chars] = '\0';
			   curs = sel_st;
			   update_cursor(curs);
			  }
		         break;
	case LEFT_A	:
			 if(curs > 0)
			 {
			 curs--;
			 update_cursor(curs);
			 }
			 break;
	case RIGHT_A	:
			 if(curs < total_chars)
			 {
			 curs++;
			 update_cursor(curs);
			 }
			 break;
	case HOME	:
			 curs = 0;
			 update_cursor(curs);
			 break;
	case END	:
			 curs = total_chars;
			 update_cursor(curs);
			 break;
       }
       is_sel = false;
      }
    else
     {
      switch(ch)
       {
        case LEFT_A	:
			 if(curs > 0)
			 {
			 curs--;
			 update_cursor(curs);
			 if(is_sel)
			  {
			   if(curs > sel_st)
			    {
			     sel_en = curs;
			    }
			   else if(curs == sel_st)
			    is_sel = false;
			   else
			    sel_st = curs;
			  }
			 else
			  {
			   is_sel = true;
			   sel_st = curs;
			   sel_en = curs + 1;
			  }
			 }
			 break;
	case RIGHT_A	:
			 if(curs < total_chars)
			 {
			 curs++;
			 update_cursor(curs);
			 if(is_sel)
			  {
			   if(curs > sel_en)
			    {
			     sel_en = curs;
			    }
			   else if(curs = sel_en)
			    is_sel = false;
			   else
			    sel_st = curs;
			  }
			 else
			  {
			   is_sel = true;
			   sel_st = curs - 1;
			   sel_en = curs;
			  }
			 }
			 break;
	case HOME	:
	 		 if(curs != 0)
			 {
			 sel_en = curs;
			 sel_st = 0;
			 is_sel = true;
			 curs = 0;
			 update_cursor(curs);
			 }
			 break;
	case END	:
			 if(curs != total_chars)
			 {
			 sel_en = total_chars;
			 sel_st = curs;
			 is_sel = true;
			 curs = total_chars;
			 update_cursor(curs);
			 }
			 break;
       }
      }
     }

 if(ch < ESC)
 {
      is_sel = false;
      switch(ch)
      	{
	 case VK_BACKSPACE :
	 		if(!(state & ST_SHIFT))
			{
			if(total_chars > 0 && curs <= total_chars && curs > 0)
			 {
			 for(i=curs-1;i<total_chars - 1;i++)
			  txt[i] = txt[i+1];

			 txt[total_chars-1] = '\0';
			 total_chars--;
			 curs--;
			 if(curs == start)
			 {
			  if(start > allow_chars)
			    start = start - allow_chars;
			  else
			    start = 0;
			 }
			 update_cursor(curs);
    			 }
			 }
	 		break;
	case VK_ENTER:
			break;
	 default :
		if(total_chars >= TEXT_MAX)
			return;
		for(i=total_chars;i>curs;i--)
			txt[i] = txt[i-1];

		txt[total_chars+1] = '\0';
		//     if(state & ST_SHIFT)
		txt[curs] = ch; //+(_shift?-32:0);

		total_chars++;

		curs++;
		update_cursor(curs);
	}
 }
 		restoreImage(mcurx,mcury);
		paint();
		if(mouse_inited)
			{
			getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
			}
		mvMini2Svga(pt.x,pt.y,width,height);
}

void text::copy()
 {
   SDW i;
   if(!is_sel)
    return;
   for(i = sel_st;i<sel_en;i++)
    clip[i - sel_st] = txt[i];

   clip[sel_en - sel_st] = '\0';
   cl_pres = true;
 }
void text::cut()
 {
   SDW i,j,len;
   POINT pt;
   pt =getAbsLoc(this);

   if(!is_sel)
    return;

   len =  sel_en - sel_st;

   for(i = sel_st;i<sel_en;i++)
    clip[i - sel_st] = txt[i];

   clip[len] = '\0';
   cl_pres = true;

   for(i = sel_st;i<total_chars;i++)
     txt[i] = txt[i + len];

   total_chars -= len;
   txt[total_chars] = '\0';
   is_sel = false;

   curs = sel_st;
   update_cursor(curs);

	restoreImage(mcurx,mcury);
	paint();
	if(mouse_inited)
		{
		getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
		}
	mvMini2Svga(pt.x,pt.y,width,height);

 }
void text::paste()
 {
   SDW i,j,len;
   POINT pt;
   pt =getAbsLoc(this);

   if(!cl_pres)
    return;

      len = strlen(clip);
      for(i = 0;i<len;i++)
	 {
	  if(clip[i] == '\n')
	   break;
	 }
	len = i;

    for(i = total_chars - 1; i >= curs ; i--)
     txt[i + len] = txt[i];

    for(j = 0;j <len;j++)
    {
     txt[j+curs] = clip[j];
    }
    total_chars += len;
    txt[total_chars] = '\0';

 	curs = curs + len;
	update_cursor(curs);

    	restoreImage(mcurx,mcury);
	paint();
	if(mouse_inited)
		{
		getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
		}
	mvMini2Svga(pt.x,pt.y,width,height);
 }
  void text::setText(char * text)
   {
   POINT pt;
   pt =getAbsLoc(this);
   DW i;

	for(i = 0;i<strlen(text);i++)
	 {
	  if(text[i] == '\n')
	   break;
	  txt[i] = text[i];
	 }
	 txt[i] = '\0';
	total_chars = strlen(txt);
        restoreImage(mcurx,mcury);
	paint();
	if(mouse_inited)
		{
		getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
		}
	mvMini2Svga(pt.x,pt.y,width,height);
   }
  void text::getText(char * text)
   {
    strcpy(text,txt);
  }


