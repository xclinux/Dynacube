/***************************************************************************
                          cmos.c  -  description
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

 #include "cmos.h"

 void gettime(TIME *t)
  {
             	t->sec = CMOS_READ(SECOND_ADDR);
                t->min = CMOS_READ(MINUTE_ADDR);
                t->hour = CMOS_READ(HOUR_ADDR);

		t->sec = BCD2BIN(t->sec);
        	t->min = BCD2BIN(t->min);
        	t->hour = BCD2BIN(t->hour);
  }
 void settime(TIME *t)
  {
	CMOS_WRITE(SECOND_ADDR,BIN2BCD(t->sec));
 	CMOS_WRITE(MINUTE_ADDR,BIN2BCD(t->min));
        CMOS_WRITE(HOUR_ADDR,BIN2BCD(t->hour));
  }
 void getdate(DATE *d)
  {
   		d->dd = CMOS_READ(DATE_ADDR);
                d->mm = CMOS_READ(MONTH_ADDR);
                d->yy = CMOS_READ(YEAR_ADDR);

		d->dd = BCD2BIN(d->dd);
        	d->mm = BCD2BIN(d->mm);
        	d->yy = BCD2BIN(d->yy);
  }
 void setdate(DATE *d)
  {
	CMOS_WRITE(DATE_ADDR,BIN2BCD(d->dd));
	CMOS_WRITE(MONTH_ADDR,BIN2BCD(d->mm));
	CMOS_WRITE(YEAR_ADDR,BIN2BCD(d->yy));
  }

