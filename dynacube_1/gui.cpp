/***************************************************************************
                          gui.cpp  -  description
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

 #include "gui.h"
 #include "window.h"
 #include "startmenu.h"

 #include "mouse.h"
 
 #include "button.h"
 #include "text.h"
 #include "textarea.h"
 #include "label.h"
 #include "folderview.h"

 #include "list.h"
 #include "hashmap.h"
 #include "svga.h"
 #include "stdlib.h"
 #include "cursor.h"

 extern "C"
 {
   #include "icon.h"
   #include "cmos.h"
 }


 //To store the ON_FOCUS component/Window/Frame
 window *focus = (window *)NULL;
 window *clamped = (window *)NULL;
 DW clamp_x = 0, clamp_y = 0;

 COLOR tsk_color;
 startmenu *sm;
 cursor csr;


 void cursor_paint() //C wrapper
 {
   csr.paint();
 }

 void runGUI()
 {
   MSG msg1;
   DW i = 0, j, k;
   DD ret_val;
   char smsg[128];

//   COLOR c = 0xFFFF;
//   //0xF6B3, 0xF695, 0xEE75, 0xEDFD,0xDDBD,
//   COLOR color[] = {0xE5F1, 0xBC4D}; // 0xE637, 0xDE99, 0xCDE7, 0xB5DD, 0xAD57, 0xA537, 0x9D53, 0x9CD1, 0x9533, 0x94D9, 0x8557, 0x6C75
//
//   DW r = 0, g = 0, b = 0;

  initgraphics(800,600,16,vbe_mode.PhysBasePtr);

//	cli();
//  setScreen(0x0);
//	sys_init_info();
//  sti();

  sm = (startmenu *)kmalloc(sizeof(startmenu));
  sm->startmenu_init();
  csr.cursor_init();
  setScreen(SCREEN_COLOR);
  repaint();

//  drawIcon(100,100,&folder[0][0]);
//  mvBuf2Svga();
//  BLOCK

//  while(c >= 0)//c < 64000)
//  {
//
//    for(i = 0 ; i < 800 ; i+=100)
//    {
//      for(j = 0 ; j < 600 ; j += 100)
//      {
////      c = ((r & 0x1F)<<11) | ((g & 0x3F)<<5) | ((b & 0x1F));
//          fillrect(i,j,80,50,c);
//          ginfo(i+5,j+5,itoa(c,16));
//          //c = c + 1;
//          c = c - 10;
//      }
//    }
//
//    mvBuf2Svga();
//
//    delay(0xFFFF);
//
//  }

//  for(i = 0 ; i < 20 ; i++)
//  {
//   line(300+i*2,300-i*3,50+i,50-i,0xF800);
//  }

//  fillrect(100,100,200,100,0x0BB0);//0xABBA
//  emboss3D(100,100,200,100,0,_false);
//
//  fillrect(350,100,200,100,0x0BB0);//0xABBA
//  emboss3D(350,100,200,100,0,_true);

//  tsk_color = 0xFED4;
//
//  for(i = 0 ; i < 2 ; i++)
//  {
//    drawTaskbar();
//    fillrect(START_WIDTH + i*100 + 10, SCREEN_HEIGHT + 5, 95, 20, color[i]);
//    mvBuf2Svga();
//    delay(0xFFFF);
//  }
//
//  BLOCK

   while(1)
   {
     printf("\nHello from GUI");
     printf("\nAbout to block In GUI RECV");

     asm("pushl %0"::"r"(&msg1));
     asm("int $0x30"::"a"(4));
//     BLOCK

     printf("\n\n\nfrom_pid %d ",msg1.from_pid);
     printf("\nbuffer %s",msg1.msg_buf);

     cli();
     ret_val = processMessage(&msg1);
     sti();

     if(msg1.from_pid != KERNEL_PID)
     {
       asm("pushl %%eax"::"a"(ret_val));
       asm("pushl %%eax"::"a"(msg1.from_pid));
       asm("int $0x30"::"a"(11));
     }
     
   }
 }


 SDW processMessage(MSG *msg)
 {
   button *btn_ptr;

   switch(msg->type)
   {
    case CREATE:
          return processCreate(msg);
          break;

    case ADD:
          break;

    case SHOW:
          return processShow(msg);
          break;

    case HIDE:
          return processHide(msg);
          break;

    case RESIZE:
          return processResize(msg);
          break;

    case ENABLE:
    	  return processEnable(msg);
          break;

    case DISABLE:
    	  return processDisable(msg);
          break;

    case DESTROY:
          return processDestroy(msg);
          break;

    case ACTION:
          switch(msg->sub_type)
          {
            case MOUSE:
                  return processMouse(msg);
                  break;

            case KBD:
//            	  ginfo(300,300,"KBD Called");
                  return processKBD(msg);
                  break;

            default:
                  return -1;
                  break; //Not Really Needed - But Just In case :-)
          }

          break;

    case FINISHED:
          switch(msg->sub_type)
          {
            case BUT_TYPE:

//            ginfo(100,300,itoa(*(DW*)msg->msg_buf,10));
//            ginfo(100,300,itoa(hfind(msg->from_pid,COMP_TYPE,*(DW*)msg->msg_buf),10));

             btn_ptr = (button*)lfind(msg->from_pid,COMP_TYPE,hfind(msg->from_pid,COMP_TYPE,*(DW*)msg->msg_buf));
             if(btn_ptr != NULL)
               btn_ptr->react();
             else
               ginfo(50,50,"NULL BUTTON");
             break;
          }
          break;
//change
    case SET:
	    return processSet(msg);
    	    break;
    case GET:
    	    return processGet(msg);
    	    break;
    case COPY:
    	    return processCopy(msg);
    	    break;
    case CUT:
    	    return processCut(msg);
    	    break;
    case PASTE:
    	    return processPaste(msg);
    	    break;
    default:
          break;
   }
 }


 SDW processCreate(MSG *msg)
 {
  DD i, j;
  SDW id, parent_id;
  DW pid;
  DW cntr_found = ALIAS_MAX;
  CREATE_INFO *cr_info;
  COMP_CREATE_INFO *cmp_cr_info;
  DD phy;

  //Container Pointers
  window *win_ptr;
  frame *frm_ptr;

  //Component Pointers
  button *but_ptr;
  text *txt_ptr;
  textarea *txtarea_ptr;
  label *lbl_ptr;
  folderview *fv_ptr;

  pid = msg->from_pid;

  switch(msg->sub_type)
  {
    case WINDOW:
              cr_info = (CREATE_INFO *)msg->msg_buf;

              printf("\nalias_id %d cont_id %d",cr_info->alias_id,cr_info->cntr_id);
              printf("\n x %d y %d width %d height %d",cr_info->x,cr_info->y,cr_info->width,cr_info->height);
              printf("\ntitle %s",cr_info->title);

              if(cr_info->width < MIN_WIDTH)
                cr_info->width = MIN_WIDTH;

              if(cr_info->height < MIN_HEIGHT)
                cr_info->height = MIN_HEIGHT;

              if(cr_info->cntr_id)
               {
                 parent_id = hfind(pid,WIND_TYPE,cr_info->cntr_id);
                 if(parent_id == -1)
                    return -1;
               }
               else
               {
                 parent_id = WINDOW_MAX;
               }

                 win_ptr = (window *)kmalloc(sizeof(window));

                 if(win_ptr == NULL)
                    return -1;

                 id = ladd(pid,WIND_TYPE,(void *)win_ptr);

                 if(id == -1)
                 {
                  free((void *)win_ptr);
                  return -1;
                 }

                 if(hadd(pid,WIND_TYPE,cr_info->alias_id,id) == -1)
                 {
                   free((void *)win_ptr);
                   return -1;
                 }
                 printf("\n p_id %d id %d winptr %x",parent_id,id,win_ptr);

                 win_ptr->win_init(id,   \
                            parent_id, \
                            cr_info->x % SCREEN_WIDTH, cr_info->y % SCREEN_HEIGHT, \
                            cr_info->width % SCREEN_WIDTH,   \
                            cr_info->height % SCREEN_HEIGHT, \
                            cr_info->style,                   \
			    0,			              \
                            cr_info->title                    \
                           );

                return 0;

              break;

    case BUTTON:

              cmp_cr_info = (COMP_CREATE_INFO *)msg->msg_buf;

              printf("\nalias_id %d cont_id %d",cmp_cr_info->alias_id,cmp_cr_info->cntr_id);
              printf("\n x %d y %d width %d height %d",cmp_cr_info->x,cmp_cr_info->y,cmp_cr_info->width,cmp_cr_info->height);
              printf("\ntitle %s",cmp_cr_info->label);

              if(cmp_cr_info->width < MIN_BUT_WIDTH)
                cmp_cr_info->width = MIN_BUT_WIDTH;

              if(cmp_cr_info->height < MIN_BUT_HEIGHT)
                cmp_cr_info->height = MIN_BUT_HEIGHT;


               if(cmp_cr_info->cnt_type == WIND_TYPE)
                   parent_id = hfind(pid,WIND_TYPE,cmp_cr_info->cntr_id);
               else
                   parent_id = hfind(pid,FRM_TYPE,cmp_cr_info->cntr_id);

               //KR we have to check for Frames also               
               if(parent_id == -1)
                   return -1;

               if(cmp_cr_info->cnt_type == WIND_TYPE)
                 win_ptr = (window *)lfind(pid,WIND_TYPE,parent_id);
               else
                 frm_ptr = (frame *)lfind(pid,FRM_TYPE,parent_id);   
                   
               but_ptr = (button *)kmalloc(sizeof(button));

               if(but_ptr == NULL)
                    return -1;

               id = ladd(pid,COMP_TYPE,(void *)but_ptr);

               if(id == -1)
                 {
                  free((void *)but_ptr);
                  return -1;
                 }

               if(hadd(pid,COMP_TYPE,cmp_cr_info->alias_id,id) == -1)
                 {
                   free((void *)but_ptr);
                   return -1;
                 }
               printf("\n p_id %d id %d winptr %x",parent_id,id,but_ptr);
               if(cmp_cr_info->cnt_type == WIND_TYPE)
               {
                  win_ptr->attachComponent(but_ptr);
                  but_ptr->but_init(id,   \
                            parent_id, \
                            cmp_cr_info->cnt_type, \
                            (void *)win_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );
               }
               else
               {
                  frm_ptr->attachComponent(but_ptr);
                  but_ptr->but_init(id,   \
                            parent_id,     \
                            cmp_cr_info->cnt_type, \
                            (void *)frm_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );

               }

                return 0;

              break;

    case TEXT:
              cmp_cr_info = (COMP_CREATE_INFO *)msg->msg_buf;

              printf("\nalias_id %d cont_id %d",cmp_cr_info->alias_id,cmp_cr_info->cntr_id);
              printf("\n x %d y %d width %d height %d",cmp_cr_info->x,cmp_cr_info->y,cmp_cr_info->width,cmp_cr_info->height);
              printf("\ntitle %s",cmp_cr_info->label);

              if(cmp_cr_info->width < MIN_TEXT_WIDTH)
                cmp_cr_info->width = MIN_TEXT_WIDTH;

              if(cmp_cr_info->height < MIN_TEXT_HEIGHT)
                cmp_cr_info->height = MIN_TEXT_HEIGHT;


               if(cmp_cr_info->cnt_type == WIND_TYPE)
                   parent_id = hfind(pid,WIND_TYPE,cmp_cr_info->cntr_id);
               else
                   parent_id = hfind(pid,FRM_TYPE,cmp_cr_info->cntr_id);

               //KR we have to check for Frames also
               if(parent_id == -1)
                   return -1;

               if(cmp_cr_info->cnt_type == WIND_TYPE)
                 win_ptr = (window *)lfind(pid,WIND_TYPE,parent_id);
               else
                 frm_ptr = (frame *)lfind(pid,FRM_TYPE,parent_id);

               txt_ptr = (text *)kmalloc(sizeof(text));

               if(txt_ptr == NULL)
                    return -1;

               id = ladd(pid,COMP_TYPE,(void *)txt_ptr);

               if(id == -1)
               {
                  free((void *)txt_ptr);
                  return -1;
               }

               if(hadd(pid,COMP_TYPE,cmp_cr_info->alias_id,id) == -1)
               {
                   free((void *)txt_ptr);
                   return -1;
               }
               printf("\n p_id %d id %d winptr %x",parent_id,id,txt_ptr);
               if(cmp_cr_info->cnt_type == WIND_TYPE)
               {
                  win_ptr->attachComponent(txt_ptr);
                  txt_ptr->text_init(id,   \
                            parent_id, \
                            cmp_cr_info->cnt_type, \
                            (void *)win_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );
               }
               else
               {
                  frm_ptr->attachComponent(txt_ptr);
                  txt_ptr->text_init(id,   \
                            parent_id,     \
                            cmp_cr_info->cnt_type, \
                            (void *)frm_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );

               }

                return 0;

              break;

    case TEXTAREA:
              cmp_cr_info = (COMP_CREATE_INFO *)msg->msg_buf;

              printf("\nalias_id %d cont_id %d",cmp_cr_info->alias_id,cmp_cr_info->cntr_id);
              printf("\n x %d y %d width %d height %d",cmp_cr_info->x,cmp_cr_info->y,cmp_cr_info->width,cmp_cr_info->height);
              printf("\ntitle %s",cmp_cr_info->label);

              if(cmp_cr_info->width < MIN_TEXTAREA_WIDTH)
                cmp_cr_info->width = MIN_TEXTAREA_WIDTH;

              if(cmp_cr_info->height < MIN_TEXTAREA_HEIGHT)
                cmp_cr_info->height = MIN_TEXTAREA_HEIGHT;


               if(cmp_cr_info->cnt_type == WIND_TYPE)
                   parent_id = hfind(pid,WIND_TYPE,cmp_cr_info->cntr_id);
               else
                   parent_id = hfind(pid,FRM_TYPE,cmp_cr_info->cntr_id);

               //KR we have to check for Frames also
               if(parent_id == -1)
                   return -1;

               if(cmp_cr_info->cnt_type == WIND_TYPE)
                 win_ptr = (window *)lfind(pid,WIND_TYPE,parent_id);
               else
                 frm_ptr = (frame *)lfind(pid,FRM_TYPE,parent_id);

               txtarea_ptr = (textarea *)kmalloc(sizeof(textarea));

               if(txtarea_ptr == NULL)
                    return -1;

               id = ladd(pid,COMP_TYPE,(void *)txtarea_ptr);

               if(id == -1)
               {
                  free((void *)txtarea_ptr);
                  return -1;
               }

               if(hadd(pid,COMP_TYPE,cmp_cr_info->alias_id,id) == -1)
               {
                   free((void *)txtarea_ptr);
                   return -1;
               }
               printf("\n p_id %d id %d winptr %x",parent_id,id,txtarea_ptr);
               if(cmp_cr_info->cnt_type == WIND_TYPE)
               {
                  win_ptr->attachComponent(txtarea_ptr);
                  txtarea_ptr->textarea_init(id,   \
                            parent_id, \
                            cmp_cr_info->cnt_type, \
                            (void *)win_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );
               }
               else
               {
                  frm_ptr->attachComponent(txtarea_ptr);
                  txtarea_ptr->textarea_init(id,   \
                            parent_id,     \
                            cmp_cr_info->cnt_type, \
                            (void *)frm_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );

               }

                return 0;
    
              break;
              

    case LIST:
              break;

    case HSCROLLBAR:
              break;

    case VSCROLLBAR:
              break;

    case CHECKBOX:
              break;

    case RADIOBUTTON:
              break;

    case MENU:
//    					rect(0,0,800,600);
//    				  ginfo(10,10,"Create:GUI:MENU");
//    				  ginfo(10,20,itoa(msg->msg_buf[0],10));
//    				  ginfo(10,40,itoa(*(DD*)(msg->msg_buf+2),10));
				      phy = get_phys(msg->from_pid,*(DD *)(msg->msg_buf + 2));							
//    				  ginfo(10,60,itoa(phy,10));
//          		delay(0x3FFF);

							parent_id = hfind(pid,WIND_TYPE,*(DW *)msg->msg_buf);

           		if(parent_id == -1)
           		{
							  ginfo(50,50,"Error");
              	return -1;
              }
              else
              {
//							  ginfo(50,50,itoa(parent_id,10));
							}
						                
               win_ptr = (window *)lfind(pid,WIND_TYPE,parent_id);

               if(win_ptr != NULL)
               {
	              win_ptr->menuInit(phy,msg->from_pid);
//							  ginfo(50,70,win_ptr->title);
							  win_ptr->paint_win();
							  mvBuf2Svga();
							 }

//							delay(0x9FFF);
//							ginfo(50,50,"MENU Completed");							
              break;
    
    case TOOLBAR:
              break;

    case FRAME:
              break;

    case ICON:
              break;
              
    case LABEL:
              cmp_cr_info = (COMP_CREATE_INFO *)msg->msg_buf;

              printf("\nalias_id %d cont_id %d",cmp_cr_info->alias_id,cmp_cr_info->cntr_id);
              printf("\n x %d y %d width %d height %d",cmp_cr_info->x,cmp_cr_info->y,cmp_cr_info->width,cmp_cr_info->height);
              printf("\ntitle %s",cmp_cr_info->label);

              if(cmp_cr_info->width < MIN_LABEL_WIDTH)
                cmp_cr_info->width = MIN_LABEL_WIDTH;

              if(cmp_cr_info->height < MIN_LABEL_HEIGHT)
                cmp_cr_info->height = MIN_LABEL_HEIGHT;


               if(cmp_cr_info->cnt_type == WIND_TYPE)
                   parent_id = hfind(pid,WIND_TYPE,cmp_cr_info->cntr_id);
               else
                   parent_id = hfind(pid,FRM_TYPE,cmp_cr_info->cntr_id);

               if(parent_id == -1)
                   return -1;

               if(cmp_cr_info->cnt_type == WIND_TYPE)
                 win_ptr = (window *)lfind(pid,WIND_TYPE,parent_id);
               else
                 frm_ptr = (frame *)lfind(pid,FRM_TYPE,parent_id);

               lbl_ptr = (label *)kmalloc(sizeof(label));

               if(lbl_ptr == NULL)
                    return -1;

               id = ladd(pid,COMP_TYPE,(void *)lbl_ptr);

               if(id == -1)
               {
                  free((void *)lbl_ptr);
                  return -1;
               }

               if(hadd(pid,COMP_TYPE,cmp_cr_info->alias_id,id) == -1)
               {
                   free((void *)lbl_ptr);
                   return -1;
               }
               printf("\n p_id %d id %d winptr %x",parent_id,id,lbl_ptr);
               if(cmp_cr_info->cnt_type == WIND_TYPE)
               {
                  win_ptr->attachComponent(lbl_ptr);
                  lbl_ptr->label_init(id,   \
                            parent_id, \
                            cmp_cr_info->cnt_type, \
                            (void *)win_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );
               }
               else
               {
                  frm_ptr->attachComponent(lbl_ptr);
                  lbl_ptr->label_init(id,   \
                            parent_id,     \
                            cmp_cr_info->cnt_type, \
                            (void *)frm_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );

               }

              return 0;    
              break;
              
    case FOLDERVIEW:
              cmp_cr_info = (COMP_CREATE_INFO *)msg->msg_buf;

              printf("\nalias_id %d cont_id %d",cmp_cr_info->alias_id,cmp_cr_info->cntr_id);
              printf("\n x %d y %d width %d height %d",cmp_cr_info->x,cmp_cr_info->y,cmp_cr_info->width,cmp_cr_info->height);
              printf("\ntitle %s",cmp_cr_info->label);

              if(cmp_cr_info->width < MIN_FV_WIDTH)
                cmp_cr_info->width = MIN_FV_WIDTH;

              if(cmp_cr_info->height < MIN_FV_HEIGHT)
                cmp_cr_info->height = MIN_FV_HEIGHT;


               if(cmp_cr_info->cnt_type == WIND_TYPE)
                   parent_id = hfind(pid,WIND_TYPE,cmp_cr_info->cntr_id);
               else
                   parent_id = hfind(pid,FRM_TYPE,cmp_cr_info->cntr_id);

               if(parent_id == -1)
                   return -1;

               if(cmp_cr_info->cnt_type == WIND_TYPE)
                 win_ptr = (window *)lfind(pid,WIND_TYPE,parent_id);
               else
                 frm_ptr = (frame *)lfind(pid,FRM_TYPE,parent_id);

               fv_ptr = (folderview *)kmalloc(sizeof(folderview));

               if(fv_ptr == NULL)
                    return -1;

               id = ladd(pid,COMP_TYPE,(void *)fv_ptr);

               if(id == -1)
               {
                  free((void *)fv_ptr);
                  return -1;
               }

               if(hadd(pid,COMP_TYPE,cmp_cr_info->alias_id,id) == -1)
               {
                   free((void *)fv_ptr);
                   return -1;
               }
               printf("\n p_id %d id %d winptr %x",parent_id,id,fv_ptr);

               if(cmp_cr_info->cnt_type == WIND_TYPE)
               {
                  win_ptr->attachComponent(fv_ptr);
                  fv_ptr->folderview_init(id,   \
                            parent_id, \
                            cmp_cr_info->cnt_type, \
                            (void *)win_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
												    cmp_cr_info->style,			\
                            cmp_cr_info->label  \
                           );/* Here it is equ to dir name */
               }
               else
               {
                  frm_ptr->attachComponent(fv_ptr);
                  fv_ptr->folderview_init(id,   \
                            parent_id,     \
                            cmp_cr_info->cnt_type, \
                            (void *)frm_ptr, \
                            cmp_cr_info->alias_id,\
                            cmp_cr_info->x % SCREEN_WIDTH,cmp_cr_info->y % SCREEN_HEIGHT, \
                            cmp_cr_info->width % SCREEN_WIDTH,   \
                            cmp_cr_info->height % SCREEN_HEIGHT, \
			    cmp_cr_info->style,			\
                            cmp_cr_info->label                    \
                           );

               }

              return 0;
              break;

   case DIALOG :
   		cr_info = (CREATE_INFO *)msg->msg_buf;

              if(cr_info->width < MIN_WIDTH)
                cr_info->width = MIN_WIDTH;

              if(cr_info->height < MIN_HEIGHT)
                cr_info->height = MIN_HEIGHT;

              if(cr_info->cntr_id)
               {
                 parent_id = hfind(pid,WIND_TYPE,cr_info->cntr_id);
                 if(parent_id == -1)
                    return -1;
               }
               else
               {
                 return -1;
               }

                 win_ptr = (window *)kmalloc(sizeof(window));

                 if(win_ptr == NULL)
                    return -1;

                 id = ladd(pid,WIND_TYPE,(void *)win_ptr);

                 if(id == -1)
                 {
                  free((void *)win_ptr);
                  return -1;
                 }

                 if(hadd(pid,WIND_TYPE,cr_info->alias_id,id) == -1)
                 {
                   free((void *)win_ptr);
                   return -1;
                 }
                 printf("\n p_id %d id %d winptr %x",parent_id,id,win_ptr);

                 win_ptr->win_init(id,   \
                            parent_id, \
                            cr_info->x % SCREEN_WIDTH, cr_info->y % SCREEN_HEIGHT, \
                            cr_info->width % SCREEN_WIDTH,   \
                            cr_info->height % SCREEN_HEIGHT, \
                            cr_info->style,                   \
			    1 ,				     \
                            cr_info->title                    \
                           );

                return 0;
		break;
  }
 }

 SDW processShow(MSG *msg)
 {
  SDW ret;
  window *win_ptr;
  window *diag_ptr;
  DW z_in;

  switch(msg->sub_type)
  {
    case WINDOW:
              ret = hfind(msg->from_pid,WIND_TYPE,*(DW *)msg->msg_buf);
              printf("\nSHOW:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;

              win_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,ret);
              win_ptr->style &= ~HIDDEN;

              z_in = z_get_max();
//              ginfo(50,400,itoa(z_in,10));
//              cli();
//              delay(0x9FFF);
//              sti();
              z_enq(msg->from_pid,ret,z_in);
              break;

    case BUTTON:
              break;

    case TEXT:
              break;

    case TEXTAREA:
              break;

    case LIST:
              break;

    case HSCROLLBAR:
              break;

    case VSCROLLBAR:
              break;

    case CHECKBOX:
              break;

    case RADIOBUTTON:
              break;

    case MENU:
              break;

    case TOOLBAR:
              break;

    case FRAME:
              break;

    case ICON:
              break;
    case DIALOG:
              ret = hfind(msg->from_pid,WIND_TYPE,*(DW *)msg->msg_buf);

              if(ret == -1)
                return -1;

              diag_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,ret);
              diag_ptr->style &= ~HIDDEN;

	      win_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,diag_ptr->parent_id);
	      win_ptr->attachDialog(diag_ptr);

              break;

    default:
            return -1;
   }

   repaint();
   return 0;
 }

 SDW processDisable(MSG *msg)
  {
   SDW ret;
   window *win_ptr;
   component *comp_ptr;

   switch(msg->sub_type)
   {
    case WINDOW:
    	      ret = hfind(msg->from_pid,WIND_TYPE,*(DW *)msg->msg_buf);
              printf("\nDEACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;

	      win_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,ret);
              win_ptr->deactivate();
              break;

    case BUTTON:

    case TEXT:

    case TEXTAREA:
	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nDEACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;

	      comp_ptr = (component *)lfind(msg->from_pid,COMP_TYPE,ret);
              comp_ptr->deactivate();
              break;


    case LIST:
              break;

    case HSCROLLBAR:
              break;

    case VSCROLLBAR:
              break;

    case CHECKBOX:
              break;

    case RADIOBUTTON:
              break;

    case MENU:
              break;

    case TOOLBAR:
              break;

    case FRAME:
              break;

    case ICON:
              break;
    case DIALOG:
		break;

    default:
            return -1;
   }

   repaint();
   return 0;
  }

 SDW processEnable(MSG *msg)
  {
   SDW ret;
   window *win_ptr;
   component *comp_ptr;

   switch(msg->sub_type)
   {
    case WINDOW:
    	      ret = hfind(msg->from_pid,WIND_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;

	      win_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,ret);
              win_ptr->activate();
              break;

    case BUTTON:

    case TEXT:

    case TEXTAREA:
	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;

	      comp_ptr = (component *)lfind(msg->from_pid,COMP_TYPE,ret);
              comp_ptr->activate();
              break;


    case LIST:
              break;

    case HSCROLLBAR:
              break;

    case VSCROLLBAR:
              break;

    case CHECKBOX:
              break;

    case RADIOBUTTON:
              break;

    case MENU:
              break;

    case TOOLBAR:
              break;

    case FRAME:
              break;

    case ICON:
              break;

    default:
            return -1;
   }

   repaint();
   return 0;
  }

 SDW processDestroy(MSG *msg)
 {
  SDW ret;
  window *win_ptr;

  switch(msg->sub_type)
  {
    case WINDOW:                                     //alias_id
              ret = hremove(msg->from_pid,WIND_TYPE,*(DW *)msg->msg_buf);

              if(ret == -1)
              {
                return -1;
              }

              win_ptr = (window*)lfind(msg->from_pid,WIND_TYPE,ret);
              win_ptr->freeAll();
              free((void *)win_ptr);

              z_remove(msg->from_pid, ret);

              printf("\nDESTROY:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              break;

    case BUTTON:
              break;

    case TEXT:
              break;

    case TEXTAREA:
              break;

    case LIST:
              break;

    case HSCROLLBAR:
              break;

    case VSCROLLBAR:
              break;

    case CHECKBOX:
              break;

    case RADIOBUTTON:
              break;

    case MENU:
              break;

    case TOOLBAR:
              break;

    case FRAME:
              break;

    case ICON:
              break;
    default:
              return -1;
   }

   repaint();
   return 0;
 }

 SDW processHide(MSG *msg)
 {
  SDW ret;
  DW alias_id = *(DW *)msg->msg_buf;
  window *win_ptr;
  window *diag_ptr;

  switch(msg->sub_type)
  {
    case WINDOW:
              ret = hfind(msg->from_pid,WIND_TYPE,alias_id);
              printf("\nHIDE:WIND (alias_id) %d ret %d",alias_id,ret);

              if(ret == -1)
                return -1;

              z_remove(msg->from_pid,ret);
              win_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,ret);
              win_ptr->style |= HIDDEN;
              break;

    case BUTTON:
              break;

    case TEXT:
              break;

    case TEXTAREA:
              break;

    case LIST:
              break;

    case HSCROLLBAR:
              break;

    case VSCROLLBAR:
              break;

    case CHECKBOX:
              break;

    case RADIOBUTTON:
              break;

    case MENU:
              break;

    case TOOLBAR:
              break;

    case FRAME:
              break;

    case ICON:
              break;
    case DIALOG:
	      ret = hfind(msg->from_pid,WIND_TYPE,*(DW *)msg->msg_buf);

	                    
	       if(ret == -1)
                return -1;

              diag_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,ret);
              diag_ptr->style |= HIDDEN;

	      win_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,diag_ptr->parent_id);
	      win_ptr->detachDialog();

    	      break;
    default:
            return -1;
   }

   repaint();
   return 0;
 }

 SDW processResize(MSG *msg)
 {
  SDW ret;
  window *win_ptr;
  RESIZE_INFO *rs_info;

  switch(msg->sub_type)
  {
    case WINDOW:
              rs_info = (RESIZE_INFO *)msg->msg_buf;

              if(rs_info->width < MIN_WIDTH)
                rs_info->width = MIN_WIDTH;

              if(rs_info->height < MIN_HEIGHT)
                rs_info->height = MIN_HEIGHT;
    
              ret = hfind(msg->from_pid,WIND_TYPE,rs_info->alias_id);
              printf("\nRESIZE:WIND (alias_id) %d ret %d",rs_info->alias_id,ret);

              if(ret == -1)
                return -1;

              win_ptr = (window *)lfind(msg->from_pid,WIND_TYPE,ret);
              win_ptr->x = rs_info->x;
              win_ptr->y = rs_info->y;
              win_ptr->width = rs_info->width;
              win_ptr->height = rs_info->height;
              break;

    case BUTTON:
              break;

    case TEXT:
              break;

    case TEXTAREA:
              break;

    case LIST:
              break;

    case HSCROLLBAR:
              break;

    case VSCROLLBAR:
              break;

    case CHECKBOX:
              break;

    case RADIOBUTTON:
              break;

    case MENU:
              break;

    case TOOLBAR:
              break;

    case FRAME:
              break;

    case ICON:
              break;

    default:
            return -1;
   }

   repaint();
   return 0;
 }
 
//change
 SDW processSet(MSG *msg)
 {
 DD phy;
 SDW ret;
 text *text_ptr;
 textarea *textarea_ptr;
 switch(msg->sub_type)
  {
    case TEXT:
	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;

	      text_ptr = (text *)lfind(msg->from_pid,COMP_TYPE,ret);
	      phy = get_phys(msg->from_pid,*(DD *)(msg->msg_buf + 2));
 	      text_ptr->setText((char *) phy);
              break;

    case TEXTAREA:

	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      textarea_ptr = (textarea *)lfind(msg->from_pid,COMP_TYPE,ret);
	      phy = get_phys(msg->from_pid,*(DD *)(msg->msg_buf + 2));
	      textarea_ptr->setText((char *) phy);
              break;
    default:
            return -1;
  }
    return 0;
 }
 
 SDW processGet(MSG *msg)
 {
 DD phy;
 SDW ret;
 text *text_ptr;
 textarea *textarea_ptr;
 switch(msg->sub_type)
  {
    case TEXT:
	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      text_ptr = (text *)lfind(msg->from_pid,COMP_TYPE,ret);
	      phy = get_phys(msg->from_pid,*(DD *)(msg->msg_buf + 2));

	      text_ptr->getText((char *) phy);

              break;

    case TEXTAREA:

	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      textarea_ptr = (textarea *)lfind(msg->from_pid,COMP_TYPE,ret);
	      phy = get_phys(msg->from_pid,*(DD *)(msg->msg_buf + 2));

	      textarea_ptr->getText((char *) phy);
              break;
    default:
            return -1;
  }
    return 0;

 }

 SDW processCopy(MSG *msg)
 {
 SDW ret;
 text *text_ptr;
 textarea *textarea_ptr;
 switch(msg->sub_type)
  {
    case TEXT:
	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      text_ptr = (text *)lfind(msg->from_pid,COMP_TYPE,ret);
	      text_ptr->copy();

              break;

    case TEXTAREA:

	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      textarea_ptr = (textarea *)lfind(msg->from_pid,COMP_TYPE,ret);
	      textarea_ptr->copy();
              break;
    default:
            return -1;
  }
    return 0;
 }
 
 SDW processCut(MSG *msg)
 {
 SDW ret;
 text *text_ptr;
 textarea *textarea_ptr;
 switch(msg->sub_type)
  {
    case TEXT:
	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      text_ptr = (text *)lfind(msg->from_pid,COMP_TYPE,ret);
	      text_ptr->cut();

              break;

    case TEXTAREA:

	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      textarea_ptr = (textarea *)lfind(msg->from_pid,COMP_TYPE,ret);
	      textarea_ptr->cut();
              break;
    default:
            return -1;
  }
    return 0;
 }
 
 SDW processPaste(MSG *msg)
 {
 SDW ret;
 text *text_ptr;
 textarea *textarea_ptr;
 switch(msg->sub_type)
  {
    case TEXT:
	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      text_ptr = (text *)lfind(msg->from_pid,COMP_TYPE,ret);
	      text_ptr->paste();

              break;

    case TEXTAREA:

	      ret = hfind(msg->from_pid,COMP_TYPE,*(DW *)msg->msg_buf);
              printf("\nACTIVATE:WIND (alias_id) %d ret %d",*(DW *)msg->msg_buf,ret);

              if(ret == -1)
                return -1;


	      textarea_ptr = (textarea *)lfind(msg->from_pid,COMP_TYPE,ret);
	      textarea_ptr->paste();
              break;
    default:
            return -1;
  }
    return 0;

 }

 void repaint()
 {
   DW i, j;
   window *win;

   cli();
   drawDesktop();

   printf("repaint()");

   for(i=0 ; i < z_endptr ; i++)
     {
        win = (window*)lfind(zorder[i].pid,WIND_TYPE,zorder[i].window_id);
        win->paint_win();

        //Setting the topmost visible window
        if(!(win->style & W_MINIMIZE))
          focus = win;
     }

    drawTaskbar();

    if(mouse_inited)
    {
      getimage(mcurx,mcury,16,16, &mouseimg[0][0]);

	    for(i = mcurx ; i < mcurx+16 ; i++)
	    {
	      for(j = mcury ; j < mcury+16 ; j++)
	      {
	        if(mouseptr[j-mcury][i-mcurx])
	        {
	          setPixel(i,j,0x0);
	        }
	      }
	    }
	    	    
    }
     
    mvBuf2Svga();
 }

  SDW processMouse(MSG *msg)
  {
    ENTITY en;
    DW x, y, status;
    MSG msg1;

//    charrect(300,SCREEN_HEIGHT,100,20,'M');

    x = *(DW*)(msg->msg_buf);
    y = *(DW*)(msg->msg_buf+2);
    status = *(DW *)(msg->msg_buf+4);

//    rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
//    ginfo(100,100,itoa(status,10));
//    setPixel(x,y,0xF800);

    printf("\nValue x : %d y : %d",x,y);
    printf("\n mcurx %d mcury %d",mcurx,mcury);

    csr.hide();

    if(status & CLICK)
    {
			clamped = (window*)NULL;
			clamp_x = 0;
			clamp_y = 0;
	    en = findEntity(x,y);
//	    ginfo(10,10,"CLICKED");
		}
    else if(status & MOVE)
    {
			if(clamped != NULL && clamp_x != 0 && clamp_y != 0)
			{
				clamped->move(x - clamp_x, y - clamp_y);
				clamp_x = x;
				clamp_y = y;
			}
		}


    if(en.type != NO_TYPE)
    {
     msg1.type     = WM_CLICKED;
     msg1.sub_type = en.type;
     msg1.length   = sizeof(DD) + 4;
     *(DW*)msg1.msg_buf = en.alias_id;

     asm("pushl %0"::"r"(&msg1));
     asm("pushl %0"::"r"((DD)en.pid));
     asm("int $0x30"::"a"(3));
    }

    return 0;
  }

  SDW processKBD(MSG *msg)
  {
    if(focus == NULL)
    {
//      ginfo(300,350,"NULL focus");
    }
    else
    {
//      ginfo(300,350,focus->title);
      focus->keyPress(*((DW *)msg->msg_buf),*((DW *) msg->msg_buf+1));
    }
    return 0;
  }

  ENTITY findEntity(DW x,DW y)
  {
    SDW i;
    DW _x, _y, _width, _height;
    window * win_ptr;
    window * par_ptr;
    ENTITY en;
    DW width_max = 100;
    DB num_of_tasks;
    DW tskWidth, tskHeight, tskOffset = 10;
    MSG msg;
    DW min,min_p,j;
    SDW cur_min = -1;
    SDW emb_id;
    DW diag_pres = 0;

    en.type = NO_TYPE;

		//Just do MenuHandling
		if(focus != NULL)
		{
		    if(focus->processMenu(x,y) == 0)
		    	return en;
    }


    if(processStartMenu(x,y) == 0)
      return en;

  	  //Taskbar Handling
	    if(iswithin(x,y,0,SCREEN_HEIGHT,TASKBAR_WIDTH,TASKBAR_HEIGHT))
      {
			 //change
       if(iswithin(x,y,SCREEN_WIDTH-TIME_X-105,SCREEN_HEIGHT + TIME_Y,TIME_WIDTH,TIME_HEIGHT))
			 {
				  __asm__ __volatile__("pushl %%eax"::"a"("\\timeset"));
		   	  __asm__ __volatile__("movl $0x1, %eax");
          __asm__ __volatile__("int $0x30");
				  en.type = NO_TYPE;
				  return en;
			 }

        num_of_tasks = z_endptr;
				//change TIME_WIDTH
        if(num_of_tasks != 0)
        {
         tskWidth = (TASKBAR_WIDTH - START_WIDTH - TIME_WIDTH) / num_of_tasks;
        }
        else
        {
         en.type = NO_TYPE;
         return en;
        }

        if(tskWidth > width_max)
         tskWidth = width_max;

        tskHeight = TASKBAR_HEIGHT - 10;

      	emb_id = MAX_PROC * WINDOW_MAX;

      	for(i= num_of_tasks-1 ; i >= 0 ; i--)
       	{
      		win_ptr = (window*)lfind(zorder[i].pid,WIND_TYPE,zorder[i].window_id);
      		if(!(win_ptr->style & W_MINIMIZE))
      			break;
      	}

      	emb_id = i;

        for(i = 0 ; i < num_of_tasks ; i++)
        {
         min = MAX_PROC * WINDOW_MAX;

         for(j = 0 ; j < num_of_tasks ; j++)
         {
          if(zorder[j].task_id <= min && zorder[j].task_id > cur_min)
          {
           min = zorder[j].task_id;
           min_p = j;
          }
         }

         cur_min = min;

         if(iswithin(x,y,START_WIDTH + i*tskWidth + tskOffset, SCREEN_HEIGHT + 5, tskWidth - tskOffset + 5, tskHeight))
          {
            win_ptr = (window*)lfind(zorder[min_p].pid,WIND_TYPE,zorder[min_p].window_id);


            if(win_ptr->style & W_MINIMIZE)
            {
              win_ptr->style &= ~W_MINIMIZE;
            }

            if(emb_id == min_p)
            {
              win_ptr->style |= W_MINIMIZE;
            }

            z_moveTop(zorder[min_p].pid,zorder[min_p].window_id);

            repaint();
            en.type = NO_TYPE;
            return en;
          }
        }
      }// for taskbar if

    // ginfo(300,80,"Window Detection");

    for(i = z_endptr-1; i>= 0;i--)
     {
      // ginfo(300,90+i*10,itoa(i,10));
	diag_pres = 0;
      win_ptr = (window *)lfind(zorder[i].pid,WIND_TYPE,zorder[i].window_id);

      if(win_ptr->style & W_MINIMIZE)
        continue;

      if(win_ptr->diag != NULL)
      {
        par_ptr = win_ptr;
    	win_ptr = win_ptr->diag;
	diag_pres = 1;
      }

         if(win_ptr->style & W_MAXIMIZE)
         {
             _x = 0;
             _y = 0;
             _width = SCREEN_WIDTH;
             _height = SCREEN_HEIGHT;
         }
         else
         {
             _x = win_ptr->x;
             _y = win_ptr->y;
             _width = win_ptr->width;
             _height = win_ptr->height;
         }


      //Check For the window
      if(iswithin(x,y,_x,_y,_width,_height))
      {
				//change
        if(win_ptr->style & W_DISABLED)
				return en;
        // ginfo(400,10,"z_MT");

				//Check For Menu - Yea for the second time to open hidden menus
	      if(iswithin(x,y,_x,_y + TITLE_HEIGHT,_width,_height + MENUBAR_HEIGHT))
	      {
				 win_ptr->paint_win();
				 win_ptr->processMenu(x,y);
				}


        //Check for TITLE bar
        if(iswithin(x,y,_x,_y,_width,TITLE_HEIGHT))
        {
	 if(diag_pres == 0)
	 {
          //Minimize
          if(iswithin(x,y,_x+_width-3*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12))
          {
            z_moveTop(zorder[i].pid,zorder[i].window_id);
              win_ptr->style |= W_MINIMIZE;
            emboss3D(_x+_width-3*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,0,_true,2);
            mvMini2Svga(_x+_width-3*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12);
//              win_ptr->style &= ~W_MAXIMIZE;

              repaint();
              en.type = NO_TYPE;
              return en;
          }

          //Maximize
          if(iswithin(x,y,_x+_width-2*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12))
          {
						//change
					  if(win_ptr->style & W_NORESIZE)
							return en;

              z_moveTop(zorder[i].pid,zorder[i].window_id);

              //Remove MINIMIZED val
              if(win_ptr->style & W_MAXIMIZE)
              {
                win_ptr->style &= ~W_MAXIMIZE;
              }
              else
              {
                win_ptr->style |= W_MAXIMIZE;
              }

            emboss3D(_x+_width-2*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,0,_true,2);
            mvMini2Svga(_x+_width-2*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12);

//              win_ptr->style &= ~W_MINIMIZE;

              repaint();
              en.type = NO_TYPE;
              return en;
          }
	 }
          //Close
          if(iswithin(x,y,_x+_width-1*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12))
          {
	      if(diag_pres == 0)
	      {
              //Send Msg to Process
              msg.length = sizeof(DW);
              msg.type   = WM_DESTROY;
              msg.sub_type = WINDOW;
              *(DW *)msg.msg_buf = afind(zorder[i].pid,WIND_TYPE,zorder[i].window_id);
              asm("pushl %0"::"r"(&msg));
              asm("pushl %0"::"r"((DD)zorder[i].pid));
              asm("int $0x30"::"a"(3));


              win_ptr->freeAll();
              free(win_ptr);

              lremove(zorder[i].pid,WIND_TYPE,zorder[i].window_id);
              hremove(zorder[i].pid,WIND_TYPE,zorder[i].window_id);
              z_remove(zorder[i].pid,zorder[i].window_id);
	      }
	      else
	       {
		 par_ptr->detachDialog();
		 ginfo(300,400,"diag close");
	       }

              emboss3D(_x+_width-1*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12,0,_true,2);
              mvMini2Svga(_x+_width-1*14 - BORDER_WIDTH,_y+BORDER_HEIGHT+3,12,12);

              repaint();
              en.type = NO_TYPE;
              return en;
          }
          else //This means it is just a title CLICK
          {
						clamped = win_ptr;
						clamp_x = x;
						clamp_y = y;
//						restoreImage(mcurx,mcury);
					}

        }//if TITLE CONTROLS


           if(!(win_ptr->style & W_DISABLED))
           {
             en = win_ptr->findEntity(x,y);
             en.pid = zorder[i].pid;
           }

           z_moveTop(zorder[i].pid,zorder[i].window_id);

           // ginfo(300,120,"About to REPAINT");

           repaint();
//           en.type = NO_TYPE; //Send Right Component id
           return en;

      }// if(iswithin(x,y,_x,_y,_width,_height))

     }//  for(i = z_endptr-1; i>= 0;i--)


  }

  SDB processStartMenu(DW x,DW y)
  {
    SDB ret;
    ret = sm->processClick(x,y);
    mvBuf2Svga();
    return ret;
  }

  void drawDesktop()
  {
   //Add Desktop icons
   setScreen(SCREEN_COLOR);
  }

  void drawTaskbar()
  {
    DB num_of_tasks;
    DW tskWidth = 0, tskHeight, tskOffset = 10;
    window *win_ptr;
    DW min,min_p,j;
    SDW i;
    char temp[20];
    SDW cur_min = -1;
    DW width_max = 100;
    SDW emb_id;

    //Taskbar Base
    fillrect(0,TOTAL_HEIGHT - TASKBAR_HEIGHT,TASKBAR_WIDTH,TASKBAR_HEIGHT,TASKBAR_COLOR);

    emboss3D(0,TOTAL_HEIGHT - TASKBAR_HEIGHT,TASKBAR_WIDTH,TASKBAR_HEIGHT,TOP | RIGHT,_false,3);

    //Start Button
    fillrect(START_X,SCREEN_HEIGHT + START_Y,START_WIDTH,START_HEIGHT,0xDEAD);
    drawstring(START_X+15,SCREEN_HEIGHT + START_Y + 10,"START");
    emboss3D(START_X,SCREEN_HEIGHT + START_Y,START_WIDTH,START_HEIGHT,0,_false,2);

    num_of_tasks = z_endptr;
//change
    if(num_of_tasks != 0)
      tskWidth = (TASKBAR_WIDTH - START_WIDTH - TIME_WIDTH) / num_of_tasks;

    if(tskWidth > width_max)
      tskWidth = width_max;

    tskHeight = TASKBAR_HEIGHT - 10;

  	emb_id = MAX_PROC * WINDOW_MAX;

  	for(i= num_of_tasks-1 ; i >= 0 ; i--)
  	{
  		win_ptr = (window*)lfind(zorder[i].pid,WIND_TYPE,zorder[i].window_id);
  		if(!(win_ptr->style & W_MINIMIZE))
  			break;
  	}

  	emb_id = i;

    cur_min = -1;

    for(i = 0 ; i < num_of_tasks ; i++)
    {
      min = MAX_PROC * WINDOW_MAX;

      for(j = 0 ; j < num_of_tasks ; j++)
      {
       if(zorder[j].task_id <= min && zorder[j].task_id > cur_min)
       {
        min = zorder[j].task_id;
        min_p = j;

//        ginfo(50+j*7,420,itoa(min,10));
//        ginfo(50+j*7,430,itoa(min_p,10));
       }
      }
      cur_min = min;

      win_ptr = (window*)lfind(zorder[min_p].pid,WIND_TYPE,zorder[min_p].window_id);

//    if(i == num_of_tasks - 1 && num_of_tasks != 1 && win_dptr->style & W_MINIMIZE)
      if(min_p == emb_id) //      if(!(win_ptr->style & W_MINIMIZE))
      {
          fillrect(START_WIDTH + i*tskWidth + tskOffset, SCREEN_HEIGHT + 5, tskWidth - tskOffset + 5, tskHeight, TASK_AC_COLOR);
          emboss3D(START_WIDTH + i*tskWidth + tskOffset, SCREEN_HEIGHT + 5, tskWidth - tskOffset + 5, tskHeight,0,_true,2);
      }
      else
      {
          fillrect(START_WIDTH + i*tskWidth + tskOffset, SCREEN_HEIGHT + 5, tskWidth - tskOffset + 5, tskHeight, TASK_INAC_COLOR);
          emboss3D(START_WIDTH + i*tskWidth + tskOffset, SCREEN_HEIGHT + 5, tskWidth - tskOffset + 5, tskHeight,0,_false,2);
      }
//Change
      drawstring(START_WIDTH + i*tskWidth + tskOffset + 5, SCREEN_HEIGHT + 10, (char *)strmncpy(temp,win_ptr->title,0,((tskWidth - tskOffset + 5)/7) - 1));

     }
//change
     draw_time(0);
  }
//change
  void draw_time(DB flush)
   {
     TIME t;
     DATE d;
     char dt[20];

     if(!graphics)
      return;

     gettime(&t);
     getdate(&d);

     if(d.dd < 10)
      {
       strcpy(dt,"0");
       strcat(dt,itoa(d.dd,10));
      }
     else
      {
       strcpy(dt,itoa(d.dd,10));
      }
     strcat(dt,"/");
     if(d.mm < 10)
      strcat(dt,"0");
     strcat(dt,itoa(d.mm,10));
     strcat(dt,"/");
     if(d.yy < 10)
      strcat(dt,"0");
     strcat(dt,itoa(d.yy,10));
     strcat(dt," ");
     if(t.hour < 10)
      strcat(dt,"0");
     strcat(dt,itoa(t.hour,10));
     strcat(dt,":");
     if(t.min < 10)
      strcat(dt,"0");
     strcat(dt,itoa(t.min,10));
/*     strcat(dt,":");
     strcat(dt,itoa(t.sec,10));*/

     fillrect(SCREEN_WIDTH-TIME_X-105,SCREEN_HEIGHT + TIME_Y,TIME_WIDTH-2,TIME_HEIGHT,0xDEAD);
     drawstring(SCREEN_WIDTH-TIME_X-100,SCREEN_HEIGHT + TIME_Y + 10,dt);
     emboss3D(SCREEN_WIDTH-TIME_X-105,SCREEN_HEIGHT + TIME_Y,TIME_WIDTH-2,TIME_HEIGHT,0,_false,2);

     if(flush)
      {
       //mvBuf2Svga();
       mvMini2Svga(SCREEN_WIDTH-TIME_X-110,SCREEN_HEIGHT + TIME_Y,TIME_WIDTH,TIME_HEIGHT);
      }

   }
//change
 void destroy_win(DW pid)
  {
   lremoveAll(pid);
   z_removeAll(pid);
   hremoveAll(pid);
   repaint();
  }

  void sys_init_info()
  {
    DB i,j;

    char *sys[] = { \
    "DYNACUBE 1.0 LOADING",\
    "---------------------------------",\
    "DISABLING HARDWARE INTERRUPTS................",\
    "SYSTEM DESCRIPTORS LOADED ..............",\
    "PROGRAMMABLE INTERRUPT CONTROLLER (PIC) REMAPPED ................",\
    "TASK STUCTURES INITIALIZED .............",\
    "PROCESS STUCTURES INITIALIZED .............",\
    "SYSTEM QUEUES INITIALIZED .............",\
    "GUI ZORDER INITIALIZED .............",\
    "SYSTEM HASHTABLES INITIALIZED .............",\
    "SYSTEM LISTS INITIALIZED .............",\
    "RETRIEVING SVGA INFO .............",\
    "PS/2 KEYBOARD INITIALIZED .............",\
    "PS/2 MOUSE INITIALIZED .............",\
    "SYSTEM MEMORY STRUCTURES INITIALIZED .............",\
    "FORKING NULL PROCESS .............",\
    "STARTING GUI SERVER ................",\
    "STARTING FLOPPY SERVER ................",\
    "STARTING FILE SERVER SERVER ................",\
    "SYSTEM MEMORY STRUCTURES INITIALIZED .............",\
    "SYSTEM TIMER INITIALIZED .............", \
    "TIMER IRQ ENABLED .............", \
    "KEYBOARD IRQ ENABLED .............", \
    "PS/2 MOUSE IRQ ENABLED .............", \
    "FLOPPY IRQ ENABLED .............", \
    "ENABLING HARDWARE INTERRUPTS................",\
    "ABOUT TO START ................",\
    ""};

    for(i = 0,j = 0 ; i < sizeof(sys)/sizeof(char*) ; i++,j++)
    {
      if((i+1) % (SCREEN_HEIGHT/20) == 0)
      {
        j = 0;
        setScreen(0x0);
      }
      cprint(20,(j+1)*20,sys[i],0x7E0);
		  mvBuf2Svga();
//      delay(0x5FFF);
    }
//    delay(0x9FFF);
  }    
