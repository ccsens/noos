
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



#include "urec2protocol.h"
/*
void L1_UProtocol_init(void)
{
	//L0_UARTcom0_Init();


}

*/
/// �ڴ����ж��е��� uart hardware to buffer  ���ڵ�������
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
		{		// p->ok = 1;//�յ� ��־��1	; 55 aa 44 55
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
						p->ok = 1;//�յ� �������,�����и��ط���0�������޷��ٴν��ܱ���
					//	D_led_D2_OFF();
					}		
					p->num = 0; 	//����if (p->ok != 1) ��
					p->head = 0;	//����if (p->ok != 1) ��
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
			p->ok = 1;//�յ� �������,�����и��ط���0�������޷��ٴν��ܱ���
			p->num = 0;		
		}
}


/******************************************************************************
**                            End Of File
******************************************************************************/
