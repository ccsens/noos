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
///		adc app function	vc
///		adc hardware  driver SHC6601_adc
//
//////////////////////////////////////////////////////////////////////////



/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "app_fsk.h"	

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


struct  _s_array_hd_ s_array_hd = {
	0,
};
struct  _s_array_bit_ s_array_bit= {
	0,
};


U8 L1_fsk_Init(void)
{
    U8 status   = 0x44;
	s_array_hd.haveDat = 0;
	s_array_hd.savef = 0;
	//D_led_debug_OFF();
	s_array_hd.zn = 0;
	s_array_hd.hn = 0;
	s_array_bit.usTime = 0;
	s_array_bit.ucByte_shift = 0;
	s_array_bit.ucByte_n = 0;
	s_array_bit.usN = 0;


	
    return status;
}


#define LD_diff(a,b,d); 	if ((a) > (b)){(d) = (a) - (b);}else{(d) = (b) - (a);} (a) = (b);
#define LD_scope(a,max,min) 	(((a)<(max))&&((a)>(min)))
	
#define D_fsk_diff	3		//���ǰ��Ĳ�
#define D_fsk_H_max	12		//�����ȶ�������
#define D_fsk_L_min	8		//�����ȶ�������
	
#define D_fsk_f_diff_wending	5		//�ȶ��ڸߵ�ƽʱ���㹻



// 5a a5 03 e0 00 33
//  FE            a5  08  d0    d1    d2    d3    d4    d5    d6    d7 
//  11111 1110
//  ��1111111�������ж���ʼ������,��0 ��ʼ���� ,n*16(ȡ����wave�����ļ������ݵ���) Ϊ�߻��ǵ����ж�           
	//  3000---7 2050---10  n= 16 
//fe a5 08 d1 d2 d3 fe a5 08 d1 d2 d3 


//	//  0     1010      1010      1
	//��ʼλ bit0       bit7    ֹͣλ  TTL��ƽ
	//'1' = low  uart  1= LOW  0 = High   ��λ��ǰ

// 1111 1110 10101010  0010 0010 
//  fe          aa      22   -->��Ϊ��λ��ǰ ����Ӧ����  7f 55 44

	
// 20160506 Ӧ���ڴ��� 0x95 --150  (130----150-----168)  ���ж�������
//  ���ں�ʱ����adc���¹����Լ��  �������� �� �յ���Ч���ݵ��жϺ����� 


void L2_fsk_curve(void)
{	
	// 2>>>>>>>>>>>>>>>>>>>>>>>>> �жϹյ�		
	//	____/[0]----[1]----[2]/^^^^^
			s_array_hd.ucCache[0] = s_array_hd.ucCache[1];
			s_array_hd.ucCache[1] = s_array_hd.ucCache[2];	
			s_array_hd.ucCache[2] = s_adc.val;
			if(s_array_hd.ucCache[2] > s_array_hd.ucCache[1])
			{
				if(s_array_hd.ucCache[1] >= s_array_hd.ucCache[0])
				{	//		��ʼ����
					if(0 == s_array_hd.up)
					{
						s_array_hd.up = 1;		//D_led_D1_REV();
						/// 2.1>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
						/// step 1: ���ǰ��Ĳ�
						LD_diff(s_array_hd.f_pool, s_array_hd.f, s_array_hd.f_diff);
	
						/// step 2: �ɴ˲����ж����ȱ仯�Ĵ�С
						if (s_array_hd.f_diff < D_fsk_diff)
						{
							if (0 == s_array_hd.savef)
							{// û�н�����Ч����״̬
								if (LD_scope(s_array_hd.f_pool, D_fsk_H_max, D_fsk_L_min))
								{//  ///  �ɴ˲����ж������Ƿ��Ǹߵ�ƽ��  10+/-
									s_array_hd.hn++;	
									if (s_array_hd.hn > D_fsk_f_diff_wending)/// step 3: �ȶ��ڸߵ�ƽʱ���㹻
									{//  �յ�������Ч������
											s_array_hd.savef = 1;// ������Ч���ݵı�ʶλ
											
											s_array_hd.usN = 0;
									}
									s_array_hd.hn_zaibo = 0;
								}
								else
								{/// û�иߵ�ƽ��������żȻ��ˮƽ��
									s_array_hd.hn_zaibo ++;
									if(s_array_hd.hn_zaibo > 2)
									{// �쳣
										s_array_hd.hn = 0;
									}
								}			
							}
							s_array_hd.zn = 0;
						}
						else
						{//  �յ���������
							s_array_hd.zn++;
							if (s_array_hd.zn > 5)
							{//  �յ�������������,�������Ӳ��ֳ� ������ ����ͻȻ�ж� �������ݽ��ս���
									//D_led_D2_REV();
								if (1 == s_array_hd.savef)// ������Ѿ�������Ч����ͨ��
								{
									if(0 == s_array_hd.haveDat)
									{ //  ������ݻ���pool���ǿյ� �򱣴����ݵ�������,��¼���ݵĳ���
										//if(L0_uart0_SendIntFree())
										{
											s_array_bit.ucByte_num = s_array_bit.ucByte_shift / 8;
											if(s_array_bit.ucByte_num > 3)// Э��Ӧ�ó���3��
											{												
												for (s_array_hd.zn = 0; s_array_hd.zn < s_array_bit.ucByte_num;s_array_hd.zn++ )
												{
													s_array_bit.ucByte_pool[s_array_hd.zn] = s_array_bit.ucByte[s_array_hd.zn];
													//s_array_bit.ucByte_pool[s_array_hd.zn] = s_array_hd.zn;
													s_array_bit.ucByte[s_array_hd.zn] = 0;
												}
												s_array_hd.haveDat = 1;
											}
										}
									}
									s_array_hd.savef = 0;
									//D_led_debug_OFF();
									s_array_hd.zn = 0;
									s_array_hd.hn = 0;
									s_array_bit.usTime = 0;
									s_array_bit.ucByte_shift = 0;
									s_array_bit.ucByte_n = 0;
									s_array_bit.usN = 0;
								}
							}
							else	//if (s_array_hd.zn > 2)
							{//�����Ƚ�С����Ծ���� Ҳ����ż������һ����ֵ�ر��� �����쳣�˵�
							
									
							}///if (s_array_hd.zn > 2)
						}
						
						/// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>��������>>>>>>
						/// step 3:
						if (1 == s_array_hd.savef)
						{
							if (0 == s_array_bit.usTime % 16)
							{
								if(s_array_hd.f_pool >= 8 )
								{
									//s_array_bit.ucBit[s_array_bit.usN] = 0x31;
									s_array_bit.ucByte[s_array_bit.ucByte_shift/8] |= (1<<(s_array_bit.ucByte_shift%8));
								}
								else
								{
									//s_array_bit.ucBit[s_array_bit.usN] = 0x30;
									//s_array_bit.ucByte[s_array_bit.ucByte_shift/8] &= ~(1<<(s_array_bit.ucByte_shift%8));
								}
								s_array_bit.usN++;
								s_array_bit.ucByte_shift ++;		// 255/8 =32 һ���������Ϊ32Byte
								if(s_array_bit.ucByte_shift  > D_array_bit_max)
								{
									s_array_bit.ucByte_shift = 0;
								}
							}
							s_array_bit.usTime ++;
						}
	
		/// 2.1<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		/// 2.2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>��������>>>>>>
	//#define D_open_save_f
#ifdef D_open_save_f
						//if(1 == s_array_hd.savef)
						{//D_led_D2_ON();
							if(L0_uart0_SendIntFree())// ���ⲿ��ʹ�ó���� uc arayy ���л���
							{	//D_led_D2_OFF();
								
								s_array_hd.ucArray_f[s_array_hd.usN] = s_array_hd.f_pool; 
								s_array_hd.usN ++;	
								if(s_array_hd.usN >= D_array_hd_max) 
									{s_array_hd.usN = 0;}
								//D_led_D2_ON();
							}//D_led_D2_OFF();
						}
	
#endif	//#define D_open_save_f
						s_array_hd.f = 0;
						
		/// 2.2<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��������<<<<<
					}
				}
			}
			else
			{
				s_array_hd.up = 0;
			}	
			s_array_hd.f ++;
	// 2<<<<<<<<<<<<<<<<<<<<<<<<<<<  �жϹյ�		


}

void L2_fsk_curve2(void)
{	
	if(s_array_hd.ui_n > 1000)
	{
		s_array_hd.savef = 1;
	}else
	{
		s_array_hd.ucArray_f[s_array_hd.ui_n] = s_adc.val;
		s_array_hd.ui_n ++;
	}
}



void L2_fsk_show(void)
{	
	if(1 == s_array_hd.savef)
	{

		
		s_array_hd.savef = 0;
	}else
	{
		s_array_hd.ucArray_f[s_array_hd.ui_n] = s_adc.val;
		s_array_hd.ui_n ++;
	}
}


