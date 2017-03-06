/*****************************************************************************
 *   uart.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2017,SensorControl
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *2017.01.10  ver 1.10    rename tick.h  tick.c
****************************************************************************************/
#include "tick.h"
		#ifdef D_debug_sim

		#include "../msp/msp_rtc.h"
		#endif
		
		#include "../debug/debug_led.h"
struct  _s_nos_tick_ s_nos_tick;

/*********************************************************************************************************
* Function Name:        timer0Isr
* Description:          TIMER0 中断处理函数
* Input:                无
* Output:               无
* Return:               无
*********************************************************************************************************/

void L1_tick_init(void)
{
	s_nos_tick.n_stamp = 0;  
//	s_nos_tick.t1s_heatbeart= 0;
//	s_nos_tick.t1s_flag[0] = 0;
//	s_nos_tick.t1s_flag[1] = 0;
//	s_nos_tick.t1s_flag[2] = 0;
//	s_nos_tick.t1s_flag[3] = 0;
//	s_nos_tick.t1s_flag[4] = 0;
//	s_nos_tick.t1s_flag[5] = 0;
	s_nos_tick.t_10ms = 0;
	s_nos_tick.t_1s = 0;
	s_nos_tick.t1s_heatbeart = 0;
	s_nos_tick.t1s_rtc= 0;
	s_nos_tick.t1s_rtc_n = 0;

	
	s_nos_tick.t1m_rtc = 0;
	s_nos_tick.t1m_rtc_one = 0;
}

void L1_tick_tick (void)
{/// 定时器设置为10ms 进入一次
	/// s  5ms		 65535*65535 /3600/24/365=139nian/s 
	// 4,294,836,225 = 65535*65535  ;3600*24*60*60 = 31,536,000秒/年
	// fixme:此处 保留了一个497天后会溢出的bug 那个时候不能有人使用t_10ms
	/// 在一个系统比较确定的时间内s_nos_tick.t_10ms 需要被清理 例如进入低功耗模式之前 
	/// 这样永远就没有这种bug存在了 201702  还有一种方式添加变量 使用的时候++,不使用时
	/// -- 这样释放,当变量=0时代表没有其他人使用t_10ms这时可以恢复初始值=目前值%100
	s_nos_tick.t_10ms ++;//D_led_D1_REV(); 20160522 验证
	if(s_nos_tick.t_10ms%D_TIMER0_1S_COUNT == 0)
	{// 65535*65535/24/60/60/356/10 =12.7年 
	//	

		s_nos_tick.t_1s ++;//
		s_nos_tick.t1s_heatbeart = 1;
		//led =~led;
		//s_nos_tick.t1s_flag[0] = 1;
		//s_nos_tick.t1s_flag[1] = 1;
		//s_nos_tick.t1s_flag[2] = 1;
		//s_nos_tick.t1s_flag[3] = 1;
		//s_nos_tick.t1s_flag[4] = 1;
		//s_nos_tick.t1s_flag[5] = 1;
		#ifdef D_debug_sim
			RTC_Time.sec ++;
			s_nos_tick.t1s_rtc = 1;
		#endif
	}
}




#if 0	///<1213123
// 定时程序:  首先定义某个通道ch 然后定义t_1s 的invent倍数  ,满足后显示's'   
void L2_time_beat_heart(U32 ch,U8 invent,U8 s)
{
	/**********
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			//L0_debugS_uc(s);
		}
	}
	***********/
}

/***************
if(1 == s_nos_tick.t1s_heatbeart)// 整秒时刻
{s_nos_tick.t1s_heatbeart= 0;
	L0_debugS_uc('.');
	L2_task_go(D_task_stop);
}
***************/

/*********************************************************************************************************
** Function name:	    delayNS
** Descriptions:	    延时函数
** input parameters:    ulDly:   值越大，延时时间越长
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void delayNS (U32 ulDly)
{
    U32 i; 
    
    for (; ulDly > 0; ulDly--) {
        for (i = 0; i < 50000; i++);
    }
}

/*

#if 0

LPC_SC->PCONP |= (1<<1);                       //打开功率控制  
      
    LPC_TIM0->TCR |= (1<<1);                       //复位定时器  
    LPC_TIM0->PR   = 0x00;                           //预分频清零  
    LPC_TIM0->MR0  = 10000;                          //匹配寄存器与定时器计数器值相比较  
    LPC_TIM0->IR  |= 0XFF;                           //清所有中断标志位  
    LPC_TIM0->MCR |= ((1<<1)|(1<<0));                //MR0与TC值匹配时将产生中断,TC复位  
    LPC_TIM0->TCR  = (1<<0);                       //启动定时器  
  
    NVIC_EnableIRQ(TIMER0_IRQn);                    // enable irq in nvic             // 
	T0PR = 99;				 // 设置定时器0分频为100分频，得160000Hz 晶振 16M

#endif


void L0_timer0_Init (void)
{

}

// s_nos_tick.t1s_flag[1]




// 定时程序:  首先定义某个通道ch 然后定义t_1s 的invent倍数  ,满足后执行*fun()   
void L2_time_beat_heart_fun(U32 ch,U8 invent,void (*fun)(void))
{
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			fun();
		}
	}
}


// 定时程序:  首先定义某个通道ch 然后定义t_1s 的invent倍数  ,满足后执行*fun()   
U32 L2_tick_beat_heart_flag(U32 ch,U32 invent)
{
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			return 0;
		}
	}
	return 0;
}




void L2_time_show_tick(U8 ch)
{	
	#if 0
	if (s_time0.tmp != s_time0.t_10ms)
	{
		s_time0.tmp = s_time0.t_10ms;
		if(0 == s_time0.tmp%100)
		{
			//L0_debug_show_ul("\r\nt =\0x00",s_time0.tmp/100); 
			L0_putstr(0x09);L0_putstr('t');L0_send0_uc_hex(ch);
			L0_send0_uc('=');L0_send0_Aul(s_time0.tmp/100);
		}
	}	

	if(1 == s_time0.t1s_flag)
	{s_time0.t1s_flag = 0;
		//L0_debug_show_ul("\r\nt =\0x00",s_time0.tmp/100); 
		L0_putstr(0x09);L0_send0_uc('t');L0_send0_uc_hex(ch);
		L0_send0_uc('=');L0_send0_Aul(s_time0.t_10ms/100);
	}

	if(1 == s_time0.t1s_flag)
	{s_time0.t1s_flag = 0;
		if(0 == (s_time0.t_1s%D_showtick_value))
		{
			L0_putstr("\r\nt");L0_send0_uc_hex(ch);
			L0_send0_uc('=');L0_send0_Auc(s_time0.t_1s/60/60);L0_send0_uc('h');
			L0_send0_uc('=');L0_send0_Auc(s_time0.t_1s/60);	L0_send0_uc('m');
			L0_send0_uc(':');L0_send0_Auc(s_time0.t_1s%60);L0_send0_uc('s');
			L0_send0_uc_hex((U8)s_time0.tmp);
		}
	}

//	#else
	U32 m,n; 
	
#define D_showtick_value	5	
	
	

	if(1 == s_nos_tick.t1s_flag)
	{//s_nos_tick.t1s_flag = 0;
		if(0 == (s_nos_tick.t_1s%D_showtick_value))
		{

			s_nos_tick.m = (U8)(s_nos_tick.time_left/100/60/60);
			s_nos_tick.h = s_nos_tick.time_left/100/60 - s_nos_tick.m*60;



		L0_USART_print(UART_debug,"\r\n ",m,s_nos_tick.time_left/100/60-m*60;);

			
		L0_putstr("\r\nCH");L0_send0_uc_hex(ch);//			L0_send0_Aul();
			L0_send0_uc('\t');L0_send0_Auc(m);
			n=s_nos_tick.time_left/100/60-m*60;
			L0_send0_uc(':');L0_send0_Auc(n);
			L0_send0_uc(':');L0_send0_Auc((s_nos_tick.time_left/100)%60);
			L0_send0_uc(0x09);
			L0_send0_uc_hex((U8)s_nos_tick.tmp);
			s_nos_tick.ts_flag = 1;
			L0_send0_uc(0x09);

			L0_USART_print(UART_debug,x);

			
		}
	}
	#endif
}
*/


#endif	//#if 0	///<1213123


#if 0	///<1213123


/*********************************************************************************************************
** Function name:	    delayNS
** Descriptions:	    延时函数
** input parameters:    ulDly:   值越大，延时时间越长
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void delayNS (U32 ulDly)
{
    U32 i; 
    
    for (; ulDly > 0; ulDly--) {
        for (i = 0; i < 50000; i++);
    }
}

/*

#if 0

LPC_SC->PCONP |= (1<<1);                       //打开功率控制  
      
    LPC_TIM0->TCR |= (1<<1);                       //复位定时器  
    LPC_TIM0->PR   = 0x00;                           //预分频清零  
    LPC_TIM0->MR0  = 10000;                          //匹配寄存器与定时器计数器值相比较  
    LPC_TIM0->IR  |= 0XFF;                           //清所有中断标志位  
    LPC_TIM0->MCR |= ((1<<1)|(1<<0));                //MR0与TC值匹配时将产生中断,TC复位  
    LPC_TIM0->TCR  = (1<<0);                       //启动定时器  
  
    NVIC_EnableIRQ(TIMER0_IRQn);                    // enable irq in nvic             // 
	T0PR = 99;				 // 设置定时器0分频为100分频，得160000Hz 晶振 16M

#endif


void L0_timer0_Init (void)
{

}

// s_nos_tick.t1s_flag[1]




// 定时程序:  首先定义某个通道ch 然后定义t_1s 的invent倍数  ,满足后执行*fun()   
void L2_time_beat_heart_fun(U32 ch,U8 invent,void (*fun)(void))
{
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			fun();
		}
	}
}


// 定时程序:  首先定义某个通道ch 然后定义t_1s 的invent倍数  ,满足后执行*fun()   
U32 L2_time_beat_heart_flag(U32 ch,U32 invent)
{
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			return 0;
		}
	}
	return 0;
}




void L2_time_show_tick(U8 ch)
{	
	#if 0
	if (s_time0.tmp != s_time0.t_10ms)
	{
		s_time0.tmp = s_time0.t_10ms;
		if(0 == s_time0.tmp%100)
		{
			//L0_debug_show_ul("\r\nt =\0x00",s_time0.tmp/100); 
			L0_putstr(0x09);L0_putstr('t');L0_send0_uc_hex(ch);
			L0_send0_uc('=');L0_send0_Aul(s_time0.tmp/100);
		}
	}	

	if(1 == s_time0.t1s_flag)
	{s_time0.t1s_flag = 0;
		//L0_debug_show_ul("\r\nt =\0x00",s_time0.tmp/100); 
		L0_putstr(0x09);L0_send0_uc('t');L0_send0_uc_hex(ch);
		L0_send0_uc('=');L0_send0_Aul(s_time0.t_10ms/100);
	}

	if(1 == s_time0.t1s_flag)
	{s_time0.t1s_flag = 0;
		if(0 == (s_time0.t_1s%D_showtick_value))
		{
			L0_putstr("\r\nt");L0_send0_uc_hex(ch);
			L0_send0_uc('=');L0_send0_Auc(s_time0.t_1s/60/60);L0_send0_uc('h');
			L0_send0_uc('=');L0_send0_Auc(s_time0.t_1s/60);	L0_send0_uc('m');
			L0_send0_uc(':');L0_send0_Auc(s_time0.t_1s%60);L0_send0_uc('s');
			L0_send0_uc_hex((U8)s_time0.tmp);
		}
	}

//	#else
	U32 m,n; 
	
#define D_showtick_value	5	
	
	

	if(1 == s_nos_tick.t1s_flag)
	{//s_nos_tick.t1s_flag = 0;
		if(0 == (s_nos_tick.t_1s%D_showtick_value))
		{

			s_nos_tick.m = (U8)(s_nos_tick.time_left/100/60/60);
			s_nos_tick.h = s_nos_tick.time_left/100/60 - s_nos_tick.m*60;



		L0_USART_print(UART_debug,"\r\n ",m,s_nos_tick.time_left/100/60-m*60;);

			
		L0_putstr("\r\nCH");L0_send0_uc_hex(ch);//			L0_send0_Aul();
			L0_send0_uc('\t');L0_send0_Auc(m);
			n=s_nos_tick.time_left/100/60-m*60;
			L0_send0_uc(':');L0_send0_Auc(n);
			L0_send0_uc(':');L0_send0_Auc((s_nos_tick.time_left/100)%60);
			L0_send0_uc(0x09);
			L0_send0_uc_hex((U8)s_nos_tick.tmp);
			s_nos_tick.ts_flag = 1;
			L0_send0_uc(0x09);

			L0_USART_print(UART_debug,x);

			
		}
	}
	#endif
}
*/


#endif	//#if 0	///<1213123





