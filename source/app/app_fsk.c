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
	
#define D_fsk_diff	3		//求得前后的差
#define D_fsk_H_max	12		//曲线稳定的上限
#define D_fsk_L_min	8		//曲线稳定的下限
	
#define D_fsk_f_diff_wending	5		//稳定在高电平时间足够



// 5a a5 03 e0 00 33
//  FE            a5  08  d0    d1    d2    d3    d4    d5    d6    d7 
//  11111 1110
//  由1111111计数来判定开始有数据,从0 开始计数 ,n*16(取决于wave生产文件的数据点数) 为高还是低来判断           
	//  3000---7 2050---10  n= 16 
//fe a5 08 d1 d2 d3 fe a5 08 d1 d2 d3 


//	//  0     1010      1010      1
	//起始位 bit0       bit7    停止位  TTL电平
	//'1' = low  uart  1= LOW  0 = High   高位在前

// 1111 1110 10101010  0010 0010 
//  fe          aa      22   -->因为低位在前 所以应该是  7f 55 44

	
// 20160506 应该在大于 0x95 --150  (130----150-----168)  先判定有数据
//  可在何时启动adc上下功夫节约电  按键启动 后 收到有效数据的中断后启动 


void L2_fsk_curve(void)
{	
	// 2>>>>>>>>>>>>>>>>>>>>>>>>> 判断拐点		
	//	____/[0]----[1]----[2]/^^^^^
			s_array_hd.ucCache[0] = s_array_hd.ucCache[1];
			s_array_hd.ucCache[1] = s_array_hd.ucCache[2];	
			s_array_hd.ucCache[2] = s_adc.val;
			if(s_array_hd.ucCache[2] > s_array_hd.ucCache[1])
			{
				if(s_array_hd.ucCache[1] >= s_array_hd.ucCache[0])
				{	//		开始上升
					if(0 == s_array_hd.up)
					{
						s_array_hd.up = 1;		//D_led_D1_REV();
						/// 2.1>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
						/// step 1: 求得前后的差
						LD_diff(s_array_hd.f_pool, s_array_hd.f, s_array_hd.f_diff);
	
						/// step 2: 由此差来判定幅度变化的大小
						if (s_array_hd.f_diff < D_fsk_diff)
						{
							if (0 == s_array_hd.savef)
							{// 没有进入有效数据状态
								if (LD_scope(s_array_hd.f_pool, D_fsk_H_max, D_fsk_L_min))
								{//  ///  由此差来判定数据是否是高电平的  10+/-
									s_array_hd.hn++;	
									if (s_array_hd.hn > D_fsk_f_diff_wending)/// step 3: 稳定在高电平时间足够
									{//  收到连续有效的数据
											s_array_hd.savef = 1;// 存在有效数据的标识位
											
											s_array_hd.usN = 0;
									}
									s_array_hd.hn_zaibo = 0;
								}
								else
								{/// 没有高电平或者其他偶然的水平线
									s_array_hd.hn_zaibo ++;
									if(s_array_hd.hn_zaibo > 2)
									{// 异常
										s_array_hd.hn = 0;
									}
								}			
							}
							s_array_hd.zn = 0;
						}
						else
						{//  收到无序数据
							s_array_hd.zn++;
							if (s_array_hd.zn > 5)
							{//  收到连续无序数据,可能是杂波闹成 或者是 数据突然中断 或者数据接收结束
									//D_led_D2_REV();
								if (1 == s_array_hd.savef)// 如果是已经进入有效数据通道
								{
									if(0 == s_array_hd.haveDat)
									{ //  如果数据缓存pool中是空的 则保存数据到缓存中,记录数据的长度
										//if(L0_uart0_SendIntFree())
										{
											s_array_bit.ucByte_num = s_array_bit.ucByte_shift / 8;
											if(s_array_bit.ucByte_num > 3)// 协议应该超过3个
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
							{//其他比较小的跳跃忽略 也就是偶尔出现一个差值特别大的 当做异常滤掉
							
									
							}///if (s_array_hd.zn > 2)
						}
						
						/// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>解析数据>>>>>>
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
								s_array_bit.ucByte_shift ++;		// 255/8 =32 一次最长的数组为32Byte
								if(s_array_bit.ucByte_shift  > D_array_bit_max)
								{
									s_array_bit.ucByte_shift = 0;
								}
							}
							s_array_bit.usTime ++;
						}
	
		/// 2.1<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		/// 2.2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>保存数据>>>>>>
	//#define D_open_save_f
#ifdef D_open_save_f
						//if(1 == s_array_hd.savef)
						{//D_led_D2_ON();
							if(L0_uart0_SendIntFree())// 和外部的使用程序对 uc arayy 进行互锁
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
						
		/// 2.2<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<保存数据<<<<<
					}
				}
			}
			else
			{
				s_array_hd.up = 0;
			}	
			s_array_hd.f ++;
	// 2<<<<<<<<<<<<<<<<<<<<<<<<<<<  判断拐点		


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


