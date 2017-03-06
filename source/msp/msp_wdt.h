//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            msp_io.h
/// @brief            
///  
///（本文件实现的功能的详述）  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20170214
///  
///  
///     修订说明：最初版本
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
///


//////////////////////////////////////////////////////////////////////////
/*****************************************************************************

----------------------------------------------------------------
7： 4       WDT[3:0]            20位WDT计时值最低4位LSB
----------------------------------------------------------------
3           WDTR                WDT运行标志位
...............................................................
								1： WDT计时
								0： WDT停止
2:0 		WOV[2:0] 			WDT计时溢出控制位   
...............................................................
     看门狗溢出时间选择  |看门狗计数器位数  | 溢出周期  |溢出时间
     WOV2  WOV1  WOV0    |                  |           | @X32K         
----------------------------------------------------------------
     0     0     0       |  13-bit          | 8 K       | 250ms
     0     0     1       |  14-bit          | 16 K      | 500ms
     0     1     0       |  15-bit          | 32 K      | 1s
     0     1     1       |  16-bit          | 64 K      | 2s
     1     0     0       |  17-bit          | 128 K     | 4s
     1     0     1       |  18-bit          | 256 K     | 8s
     1     1     0       |  19-bit          | 512 K     | 16s
     1     1     1       |  20-bit          | 1024K     | 32s
     Figure 19-3 看门狗控制寄存器（ WDTCON）
*************************************************************************************/
#ifndef _msp_wdt_H 
#define _msp_wdt_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

//#include "../clib/Type.h"
//#include "../bsp/hard_config.h"
///#include "../cpu/SHC6601_system.h"

typedef enum WDTTimeOverflowControl
{
	WDT_WDTCON_WOV_250ms,
	WDT_WDTCON_WOV_500ms,
	WDT_WDTCON_WOV_1s,
	WDT_WDTCON_WOV_2s,
	WDT_WDTCON_WOV_4s,
	WDT_WDTCON_WOV_8s,
	WDT_WDTCON_WOV_16s,
	WDT_WDTCON_WOV_32s
}WDTTimeOverflowControl;
 
/*****************simple function********************************/

#if 1
#define L0_IsWDTRun  ((WDTCON&0x08) == 0x08)
#define L0_WDT_OverFlowTimeSelect(what)		WDTCON = (WDTCON & 0xF8) | (what);
#define L0_WDT_CleanAndStartWdt()		WDTRST = 0x1E;	WDTRST = 0xE1;
#define L0_WDT_init()		BITN_0(CLKC,BITN6);L0_WDT_OverFlowTimeSelect(WDT_WDTCON_WOV_4s);L0_WDT_CleanAndStartWdt();


////BITN_0(CLKC,BITN6)
///6 WDTCS WDT 时钟选择
///1： WDT 时钟来源为内部 32K RC OSC
///0： WDT 时钟来源为外部 32K 晶振


#else
#define L0_IsWDTRun  ((WDTCON&0x08) == 0x08)
#define L0_WDT_OverFlowTimeSelect(what)		WDTCON = (WDTCON & 0xF8) | (what);
#define L0_WDT_CleanAndStartWdt()		;
#define L0_WDT_init()		;


#endif
#endif //#ifndef _msp_wdt_H 


