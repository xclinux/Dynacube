#define FLOPPY_1

#ifdef FLOPPY_2

#include "floppy.h"
#include "message.h"
#include "device.h"
#include "queue.h"
#include "kpic.h"
#include "kint.h"
char f_results[MAX_RESULTS];
int no_sectors = 18;
int no_tracks = 80;
int rate = 300;
int motor_status = 0;
int motorgoal;
int need_reset = FALSE;
int f_intr = 0;
int l_base = 0;
int no_blocks = 2880;
int size = 2880 << SECTOR_SHIFT;
int steps_per_cyl = 1;
int no_heads = 2;
int gap = 0x1b;
request freqs[MAX_FL_REQ];
int fr_req = 0;
volatile int no_req = 0;
int en_req = 0;
int tmp;
unsigned char dma_buf[512] __attribute__((aligned (_4KB)));
struct floppy fp;
void fdc_out(int val)
{
  int i =0;
  if (need_reset) return;
  while ((inb(FDC_STATUS) & (MASTER | DIRECTION)) != (MASTER | 0)) {
if (i>= 1000) {
need_reset = TRUE;
return;
}
i++;
  }
  outb(FDC_DATA, val);
}
int startmotor()
 {
   int running;
   motorgoal = 0x1;
   running = motor_status & motorgoal;
   if(!running)
    {
    cli();
    floppy_int_pending = 0;
    outb(DOR,1 << 4 | ENABLE_DMA);
    wait_for_intr();
    sti();
//    cli();
//    printf("\nreturn : %d",tmp);
//     delay(0xFFFF);
//    sti();
    }
    printf("Motor Started\n");
   //sleep(TIME_OUT);
//    wait_for_intr();
   motor_status = motorgoal;
   return 0;
 }
void stopmotor()
 {
    motorgoal = 0;
    if(motor_status != motorgoal)
    {
     printf("stoping motor\n");
     cli();
     floppy_int_pending = 0;
     outb(DOR,0 << 4 | ENABLE_DMA);
     motor_status = motorgoal;
//     wait_for_intr();
     sti();
    }
 }
void dma_setup(request *req)
 {
    int r_or_w,i;
    short page;
    unsigned long offs;
    page=(long)((DD)dma_buf>>16);
    offs =(short)((DD)dma_buf & 0xffff);
    if(req->opcode == 1)
     r_or_w = DMA_READ;
    else
     r_or_w = DMA_WRITE;
    outb(DMA_INIT, DMA_RESET_VAL);
    outb(DMA_FLIPFLOP, 0);
    outb(DMA_MODE, r_or_w);
    outb(DMA_ADDR,  offs & 0xff);
    outb(DMA_ADDR, ( offs >>  8) & 0xff);
    outb(DMA_TOP, page);
    outb(DMA_COUNT, (req->r_count - 1) >> 0);
    outb(DMA_COUNT, (req->r_count - 1) >> 8);
    outb(DMA_INIT, 2);
 }
int do_transfer(request *req)
  {
     int r, s;
     if (fp.fl_calibration == FALSE) return(ERR_TRANSFER);
//     if ((motor_status) == 0) return(ERR_TRANSFER);
     cli();
     floppy_int_pending = 0;
     fdc_out(req->opcode == 1 ? FDC_READ : FDC_WRITE);
     fdc_out(fp.fl_head << 2);
     fdc_out(fp.fl_cylinder);
     fdc_out(fp.fl_head);
     fdc_out(fp.fl_sector);
     fdc_out(SECTOR_SIZE_CODE);
     fdc_out(no_sectors);
     fdc_out(gap);
     fdc_out(DTL);
     if (need_reset) return(ERR_TRANSFER);
//     delay(0x4FF);
printf("Transfer 1\n");
     if((tmp=wait_for_intr()) == -1)
       return ERR_TIMEOUT;
     sti();
      //cli();
      //printf("\nreturn : %d",tmp);
      //delay(0xFFFF);
      //  sti();
     printf("Transfer\n");
     r = fdc_results();
     if (r != OK) return(r);
     printf("Transfer 2\n");
     if (f_results[ST1] & WRITE_PROTECT)
     {
           printf("floppy is write protected.\n" );
           return(ERR_WR_PROTECT);
     }
     if ((f_results[ST0] & ST0_BITS) != TRANS_ST0) return(ERR_TRANSFER);
     if (f_results[ST1] | f_results[ST2]) return(ERR_TRANSFER);
     s =  (f_results[ST_CYL] - fp.fl_cylinder) * no_heads * no_sectors;
     s += (f_results[ST_HEAD] - fp.fl_head) * no_sectors;
     s += (f_results[ST_SEC] - fp.fl_sector);
     if ((s << SECTOR_SHIFT) != req->r_count) return(ERR_TRANSFER);
printf("Transfer 3\n");
//     fp.fl_sector = f_results[ST_SEC];
     return(OK);
  }
int perform_oper(request *req)
 {
  int block;
  if(req->r_count == 0) return OK;
  block = (l_base + req->offset) >> SECTOR_SHIFT;
  fp.fl_cylinder = block / (no_heads * no_sectors);
  fp.fl_hardcyl = fp.fl_cylinder * steps_per_cyl;
  fp.fl_head = (block % (no_heads * no_sectors)) / no_sectors;
  fp.fl_sector = (block % no_sectors) +1;
  if (need_reset) reset();
  if (seek() != OK) return ERR_SEEK;
  dma_setup(req);
  printf("\ncylinder values %d %d %d %d",  fp.fl_cylinder,  fp.fl_hardcyl,  fp.fl_head,  fp.fl_sector);
  return do_transfer(req);
 }
int fdc_results()
{
  int result_nr, status;
  int i=0;
  result_nr = 0;
  do {
status = inb(FDC_STATUS) & (MASTER | DIRECTION | CTL_BUSY);
if (status == (MASTER | DIRECTION | CTL_BUSY))
     {
      if (result_nr >= MAX_RESULTS)
       break;
f_results[result_nr++] = inb(FDC_DATA);
continue;
}
if (status == MASTER) {
                  for(i=0;i<result_nr;i++)
                    printf("%x\n ",f_results[i]);
                        return(OK);
}
i++;
  } while (i<1000);
          need_reset = TRUE;
  return(ERR_STATUS);
}
int recalibrate()
{
  int r;
    printf("Recalibrating\n");
  startmotor();
  cli();
  floppy_int_pending = 0;
  fdc_out(FDC_RECALIBRATE);
  fdc_out(0);
  if (need_reset) return(ERR_SEEK);
//          delay(0x4FF);
     if((tmp= wait_for_intr()) == -1)
       return ERR_TIMEOUT;
       sti();
            //cli();
    //if(tmp == -1)
    //printf("\nreturn : %d",tmp);
     //delay(0xFFFF);
     //sti();
    fdc_out(FDC_SENSE);
  r = fdc_results();
  fp.fl_curcyl = NO_CYL;
  if (r != OK || (f_results[ST0] & ST0_BITS) != SEEK_ST0 || f_results[ST_PCN] != 0)
    {
need_reset = TRUE;
return(ERR_RECALIBRATE);
  }
    else
    {
fp.fl_calibration = TRUE;
return(OK);
  }
}
int seek()
{
  int r;
  if (fp.fl_calibration == 0)
if (recalibrate() != OK) return(ERR_SEEK);
//  if (fp.fl_curcyl == fp.fl_hardcyl) return(OK);
printf("Seeking\n");
      cli();
  fdc_out(FDC_SEEK);
  fdc_out((fp.fl_head << 2));
  fdc_out(fp.fl_hardcyl);
  if (need_reset) return(ERR_SEEK);
//          delay(3000);
  if((tmp = wait_for_intr()) == -1)
       return ERR_TIMEOUT;
      sti();
          // cli();
   // if(tmp == -1)
    //printf("\nreturn : %d",tmp);
     //delay(0xFFFF);
     //sti();
/*  if (f_intr != 1) return(ERR_TIMEOUT);
  f_intr = 0;
  enable();*/
  fdc_out(FDC_SENSE);
  r = fdc_results();
  if (r != OK || (f_results[ST0] & ST0_BITS) != SEEK_ST0
|| f_results[ST1] != fp.fl_hardcyl) {
return(ERR_SEEK);
  }
  fp.fl_curcyl = fp.fl_hardcyl;
  return(OK);
}
int reset()
 {
  //disable int
   need_reset = FALSE;
   motor_status = 0;
   motorgoal = 0;
   cli();
   outb(DOR, 0);
   outb(DOR, ENABLE_DMA);
   sti();
  //enable int
 }
int transfer(request r)
 {
  unsigned char *d;
  int res,i,count;
  count = r.r_count;
  r.r_count = (r.r_count/512)*512;
  if(startmotor() == 0)
  {
  // dma_setup(&r);
 if(r.opcode == 2)
  {
   // copy memory physical copy
   phys_mem_copy(r.pid,(void *)r.r_dma,FLOPPY_PID,(void *)dma_buf,r.r_count);
    cli();
    cls();
     printf("write buffer:\n");
    for(i=0;i<10;i++)
      printf("%x ",dma_buf[i]);
//    delay(0xFFF);
    sti();
    printf("\n");
  }
//  d =a;
//  for(i=0;i<count;i++,d++)
//     printf("%p %d\n",d,*d);
//  printf("\n");
//  printf("oper:\n");
  res = perform_oper(&r);
   printf("\nfloppy res: %d\n",res);
  motorgoal = 0;
  stopmotor();
//  printf("\n");
 if(r.opcode == 1 && res == 0)
 {
 cli();
cls();
  printf("buffer:\n");
  for(i=0;i<10;i++)
     printf("%x ",dma_buf[i]);
//  delay(0xFFF);
  sti();
printf("\n");
phys_mem_copy(FLOPPY_PID,(void *)dma_buf,r.pid,(void *)r.r_dma,r.r_count);
  }
  }
  else
  {
  motorgoal = 0;
  stopmotor();
  }
  if(res != 0)
   return -1;
  else
   return 0;
 }
void runFloppy()
{
  while(1)
  {
//   sti();
//     printf("running %d",no_req);
    if(no_req != 0)
    {
     cli();
     cls();
//     delay(0x5FFF);
     //printf("\nrunning %d",no_req);
     _proc[freqs[fr_req].pid].eax = transfer(freqs[fr_req]);
     remove(&device_q[FLOPPY_DEV],freqs[fr_req].pid);
     enq(&ready_q,freqs[fr_req].pid);
     fr_req = (fr_req +1) %MAX_FL_REQ;
     no_req--;
    }
  }
}

int wait_for_intr()
 {
  int tmp;
  wait_intr_timer(0x26,TIME_OUT);
  asm("pushl %eax");
  asm("popl %0"::"r"(tmp));
//  sleep(5);
  return tmp;
 }

int addreq(request *r)
{
  if(no_req == MAX_FL_REQ)
    return -1;
  freqs[en_req].offset = r->offset;
  freqs[en_req].opcode = r->opcode;
  freqs[en_req].r_count = r->r_count;
  freqs[en_req].r_dma = r->r_dma;
  freqs[en_req].pid = r->pid;
  en_req = (en_req +1) %MAX_FL_REQ;
  no_req++;
}
#endif

#ifdef FLOPPY_1

#include "floppy.h"
#include "message.h"
#include "device.h"
#include "queue.h"
#include "kpic.h"


char f_results[MAX_RESULTS];
int no_sectors = 18;
int no_tracks = 80;
int rate = 300;
int motor_status = 0;
int motorgoal;
int need_reset = FALSE;
int f_intr = 0;
int l_base = 0;
int no_blocks = 2880;
int size = 2880 << SECTOR_SHIFT;
int steps_per_cyl = 1;
int no_heads = 2;
int gap = 0x1b;
request freqs[MAX_FL_REQ];
int fr_req = 0;
volatile int no_req = 0;
int en_req = 0;
int tmp;


//for djggp finding physical address



unsigned char dma_buf[512] __attribute__((aligned (_4KB)));

struct floppy fp;
void fdc_out(int val)
	{
	  int i =0;
	  if (need_reset) return;
	  while ((inb(FDC_STATUS) & (MASTER | DIRECTION)) != (MASTER | 0)) {
		if (i>= 1000) {
			need_reset = TRUE;
			return;
		}
		i++;
	  }
	  outb(FDC_DATA, val);
	}

int startmotor()
 {
   int running;
   motorgoal = 0x1;
   running = motor_status & motorgoal;

   if(!running)
    {
      cli();
	    outb(DOR,motorgoal << 4 | ENABLE_DMA);
//	    tmp = wait_for_intr();
	    sti();
//	    cli();
//	    printf("\nreturn : %d",tmp);
//   	  delay(0xFFFF);
//  	  sti();

    }
    printf("Motor Started\n");
   //sleep(TIME_OUT);
//    wait_for_intr();
   motor_status = motorgoal;

   return 0;
 }

void stopmotor()
 {
    if(motor_status != motorgoal)
    {
     outb(DOR,motorgoal << 4 | ENABLE_DMA);
     motor_status = motorgoal;
    }
 }
void dma_setup(request *req)
 {
    int r_or_w,i;
    short page;
    unsigned long offs;

    page=(long)((DD)dma_buf>>16);
    offs =(short)((DD)dma_buf & 0xffff);

    if(req->opcode == 1)
     r_or_w = DMA_READ;
    else
     r_or_w = DMA_WRITE;
    outb(DMA_INIT, DMA_RESET_VAL);
    outb(DMA_FLIPFLOP, 0);
    outb(DMA_MODE, r_or_w);

    outb(DMA_ADDR,  offs & 0xff);
    outb(DMA_ADDR, ( offs >>  8) & 0xff);
    outb(DMA_TOP, page);

    outb(DMA_COUNT, (req->r_count - 1) >> 0);
    outb(DMA_COUNT, (req->r_count - 1) >> 8);
    outb(DMA_INIT, 2);
 }
int do_transfer(request *req)
  {
     int r, s;
     if (fp.fl_calibration == FALSE) return(ERR_TRANSFER);
     if ((motor_status) == 0) return(ERR_TRANSFER);

     cli();
     fdc_out(req->opcode == 1 ? FDC_READ : FDC_WRITE);
     fdc_out(fp.fl_head << 2);
     fdc_out(fp.fl_cylinder);
     fdc_out(fp.fl_head);
     fdc_out(fp.fl_sector);
     fdc_out(SECTOR_SIZE_CODE);
     fdc_out(no_sectors);
     fdc_out(gap);
     fdc_out(DTL);


     if (need_reset) return(ERR_TRANSFER);

//     delay(0x4FF);

     if((tmp=wait_for_intr()) == -1)
       return ERR_TIMEOUT;
     sti();
      //cli();
      //printf("\nreturn : %d",tmp);
      //delay(0xFFFF);
      //  sti();
     printf("Transfer\n");
     r = fdc_results();
     if (r != OK) return(r);




     if (f_results[ST1] & WRITE_PROTECT)
     {
           printf("floppy is write protected.\n" );
           return(ERR_WR_PROTECT);
     }

     if ((f_results[ST0] & ST0_BITS) != TRANS_ST0) return(ERR_TRANSFER);


     if (f_results[ST1] | f_results[ST2]) return(ERR_TRANSFER);


     s =  (f_results[ST_CYL] - fp.fl_cylinder) * no_heads * no_sectors;
     s += (f_results[ST_HEAD] - fp.fl_head) * no_sectors;
     s += (f_results[ST_SEC] - fp.fl_sector);

     if ((s << SECTOR_SHIFT) != req->r_count) return(ERR_TRANSFER);


//     fp.fl_sector = f_results[ST_SEC];
     return(OK);
  }

int perform_oper(request *req)
 {
  int block;
  if(req->r_count == 0) return OK;
  block = (l_base + req->offset) >> SECTOR_SHIFT;
  fp.fl_cylinder = block / (no_heads * no_sectors);
  fp.fl_hardcyl = fp.fl_cylinder * steps_per_cyl;
  fp.fl_head = (block % (no_heads * no_sectors)) / no_sectors;
  fp.fl_sector = (block % no_sectors) +1;

  if (need_reset) reset();


  if (seek() != OK) return ERR_SEEK;

  dma_setup(req);
  printf("\n%d %d %d %d",  fp.fl_cylinder,  fp.fl_hardcyl,  fp.fl_head,  fp.fl_sector);
  return do_transfer(req);
 }

int fdc_results()
	{
	  int result_nr, status;
	  int i=0;
	  result_nr = 0;
	  do {
		status = inb(FDC_STATUS) & (MASTER | DIRECTION | CTL_BUSY);
		if (status == (MASTER | DIRECTION | CTL_BUSY))
     {
      if (result_nr >= MAX_RESULTS)
       break;
			f_results[result_nr++] = inb(FDC_DATA);
			continue;
		}
		if (status == MASTER) {
                  for(i=0;i<result_nr;i++)
                    printf("%x\n ",f_results[i]);
                        return(OK);
		}
		i++;
	  } while (i<1000);
          need_reset = TRUE;
	  return(ERR_STATUS);
	}


int recalibrate()
	{
	  int r;
    printf("Recalibrating\n");
	  startmotor();
	  cli();
	  fdc_out(FDC_RECALIBRATE);
	  fdc_out(0);
	  if (need_reset) return(ERR_SEEK);
//          delay(0x4FF);

     if((tmp= wait_for_intr()) == -1)
       return ERR_TIMEOUT;
       sti();
            //cli();
	    //if(tmp == -1)
    		//printf("\nreturn : %d",tmp);
  	   //delay(0xFFFF);
  	   //sti();

    fdc_out(FDC_SENSE);
	  r = fdc_results();
	  fp.fl_curcyl = NO_CYL;
	  if (r != OK || (f_results[ST0] & ST0_BITS) != SEEK_ST0 || f_results[ST_PCN] != 0)
    {
		need_reset = TRUE;
		return(ERR_RECALIBRATE);
	  }
    else
    {
		fp.fl_calibration = TRUE;
		return(OK);
	  }
	}

int seek()
	{
	  int r;

	  if (fp.fl_calibration == 0)
		if (recalibrate() != OK) return(ERR_SEEK);
	  if (fp.fl_curcyl == fp.fl_hardcyl) return(OK);
    	  cli();
	  fdc_out(FDC_SEEK);
	  fdc_out((fp.fl_head << 2));
	  fdc_out(fp.fl_hardcyl);
	  if (need_reset) return(ERR_SEEK);
//          delay(3000);
	  if((tmp = wait_for_intr()) == -1)
       		return ERR_TIMEOUT;
    	  sti();
          // cli();
	   // if(tmp == -1)
    		//printf("\nreturn : %d",tmp);
  	   //delay(0xFFFF);
  	   //sti();

// / *
//	  if (f_intr != 1) return(ERR_TIMEOUT);
//	  f_intr = 0;
//	  enable(); * /




	  fdc_out(FDC_SENSE);
	  r = fdc_results();
	  if (r != OK || (f_results[ST0] & ST0_BITS) != SEEK_ST0
					|| f_results[ST1] != fp.fl_hardcyl) {

		return(ERR_SEEK);
	  }
	  fp.fl_curcyl = fp.fl_hardcyl;
	  return(OK);

	}
int reset()
 {
  //disable int
   need_reset = FALSE;
   motor_status = 0;
   motorgoal = 0;
   cli();
   outb(DOR, 0);
   outb(DOR, ENABLE_DMA);
   sti();
  //enable int
 }
int transfer(request r)
 {
  unsigned char *d;
  int res,i,count;

  count = r.r_count;
  r.r_count = (r.r_count/512)*512;

  if(startmotor() == 0)
  {
  // dma_setup(&r);
	 if(r.opcode == 2)
  	{
   	// copy memory physical copy
   		phys_mem_copy(r.pid,(void *)r.r_dma,FLOPPY_PID,(void *)dma_buf,r.r_count);
    	cli();
    	cls();
     	printf("write buffer:\n");
    	for(i=0;i<10;i++)
      		printf("%x ",dma_buf[i]);
//    	delay(0xFFF);
    	sti();
    	printf("\n");
  	}

	//  d =a;
	//  for(i=0;i<count;i++,d++)
	//     printf("%p %d\n",d,*d);
	//  printf("\n");

	//  printf("oper:\n");

	  res = perform_oper(&r);
    printf("\nfloppy res: %d\n",res);
  	motorgoal = 0;
  	stopmotor();
	//  printf("\n");
 	if(r.opcode == 1 && res == 0)
 	{
 	cli();
	cls();
  	printf("buffer:\n");
  	for(i=0;i<10;i++)
     		printf("%x ",dma_buf[i]);
//  	delay(0xFFF);
  	sti();
	printf("\n");
	phys_mem_copy(FLOPPY_PID,(void *)dma_buf,r.pid,(void *)r.r_dma,r.r_count);
  }
  }
  else
  {
  	motorgoal = 0;
  	stopmotor();
  }

  if(res != 0)
   return -1;
  else
   return 0;
 }
void runFloppy()
{
  while(1)
  {
//   sti();
//     printf("running %d",no_req);

    if(no_req != 0)
    {
     cli();
     cls();
//     delay(0x5FFF);

     //printf("\nrunning %d",no_req);
     _proc[freqs[fr_req].pid].eax = transfer(freqs[fr_req]);
     remove(&device_q[FLOPPY_DEV],freqs[fr_req].pid);
     enq(&ready_q,freqs[fr_req].pid);
     fr_req = (fr_req +1) %MAX_FL_REQ;
     no_req--;
    }
  }
}
int wait_for_intr()
 {
  int tmp;
  wait_intr_timer(0x26,TIME_OUT);

  asm("pushl %eax");
  asm("popl %0"::"r"(tmp));
//  sleep(5);
  return tmp;
 }
int addreq(request *r)
{
  if(no_req == MAX_FL_REQ)
    return -1;

  freqs[en_req].offset = r->offset;
  freqs[en_req].opcode = r->opcode;
  freqs[en_req].r_count = r->r_count;
  freqs[en_req].r_dma = r->r_dma;
  freqs[en_req].pid = r->pid;
  en_req = (en_req +1) %MAX_FL_REQ;
  no_req++;
}

#endif
