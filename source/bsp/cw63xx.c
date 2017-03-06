////////////////////////////////////////////////////////////////////////////  
///@copyright  Copyright (c) 2017, 传控科技 All rights reserved.  
///-------------------------------------------------------------------------  
/// @file            cw63xx.c
/// @brief           cw630x driver app
///-------------------------------------------------------------------------  
/// @version		1.0  
/// @author		CC 
/// @date			20170122
/// @note			cc_swhh_MD02
//////////////////////////////////////////////////////////////////////////////

#include "cw63xx.h"	
#include "../debug/debug_drv.h"
#include "../msp/msp_i2c.h"
///-------------------------------------------------------------------------     
///      @breif L1_cw63xx_init     
///      @param a s_task_PWON
///      @param s "L1_cw63xx_init"
///      @return	none
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
///-------------------------------------------------------------------------
void L1_cw63xx_init(void)
{
//	L1_cw63xx_set(D_CW63X_REG_LDO1,D_CW63XX_ON|D_CW63XX_1V8);
//	L1_cw63xx_set(D_CW63X_REG_LDO4,D_CW63XX_ON|D_CW63XX_1V8);	// 打开 LDO1 并设置为1.8v
//	L1_cw63xx_set(D_CW63X_REG_LDO1,D_CW63XX_OFF|D_CW63XX_1V8);// 关闭LDO1 
/// pw_IRQ  P04
/// PW_PG   P20

 
}


// 260uA/Mhz@3v  4M  cpu: VCC 工作电压 1.80 3.0 3.80*1 V

/// reg[5:3] [2:0]     7654,3210

/*************************sdf地方大发dfd地方



///-------------------------------------------------------------------------     
///      @breif L1_cw63xx_set     
///      @param a sta
///      @param s "L1_cw63xx_set"
///      @return	
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
///-------------------------------------------------------------------------
void L1_cw63xx_set(U8 reg,U8 dat)
{	
	s_task_i2c.bath.Txmax = 1;
	s_task_i2c.bath.addr =  D_i2c_addr_cw63xx;
	s_task_i2c.bath.reg =  reg;
	s_task_i2c.bath.Txbuf[0] = dat;
	L3_i2c_write();
}



void L1_cw63xx_read(U8 reg,U8 *dat)
{	
	s_task_i2c.bath.Rxmax = 1;
	s_task_i2c.bath.addr =  D_i2c_addr_cw63xx;
	s_task_i2c.bath.reg =  reg;
	L3_i2c_read();
//	L0_uart0_uc('r');
	//
//	L0_uart0_uchex('r');

				// 0 	1 	2
				//addr reg max
}
/// L1_cw63xx_get();  L1_cw63xx_set()



00 : B1110_0000   E0
01 : B0010_0000   20
02 : B0000_0101   05
03 : B0000_0000   00
04 : B1111_1111   FF

0A : B1011_1100   BC
0B : B0001_1100   1C
0C : B0011_1100   3C
0D : B1011_1100   BC


*****/
void L1_cw63xx_read(U8 reg)
{	
	if(L0_i2c_free())
	{
		L1n_i2c_read(D_i2c_addr_cw63xx,reg,0x01);
	}
}

unsigned char L1_cw63xx_get(void)
{	
	if(L0_i2c_free())
	{
		//L0_i2c_end();
		gRegU_CWreg = s_task_i2c.pool.Rxbuf[1];
		L1_i2c_Configure(0);
		return 1;
	}else
	{
		return 0;

	}
	/// s_task_i2c.pool.Rxbuf[0]; 数据保留在

}

void L1_cw63xx_write(U8 reg,U8 dat)
{	
	if(L0_i2c_free())
	{
		L1n_i2c_write(D_i2c_addr_cw63xx,reg,dat);
	}
}

unsigned char L1_cw63xx_write_ok(void)
{	
	if(L0_i2c_free())
	{
		L1_i2c_Configure(0);
		return 1;
	}else
	{
		return 0;
	}
	/// s_task_i2c.pool.Rxbuf[0]; 数据保留在

}



