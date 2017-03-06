/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			MX25L1602.c
** Descriptions:		SPI�µ�SST25VF016B���������� 
**
**------------------------------------------------------------------------------------------------------
** Created by:			Litiantian
** Created date:		2007-04-16
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/
#include "time.h"	
#include "../cpu/SHC6601_system.h"
#include "../cpu/SHC16L_macro.h"

#include "../debug/Debug_led.h"
#include "../app/App_fsk.h"

extern void L2_fsk_curve2(void);
/*********************************************************************************************************
* Function Name:        timer0Isr
* Description:          TIMER0 �жϴ�����
* Input:                ��
* Output:               ��
* Return:               ��
*********************************************************************************************************/
void L0_timer2_Init(void)
{
	TR2 = 0;// �ر� CT0
	D_T2_cycle();
	BITN_1(PERI_CLK2,TIMER_CLKEN);//  timer ʱ�ӿ���
	BITN_1(PERI_CLK2,PORT_CLKEN);//  port ʱ�ӿ���
	TMM2 = 0;		//Timer2 ����ģʽѡ��0�� 16 λ����������ģʽ1: 8λ�Զ��ؼ��ع���ģʽ
	//ET2 = 1;	//CT0 interrupt enable1����ʱ�� 0,��ʱ�� 2 �ж�ʹ��
	ET0 = 1;	//CT0 interrupt enable
	TR2 = 1;// ����������2
}

#if 0
void L0_timer0_Init(void)
{
	TR0 = 0;// �ر� CT0
	D_T0_cycle();
	 BITN_1(PERI_CLK2,TIMER_CLKEN);//  timer ʱ�ӿ���
	//if(TM0_OVF )// timer0 �����ʶΪ


///3 GATE0 ��ʱ��0�ſ�λ
///0����TR0=1ʱ����ʱ��1���������ⲿ�ſ����루 P50��P26���޹�
///1��ֻ�е�TR0=1, �����ⲿ�ſ�����(P50��P26)Ϊ1ʱ����ʱ��1����

///2 CT0 ��ʱ�� 0 ����ѡ��
///0����ʱ�����ܣ���ʱ�� 1 ����Ƶ/12 �����м���
///1�����������ܣ������� 1 ���ⲿ���루 P51 �� P27���½��ؽ��м���

///1 M10 M10 M00 ������/��ʱ�� 0 ������ʽ
///0 0 ģʽ 0: 13 λ������/��ʱ��
///0 1 ģʽ 1�� 16 λ������/��ʱ��
///1 0 ģʽ 2�� ����Զ����� 8 λ������/��ʱ
///1 1 ģʽ 3�� 2 �� 8 λ������/��ʱ��
///0 M00

	BITN_0(TMOD,BITN3);	// 0����TR0=1ʱ����ʱ��1���������ⲿ�ſ����루 P50��P26���޹�
	BITN_0(TMOD,BITN2);	//0����ʱ�����ܣ���ʱ�� 1 ����Ƶ/12 �����м���
	BITN_0(TMOD,BITN1);	BITN_1(TMOD,BITN0);	///ģʽ 1�� 16 λ������/��ʱ��
	ET0 = 1;	//CT0 interrupt enable
	TR0 = 1;// ����������0
}
#else
void L0_timer0_Init_extinput(void)
{
	BITN_1(P2_DIR,BITN7);	//�˿� Px7 ����������üĴ���1�����ó�����0�����ó����

	BITN_1(P2_SEL2,BITN7);
	BITN_0(P2_SEL1,BITN7);	///10: P27 �����óɼ����� Timer0 ʱ������˿�
	BITN_0(P2_SEL0,BITN7);	/// no  lcd segment
	
	TR0 = 0;// �ر� CT0
	D_T0_cycle();
	 BITN_1(PERI_CLK2,TIMER_CLKEN);//  timer ʱ�ӿ���
	//if(TM0_OVF )// timer0 �����ʶΪ


///3 GATE0 ��ʱ��0�ſ�λ
///0����TR0=1ʱ����ʱ��1���������ⲿ�ſ����루 P50��P26���޹�
///1��ֻ�е�TR0=1, �����ⲿ�ſ�����(P50��P26)Ϊ1ʱ����ʱ��1����




///2 CT0 ��ʱ�� 0 ����ѡ��
///0����ʱ�����ܣ���ʱ�� 1 ����Ƶ/12 �����м���
///1�����������ܣ������� 1 ���ⲿ���루 P51 �� P27���½��ؽ��м���

///1 M10 M10 M00 ������/��ʱ�� 0 ������ʽ
///0 0 ģʽ 0: 13 λ������/��ʱ��
///0 1 ģʽ 1�� 16 λ������/��ʱ��
///1 0 ģʽ 2�� ����Զ����� 8 λ������/��ʱ
///1 1 ģʽ 3�� 2 �� 8 λ������/��ʱ��
///0 M00

	BITN_0(TMOD,BITN3);	/// �ſ���Ч 3 //GATE0 ��ʱ��0�ſ�λ 0����TR0=1ʱ����ʱ��1���������ⲿ�ſ����루 P50��P26���޹�
	BITN_1(TMOD,BITN2);	/// ����������1�����������ܣ������� 1 ���ⲿ���루 P51 �� P27���½��ؽ��м���
	BITN_0(TMOD,BITN1);	BITN_1(TMOD,BITN0);	///ģʽ 1�� 16 λ������/��ʱ��
	ET0 = 1;	//CT0 interrupt enable
	TR0 = 1;// ����������0
}


#endif



void L1_time0_init(void)
{
	L1_tick_init();
	//L0_timer0_Init();//
	L0_timer0_Init_extinput();
	L0_timer2_Init();
}




//#define	D_TIMER0_10MS_COUNT	56
void TIMER0_IRQHandler (void) interrupt Interrupt_Timer0_Timer2_Number// using 0
{//
#ifndef D_sim_timer0
	if(TM2_OVF)
#endif		
	{TM2_OVF = 0;
	//	D_led_THB_REV();
		D_T2_cycle();
		L1_tick_tick();
		//L2_fsk_curve2();
		//if(0 == s_array_hd.savef)
		{
			s_array_hd.savef = 1;
			
			s_array_hd.hn = TH0;
			s_array_hd.zn = TL0;
			TH0 = 0;
			TL0 = 0;
		}
	}
#ifndef D_sim_timer0

else

	{TM0_OVF = 0;
	//	D_led_DEBUG_REV();
		D_T0_cycle();
	//	L1_tick_tick();

	}
#endif
}


