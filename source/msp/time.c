/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			MX25L1602.c
** Descriptions:		SPI下的SST25VF016B操作函数库 
**
**------------------------------------------------------------------------------------------------------
** Created by:			Litiantian
** Created date:		2007-04-16
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/
#include "time.h"	
#include "../cpu/SHC6601_system.h"
#include "../cpu/SHC16L_macro.h"

#include "../debug/Debug_led.h"
#include "../app/App_fsk.h"

extern void L2_fsk_curve2(void);
/*********************************************************************************************************
* Function Name:        timer0Isr
* Description:          TIMER0 中断处理函数
* Input:                无
* Output:               无
* Return:               无
*********************************************************************************************************/
void L0_timer2_Init(void)
{
	TR2 = 0;// 关闭 CT0
	D_T2_cycle();
	BITN_1(PERI_CLK2,TIMER_CLKEN);//  timer 时钟控制
	BITN_1(PERI_CLK2,PORT_CLKEN);//  port 时钟控制
	TMM2 = 0;		//Timer2 工作模式选择0： 16 位计数器工作模式1: 8位自动重加载工作模式
	//ET2 = 1;	//CT0 interrupt enable1：定时器 0,定时器 2 中断使能
	ET0 = 1;	//CT0 interrupt enable
	TR2 = 1;// 启动计算器2
}

#if 0
void L0_timer0_Init(void)
{
	TR0 = 0;// 关闭 CT0
	D_T0_cycle();
	 BITN_1(PERI_CLK2,TIMER_CLKEN);//  timer 时钟控制
	//if(TM0_OVF )// timer0 溢出标识为


///3 GATE0 定时器0门控位
///0：当TR0=1时，定时器1工作，与外部门控输入（ P50或P26）无关
///1：只有当TR0=1, 并且外部门控输入(P50或P26)为1时，定时器1工作

///2 CT0 定时器 0 功能选择
///0：定时器功能：定时器 1 由主频/12 来进行计数
///1：计数器功能：计数器 1 由外部输入（ P51 或 P27）下降沿进行计数

///1 M10 M10 M00 计数器/定时器 0 工作方式
///0 0 模式 0: 13 位计数器/定时器
///0 1 模式 1： 16 位计数器/定时器
///1 0 模式 2： 溢出自动加载 8 位计数器/定时
///1 1 模式 3： 2 个 8 位计数器/定时器
///0 M00

	BITN_0(TMOD,BITN3);	// 0：当TR0=1时，定时器1工作，与外部门控输入（ P50或P26）无关
	BITN_0(TMOD,BITN2);	//0：定时器功能：定时器 1 由主频/12 来进行计数
	BITN_0(TMOD,BITN1);	BITN_1(TMOD,BITN0);	///模式 1： 16 位计数器/定时器
	ET0 = 1;	//CT0 interrupt enable
	TR0 = 1;// 启动计算器0
}
#else
void L0_timer0_Init_extinput(void)
{
	BITN_1(P2_DIR,BITN7);	//端口 Px7 输入输出配置寄存器1：配置成输入0：配置成输出

	BITN_1(P2_SEL2,BITN7);
	BITN_0(P2_SEL1,BITN7);	///10: P27 被配置成计数器 Timer0 时钟输入端口
	BITN_0(P2_SEL0,BITN7);	/// no  lcd segment
	
	TR0 = 0;// 关闭 CT0
	D_T0_cycle();
	 BITN_1(PERI_CLK2,TIMER_CLKEN);//  timer 时钟控制
	//if(TM0_OVF )// timer0 溢出标识为


///3 GATE0 定时器0门控位
///0：当TR0=1时，定时器1工作，与外部门控输入（ P50或P26）无关
///1：只有当TR0=1, 并且外部门控输入(P50或P26)为1时，定时器1工作




///2 CT0 定时器 0 功能选择
///0：定时器功能：定时器 1 由主频/12 来进行计数
///1：计数器功能：计数器 1 由外部输入（ P51 或 P27）下降沿进行计数

///1 M10 M10 M00 计数器/定时器 0 工作方式
///0 0 模式 0: 13 位计数器/定时器
///0 1 模式 1： 16 位计数器/定时器
///1 0 模式 2： 溢出自动加载 8 位计数器/定时
///1 1 模式 3： 2 个 8 位计数器/定时器
///0 M00

	BITN_0(TMOD,BITN3);	/// 门控无效 3 //GATE0 定时器0门控位 0：当TR0=1时，定时器1工作，与外部门控输入（ P50或P26）无关
	BITN_1(TMOD,BITN2);	/// 计数器功能1：计数器功能：计数器 1 由外部输入（ P51 或 P27）下降沿进行计数
	BITN_0(TMOD,BITN1);	BITN_1(TMOD,BITN0);	///模式 1： 16 位计数器/定时器
	ET0 = 1;	//CT0 interrupt enable
	TR0 = 1;// 启动计算器0
}


#endif



void L1_time0_init(void)
{
	L1_tick_init();
	//L0_timer0_Init();//
	L0_timer0_Init_extinput();
	L0_timer2_Init();
}




//#define	D_TIMER0_10MS_COUNT	56
void TIMER0_IRQHandler (void) interrupt Interrupt_Timer0_Timer2_Number// using 0
{//
#ifndef D_sim_timer0
	if(TM2_OVF)
#endif		
	{TM2_OVF = 0;
	//	D_led_THB_REV();
		D_T2_cycle();
		L1_tick_tick();
		//L2_fsk_curve2();
		//if(0 == s_array_hd.savef)
		{
			s_array_hd.savef = 1;
			
			s_array_hd.hn = TH0;
			s_array_hd.zn = TL0;
			TH0 = 0;
			TL0 = 0;
		}
	}
#ifndef D_sim_timer0

else

	{TM0_OVF = 0;
	//	D_led_DEBUG_REV();
		D_T0_cycle();
	//	L1_tick_tick();

	}
#endif
}


