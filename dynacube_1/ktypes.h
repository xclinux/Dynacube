/***************************************************************************
                          ktypes.h  -  description
                             -------------------
    begin                : Sat Dec 13 2003
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

#ifndef __KTYPES_H
#define __KTYPES_H

	typedef unsigned char 	DB;	// 1 byte
	typedef unsigned short 	DW;	// 2 byte
	typedef unsigned int 	  DD;	// 4 byte

  //Signed xtensions
	typedef char 	  SDB;	// 1 byte
	typedef short 	SDW;	// 2 byte
	typedef int 	  SDD;	// 4 byte
  

	typedef enum {_false, _true} boolean;
	typedef enum {dpl_0,dpl_1,dpl_3,dpl_4} DPL;

  #define TI_GLOBAL 0b
  #define TI_LOCAL  1b

	#define RPL_0 00b
	#define RPL_1 01b
	#define RPL_2 10b
	#define RPL_3 11b
	
	#define F_TYPE_CODE     1<<3
	#define F_TYPE_C        1<<2
	#define F_TYPE_R        1<<1

	#define F_TYPE_DATA     0
	#define F_TYPE_E        1<<2
	#define F_TYPE_W        1<<1
	
	#define F_TYPE_A        1

	typedef struct
	{
	 DB rpl : 2;
	 DB ti : 1;
	 DW index:13;
	} SEG_SEL;

  #define F_DPL_1 01b
	#define F_DPL_2 10b
	#define F_DPL_3 11b

	#define F_S     1<<4        //Flag for Code/Data

	#define F_SD_DPL_1 1<<5
	#define F_SD_DPL_2 1<<6
	#define F_SD_DPL_3 (F_SD_DPL_1 | F_SD_DPL_2)

	#define F_P     1<<7    //Always Present in memory

	#define F_AVL   1
	#define F_D_B   1<<2
	#define F_G     1<<3

	typedef struct
	{
	 DW lt_0_15;
	 DW base_0_15;
	 DB base_16_23;
	 DB flags_8_15;
	 DB lt_16_19 : 4;
	 DB flags_20_23 : 4;
	 DB base_24_31;
	} SEG_DESC;

  typedef struct
  {
    DW limit;     
    DW lobase;
    DW hibase;
  } GDT;

  typedef struct
  {
    DW limit;    
    DW lobase;
    DW hibase;
  } IDT;

  typedef struct
  {
    DW limit;
    DW lobase;
    DW hibase;
  } LDT;
  
	//For the following
	//eg:
	//      F_IG = F_IG_P | F_IG | F_DPL_0<<13
	//      F_TG = F_TG_P | F_TG | F_DPL_0<<13
	//      F_TRG = F_TRG_P | F_TRG | F_DPL_0<<13

	//Interrupt Gate
	/* P(1) DPL(2) 0 D(1) 1 1 0 | 0 0 0 | 0 0 0 0 0*/
  #define F_IG 0x0E00
	#define F_IG_P 1<<15

	typedef struct
	{
	 DW off_0_15;
	 DW segsel_16_31;
	 DW flags_0_15;
	 DW off_16_31;
	} IG_DESC;

	//Task Gate
	/* P(1) DPL(2) | 0 0 1 0 1 | 0 0 0 0 0 0 0 0 */
	#define F_TG 0x0500  
	#define F_TG_P  1<<15

	typedef struct
	{
	 DW hole_0_15;
	 DW tss_seg_sel_16_31;
	 DW flags_0_15;
	 DW hole_16_31;
	} TG_DESC;

  //Trap Gate
	/* P(1) DPL(2) 0 D 1 1 1 | 0 0 0 | 0 0 0 0 0 */
	#define F_TRG 0F00  
	#define F_TRG_P 1<<15;
	
	typedef struct
	{ 
	 DW off_0_15;
	 DW segsel_16_31;
	 DW flags_0_15;
	 DW off_16_31;
	} TRG_DESC;

  typedef struct
  {
    DW off_0_15;
    DW segsel_16_31;
    DB param_count;
    DB flags;
    DW off_16_31;
  } CALL_GATE;
  
  extern DW cur_pid;

   #ifndef __SIZE_T
    #define size_t DD
   #endif

#endif
