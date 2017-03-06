////////////////////////////////////////////////////////////////////////////  
///@copyright  Copyright (c) 2017, ���ؿƼ� All rights reserved.  
///-------------------------------------------------------------------------  
/// @file            hard_config.h
/// @brief           hard config include
///FILE FOR HARDWARE SETUP AND SOFTWARE SETUP
///FOR EXAMPLE: BAORD ,MCU,IDE
///YOU CAN CHANGE OR ADD THE DEFINE IF YOU NEED
/// ����Ƕ��ʽ��Ŀ�����  ������ȷ�ϵ�·��  Ȼ��ȷ��cpu оƬ�ͺ�  Ȼ��ȷ�ϱ�����  ֮����������  �����Ӧ�ó���  
///  HARD_CONFIG  Ϊ����ͷ�ļ���ʼ�� TYPE_BOARD_xx
///-------------------------------------------------------------------------  
/// @version		1.0  
/// @author		CC 
/// @date			20170122
/// @note			cc_swhh_MD02
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
#ifndef   _HARD_CONFIG_H
#define   _HARD_CONFIG_H
#include <INTRINS.H>

#if 0
#define D_debug_sim
#endif
//#define D_iic_inspect
#define D_open_save_f
//>>>>>>>>>>>>>>>>>>>>>>.BORAD TYPE
#define TYPE_BOARD_hhnew			16
#define	TYPE_BOARD_st_sleep04_01		4
#define	TYPE_BOARD_st_sleep03		5
#define TYPE_BOARD_SMMM_MB_VH032_0E	6
#define TYPE_BOARD_LPC17xx_	8
#define TYPE_BOARD_STM32F_103ZET6_READBULL	1036
#define TYPE_BOARD_hh_CC_MD_VH05_anyriny_simple_m51		0x0551


#define D_CPUfamily_8bits	8
#define D_CPUfamily_16bits	16
#define D_CPUfamily_32bits	32
#define TYPE_BOARD_stc5as32_WIFIBV01	532
#define TYPE_BOARD_SHC16LAXXQN32		1632		//SHC16LAXXQN32
// BORAD,
// MCU:SHC6601
// IDE :KEIL

#define TYPE_MCU_SHC6601	66
#define TYPE_MCU_STC	51
#define TYPE_MCU_LPC17xx	3217
#define TYPE_MCU_STM32		3232

//<<<<<<<<<<<<<<<<<<<<<<<<<<<.BORAD TYPE

//>>>>>>>>>>>>>>>>>>>>>>IDE TYPE

#define TYPE_IDE_KEIL	1
#define TYPE_IDE_MDK	2
#define TYPE_IDE_IAR	3

//<<<<<<<<<<<<<<<<<<<<<<IDE TYPE

//#define TYPE_BOARD	TYPE_BOARD_SMMM_MB_VH032_0E
//#define TYPE_BOARD	TYPE_BOARD_stc90c516rd
#define TYPE_BOARD	TYPE_BOARD_hh_CC_MD_VH05_anyriny_simple_m51
//#define TYPE_BOARD	TYPE_BOARD_stc5as32_WIFIBV01
//#define TYPE_BOARD	TYPE_BOARD_hhnew

//USER DEFINE 
#define TYPE_ASENSOR_ADXL362	362
#define TYPE_ASENSOR_MSA300	362
#define TYPE_ASENSOR	TYPE_ASENSOR_MSA300

#if(TYPE_BOARD == TYPE_BOARD_SMMM_MB_VH032_0E)


#elif(TYPE_BOARD == TYPE_BOARD_hh_CC_MD_VH05_anyriny_simple_m51)
///////>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	#define TYPE_MCU	TYPE_MCU_SHC6601
	#define TYPE_IDE	TYPE_IDE_KEIL
 //   typedef unsigned char	type_comm;//ͨ�����͵ı���,ȡ���ڱ�������cpu��λ����ϵͳ�Ķ�ջ�Ż���
	#include <stdio.h>
	#include <string.h>
	#include <intrins.h>
	#define NOP()	_nop_()

	#define D_l0_delay_ms	600	   //
	#define D_CPUfamily_type	D_CPUfamily_8bits
#ifdef D_debug_sim
#define D_sim_uart
#define D_sim_timer0

#endif
	#include "../clib/Type.h"
	#include "../clib/bit.h"
	#include "../cpu/SHC16L.h"
	#include "../cpu/shc16l_macro.h"	
	#include "../msp/msp_wdt.h"	
/// ���õ�reg ��Ϊ����ʹ��

//SADEN1 ���ڴ� ����ַ 

#define gReg_user2 	SADEN1
#define gRegU_SO 	SADDR
#define gRegU_AppFlag 			CCAP0L	// io��״̬λ
#define gRegU_iic_wr 		CCAP1L		// iic ��д״̬λ
#define gRegU_iic_return 	CCAP2L		///// i2cģ���������״̬,�ж�i2cģ���Ƿ���еı�־
#define gRegU_CWreg 			CCAP3L
#define gRegU_SO3 			CCAP3L

#define D_AppFlag_CWInt		BITN0		/// CW ���ж�app��־ �������жϱ�־,һ�����ڱ����жϱ�־
											/// ��Ϊ�жϱ�־�󲿷ֻ����ж����Զ����߳������,Ӧ�ó����п�������
#define D_AppFlag_HotReset		BITN1		/// �������ı�־λ


#define L2_AppFlag_init()				gRegU_AppFlag = 0;


///L2_AppFlag_CWInt_is(D_AppFlag_CWInt)
#define L2_AppFlag_CWInt_is(BITNx)		BITN_G(gRegU_AppFlag, (BITNx))
#define L2_AppFlag_CWInt_set(BITNx)		BITN_1(gRegU_AppFlag,(BITNx))
#define L2_AppFlag_CWInt_clear(BITNx)		BITN_0(gRegU_AppFlag,(BITNx))


#define L2_AppFlag_HotReset_is(BITNx)		BITN_G(gRegU_AppFlag, (BITNx))
#define L2_AppFlag_HotReset_set(BITNx)		BITN_1(gRegU_AppFlag,(BITNx))
#define L2_AppFlag_HotReset_clear(BITNx)		BITN_0(gRegU_AppFlag,(BITNx))





//#define reg_user4 	SADEN1
//#define reg_user5 	SADEN1
/******************
SHC16LAXXQN32 
P51 txd
P50 rxd

P07	BAT_CAL  
P06 BAT_CAL_EN
P05 VCIN0
P04 PW_IRQ

P31 SENSINT2
P30 SENSINT3

P27 LED1
P26 LED12
P25 LED82 
P24 LED8
P23 LED5 
P22 LED51
P21	 BUZ
P21 PW_PG

P10 SCL
p11 SDA
typedef enum MainFreSelect
{
	MainFre_2M,
	MainFre_4M,
	MainFre_8M,
	MainFre_16M,
	MainFre_Max
}MainFreSelect;


*************************/

#define D_MainFre	1	//MainFre_4M

//////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if(D_CPUfamily_type == D_CPUfamily_32bits)
	typedef vU32 UN_TYPE;                               
#elif(D_CPUfamily_type == D_CPUfamily_16bits)
	typedef U16 UN_TYPE;

#else        
	typedef U8 UN_TYPE;
    typedef unsigned char type_comm;
#endif

#elif(TYPE_BOARD == TYPE_BOARD_hhnew)

#include "../cpu/SHC16L_macro.h"

	#define TYPE_MCU	TYPE_MCU_SHC6601
	#define TYPE_IDE	TYPE_IDE_KEIL
    typedef unsigned char	type_comm;//ͨ�����͵ı���,ȡ���ڱ�������cpu��λ����ϵͳ�Ķ�ջ�Ż���

#elif(TYPE_BOARD == TYPE_BOARD_stc5as32_WIFIBV01)
	#define TYPE_MCU	TYPE_MCU_STC
	#define TYPE_IDE	TYPE_IDE_KEIL
    typedef unsigned char	type_comm;//ͨ�����͵ı���,ȡ���ڱ�������cpu��λ����ϵͳ�Ķ�ջ�Ż���
	#include <stdio.h>
	#include <string.h>
	#include <intrins.h>

	#include "../cpu/stc_cc_8051.h"

	#define D_l0_delay_ms	600	   //
	#define D_CPUfamily_type	D_CPUfamily_8bits

#elif(TYPE_BOARD == TYPE_BOARD_LPC17xx_)
	#define TYPE_MCU	TYPE_MCU_LPC17xx
	#define TYPE_IDE	TYPE_IDE_MDK
//	typedef unsigned int	type_comm;//ͨ�����͵ı���,ȡ���ڱ�������cpu��λ����ϵͳ�Ķ�ջ�Ż���

#include "lpc17xxcc.h"		  
#include "lpc17xxzlg.h"			 
#include "lpc17xx_macro.h"
#include "target_cfg.h"

#elif(TYPE_BOARD == TYPE_BOARD_STM32F_103ZET6_READBULL)
	#define TYPE_MCU	TYPE_MCU_STM32
	#define TYPE_IDE	TYPE_IDE_MDK
//	typedef unsigned int	type_comm;//ͨ�����͵ı���,ȡ���ڱ�������cpu��λ����ϵͳ�Ķ�ջ�Ż���
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32_macro.h"
#endif

#endif//_HARD_CONFIG_H
/*********************************end file*********************************************/


