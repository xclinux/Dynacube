/***************************************************************************
                          mm.c  -  description
                             -------------------
    begin                : Sat Dec 27 2003
    copyright            : (C) 2003 by Dynacube Team
    email                : mdshah82@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

 #include "mm.h"
 #include "kerror.h"
 #include "ktypes.h"
 #include "kasm.h"
 #include "stdlib.h"
 #include "svga.h"
 

 DD _pgde[1024] __attribute__((aligned (_4KB)));
 DD _pgte[MAX_PROC][1024] __attribute__((aligned (_4KB)));
 DD _kpgde[1024] __attribute__((aligned (_4KB)));
 DD _kpgte[PHYS_MEM/_4MB][1024] __attribute__((aligned (_4KB))); //PHYS_MEM/4Mb

 DD _svgapgte[1024] __attribute__((aligned (_4KB))); //PHYS_MEM/4Mb
 DD frmlist[PHYS_MEM/(0x20*_4KB)] = {0}; //Each Byte contains 8 pages

 void mm_init()
 {
	 /* Assumptions PHYS_MEM is a multiple of _4MB
	 		Don't do anything to _kpgde and _kpgte as they should
	    do 1-to-1 linear-to-physical mapping.
	 */
	 
	 DD i = 0, j = 0;
   DD cr0 = 0, cr3 = 0 ;
	 int *p;
   

	 //Page
   printf(" PHYS_MEM/_4MB %d %x\n", PHYS_MEM/_4MB, PHYS_MEM/_4MB);
   
	 for(i=0;i< PHYS_MEM/_4MB;i++)
	 {
  	 _kpgde[i] = (DD)_kpgte[i] | 3;
   }

   //Directories that do not point to valid Memory  
   for(i= PHYS_MEM/_4MB ; i < 1024 ; i++)
   {
     _kpgde[i] |= 0;
   }

   //To get sufficient Pg Dir Entries even when KERNEL_SIZE != m * _4MB
   //Kernel Mapping - Priviliege Level 0 - Highest
   for(i=0; i<(KERNEL_SIZE/_4MB)+((KERNEL_SIZE%_4MB)?1:0); i++)
   {
  	 _pgde[i] = (DD)_kpgte[i] | 3;
   }
  
	 for(i=(KERNEL_SIZE/_4MB)+((KERNEL_SIZE%_4MB)?1:0) ; i < (PHYS_MEM/_4MB) ; i++)
	 {
			_pgde[i] |=  3;
	 }

	 //Page Table Init
   for(i=0; i < (PHYS_MEM/_4MB) ;i++) //Each DirEnt contains 4Mb
   {
	  for(j=0 ; j < 1024 ; j++) //1024 pg table entries
  	{
				_kpgte[i][j] = i<<22 | j<<12 | 3;
    }
   }

   if(vbe_mode.PhysBasePtr)
     map_linear(vbe_mode.PhysBasePtr);//0xD0000000); //vbe_mode.PhysBasePtr
   //Setting for linear frame buffer of SVGA

  
  getCR0(cr0);
	cr0 |= (1<<31); // | (1 << 1) | (1 << 5); // MP bit for FPU init
  getCR3(cr3);	
	cr3 = (cr3 & 0xFFF) | (((DD)_kpgde) & 0xFFFFF000);
	
  setCR3(cr3);
  setCR0(cr0);
    
  printf("\nPAGING enabled");
 }
 
 DD pindex = 0;

 SDD findpage()
 {
	 DD tindex = 0, and = 0, freebyte = 0, freenibble = 0;	 
	 DB i = 0,j = 0;

    
   //printf("\npin %d tin %d fr %b",pindex,tindex,frmlist[pindex]);
	 tindex = pindex;
	 
	 while((frmlist[pindex] & 0xFFFFFFFF) == 0xFFFFFFFF)
	 {
		 	pindex++;
		  pindex %= (NUM_PAGES/32);
		  
      //printf("\nInside loop pindex %d tindex %d",pindex,tindex);
   
		  if(pindex == tindex) //No Free pages
		  	 return PAGE_NOT_FOUND;
	 }

    for(i = 0 ; i < 4 ; i++)
    {
			and = 0xFF<<(i*8);

			//printf("\tand %x",and);
			
			if( (freebyte=(frmlist[pindex] & and)) != and ) //We have a free page here
			{
				//printf("fb %x",freebyte);

				freebyte >>= (i*8);
				
				if( (freenibble=(freebyte & 0xF)) != 0xF )
				{
					for(j = 0 ; j < 4 ; j++)
					{
						if(!(freenibble & 0x1))
						{
							frmlist[pindex] |= (1<<(i*8+j));
							return pindex * 32 + i * 8 + j;
						}
						else
						{
							freenibble>>=1;
						}
					}					
				}
				else
				{
					freenibble = (freebyte >> 4);
					
					for(j = 0 ; j < 4 ; j++)
					{
						if(!(freenibble & 0x1))
						{
							frmlist[pindex] |= (1<<(i*8+j+4));
							return pindex * 32 + i * 8 + j+4;
						}
						else
						{
							freenibble>>=1;
						}
					}
															
				}//else
								
			}//if( (freebyte=(frmlist[pindex] & and)) != and ) //We have a free page here
			
		}//for
		
 }// DD findpage()


  void freepage(DD index)
  {
     
		frmlist[index/32] ^= (1<<index%32);
		
	}//void freepage(DD index)

  DD lin_to_phy(SDW pid, DD linear_addr)
  {
   DW dirent, tabent, offset;
   DD *ptr;

   dirent = linear_addr >> 22; //10bits
   tabent = (linear_addr >> 12) & 0x3FF ; //10bits
   offset = (linear_addr & 0xFFF); //12 bits

//   printf("\nlin_addr %b",linear_addr);
//   printf("\nlin_addr %x DE %d TE %d OE %d",linear_addr,dirent,tabent,offset);
//
//   printf("\nbase _kde %x _kpte %x",(_kpgde[dirent] & 0xFFFFF000),_kpgte[2][256]);

   if(pid == KERNEL_PID || pid == GUI_PID || pid == FLOPPY_PID || pid == FS_PID) // || pid == GUI_PID
   {
    ptr = (DD *)(_kpgde[dirent] & 0xFFFFF000);
   }

   else
   {
    ptr = (DD *)(_pgde[dirent] & 0xFFFFF000);
	 }
	 
   return (((DD)*(ptr+tabent)) & 0xFFFFF000)|offset;
  }

  DD logi_to_lin(SDW pid ,DW seg_sel, DD offset)

  {
		SEG_DESC tmp;
		
		if((seg_sel & 0x1) == 0) // || pid == GUI_PID
		{
			getDesc(seg_sel>>3,&tmp);
		}
		else
		{
			tmp = _ldte[pid][seg_sel>>3];
		}

//		printDESC(&tmp);
		
		return (tmp.base_24_31<<24|tmp.base_16_23<<16|tmp.base_0_15)+offset;
		
	}

 void phys_mem_copy(DW pid_s,void * src,DW pid_d,void *dest,DD size)
  {
    DW seg;
    DD linear, phy_s,phy_d;

    linear = logi_to_lin(pid_s,_proc[pid_s].cs,(DD)src);
    phy_s = lin_to_phy(pid_s,linear);
    
    linear = logi_to_lin(pid_d,_proc[pid_d].cs,(DD)dest);
    phy_d = lin_to_phy(pid_d,linear);

    memcpy((void *) phy_d, (void *) phy_s,size);

  }

 struct MHEADER base = {0,0};
 struct MHEADER *freep = NULL;

 void *kmalloc(size_t nbytes)
  {
    struct MHEADER *p,*prevp;
    DD nunits;
    DD fp;

    nunits = (nbytes + sizeof(struct MHEADER)-1)/sizeof(struct MHEADER) +1;
    if((prevp = freep) == NULL)
    {
      base.ptr = freep = prevp = &base;
      base.size = 0;
    }
    for(p = prevp->ptr; ; prevp=p, p=p->ptr)
    {
      if(p->size >= nunits)
      {
       if(p->size == nunits)
          {
            prevp->ptr = p->ptr;
          }          
       else
        {
          p->size -= nunits;
          p += p->size;
          p->size = nunits;
        }   
       freep = prevp;
       return (void *)(p+1);          
      }
      if(p == freep)
      {
        if((fp = findpage()) != PAGE_NOT_FOUND)
        {
          p = KERNEL_SIZE + fp * _4KB;
          p->size = _4KB/sizeof(struct MHEADER);
          free((void *)(p+1));
          p = freep;
        }        
        else
          return NULL;        
      }
    }          
  }

  void free(void *ap)
  {
    struct MHEADER *bp,*p;

    bp = (struct MHEADER *)ap -1;
    for(p=freep; !(bp >p && bp < p->ptr); p =p->ptr)
      if(p >= p->ptr && (bp > p || bp < p->ptr))
        break;

    if(bp + bp->size == p->ptr)
      {
        bp->size += p->ptr->size;
        bp->ptr = p->ptr->ptr;
      }
    else
      bp->ptr = p->ptr;

    if(p + p->size ==  bp)
    {
       p->size += bp->size;
       p->ptr  = bp->ptr;
    }
    else
      p->ptr = bp;
      
    freep = p;     
 }    

 void map_linear(DD addr)
 {
   DD dir;
   DD i;
   DD phys;
   
   dir = addr >> 22;
   _kpgde[dir] = (DD)(& _svgapgte[0]) | 3;
   cls();
  
   for(i=0;i<1024 ;i++)  // 1MB frame buffer
    {
      _svgapgte[i] = (dir<<22) | (i<<12) | 3;
    }
 }
//change
 DD get_phys(DW pid,DD ptr)
  {
   DD linear,phy;
   linear = logi_to_lin(pid,_proc[pid].ss,ptr);
   phy = lin_to_phy(pid,linear);
   return phy;
  }







