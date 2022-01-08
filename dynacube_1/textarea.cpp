/***************************************************************************
                          textarea.cpp  -  description
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
 #include "textarea.h"


 void textarea::textarea_init(DW _id,DW _parent_id,DW _cnt_type,void *_cnt_ptr,DW _alias_id,DW _x,DW _y,DW _width,DW _height,DD _style,char *_txt)
 {
    DW i,k,rows;
    DW num_chars;
    memcpy(txt,_txt,strlen(_txt));
    comp_init(TEXTAREA_TYPE,_id,_parent_id,_cnt_type,_cnt_ptr,_alias_id,_x,_y,_width,_height,_style);
    rows = 0;
    cur_x = 0;
    cur_y = 0;
    st_row = 0;
    st_col = 0;
    num_chars = strlen(_txt);
    visi_rows = (height/(CHAR_HEIGHT+Y_OFFSET)) - 1;
    visi_cols = (width/(CHAR_WIDTH+X_OFFSET)) - 1;
    for(k=0,i=0;i<num_chars;i++)
      {
        if(_txt[i] == '\n')
         {
           txt[rows][k] = '\0';
           k = 0;
           rows++;
         }
	else
	 {
         txt[rows][k] = _txt[i];
	 k++;
	 }
  }
	if(k != 0)
	  txt[rows][k] = '\0';
  max_row = rows + 1;

    is_sel = false;
    sel_stx = 0;
    sel_sty = 0;
    sel_enx = 0;
    sel_eny = 0;
 }

 void textarea::paint()
  {
    window *win_ptr;
    frame *frm_ptr;
    DW _x,_y,_width,_height;
    DW i,j,k;
    char tmp[255];

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
/*                         rect(30,30,100,100);
             					   ginfo(50,30,itoa(cur_x,10));
                				 ginfo(70,30,itoa(cur_y,10));*/

                         fillrect(x+_x, y+_y, width, height,TEXT_COLOR);
                  			 if(is_sel)
                      	  {
/*               					    ginfo(50,50,itoa(sel_stx,10));
                					  ginfo(70,50,itoa(sel_sty,10));
                					  ginfo(50,70,itoa(sel_enx,10));
                					  ginfo(70,70,itoa(sel_eny,10)); */

                           //same line case                       
                           if(sel_sty == sel_eny)
                            {
                             if(sel_stx >=st_col && sel_stx <= st_col + visi_cols)
                      		    {
                    			     if(sel_enx <= st_col + visi_cols)
                        				 fillrect(x+_x + X_OFFSET + (sel_stx - st_col) * 7,y + _y + Y_OFFSET +(sel_sty - st_row) *9,(sel_enx - sel_stx) * 7,9,0x3E0);
                      		     else
                         				 fillrect(x+_x + X_OFFSET + (sel_stx - st_col) * 7,y + _y + Y_OFFSET+(sel_sty - st_row) *9,(visi_cols + st_col - sel_stx) * 7,9,0xE300);
                        	    }
                    			   else if(sel_enx >=st_col && sel_enx <= st_col + visi_cols)
                    			    {
                      				 fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (st_row + sel_sty) *9,(sel_enx - st_col) * 7,9,0x1F);
                    			    }
                            }                            
                           else
                           {
                           //start is in the visible portion
                  			   if(sel_sty >=st_row && sel_sty <= st_row + visi_rows)
        	          		    {
                              if(sel_stx >=st_col && sel_stx <= st_col + visi_cols)
                                 fillrect(x+_x + X_OFFSET + (sel_stx - st_col) * 7,y + _y + Y_OFFSET  + (sel_sty - st_row) *9,(visi_cols + st_col - sel_stx) * 7,9,0x3E0);
                              else if(sel_stx < st_col)
                                 fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (sel_sty - st_row) *9,visi_cols * 7,9,0x3E0);

                    				for(i = sel_sty+1;i < sel_eny && i <= st_row + visi_rows;i++)
                    				  fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (i - st_row) *9,visi_cols * 7,9,0x3E0);

                            if(sel_eny <= st_row + visi_rows)
                             {
                              if(sel_enx >=st_col && sel_enx <= st_col + visi_cols)
                                fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (sel_eny - st_row) *9,(sel_enx - st_col) * 7,9,0x3E0);
                              else if(sel_enx > st_col)
                                 fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (sel_eny - st_row) *9,visi_cols * 7,9,0x3E0);
                             }
                  			    }
                            //end is in the visible portion
                  			   else if(sel_eny >=st_row && sel_eny <= st_row + visi_rows)
                    		    {
                    				for(i = st_row;i < sel_eny ;i++)
                     				  fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (i - st_row) *9,visi_cols * 7,9,0x3E0);
  
                            if(sel_enx >=st_col && sel_enx <= st_col + visi_cols)
                                fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (sel_eny - st_row) *9,(sel_enx - st_col) * 7,9,0x3E0);
                            else if(sel_enx > st_col)
                                 fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (sel_eny - st_row) *9,visi_cols * 7,9,0x3E0);
                    		    }
                           //both are not. but visible is selected                           
                           else if(sel_eny >=st_row)
                            {
                            for(i = st_row;i <= st_row + visi_rows;i++)
                    				  fillrect(x+_x + X_OFFSET,y + _y + Y_OFFSET + (i - st_row) *9,visi_cols * 7,9,0x3E0);                              
                            }
                           } 
                 			    }//selection

                         for(j=st_row;j<=st_row+visi_rows && j < max_row;j++)
                          {
                            drawstring(x+_x+X_OFFSET,y+_y+Y_OFFSET+(j-st_row)*9,(char *)strmncpy( (void *)tmp,(void *)txt[j],st_col,visi_cols));
                          }
//                         drawstring(x+_x+5,y+_y+5,txt);
                         emboss3D(x+_x, y+_y, width, height,0,_true,1);
                      }
                      else
                      {
                         rect(x+_x, y+_y, width, height);
                         drawstring(x+_x+5,y+_y+5,tmp);
                         emboss3D(x+_x, y+_y, width, height,0,_true,1);
                      }
                      break;
//      case FRM_TYPE :
//                      frm_ptr = (frame *) cnt_ptr;
//                      if((x + width <  frm_ptr->width) && (y + height < frm_ptr->height))
//                         rect(x+frm_ptr->x,y+frm_ptr->y,width,height);

    }
  }
   void textarea::updateCursor()
   {
     POINT pt;

     pt = getAbsLoc(this);

     if(cur_x > st_col + visi_cols)
     	st_col = cur_x - visi_cols;
     if(cur_x < st_col)
     	st_col = cur_x;

     if(cur_y > st_row + visi_rows)
     	st_row = cur_y - visi_rows;
     if(cur_y < st_row)
     	st_row = cur_y;

     pt.x += (DW)((cur_x - st_col)*7) - 1;
     pt.y += (DW)((cur_y - st_row)*9) - 1;
     pt.x += X_OFFSET;
     pt.y += Y_OFFSET;
     csr.setCursor(pt);
     csr.show();
   }
   
   void textarea::react(DW _x,DW _y)
   {
    POINT pt;
    DW row,col;

    pt = getAbsLoc(this);
    col = (_x - pt.x - X_OFFSET) / 7;
    row = (_y - pt.y - Y_OFFSET) / 9;
    is_sel = false;

    if((row + st_row) < max_row)
       cur_y = row + st_row;
    else
       cur_y = max_row -1;

    if((col + st_col) <= strlen(txt[cur_y]))
 	     cur_x = col + st_col;
    else
   	   cur_x = strlen(txt[cur_y]);
    updateCursor();
   }

   void textarea::keyPress(DW state,DW ch)
   {
     DW i,j;
     char tmp,tmp1;
     DW prev_cur_x,prev_cur_y;
     POINT pt;
     DW total_chars,num_lines,len;
     pt = getAbsLoc(this);
     prev_cur_x = cur_x;
     prev_cur_y = cur_y;

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
         case HOME	:
   	             		 cur_x = 0;
               			 cur_y = 0;
              			 updateCursor();
                     if(!(state & ST_SHIFT))
                       {
   		              	  is_sel = false;
                       }
                    else
                       {
                        if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                          return;
          		        	if(is_sel)
          			        {
                         switch(ptcmp(cur_x,cur_y,sel_stx,sel_sty))
                          {
                           case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                           case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                           case 0:
                                is_sel = false;
                                break;
                          }
                   		  }
                			 else
                			  {
                    	   is_sel = true;
                			   sel_stx = cur_x;
                			   sel_sty = cur_y;
            		    	   sel_enx = prev_cur_x;
            			       sel_eny = prev_cur_y;
                			  }
                       }
             			 restoreImage(mcurx,mcury);
          	  		 paint();
          		  	 if(mouse_inited)
    	        		   {
      		 	          getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
              			 }
            			 mvMini2Svga(pt.x,pt.y,width,height);
            			 break;
	case END	:
      			 cur_y = max_row-1;
			       cur_x = strlen(txt[cur_y]);
      			 updateCursor();
             if(!(state & ST_SHIFT))
             {
   		    	  is_sel = false;
             }
            else
             {
               if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                 return;
           		 if(is_sel)
             			  {
                     switch(ptcmp(cur_x,cur_y,sel_enx,sel_eny))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }
                     }
          			 else
          			  {
              	   is_sel = true;
          			   sel_enx = cur_x;
         	  		   sel_eny = cur_y;
          			   sel_stx = prev_cur_x;
        		  	   sel_sty = prev_cur_y;
        			    }
             }
       			 restoreImage(mcurx,mcury);
    	  		 paint();
    		  	 if(mouse_inited)
    			   {
      		 	  getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
      			 }
      			 mvMini2Svga(pt.x,pt.y,width,height);
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
              			 total_chars = strlen(txt[cur_y]);
               		   if(cur_x < total_chars)
                		  {
                		   for(i=cur_x;i<total_chars - 1;i++)
                		     txt[cur_y][i] = txt[cur_y][i+1];
              			   txt[cur_y][total_chars-1] = '\0';
              			  }
              		   else
              			  {
              			   if(cur_y == max_row - 1)
                  		    return;
              			   strcat(txt[cur_y],txt[cur_y+1]);

              			   for(i=cur_y +1;i<max_row - 1;i++)
                			    strcpy(txt[i],txt[i+1]);

                       strcpy(txt[i],"");
              			   max_row--;
              			  }
              			 if(cur_x > strlen(txt[cur_y]))
                		   	cur_x = strlen(txt[cur_y]);
                    }
                else
                {
                 num_lines = sel_eny - sel_sty;
                 if(num_lines == 0)
                 {
                  len =  sel_enx - sel_stx;
                	total_chars = strlen(txt[sel_sty]);

                  for(i = sel_stx;i<total_chars;i++)
                      txt[sel_sty][i] = txt[sel_sty][i + len];

                  total_chars -= len;
                  txt[sel_sty][total_chars] = '\0';
                 }
                 else
                  {
                    for(i = sel_enx; i < strlen(txt[sel_eny]) ; i++)
                       txt[sel_sty][sel_stx + i - sel_enx] =txt[sel_eny][i];

                    txt[sel_sty][sel_stx + i - sel_enx] = '\0';

                    for(i = sel_sty + 1; i < max_row ;i++)
                      strcpy(txt[i],txt[i+num_lines]);
                    max_row -= num_lines;
                  }
                  cur_x = sel_stx;
                  cur_y = sel_sty;
                  updateCursor();
                }
		         break;
	case LEFT_A	:
			 if(cur_x > 0)
			 {
			 cur_x--;
			 updateCursor();
			 }
			 else if(cur_y > 0)
			  {
			   cur_y--;
			   cur_x = strlen(txt[cur_y]);
			   updateCursor();
			  }
			 break;
	case RIGHT_A	:
			 if(cur_x < strlen(txt[cur_y]))
			 {
			  cur_x++;
			  updateCursor();
			 }
			 else if(cur_y < max_row -1)
			 {
			   cur_y++;
			   cur_x = 0;
			   updateCursor();
			 }
			 break;
	case UP 	:
			 if(cur_y > 0)
			  {
			   cur_y--;
			   if(cur_x > strlen(txt[cur_y]))
			   	cur_x = strlen(txt[cur_y]);
			   updateCursor();
			  }
			 break;
	case DOWN	:
			 if(cur_y < max_row -1)
			  {
			   cur_y++;
			   if(cur_x > strlen(txt[cur_y]))
			   	cur_x = strlen(txt[cur_y]);
			   updateCursor();
			  }
			 break;
	case HOME	:
			 cur_x = 0;
			 updateCursor();
			 break;
	case END	:
			 cur_x = strlen(txt[cur_y]);
			 updateCursor();
			 break;
	case PAGE_UP	:
			 if(st_row - visi_rows >= 0)
			 {
			   st_row -= visi_rows - 1;
			   cur_y  -= visi_rows;
			 }
			 else
			 {
			    cur_y = 0;
			    st_row = 0;
			 }

  			 if(cur_x > strlen(txt[cur_y]))
 			   	 cur_x = strlen(txt[cur_y]);
			 break;
	case PAGE_DOWN	:
			if(st_row + visi_rows < max_row)
			{
			   st_row += visi_rows - 1;
			   if(cur_y + visi_rows < max_row)
			     cur_y  += visi_rows;
			   else
			     cur_y = max_row - 1;
			}
			else
			 {
			      cur_y = max_row - 1;
			 }
  			 if(cur_x > strlen(txt[cur_y]))
			   	cur_x = strlen(txt[cur_y]);
			 break;
   }
    is_sel = false;
  }
    else
     {
      switch(ch)
       {
        case LEFT_A	:
            			 if(cur_x > 0)
              			 {
              			 cur_x--;
              			 updateCursor();
              			 }
              		 else if(cur_y > 0)
              		  {
            			   cur_y--;
              		   cur_x = strlen(txt[cur_y]);
            			   updateCursor();
            			  }
                   if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                    return;
         		    	 if(is_sel)
          			    {
                     switch(ptcmp(cur_x,cur_y,sel_stx,sel_sty))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }   
               		  }
            			 else
            			  {
                	   is_sel = true;
            			   sel_stx = cur_x;
            			   sel_sty = cur_y;
            			   sel_enx = prev_cur_x;                
            			   sel_eny = prev_cur_y;
            			  }
        			 break;
	case RIGHT_A	:
        			 if(cur_x < strlen(txt[cur_y]))
  	        	 {
    	    		  cur_x++;
    		    	  updateCursor();
    			     }
           		 else if(cur_y < max_row -1)
		        	 {
        		   cur_y++;
      			   cur_x = 0;
      			   updateCursor();
      			   }
                if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                  return;
           			 if(is_sel)
             			  {
                     switch(ptcmp(cur_x,cur_y,sel_enx,sel_eny))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }   
                     }
          			 else
          			  {
              	   is_sel = true;
          			   sel_enx = cur_x;
         	  		   sel_eny = cur_y;
          			   sel_stx = prev_cur_x;
        		  	   sel_sty = prev_cur_y;
        			    }
           
         			  break;
  case UP :
                 if(cur_y > 0)
    	      		  {
		    	         cur_y--;
      			       if(cur_x > strlen(txt[cur_y]))
     	        		   	cur_x = strlen(txt[cur_y]);
      			       updateCursor();
    	      		  }
                   if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                    return;
         		    	 if(is_sel)
          			    {
                     switch(ptcmp(cur_x,cur_y,sel_stx,sel_sty))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }
               		  }
            			 else
            			  {
                	   is_sel = true;
            			   sel_stx = cur_x;
            			   sel_sty = cur_y;
            			   sel_enx = prev_cur_x;
            			   sel_eny = prev_cur_y;
            			  }
                    break;
	case DOWN	:
          			 if(cur_y < max_row -1)
		          	  {
			             cur_y++;
           			   if(cur_x > strlen(txt[cur_y]))
      	      		   	cur_x = strlen(txt[cur_y]);
          			   updateCursor();
    	      		  }
                if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                  return;
           			 if(is_sel)
             			  {
                     switch(ptcmp(cur_x,cur_y,sel_enx,sel_eny))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }
                     }
          			 else
          			  {
              	   is_sel = true;
          			   sel_enx = cur_x;
         	  		   sel_eny = cur_y;
          			   sel_stx = prev_cur_x;
        		  	   sel_sty = prev_cur_y;
        			    }
    			 break;

	case HOME	:
                	 cur_x = 0;
                   updateCursor();
                   if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                    return;
         		    	 if(is_sel)
          			    {
                     switch(ptcmp(cur_x,cur_y,sel_stx,sel_sty))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }
               		  }
            			 else
            			  {
                	   is_sel = true;
            			   sel_stx = cur_x;
            			   sel_sty = cur_y;
            			   sel_enx = prev_cur_x;
            			   sel_eny = prev_cur_y;
            			  }
                break;			
	case END	:
          			 cur_x = strlen(txt[cur_y]);
			           updateCursor();
                 if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                   return;
           			 if(is_sel)
             			  {
                     switch(ptcmp(cur_x,cur_y,sel_enx,sel_eny))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }
                     }
          			 else
          			  {
              	   is_sel = true;
          			   sel_enx = cur_x;
         	  		   sel_eny = cur_y;
          			   sel_stx = prev_cur_x;
        		  	   sel_sty = prev_cur_y;
        			    }
                 break;
	case PAGE_UP	:
        	  		 if(st_row - visi_rows >= 0)
          	  		 {
            			   st_row -= visi_rows - 1;
            			   cur_y  -= visi_rows;
            			 }
          			 else
            			 {
            		    cur_y = 0;
            		    st_row = 0;
            			 }
          			if(cur_x > strlen(txt[cur_y]))
         			   	 cur_x = strlen(txt[cur_y]);
                   if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                     return;
         		    	 if(is_sel)
          			    {
                     switch(ptcmp(cur_x,cur_y,sel_stx,sel_sty))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }
               		  }
            			 else
            			  {
                	   is_sel = true;
            			   sel_stx = cur_x;
            			   sel_sty = cur_y;
            			   sel_enx = prev_cur_x;
            			   sel_eny = prev_cur_y;
            			  }


           		  break;
	case PAGE_DOWN	:
            			if(st_row + visi_rows < max_row)
            			{
          			   st_row += visi_rows - 1;
          			   if(cur_y + visi_rows < max_row)
          			     cur_y  += visi_rows;
            		   else
          			     cur_y = max_row - 1;
            			}
              		else
            			 {
        			      cur_y = max_row - 1;
            			 }
            		 if(cur_x > strlen(txt[cur_y]))
            		   	cur_x = strlen(txt[cur_y]);

                 if(cur_y == prev_cur_y && cur_x == prev_cur_x)
                  return;
           			 if(is_sel)
             			  {
                     switch(ptcmp(cur_x,cur_y,sel_enx,sel_eny))
                      {
                        case 1:
                     			     sel_enx = cur_x;
                    			     sel_eny = cur_y;
                                break;
                        case -1:
                                sel_stx = cur_x;
                      		      sel_sty = cur_y;
                                break;
                        case 0:
                                is_sel = false;
                                break;
                      }
                     }
          			 else
          			  {
              	   is_sel = true;
          			   sel_enx = cur_x;
         	  		   sel_eny = cur_y;
          			   sel_stx = prev_cur_x;
        		  	   sel_sty = prev_cur_y;
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
			total_chars = strlen(txt[cur_y]);
			if(cur_x > 0)
			 {
			 for(i=cur_x-1;i<total_chars - 1;i++)
			  txt[cur_y][i] = txt[cur_y][i+1];

			 txt[cur_y][total_chars-1] = '\0';
			 cur_x--;
 			 }
			 else
			  {
			   if(cur_y == 0)
			    return;

			   strcat(txt[cur_y -1],txt[cur_y]);

			   for(i=cur_y;i<max_row - 1;i++)
			     strcpy(txt[i],txt[i+1]);

			   strcpy(txt[i],"");
			   max_row--;
			   cur_y--;
			   cur_x = strlen(txt[cur_y]);
			  }
			 }
	 		break;
	 case VK_ENTER:
	 		total_chars = strlen(txt[cur_y]);
			if(max_row >= TEXTAREA_ROWS)
			  return;

			for(i=max_row;i>cur_y +1;i--)
			   strcpy(txt[i],txt[i-1]);

			if(cur_x == total_chars)
			 strcpy(txt[cur_y+1],"");
			else
			{
			 strmncpy(txt[cur_y+1],txt[cur_y],cur_x,total_chars - cur_x);
			 txt[cur_y][cur_x] = '\0';
			}
			 cur_y++;
			 cur_x = 0;
			 max_row++;
			break;

   default :
		total_chars = strlen(txt[cur_y]);
		if(total_chars >= TEXTAREA_COLS)
			return;

		for(i=total_chars;i>cur_x;i--)
			txt[cur_y][i] = txt[cur_y][i-1];

		txt[cur_y][total_chars+1] = '\0';

		txt[cur_y][cur_x] = ch;

		cur_x++;
	}
 }

    updateCursor();
    restoreImage(mcurx,mcury);
    paint();
    if(mouse_inited)
    {
      getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
    }
    mvMini2Svga(pt.x,pt.y,width,height);
   }

  void textarea::setText(char * text)
   {
    DW i,k;
    DW num_chars;
    DW rows = 0;
    POINT pt;
    pt = getAbsLoc(this);
    num_chars = strlen(text);
    for(i=0;i<num_chars;i++)
      {
        if(text[i] == '\n')
         {
           txt[rows][k] = '\0';
           k = 0;
           rows++;
         }
      	else
      	 {
           txt[rows][k] = text[i];
	         k++;
      	 }
      }
      if(k != 0)
      	txt[rows][k] = '\0';
     st_row = 0;
     st_col = 0;
     max_row = rows + 1;

 /* if(this == focus->focus_ptr)
    {
     cur_x = 0;
     cur_y = 0;
     updateCursor();
    } */

    restoreImage(mcurx,mcury);
    paint();
    if(mouse_inited)
    {
      getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
    }
    mvMini2Svga(pt.x,pt.y,width,height);
   }

  void textarea::getText(char * text)
   {
    DW i;

    strcpy(text,"");
    for(i=0;i<max_row-1;i++)
     {
      strcat(text,txt[i]);
      strcat(text,"\n");
     }
     strcat(text,txt[i]);
   }
   
   void textarea::copy()
   {
    SDW i,j,k;

    if(!is_sel)
     return;
    k = 0;
    
    if(sel_sty == sel_eny)
     {
       for(j = sel_stx; j < sel_enx ;j++)
        {
          clip[k] = txt[sel_sty][j];
          k++;
        }
       clip[k] = '\0';
     }
    else
    { 
     for(j = sel_stx; j <strlen(txt[sel_sty]);j++)
        {
          clip[k] = txt[sel_sty][j];
          k++;
        }
    clip[k] = '\n';
    k++;    
    for(i = sel_sty + 1; i < sel_eny;i++)
     {                         
       for(j = 0; j <strlen(txt[i]);j++)
        {
          clip[k] = txt[i][j];
          k++;
        }
       clip[k] = '\n';
       k++;     
     }
      for(j = 0; j < sel_enx;j++)
        {
          clip[k] = txt[sel_eny][j];
          k++;
        }
     clip[k] = '\0';
   } 
    cl_pres = true;    
   }
 void textarea::cut()
  {     
   SDW i,j,k,len;
   DW num_lines;
   DW total_chars;
   POINT pt;
   pt =getAbsLoc(this);

   if(!is_sel)
    return;

    k = 0;
    num_lines = sel_eny - sel_sty;
    if(num_lines == 0)
     {
       len =  sel_enx - sel_stx;
       for(j = sel_stx; j < sel_enx ;j++)
        {
          clip[k] = txt[sel_sty][j];
          k++;
        }        
       clip[k] = '\0';

       total_chars = strlen(txt[sel_sty]);
       
       for(i = sel_stx;i<total_chars;i++)
         txt[sel_sty][i] = txt[sel_sty][i + len];

       total_chars -= len;
       txt[sel_sty][total_chars] = '\0';
     }
    else
    {
     for(j = sel_stx; j <strlen(txt[sel_sty]);j++)
        {
          clip[k] = txt[sel_sty][j];
          k++;
        }
    clip[k] = '\n';
    k++;
    for(i = sel_sty + 1; i < sel_eny;i++)
     {
       for(j = 0; j <strlen(txt[i]);j++)
        {
          clip[k] = txt[i][j];
          k++;
        }
       clip[k] = '\n';
       k++;
     }
      for(j = 0; j < sel_enx;j++)
        {
          clip[k] = txt[sel_eny][j];
          k++;
        }
     clip[k] = '\0';

     for(i = sel_enx; i < strlen(txt[sel_eny]) ; i++)
       txt[sel_sty][sel_stx + i - sel_enx] =txt[sel_eny][i];

     txt[sel_sty][sel_stx + i - sel_enx] = '\0';

     for(i = sel_sty + 1; i < max_row ;i++)
      strcpy(txt[i],txt[i+num_lines]);

     max_row -= num_lines;  
   }
    cl_pres = true;
    
    cur_x = sel_stx;
    cur_y = sel_sty;

  cl_pres = true;
  is_sel = false;
  updateCursor();
  restoreImage(mcurx,mcury);
	paint();
	if(mouse_inited)
		{
		getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
		}
	mvMini2Svga(pt.x,pt.y,width,height);
}
   void textarea::paste()
   {
     SDW i,j,k;
     DW cl_enx = 0;
     DW num_lines = 0;
     DW len;
     DW total_chars;
     POINT pt;
     pt =getAbsLoc(this);

     if(!cl_pres)
      return;

      len = strlen(clip);
      for(i = 0;i<len;i++)
    	 {
	      if(clip[i] == '\n')
         {
          num_lines++;
          cl_enx = i + 1;
         }
    	 }
      if(num_lines == 0)
       {
         total_chars = strlen(txt[cur_y]);
         for(i = total_chars - 1; i >= cur_x ; i--)
          txt[cur_y][i + len] = txt[cur_y][i];
         for(j = 0;j <len;j++)
          {
           txt[cur_y][j+cur_x] = clip[j];
          }
        total_chars += len;
        txt[cur_y][total_chars] = '\0';
        cur_x = cur_x + len;
       }
      else
       {
          for(i = max_row -1; i > cur_y; i--)
            strcpy(txt[i + num_lines],txt[i]);

          total_chars = strlen(txt[cur_y]);
          strmncpy(txt[cur_y + num_lines],clip,cl_enx,len - cl_enx);

          for(i = cur_x; i < total_chars; i++)
            txt[cur_y + num_lines][len-cl_enx + i - cur_x] = txt[cur_y][i];

          txt[cur_y + num_lines][len-cl_enx + i - cur_x] = '\0';


          for(i = total_chars - 1; i >= cur_x ; i--)
              txt[cur_y][i + len] = txt[cur_y][i];

          for(i = 0; i < len ; i++)
           {
            if(clip[i] != '\n')
             txt[cur_y][cur_x + i] = clip[i];
            else
              break;
           }
           txt[cur_y][cur_x + i] = '\0';

          if(num_lines != 1)
          {
           j = cur_y + 1;
           k = 0;
           i++;
          for(; i < len; i++)
           {
             if(clip[i] == '\n')
              {
               txt[j][k] = '\0';
               j++;
               k = 0;
              }
             else
              {
               txt[j][k] = clip[i];
               k++;
              }
           }
          }
          max_row += num_lines;
          cur_y = cur_y + num_lines;
          cur_x = strlen(txt[cur_y]);
        }
       updateCursor();
       restoreImage(mcurx,mcury);
     	 paint();
     	 if(mouse_inited)
    		{
		    getimage(mcurx,mcury,16,16, &mouseimg[0][0]);
    		}
     	 mvMini2Svga(pt.x,pt.y,width,height);
   }

  SDW textarea::ptcmp(DW x1,DW y1,DW x2,DW y2)
   {
   	   if(y1 > y2)
   	    {
         return 1;    	     
        }
        else if(y1 == y2)
		    {
			    if(x1 > x2)
   			    {
             return 1;
   			    }
	        else if(x1 == x2)
            return 0;
    	    else
  			     {
              return -1;
   			     }
	      }
		   else
 			    {
           return -1;
 			    }
   }  
/*if(ch < ESC)
     {
     tmp = txt[cur_y][visi_cols - 1];

     for(j = visi_cols - 1; j > cur_x ; j--)
        txt[cur_y][j] = txt[cur_y][j-1];

     for(i = cur_y + 1; i < TEXTAREA_ROWS ; i++)
     {
      tmp1 = txt[i][visi_cols -1];
      for(j = visi_cols - 1; j > 0; j--)
        txt[i][j] = txt[i][j-1];
      txt[i][0] = tmp;
      tmp = tmp1;
     }
     txt[cur_y][cur_x] = ch;

     cur_x++;
     if(cur_x >= visi_cols)
      {
        cur_x = 0;
        cur_y++;
        if((cur_y - st_row) >= visi_rows)
         st_row++;
      }
    }
    else
     {
       switch(ch)
        {
          case DEL:
                    for(j = cur_x; j < visi_cols - 1; j++)
                          txt[cur_y][j] = txt[cur_y][j+1];

                    for(i = cur_y + 1; i < max_row ; i++)
                       {
                        txt[i-1][visi_cols - 1] = txt[i][0];
                        for(j = 0; j <visi_cols-1; j++)
                          txt[i][j] = txt[i][j+1];
                       }
                    txt[max_row-1][visi_cols - 1] = txt[max_row][0];
                    for(j = 0; j <visi_cols-1; j++)
                      txt[max_row][j] = txt[max_row][j+1];

                    break;
        }
     } */
