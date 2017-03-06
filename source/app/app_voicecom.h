//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            app_vc.h
/// @brief           votage compare app headfile  
///  
///（本文件实现的功能的详述）  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20160412
///  
///  
///     修订说明：最初版本
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
///
///		adc app function	app_vc
///		adc hardware  driver SHC6601_adc
//////////////////////////////////////////////////////////////////////////


#ifndef _app_voicecom_H 
#define _app_voicecom_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

//#include "../clib/Type.h"
#include "../bsp/hard_config.h"
#include "../cpu/SHC6601_system.h"
#include "../msp/uart0.h"
#include "../debug/debug_drv.h"//
#include "app_fsk.h"
/////////////////////////
struct _s_task_voicecom_
{
	TS_task task;
	unsigned char t;
	unsigned char ocr;
};
extern struct _s_task_voicecom_ s_task_voicecom;

extern void L3_task_voicecom_init(void);
extern void L3_task_voicecom_handdle(struct _s_task_voicecom_ *s);

extern void L3_voicecom_init(void);



#define D_task_voicecom_1		0x40

#define D_task_voicecom_2	0x41

#define D_task_voicecom_3		0x42

#define D_task_voicecom_4		0x44

#define D_task_voicecom_5		0x45



#endif //	_vc_H


