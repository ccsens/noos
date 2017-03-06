

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
#define D_CMD_cmd_G5V	 	0x52	//�̵�����

typedef struct 
{//8byte
    U8 Filter1;	//֡ ͷ 
    U8 Filter2;	//֡ ͷ 
	U8 len;     //���ݳ���
    U8 cmd; 	//����    
    U8 dat[(52+11)*4]; //���� //fixme 
    vU16 ocr; //ָ������ݵ�CRC У�� 
}Ts_cmd_pro;

extern void L1_uart0_rx_handle(void);
extern struct _s_protocol_ s_at0;
extern void L3_UARTcom0_exp_protocol(struct _s_protocol_ *p);
extern void L0_UARTcom_Init(struct _s_protocol_ *p);


#endif /* end __uprotocol2app_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
