//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, ���ؿƼ�
/// All rights reserved.  
///  
/// @file            app_rtc.h
/// @brief           rtc driver headfile  
///  
///�����ļ�ʵ�ֵĹ��ܵ�������  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20160412
///  
///  
///     �޶�˵��������汾
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
//////////////////////////////////////////////////////////////////////////


#ifndef _msp_rtc_H 
#define _msp_rtc_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

//#include "../clib/Type.h"
#include "../bsp/hard_config.h"
//#include "../msp/spi.h"
#include "../debug/debug_drv.h"//
#include "../cpu/SHC6601_system.h"
#include "SHC6601_rtc.h"
#include "time.h"

/*! Initializes the device. */
//void L0_RTC_init(void);


extern RTC_Time_Struct RTC_Time; 

void L1_Rtc_Configure(void);
//void L0_Rtc_read(void);

#endif //	_adxl362_H


