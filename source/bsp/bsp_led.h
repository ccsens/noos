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
//////////////////////////////////////////////////////////////////////////////

#ifndef __bsp_LED_H 
#define __bsp_LED_H

#include "../bsp/hard_config.h"

#define D_LED51_REV() 		D_led_P22_REV() 
#define D_LED51_ONF(x)		D_led_P22_ONF(x)
#define D_LED51_init()		D_led_P22_init()

#define D_LED50_REV()		D_led_P23_REV() 
#define D_LED50_ONF(x)		D_led_P23_ONF(x)
#define D_LED50_init()		D_led_P23_init()

#define D_LED80_REV() 		D_led_P24_REV() 
#define D_LED80_ONF(x)		D_led_P24_ONF(x)
#define D_LED80_init()		D_led_P24_init()

#define D_LED82_REV()		D_led_P25_REV() 
#define D_LED82_ONF(x)		D_led_P25_ONF(x)
#define D_LED82_init()		D_led_P25_init()

#define D_LED12_REV()		D_led_P26_REV() 
#define D_LED12_ONF(x)		D_led_P26_ONF(x)
#define D_LED12_init()		D_led_P26_init()

#define D_LED10_REV()		D_led_P27_REV() 
#define D_LED10_ONF(x)		D_led_P27_ONF(x)
#define D_LED10_init()		D_led_P27_init()
 
#define D_bsp_led_allon()	D_LED51_ONF(1);\
         					D_LED50_ONF(1);\
         					D_LED80_ONF(1);\
         					D_LED82_ONF(1);\
         					D_LED12_ONF(1);\
         					D_LED10_ONF(1);\
							 
#define D_bsp_led_alloff()	D_LED51_ONF(0);\
         					D_LED50_ONF(0);\
         					D_LED80_ONF(0);\
         					D_LED82_ONF(0);\
         					D_LED12_ONF(0);\
         					D_LED10_ONF(0);\


 
#define D_bsp_led_init()	D_LED51_init();\
         					D_LED50_init();\
         					D_LED80_init();\
         					D_LED82_init();\
         					D_LED12_init();\
         					D_LED10_init();\
         					D_bsp_led_allon();
							 
							 
extern void L1_bsp_led_init(void);
extern void L2_bsp_led_test(void);
extern void L1_bsp_led_onf(U8 m,U8 v);
#endif /* end __bsp_LED_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/


