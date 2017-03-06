#ifndef   _INIT_TIMER0_H
#define   _INIT_TIMER0_H

#include "../clib/Type.h"

#include "../clib/Bit.h"

#include "../bsp/hard_config.h"
#include "../ctask/tick.h"

extern void L1_time0_init(void);
//extern void L0_timer0_Init(void);
#define L0_timer0_open(x)	TR0 = x		//

// 他和t_10ms 关联,如果t_10ms递增为1时间隔为(D_TIMER0_10MS_COUNT*定时器间隔)
//#define	D_TIMER0_10MS_COUNT	1	//定时器为 10ms一中断 
#define	D_1us_delay_para	1
#define	D_1ms_delay_para	993

#define L0_delay_1us()	NOP();NOP();NOP();NOP();	// 11.05926M  


#define L0_timer0_ONF(x) TR0 = (x)

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>定时器设置>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define D_T0_load(h,l)		TH0 = h;TL0 = l;
#define D_TH016_1ms() 	   D_T0_load(0xfe,0xb4)	//((vU16)(65535 - 30000))		
//#define D_TH016_5ms()	   D_T0_load(0xf9,0x87)	//   0xf987 = 65535- 1656 

// 4M/12 = 1/3 M = 3us 10ms /3us = 3333 = 0xd05 = 65535-62202 = 0xffff-0xf2fa 
#define D_TH016_10ms()	   D_T0_load(0xf2,0xfa)	//   0xf987 = 65535- 1656  
// 4M while 时间为

//系统时钟为  4M / 12 = 333k  3us 一个定时器中断的间隔是3us  定时器的一个机器周期是1/12  
//              0xfeb4 = 0xffff- 331  331*333us = 1ms                

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<定时器设置<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 他和t_10ms 关联,如果t_10ms递增为1时间隔为(D_TIMER0_10MS_COUNT*定时器间隔)
//#define	D_TIMER0_10MS_COUNT	((U32)2)	//定时器为 10ms一中断 TYPE_BOARD_stc90c516rd

// 他和t_10ms 关联,如果t_10ms递增为1时间隔为(D_TIMER0_10MS_COUNT*定时器间隔)
#define D_T0_cycle()	D_TH016_10ms()
////------------------------------------------------------------
// 4M/12 = 1/3 M = 3us 10ms /3us = 3333 = 0xd05 = 65535-62202 = 0xffff-0xf2fa 
#define D_T2_load(h,l)		TH2 = h;TL2 = l;
//#define D_TH216_10ms()	   D_T2_load(0xf2,0xfa)	
#define D_TH216_10ms()	   D_T2_load(0xf2,0xfa)	
#define D_T2_cycle()	D_TH216_10ms()
#endif //_INIT_TIMER0_H


