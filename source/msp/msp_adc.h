//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, ���ؿƼ�
/// All rights reserved.  
///  
/// @file            app_vc.h
/// @brief           votage compare app headfile  
///  
///�����ļ�ʵ�ֵĹ��ܵ�������  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20160412
///  
///  
///     �޶�˵��������汾
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
///
///		adc app function	app_vc
///		adc hardware  driver SHC6601_adc
//////////////////////////////////////////////////////////////////////////


#ifndef _msp_adc_H 
#define _msp_adc_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

//#include "../clib/Type.h"
#include "../bsp/hard_config.h"
#include "../cpu/SHC6601_system.h"
#include "uart0.h"
#include "../debug/debug_drv.h"//

//#include "SHC6601_adc.h"
//#include "../app/app_fsk.h"

//#define D_open_save_buf
#define D_ucAdc_buff_max	256
struct	_s_adc_
{		
	//vU8 flag;
	U8 val;
	U8 n; 	
	U8 m; 	

	#ifdef 	D_open_save_buf
	vU16 usN; 
	U8 ucArray[D_ucAdc_buff_max + 1]; 
	#endif
};
extern struct  _s_adc_ s_adc;

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/
//#define D_P21_cofig_BUZZ()	BITN_1(P2_SEL2,(BIT1));BITN_0(P2_SEL1,(BIT1));BITN_0(P2_SEL0,(BIT1))
//#define D_P21_cofig_IO()		BITN_0(P2_SEL2,(BIT1));BITN_0(P2_SEL1,(BIT1));BITN_0(P2_SEL0,(BIT1));P21 = 1
#define D_adc_open()	BITN_1(ADC1,BITN0)
#define D_adc_close()	BITN_0(ADC1,BITN0)	///����/ �ر� ADCʹ���ź�

#define L0_ADC_START() BITN_1(ADC2,BITN0)
#define L0_ADC_STOP() 	BITN_0(ADC2,BITN0)	//ADC ��ʼ����,ֹͣ����

#define D_adc_read()	(ADCH)		// aliga = left

//#define SetP0DigitalPort() (P0_Sel0 = 0x00)
#define Clean_Adc_Interrput_Flag() (AIF5 = 0)

extern void L0_adc_EIO_Init(void);
extern void L0_adc_ch(unsigned char ch);
extern void L0_adc_EIO_close(unsigned char sw);
#endif //	_vc_H


