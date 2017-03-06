//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, ���ؿƼ�
/// All rights reserved.  
///  
/// @file            app_vc.h
/// @brief           votage compare app headfile  
///  
///�����ļ�ʵ�ֵĹ��ܵ�������  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20160412
///  
///  
///     �޶�˵��������汾
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

2 AA AA��Ӧ���־λ��
	�� AA ��λʱ���� SCL �ߵ�Ӧ��ʱ�������ڣ������������������֮һ
	������һ��Ӧ���źţ� SDA ��Ϊ�͵�ƽ����
		(1) ���յ�����ӵ�ַ�Ĵ����еĵ�ַ��
		(2) �� I2CADR �е�ͨ�õ���λ�� GC����λʱ�����յ�ͨ�õ��õ�ַ��
		(3) �� I2C �ӿڴ��ڿ�Ѱַ�Ĵӽ���ģʽʱ�����յ�һ�������ֽڡ�
	�� AA Ϊ��ʱ�� SCL �ߵ�Ӧ��ʱ�������ڳ����������������һ����Ӧ
	���źţ� SDA ��Ϊ�ߵ�ƽ����
		(1) �� I2C �ӿڴ���������ģʽʱ�����յ�һ�������ֽڣ�
		(2) �� I2C �ӿڴ��ڿ�Ѱַ�Ĵӽ���ģʽʱ�����յ�һ�������ֽڡ�



*************************/

#define NC	0
#define L0_i2c_NOSP()		I2C_Control(START_0,STOP_0,NC)
#define L0_i2c_start()			I2C_Control(START_1,STOP_0,NC)
#define L0_i2c_ACK() 		I2C_Control(START_0,STOP_0,ACK)	//ACK = 1; SDA = 0 master ��slaveӦ��
#define L0_i2c_NOACK() 		I2C_Control(START_0,STOP_0,NoACK)//ACK = 0; SDA = 1 master ����slaveӦ�� ���ݽ���
#define L0_i2c_stop()		I2C_Control(START_0,STOP_1,NoACK)
//A = Ӧ�� (SDA��)
// \A = ��Ӧ�� (SDA��)
#define D_iic_buf_max		16
typedef struct 
{
//	U8 now_rw;	///��ǰʹ��i2c�������Ķ�д״̬
	U8 addr;	///��ǰʹ��i2c��������i2c��ַ	
    U8 reg; 	///�Ĵ�����ַ,��ʱ,�ȷ���д����Ȼ����reg ����Ϳ�ʼ,����д����,�����ȡ����ģʽ
    			///�Ĵ�����ַ,дʱ,�ȷ���д����Ȼ����reg ���������,�����ı�reg���ڵ�ַ���Ժ������
    U8 Rxcnt; 	///Rxbuf  ����ֵ
    U8 Rxmax; 	///Rxbuf ����Ҫ���͵��������ֵ
    U8 Rxbuf[D_iic_buf_max+1]; /// �������ݻ���

	
    U8 Txcnt; 	///Txbuf  ����ֵ
    U8 Txmax; 	///Txbuf ����Ҫ���͵��������ֵ
    U8 Txbuf[D_iic_buf_max+1]; /// �������ݻ���
    
}Ts_comm_p;



struct  _s_task_i2c_
{
//	TS_task task;
//	vU32 t_stamp;	//
#ifdef D_iic_inspect

	U8 tbuf_n;
	U8 status_n;
	U8 status_buf[180];		/// i2cģ���������״̬,�ж�i2cģ���Ƿ���еı�־
	U8 tbuf[180];		/// i2cģ���������״̬,�ж�i2cģ���Ƿ���еı�־
	
#endif //#ifdef D_iic_inspect
	Ts_comm_p pool;  
//	Ts_comm_p bath; /// ��ȥϴ��Ȼ����ܽ���pool����Ӿ
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


