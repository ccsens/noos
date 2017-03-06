//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            app_vc.h
/// @brief           votage compare app headfile  
///  
///（本文件实现的功能的详述）  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20160412
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


#ifndef _msp_i2c_H 
#define _msp_i2c_H

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

//#include "../clib/Type.h"
#include "../bsp/hard_config.h"
#include "../cpu/SHC6601_system.h"
#include "uart0.h"
#include "../debug/debug_drv.h"//

#include "SHC6601_i2c.h"
//#include "../app/app_fsk.h"
/********************

2 AA AA：应答标志位。
	当 AA 置位时，在 SCL 线的应答时钟脉冲内，出现下面的任意条件之一
	将产生一个应答信号（ SDA 线为低电平）：
		(1) 接收到自身从地址寄存器中的地址；
		(2) 当 I2CADR 中的通用调用位（ GC）置位时，接收到通用调用地址；
		(3) 当 I2C 接口处于可寻址的从接收模式时，接收到一个数据字节。
	当 AA 为零时， SCL 线的应答时钟脉冲内出现下列情况将返回一个非应
	答信号（ SDA 线为高电平）：
		(1) 当 I2C 接口处于主接收模式时，接收到一个数据字节；
		(2) 当 I2C 接口处于可寻址的从接收模式时，接收到一个数据字节。



*************************/

#define NC	0
#define L0_i2c_NOSP()		I2C_Control(START_0,STOP_0,NC)
#define L0_i2c_start()			I2C_Control(START_1,STOP_0,NC)
#define L0_i2c_ACK() 		I2C_Control(START_0,STOP_0,ACK)	//ACK = 1; SDA = 0 master 给slave应答
#define L0_i2c_NOACK() 		I2C_Control(START_0,STOP_0,NoACK)//ACK = 0; SDA = 1 master 不给slave应答 数据结束
#define L0_i2c_stop()		I2C_Control(START_0,STOP_1,NoACK)
//A = 应答 (SDA低)
// \A = 非应答 (SDA高)
#define D_iic_buf_max		16
typedef struct 
{
//	U8 now_rw;	///当前使用i2c的器件的读写状态
	U8 addr;	///当前使用i2c的器件的i2c地址	
    U8 reg; 	///寄存器地址,读时,先发送写命令然后发送reg 其后发送开始,发送写命令,切入读取数据模式
    			///寄存器地址,写时,先发送写命令然后发送reg 其后发送数据,这样改变reg所在地址及以后的数据
    U8 Rxcnt; 	///Rxbuf  计数值
    U8 Rxmax; 	///Rxbuf 中需要发送的数据最大值
    U8 Rxbuf[D_iic_buf_max+1]; /// 接收数据缓存

	
    U8 Txcnt; 	///Txbuf  计数值
    U8 Txmax; 	///Txbuf 中需要发送的数据最大值
    U8 Txbuf[D_iic_buf_max+1]; /// 发送数据缓存
    
}Ts_comm_p;



struct  _s_task_i2c_
{
//	TS_task task;
//	vU32 t_stamp;	//
#ifdef D_iic_inspect

	U8 tbuf_n;
	U8 status_n;
	U8 status_buf[180];		/// i2c模块任务调度状态,判定i2c模块是否空闲的标志
	U8 tbuf[180];		/// i2c模块任务调度状态,判定i2c模块是否空闲的标志
	
#endif //#ifdef D_iic_inspect
	Ts_comm_p pool;  
//	Ts_comm_p bath; /// 先去洗澡然后才能进入pool中游泳
};
extern struct _s_task_i2c_ s_task_i2c;

#define I2C_STATUS_END 	2
#define I2C_STATUS_BEGIN 	3
#ifdef D_debug_sim
#define L0_i2c_free()	(gRegU_iic_return = I2C_STATUS_END)
#else

#define L0_i2c_free()	(I2C_STATUS_END == gRegU_iic_return)
#endif

#define L0_i2c_busy()	(I2C_STATUS_END != gRegU_iic_return)
#define L0_i2c_begin();	gRegU_iic_return = I2C_STATUS_BEGIN;L1_i2c_Configure(1);
#define L0_i2c_end();		gRegU_iic_return = I2C_STATUS_END;

extern void L1_i2c_Configure(unsigned char onf);
//extern void L1_i2c_Configure(void);
extern void L2_task_i2c_init(void);
extern void L2_i2c_write(U8 addr,U8 reg,U8 dat);
extern void L2_i2c_read(U8 addr,U8 reg,U8 num);

extern void L1n_i2c_write(U8 addr,U8 reg,U8 dat);
extern void L1n_i2c_read(U8 addr,U8 reg,U8 num);

#endif //#ifndef _msp_i2c_H 


