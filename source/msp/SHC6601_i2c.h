/****************************************************************
Copyright (C) 2014, SHHIC .Co. ,Ltd. All rights reserved.

File name      :	SHC6601_i2c.h
Version        :	0.1
Author         :	Yanxian
Data	       :	2014-07-14
Description    :    i2c defines 
****************************************************************/

#ifndef _SHC6601_i2c_H_
#define _SHC6601_i2c_H_	

#ifdef __cplusplus
 extern "C" {
#endif

#include "../bsp/hard_config.h"
#include "../debug/debug_drv.h"	
#include "../cpu/SHC6601_system.h"


/*****************************************************************
************************** struct and enum************************  
*****************************************************************/
typedef enum 
{	
	START_0 = 0x00,
	START_1 
}START_SIGNAL;

typedef enum 
{	
	STOP_0 = 0x00,
	STOP_1 
}STOP_SIGNAL;

typedef enum 
{	
	NoACK = 0x00,
	ACK 
}ACK_SIGNAL;

typedef enum I2C_Baud
{
	I2C_BAUD_1DIVIDED256,
	I2C_BAUD_1DIVIDED224,
	I2C_BAUD_1DIVIDED198,
	I2C_BAUD_1DIVIDED170,
	I2C_BAUD_1DIVIDED960,
	I2C_BAUD_1DIVIDED150,
	I2C_BAUD_1DIVIDED90,
	I2C_BAUD_1DIVIDED64,
	I2C_BAUD_1DIVIDED88,
	I2C_BAUD_1DIVIDED120,
	I2C_BAUD_1DIVIDED160,
	I2C_BAUD_1DIVIDED200,
	I2C_BAUD_OHTER
}I2C_Baud;

#define I2C_I2CCON_i2c_Enable_Pos 6
#define I2C_I2CCON_i2c_Enable_Msk (0x01<<I2C_I2CCON_i2c_Enable_Pos)

#define I2C_I2CCON_Start_Pos  5
#define I2C_I2CCON_Start_Msk (0x01<<I2C_I2CCON_Start_Pos)

#define I2C_I2CCON_Stop_Pos  4
#define I2C_I2CCON_Stop_Msk (0x01<<I2C_I2CCON_Stop_Pos)

#define I2C_I2CCON_Ack_Pos	2
#define I2C_I2CCON_Ack_Msk (0x01<<I2C_I2CCON_Ack_Pos)
 
/*****************simple function********************************/
#define I2C_Moudle_Enable()      (I2CCON |= I2C_I2CCON_i2c_Enable_Msk)
#define I2C_Moudle_Disable()     (I2CCON &= ~I2C_I2CCON_i2c_Enable_Msk) 

#define I2C_Interrupt_Clean()    (I2CCON &= (~(0x01 << 3)))

#define I2C_Baud_Counter_Run() 	 (I2C_RUN |= 0x01)
#define I2C_Baud_Counter_Stop()  (I2C_RUN &= ~0x01)

/*****************************************************************
************************** Exported_fuctions************************ 
*****************************************************************/


#ifdef D_iic_inspect
#define L0_I2C_Write(x)	s_task_i2c.tbuf[s_task_i2c.tbuf_n ++ ] = x;I2CDAT = x
#else
#define L0_I2C_Write(x)	I2CDAT = (x)
#endif //#ifdef D_iic_inspect
#define L0_I2C_Read(x)		(I2CDAT) 


void I2C_Control(START_SIGNAL para1,STOP_SIGNAL para2,ACK_SIGNAL para3);
void I2C_Baud_Select(u8 which);

#ifdef __cplusplus
}
#endif

#endif
