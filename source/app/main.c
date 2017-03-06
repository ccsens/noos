//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            main.c
/// @brief           main app  
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
/// Descriptions:	CC-PWR-VH01-m02.sch
//////////////////////////////////////////////////////////////////////////

//20160413 CC-ACC-VH02 




/// 下面是一个含有两个参数的函数的注释说明（简述）   
///     
///      这里写该函数的详述信息     
///      @param a 被测试的变量（param描述参数）     
///      @param s 指向描述测试信息的字符串     
///      @return     测试结果（return描述返回值）   
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 




/************************************************


SHC16LC32LQ80

SHC6601主程序框架
************************************************/

//===============================================
//寄存器头文件
//===============================================											
#include "main.h"
#include "../uartcom/urec2protocol.h"
/********************
#define D_ram_test_max 500
long c[D_ram_test_max] = {0};
c[D_ram_test_max -1 ] = 9;
	
**************************/

///      main init
///      @param a 被测试的变量（param描述参数）     
///      @param s 指向描述测试信息的字符串     
///      @return     测试结果（return描述返回值）   
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 

void L0_main_init(void)
{
//	U8 i;
///step : 1>>>>>>>>>>cpu时钟初始化-------------------------------------
	L3_debug_led_init();
	L1_bsp_led_init();
	///  rev指令时间 6us
	L1_System_SystemClockInitial();//  1 System_MainFreSelect(MainFre_16M);
	L0_WDT_init();
	L2_AppFlag_init();
	///4M  rev指令时间 2us
///step : 2>>>>>>>>>>定时器初始化-------------------------------------
	L1_time0_init();
	L1_Rtc_Configure();

#ifndef D_sim_timer0
	Lc_delay_ms(400);// 2000--7s
#endif

///step : 3>>>>>>>>>串口等debug相关>>>>>>>>>
	L0_UARTcom_Init(&s_at0);
	L0_uart0_init();

	//打开总中断-------------------------------------
///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	BITN_1(IPH0,BITN4);
	BITN_1(IPL0,BITN4);// uart 串口中断优先级最高
///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	EA = 1;
	Lc_print_buf("\r\n\r\nHV:CC-MD-VH03_m10\r\n"); 
	L3_debug_time();
	L0_WDT_CleanAndStartWdt();
	
//	L3_debug_drv_init();
//	L3_debug_led_init();
//step : 4>>>>>>>>>>>>>>>> msp or bsp driver inint
//------------------------------------------//module: cw6301  // i2c config first
#ifndef D_init_module_i2c
#define D_init_module_i2c
	
	L2_task_i2c_init();
#endif // D_init_module_i2c
	L1_cw63xx_init();
#if 0
//------------------------------------------//module: msa300  // i2c config first	
#ifndef D_init_module_i2c
#define D_init_module_i2c
	L1_i2c_Configure();		
	L2_task_i2c_init();
#endif // D_init_module_i2c
	L1_msa300_init();
//------------------------------------------
//  	L0_buzz_Init();
//------------------------------------------
//	L1_lcd_init();
//	L2_lcd_main();
//------------------------------------------


	L1_fsk_Init();
	L3_voicecom_init();
	L3_task_voicecom_init();
//------------------------------------------
#endif


//------------------------------------------
	L1_PWON_init();// 电源配置
 	L0_buzz_Init();// 蜂鸣器
 	L2_task_BUZZ_init();
//fixme: 和timer冲突的clk 输入	L1_bsp_led_init();
	L2_task_PWON_init();
}

//===============================================
//主函数
//===============================================
void main(void)
{
	
//-----------------------------------------------
//系统初始化
//----------------------------------------------
//	char s[18];
	L0_main_init();
//-----------------------------------------------
//系统主循环
//-----------------------------------------------
#ifdef D_sim_timer0
	Lc_print("\r\n!!!! D_sim_timer0 !!!!\r\n");
#endif 
#ifdef D_sim_uart
	Lc_print("\r\n!!!! D_sim_timer0 !!!!\r\n");
#endif 
	Lc_print("mainloop..;\r\n");
	while(9)
	{L0_WDT_CleanAndStartWdt();
		L2_task_PWON_handdle(&s_task_PWON);
		L3_UARTcom0_exp_protocol(&s_at0);
//		L3_task_voicecom_handdle(&s_task_voicecom);
		L2_task_BUZZ_handdle(&s_task_BUZZ);
////		L2_task_ACTION_handdle(&s_task_ACTION);
	}
}//end main


/*******************

	sprintf(s, "%10.3f", 3.1415626); 
	sprintf(s, "%0.3f", 1234563.1415626); 
	sprintf(s, "%13.3f", 456456.1415626); 
	sprintf(s, "%5.3f", 3.1415626); 
	sprintf(s, "%2.2f", 3.1415626); 

********************/
