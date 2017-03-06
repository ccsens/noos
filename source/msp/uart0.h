//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, ���ؿƼ�
/// All rights reserved.  
///  
/// @file            main.c
/// @brief           main app  
///  
///�����ļ�ʵ�ֵĹ��ܵ�������  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20150102
///  
///  
///     �޶�˵��������汾
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
update by cc @201501101001
��Զമ�� �� ��һ���� ������ ÿ�������Ƕ����Ļ��Ƿֿ����н��� �����Ǹ��ӵĻ������Ӧ�ü���
����Ҫƽ�������.

clib/clib.c:  
���õĺ��� 	��Ӳ���޹� 
���ô���ģʽ(���ڵ�����ͨѶ����������)����ĺ���,
һЩ����ģʽ�����(lcd�ȹ��������)��Ҳ��ʹ��  
					void Lc_print(void (*L0pf_send_uc)(char ww), char *dat,...)
-----------------------------------------------------------------------------------------
uartcom/Uprotocol2app  
  Э�鵽Ӧ��
  Ϊ����Ӧ��ͬ��ͨѶЭ����Ҫ��ͬ��uart������Ӧ ��Ӧ�����

typedef struct _ts_lcm_pro_; Ӧ��Э����Ķ���?    LCM��Э��------------
											L3_UARTcom0_exp_protocol ����Ӧ��Э��
-----------------------------------------------------------------------------------------
uartcom/urec2protocol: ���յ������ݷ��뵽ָ���ض�Э��Ļ����У���Э��ĸ�ʽ�й� һ���Ϊ ��ͷʽ���߱�βʽ
���õĴ���ͨѶ����		
 	struct _s_protocol_ �Ĺ���Э���(�ؼ��Ľṹ��)������------struct _s_protocol_
 							void L1_uart_2buf(struct _s_protocol_ *p)�������ݱ��浽ָ���ض�Э��Ļ�����
--------------------------------------------------------------------------------------------
msp/uartx.c    �ײ����	 ��cpu��� ���淢��Ҳ��������
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
    U8 	num;  	//���յ�����Ŀע�����ݳ��ȵķ�Χ

    U8 	now;  	///	��ǰbuf���ڵ�λ�� 0------(max-1)
    U8 	max;  	/// ��ǰbuf�����ֵ,Ҳ������Ҫ���͵ĳ���
    U8 	buf[D_send_buf_max + 1];//buffer �ĵ�һλ��    ����	  	 
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


