/*****************************************************************************
 *   uart.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2017,SensorControl
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *2017.01.10  ver 1.10    rename tick.h  tick.c
******************************************************************************/
#ifndef __tick_H 
#define __tick_H
//#include "../clib/Type.h"
#include "../bsp/hard_config.h"
#include "../msp/time.h"

struct	_s_nos_tick_
{	
	
	vU32 sys_clock; 
//	vU32 t_n; 		// 	noos系统定时器最小技术单元
	vU32 t_10ms; 	//	noos 系统定时器10m技术
	//volatile INT32U t_100ms; 
	vU32 t_1s; 
//	vU32 n; 	//fixme
	U8 t1s_rtc;

	U8 t1s_rtc_n;

	U8 t1m_rtc; 
	U8 t1m_rtc_one; 
///	volatile INT32U tmp; 	
///	volatile INT32U time_left; 
///	volatile INT32U h; 
///	volatile INT32U m; 	
	vU32 n_stamp; 	
	U8 t1s_heatbeart; 	//noos 系统定时器整秒时刻标志,需要软件清除
//	vU32 t1s_flag[6]; 	//fixme: INT32U  根据不同的系统来决定
	//volatile unsigned char t1s_flag; 
	U8 ts_flag;
};
extern struct  _s_nos_tick_ s_nos_tick;

#define D_idelay_10ms		1//D_TIMER0_10MS_COUNT		
#define D_idelay_100ms		(D_idelay_10ms*10)
#define D_idelay_300ms		(30)
#define D_idelay_500ms		(50)
#define D_idelay_1s		(D_idelay_10ms*100)
#define D_idelay_1min	(D_idelay_1s*60)
#define D_idelay_1h		(D_idelay_1min*60)
#define D_idelay_1day	(D_idelay_1h*24)
#define  D_TIMER0_1S_COUNT		100

//>> 定时器: 初始化 间隔时间到
//			L0_nos_tick10ms_start(s->times);		开始初始化s->times  以10ms为一个单位
//			if(  L0_nos_tick10ms_interval(s->times) < 20)//  s->times 执行了20次后,也就是 定时20*10m到达

//必须配对
#define L0_nos_tick10ms_start(start_n) 		(start_n) = s_nos_tick.t_10ms	
#define L0_nos_tick10ms_interval(start_n) 	(s_nos_tick.t_10ms - (start_n))


#define L0_nos_tick1s_start(start_n) 		(start_n) = s_nos_tick.t_1s	
#define L0_nos_tick1s_interval(start_n) 	(s_nos_tick.t_1s - (start_n))


//>>>//必须配对
#define L2_tick_time_stamp(time_stamp)						(time_stamp) = s_nos_tick.t_10ms;
#define L2_tick_time_interval(time_stamp,time_overflow) 	(( s_nos_tick.t_10ms - (time_stamp)) > (time_overflow))


#define L3_tick_interval(x)		L2_tick_time_interval(s_nos_tick.n_stamp,(x))
#define L2_tick_stamp()			L2_tick_time_stamp(s_nos_tick.n_stamp);


#define L3_tick_task_interval(time_overflow)		L2_tick_time_interval(s->t_stamp,(time_overflow))
#define L3_tick_task_stamp()		 				L2_tick_time_stamp(s->t_stamp)


//>>>示例如下:
#ifdef doc_99089
{
		case D_task_init://
 			Lc_print_buf(" \r\n YL_ init");
			s->step = D_AT;
			L0_esp_open();
			L2_task_go(D_task_YL_ready);
			s_at0.ok = 0;
			L2_tick_time_stamp(s->t_stamp);
		//	L1_task_idelay(1*D_idelay_1s);	//大约6s 
		break;
		case D_task_YL_ready:
			if(1 == s_at0.ok)
			{
				if(strstr(s_at0.array,"ready") != NULL)
				{
				
					Ldi_print("ready..\r\n");
					s->step = D_AT;
					L2_task_go(D_task_YL_ask);
				}
				s_at0.ok = 0;
			}
			if(L2_tick_time_stamp(s->t_stamp,1*D_idelay_1s))
			{// 时间溢出
				L0_esp_close();
				Ldi_print("fail esp restart.\r\n");
				L2_task_go(D_task_init);
				L1_task_idelay(2*D_idelay_1s);
			}
		break;
}
#endif


#define D_main_status_debug	2
#define D_main_status_run	3

// 他和t_10ms 关联,如果t_10ms递增为1时间隔为(D_TIMER0_10MS_COUNT*定时器间隔)
/// #define	D_TIMER0_10MS_COUNT	1	//定时器为 10ms一中断 


extern void L1_tick_init(void);
extern void L1_tick_tick (void);
//L2_time_beat_heart(D_TBH_ch1,2,'t')
#define  D_TBH_ch0	0
#define  D_TBH_ch1	1
#define  D_TBH_ch2	2
#define  D_TBH_ch3	3
#define  D_TBH_ch4	4
#define  D_TBH_ch5	5
extern void L2_time_beat_heart(vU32 ch,U8 invent,U8 s);
//void L2_time_beat_heart_fun(INT32U ch,unsigned char invent,void *fun(void));
extern void L2_time_beat_heart_fun(vU32 ch,U8 invent,void (*fun)(void));

#endif /* end __tick_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
