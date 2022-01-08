#ifndef __FLOPPY_H
 #define __FLOPPY_H

#include "kio.h"
#include "kstdio.h"
#include "kconst.h"
#include "kasm.h"


#define TIME_OUT    3

#define TRUE 1
#define FALSE 0
#define OK 0

#define MAX_FL_REQ   100
#define MAX_RESULTS 16
#define MAX_SECTOR 2880

#define DOR            0x3F2
#define CTL_BUSY        0x10
#define DIRECTION       0x40
#define MASTER          0x80


#define FDC_STATUS     0x3F4
#define FDC_DATA       0x3F5
#define FDC_RATE       0x3F7

#define DMA_ADDR       0x004
#define DMA_TOP        0x081
#define DMA_COUNT      0x005
#define DMA_FLIPFLOP   0x00C
#define DMA_MODE       0x00B
#define DMA_INIT       0x00A
#define DMA_RESET_VAL  0x06

#define ST0             0x00
#define ST1             0x01
#define ST2             0x02
#define ST3             0x00
#define ST_CYL          0x03
#define ST_HEAD         0x04
#define ST_SEC          0x05
#define ST_PCN          0x01

#define NO_SECTOR          0
#define NO_CYL           (-1)
#define NO_DENS          100




#define ST0_BITS        0xF8
#define TRANS_ST0       0x00
#define SEEK_ST0        0x20

/* ST1. */
#define BAD_SECTOR      0x05
#define WRITE_PROTECT   0x02

/* ST2. */
#define BAD_CYL         0x1F


#define FDC_SEEK        0x0F
#define FDC_READ        0xE6
#define FDC_WRITE       0xC5
#define FDC_SENSE       0x08
#define FDC_RECALIBRATE 0x07
#define FDC_SPECIFY     0x03
#define FDC_READ_ID     0x4A
#define FDC_FORMAT      0x4D

#define DMA_READ        0x46
#define DMA_WRITE       0x4A




#define SECTOR_SIZE 512
#define SECTOR_SHIFT 9

#define ENABLE_DMA 0x0C

#define ERR_SEEK         (-1)
#define ERR_TRANSFER     (-2)
#define ERR_STATUS       (-3)
#define ERR_READ_ID      (-4)
#define ERR_RECALIBRATE  (-5)
#define ERR_DRIVE        (-6)
#define ERR_WR_PROTECT   (-7)
#define ERR_TIMEOUT      (-8)

#define DTL                0xFF
#define BASE_SECTOR        1
#define SECTOR_SIZE_CODE   2



typedef struct

 {
    unsigned r_count;
    long offset;
    long r_dma;
    int opcode;
    int pid;
  }request;
 extern request freqs[MAX_FL_REQ];
 extern volatile int no_req;

struct floppy {
	  int fl_curcyl;
	  int fl_hardcyl;
	  int fl_cylinder;
	  int fl_sector;
	  int fl_head;
	  char fl_calibration;
        };

void fdc_out(int val);

int startmotor();

void stopmotor();
void dma_setup(request *req);
int do_transfer(request *req);
int perform_oper(request *req);
int fdc_results();
int recalibrate();
int seek();

int reset();
int transfer(request r);
int wait_for_intr();
void runFloppy();
int addreq(request *r);
#endif
