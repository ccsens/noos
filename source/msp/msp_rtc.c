/****************************************************************
Copyright (C) 2014, SHHIC .Co. ,Ltd. All rights reserved.

File name      :	app_rtc.c
Version        :	0.1
Author         :	CC
Data	       :	2016-04-14
Description    :    RTC app 
****************************************************************/

#include "msp_rtc.h"

//#include "Msp_plcd.h"
#include "../bsp/bsp_led.h"

#define Clean_RTC_Interrput_Flag() (AIF6 = 0) 

//GPIO_Struct Gpio_data;
RTC_Time_Struct RTC_Time; 
extern struct  _s_nos_tick_ s_nos_tick;

void  RtcClockSet()
{
	//选择 inside 32k 时必须确保内部的32K RS OSC打开 
	System_Inside32kEnable(ENABLE);
	System_RtcClockSelect(Inside32KClock);//outside32KClock

	//System_Inside32kEnable(DISABLE);
	//System_RtcClockSelect(outside32KClock);//Inside32KClock
	System_Peripheralmodules2ClockEnable(ENABLE,RTC_CLKEN);  //open the rtc clock
}
#define L0_Rtc_write()	RTC_TimeSet(&RTC_Time);
void L1_Rtc_Configure()
{
	 RTC_Reset();      //rtc module reset  
	 RTC_Time.sec = 0x12;
	 RTC_Time.min = 0x50;
	 RTC_Time.hor = 0x22;
	 RTC_Time.dy = 0x17;
	 RTC_Time.mon = 0x05;
	 RTC_Time.yer_0 = 0x16;
	 RTC_Time.yer_1 = 0x20;
	 System_X32KFaultEnable(ENABLE);//
	 
	 RtcClockSet();

	 RTC_TimeFormatSelect(FORMAT_24HOUR);

	 RTC_TimeSet(&RTC_Time);
	 
	 RTC_SetInterruptInterval(INTERVAL_ONE_SECOND);
	 
	 RTC_Run(ENABLE);

	 interrupt2Configure(ENABLE,Interrupt_AIE_RTCE_Msk);      //open the rtc interrupt
	 interrupt1Configure(ENABLE,Interrupt_IE0_EA_Msk); 	      //open the global interrupt
}



/*********

void L0_RTC_init(void)
{
	//RTC初始化-------------------------------------- 

	System_X32KFaultEnable(ENABLE);//

	RtcClockSet();
#if  0
	RTC_Reset();      //rtc module reset

	RTC_Time.dy = 0x10;
	RTC_Time.hor = 0x10;
	RTC_Time.min = 0x10;
	RTC_Time.mon = 0x10;
	RTC_Time.sec = 0x11;
	RTC_Time.yer_0 = 0x14;
	RTC_Time.yer_1 = 0x20;
	RTC_TimeSet(&RTC_Time);
#endif
	RTC_SetInterruptInterval(INTERVAL_ONE_SECOND);

	RTC_Run(ENABLE);

	interrupt2Configure(ENABLE,Interrupt_AIE_RTCE_Msk);      //open the rtc interrupt
	interrupt1Configure(ENABLE,Interrupt_IE0_EA_Msk); 	  //open the global interrupt

}
*******/

/*****************************************************************
Function name : interruptRTCHandler 
Input         : none				
Output		  : none
Return		  : none
Description	  :	RTC Interrupt handler
******************************************************************/
void interruptRtcHandler() interrupt Interrupt_Rtc_Number// using 3
{ 
	if (AIF6)
	{
		Clean_RTC_Interrput_Flag();
///		s_nos_tick.flag_1s2 = 1;	
		RTC_Time.sec = SECOND_DIS;
		RTC_Time.min = MINUTE_DIS;
		RTC_Time.hor = HOUR_DIS;
		RTC_Time.dy = DAY_DIS;
		RTC_Time.mon = MONTH_DIS;
		RTC_Time.yer_0 = YEAR_L_DIS;
		RTC_Time.yer_1 = YEAR_H_DIS;
		#ifdef D_use_lcd 
		L2_plcd_time();		
		#endif//#ifdef D_use_lcd 
//		D_led_THB_REV();
		if(0 == RTC_Time.sec%5)
		{
			s_nos_tick.t1s_rtc = 1;
			s_nos_tick.t1s_rtc_n ++;
			//D_leda_ON();
			//BITN_0(ts_Lcd_data.reg[D_plcd_reg_COL],D_plcd_COL);//":"
		}else
		{
			//D_leda_OFF();
			//BITN_1(ts_Lcd_data.reg[D_plcd_reg_COL],D_plcd_COL);//":"
		}
		if(0 == s_nos_tick.t1m_rtc_one	)
		{/// 只记录一次
			if((200/5) == s_nos_tick.t1s_rtc_n)
			{	s_nos_tick.t1m_rtc_one = 1;
				s_nos_tick.t1m_rtc = 1;/// 出现第2个1min
			}
		}
	}
}



