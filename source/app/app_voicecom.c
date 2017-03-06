//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, ´«¿Ø¿Æ¼¼
/// All rights reserved.  
///  
/// @file            app_voicecom.c
/// @brief           app_voicecom app   ÒôÆµÍ¨Ñ¶³ÌÐò
///  
///£¨±¾ÎÄ¼þÊµÏÖµÄ¹¦ÄÜµÄÏêÊö£©  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20150102
///  
///  
///     ÐÞ¶©ËµÃ÷£º×î³õ°æ±¾
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
// Ìí¼ÓÒôÆµÍ¨Ñ¶Ê¹ÓÃµÄ³õÊ¼»¯  ÔÚ³õÊ¼»¯ÖÐ¼ÆËãÃ»ÓÐÉùÒôµÄÆ½¾ùÖµ ÕâÑùºË¶¨Ã»ÓÐ²¨ÐÎµÄ×´Ì¬,È»ºóÉè¼Æ¶à²ã
//µÄÒôÆµÍ¨Ñ¶¼Ü¹¹
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
		
		///fixme ÐèÒª´ò¿ªÂó¿Ë·çµçÔ´ 
		///ÐèÒªÌí¼ÓADC Ä£¿é´ò¿ªºÍ¹Ø±ÕµÄ¹ÜÀí,ÐèÒªÌí¼Óadc²ÉÑùµÄ¿ªÊ¼ºÍÍ£Ö¹¹ÜÀí
		/// ÐèÒªÌí¼Óadc²ÉÑù»º´æµÄµÄÆô¶¯ºÍÒç³ö(Òç³öºó²Å¿ÉÒÔ¿ªÊ¼ÅÐ¶¨Êý¾Ýå?)¹ÜÀí,
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















