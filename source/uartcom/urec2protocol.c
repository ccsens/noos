
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



#include "urec2protocol.h"
/*
void L1_UProtocol_init(void)
{
	//L0_UARTcom0_Init();


}

*/
/// 在串口中断中调用 uart hardware to buffer  串口到缓存中
void L1_uart_2hexbuf(struct _s_protocol_ *p)
{
//		unsigned int i;
		//p->cashe[3] = p->cashe[2];
		//p->cashe[2] = p->cashe[1];
		p->cashe[1] = p->cashe[0];
		p->cashe[0] = p->pfun_get();// 
		//p->cashe[0] = SBUF;// 
		//D_led_debug_REV();
	//	p->ok = 1;
		//	D_led_D2_ON();D_led_D2_OFF();D_led_D2_ON();
		if (p->head||((p->cashe[0] == p->filter1)&&(p->cashe[1] == p->filter2)))
		{		// p->ok = 1;//收到 标志置1	; 55 aa 44 55
			p->head = 1;
			p->num ++;			
			p->buf[p->num] = p->cashe[0];	
			if(p->num >= D_s_protocol_len)
			{
				p->num = 0;
			}
			//D_led_D2_OFF();

			if(p->num > 8)
			{// protect
				p->head = 0;p->ok = 0;p->num = 0; 
				{
					//while(9)
					{
						//	D_led_D1_ON();D_led_D1_REV();D_led_D1_ON();	D_led_D2_ON();D_led_D2_REV();D_led_D2_ON();
					}
				}

			}else
			{
				if (p->num >= (p->buf[2]+2))
				{// aa 55 (03) 11 22 33
				
					if (p->ok != 1)
					{	  
					//	D_led_D2_ON();
						p->buf[0] = p->filter2;
						p->ok = 1;//收到 命令结束,必须有个地方清0，否则无法再次接受报文
					//	D_led_D2_OFF();
					}		
					p->num = 0; 	//放在if (p->ok != 1) 外
					p->head = 0;	//放在if (p->ok != 1) 外
				}


			}

		}
		else {} 
}
//L1_uart_2strbuf(&s_at0);
void L1_uart_2strbuf(struct _s_protocol_ *p)
{
//		unsigned int i;
		//p->cashe[3] = p->cashe[2];
		//p->cashe[2] = p->cashe[1];
		p->cashe[1] = p->cashe[0];
		p->cashe[0] = p->pfun_get();// 		
		p->buf[p->num] = p->cashe[0];	
		p->num ++;	
		if(p->num >= D_s_protocol_len)
		{
			p->num = 0;
		}
		if ((p->cashe[0] == p->filter1)&&(p->cashe[1] == p->filter2))// 0d0a
		{	//               0a                 0d
			p->max = p->num;
			p->buf[p->max] = 0;
			if(0 == p->ok)
			{
				for(;0 != p->num;p->num --)
				{
					p->array[p->num] = p->buf[p->num];
				}
				p->array[0] = p->buf[0];
			}
			p->ok = 1;//收到 命令结束,必须有个地方清0，否则无法再次接受报文
			p->num = 0;		
		}
}


/******************************************************************************
**                            End Of File
******************************************************************************/
