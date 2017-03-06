#ifndef   _APP_ACTION_H
#define   _APP_ACTION_H

//#include "../clib/Type.h"
#include "../bsp/hard_config.h"
#include "../cpu/SHC6601_system.h"
#include "../msp/uart0.h"
#include "../debug/debug_drv.h"//
//#include "../msp/msp_plcd.h"
#if (TYPE_ASENSOR_MSA300 == TYPE_ASENSOR)
#include "../bsp/msa300.h"

#elif (TYPE_ASENSOR_ADXL362 == TYPE_ASENSOR)

#include "../bsp/adxl362.h"


#endif

#include "../msp/SHC6601_rtc.h"
//#include "Bsp_led.h"	
//>>>>>>>>>>>>>>>>>>>>>0task
#define D_ACTION_status_time		0	// 显示时间
#define D_ACTION_status_angle	1	// 显示角度
#define D_ACTION_status_setup	2	// 设置
#define D_ACTION_status_count	3	// 显示计时开始
#define D_ACTION_status_erro		4	// 错误
struct _s_task_ACTION_
{
	TS_task task;
	vU16 x,y,z;//
	vU16 xa,ya,za;//
	//vU16 x,y,z;//
	
	unsigned char area;//
	unsigned char status;//
	unsigned char key;//
};

extern struct _s_task_ACTION_ s_task_ACTION;

extern void L2_task_ACTION_handdle(struct _s_task_ACTION_ *s);
extern void L2_task_ACTION_init(void);

#define D_task_ACTION_init	0x10

#define D_task_ACTION_read 0x56
#define D_task_ACTION_send 0x57

#define D_task_ACTION_action 0x58
#define D_task_ACTION_calA 0x60
#define D_task_ACTION_calB 0x61
#define D_task_ACTION_calC 0x62




//<<<<<<<<<<<<<<<<<<<0task


#endif	//_APP_ACTION_H



