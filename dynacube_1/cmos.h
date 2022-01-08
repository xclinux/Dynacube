/***************************************************************************
                          cmos.h  -  description
                             -------------------
    begin                : Mon Mar 14 2004
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
 #ifndef __CMOS_H
 #define __CMOS_H

#define CMOS_OUT_PORT 0x70
#define CMOS_IN_PORT 0x71

#define SECOND_ADDR 0x00
#define MINUTE_ADDR 0x02
#define HOUR_ADDR 0x04
#define DAY_ADDR 0x06
#define DATE_ADDR 0x07
#define MONTH_ADDR 0x08
#define YEAR_ADDR 0x09

#define CMOS_READ(addr) ({ \
outb(CMOS_OUT_PORT,0x80|addr); \
inb(CMOS_IN_PORT); \
})

#define CMOS_WRITE(addr,val) ({ \
outb(CMOS_OUT_PORT,0x80|addr); \
outb(CMOS_IN_PORT,val); \
})


#define BCD2BIN(bcd) ((bcd&0xF) + ((bcd>>4)*10))
#define BIN2BCD(bin)  (((bin / 10) << 4) | (bin % 10))

typedef struct
{
	char mm,dd;
	int yy;
}DATE;
typedef struct
{
	int hour,min,sec;
}TIME;

 void gettime(TIME *t);
 void settime(TIME *t);
 void getdate(DATE *d);
 void setdate(DATE *d);
 
#endif