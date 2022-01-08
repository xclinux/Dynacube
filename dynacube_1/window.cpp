/***************************************************************************
                          window.cpp  -  description
                             -------------------
    begin                : Sat Jan 31 2004
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


 #include "window.h"
 #include "frame.h"
 #include "component.h"
 #include "utility.h"
 #include "cursor.h"


     void window::win_init(DW _id, DW _parent_id, DW _x, DW _y, DW _width, DW _height, DD _style, DW _is_diag,char* _title)
     {
      this->cntr_init(_id,_parent_id,_x,_y,_width,_height);
      this->style = _style;

      this->hasMenu = false;
//      this->hasMenu = true;
      memcpy(this->title,_title,strlen(_title));
      diag = (window *)NULL;
      is_diag = _is_diag;

//      rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
//      ginfo(400,400,itoa(*(DD*)title,16));
//      delay(0x3FFF);
//      MenuBar = (menubar *)kmalloc(sizeof(menubar));
			buf = (COLOR *)kmalloc(width * height * sizeof(COLOR));
////      ginfo(400,420,itoa((DD)(void *)MenuBar,16));
////      delay(0x9FFF);
//      MenuBar->menubar_init(this,0,0,width-2*BORDER_WIDTH,MENUBAR_HEIGHT,0);
//      ginfo(400,440,itoa(*(DD*)(void *)(MenuBar->mnu[0].menu_ptr),16));
//      delay(0x9FFF);
     }

     void window::paint_win()
     {
         DW i;
         DW _x, _y, _width, _height;
         DW x1,x2,y1,y2;

         if(style & HIDDEN || style & W_MINIMIZE)
          return;
         else if(style & W_MAXIMIZE)
         {
             _x = 0;
             _y = 0;
             _width = SCREEN_WIDTH;
             _height = SCREEN_HEIGHT;
         }
         else
         {
             _x = x;
             _y = y;
             _width = width;
             _height = height;
//             getimage(x,y,width,height,buf);
         }


         //Base Window
         fillrect(_x,_y,_width,_height,FILL_COLOR);

         //border
//         fillrect(x,y,width,BORDER_HEIGHT,BORDER_COLOR);
//         fillrect(x,y,BORDER_WIDTH,height,BORDER_COLOR);
//         fillrect(x+width-BORDER_WIDTH,y,BORDER_WIDTH,height,BORDER_COLOR);
//         fillrect(x,y+height-BORDER_HEIGHT,width,BORDER_HEIGHT,BORDER_COLOR);

         //title
         fillrect(_x+BORDER_WIDTH,_y+BORDER_HEIGHT,_width-2*BORDER_WIDTH,TITLE_HEIGHT,TITLE_COLOR);
         drawstring(_x+BORDER_WIDTH+SUMMA_WIDTH,_y+BORDER_HEIGHT+(TITLE_HEIGHT-7)/2,title);

				//change
				//         if(!(style & W_NORESIZE))
	 if(is_diag == 0)
         {
          charrect(_x+_width-3*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,'-');
          emboss3D(_x+_width-3*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,0,_false,2);
          charrect(_x+_width-2*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,127);
          emboss3D(_x+_width-2*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,0,_false,2);
         }

	  charrect(_x+_width-1*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,'X');
          emboss3D(_x+_width-1*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,0,_false,2);

         emboss3D(_x,_y,_width,_height,0,_false,2);

         for(i = 0;i<num_comps;)
         {
            if(comp[i] != NULL)
            {
              paint_component(comp[i]);
              i++;
            }
         }

        for(i = 0;i<num_conts;)
         {
            if(cont[i] != NULL)
            {
              ((frame *)cont[i])->paint();
              i++;
            }
         }

         if(hasMenu)
         {
//					 ginfo(60,60,"hasMenu::MenuBar->paint");
					 MenuBar->paint();
         }

	 if(diag != NULL)
	  diag->paint_win();
     }

     void window::freeAll()
     {
       DW i;

         for(i = 0;i<num_comps;)
         {
            if(comp[i] != NULL)
            {
              free((void*)comp[i]);
              i++;
            }
         }
        for(i = 0;i<num_conts;)
         {
            if(cont[i] != NULL)
            {
              ((frame *)cont[i])->freeAll();
              free((void *)cont[i]);
              i++;
            }
         }

         if(MenuBar != NULL)
         {
	         MenuBar->freeAll();
	         free(MenuBar);
	       }

	       if(buf != NULL)
	         free(buf);
     }

     ENTITY window::findEntity(DW cx,DW cy)
     {
         DW _x, _y, _width, _height;
         DW i;
         ENTITY en;
	 en.type = NO_TYPE;

//         ginfo(100,50,"win::findEntity");
//         delay(0x5FFF);

          if(style & W_MAXIMIZE)
          {
//           ginfo(100,70,"win::MAX");
//           delay(0x5FFF);

           _x = BORDER_WIDTH;
           _y = TITLE_HEIGHT + BORDER_HEIGHT + ((hasMenu) ? MENUBAR_HEIGHT : 0);
           _width  = SCREEN_WIDTH;
           _height = SCREEN_HEIGHT;
          }
          else
          {
//           ginfo(100,70,"win::MIN");
//           delay(0x5FFF);
           _x = x + BORDER_WIDTH;
           _y = y + TITLE_HEIGHT + BORDER_HEIGHT + ((hasMenu) ? MENUBAR_HEIGHT : 0);
           _width = width;
           _height = height;
          }

         for(i = 0; i < num_comps;)
          {
//           ginfo(100,100+i*10,itoa(i,10));
//           delay(0x5FFF);
           if(comp[i] != NULL)
            {
				     if(!(comp[i]->style & DISABLED))
		 	       {
              if(iswithin(cx,cy,_x + comp[i]->x, _y + comp[i]->y,comp[i]->width,comp[i]->height))
              {
                comp_focus = comp[i];
//                ginfo(400,300,itoa(comp_focus->type,10));

                switch(comp[i]->type)
                {
                  case BUT_TYPE:
                        en.alias_id = comp[i]->alias_id;
                        en.id       = comp[i]->id;
                        en.type     = BUTTON;

                        ((button*)comp[i])->react();
                        return en;
                        break;

                  case TEXT_TYPE:
                        ((text*)comp[i])->react(cx,cy);
                        break;

                  case TEXTAREA_TYPE:
                       ((textarea*)comp[i])->react(cx,cy);
                        break;
                }
//                delay(0x3FFF);
                break;
              }
	   			   }
              i++;
            }
          }
     }

    SDB window::processMenu(DW x,DW y)
    {
      //Check for tgt
      if(hasMenu)
      {
				return MenuBar->process(x,y);
		  }
		  else
		  	return -1;
     }

    void window::deactivate()
    {
     style |= W_DISABLED;
    }

    void window::activate()
    {
     style &= ~W_DISABLED;
    }

   void window::keyPress(DW state, DW ch)
   {
    if(diag != NULL)
     {
      diag->keyPress(state,ch);
      return;
     }
    if(comp_focus != NULL)
    {		 //change
     if((comp_focus->style & DISABLED))
		   return;

      switch(comp_focus->type)
      {
        case TEXT_TYPE:
                            ((text *)comp_focus)->keyPress(state,ch);
                            break;
        case TEXTAREA_TYPE:
                           ((textarea *)comp_focus)->keyPress(state,ch);
                            break;
      }
    }
   }


   void window::move(SDW del_x, SDW del_y)
   {
		 DW tmpX, tmpY;

		 if(style & W_MAXIMIZE)
		 	return;

		 tmpX = x + del_x;
		 tmpY = y + del_y;

		 if(tmpX > 0 && (tmpX + width) < SCREEN_WIDTH && tmpY > 0 && (tmpY + height) < SCREEN_HEIGHT)
		 {
			 x += del_x;
			 y += del_y;
//			 getimage(mcurx,mcury,16,16,&mouseimg[0][0]);
			 paint_win();
//			 mvMini2Svga(x,y,width,height);
       mvBuf2Svga();
     }
   }

		void window::menuInit(DD _user_menu_addr, DW _pid)
		{
			hasMenu = true;
			MenuBar = (menubar *)kmalloc(sizeof(menubar));
      MenuBar->menubar_init(this,0,0,width-2*BORDER_WIDTH,MENUBAR_HEIGHT,_user_menu_addr,_pid);
    }
    void window::attachDialog(window* diag_ptr)
     {
	diag = diag_ptr;
     }
    void window::detachDialog()
     {
	diag = (window *)NULL;
     }
