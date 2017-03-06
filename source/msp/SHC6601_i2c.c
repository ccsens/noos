/****************************************************************
Copyright (C) 2014, SHHIC .Co. ,Ltd. All rights reserved.

File name      :	SHC6601_i2c.c
Version        :	0.1
Author         :	Yanxian
Data	       :	2014-07-14
Description    :    I2C funcions 
****************************************************************/

#include "SHC6601_i2c.h"


/*****************************************************************
Function name : I2C_Control
Input		  : @param which:It can be one or some conbination of the 
				para.
				1 para1: START_0,START_1 
				2 para2: STOP_SIGNAL_CLEAN,STOP_1 
				3 para3: NoACK,ACK 	     			
Output		  : none
Return		  : none 
Description   : control signal type 
// fixme:  可以精简点 类似这样的代码很多
******************************************************************/
void I2C_Control(START_SIGNAL para1,STOP_SIGNAL para2,ACK_SIGNAL para3)
{
	 u8 L_Reg = 0;	 

	 if(para1)
	 	L_Reg |= I2C_I2CCON_Start_Msk;
	 if(para2)
	 	L_Reg |= I2C_I2CCON_Stop_Msk;
	 if(para3)
	 	L_Reg |= I2C_I2CCON_Ack_Msk;
	 	 
	 I2CCON = (I2CCON & (~I2C_I2CCON_Start_Msk) 
	 			& (~I2C_I2CCON_Stop_Msk) & (~I2C_I2CCON_Ack_Msk)) | L_Reg;	
}
/*****************************************************************
Function name : I2C_Baud_Select
Input		  : @param which:It can be one of the para.
			1 I2C_BAUD_1DIVIDED256 = 0x00,
			2 I2C_BAUD_1DIVIDED224,
			3 I2C_BAUD_1DIVIDED198,
			4 I2C_BAUD_1DIVIDED170,
			5 I2C_BAUD_1DIVIDED960,
			6 I2C_BAUD_1DIVIDED150,
			7 I2C_BAUD_1DIVIDED90,
			8 I2C_BAUD_1DIVIDED64,
			9 I2C_BAUD_1DIVIDED88,
			10 I2C_BAUD_1DIVIDED120,
			11 I2C_BAUD_1DIVIDED160,
			12 I2C_BAUD_1DIVIDED200,
			13 I2C_TM filling data(customer self-defines)	     			
Output		: none
Return		: none 
Description : i2c baud set 
******************************************************************/
void I2C_Baud_Select(u8 which)
{	  
	if(which <= I2C_BAUD_1DIVIDED90)
	{
		I2CCON = (I2CCON & (~0x03)& (~0x80)) | (which & 0x03) | ((which &0x04)<<5);
	}
	else if(which <= I2C_BAUD_1DIVIDED200)
	{
		I2CCON = I2CCON | 0x03 | (0x01 <<7);
		switch(which)
		{
			case I2C_BAUD_1DIVIDED64:
			I2C_TM = 0xff;
			break;
			case I2C_BAUD_1DIVIDED88:
			I2C_TM = 0xfe;
			break;
			case I2C_BAUD_1DIVIDED120:
			I2C_TM = 0xfd;
			break;
			case I2C_BAUD_1DIVIDED160:
			I2C_TM = 0xfc;
			break;
			case I2C_BAUD_1DIVIDED200:
			I2C_TM = 0xfb;
			break;
			default:
				break;
		}
	}
	else
	{
		I2CCON |= 0x03 | (0x01 <<7);		   //customer self-define
		I2C_TM = which;
	}			  	  	  
}