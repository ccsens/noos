//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            main.c
/// @brief           main app  
///  
///（本文件实现的功能的详述）  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20150102
///  
///  
///     修订说明：最初版本
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
update by cc @201501101001
针对多串口 和 单一串口 有区别 每个串口是独立的还是分开的有讲究 程序是复杂的还是软件应用简单是
个需要平衡的事情.

clib/clib.c:  
公用的函数 	和硬件无关 
放置串行模式(串口等其他通讯总线类的输出)输出的函数,
一些覆盖模式输出的(lcd等固屏输出的)的也可使用  
					void Lc_print(void (*L0pf_send_uc)(char ww), char *dat,...)
-----------------------------------------------------------------------------------------
uartcom/Uprotocol2app  
  协议到应用
  为了适应不同的通讯协议需要不同的uart口来对应 和应用相关

typedef struct _ts_lcm_pro_; 应用协议包的定义?    LCM的协议------------
											L3_UARTcom0_exp_protocol 解析应用协议
-----------------------------------------------------------------------------------------
uartcom/urec2protocol: 接收到的数据放入到指向特定协议的缓存中，和协议的格式有关 一般分为 标头式或者标尾式
公用的串口通讯定义		
 	struct _s_protocol_ 的公共协议包(关键的结构体)的声明------struct _s_protocol_
 							void L1_uart_2buf(struct _s_protocol_ *p)串行数据保存到指向特定协议的缓冲中
--------------------------------------------------------------------------------------------
msp/uartx.c    底层代码	 和cpu相关 缓存发送也放在里面
			L0_UART0_Init
						UART0_IRQHandler
						    	L0_Usend_uc------UserDef
-----------------------------------------------------------------------------------------
********************************************************************************/


#ifndef _uart0_H 
#define _uart0_H

#include "../bsp/hard_config.h"
#include "../cpu/SHC6601_system.h"

#include "../uartcom/Uprotocol2app.h"

#include "../clib/Clib.h"
#include "../ctask/task.h"	

extern struct _s_protocol_ s_at0; 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define D_send_buf_max		253	/// 9600bps = 10000bps = 1000 Bps = 1Byte/ms
									/// 19200bps = 20000bps = 2000Bps = 2Byte/ms  = 1Byte/0.5ms
									///  128Bytes = 128*0.5ms = 64ms
struct _s_send_buf_
{//8byte
    U8 	num;  	//接收到的数目注意数据长度的范围

    U8 	now;  	///	当前buf所在的位置 0------(max-1)
    U8 	max;  	/// 当前buf的最大值,也就是需要发送的长度
    U8 	buf[D_send_buf_max + 1];//buffer 的第一位是    长度	  	 
}; 
extern struct _s_send_buf_ s_send_pool;
extern struct _s_send_buf_ s_send_bath;



#define L0_uart0_set(x)	SBUF = (x);	
//#define L0_uart0_get()		(SBUF)
extern unsigned char  L0_uart0_get(void);


#define L0_uart0_IntSendOver()	(gRegU_SO= 1)
#define L0_uart0_IntSendStart()	(gRegU_SO = 0)

#define L0_uart0_SendIntBusy()	(0 == gRegU_SO)

#define L0_uart0_SendIntFree()	(0 != gRegU_SO)

#define L0_uart1_IntRecOver()		(gRegU_SO = 1)
#define L0_uart1_IntRecStart()	(gRegU_SO = 0)
#define L0_uart1_SendRecBusy()	(0 == gRegU_SO)


#define L0_uart0_IntRI()	BITN_G(SCON,U0RI) 
#define L0_uart0_IntTI()	BITN_G(SCON,U0TI) 

#define L0_uart0_IntRIClear()	BITN_0(SCON,U0RI)
#define L0_uart0_IntTIClear()	BITN_0(SCON,U0TI)

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void L0_uart0_init(void);
void L0_uart0_uchex(U8 ww);

void L0_uart0_ulhex(vU32 ww);

void L0_uart0_ul(vU32 ww);

extern void L0_uart0_0d0a(void);
extern void L0_uart0_uc(U8 ww);
///////////////////////////////////////////////////////////////
extern void L0_uart0_sendbuf16(U8 buf[],vU16 num);
extern void L0_uart0_sendbuf(void);
#endif //	_uart0_H


