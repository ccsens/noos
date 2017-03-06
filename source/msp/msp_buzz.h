//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            buzz.h
/// @brief           buzzx driver headfile  
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
//////////////////////////////////////////////////////////////////////////


#ifndef _msp_buzz_H 
#define _msp_buzz_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

//#include "../clib/Type.h"
#include "../bsp/hard_config.h"
//#include "../msp/spi.h"
#include "../debug/debug_drv.h"//
#include "../cpu/SHC6601_system.h"
#define D_buzz_max	6
extern U8 gbuzz_a[D_buzz_max+1];

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/

/*! Initializes the device. */
extern void L0_buzz_Init(void);
extern void L1_buzz_play(U8 channel);

//#define D_buzz_direct_control	/// io直接驱动		
#ifdef D_buzz_direct_control
#define D_P21_cofig_BUZZ()		BITN_1(P2_SEL2,(BITN1));BITN_0(P2_SEL1,(BITN1));BITN_0(P2_SEL0,(BITN1));P21 = 1
#define D_P21_cofig_IO()		BITN_0(P2_SEL2,(BITN1));BITN_0(P2_SEL1,(BITN1));BITN_0(P2_SEL0,(BITN1));P21 = 0
// P21 fixme:  高还是低 需要研究
#else
#define D_P21_cofig_BUZZ()		BITN_0(P2_DIR,(BITN1));\
								BITN_1(P2_SEL2,(BITN1));BITN_0(P2_SEL1,(BITN1));BITN_0(P2_SEL0,(BITN1));\
								P21 = 0
#define D_P21_cofig_IO()		BITN_1(P2_DIR,(BITN1));\
								BITN_0(P2_SEL2,(BITN1));BITN_0(P2_SEL1,(BITN1));BITN_0(P2_SEL0,(BITN1));\
								P21 = 1
#endif

#define Buzz_at() BITN_G(Buzz_CTL,BITN0)

#define L0_buzz_ON();	D_P21_cofig_BUZZ();Buzz_Run();
#define L0_buzz_OFF();	Buzz_Stop();D_P21_cofig_IO();// mcu关闭buzz后默认0v 对于9015而言 需要3.3v
//		需要注意此时三极管耗电，如果avcc关闭可能也就没有这个问题了

struct _s_task_BUZZ_
{
	TS_task task;
	vU32 t_stamp;//
	type_comm V1;	/// 高音时间,使用时间片的次数代替
	type_comm V0;	/// 低音
	type_comm Vn;	///持续次数
};

extern struct _s_task_BUZZ_ s_task_BUZZ;

extern void L2_task_BUZZ_handdle(struct _s_task_BUZZ_ *s);
extern void L2_task_BUZZ_init(void);
extern void L2_task_BUZZ_run(U8 uchigh,U8 uclow,U8 ucrepeat);


#define D_task_BUZZ_heratbeat	0x70
#define D_task_BUZZ_status		0x80
#define D_task_BUZZ_repeat		0x90
#define D_task_BUZZ_ON		0xA0
#define D_task_BUZZ_OFF	0xB0
///_______/``V1```\___V0___/``V1```\___V0___``V1```\___V0___``V1```\___V0___`````\_______/`````\_______/
///-------|-----Vn=1-------|-----Vn=2-------|-----Vn=2-------|-----Vn=2-------|-----Vn=5-------|
/// L2_task_BUZZ_run();
#define L2_task_BUZZ_run(channel,uchigh,uclow,ucrepeat)	\
						s_task_BUZZ.V1 = uchigh;\
						s_task_BUZZ.V0 = uclow;\
						s_task_BUZZ.Vn = ucrepeat;\
						Buzz_CNT = gbuzz_a[channel];\
						L3_task_s_go(s_task_BUZZ,D_task_BUZZ_repeat);	


#endif //	_adxl362_H


