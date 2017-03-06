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


#ifndef   _APP_FLOW_H
#define   _APP_FLOW_H


//#include "../clib/Type.h"

#include "../bsp/hard_config.h"

#include "../cpu/SHC6601_system.h"


#include "../msp/uart0.h"

#include "../debug/debug_drv.h"//
#include "../bsp/cw63xx.h"

#include "../msp/SHC6601_rtc.h"
#include "app_action.h"	

//>>>>>>>>>>>>>>>>>>>>>0开机task
#define D_PWON_status_time		0	// 显示时间
#define D_PWON_status_angle	1	// 显示角度
#define D_PWON_status_setup	2	// 设置
#define D_PWON_status_count	3	// 显示计时开始
#define D_PWON_status_erro		4	// 错误
struct _s_task_PWON_
{
	TS_task task;
	vU32 t_stamp;//
	unsigned char area;//
	unsigned char status;//
	unsigned char key;//
	unsigned char sec;//
};

extern struct _s_task_PWON_ s_task_PWON;

extern void L2_task_PWON_handdle(struct _s_task_PWON_ *s);
extern void L2_task_PWON_init(void);

#define D_task_PWON_ask 0x56
#define D_task_PWON_enter 0x57
#define D_task_PWON_init	0x10

#define D_task_OSD_init_key	0x11

//<<<<<<<<<<<<<<<<<<<0开机task

#define D_Power_channel_LED		D_CW63X_REG_LDO1
#define D_Power_channel_BUZ		D_CW63X_REG_LDO2
#define D_Power_channel_MIC		D_CW63X_REG_LDO3
#define D_Power_channel_VCC		D_CW63X_REG_LDO4
extern void L1_PWON_init(void);
#endif	// _APP_FLOW_H



