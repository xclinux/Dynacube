/***************************************************************************
                          menubar.cpp  -  description
                             -------------------
    begin                : Mon Mar 29 2004
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

 #include "menubar.h"
 #include "window.h"
 #include "menu.h"

			 typedef struct
			 {
			  char lbl[MN_MAX_CHAR];
				 DB cmdCode; //To be sent to the client
			 } _MENUITEM;

			 typedef struct
			 {
			   DB no_item;
			   _MENUITEM mnuitem[MN_MAX_ITEM];
			  } _MENU;

			  typedef struct
			  {
			   DB no_menu;
			   struct
			   {
			    char label[MB_MAX_CHAR];
			    _MENU menu_ptr;
			   }mnu[MB_MAX_MENU];
			  } _MENUBAR;
 

 void menubar::menubar_init(void *_cnt_ptr,DW _x,DW _y,DW _width,DW _height, DD _user_menu_addr, DW _pid)
 {
	  DB i,j;
//	  MENUITEM mnuitem[10];
		MENUITEM *mnuitem;
	  char info[100];

	  cnt_ptr = _cnt_ptr;
	  x = _x;
	  y = _y;
	  width = _width;
	  height = _height;
	  user_menu_addr = _user_menu_addr;
	 
		_MENUBAR *mybar = (_MENUBAR *)_user_menu_addr;
//		ginfo(10,200,itoa(_user_menu_addr,10));
//		ginfo(10,220,itoa((DD)(void*)mybar,10));
//		ginfo(10,240,itoa(*(DB *)((DD)&mybar->no_menu),10));	  

	  //Get the real Values from user's Menu
    no_menu = (mybar->no_menu > MB_MAX_MENU) ? MB_MAX_MENU : mybar->no_menu;
//		no_menu = mybar->no_menu;
    cur_menu = -1; //No Selected Menu

    menu mymenu[MB_MAX_MENU];

    for(i = 0 ; i < no_menu ; i++)
    {
			mnu[i].menu_ptr = (menu*)kmalloc(sizeof(menu));
			strcpy(mnu[i].label,mybar->mnu[i].label);
			mnuitem = (MENUITEM*)kmalloc(mybar->mnu[i].menu_ptr.no_item * sizeof(MENUITEM));
			
			for(j = 0 ; j < mybar->mnu[i].menu_ptr.no_item ; j++)
			{
				strcpy(mnuitem[j].lbl,mybar->mnu[i].menu_ptr.mnuitem[j].lbl);
				mnuitem[j].cmdCode = mybar->mnu[i].menu_ptr.mnuitem[j].cmdCode;
			}
			
			mnu[i].menu_ptr->menu_init(_cnt_ptr,mybar->mnu[i].menu_ptr.no_item,mnuitem,_pid);

			if(mnuitem != NULL)
				free(mnuitem);
		}
 }

 void menubar::paint()
  {
    DW _x,_y,_width,_height;
    DW x1,y1,x2,y2;
    DB i;
		window *win_ptr = (window*)cnt_ptr;
		DW offset = 0, summa_x_off = 10, summa_y_off = 5;

	  if(win_ptr->style & W_MAXIMIZE)
	  {
	  	_x = BORDER_WIDTH;
	    _y = TITLE_HEIGHT + BORDER_HEIGHT ;
	    _width  = SCREEN_WIDTH;
	    _height = SCREEN_HEIGHT;
	  }
	  else
	  {
	  	_x = win_ptr->x + BORDER_WIDTH;
		  _y = win_ptr->y + TITLE_HEIGHT + BORDER_HEIGHT ;
		  _width = win_ptr->width;
		  _height = win_ptr->height;
	  }

  	fillrect(_x+x,_y+y,_width-2*BORDER_WIDTH,height,MENUBAR_COLOR);

			x1 = _x;
      y1 = _y+height;
      x2 = _x+_width-2*BORDER_WIDTH;
      y2 = _y+height;

			for(i = 0 ; i < no_menu ; i++)
			{
        cprint(x1+offset+(i+1)*summa_x_off,y1-height+summa_y_off,mnu[i].label,0x0);
        offset  += strlen(mnu[i].label) * 10;
			}
      line(x1,y1,x2,y2,0x0);

		  if(cur_menu != -1)
		  {
				//Generic Menu Painting
				x1 = mnu[cur_menu].menu_ptr->x;
				y1 = mnu[cur_menu].menu_ptr->y - MENUBAR_HEIGHT + 3;
				x2 = strlen(mnu[cur_menu].label)*10; //Not really x2 but width :-)
				y2 = MENUBAR_HEIGHT-2*3;
		    emboss3D(x1,y1,x2,y2,LEFT|TOP|RIGHT,_true,1);
				mnu[cur_menu].menu_ptr->paint();
			}

//	  ginfo(300,300,"menubar::process");
//	  ginfo(300,320,itoa(user_menu_addr,16));
  }


   SDB menubar::process(DW x,DW y) //Absolute x, y
   {
		DW _x,_y, _width, _height;
    DW x1,y1,x2,y2;
		DW offset = 0, summa_x_off = 10, summa_y_off = 5;
		window *win_ptr = (window*)cnt_ptr;
		DB i, j;
		SDB ret;

	  if(win_ptr->style & W_MAXIMIZE)
	  {
	  	_x = BORDER_WIDTH;
	    _y = TITLE_HEIGHT + BORDER_HEIGHT;
	    _width  = SCREEN_WIDTH;
	    _height = SCREEN_HEIGHT;
	  }
	  else
	  {
	  	_x = win_ptr->x + BORDER_WIDTH;
		  _y = win_ptr->y + TITLE_HEIGHT + BORDER_HEIGHT;
		  _width = win_ptr->width;
		  _height = win_ptr->height;
	  }

			x1 = _x;
      y1 = _y+height;
      x2 = _x+_width-2*BORDER_WIDTH;
      y2 = _y+height;

//	  ginfo(300,300,"menubar::process");
//	  ginfo(300,320,itoa(user_menu_addr,16));
//	  ginfo(300,340,itoa(y,10));

	  if(iswithin(x,y,_x,_y,_width,MENUBAR_HEIGHT))
	  {
			restoreImage(mcurx,mcury);

			if(cur_menu != -1)
			{
				mnu[cur_menu].menu_ptr->menu_restore();
			}

			for(i = 0 ; i < no_menu ; i++)
			{
        if(iswithin(x,y,x1+offset+(i+1)*summa_x_off,y1-height+summa_y_off,strlen(mnu[i].label)*10,height))
        {
					cur_menu = i;
		   		mnu[cur_menu].menu_ptr->x = x1+offset+(i+1)*summa_x_off-3;
		      mnu[cur_menu].menu_ptr->y = y1;
					break;
				}
        offset  += strlen(mnu[i].label) * 10;
			}

			if(i == no_menu)
			{
				cur_menu = -1;
			}

			this->paint();

//			getimage(mcurx,mcury,16,16,&mouseimg[0][0]);
			mouse_restore();

			mvBuf2Svga();

			return 0;
//			  return -1;
	  }
	  else if(cur_menu != -1)
	  {
//	    restoreImage(mcurx,mcury);
			mnu[cur_menu].menu_ptr->menu_restore();

	 		if(mnu[cur_menu].menu_ptr->process(x,y) == 0) //Something Useful
				ret = 0;
			else
				ret = -1;

	  	cur_menu = -1;

	   	win_ptr->paint_win();
	    mouse_restore();

	    if(ret == 0)
		    mvBuf2Svga();

 		  return ret;
		}

   }

   void menubar::keyPress(DW state,DW ch)
   {
	 }

	 void menubar::freeAll()
	 {
		 DB i;

		 for(i = 0 ; i < no_menu ; i++)
		 {
			 if(mnu[i].menu_ptr != NULL)
				 free(mnu[i].menu_ptr);
		 }
   }
