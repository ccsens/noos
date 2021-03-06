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



#ifndef __urec2protocol_H 
#define __urec2protocol_H

#include "../clib/type.h"	


#define D_s_protocol_len	64		//str类的协议需要长度大一些，容易bug的地方，限制为接收64bytes的数据
struct _s_protocol_
{//8byte
	U8 	rbr;
	U8 	filter1;
	U8 	filter2;	
	U8  (*pfun_get)(void);	
    U8 	num;  	//接收到的数目注意数据长度的范围
    U8 	max;  	//接收到的数目的最大值
    U8 	sub_num;  	//接收到的数目注意数据长度的范围
    U8 	head;	//接收标志头标志
    U8 	ok;		//接收协议ok标志
    U8 	data_ok;		//接收协议ok标志   
    U8 	ucXor;   
    U8 	close;   
	U8 	cashe[4];
    U8 	array[D_s_protocol_len+1];//buffer 的第一位是    长度	 	 
    U8 	buf[D_s_protocol_len + 1];	//buffer 的第一位是    长度	 	  
    U8 	pro[16];				///解析协议用	 	  
}; 

typedef struct 
{
	void(*L1_uart_rx_handle	)(struct _s_protocol_ *p);
	struct _s_protocol_ *st;

	
}Ts_uart_configRX_;


#ifdef doc43324234
__packed struct _s_uart_config_
{//8byte
    BYTE type;		//	lkt4105 的类型
	UN_TYPE usart;
	uint32_t baudrate;
	uint32_t uart_mode;	// 1200,n,8,1
	Ts_uart_configRX_ *puart_config;
	BYTE d[D_s_protocol_len];

//	E =even偶校验N = none无校验
//		串口通信是11位，包含起始位，8个数据位，校验位，停止位，偶校验：所有传送的数位(含字符的各数位和校验位)中, "1" 的个数为偶数。假如发送0x06,按位就是00000110，则偶校验位设0.假如发送0x07,按位就是00000111，则偶校验位设1.
};

extern void L1_UProtocol_init(void);

#endif



extern void L1_uart_2hexbuf(struct _s_protocol_ *p);
extern void L1_uart_2strbuf(struct _s_protocol_ *p);
#endif /* end __urec2protocol_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
