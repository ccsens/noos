/*****************************************************************************
 *   DEBUG_DRV.h:  Header file for  DEBUY DRIVER FILES
 *
 *
 *   Copyright(C) 2013, cc
 *   All rights reserved.
 *
 *   History
 *   2013.05.24  ver 1.00    Prelimnary version, first Release
 
 20160413 CC-ACC-VH02 修正
 
 led： pin33 P22 LED
 P16 P17    空置


******************************************************************************/
#ifndef __DEBUG_LED_H 
#define __DEBUG_LED_H

//#include "../clib/type.h"
#include "../bsp/hard_config.h"


#define D_led_THB_REV()       D_led_P22_REV() 
#define D_led_THB_ONF(x)      D_led_P22_ONF(x)
#define D_led_THB_init()      D_led_P22_init()

#define D_led_DEBUG_REV()     D_led_P23_REV() 
#define D_led_DEBUG_ONF(x)    D_led_P23_ONF(x)
#define D_led_DEBUG_init()    D_led_P23_init()

#define D_led_D1_REV() 		D_led_P24_REV() 
#define D_led_D1_ONF(x)		D_led_P24_ONF(x)
#define D_led_D1_init()		D_led_P24_init()

#define D_led_D2_REV()		D_led_P25_REV() 
#define D_led_D2_ONF(x)		D_led_P25_ONF(x)
#define D_led_D2_init()		D_led_P25_init()

#define D_led_D3_REV()		D_led_P26_REV() 
#define D_led_D3_ONF(x)		D_led_P26_ONF(x)
#define D_led_D3_init()		D_led_P26_init()

#define D_led_D4_REV()		D_led_P27_REV() 
#define D_led_D4_ONF(x)		D_led_P27_ONF(x)
#define D_led_D4_init()		D_led_P27_init()




// 仿linux做一个errono的结构体 用来保存当前的错误信息

struct _s_errorno_
{
 int errono;
 char *errostr;
};

extern void L3_debug_led_init(void);

#endif /* end __DEBUG_LED_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/


