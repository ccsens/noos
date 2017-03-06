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
// 20160413 CC-ACC-VH02
// ������  J22 RXD0 TXD0
//P5_DIR	&= ~BIT1;							   //p5.1���TXD
//P5_DIR	|= BIT0;							   //p5.0����RXD
//P5_SEL0 &= ~(BIT0 +BIT1);					   //����P5.0  P5.1ΪUART0 RXD TXD 
//P5_SEL1 |= BIT0 +BIT1;

/*****************************************************************************
update by cc @201501101001
��Զമ�� �� ��һ���� ������ ÿ�������Ƕ����Ļ��Ƿֿ����н��� �����Ǹ��ӵĻ������Ӧ�ü���
����Ҫƽ�������.

uartcom/uartlib.c:  
���õĺ��� 	��Ӳ���޹� 
���ô���ģʽ(���ڵ�����ͨѶ����������)����ĺ���,
һЩ����ģʽ�����(lcd�ȹ��������)��Ҳ��ʹ��  
					void Lc_print(void (*L0pf_send_uc)(char ww), char *dat,...)
-----------------------------------------------------------------------------------------
uartcom/uartcom0  
  ��uart��ص�ͨѶЭ�� com + n 
  Ϊ����Ӧ��ͬ��ͨѶЭ����Ҫ��ͬ��uart������Ӧ ��Ӧ�����

typedef struct _ts_lcm_pro_; Ӧ��Э����Ķ���?    LCM��Э��------------
											L3_UARTcom0_exp_protocol ����Ӧ��Э��
-----------------------------------------------------------------------------------------
uartcom/uprotocol: ��Ҫ��Ϊ uartcom + n�����     �����㵽Ӧ�ò㻺��Ĺ���
���õĴ���ͨѶ����		
 	struct _s_protocol_ �Ĺ���Э���(�ؼ��Ľṹ��)������------struct _s_protocol_
 							void L1_uart_2buf(struct _s_protocol_ *p)�������ݱ��浽������
--------------------------------------------------------------------------------------------
msp/uartx.c    �ײ����	 ��cpu��� 
			L0_UART0_Init
						UART0_IRQHandler
						    	L0_Usend_uc----------s_at0
-----------------------------------------------------------------------------------------
********************************************************************************/
#include "uart0.h"	
//#include "msp_vc.h"	
//#define D_debug_time
struct _s_protocol_ s_at0;

struct _s_send_buf_ s_send_pool;
struct _s_send_buf_ s_send_bath;

//#define D_uart_baudrate(X)	PCON |= U0BRD;	(256 - s_sys_para.sys_clock * (1 + 1) / (32 * X))
#define D_uart_baudrate(X)		(256 - (unsigned char)(s_sys_para.sys_clock / 16 / X))

void L0_uart0_init(void)
{
	//UART��ʼ��
	P5_DIR  &= ~BIT1;								 //p5.1���TXD
	P5_DIR  |= BIT0;								 //p5.0����RXD
	P5_SEL0 &= ~(BIT0 +BIT1);						 //����P5.0  P5.1ΪUART0 RXD TXD 
	P5_SEL1 |= BIT0 +BIT1;

#ifdef D_sim_uart

  SCON  = 0x50;                   /* SCON: mode 1, 8-bit UART, enable rcvr    */
  TMOD |= 0x20;                   /* TMOD: timer 1, mode 2, 8-bit reload      */
  TH1   = 0xf3;                   /* TH1:  reload value for 2400 baud         */
  TR1   = 1;                      /* TR1:  timer 1 run                        */
  TI    = 1;                      /* TI:   set TI to send first char of UART  */
#else//#ifdef D_sim_uart

	BITN_1(PCON,BITN7);// �����ʷ���	
	//U0_TM = 256- (vU8)n;
	//U0_TM = D_uart_baudrate(19200);//  4m double �������
	U0_TM = 0xf3;//D_uart_baudrate(19200);//  4m double �������
	
	///��ģʽ1�£�����ͨ��TXD�źŷ��Ͳ���ͨ��RXD�źŽ��գ���������10λ���:����ʼλ�� 0����
	///ʼ����������8������λ�����λ�ȣ����λ�󣩡�����ǽ���λ�� 1����ģʽ1�µĲ������ɶ�
	///ʱ��1�Ͷ�ʱ��2���ƣ������ǿɱ�̵ġ��������ڿ��ƼĴ���SM0���㣬 SM1�á� 1������ɹ���
	///��ģʽ1�¡�
	SM0 = 0;SM1 = 1;//  0 bit0---bit7(8λ)  ���� 1, �������ǵ͵�ƽΪ'1'
	SM2 = 0;// close multicommunication
	REN = 1; //enable receive mode
	U0_TMR |= UXTMR;    						     //���������ʷ�����

#endif//#ifdef D_sim_uart		
	L0_uart0_IntSendOver();
	ES = 1;										 //�򿪴����ж� 
}

unsigned char  L0_uart0_get(void){return SBUF;}

#if 0


void L0_uart0_set(unsigned char cww)
{
		SBUF = cww;	
}
#define Ld_send_buf_fill(X,Y)	s_send_buf.pbuf_fill = X;s_send_buf.num_fill = Y;
//  ����buf���� �е�0----(num-1)
void L0_uart0_sendbuf(U8 buf[],U8 num)
{
//	s_send_buf.num	.buf   D_send_buf_max
	//s_send_buf.buf[];
	if(0 != num)
	{
		while(L0_uart0_SendIntBusy()){;}
		s_send_buf.num = s_send_buf.num_fill;
		s_send_buf.n = s_send_buf.num_fill;
		s_send_buf.pbuf = s_send_buf.pbuf_fill;
		L0_uart0_IntTIClear();
		L0_uart0_IntSendStart();
		SBUF = s_send_buf.pbuf[0];
	}
}

void L0_uart0_ushex(U16 ww)
{//
	U8 t;	
	t = (U8)(((ww >> 8)&0x00ff));
	L0_uart0_uchex(t);
	t = (U8)(((ww )&0x00ff));
	L0_uart0_uchex(t);		
}

void L0_uart0_ul(U32 ww)
{
	U_U32 ultemp;
	ultemp.dWord = ww;	
	L0_uart0_uc(ultemp.BYTE4.byte0);	
	L0_uart0_uc(ultemp.BYTE4.byte1);
	L0_uart0_uc(ultemp.BYTE4.byte2);
	L0_uart0_uc(ultemp.BYTE4.byte3);		
}


//  ����buf���� �е�0----(num-1)
void L0_uart0_sendbuf444444(U8 buf[],U8 num)
{
//	s_send_buf.num	.buf   D_send_buf_max
	//s_send_buf.buf[];
	if(0 != num)
	{
		while(L0_uart0_SendIntBusy()){;}
		s_send_buf.num = num;
		s_send_buf.usn = num;
		s_send_buf.pbuf = buf;
		L0_uart0_IntTIClear();
		L0_uart0_IntSendStart();
		SBUF = s_send_buf.pbuf[0];
	}
	
}
void L0_uart0_uc22(U8 ww)
{
	//while(L0_uart0_SendIntBusy()){;}
	//L0_uart0_sendbuf(&ww,1);
	while(L0_uart0_SendIntBusy()){;}
//fixme 		if(L0_uart0_SendIntFree())
	{
		s_send_pool.num = 1;
		s_send_pool.now = 1;
		s_send_pool.buf[0] = ww;
		L0_uart0_IntTIClear();
		L0_uart0_IntSendStart();
		L0_uart0_set(ww);
	}
}

#endif


void L0_uart0_uc(U8 ww)
{
	s_send_bath.max = 1;
	s_send_bath.buf[0] = ww;
	L0_uart0_sendbuf();
}


void L0_uart0_0d0a(void)
{
	s_send_bath.max = 2;
	s_send_bath.buf[0] = 0x0d;
	s_send_bath.buf[1] = 0x0a;
	L0_uart0_sendbuf();
}
		//		L0_uart0_uc(cguHex2Char[D_uc_low(s->sec)][0]);
void L0_uart0_uchex(U8 ww)
{
	s_send_bath.max = 2;
	s_send_bath.buf[0] = cguHex2Char[D_uc_low(ww)][1];
	s_send_bath.buf[1] = cguHex2Char[D_uc_high(ww)][1];
	L0_uart0_sendbuf();
}

/******************************************************************** 
*
SBUF=value; 	   //value�Ǵ�ad�ɼ��������ݣ�ͨ�����ڷ�����λ��
	  while(!TI);
	  TI=0;

SBUF=P1;//д������	
 while(0==TI);//�ȴ��������  
 TI=0;//����жϱ�־  

***********************************************************************/

/******************************************************************** 
*
* ����: L0_Usend_uc_hex
* ˵��: ����:L0_Usend_uc_hex(0x0c); output " 0c  " 
* ����: ��������
* ����: SendHUc����Lc_HexToChar����
* ����:
* ����ֵ: ��

***********************************************************************/


void L0_uart0_uchex333(U8 ww)
{
	L0_uart0_uc(Lc_Hex2Char(ww>>4));
	L0_uart0_uc(Lc_Hex2Char(ww&0x0f));	
}



void L0_uart0_ulhex(vU32 ww)
{
	U_U32 ultemp;
	ultemp.dWord = ww;	
	L0_uart0_uchex(ultemp.BYTE4.byte0);	
	L0_uart0_uchex(ultemp.BYTE4.byte1);
	L0_uart0_uchex(ultemp.BYTE4.byte2);
	L0_uart0_uchex(ultemp.BYTE4.byte3);		
}


/*************************************************
UART �ж�
*************************************************/

void INTERRUPT_UART(void) interrupt Interrupt_Uart0_Uart1_Number// using 2

{
	//D_led_D0_REV();
//------------------------------------------------
	if(L0_uart0_IntRI())					//�����U0�����ж�	
	{L0_uart0_IntRIClear(); 				//��������жϱ�־
		//L1_uart_2buf(&s_at0);
		L1_uart_2strbuf(&s_at0);
		//D_led_D2_REV();
	}
//------------------------------------------------
	else
	{
		if(L0_uart0_IntTI())				//�����U0�����ж�
		{L0_uart0_IntTIClear();			//��������жϱ�־
		#if 0
		//	if(s_send_buf.n < 1){while(9)D_led_D1_REV();D_led_debug_REV();}
			s_send_buf.usn --;
			if(0 != s_send_buf.usn)
			{
				//if(s_send_buf.num <= s_send_buf.n)	{while(9){D_led_D2_REV();}}
				L0_uart0_set(s_send_buf.Txbuf[s_send_buf.num - s_send_buf.usn]);
			}else
			{
				L0_uart0_IntSendOver();		//���Է�����һ������
			}
		#else
			if(s_send_pool.max != s_send_pool.now)
			{
				L0_uart0_set(s_send_pool.buf[s_send_pool.now]);
				s_send_pool.now ++;
			}else
			{	
				s_send_pool.max = 0;s_send_pool.now = 0;
				L0_uart0_IntSendOver();		//���Է�����һ������
			}
		#endif

		}
	}	
	//D_led_D1_REV();
}


#define D_task_uart0_buf_send  0x11
#define D_task_uart0_buf_pre  0x12
#define D_task_uart0_buf_over  0x13


//  ����buf���� �е�0----(num-1)
void L0_uart0_sendbuf(void)
{	
	unsigned char n = 0;
	//s_send_bath.max = 1;
	//s_send_bath.0 = 1;
	//s_send_bath.buf[0] = ww;
	/// s_send_bath.buf  s_send_bath.max �Ѿ��ڵ���ǰд��	
	if(s_send_bath.max>= D_send_buf_max)
	{
		s_send_bath.max = 3;
	}
	ES = 0;
	if(L0_uart0_SendIntFree())
	{///  �ϴε��Ѿ����������,���ߵ�һ�ο�ʼ
	/// (s_send_pool.now == s_send_pool.max = 0 buf��Ϊ��)
		for(n = 0;n < s_send_bath.max; n++)
		{
			s_send_pool.buf[n] = s_send_bath.buf[n]; 
		}
		//s_send_pool.now = 0;
		s_send_pool.max = s_send_bath.max;
		L0_uart0_IntTIClear();
		L0_uart0_IntSendStart();
		s_send_pool.now = 1;
		L0_uart0_set(s_send_pool.buf[0]);
	}else
	{// ��Ҫ����
		///  [0]--?--[pool.now]--?--[pool.max-1].......................................
		///  [0]--?--[pool.now]--?--[pool.max]+[bath.0]--?---[bath.max-1].............
		for(n = 0;n < s_send_bath.max; n++)
		{
			s_send_pool.buf[s_send_pool.max] = s_send_bath.buf[n];
			s_send_pool.max ++;
			if(s_send_pool.max >= D_send_buf_max)
			{
				s_send_pool.max = D_send_buf_max;
			}
		}
	}
	ES = 1;
}



/******


struct _s_task_uart0_ s_task_uart0;

void L0_uart0_sendstr(U8 *str)
{
	L0_uart0_sendbuf(str,strlen(str));
}
/// ���ͳ��� 256bytes������
void L0_uart0_sendbuf16(U8 buf[],vU16 num)
{
	if(L3_task_s_free(s_task_uart0))
	{
	if(0 != num)
	{
		s_task_uart0.num =	num;
		s_task_uart0.pbuf =  buf;
		L3_task_s_go(s_task_uart0,D_task_uart0_buf_pre); 
	}	
}
}


//  L3_UART0_handdle(&s_task_uart0);
void L3_UART0_handdle(struct _s_task_uart0_ *s)
{  
	switch(s->task.sh)
	{
		case D_task_init://
		//	Lc_print("\r\n D_task_init");
			L2_task_go(D_task_close);
		break;	
		case D_task_uart0_buf_pre:
			if(L0_uart0_SendIntBusy())
			{/// wait preview uart send over
			}else
			{
				L2_task_go(D_task_uart0_buf_send);
			}
		break;
		case D_task_uart0_buf_send:			
			
			//s_adc_vc.flag = D_flag_lock;			
			s_send_pool.num = s->num;
			s_send_pool.now = s->num;
   			Lc_buf_copy_uc(s_send_pool.buf,s->pbuf,s->num);
			
			L0_uart0_IntTIClear();
			//D_led_D1_ON();  66ms 129��  D_led_D1_OFF();
			L0_uart0_IntSendStart();
			
			s_array_hd.ucArray_f[s_array_hd.usN] = 20;
			s_array_hd.ucArray_f[s_array_hd.usN+1] = 3;//  ���Ǻ�,��֪����ǰ��usN���˶���
			
			L0_uart0_set(s_send_pool.buf[0]);
			L2_task_go(D_task_uart0_buf_over);
		break;
		case D_task_uart0_buf_over:			
			if(L0_uart0_SendIntFree())
			{	
				L2_task_go(D_task_close);			
			}else
			{
				//D_led_D1_REV();
			}
		break;
		L2_task_switch_default_idelay();
	}
}

struct _s_task_uart0_
{
	TS_task task;    
	vU16 num;  	//���յ�����Ŀע�����ݳ��ȵķ�Χ
    U8 	*pbuf;//buffer �ĵ�һλ��    ����	 	 
    
};
extern struct _s_task_uart0_ s_task_uart0;
extern void L3_UART0_handdle(struct _s_task_uart0_ *s);




******/


