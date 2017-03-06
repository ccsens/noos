//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            app_fsk.h
/// @brief           fsk app headfile  
///  
///（本文件实现的功能的详述）  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20160512
///  
///  
///     修订说明：最初版本
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	
///
///		adc app function	app_vc
///		adc hardware  driver SHC6601_adc
//////////////////////////////////////////////////////////////////////////


#ifndef _app_fsk_H 
#define _app_fsk_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "../msp/msp_adc.h"



#define D_array_hd_max	  1024		//1bit  10个cycle 取决载波频率和基带 11Byte = 11*8*10 = 880 协议为3+8Byte
struct	_s_array_hd_
{
	vU16 usN;
	//vU8 usN; 	//for test
	U8 up;
	U8 haveDat;

	U8 hn_zaibo;
	U8 hn;
	U8 zn;
	U8 savef;
	U8 f;
	U8 f_diff;
	U8 f_pool;
	U8 ucCache[3];
	//	vU8 ucCache_f[2]; 
	#ifdef D_open_save_f
	U8 ucArray_f[D_array_hd_max];
	U16 ui_n;
	#endif
	//vU8 ucBuf_f[D_array_hd_max]; 
};
extern struct  _s_array_hd_ s_array_hd;


#define D_array_byte_max	16
#define D_array_bit_max	128			// 16*8

struct	_s_array_bit_
{
	//vU8 flag;
	vU16 usTime;

	U8 ucByte_shift;
	U8 ucByte_n;
	U8 ucByte_num;
	U8 ucByte[D_array_bit_max];
	U8 ucByte_pool[D_array_bit_max];
	
	vU16 usN;
	//vU8 ucBit[D_array_bit_max];
};
extern struct  _s_array_bit_ s_array_bit;



//U8 L0_vc_Init(void);
extern U8 L1_fsk_Init(void);
extern void L2_fsk_curve(void);


#endif //	_fsk_H


