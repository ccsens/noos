/****************************************************************
Copyright (C) 2014, SHHIC .Co. ,Ltd. All rights reserved.

File name     :	SHC6601_system.c
Version       :	0.1
Author        :	Yanxian
Data	      :	2014-06-11
Description   :  Achieve the function of the system related functions,
				inlude interrupt,clk,Lpm and so on
****************************************************************/

#include "SHC6601_system.h"
struct  _s_sys_para_ s_sys_para;

/*****************************************************************
Function name : System_SystemClockIsMainFre 
Input         : @param what:It may be only one of these everytime.
				1.SystemClockIsMainFre
				2.SystemClockIsMainFre2
				3.SystemClockIsMainFre4
				4.SystemClockIsMainFre8
Output		  : none
Return		  : none
Description	  :	select system clock
******************************************************************/
void System_SystemClockIsMainFre(MainFreDivideSelect what)
{
	CLKC = (CLKC & ~SystemClock_CLKC_SYSCS_Msk) | (what<<SystemClock_CLKC_SYSCS_Pos);
}


/*****************************************************************
Function name : interrupt1Configure 
Input         : @param Option: 1. DISABLE; 2.ENABLE	
                @param which : It may be one or a combination of these.
				1. Interrupt_IE0_EA_Msk 

				2. Interrupt_IE0_EC_Msk 

				3. Interrupt_IE0_SPIE_Msk 

				4. Interrupt_IE0_ES_Msk 

				5. Interrupt_IE0_ET1_Msk 

				6. Interrupt_IE0_EX1_Msk 

				7. Interrupt_IE0_ET0_Msk 

				8. Interrupt_IE0_EX0_Msk 
Output		  : none
Return		  : none
Description	  :	open or close the Corresponding interrupt
******************************************************************/
void interrupt1Configure(FunctionalState Option,U8 which)
{
	if(Option)
	{
		IE0 |= which;
	}
	else
	{
		IE0 &= ~which;	
	}	 
}
/*****************************************************************
Function name : interrupt2Configure 
Input         : @param Option: 1. DISABLE; 2.ENABLE	
                @param which : It may be one or a combination of these.
				1. Interrupt_AIE_RTCE_Msk 

				2. Interrupt_AIE_ADCE_Msk 

				3. Interrupt_AIE_VCE_Msk 

				4. Interrupt_AIE_LVDE_Msk 

				5. Interrupt_AIE_7816E_Msk 

				6. Interrupt_AIE_i2cE_Msk 

				7. Interrupt_AIE_PTE_Msk 
Output		  : none
Return		  : none
Description	  :	open or close the Corresponding interrupt
******************************************************************/
void interrupt2Configure(FunctionalState Option,U8 which)
{
	if(Option)
	{
		AIE |= which;
	}
	else
	{
		AIE &= (~which);	
	}		
}
#if 10



/*****************************************************************
Function name : System_SystemClockFreSelect 
Input         : @param what:It may be only one of these everytime.
				1.SystemClockSelectHighRC
				2.SystemClockSelectLowX32K
Output		  : none
Return		  : none
Description	  :	select system clock from where
******************************************************************/
void System_SystemClockFreSelect(SystemClockFromWhere what)
{
	CLKC = (CLKC & ~SystemClock_CLKC_CLKSS_Msk) | (what<<SystemClock_CLKC_CLKSS_Pos);
}
/*****************************************************************
Function name : System_SystemRCOSCEnable 
Input         : @param what:It may be only one of these everytime.
				1.DISABLE
				2.ENABLE
Output		  : none
Return		  : none
Description	  :	enable or disable the RC OSC
******************************************************************/
void System_SystemRCOSCEnable(FunctionalState what)
{
	if(what)
	{
		CLKC |= SystemClock_CLKC_IRCEN_Msk; 
	}
	else
	{
		CLKC &= (~SystemClock_CLKC_IRCEN_Msk);
	}
}
/*****************************************************************
Function name : System_RtcClockSelect 
Input         : @param what:It may be only one of these everytime.
				1.Inside32KClock
				2.outside32KClock
Output   	  : none
Return		  : none
Description	  :	Rtc clock select
******************************************************************/
void System_RtcClockSelect(InOut32K which)
{
	CLKC = ((CLKC & ~SystemClock_CLKC_RTCCS_Msk) | (which<<SystemClock_CLKC_RTCCS_Pos));
}

/*****************************************************************
Function name : System_X32KFaultEnable
Input         : @param what:It may be only one of these everytime.
				1.DISABLE  
				2.ENABLE 
Output   	  : none
Return		  : none
Description	  :	X32K fault enable or diable
******************************************************************/
void System_X32KFaultEnable(FunctionalState what)
{
	if(what)
	{
		X32K_CTL |= SystemClock_X32K_CTL_X32K_Fault_enable_Msk;
	}
	else
	{
		X32K_CTL &= ~SystemClock_X32K_CTL_X32K_Fault_enable_Msk;
	}
}
/*****************************************************************
Function name : System_Peripheralmodules1ClockEnable
Input         : @param what:It may be only one of these everytime.
		        1.DISABLE  
		        2.ENABLE
				@param which:It may be one or combination of these everytime.
			    1.LCD_CLKEN 
			    2.ADC_CLKEN
			    3.BGR_CLKEN
			    4.LVD_CLKEN
			    5.VC_ClkEN  		        
Output   	  : none
Return		  : none
Description	  :	Peripheral modules1 Clock open or close
******************************************************************/
void System_Peripheralmodules1ClockEnable(FunctionalState what,vU32 which)
{
	if(what)
	{
		PERI_CLK0 |= which;
	}
	else
	{
		PERI_CLK0 &= ~which;
	}
}
/*****************************************************************
Function name : System_Peripheralmodules2ClockEnable
Input         : @param what:It may be only one of these everytime.
		        1.DISABLE  
		        2.ENABLE
				@param which:It may be one or combination of these everytime.
				1.FLASH_CLKEN
				2.RTC_CLKEN 
				3.DMA_CLKEN 
				4.CRC_CLKEN 
				5.RNG_CLKEN 
				6.DES_CLKEN 
				7.SPI_CLKEN       
Output   	  : none
Return		  : none
Description	  :	Peripheral modules2 Clock open or close
******************************************************************/
void System_Peripheralmodules2ClockEnable(FunctionalState what,vU32 which)
{
	if(what)
	{
		PERI_CLK1 |= which;
	}
	else
	{
		PERI_CLK1 &= ~which;
	}
}
/*****************************************************************
Function name : System_BuzzConfigureAndRun
Input         : @param which:It may be only one of these everytime.
		        1.BuzzClockFromOutsideX32
	            2.BuzzClockFromInsideMainFreDivided512 
				@param counter: 0-255      
Output   	  : none
Return		  : none
Description	  :	configure buzz register and run it

System_BuzzConfigureAndRun(BuzzClockFromOutsideX32,231);

******************************************************************/
void System_BuzzConfigureAndRun(BuzzClockSource which,U8 counter)
{
	Buzz_CTL = (Buzz_CTL & ~SystemClock_Buzz_CTL_BUZ_CS_Msk) | (which<<SystemClock_Buzz_CTL_BUZ_CS_Pos);
	Buzz_CNT = counter;
	Buzz_Stop();//Buzz_Run();
}



/*****************************************************************
Function name : System_InsideIRCStabletimeSelect 
Input         : @param what:It may be only one of these everytime.
				1.InsideIRCStableSelect0
				2.InsideIRCStableSelect2
				3.InsideIRCStableSelect4
				4.InsideIRCStableSelect16
				5.InsideIRCStableSelect64
				6.InsideIRCStableSelect256
				7.InsideIRCStableSelect1024
				8.InsideIRCStableSelect4096
Output   	  : none
Return		  : none
Description	  :	inside IRC clock stable time select
******************************************************************/
void System_InsideIRCStabletimeSelect(InsideIRCStableSelect which)
{
	CLKC2 = ((CLKC2 & ~SystemClock_CLKC2_IRC_stable_sel_Msk) | (which<<SystemClock_CLKC2_IRC_stable_sel_Pos));
}

/*****************************************************************
Function name : System_Inside32kEnable 
Input         : @param what:It may be only one of these everytime.
				1.ENABLE
				2.DISABLE 
Output   	  : none
Return		  : none
Description	  :	inside 32k clock enable or diable
******************************************************************/
void System_Inside32kEnable(FunctionalState what)
{
	if(what)
	{
		CLKC2 |= SystemClock_CLKC2_IRC32K_En_Msk;
	}
	else
	{
		CLKC2 &= ~SystemClock_CLKC2_IRC32K_En_Msk;
	}
}
/*****************************************************************
Function name : System_LcdClockSelect 
Input         : @param what:It may be only one of these everytime.
				1.Inside32KClock 
				2.outside32KClock
Output   	  : none
Return		  : none
Description	  :	Lcd clock select
******************************************************************/
void System_LcdClockSelect(InOut32K which)
{
	CLKC = ((CLKC & ~SystemClock_CLKC_LCDCS_Msk) | (which<<SystemClock_CLKC_LCDCS_Pos));
}


/*****************************************************************
Function name : System_SystemX32KEnable 
Input           : @param what:It may be only one of these everytime.
				1.DISABLE
				2.ENABLE
Output		  : none
Return		  : none
Description	  : enable or disable the X32K
******************************************************************/
void System_SystemX32KEnable(FunctionalState what)
{
	if(what)
	{
		CLKC |= SystemClock_CLKC_X32KEN_Msk; 
	}
	else
	{
		CLKC &= (~SystemClock_CLKC_X32KEN_Msk);
	}
}

/*****************************************************************

Function name : System_Peripheralmodules3ClockEnable
Input         : @param what:It may be only one of these everytime.
		        1.DISABLE  
		        2.ENABLE
				@param which:It may be one or combination of these everytime.
				1.PORT_CLKEN
				2.WDT_CLKEN
				3.PCA_CLKEN 
				4.Timer_CLKEN 
				5.UART1_CLKEN
				6.UART0_CLKEN 
				7.I2C_CLKEN
				8.CLKEN7816	        
Output   	  : none
Return		  : none
Description	  :	Peripheral modules3 Clock open or close
******************************************************************/
void System_Peripheralmodules3ClockEnable(FunctionalState what,U32 which)
{
	if(what)
	{
		PERI_CLK2 |= which;
	}
	else
	{
		PERI_CLK2 &= ~which;
	}
}

#else



/*****************************************************************
Function name : System_EnterIdleMode 
Input         : none				
Output		  : none
Return		  : none
Description	  :	enter idle mode
******************************************************************/
void System_EnterIdleMode(void)
{
	PCON |= System_PCON_IDL_Msk;

//	_nop_();
//	_nop_();
}
/*****************************************************************
Function name : System_EnterLPMMode 
Input         : none				
Output		  : none
Return		  : none
Description	  :	enter low power mode
******************************************************************/
void System_EnterLPMMode(void)
{
	LPM |= System_LPM_LPMEN_Msk;
	LPM |= System_LPM_LPM_Msk; 

	_nop_();
	_nop_();
}


/*****************************************************************
Function name : interruptPriorConfigure 
Input         : @param which : It may be only one of these everytime.
				  1.Interrupt_INT0_Number           
				  2.Interrupt_Timer0_Timer2_Number 
				  3.Interrupt_INT1_Number
				  4.Interrupt_Timer1_Timer3_Number 
				  5.Interrupt_Uart0_Uart1_Number 
				  6.Interrupt_Spi_Number
				  7.Interrupt_Pca_Number 
				  8.Interrupt_All_Port_Number
				  9.Interrupt_I2c_Number 
				  10.Interrupt_Iso7816_Number
				  11.Interrupt_Lvd_Number
				  12.Interrupt_Vc_Number
				  13.Interrupt_Adc_Number
				  14.Interrupt_Rtc_Number
			    @param Prior_Level:			
				  1.Prior_Level_00
				  2.Prior_Level_01
				  3.Prior_Level_10
				  4.Prior_Level_11	
Output		  : none
Return		  : none
Description	  :	interrupt prior configure
******************************************************************/
void interruptPriorConfigure(U8 which,U8 Prior_Level)
{
	U8 Prior_Level_High = 0;
	U8 Prior_Level_Low = 0;

    /* clear the corresbonding bit*/	
	if(which <= 6)
	{
		IPH0 &= ~(1<<which);
		IPL0 &= ~(1<<which);
	}
	else
	{
		AIPH &= ~(1<<(which - 8));
		AIPL &= ~(1<<(which - 8));
	}
	
	/*configure the interrupt*/
	Prior_Level_High = (Prior_Level>>1) & 0x01;
	Prior_Level_Low = (Prior_Level&0x01);
	
	switch (which)
	{
		case 0:
			IPH0 |=  Prior_Level_High;
			IPL0 |=  Prior_Level_Low;
		break;
		case 1:
			IPH0 |=  Prior_Level_High<<1;
			IPL0 |=  Prior_Level_Low<<1;
		break;
		case 2:
			IPH0 |=  Prior_Level_High<<2;
			IPL0 |=  Prior_Level_Low<<2;
		break;
		case 3:
			IPH0 |=  Prior_Level_High<<3;
			IPL0 |=  Prior_Level_Low<<3;
		break;
		case 4:
			IPH0 |=  Prior_Level_High<<4;
			IPL0 |=  Prior_Level_Low<<4;
		break;
		case 5:
			IPH0 |=  Prior_Level_High<<5;
			IPL0 |=  Prior_Level_Low<<5;
		break;
		case 6:
			IPH0 |=  Prior_Level_High<<6;
			IPL0 |=  Prior_Level_Low<<6;
		break;
		case 8:
			AIPH |=  Prior_Level_High;
			AIPL |=  Prior_Level_Low;
		break;
		case 9:
			AIPH |=  Prior_Level_High<<1;
			AIPL |=  Prior_Level_Low<<1;
		break;
		case 10:
			AIPH |=  Prior_Level_High<<2;
			AIPL |=  Prior_Level_Low<<2;
		break;
		case 11:
			AIPH |=  Prior_Level_High<<3;
			AIPL |=  Prior_Level_Low<<3;
		break;
		case 12:
			AIPH |=  Prior_Level_High<<4;
			AIPL |=  Prior_Level_Low<<4;
		break;
		case 13:
			AIPH |=  Prior_Level_High<<5;
			AIPL |=  Prior_Level_Low<<5;
		break;
		case 14:
			AIPH |=  Prior_Level_High<<6;
			AIPL |=  Prior_Level_Low<<6;
		break;
		default:
			break;	
	}
}


/*****************************************************************
Function name : System_WdtClockSelect 
Input         : @param what:It may be only one of these everytime.
				1.Inside32KClock
				2.outside32KClock
Output   	  : none
Return		  : none
Description	  :	Wdt clock select
******************************************************************/
void System_WdtClockSelect(InOut32K which)
{
	CLKC = ((CLKC & ~SystemClock_CLKC_WDTCS_Msk) | (which<<SystemClock_CLKC_WDTCS_Pos));
}


/*****************************************************************
Function name : System_OutsideX32kStabletimeSelect 
Input         : @param what:It may be only one of these everytime.
				1.OutSideX32kStableSelect256
				2.OutSideX32kStableSelect1024
				3.OutSideX32kStableSelect4096
				4.OutSideX32kStableSelect16384
Output   	  : none
Return		  : none
Description	  :	outside x32k stable time select
******************************************************************/
void System_OutsideX32kStabletimeSelect(OutSideX32kStableSelect which)
{
	CLKC2 = ((CLKC2 & ~SystemClock_CLKC2_X32K_stable_sel_Msk) | (which<<SystemClock_CLKC2_X32K_stable_sel_Pos));
}

/*****************************************************************
Function name : System_OutsideX32KCapSelect
Input         : @param what:It may be only one of these everytime.
				1.OutsideX32kCap00,
				2.OutsideX32kCap01,
				3.OutsideX32kCap10,
				4.OutsideX32kCap11,
Output   	  : none
Return		  : none
Description	  :	outside x32k cap select
******************************************************************/
void System_OutsideX32KCapSelect(OutsideX32kCap which)
{	
	X32K_CTL  = (X32K_CTL & ~SystemClock_X32K_CTL_X32K_CapSel_Msk) | (which<<SystemClock_X32K_CTL_X32K_CapSel_Pos);
}
/*****************************************************************
Function name : System_OutsideX32KBiasSelect 
Input         : @param what:It may be only one of these everytime.
				1.OutsideX32KBias00
				2.OutsideX32KBias01
				3.OutsideX32KBias10
				4.OutsideX32KBias11
Output   	  : none
Return		  : none
Description	  :	outside x32k Bias select
******************************************************************/
void System_OutsideX32KBiasSelect(OutsideX32KBias which)
{
	X32K_CTL = (X32K_CTL & ~SystemClock_X32K_CTL_X32K_BiaSel_Msk) | (which<<SystemClock_X32K_CTL_X32K_BiaSel_Pos);
}
/*****************************************************************
Function name : System_MainFreOutputSelect
Input         : @param what:It may be only one of these everytime.
				1.MainFreOutputClose,
	            2.MainFreoutputOne,
	            3.MainFreoutputOneOfTwo,
	            4.MainFreoutputOneofFour,	
Output   	  : none
Return		  : none
Description	  :	main frequency output select
******************************************************************/
void System_MainFreOutputSelect(MainFreOutput which)
{
	X32K_CTL  = (X32K_CTL & ~SystemClock_X32K_CTL_MOUT_SEL_Msk) | (which<<SystemClock_X32K_CTL_MOUT_SEL_Pos);
}


/*****************************************************************
Function name : System_systemClockTransferToFsub
Input         : none       
Output   	  : none
Return		  : none
Description	  :	system clock transfer to Fsub
******************************************************************/
void L1_System_systemClockTransferToFsub(void)
{
	System_SystemRCOSCEnable(ENABLE);
	System_SystemX32KEnable(ENABLE);
	System_SystemClockFreSelect(SystemClockSelectHighRC);

	while(!(IsX32kStable()));

	System_SystemClockFreSelect(SystemClockSelectLowX32K);
	System_SystemRCOSCEnable(DISABLE);
}


/*****************************************************************
Function name  : System_systemClockTransferToFmain
Input          : none       
Output   	   : none
Return		   : none
Description	   : system clock transfer to Fmain
******************************************************************/
void  L1_System_systemClockTransferToFmain(void)
{
	System_SystemRCOSCEnable(ENABLE);
	System_SystemX32KEnable(ENABLE);
	System_SystemClockFreSelect(SystemClockSelectLowX32K);

	while(!(IsIRCStable()));
	
	System_SystemClockFreSelect(SystemClockSelectHighRC);
	System_SystemX32KEnable(DISABLE);	
}

#endif
/*****************************************************************
Function name : System_SystemClockInitial
Input         : none       
Output   	  : none
Return		  : none
Description	  :	system clock initial,main frequency 4M,stable time
				4096,source from highRC,not divided
******************************************************************/
void L1_System_SystemClockInitial(void)
{
	#ifdef D_debug_sim
		int n;
	#endif
	L0_System_MainFreSelect(D_MainFre);
	//L0_System_MainFreSelect(MainFre_16M);
	

	System_InsideIRCStabletimeSelect(InsideIRCStableSelect4096);
	System_SystemClockIsMainFre(SystemClockIsMainFre);
	System_SystemClockFreSelect(SystemClockSelectHighRC);

	System_SystemRCOSCEnable(ENABLE);
	while(!(IsIRCStable()))
	{
		#ifdef D_debug_sim
		if (n++ > 10000)n = 0;
			break;
		#endif
	}

	System_SystemX32KEnable(ENABLE);
 	while(!(IsX32kStable()))
	{
		#ifdef D_debug_sim
		if (n++ > 10000)
			break;
		#endif
	} 
	System_RtcClockSelect(outside32KClock);
};
/*****************************************************************
Function name : System_MainFreSelect 
Input         : @param what:It may be only one of these everytime.
				1.MainFre_2M 
				2.MainFre_4M
                3.MainFre_8M
				4.MainFre_16M
Output   	  : none
Return		  : none
Description	  :	main frequency clock select
******************************************************************/
void L0_System_MainFreSelect(MainFreSelect which)
{
	switch (which)
	{
		case 0x00:
			CLKC1 = ((CAL0>>8) & 0xFF);
			s_sys_para.sys_clock = 2000000;
		break;
		case 0x01:
			CLKC1 = ((CAL0 & 0xFF));
			s_sys_para.sys_clock = 4000000;
		break;
		case 0x02:
			CLKC1 = ((CAL1>>8) & 0xFF);
			s_sys_para.sys_clock = 8000000;
		break;
		case 0x03:
			CLKC1 = (CAL1 & 0xFF);
			s_sys_para.sys_clock = 16000000;
		break;
		default:
			s_sys_para.sys_clock = 2000000;
			break;
	}
}


/*******************(C) COPYRIGHT 2014 SHHIC *****END OF FILE*****/
