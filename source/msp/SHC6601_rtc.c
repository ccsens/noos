/****************************************************************
Copyright (C) 2014, SHHIC .Co. ,Ltd. All rights reserved.

File name      :	SHC6601_rtc.c
Version        :	0.1
Author         :	Yanxian
Data	       :	2014-09-14
Description    :    RTC funcions 
****************************************************************/

#include "SHC6601_rtc.h"
/*****************************************************************
Function name : RTC_SetInterruptInterval
Input         : @param what:RTC_Interrupt_Interval 
				it can be only one of these everytime:
				1 INTERVAL_NONE
				2 INTERVAL_DAY
				3 INTERVAL_MONTH
				4 INTERVAL_YEAR
				5 INTERVAL_ONE_SECOND
				6 INTERVAL_ONE_MINUTE
				7 INTERVAL_ONE_HOUR
			    8 INTERVAL_ONE_MS
Output   	  : none
Return		  : none
Description	  :	set the rtc interrupt interval time 
******************************************************************/
void RTC_SetInterruptInterval(RTC_Interrupt_Interval what)
{
	INTERVAL = what;
}
/*****************************************************************
Function name : RTC_Run
Input         : @param what:RTC_Interrupt_Interval 
				it can be only one of these everytime:
				1 ENABLE 
				2 DISABLE
Output   	  : none
Return		  : none
Description	  : run the rtc module
******************************************************************/
void RTC_Run(FunctionalState what)
{
	if(what)
	{
		RTC_HOLD &= 0xFE;      //run the rtc module
	}
	else
	{
		RTC_HOLD |= 0x01;      //stop the rtc module
	}
}


/*****************************************************************
Function name : RTC_TimeSet
Input         : @param what: RTC_Time_Struct
Output   	  : none
Return		  : none
Description	  :	set the rtc time 
******************************************************************/
void RTC_TimeSet(RTC_Time_Struct *what)
{
	SECOND = (what->sec & 0x7f);
	MINUTE = (what->min & 0x7f);
	HOUR   = (what->hor & 0x3f);
	DAY    = (what->dy  & 0x3f);
	MONTH  = (what->mon & 0x1f);
	YEAR_L=  what->yer_0;
	YEAR_H=  what->yer_1;
}


/*****************************************************************
Function name : RTC_Reset
Input         : none			
Output   	  : none
Return		  : none
Description	  :	reset the rtc moudule
******************************************************************/
void RTC_Reset(void)
{
	U8 temp;
	temp = 0x00;

	RTC_RST &= 0xFE;	//RESET 有效
	RTC_RST |= 0x01;	// RESET 无效

	for(;temp<70;temp++);   //wait for about 60us,then the reset will be valid.
}





/*****************************************************************
Function name : RTC_TimeFormatSelect
Input         : @param what: 
		      it can be only one of these everytime:
		      1 FORMAT_12HOUR,
	          2 FORMAT_24HOUR
Output   	  : none
Return		  : none
Description	  : choose the time format
******************************************************************/
void RTC_TimeFormatSelect(RTC_FormatSelect what)
{
	FORMAT |= what; 
}

#if 0


/*****************************************************************
Function name : RTC_PulseOutputConfigure
Input         : @param : 	
				1 RTC_PULSE_SELECT
				2 RTC_PULSE_FRE
				3 RTC_PULSE_WIDTH
Output   	  : none
Return		  : none
Description	  :	configure RTC pulse 
******************************************************************/
void RTC_PulseOutputConfigure(RTC_PULSE_SELECT which,RTC_PULSE_FRE time,RTC_PULSE_WIDTH width)
{
	if(which)
	{
		CONF1 = (CONF1 & 0x0f) | (time << 2) | (width <<0);
	}
	else
	{
		CONF0 = (CONF0 & 0x0f) | (time << 2) | (width <<0);
	}
}


#endif























