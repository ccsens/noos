/*****************************************************************************
update by cc @201700110
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

typedef struct _ts_lcm_pro_; Ӧ��Э����Ķ���     LCM��Э��------------
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



#ifndef __urec2protocol_H 
#define __urec2protocol_H

#include "../clib/type.h"	


#define D_s_protocol_len	64		//str���Э����Ҫ���ȴ�һЩ������bug�ĵط�������Ϊ����64bytes������
struct _s_protocol_
{//8byte
	U8 	rbr;
	U8 	filter1;
	U8 	filter2;	
	U8  (*pfun_get)(void);	
    U8 	num;  	//���յ�����Ŀע�����ݳ��ȵķ�Χ
    U8 	max;  	//���յ�����Ŀ�����ֵ
    U8 	sub_num;  	//���յ�����Ŀע�����ݳ��ȵķ�Χ
    U8 	head;	//���ձ�־ͷ��־
    U8 	ok;		//����Э��ok��־
    U8 	data_ok;		//����Э��ok��־   
    U8 	ucXor;   
    U8 	close;   
	U8 	cashe[4];
    U8 	array[D_s_protocol_len+1];//buffer �ĵ�һλ��    ����	 	 
    U8 	buf[D_s_protocol_len + 1];	//buffer �ĵ�һλ��    ����	 	  
    U8 	pro[16];				///����Э����	 	  
}; 

typedef struct 
{
	void(*L1_uart_rx_handle	)(struct _s_protocol_ *p);
	struct _s_protocol_ *st;

	
}Ts_uart_configRX_;


#ifdef doc43324234
__packed struct _s_uart_config_
{//8byte
    BYTE type;		//	lkt4105 ������
	UN_TYPE usart;
	uint32_t baudrate;
	uint32_t uart_mode;	// 1200,n,8,1
	Ts_uart_configRX_ *puart_config;
	BYTE d[D_s_protocol_len];

//	E =evenżУ��N = none��У��
//		����ͨ����11λ��������ʼλ��8������λ��У��λ��ֹͣλ��żУ�飺���д��͵���λ(���ַ��ĸ���λ��У��λ)��, "1" �ĸ���Ϊż�������緢��0x06,��λ����00000110����żУ��λ��0.���緢��0x07,��λ����00000111����żУ��λ��1.
};

extern void L1_UProtocol_init(void);

#endif



extern void L1_uart_2hexbuf(struct _s_protocol_ *p);
extern void L1_uart_2strbuf(struct _s_protocol_ *p);
#endif /* end __urec2protocol_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
