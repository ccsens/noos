//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            vc.c
/// @brief           vc driver app  
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
//// 配置 ADC通道
void L0_adc_ch(unsigned char ch)
{
	BITN_1(P0_SEL0,1<<ch);		//设置成	ADC通道ch的输入
	BITN_0(ADC1,BITN5|BITN4|BITN3);	//
	BITN_1(ADC1,ch<<3);

/**************
543----ADC_CHL_SEL[2:0] adc采样通道选择
5:3 ADC_CHL_SEL[2:0] ADC 采样通道选择
111：选择内部温度传感器
110：选择外部 P06 输入
101：选择外部 P05 输入
100：选择外部 P04 输入
011：选择外部 P03 输入
010：选择外部 P02 输入
001：选择外部 P01 输入
000：选择外部 P00 输入
**********************************/
}

void L0_adc_EIO_Init(void)
{
				
/// 外设通用步骤
/// 模块使能
/// step 1.1: 系统分配时钟源
/// step 1.2: 系统分配时钟使能
/// step 1.3: 系统模块使能

/// 模块设置
/// step 2.1: 模块自身设置:  
/// step 2.2: 特殊模块使能(例如ADC 的邋邋 BGR)

/// 中断设置
/// step 3.1: 模块中断优先级
/// step 3.2: 模块中断启动
/// step 3.3: 全局中断(和其他模块共享,调试中需要关注)
///
/// 启动模块
/// step 4.1: 启动模块 开始工作



/// 模块使能
//---------------------------------------------------------------------------
/// step 1.1: 系统分配时钟源
	BITN_1(PERI_CLK0,ADC_CLKEN);
//---------------------------------------------------------------------------
/// step 1.2: 系统分配时钟使能
//---------------------------------------------------------------------------
/// step 1.3: 系统模块使能
	D_adc_open();
//---------------------------------------------------------------------------
/// 模块设置
/// step 2.1: 模块自身设置:

	//BITN_1(ADC1,BITN7);						///	 1X： 选择外部参考电压
	BITN_0(ADC1,BITN7);BITN_1(ADC1,BITN7);	///	 01：内部 1.5v 参考电压
	//BITN_0(ADC1,BITN7);BITN_0(ADC1,BITN7);	/// 00：内部 2.5v 参考电压

/// 默认通道选择
/// 采样时钟
	//BITN_0(ADC1,BITN2);BITN_0(ADC1,BITN1);	///系统
	//BITN_0(ADC1,BITN2);BITN_1(ADC1,BITN1);	///sys/2
	//BITN_1(ADC1,BITN2);BITN_0(ADC1,BITN1);	///sys/4
	BITN_1(ADC1,BITN2);BITN_1(ADC1,BITN1);	///sys/8
/// 采样时间
	BITN_0(ADC2,BITN7);BITN_0(ADC2,BITN6);	///3
	//BITN_0(ADC2,BITN7);BITN_1(ADC2,BITN6);	///6
	//BITN_1(ADC2,BITN7);BITN_0(ADC2,BITN6);	///1
	//BITN_1(ADC2,BITN7);BITN_1(ADC2,BITN6);	///9

///采样模式
	//BITN_1(ADC2,BITN3);//采样模式 	single
	BITN_0(ADC2,BITN3);//采样模式	continue

///对齐模式
	//BITN_0(ADC2,BITN2);	///1：右对齐。结果为 xxxxMSB~LSB
	BITN_1(ADC2,BITN2);	///0：左对齐。结果为 MSB~LSBxxxx  读取 adcH 即可
//ADC 工作电流配置	
	BITN_1(ADC3,BITN2);BITN_1(ADC3,BITN1);	///11: 最低 ADC 工作电流(推荐)
//---------------------------------------------------------------------------
/// step 2.2: 特殊模块使能(例如ADC 的邋邋 BGR)

	BITN_1(BGRC,BGR_EN);

//---------------------------------------------------------------------------
/// 中断设置
/// step 3.1: 模块中断优先级
//---------------------------------------------------------------------------
/// step 3.2: 模块中断启动
	BITN_1(AIE,AIE_ADCE);
//---------------------------------------------------------------------------
/// step 3.3: 全局中断(和其他模块共享,调试中需要关注)
///

//---------------------------------------------------------------------------
	L0_ADC_START();	/// 开始采样
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

//// 配置  温度输入 输入
static void L0_adc_temp_Init(void)
{

//>>>>>>>ADC1  ADC config register 1
//		7:6 ADC_VREF[1:0] 		ADC 参考电压选择寄存器
//			1X： 				选择外部参考电压
//			01：				内部 1.5v 参考电压
//			00：				内部 2.5v 参考电压
	BITN_0(ADC1,BITN7); BITN_0(ADC1,BITN6);	// 内部 2.5v 参考电压

///采样模式
	BITN_1(ADC2,BITN3);//采样模式 	single

	
/**************
543----ADC_CHL_SEL[2:0] adc采样通道选择
5:3 ADC_CHL_SEL[2:0] ADC 采样通道选择
111：选择内部温度传感器
110：选择外部 P06 输入
101：选择外部 P05 输入
100：选择外部 P04 输入
011：选择外部 P03 输入
010：选择外部 P02 输入
001：选择外部 P01 输入
000：选择外部 P00 输入
**********************************/
	BITN_1(ADC1,BITN5);BITN_1(ADC1,BITN4);BITN_1(ADC1,BITN3);/// 内部温度传感器
	BITN_1(ADC2,BITN5);//70
	
	BITN_1(ADC3,BITN0);//1: 启动内部温度传感器
	//BITN_0(ADC3,BITN0);//0: 禁用内部温度传感器
			  
			  //when use the temprature sensor,you need to wait
								  //about 100us to setup the stable time

}


//while(9);	
/**************************************************
内部 BGR 输出的参考电压做为比较基准电压(1.2v)。 BGR 的启动需要 30uS 的时间，
2 BGR_CLKEN BGR 时钟使能， BGR 产生内部参考电压，供给 ADC， VC， LVD

PERI_CLK0 周围功能模块时钟控制寄存器0  地址空间： S:B3h   1： BGR 有时钟输入0： BGR 无时钟输入

BGRC   BGR 控制寄存器  地址空间： S:09Ah
7:5 OPT[2:0] BGR 工作选项
4 BGR_Auto BGR 低功耗自动关闭设置
1： BGR 在进入低功耗模式时，自动关闭；工作模式时自动开启。
0： BGR 开关由 BGR_EN 控制.
3:1 -- 保留位
0 BGR_EN BGR 使能位
1： BGR 使能
0： BGR 关闭


step 1: 使能 BGR.EN
step 2: ADC.EN
step 3: wait 30us   
step 4: config vref sample clk mode
step 5: 置位 ADC_START
step 6: wait 17~26 adc clk ADC 自动得到12bits ADC采样结果,产生ADC中断
step 7

**************************************************/

#define ADC_START	BITN0

void isr_adc_Handler() interrupt Interrupt_Adc_Number //using 1
{//D_led_debug_OFF();
	if(AIF5)	 // ADC中断触发
	{
	//	D_led_D3_REV();// 47us 21.2k
		Clean_Adc_Interrput_Flag();//D_led_debug_ON();
		s_adc.val = D_adc_read();	

#ifdef D_open_save_buf
// 1>>>>>>>>>>>>>>>>>>>>>>>>>>adc 存入缓存中
		if(L0_uart0_SendIntFree())// 和外部的使用程序对 uc arayy 进行互锁
		{
			s_adc.ucArray[s_adc.n] = s_adc.val;	
			s_adc.n ++;
		}
// 1<<<<<<<<<<<<<<<<<<<<<<<<<<<adc 存入缓存中
#endif	//#define D_open_save_buf

//	L2_fsk_curve();

	}

//D_led_debug_OFF();

}

	
