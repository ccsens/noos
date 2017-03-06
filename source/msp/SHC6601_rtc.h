/****************************************************************
Copyright (C) 2014, SHHIC .Co. ,Ltd. All rights reserved.

File name      :	SHC6601_rtc.h
Version        :	0.1
Author         :	Yanxian
Data	       :	2014-07-14
Description    :    RTC module defines  
****************************************************************/

#ifndef _SHC6601_RTC_H_
#define _SHC6601_RTC_H_	

#ifdef __cplusplus
 extern "C" {
#endif

//#include "SHC6601.h"
//#include "SHC6601_type.h"
#include "../bsp/hard_config.h"
#include "../debug/debug_drv.h"	
#include "../cpu/SHC6601_system.h"

/****************************************************************
************************** struct and enum***********************  
*****************************************************************/
typedef struct RTC_Time_Struct
{
	U8 sec;
	U8 min;
	U8 hor;
	U8 dy;
	U8 mon;
	U8 yer_0;
	U8 yer_1;
}RTC_Time_Struct;

typedef enum RTC_Interrupt_Interval
{
	INTERVAL_NONE = 0x00,
	INTERVAL_DAY = 0x10,
	INTERVAL_MONTH = 0x20,
	INTERVAL_YEAR = 0x30,
	INTERVAL_ONE_SECOND = 0x41,
	INTERVAL_ONE_MINUTE = 0x81,
	INTERVAL_ONE_HOUR = 0xC1,
	INTERVAL_ONE_MS = 0xE0,
	INTERVAL_MAX
}RTC_Interrupt_Interval;

typedef enum
{
	FORMAT_12HOUR,
	FORMAT_24HOUR,
	FORMAT_MAX
}RTC_FormatSelect;

typedef enum
{
	RTC_PULSE0,
	RTC_PULSE1	
}RTC_PULSE_SELECT;

typedef enum
{
	RTC_PULSE_FRE_HALF_SEC,
	RTC_PULSE_FRE_ONE_SEC,
	RTC_PULSE_FRE_TWO_SEC,
	RTC_PULSE_FRE_FOUR_SEC,
	RTC_PULSE_FRE_MAX
}RTC_PULSE_FRE;

typedef enum
{
	RTC_PULSE_WIDTH_FORTH_MS,
	RTC_PULSE_WIDTH_HALF_MS,
	RTC_PULSE_WIDTH_ONE_MS,
	RTC_PULSE_WIDTH_TWO_MS,
	RTC_PULSE_WIDTH_MAX
}RTC_PULSE_WIDTH;

/*****************************************************************
************************** Exported_fuctions********************** 
*****************************************************************/
void RTC_TimeSet(RTC_Time_Struct *what);
void RTC_SetInterruptInterval(RTC_Interrupt_Interval what);
void RTC_Reset(void);
void RTC_Run(FunctionalState what);
void RTC_PulseOutputConfigure(RTC_PULSE_SELECT which,RTC_PULSE_FRE time,RTC_PULSE_WIDTH width);
void RTC_TimeFormatSelect(RTC_FormatSelect what);

#ifdef __cplusplus
}
#endif

#endif


