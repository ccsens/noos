#ifndef   _INIT_TIMER0_H
#define   _INIT_TIMER0_H

#include "../clib/Type.h"

#include "../clib/Bit.h"

#include "../bsp/hard_config.h"
#include "../ctask/tick.h"

extern void L1_time0_init(void);
//extern void L0_timer0_Init(void);
#define L0_timer0_open(x)	TR0 = x		//

// ����t_10ms ����,���t_10ms����Ϊ1ʱ���Ϊ(D_TIMER0_10MS_COUNT*��ʱ�����)
//#define	D_TIMER0_10MS_COUNT	1	//��ʱ��Ϊ 10msһ�ж� 
#define	D_1us_delay_para	1
#define	D_1ms_delay_para	993

#define L0_delay_1us()	NOP();NOP();NOP();NOP();	// 11.05926M  


#define L0_timer0_ONF(x) TR0 = (x)

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>��ʱ������>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define D_T0_load(h,l)		TH0 = h;TL0 = l;
#define D_TH016_1ms() 	   D_T0_load(0xfe,0xb4)	//((vU16)(65535 - 30000))		
//#define D_TH016_5ms()	   D_T0_load(0xf9,0x87)	//   0xf987 = 65535- 1656 

// 4M/12 = 1/3 M = 3us 10ms /3us = 3333 = 0xd05 = 65535-62202 = 0xffff-0xf2fa 
#define D_TH016_10ms()	   D_T0_load(0xf2,0xfa)	//   0xf987 = 65535- 1656  
// 4M while ʱ��Ϊ

//ϵͳʱ��Ϊ  4M / 12 = 333k  3us һ����ʱ���жϵļ����3us  ��ʱ����һ������������1/12  
//              0xfeb4 = 0xffff- 331  331*333us = 1ms                

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��ʱ������<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����t_10ms ����,���t_10ms����Ϊ1ʱ���Ϊ(D_TIMER0_10MS_COUNT*��ʱ�����)
//#define	D_TIMER0_10MS_COUNT	((U32)2)	//��ʱ��Ϊ 10msһ�ж� TYPE_BOARD_stc90c516rd

// ����t_10ms ����,���t_10ms����Ϊ1ʱ���Ϊ(D_TIMER0_10MS_COUNT*��ʱ�����)
#define D_T0_cycle()	D_TH016_10ms()
////------------------------------------------------------------
// 4M/12 = 1/3 M = 3us 10ms /3us = 3333 = 0xd05 = 65535-62202 = 0xffff-0xf2fa 
#define D_T2_load(h,l)		TH2 = h;TL2 = l;
//#define D_TH216_10ms()	   D_T2_load(0xf2,0xfa)	
#define D_TH216_10ms()	   D_T2_load(0xf2,0xfa)	
#define D_T2_cycle()	D_TH216_10ms()
#endif //_INIT_TIMER0_H


