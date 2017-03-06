/****************************************************************
Copyright (C) 2014, SHHIC .Co. ,Ltd. All rights reserved.

File name    :	SHC6601_system.h
Version      :	0.1
Author       :	Yanxian
Data		 :	2014-06-11
Description  :  miscellaneous definitions,include interrupt,LPM,
				clk,LVD and so on

				modify by cc  struct  _s_sys_para_ s_sys_para;
****************************************************************/

#ifndef _SHC6601_SYSTEM_H_
#define _SHC6601_SYSTEM_H_	

#ifdef __cplusplus
 extern "C" {
#endif

//#include "SHC6601.h"
//#include "SHC6601_type.h"
#include "../bsp/hard_config.h"
//#include "../debug/debug_drv.h"	
struct	_s_sys_para_
{	
	
	vU32 sys_clock; 
	
};
extern struct  _s_sys_para_ s_sys_para;


/*****************************************************************
*********************system interrupt number**********************    
*****************************************************************/

#define	Interrupt_INT0_Number  0          
#define	Interrupt_Timer0_Timer2_Number  1
#define	Interrupt_INT1_Number  2
#define	Interrupt_Timer1_Timer3_Number  3
#define	Interrupt_Uart0_Uart1_Number  4
#define	Interrupt_Spi_Number  5
#define	Interrupt_Pca_Number  6
#define	Interrupt_Nmi_Number  7
#define	Interrupt_All_Port_Number  8
#define	Interrupt_I2c_Number  9
#define	Interrupt_Iso7816_Number  10
#define	Interrupt_Lvd_Number  11
#define	Interrupt_Vc_Number  12
#define	Interrupt_Adc_Number  13
#define	Interrupt_Rtc_Number  14
	 
typedef enum ITQ_Prior
{
	Prior_Level_00 = 0x00,
	Prior_Level_01,
	Prior_Level_10,
	Prior_Level_11,
	Prior_Level_Max
}ITQ_Prior;

typedef enum MainFreDivideSelect
{
	SystemClockIsMainFre,
	SystemClockIsMainFre2,
	SystemClockIsMainFre4,
	SystemClockIsMainFre8,
	SystemClockIsMainFreMax
}MainFreDivideSelect;

typedef enum SystemClockFromWhere
{
	SystemClockSelectLowX32K,
	SystemClockSelectHighRC,
	SystemClockMax
}SystemClockFromWhere;

typedef enum InOut32K
{	
	outside32KClock,
	Inside32KClock,
	InOutMax
}InOut32K;

typedef enum MainFreSelect
{
	MainFre_2M,
	MainFre_4M,
	MainFre_8M,
	MainFre_16M,
	MainFre_Max
}MainFreSelect;

typedef enum OutSideX32kStableSelect
{
	OutSideX32kStableSelect256,
	OutSideX32kStableSelect1024,
	OutSideX32kStableSelect4096,
	OutSideX32kStableSelect16384,
	OutSideX32kStableSelectMax
}OutSideX32kStableSelect;

typedef enum InsideIRCStableSelect
{
	InsideIRCStableSelect0,
	InsideIRCStableSelect2,
	InsideIRCStableSelect4,
	InsideIRCStableSelect16,
	InsideIRCStableSelect64,
	InsideIRCStableSelect256,
	InsideIRCStableSelect1024,
	InsideIRCStableSelect4096,
	InsideIRCStableSelectMax
}InsideIRCStableSelect;

typedef enum OutsideX32kCap
{
	OutsideX32kCap00,
	OutsideX32kCap01,
	OutsideX32kCap10,
	OutsideX32kCap11,
	OutsideX32kCapMax
}OutsideX32kCap;

typedef enum OutsideX32KBias
{
	OutsideX32KBias00,
	OutsideX32KBias01,
	OutsideX32KBias10,
	OutsideX32KBias11,
	OutsideX32KBiasMax
}OutsideX32KBias;

typedef enum MainFreOutput
{
	MainFreOutputClose,
	MainFreoutputOne,
	MainFreoutputOneOfTwo,
	MainFreoutputOneofFour,
	MainFreoutputMax
}MainFreOutput;

typedef enum PeriModulesClock1
{
	LCD_CLKEN = 1,
	ADC_CLKEN = 2,
    BGR_CLKEN = 4,
	LVD_CLKEN = 8,
	VC_ClkEN  = 16,
	PeriMax1
}PeriModulesClock1;

typedef enum PeriModulesClock2
{
	FLASH_CLKEN = 1,
	RTC_CLKEN = 2,
	DMA_CLKEN = 4,
	CRC_CLKEN = 8,
	RNG_CLKEN = 16,
	DES_CLKEN = 32,
	SPI_CLKEN = 64,
	PeriMax2
}PeriModulesClock2;

typedef enum PeriModulesClock3
{
	PORT_CLKEN = 1,
	WDT_CLKEN = 2,
	PCA_CLKEN = 4,
	TIMER_CLKEN = 8,
	UART1_CLKEN = 16,
	UART0_CLKEN = 32,
	I2C_CLKEN = 64,
	CLKEN7816 = 128,
	PeriMax3
}PeriModulesClock3;

typedef enum BuzzClockSource
{
	BuzzClockFromOutsideX32,
	BuzzClockFromInsideMainFreDivided512,
	BuzzClockMax
}BuzzClockSource;

/*****************************************************************
**************************interrupt bit define********************  
*****************************************************************/

/* Interrupt Enable Register Definitions */
#define Interrupt_IE0_EA_Pos 7
#define Interrupt_IE0_EA_Msk (1<<Interrupt_IE0_EA_Pos)

#define Interrupt_IE0_EC_Pos 6
#define Interrupt_IE0_EC_Msk (1<<Interrupt_IE0_EC_Pos)

#define Interrupt_IE0_SPIE_Pos 5
#define Interrupt_IE0_SPIE_Msk (1<<Interrupt_IE0_SPIE_Pos)

#define Interrupt_IE0_ES_Pos  4
#define Interrupt_IE0_ES_Msk (1<<Interrupt_IE0_ES_Pos)

#define Interrupt_IE0_ET1_Pos 3
#define Interrupt_IE0_ET1_Msk (1<<Interrupt_IE0_ET1_Pos)

#define Interrupt_IE0_EX1_Pos 2
#define Interrupt_IE0_EX1_Msk (1<<Interrupt_IE0_EX1_Pos)

#define Interrupt_IE0_ET0_Pos 1
#define Interrupt_IE0_ET0_Msk (1<<Interrupt_IE0_ET0_Pos)

#define Interrupt_IE0_EX0_Pos 0
#define Interrupt_IE0_EX0_Msk (1<<Interrupt_IE0_EX0_Pos)

/* additional Interrupt enable Register Definitions */
#define Interrupt_AIE_RTCE_Pos 6
#define Interrupt_AIE_RTCE_Msk (1<<Interrupt_AIE_RTCE_Pos)

#define Interrupt_AIE_ADCE_Pos 5
#define Interrupt_AIE_ADCE_Msk (1<<Interrupt_AIE_ADCE_Pos)

#define Interrupt_AIE_VCE_Pos 4
#define Interrupt_AIE_VCE_Msk (1<<Interrupt_AIE_VCE_Pos)

#define Interrupt_AIE_LVDE_Pos 3
#define Interrupt_AIE_LVDE_Msk (1<<Interrupt_AIE_LVDE_Pos)

#define Interrupt_AIE_7816E_Pos 2
#define Interrupt_AIE_7816E_Msk (1<<Interrupt_AIE_7816E_Pos)

#define Interrupt_AIE_i2cE_Pos  1
#define Interrupt_AIE_i2cE_Msk (1<<Interrupt_AIE_i2cE_Pos)

#define Interrupt_AIE_PTE_Pos   0
#define Interrupt_AIE_PTE_Msk (1<<Interrupt_AIE_PTE_Pos)

/*****************************************************************
**************************system mode define**********************  
*****************************************************************/

/* Power control Register Definitions */
#define System_PCON_SMOD01_Pos 7
#define System_PCON_SMOD01_Msk (1<<System_PCON_SMOD01_Pos)

#define System_PCON_SMOD00_Pos 6
#define System_PCON_SMOD00_Msk (1<<System_PCON_SMOD00_Pos)

#define System_PCON_SMOD11_Pos 3
#define System_PCON_SMOD11_Msk (1<<System_PCON_SMOD11_Pos)

#define System_PCON_SMOD10_Pos 2
#define System_PCON_SMOD10_Msk (1<<System_PCON_SMOD10_Pos)

#define System_PCON_IDL_Pos  0
#define System_PCON_IDL_Msk  (1<<System_PCON_IDL_Pos)

/* Low Power Mode Control Register Definitions */
#define System_LPM_LPM_Pos 1
#define System_LPM_LPM_Msk   (1<<System_LPM_LPM_Pos)

#define System_LPM_LPMEN_Pos 0
#define System_LPM_LPMEN_Msk (1<<System_LPM_LPMEN_Pos)

/*****************************************************************
**************************system clock define********************* 
*****************************************************************/

/* Clock Control Register Definitions */
#define SystemClock_CLKC_LCDCS_Pos 7
#define SystemClock_CLKC_LCDCS_Msk (1<<SystemClock_CLKC_LCDCS_Pos)

#define SystemClock_CLKC_WDTCS_Pos 6
#define SystemClock_CLKC_WDTCS_Msk (1<<SystemClock_CLKC_WDTCS_Pos)

#define SystemClock_CLKC_RTCCS_Pos 5
#define SystemClock_CLKC_RTCCS_Msk (1<<SystemClock_CLKC_RTCCS_Pos)

#define SystemClock_CLKC_SYSCS_Pos 3
#define SystemClock_CLKC_SYSCS_Msk (0x03<<SystemClock_CLKC_SYSCS_Pos)

#define SystemClock_CLKC_X32KEN_Pos 2
#define SystemClock_CLKC_X32KEN_Msk (1<<SystemClock_CLKC_X32KEN_Pos)

#define SystemClock_CLKC_IRCEN_Pos 1
#define SystemClock_CLKC_IRCEN_Msk (1<<SystemClock_CLKC_IRCEN_Pos)

#define SystemClock_CLKC_CLKSS_Pos 0
#define SystemClock_CLKC_CLKSS_Msk (1<<SystemClock_CLKC_CLKSS_Pos)

/* Main Clock Control Register Definitions */
#define SystemClock_CLKC1_MainFreSelect_Pos 6
#define SystemClock_CLKC1_MainFreSelect_Msk  (0x03<<SystemClock_CLKC1_MainFreSelect_Pos)

#define SystemClock_CLKC1_MainFreAdjust_Pos 0
#define SystemClock_CLKC1_MainFreAdjust_Msk (0x3F<<SystemClock_CLKC1_MainFreAdjust_Pos)

/* Clock Stable Cycle Control Register Definitions */
#define SystemClock_CLKC2_X32k_Stable_Pos 7
#define SystemClock_CLKC2_X32k_Stable_Msk (1<<SystemClock_CLKC2_X32k_Stable_Pos)

#define SystemClock_CLKC2_IRC_Stable_Pos 6
#define SystemClock_CLKC2_IRC_Stable_Msk (1<<SystemClock_CLKC2_IRC_Stable_Pos)

#define SystemClock_CLKC2_IRC32K_En_Pos 5
#define SystemClock_CLKC2_IRC32K_En_Msk (1<<SystemClock_CLKC2_IRC32K_En_Pos)

#define SystemClock_CLKC2_X32K_stable_sel_Pos 3
#define SystemClock_CLKC2_X32K_stable_sel_Msk (0x03<<SystemClock_CLKC2_X32K_stable_sel_Pos)

#define SystemClock_CLKC2_IRC_stable_sel_Pos 0
#define SystemClock_CLKC2_IRC_stable_sel_Msk (0x07<<SystemClock_CLKC2_IRC_stable_sel_Pos)

/*simple function*/
#define IsIRCStable()  (CLKC2 & SystemClock_CLKC2_IRC_Stable_Msk) 
#define IsX32kStable()  (CLKC2 & SystemClock_CLKC2_X32k_Stable_Msk)

/* X32K clock Control Register Definitions */
#define SystemClock_X32K_CTL_X32K_CapSel_Pos 6
#define SystemClock_X32K_CTL_X32K_CapSel_Msk (0x03<<SystemClock_X32K_CTL_X32K_CapSel_Pos)

#define SystemClock_X32K_CTL_X32K_BiaSel_Pos 4
#define SystemClock_X32K_CTL_X32K_BiaSel_Msk (0x03<<SystemClock_X32K_CTL_X32K_BiaSel_Pos)

#define SystemClock_X32K_CTL_MOUT_SEL_Pos 2
#define SystemClock_X32K_CTL_MOUT_SEL_Msk (0x03<<SystemClock_X32K_CTL_MOUT_SEL_Pos)

#define SystemClock_X32K_CTL_X32K_Fault_flag_Pos 1
#define SystemClock_X32K_CTL_X32K_Fault_flag_Msk (1<<SystemClock_X32K_CTL_X32K_Fault_flag_Pos)

#define SystemClock_X32K_CTL_X32K_Fault_enable_Pos 0
#define SystemClock_X32K_CTL_X32K_Fault_enable_Msk (1<<SystemClock_X32K_CTL_X32K_Fault_enable_Pos)

/* Buzz Control Register Definitions */
#define SystemClock_Buzz_CTL_BUZ_CS_Pos 1
#define SystemClock_Buzz_CTL_BUZ_CS_Msk (1<<SystemClock_Buzz_CTL_BUZ_CS_Pos)

#define SystemClock_Buzz_CTL_BUZ_RUN_Pos 0
#define SystemClock_Buzz_CTL_BUZ_RUN_Msk (1<<SystemClock_Buzz_CTL_BUZ_RUN_Pos)

/* Simple funcitons of Buzz*/
#define Buzz_Run()  (Buzz_CTL |=SystemClock_Buzz_CTL_BUZ_RUN_Msk)
#define Buzz_Stop() (Buzz_CTL &=~SystemClock_Buzz_CTL_BUZ_RUN_Msk)


/* Buzz counter control Register Definitions */
#define SystemClock_Buzz_CNT_BUZ_RUN_Pos 1
#define SystemClock_Buzz_CNT_BUZ_RUN_Msk (1<<SystemClock_Buzz_CNT_BUZ_RUN_Pos)


/*****************************************************************
**************************Exported_Functions**********************  
*****************************************************************/

/*********************interrupt functions************************/
void interrupt1Configure(FunctionalState Option,U8 which);
void interrupt2Configure(FunctionalState Option,U8 which);
void interruptPriorConfigure(U8 which,U8 Prior_Level);

/*********************system mode set********************************/
void System_EnterIdleMode(void);
void System_EnterLPMMode(void);

/*********************system clock set***************************/
void System_SystemClockIsMainFre(MainFreDivideSelect what);
void System_SystemClockFreSelect(SystemClockFromWhere what);
void System_SystemRCOSCEnable(FunctionalState what);
void System_SystemX32KEnable(FunctionalState what);

void System_RtcClockSelect(InOut32K which);
void System_WdtClockSelect(InOut32K which);
void System_LcdClockSelect(InOut32K which);

void L0_System_MainFreSelect(MainFreSelect which);

void System_Inside32kEnable(FunctionalState what);
void System_OutsideX32kStabletimeSelect(OutSideX32kStableSelect which);
void System_InsideIRCStabletimeSelect(InsideIRCStableSelect which);

void System_OutsideX32KCapSelect(OutsideX32kCap which);
void System_OutsideX32KBiasSelect(OutsideX32KBias which);
void System_MainFreOutputSelect(MainFreOutput which);
void System_X32KFaultEnable(FunctionalState what);

void System_Peripheralmodules1ClockEnable(FunctionalState what,vU32 which);
void System_Peripheralmodules2ClockEnable(FunctionalState what,vU32 which);
void System_Peripheralmodules3ClockEnable(FunctionalState what,vU32 which);

void System_BuzzConfigureAndRun(BuzzClockSource which,U8 counter);

void L1_System_SystemClockInitial(void);

void  L1_System_systemClockTransferToFsub(void);
void  L1_System_systemClockTransferToFmain(void);


#ifdef __cplusplus
}
#endif


#endif				

/******************* (C) COPYRIGHT 2014 SHHIC *****END OF FILE****/
