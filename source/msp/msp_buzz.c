//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            adxl362.c
/// @brief           adxl362 driver app  
///  
///（本文件实现的功能的详述）  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20150102
///  
///  
///     修订说明：最初版本
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
//////////////////////////////////////////////////////////////////////////



/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "msp_buzz.h"	

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/***************************************************************************//**
 * @brief Initializes communication with the device and checks if the part is
 *        present by reading the device id.
 *
 * @return 1 if the initialization was successful and the device is present,
 *         0 if an error occurred.
*******************************************************************************/

// CC-ACC-VH02  
// P21  BUZ 

U8 gbuzz_a[D_buzz_max+1] = {255,254,253,210,215,220,224};	//音调频率初值

struct _s_task_BUZZ_ s_task_BUZZ;

void L0_buzz_Init(void)
{
	///  10 -----  buzz mode
	//BITN_0(P2_DIR,(BITN1));	// P21  output

	D_P21_cofig_BUZZ();
	System_BuzzConfigureAndRun(BuzzClockFromOutsideX32,231);
	L0_buzz_OFF();
}

void L1_buzz_play(U8 channel)
{
	if (channel > D_buzz_max)
	{
		L0_buzz_OFF();
	}else
	{
		Buzz_CNT = gbuzz_a[channel];						 //读入频率初值		
		L0_buzz_ON();		 //打开蜂鸣器  使用主频
	}

}


///-------------------------------------------------------------------------     
///      @breif L2_task_BUZZ_init     
///      @param a s_task_BUZZ
///      @param s "L2_task_BUZZ_init"
///      @return	
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
///-------------------------------------------------------------------------
void L2_task_BUZZ_init(void)
{
	
	L1_task_init(&s_task_BUZZ.task);
	L3_task_s_go(s_task_BUZZ,D_task_init);	
}


//>>>>>>>>>>>>>>>>>>>>>0开机task

// L2_task_BUZZ_handdle(&s_task_BUZZ);
void L2_task_BUZZ_handdle(struct _s_task_BUZZ_ *s)
{
	switch(s->task.sh)
	{
		case D_task_init://
		if(L0_uart0_SendIntFree())
		{
			Lc_print_buf(" \r\n  BUZZ init");
			L2_task_go(0);
		//	L1_task_idelay(1*D_idelay_1s);	//大约6s 
		}
		break;
		case D_task_BUZZ_repeat:
			if(s->Vn)
			{
				s->Vn --;
			//	L0_uart0_uc('/');	
			//	L0_uart0_uchex(s->Vn);	
				L2_task_go(D_task_BUZZ_ON);
			}else
			{//结束 
				L2_task_go(0);
			}
		break;
		case D_task_BUZZ_ON:
				L0_buzz_ON();
			//	L0_uart0_uc('`');	
				L2_task_go(D_task_BUZZ_OFF);
				L1_task_idelay(s->V1*D_idelay_100ms);	//大约1s
			break;
		case D_task_BUZZ_OFF:
				L0_buzz_OFF();
			//	L0_uart0_uc('_');	
				L2_task_go(D_task_BUZZ_repeat);
				L1_task_idelay(s->V0*D_idelay_100ms);	//大约1s
		break;
		L2_task_switch_flag_idelay(1,'p');
	}
}


///	L1_buzz_play(2);

#if 0
void L2_task_BUZZ_run(U8 uchigh,U8 uclow,U8 ucrepeat,)
{
	s_task_BUZZ.V1 = uchigh;	///buzz工作 发声 1s = 10*D_idelay_100ms
	s_task_BUZZ.V0 = uclow;		///buzz关闭 静音 1s = 10*D_idelay_100ms
	s_task_BUZZ.Vn = ucrepeat;	/// 持续 5次 也就是5个(1s 发声+ 1s 静音) = 10s的蜂鸣器工作期,
								///当然最后一个1s静音可以忽略
	Buzz_CNT = gbuzz_a[channel];
L3_task_s_go(s_task_BUZZ,D_task_BUZZ_repeat);		
}

#endif



