//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            main.c
/// @brief           main app  
///  
///（本文件实现的功能的详述）  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20150102
///  
///  
///     修订说明：最初版本
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	CC-PWR-VH01-m02.sch
//////////////////////////////////////////////////////////////////////////

//20160413 CC-ACC-VH02 




/// 下面是一个含有两个参数的函数的注释说明（简述）   
///     
///      这里写该函数的详述信息     
///      @param a 被测试的变量（param描述参数）     
///      @param s 指向描述测试信息的字符串     
///      @return     测试结果（return描述返回值）   
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 




/************************************************


/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "msp_i2c.h"	

#define I2C_Read 1

#define Master_Read_Data 0
#define Master_Write_Data 1



#ifdef D_iic_inspect

void L2_i2c_debug_init(void)
{
		int n;

		s_task_i2c.status_buf[15] = 0;
		s_task_i2c.tbuf_n = 0;
		s_task_i2c.status_n = 0;
		s_task_i2c.bath.Rxcnt =  0;
}

void L2_i2c_debug(void)
{
		int n;
			L0_uart0_uc(0x0d);	L0_uart0_uc(0x0a);
			L0_uart0_uc('T');	
			L0_uart0_uchex(s_task_i2c.tbuf_n);
			for(n = 0;n < s_task_i2c.tbuf_n;n ++)
			{
				//L0_uart0_uc(' ');
				L0_uart0_uchex(s_task_i2c.tbuf[n]);
			}
			#if 10
			// L0_uart0_uc(0x0d);	L0_uart0_uc(0x0a);
			L0_uart0_uc('s');				
			L0_uart0_uchex(s_task_i2c.status_n);
			//L0_uart0_uc('n');		
			//L0_uart0_uchex(s_task_i2c.status_buf[15]);
			//L0_uart0_uc(':');
			for(n = 0;n < s_task_i2c.status_n;n ++)
			{
				//L0_uart0_uc(' ');
				L0_uart0_uchex(s_task_i2c.status_buf[n]);
			}
			#endif
			if(s_task_i2c.pool.Rxcnt)
			{
				//L0_uart0_uc(0x0d);	L0_uart0_uc(0x0a);
				L0_uart0_uc('R');				
				L0_uart0_uchex(s_task_i2c.pool.Rxcnt);
				//L0_uart0_uc('n');		
				//L0_uart0_uchex(s_task_i2c.status_buf[15]);
				//L0_uart0_uc(':');
				for(n = 0;n < s_task_i2c.pool.Rxcnt;n ++)
				{
					//L0_uart0_uc(' ');
					L0_uart0_uchex(s_task_i2c.pool.Rxbuf[n]);
				}
				L0_uart0_uc(0x0d);	L0_uart0_uc(0x0a);
			}

}
#else
#define L2_i2c_debug()			
#define L2_i2c_debug_init()		

#endif //#ifdef D_iic_inspect













void L1_i2c_Configure(unsigned char onf)
{

	if(1 == onf)
	{
		//step 1: 系统时钟选择
		//step 2: 使能 I2C 中断 AIE.I2CE；附加中断使能寄存器(AIE)
					//  1 I2CE I2C 中断使能信号
					//  1： I2C 中断使能
					//  0： I2C 中断禁止
		//step 3: IE0里面的最高位 全局中断
		//step 4: 管脚设置
		//step 5: iic 波特率设置 
		//step 6: iic 波特率启动
		//step 7: iic 模块使能
		
		 System_Peripheralmodules3ClockEnable(ENABLE,I2C_CLKEN); //open the i2c clock

		 interrupt2Configure(ENABLE,Interrupt_AIE_i2cE_Msk);	 //open the interrupt of i2c
		 //interrupt1Configure(ENABLE,Interrupt_IE0_EA_Msk);/// 全局中断
		// P10 SCL
		// p11 SDA
	///P10_SEL2,P10_SEL1:
	///00: P10 被配置成 GPIO
	///01: P10 被配置成 I2C SCL 端口
	///10: P10 被配置成副频时钟 X32K 输出端口
	///11: P10 被配置成计数器 Timer1 的门控输入
		BITN_0(P1_SEL2,BITN0);	BITN_1(P1_SEL1,BITN0);
		BITN_0(P1_SEL2,BITN1);	BITN_1(P1_SEL1,BITN1);

	///Px_PE  端口Px 输入上拉使能寄存器
	///0 Px0_PE 端口 Px0 输入上拉使能信号
	///0：无上拉功能
	///1：有内部上拉功能
	//	BITN_1(P1_PE,BITN0|BITN1);		///1：有内部上拉功能 如果外部不加电阻上拉
		BITN_1(P1_OD,BITN0|BITN1);		///1：输出为开漏(Open Drain)输出

	///bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0 地址 初始值 属性 支持端口
	///P0_DIR 0x0AC 11111111
	///R/W
	///P07--P00

	///1 PxDIR 端口 Px1 输入输出配置寄存器
	///1：配置成输入
	///0：配置成输出
		BITN_0(P1_DIR,BITN0|BITN1);		///设置为输出 不设置会出错
	//	BITN_1(P1,BITN0|BITN1);				///
	//	BITN_1(P1_DS,BITN0|BITN1);			///增强型
		
		////	 P1_DIR &= 	~(BIT0 |BIT1);	
		//I2C_Baud_Select(I2C_BAUD_1DIVIDED960);		// 4m时钟 I2C_BAUD_1DIVIDED960 clk周期120usx2
		I2C_Baud_Select(I2C_BAUD_1DIVIDED64);		// 4m时钟 I2C_BAUD_1DIVIDED64 clk周期18us
		//I2C_Baud_Select(I2C_BAUD_1DIVIDED90);		// 4m时钟 I2C_BAUD_1DIVIDED64 clk周期18us

		I2C_Baud_Counter_Run();		 
		I2C_Moudle_Enable();                //i2c part enable 			
		L2_i2c_debug_init();
//		L0_uart0_uc('A');
		//Lc_delay_ms(400);
		
	}else
	{
		BITN_0(PERI_CLK2,I2C_CLKEN); ///close the i2c clock
		BITN_0(AIE,Interrupt_AIE_i2cE_Msk);// close the interrupt of i2c
		 //interrupt1Configure(ENABLE,Interrupt_IE0_EA_Msk);/// 全局中断
		// P10 SCL
		// p11 SDA
	///P10_SEL2,P10_SEL1:
	///00: P10 被配置成 GPIO
		BITN_0(P1_SEL2,BITN0);	BITN_0(P1_SEL1,BITN0);
		BITN_0(P1_SEL2,BITN1);	BITN_0(P1_SEL1,BITN1);

	///Px_PE  端口Px 输入上拉使能寄存器
	///0 Px0_PE 端口 Px0 输入上拉使能信号
	///0：无上拉功能
	///1：有内部上拉功能
	//	BITN_1(P1_PE,BITN0|BITN1);		///1：有内部上拉功能 如果外部不加电阻上拉
		BITN_0(P1_OD,BITN0|BITN1);		///1：输出为开漏(Open Drain)输出

	///bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0 地址 初始值 属性 支持端口
	///P0_DIR 0x0AC 11111111
	///R/W
	///P07--P00

	///1 PxDIR 端口 Px1 输入输出配置寄存器
	///1：配置成输入
	///0：配置成输出
		BITN_1(P1_DIR,BITN0|BITN1);		///设置成输入  
	//	BITN_1(P1,BITN0|BITN1);				///
	//	BITN_1(P1_DS,BITN0|BITN1);			///增强型

		I2C_Baud_Counter_Stop();		 
		I2C_Moudle_Disable();                //i2c part enable 		
		
	//	L0_uart0_uc('B');
		//Lc_delay_ms(400);
	}
}


/*****************************************************************
Function name : interruptI2cHandler 
Input         : none				
Output		  : none
Return		  : none
Description	  :	i2c Interrupt handler

6 ENS1 I2C 接口使能。
	当 ENS1 置“ 1”时，使能 I2C 接口。
5 STA 起始标志位。
	当 STA=1 时， I2C 接口进入主模式并发送一个起始条件，如果已经处于
	主模式，则发送一个重复起始条件。
	当 STA=1 并且 I2C 接口还没进入主模式时， I2C 接口进入主模式，检测
	总线并在总线空闲时产生一个起始条件。如果总线忙，则等待一个停
	止条件（释放总线）并在延迟半个内部时钟发生器周期后发送一个起
	始条件。当 I2C 接口已经处于主模式中并发送或接收了数据时， I2C 接
	口会发送一个重复的起始条件。 STA 可在任何时候置位，当 I2C 接口处
	于可寻址的从模式时， STA 也可以置位。
4 STO 停止标志位。
	在主模式中， 当 STO 为 1 时，会使 I2C 接口发送一个停止条件或在从模
	式中从错误状态中恢复。当总线检测到停止条件时， STO 自动清零。
	在从模式中，置位 STO 位可从错误状态中恢复。这种情况下不向总线
	发送停止条件。硬件的表现就好像是接收到一个停止条件并切换到不
	可寻址的从接收模式。
STO 标志由硬件自动清零	
3 SI I2C 中断标志。
	当 I2C 状态改变时 SI 置位。但进入状态 F8 不会使 SI 置位。
	当 SI 置位时， SCL 线上的低电平串行时钟周期会被扩展，且串行传输
	被中止。当 SCL 为高时， SI 标志的状态不受影响。
	SI 必须通过软件复位。写“ 0”来复位 SI，写“ 1”不起作用。
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


	I2C 主发送模式 
	必须将I2CCON.ENS1置“ 1”来使能I2C模块。如果I2CCON.AA位复位，当另一个器件正变成总
线主机时， I2C模块将不会应答其自身的从机地址或通用调用地址， I2C接口就不能进入从机模式。
I2CCON寄存器的STA， STO和SI位必须复位。
此时，可通过置位I2CCON.STA位进入主发送模式。一旦总线空闲， I2C逻辑会马上测试I2C总线
并产生一个起始条件。

当发送起始条件时，串行中断标志（ SI）置位，状态寄存器（ I2CSTAT）中的状态代码为0x08。
中断服务程序利用该状态代码进入相应的状态服务程序，将从机地址和数据方向位（ SLA+W）装入I2CDAT。 
I2CCON的SI位必须在串行传输继续之前复位。
当发送完从机地址和方向位且接收到一个应答位时，串行中断标志（ SI）再次置位， I2STAT
中可能是一系列不同的状态代码。
主机模式下为0x18， 0x20或0x38。
每个状态代码对应的操作在下表中详细介绍。在发送完重复起始条件（状态0x10）后， 
I2C模块通过将SLA+R装入I2CDAT切换到主接收模式。



在主接收模式中，主机所接收的数据字节来自从发送器。按主发送模式中的方法初始化传输。
当发送完起始条件后，中断服务程序必须把7位从机地址和数据方向位（ SLA+R）装入I2CDAT。
必须先清除I2CCON中的SI位，再继续执行串行传输。
当发送完从机地址和数据方向位且接收到一个应答位时，串行中断标志SI再次置位，这时，
I2CSTAT中可能是一系列不同的状态代码。
主机模式下为0x40， 0x48或0x38，
每个状态代码对应的操作详见下表。在发送完重复起始条件（状态0x10）
后， I2C模块通过将SLA+W装入I2CDAT切换到主发送模式。

******************************************************************/
void interruptI2cHandler() interrupt Interrupt_I2c_Number
{
	//D_led_D2_REV();

	if(Master_Write_Data == gRegU_iic_wr)
	{// 0600:08 18 28 28 28 28
		//D_led_D3_REV();
		switch(I2CSTA)
		{
			//step 1 start
			case 0x08:// 已发送起始条件	
			//step 2 addr 
				L0_I2C_Write(s_task_i2c.pool.addr);
				gRegU_iic_return = 0x08;
				break;
			case 0x18://已发送 SLA+W 已接收 ACK
			//step 3 addr 1st data = reg 
				L0_I2C_Write(s_task_i2c.pool.reg);	   //send the addr
			    L0_i2c_NOSP();//I2C_Control(START_0,STOP_0,NoACK);			
				gRegU_iic_return = 0x18; 	
				break;
			case 0x20:// 已发送 SLA +W 已接收非 ACK
				L0_i2c_stop();//I2C_Control(START_0,STOP_1,NoACK); 
				break;
			case 0x28:// 已发送 I2CDAT中的数据;已接收 ACK
			//step 3 addr 2st data = data0..data1 
				if(s_task_i2c.pool.Txcnt >= s_task_i2c.pool.Txmax)					   //receive 10 datas and send the repeat start condition
				{ 
					L0_i2c_stop();///I2C_Control(START_0,STOP_1,NoACK);
					L0_i2c_end();
				}
				else
				{
					L0_I2C_Write(s_task_i2c.pool.Txbuf[s_task_i2c.pool.Txcnt]);
					s_task_i2c.pool.Txcnt ++;
					gRegU_iic_return = 0x28; 	
					L0_i2c_NOSP();//I2C_Control(START_0,STOP_0,NoACK); 
				}
				break;
			case 0x30://已发送 I2CDAT中的数据;
				L0_i2c_stop();//I2C_Control(START_0,STOP_1,NoACK); 
				L0_i2c_end();
				break;
			case 0x38://在 SLA+R/W或写数据字节时丢失仲裁
				L0_i2c_end();
				break;
			default:
				L0_i2c_stop();//I2C_Control(START_0,STOP_1,NoACK); 
				L0_i2c_end();
				gRegU_iic_return = I2CSTA;
				break;
		};

	}
	else
	{// read //0C00:08	18	28	10	40	50	50	50	50	50	50	58	000
	
		switch(I2CSTA)
		{
			//step 1 start
			case 0x08:// 已发送起始条件	
			//step 2 addr 
				L0_I2C_Write(s_task_i2c.pool.addr);
				break;
			case 0x18://已发送 SLA+W 已接收 ACK
			//step 3 addr 1st data = reg 
				L0_I2C_Write(s_task_i2c.pool.reg);	   //send the addr
			    L0_i2c_NOSP();//I2C_Control(START_0,STOP_0,NoACK);			 	
				break;
			case 0x28:// 已发送 I2CDAT中的数据;已接收 ACK
				L0_i2c_start();s_task_i2c.pool.Rxcnt = 0;
				break;
			case 0x10://已 发 送 重 复 起始条件	
				L0_I2C_Write(s_task_i2c.pool.addr|I2C_Read);			    //reverse to master receive mode 
				L0_i2c_NOSP();//I2C_Control(START_0,STOP_0,NoACK);	
				break;
			case 0x48:// 主接收 已 发 送 SLA+R 已接收非 ACK
				I2C_Control(START_1,STOP_1,NoACK);	 
				break;
			case 0x40:// 已发送 SLA+R 已接收 ACK		// 此处读取的值是addr|0x01 
			case 0x50://已 接 收 数 据 字节 ACK 已返回 
				s_task_i2c.pool.Rxbuf[s_task_i2c.pool.Rxcnt] = L0_I2C_Read();
				s_task_i2c.pool.Rxcnt ++;
				if(s_task_i2c.pool.Rxcnt >= s_task_i2c.pool.Rxmax)
				{
					L0_i2c_NOACK();
				}else
				{
					L0_i2c_ACK();
				}
				break;
			case 0x58://已 接 收 数 据 字节非 ACK 已返回 需要结束
			/// fixme: 总是多一个时钟数据 很奇怪
				s_task_i2c.pool.Rxbuf[s_task_i2c.pool.Rxcnt] = L0_I2C_Read();
				L0_i2c_stop();//I2C_Control(START_0,STOP_1,NoACK);
				L0_i2c_end();
				break;
			default:
				L0_i2c_stop();
				L0_i2c_end();
				gRegU_iic_return = I2CSTA;
				break;
		};
	}
	#ifdef D_iic_inspect
	
		s_task_i2c.status_buf[s_task_i2c.status_n] = I2CSTA;
		s_task_i2c.status_n++;
		if(s_task_i2c.status_n > 140)
		{
			s_task_i2c.status_n = 0;
			//s_task_i2c.status_buf[15] = 0xfe;
		}
	#endif //#ifdef D_iic_inspect
	I2C_Interrupt_Clean();	// SI写0 复位
}

	/********************************************************
	之前状态为 0x08 或 0x10 表示已发送从机地址和写操作位，并接收了应答。即将发
	送第一个数据字节和接收 ACK 位。
	a）将主发送缓冲区的第一个数据字节装入 I2CDAT；
	b）向 I2CCON 写入 0x04 来置位 AA 位；
	c）向 I2CCON 写入 !0x08 来清除 SI 标志；
	d）主发送缓冲区指针加 1；
	e）退出。
	*************************************************************/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Task>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


struct _s_task_i2c_ s_task_i2c;

void L2_task_i2c_init(void)
{
	s_task_i2c.pool.Txcnt = 0;
	s_task_i2c.pool.Rxcnt= 0;
	s_task_i2c.pool.Rxmax= 0;
	s_task_i2c.pool.Txmax= 0;
	s_task_i2c.pool.reg = 0;
	gRegU_iic_wr = 0;
	//	L1_i2c_Configure(1);	
	L0_i2c_end();
//	L1_task_init(&s_task_i2c.task);
//	L3_task_s_go(s_task_i2c,D_task_init);
}


#if 0
wirte: 
Master:	S---addr---W---*---reg---*---data1---*---data2---*---data3---*------P
Slave :	---------------A---------A-----------A-----------A-----------A--------
Isr   : 08-------------18--------28----------28----------28----------28-----
Txcnt :--------------------------3-----------2------------1----------0

read: 
Master:	S---addr---W---*---reg---*---S---addr---R---*----------A---------A---------A----------NA---P
Slave :	---------------A---------A------------------A---data1--*--data2--*--data3--*---data4--*----
Isr   : 08-------------18--------28----10-----------40----------50-------50--------50---
Rxcnt :-------------------------------------------------2------------1----------0

//L2_task_i2c_handdle(&s_task_i2c);
void L2_task_i2c_handdle(struct _s_task_i2c_ *s)
{

	switch(s->task.sh)
	{
		case D_task_init://
/*************************************
初始化程序
将 I2C 接口初始化用作从机和/或主机的例子。
a）将自身的从机地址装入 I2CADR，使能通用调用识别 I2CADR.GC（如果需要的话）；
b）使能 I2C 中断 AIE.I2CE；
c）向寄存器 I2CCON 写入 0x44 来置位 ENS1 和 AA 位，使能从机功能。对于主机功
能，可向寄存器 I2CCON 写入 0x40。
************************************/

		if(L0_uart0_SendIntFree())
		{
 			Lc_print_buf(" \r\niic ");
		//	L1_i2c_Configure();
			L2_task_go(0);
		//	L1_task_idelay(1*D_idelay_1s);	//大约6s 
		}
		break;
		case D_task_i2c_work:
			Lc_buf_copy_uc((char *)&s_task_i2c.pool,(char *)&s_task_i2c.bath,sizeof(s_task_i2c.pool));
			s_task_i2c.status = I2C_STATUS_START;
			L0_i2c_start();
			L2_i2c_debug_init();
			L3_tick_task_stamp();
 			//Lc_print_buf(" \r\nS ");
			L2_task_go(D_task_i2c_work_wait);
		break;
		case D_task_i2c_work_wait:
			if(I2C_STATUS_END == s_task_i2c.status)
			{
 				//Lc_print_buf("end");
				if(Master_Write_Data == s_task_i2c.pool.now_rw)
				{
					L0_uart0_uc('W');				
					L0_uart0_uchex(s_task_i2c.pool.Txcnt);
					L0_uart0_uchex(s_task_i2c.pool.Txbuf[0]);
				}
				else
				{
					L0_uart0_uc('R');				
					L0_uart0_uchex(s_task_i2c.pool.Rxcnt);
					L0_uart0_uchex(s_task_i2c.pool.Rxbuf[0]);
				}
				
				L2_task_go(D_task_i2c_end);
				//L1_task_idelay(D_idelay_300ms);
			}
			if(	L3_tick_task_interval(D_idelay_1s))
			{
 				Lc_print_buf("over");
				L2_task_go(D_task_i2c_end);
				//L1_task_idelay(D_idelay_300ms);
			}
		break;
		case D_task_i2c_end:
///S end
///T03 12 0B 13
///s09 08 18 28 10 40 50 50 50 58
///R03 13 1C 0C000000000
			L2_i2c_debug();
			L2_task_go(0);
			//L1_task_idelay(D_idelay_100ms);// fixme
		break;
		L2_task_switch_flag_idelay(1,'p');
	}
}

#endif

/// L1 no wait
/// 只可以写一个寄存器的数据
void L1n_i2c_write(U8 addr,U8 reg,U8 dat)
{
	if(L0_i2c_free())
	{
		L0_i2c_begin();	
		gRegU_iic_wr =  Master_Write_Data;
		s_task_i2c.pool.Txcnt =  0;
		s_task_i2c.pool.Txmax =  1;
		s_task_i2c.pool.addr =  addr;
		s_task_i2c.pool.reg =  reg;
		s_task_i2c.pool.Txbuf[0] = dat;
    	L0_i2c_start();
	}else
	{
		L0_uart0_uchex(gRegU_iic_return );
	}
}

//写一个数据平均消耗428us  4M频率 I2C_Baud_Select(I2C_BAUD_1DIVIDED64);		
// 4m时钟 I2C_BAUD_1DIVIDED64 clk周期17us 
/// 调用这个"无等待"函数会发现
void L1n_i2c_read(U8 addr,U8 reg,U8 num)
{
	if(L0_i2c_free())
	{
		L0_i2c_begin();
		gRegU_iic_wr =  Master_Read_Data;
		s_task_i2c.pool.Rxcnt =  0;
		s_task_i2c.pool.Rxmax=  num;
		s_task_i2c.pool.addr =  addr;
		s_task_i2c.pool.reg =  reg;
		L0_i2c_start();
	}else
	{
		L0_uart0_uchex(gRegU_iic_return);
	}
}
/// cw63 或者 msa300等i2c外设的读取 工作顺序 
/// step 1 收到中断 
/// step 2 启动 i2c外设的任务handdle的读取 指令后, 
/// step 4 在外设任务handdle中 等待任务结束
/// step 5 任务结束后 设置相应的全局标志位提供给系统使用,或者直接调用简单函数,实现某种功能
/// step 6 外设任务handdle恢复成空闲

void L1n_cw63_read(U8 addr,U8 reg)
{
	//L1n_i2c_read(D_i2c_addr_cw63xx,D_CW63X_REG_LDO1);
	

}

///  addr reg and the number which need to read
//num = 3  R addr+r,data1[reg[,data2[reg+1]
//写一个数据平均消耗428us  4M频率 I2C_Baud_Select(I2C_BAUD_1DIVIDED64);		
// 4m时钟 I2C_BAUD_1DIVIDED64 clk周期17us 
void L2_i2c_read(U8 addr,U8 reg,U8 num)
{
	L0_i2c_begin();
	gRegU_iic_wr =  Master_Read_Data;
	s_task_i2c.pool.Rxcnt =  0;
	s_task_i2c.pool.Rxmax=  num;
	s_task_i2c.pool.addr =  addr;
	s_task_i2c.pool.reg =  reg;
	L2_tick_stamp();	
	L0_i2c_start();
	//L2_i2c_debug_init();
	while(L0_i2c_busy())
	{
		if(	L3_tick_interval(3*D_idelay_10ms))
		{
			//Lc_print("\r\ni2cR %d,%d %d",(int)addr,(int)reg,(int)gRegU_iic_return);
			L0_uart0_uc('e');
			L0_uart0_uchex(gRegU_iic_return);
			break;
		}
	}
	L0_i2c_end();
	L1_i2c_Configure(0);
	L0_uart0_uc('R');
	for(s_task_i2c.pool.Rxcnt = 1;s_task_i2c.pool.Rxcnt <= num;s_task_i2c.pool.Rxcnt ++)
	{
		L0_uart0_uchex(s_task_i2c.pool.Rxbuf[s_task_i2c.pool.Rxcnt]);
	}
}
/// 只可以在单任务执行时调用

//写一个数据平均消耗428us  4M频率 I2C_Baud_Select(I2C_BAUD_1DIVIDED64);		
// 4m时钟 I2C_BAUD_1DIVIDED64 clk周期17us 
void L2_i2c_write(U8 addr,U8 reg,U8 dat)
{
	L0_i2c_begin();
	gRegU_iic_wr =  Master_Write_Data;
	s_task_i2c.pool.Txcnt =  0;
	s_task_i2c.pool.Txmax =  1;
	s_task_i2c.pool.addr =  addr;
	s_task_i2c.pool.reg =  reg;
	s_task_i2c.pool.Txbuf[0] = dat;
	L2_tick_stamp();			
	L0_i2c_start();
	//L2_i2c_debug_init();
	while(L0_i2c_busy())
	{
		if(	L3_tick_interval(3*D_idelay_10ms))
		{
			//Lc_print("\r\ni2cW %x,%x,%x erro",addr,reg,dat);
			L0_uart0_uc('e');
			L0_uart0_uchex(gRegU_iic_return);
			break;
		}
	}
	L0_i2c_end();
	L1_i2c_Configure(0);
	L0_uart0_uc('w');
	L0_uart0_uchex(dat);
	//L2_i2c_debug();
}




//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Task<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/***************************

void L3_i2c_read(void)
{
	if(L2_task_free(s_task_i2c))
	{
				s_task_i2c.bath.now_rw =  Master_Read_Data;
				s_task_i2c.bath.Rxcnt =  0;
		L3_task_s_go(s_task_i2c,D_task_i2c_work);
	}
}

void L3_i2c_write(void)
{
	if(L2_task_free(s_task_i2c))
	{
				s_task_i2c.bath.now_rw =  Master_Write_Data;
				s_task_i2c.bath.Txcnt =  0;
		L3_task_s_go(s_task_i2c,D_task_i2c_work);
	}
}



*****/

/*************************************
启动主机发送功能
通过建立缓冲区、指针和数据计数然后发启起始条件便可执行主发送操作。
a）初始化主机数据计数器；
b）建立数据将被发送到的从机地址，并且添加写位；
c）向 I2CCON 写入 0x20 来置位 STA 位；
d）在主发送缓冲区内建立要发送的数据；
e）初始化主机数据计数器来匹配正在发送的信息长度；
f）退出。

************************************/

/*************************************
通过建立缓冲区、指针和数据计数然后发启起始条件便可执行主接收操作。
a）初始化主机数据计数器；
b）建立数据将被发送到的从机地址，并且添加读位；
c）向 I2CCON 写入 0x20 来置位 STA 位；
d）在主接收缓冲区内建立要发送的数据；
e）初始化主机数据计数器来匹配正在发送的信息长度；
f）退出。

************************************/



