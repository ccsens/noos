////////////////////////////////////////////////////////////////////////////  
///@copyright  Copyright (c) 2017, 传控科技 All rights reserved.  
///-------------------------------------------------------------------------  
/// @file            msa300.c
/// @brief           msa300 driver app
///-------------------------------------------------------------------------  
/// @version		1.0  
/// @author		CC 
/// @date			20170122
/// @note			cc_swhh_MD02
//////////////////////////////////////////////////////////////////////////////

#ifndef _cw63xx_H 
#define _cw63xx_H

#define D_i2c_addr_cw63xx		0x12
#include "../bsp/hard_config.h"

///--------------------------------------------------------------------
#define D_CW63X_REG_Charge				0X01
#define D_CW63X_EN_NTC		BITN7		///Enable NTC check
#define D_CW63X_EN_CHG		BITN6		/// Enable charging
#define D_CW63X_EN_TIMER	BITN5		// Enalble charging timer

// in power-off state,the IC will turn off LDO1,2,3,B	ut hte LDORTC/LDO4 will remain on
#define D_CW63X_power_off	0x0a		
//L1_cw63xx_set(D_CW63X_REG_Safety,D_CW63X_EN_NTC|D_CW63X_EN_CHG|D_CW63X_EN_TIMER|D_CW63X_power_off);
//L1_cw63xx_set(D_CW63X_REG_Safety,D_CW63X_EN_NTC|D_CW63X_EN_CHG|D_CW63X_EN_TIMER);

///--------------------------------------------------------------------

#define D_CW63X_REG_Safety				0X02
#define D_CW63X_LowBateryThreshold	0
#define L0_set_LBT(x)	((x) - 28)
//		L0_set_LBT(28)
/// L1_cw63xx_set(D_CW63X_REG_Safety,L0_set_LBT(28));/// 2.8v报警
/// fixme 依靠这个实现电源的测量 
///--------------------------------------------------------------------
#define D_CW63X_REG_Interrupt			0X03
#define D_CW63X_REG_Interrupt_type	0X04	
#define D_CW63X_INT_CHG_OUT			BITN7	///Charging unplugged
#define D_CW63X_INT_TIMER_EXPIRE		BITN6	///Charging timer expire
#define D_CW63X_INT_CHG_INT			BITN5	///Charger detected
#define D_CW63X_INT_BAT_FULL			BITN4	///Battery full

#define D_CW63X_INT_BAT_OT			BITN3	///Battery over temperature
#define D_CW63X_INT_BAT_UT			BITN2	///Battery under temperature
#define D_CW63X_INT_LOW_BAT		BITN1	///Battery low voltage
#define D_CW63X_INT_BUTTON			BITN0	///button detected

///--------------------------------------------------------------------

#define D_CW63X_REG_LDO1	0X0A
#define D_CW63X_REG_LDO2	0X0B
#define D_CW63X_REG_LDO3	0X0C
#define D_CW63X_REG_LDO4	0X0D	

#define D_CW63XX_1V8	B0001_1100
#define D_CW63XX_2V1	B0011_0001
#define D_CW63XX_2V5	B0011_0101
#define D_CW63XX_3V	B0011_1010
#define D_CW63XX_3V2	B0011_1100

#define D_CW63XX_ON	B1000_0000
#define D_CW63XX_OFF	B1000_0000


extern void L1_cw63xx_set(U8 reg,U8 dat);
extern void L1_cw63xx_init(void);


/// read和get必须配套使用
/// L1_cw63xx_read(D_CW63X_REG_Interrupt)  if(L1_cw63xx_get())
extern void L1_cw63xx_read(U8 reg);
extern unsigned char L1_cw63xx_get(void);
extern unsigned char L1_cw63xx_write_ok(void);
extern void L1_cw63xx_write(U8 reg,U8 dat);
#endif //	#ifndef _cw63xx_H 

