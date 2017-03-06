////////////////////////////////////////////////////////////////////////////  
///@copyright  Copyright (c) 2017, 传控科技 All rights reserved.  
///-------------------------------------------------------------------------  
/// @file            app_flow.c
/// @brief           应用程序里的流程,包括电源管理,上电顺序, 
///-------------------------------------------------------------------------  
/// @version		1.1  
/// @author		CC 
/// @date			20150102
/// @note			CC-PWR-VH01-m02.sch
///-------------------------------------------------------------------------
/// @version		1.2  
/// @author		CC 
/// @date			20170122
/// @note			cc_swhh_MD02
///			/--.....----------------|
///		   ( LED50	LED10	LED80  -|	    红色
///		   ( LED51	LED12	LED82  -|		绿色
///			\-----------------------|
///
//////////////////////////////////////////////////////////////////////////////


#include "bsp_led.h"


//L0_bsp_led_init();
//  1		2		3
//  4		5(51)	6
//  7		8		9
///-------------------------------------------------------------------------     
///      @breif L1_bsp_led_onf     
///      @param a m v
///      @param s "L1_bsp_led_onf"
///      @return	
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
///-------------------------------------------------------------------------
void L1_bsp_led_onf(U8 m,U8 v)
{
	switch(m)
	{
		case 0x0:
			if(v != 0)
				{D_bsp_led_allon();}
			else 
				{D_bsp_led_alloff();}
			break;		
		case 0x01:D_LED51_ONF(v);break;
		case 0x02:D_LED50_ONF(v);break;
		case 0x03:D_LED80_ONF(v);break;
		case 0x04:D_LED82_ONF(v);break;
		case 0x05:D_LED12_ONF(v);break;
		case 0x06:D_LED10_ONF(v);break;
		default:
		       D_bsp_led_alloff();
		break;
	};
		
}		


///-------------------------------------------------------------------------     
///      @breif L1_bsp_led_onf     
///      @param a m v
///      @param s "L1_bsp_led_onf"
///      @return	
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
///-------------------------------------------------------------------------
void L1_bsp_led_init(void)
{
	D_bsp_led_init();
//	L1_bsp_led_onf(0,0);

}
///-------------------------------------------------------------------------     
///      @breif L2_task_PWON_init     
///      @param a s_task_PWON
///      @param s "L2_task_PWON_init"
///      @return	
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
///-------------------------------------------------------------------------
void L2_bsp_led_test(void)
{
	//L0_bsp_led_init();
	SADEN1++;
	L1_bsp_led_onf(0,0);
	L1_bsp_led_onf((U8)(SADEN1%13),1);
}



