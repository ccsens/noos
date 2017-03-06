//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, ���ؿƼ�
/// All rights reserved.  
///  
/// @file            vc.c
/// @brief           vc driver app  
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
//
//
///		adc app function	adc
///		adc hardware  driver SHC6601_adc
//
//////////////////////////////////////////////////////////////////////////



/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "msp_adc.h"	
#include "../app/App_fsk.h"
/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/***************************************************************************//**
 * @brief Initializes communication with the device and checks if the part is
 *        present by reading the device id.
 *
 * @return 1 if the initialization was successful and the device is present,
 *         0 if an error occurred.
*******************************************************************************/


struct  _s_adc_ s_adc = {
	0,
};
//// ���� ADCͨ��
void L0_adc_ch(unsigned char ch)
{
	BITN_1(P0_SEL0,1<<ch);		//���ó�	ADCͨ��ch������
	BITN_0(ADC1,BITN5|BITN4|BITN3);	//
	BITN_1(ADC1,ch<<3);

/**************
543----ADC_CHL_SEL[2:0] adc����ͨ��ѡ��
5:3 ADC_CHL_SEL[2:0] ADC ����ͨ��ѡ��
111��ѡ���ڲ��¶ȴ�����
110��ѡ���ⲿ P06 ����
101��ѡ���ⲿ P05 ����
100��ѡ���ⲿ P04 ����
011��ѡ���ⲿ P03 ����
010��ѡ���ⲿ P02 ����
001��ѡ���ⲿ P01 ����
000��ѡ���ⲿ P00 ����
**********************************/
}

void L0_adc_EIO_Init(void)
{
				
/// ����ͨ�ò���
/// ģ��ʹ��
/// step 1.1: ϵͳ����ʱ��Դ
/// step 1.2: ϵͳ����ʱ��ʹ��
/// step 1.3: ϵͳģ��ʹ��

/// ģ������
/// step 2.1: ģ����������:  
/// step 2.2: ����ģ��ʹ��(����ADC ������ BGR)

/// �ж�����
/// step 3.1: ģ���ж����ȼ�
/// step 3.2: ģ���ж�����
/// step 3.3: ȫ���ж�(������ģ�鹲��,��������Ҫ��ע)
///
/// ����ģ��
/// step 4.1: ����ģ�� ��ʼ����



/// ģ��ʹ��
//---------------------------------------------------------------------------
/// step 1.1: ϵͳ����ʱ��Դ
	BITN_1(PERI_CLK0,ADC_CLKEN);
//---------------------------------------------------------------------------
/// step 1.2: ϵͳ����ʱ��ʹ��
//---------------------------------------------------------------------------
/// step 1.3: ϵͳģ��ʹ��
	D_adc_open();
//---------------------------------------------------------------------------
/// ģ������
/// step 2.1: ģ����������:

	//BITN_1(ADC1,BITN7);						///	 1X�� ѡ���ⲿ�ο���ѹ
	BITN_0(ADC1,BITN7);BITN_1(ADC1,BITN7);	///	 01���ڲ� 1.5v �ο���ѹ
	//BITN_0(ADC1,BITN7);BITN_0(ADC1,BITN7);	/// 00���ڲ� 2.5v �ο���ѹ

/// Ĭ��ͨ��ѡ��
/// ����ʱ��
	//BITN_0(ADC1,BITN2);BITN_0(ADC1,BITN1);	///ϵͳ
	//BITN_0(ADC1,BITN2);BITN_1(ADC1,BITN1);	///sys/2
	//BITN_1(ADC1,BITN2);BITN_0(ADC1,BITN1);	///sys/4
	BITN_1(ADC1,BITN2);BITN_1(ADC1,BITN1);	///sys/8
/// ����ʱ��
	BITN_0(ADC2,BITN7);BITN_0(ADC2,BITN6);	///3
	//BITN_0(ADC2,BITN7);BITN_1(ADC2,BITN6);	///6
	//BITN_1(ADC2,BITN7);BITN_0(ADC2,BITN6);	///1
	//BITN_1(ADC2,BITN7);BITN_1(ADC2,BITN6);	///9

///����ģʽ
	//BITN_1(ADC2,BITN3);//����ģʽ 	single
	BITN_0(ADC2,BITN3);//����ģʽ	continue

///����ģʽ
	//BITN_0(ADC2,BITN2);	///1���Ҷ��롣���Ϊ xxxxMSB~LSB
	BITN_1(ADC2,BITN2);	///0������롣���Ϊ MSB~LSBxxxx  ��ȡ adcH ����
//ADC ������������	
	BITN_1(ADC3,BITN2);BITN_1(ADC3,BITN1);	///11: ��� ADC ��������(�Ƽ�)
//---------------------------------------------------------------------------
/// step 2.2: ����ģ��ʹ��(����ADC ������ BGR)

	BITN_1(BGRC,BGR_EN);

//---------------------------------------------------------------------------
/// �ж�����
/// step 3.1: ģ���ж����ȼ�
//---------------------------------------------------------------------------
/// step 3.2: ģ���ж�����
	BITN_1(AIE,AIE_ADCE);
//---------------------------------------------------------------------------
/// step 3.3: ȫ���ж�(������ģ�鹲��,��������Ҫ��ע)
///

//---------------------------------------------------------------------------
	L0_ADC_START();	/// ��ʼ����
}
void L0_adc_EIO_close(unsigned char sw)
{
	if (sw)
	{
	D_adc_open();
	BITN_0(BGRC,BGR_EN);
	BITN_0(AIE,AIE_ADCE);
	L0_ADC_START();
	}else
	{
	D_adc_close();
	BITN_1(BGRC,BGR_EN);
	BITN_1(AIE,AIE_ADCE);
	L0_ADC_STOP();


	}
}

//// ����  �¶����� ����
static void L0_adc_temp_Init(void)
{

//>>>>>>>ADC1  ADC config register 1
//		7:6 ADC_VREF[1:0] 		ADC �ο���ѹѡ��Ĵ���
//			1X�� 				ѡ���ⲿ�ο���ѹ
//			01��				�ڲ� 1.5v �ο���ѹ
//			00��				�ڲ� 2.5v �ο���ѹ
	BITN_0(ADC1,BITN7); BITN_0(ADC1,BITN6);	// �ڲ� 2.5v �ο���ѹ

///����ģʽ
	BITN_1(ADC2,BITN3);//����ģʽ 	single

	
/**************
543----ADC_CHL_SEL[2:0] adc����ͨ��ѡ��
5:3 ADC_CHL_SEL[2:0] ADC ����ͨ��ѡ��
111��ѡ���ڲ��¶ȴ�����
110��ѡ���ⲿ P06 ����
101��ѡ���ⲿ P05 ����
100��ѡ���ⲿ P04 ����
011��ѡ���ⲿ P03 ����
010��ѡ���ⲿ P02 ����
001��ѡ���ⲿ P01 ����
000��ѡ���ⲿ P00 ����
**********************************/
	BITN_1(ADC1,BITN5);BITN_1(ADC1,BITN4);BITN_1(ADC1,BITN3);/// �ڲ��¶ȴ�����
	BITN_1(ADC2,BITN5);//70
	
	BITN_1(ADC3,BITN0);//1: �����ڲ��¶ȴ�����
	//BITN_0(ADC3,BITN0);//0: �����ڲ��¶ȴ�����
			  
			  //when use the temprature sensor,you need to wait
								  //about 100us to setup the stable time

}


//while(9);	
/**************************************************
�ڲ� BGR ����Ĳο���ѹ��Ϊ�Ƚϻ�׼��ѹ(1.2v)�� BGR ��������Ҫ 30uS ��ʱ�䣬
2 BGR_CLKEN BGR ʱ��ʹ�ܣ� BGR �����ڲ��ο���ѹ������ ADC�� VC�� LVD

PERI_CLK0 ��Χ����ģ��ʱ�ӿ��ƼĴ���0  ��ַ�ռ䣺 S:B3h   1�� BGR ��ʱ������0�� BGR ��ʱ������

BGRC   BGR ���ƼĴ���  ��ַ�ռ䣺 S:09Ah
7:5 OPT[2:0] BGR ����ѡ��
4 BGR_Auto BGR �͹����Զ��ر�����
1�� BGR �ڽ���͹���ģʽʱ���Զ��رգ�����ģʽʱ�Զ�������
0�� BGR ������ BGR_EN ����.
3:1 -- ����λ
0 BGR_EN BGR ʹ��λ
1�� BGR ʹ��
0�� BGR �ر�


step 1: ʹ�� BGR.EN
step 2: ADC.EN
step 3: wait 30us   
step 4: config vref sample clk mode
step 5: ��λ ADC_START
step 6: wait 17~26 adc clk ADC �Զ��õ�12bits ADC�������,����ADC�ж�
step 7

**************************************************/

#define ADC_START	BITN0

void isr_adc_Handler() interrupt Interrupt_Adc_Number //using 1
{//D_led_debug_OFF();
	if(AIF5)	 // ADC�жϴ���
	{
	//	D_led_D3_REV();// 47us 21.2k
		Clean_Adc_Interrput_Flag();//D_led_debug_ON();
		s_adc.val = D_adc_read();	

#ifdef D_open_save_buf
// 1>>>>>>>>>>>>>>>>>>>>>>>>>>adc ���뻺����
		if(L0_uart0_SendIntFree())// ���ⲿ��ʹ�ó���� uc arayy ���л���
		{
			s_adc.ucArray[s_adc.n] = s_adc.val;	
			s_adc.n ++;
		}
// 1<<<<<<<<<<<<<<<<<<<<<<<<<<<adc ���뻺����
#endif	//#define D_open_save_buf

//	L2_fsk_curve();

	}

//D_led_debug_OFF();

}

	
