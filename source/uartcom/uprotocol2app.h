

/*****************************************************************************
update by cc @201700110
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

typedef struct _ts_lcm_pro_; 应用协议包的定义�     LCM的协议------------
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


#ifndef __uprotocol2app_H 
#define __uprotocol2app_H

#include "urec2protocol.h"
//#include "../debug/debug_drv.h"	
#include "../ctask/task.h"	


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//#define Array_ts_cmd_pro0  ((unsigned char *) &ts_cmd_pro0)
//#define Array_ts_cmd_pro0_temp  ((unsigned char *) &ts_cmd_pro0_temp)  


//L0_type_byte(ts_cmd_pro0)[]
//#define D_CMD_Filter1 	0xA5
//#define D_CMD_Filter2 	0x5A
#define D_CMD_Filter1 	0x0a
#define D_CMD_Filter2 	0x0d

#define D_CMD_cmd_write	 	0x90
//a5 5a 210 90 ......
#define D_CMD_cmd_adc	 	0x53
#define D_CMD_cmd_G5V	 	0x52	//继电器打开

typedef struct 
{//8byte
    U8 Filter1;	//帧 头 
    U8 Filter2;	//帧 头 
	U8 len;     //数据长度
    U8 cmd; 	//命令    
    U8 dat[(52+11)*4]; //数据 //fixme 
    vU16 ocr; //指令和数据的CRC 校验 
}Ts_cmd_pro;

extern void L1_uart0_rx_handle(void);
extern struct _s_protocol_ s_at0;
extern void L3_UARTcom0_exp_protocol(struct _s_protocol_ *p);
extern void L0_UARTcom_Init(struct _s_protocol_ *p);


#endif /* end __uprotocol2app_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
