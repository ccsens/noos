//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            app_voicecom.c
/// @brief           app_voicecom app   音频通讯程序
///  
///（本文件实现的功能的详述）  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20150102
///  
///  
///     修订说明：最初版本
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
//
// layer 4 : app_voicecom
// layer 3 : app_fsk
// layer 2 : app_vc.h
// layer 1 : shc6601_adc

//
///		adc app function	vc
///		adc hardware  driver SHC6601_adc
//
//////////////////////////////////////////////////////////////////////////



/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "app_voicecom.h"	

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

void L3_voicecom_init(void)
{
	L0_adc_EIO_Init();		
	L0_adc_ch(5);//
	L0_ADC_START();
}
///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>task>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
struct _s_task_voicecom_ s_task_voicecom;
// 添加音频通讯使用的初始化  在初始化中计算没有声音的平均值 这样核定没有波形的状态,然后设计多层
//的音频通讯架构
// L3_voicecom_handdle(&s_task_voicecom);


///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>task>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void L3_task_voicecom_init(void)
{
	L1_task_init(&s_task_voicecom.task);
	L3_task_s_go(s_task_voicecom,D_task_init);	//		s_task_voicecom.task.sh = D_task_init;

}

struct _s_task_voicecom_ s_task_voicecom;

#define D_task_voicecom_read		0x30

void L3_task_voicecom_handdle(struct _s_task_voicecom_ *s)
{  
	switch(s->task.sh)
	{
		case D_task_init://
		
		///fixme 需要打开麦克风电源 
		///需要添加ADC 模块打开和关闭的管理,需要添加adc采样的开始和停止管理
		/// 需要添加adc采样缓存的的启动和溢出(溢出后才可以开始判定数据�?)管理,
			L0_ADC_START();
			L2_task_go(D_task_voicecom_read);
		break;	
		case D_task_voicecom_read ://
			if (1 == s_array_hd.haveDat)
			{L0_uart0_uc(0x0a); 
				if(s_array_bit.ucByte_num>3)
				{
					s->ocr = 0;
					for (s->t = 0; s->t < (s_array_bit.ucByte_num -1); s->t++)
					{
					//	c = s_array_bit.ucByte_pool[p->t];
						s->ocr += s_array_bit.ucByte_pool[s->t];
					}
					if(s->ocr == s_array_bit.ucByte_pool[s_array_bit.ucByte_num -1])
					{s->ocr = s_array_bit.ucByte_pool[s_array_bit.ucByte_num -1]+1;
						L0_uart0_uc(0x20);	
					}else
					{
						L0_uart0_uc(s->ocr);	
					}
					//L0_uart0_sendbuf(&s_array_bit.ucByte_pool[0],s_array_bit.ucByte_num);
				}
				s_array_hd.haveDat = 0;
			}
		break;			
		L2_task_switch_default_idelay();
	}
}

///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<task<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<















