/***************************************************************************
                          message.c  -  description
                             -------------------
    begin                : Thu Jan 22 2004
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

 #include "message.h"
 #include "proc.h"
 #include "kint.h"

 DB _msg[MAX_PROC][MAX_Q];
  
 SDW send(DW pid,MSG *msg)
  {
    DW seg;
    DD linear, phy;
    MSG *m;

    if(_proc[pid].avl == _true)
      return -1;

    linear = logi_to_lin(cur_pid,_proc[cur_pid].cs,(DD)msg);
    phy = lin_to_phy(cur_pid,linear);

    m = (MSG *) phy;
    m->from_pid = cur_pid;
    printf("\nsend %d %d %x",pid,cur_pid,phy);
    printf("\nAfter Send");

    if(_proc[pid].msg_q_delim + m->length + 10 >= MAX_Q)
      return -1;
  
    if(remove(&message_q,pid) == 0) //!= E_FAILURE
     {        
      memcpy((void *)_proc[pid].recv_addr,(void *)m,m->length+10); // other fields in header 3*DW + DD
      printf("\nremove msg %s",((MSG *)_proc[pid].recv_addr)->msg_buf);
      enq(&ready_q,pid);
     }
    else
     { 
       memcpy((void *)((DB *)_msg[pid] + _proc[pid].msg_q_delim),(void *)m,m->length+10); // other fields in header 3*DW + DD  
       printf("\nmessage %s delim %d %d",((MSG *)((DB*)_msg[pid]+ _proc[pid].msg_q_delim))->msg_buf,_proc[pid].msg_q_delim,((MSG *)_msg[pid])->length);
       _proc[pid].msg_q_delim = _proc[pid].msg_q_delim + m->length + 10;
     }
    return 0;    
  }
  
 SDW recv(MSG *msg)
  {
    DW seg;
    DD linear, phy;
    MSG *dest_m,*src_m;
  	DD i;

    linear = logi_to_lin(cur_pid,_proc[cur_pid].cs,(DD)msg);
	  phy = lin_to_phy(cur_pid,linear);
    dest_m = (MSG *) phy;

    cls();
    if(_proc[cur_pid].msg_q_delim != 0)
     {
      src_m = (MSG *)(_msg[cur_pid]);
      memcpy((void *)dest_m,(void *)src_m,src_m->length+10); // other fields in header 3*DW + DD
  	  printf("\nrecv %d %s delin %d %d",cur_pid,dest_m->msg_buf,_proc[cur_pid].msg_q_delim,src_m->length);
      for(i=0;i <_proc[cur_pid].msg_q_delim - dest_m->length -10;i++)   //i<dest_m->length+10 &&
	    {
  		_msg[cur_pid][i] = _msg[cur_pid][i+dest_m->length + 10];
	    }
   	  _proc[cur_pid].msg_q_delim = _proc[cur_pid].msg_q_delim - dest_m->length - 10;
     }
    else
     {
      remove(&ready_q,cur_pid); 
      enq(&message_q,cur_pid);
//      printf("\nfirst_element :%d",get_first(&message_q));
      _proc[cur_pid].recv_addr = phy;
      printf("\nQueueing ptr %d %d %d",message_q.front,message_q.end,message_q.n);
//      printf("\nREADY Q");
//      printQ(&ready_q);
      printf("\nMSG Q");      
      printQ(&message_q);      
     }      
  }

  
  SDW ksend(DW pid, MSG *m)
  {
   //Used only by Kernel & its DevDrivs
    m->from_pid = KERNEL_PID;

    printf("\n In ksend ");
    printf("\nKERNEL PID %x",m->from_pid);
//    delay(0x3FFF);

    if(_proc[pid].msg_q_delim + m->length + 10 >= MAX_Q)
      return -1;
      
    if(remove(&message_q,pid) == 0) //!= E_FAILURE
     {
//      fillrect(5,5,50,50,0x0000);       
      memcpy((void *)_proc[pid].recv_addr,(void *)m,m->length+10); // other fields in header 3*DW + DD
//      printf("\nremove msg %s",((MSG *)_proc[pid].recv_addr)->msg_buf);
      enq(&ready_q,pid);
     }
    else
     {
//       fillrect(25,25,50,50,0x5555);       
       memcpy((void *)((DB *)_msg[pid] + _proc[pid].msg_q_delim),(void *)m,m->length+10); // other fields in header 3*DW + DD
//       printf("\nmessage %s delim %d %d",((MSG *)((DB*)_msg[pid]+ _proc[pid].msg_q_delim))->msg_buf,_proc[pid].msg_q_delim,((MSG *)_msg[pid])->length);
       _proc[pid].msg_q_delim = _proc[pid].msg_q_delim + m->length + 10;
     }

    return;    
  }
