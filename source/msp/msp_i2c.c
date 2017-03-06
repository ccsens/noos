//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, ���ؿƼ�
/// All rights reserved.  
///  
/// @file            main.c
/// @brief           main app  
///  
///�����ļ�ʵ�ֵĹ��ܵ�������  
///  
/// @version 1.1      CCsens technology 
/// @author           CC 
/// @date             20150102
///  
///  
///     �޶�˵��������汾
/// Modified by:			
/// Modified date:	
/// Version:
/// Descriptions:	CC-PWR-VH01-m02.sch
//////////////////////////////////////////////////////////////////////////

//20160413 CC-ACC-VH02 




/// ������һ���������������ĺ�����ע��˵����������   
///     
///      ����д�ú�����������Ϣ     
///      @param a �����Եı�����param����������     
///      @param s ָ������������Ϣ���ַ���     
///      @return     ���Խ����return��������ֵ��   
///      @see     Test()     ���������ο���������صĺ�����������һ�����ӣ�  
///      @note     (note������Ҫע�������) 




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
		//step 1: ϵͳʱ��ѡ��
		//step 2: ʹ�� I2C �ж� AIE.I2CE�������ж�ʹ�ܼĴ���(AIE)
					//  1 I2CE I2C �ж�ʹ���ź�
					//  1�� I2C �ж�ʹ��
					//  0�� I2C �жϽ�ֹ
		//step 3: IE0��������λ ȫ���ж�
		//step 4: �ܽ�����
		//step 5: iic ���������� 
		//step 6: iic ����������
		//step 7: iic ģ��ʹ��
		
		 System_Peripheralmodules3ClockEnable(ENABLE,I2C_CLKEN); //open the i2c clock

		 interrupt2Configure(ENABLE,Interrupt_AIE_i2cE_Msk);	 //open the interrupt of i2c
		 //interrupt1Configure(ENABLE,Interrupt_IE0_EA_Msk);/// ȫ���ж�
		// P10 SCL
		// p11 SDA
	///P10_SEL2,P10_SEL1:
	///00: P10 �����ó� GPIO
	///01: P10 �����ó� I2C SCL �˿�
	///10: P10 �����óɸ�Ƶʱ�� X32K ����˿�
	///11: P10 �����óɼ����� Timer1 ���ſ�����
		BITN_0(P1_SEL2,BITN0);	BITN_1(P1_SEL1,BITN0);
		BITN_0(P1_SEL2,BITN1);	BITN_1(P1_SEL1,BITN1);

	///Px_PE  �˿�Px ��������ʹ�ܼĴ���
	///0 Px0_PE �˿� Px0 ��������ʹ���ź�
	///0������������
	///1�����ڲ���������
	//	BITN_1(P1_PE,BITN0|BITN1);		///1�����ڲ��������� ����ⲿ���ӵ�������
		BITN_1(P1_OD,BITN0|BITN1);		///1�����Ϊ��©(Open Drain)���

	///bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0 ��ַ ��ʼֵ ���� ֧�ֶ˿�
	///P0_DIR 0x0AC 11111111
	///R/W
	///P07--P00

	///1 PxDIR �˿� Px1 ����������üĴ���
	///1�����ó�����
	///0�����ó����
		BITN_0(P1_DIR,BITN0|BITN1);		///����Ϊ��� �����û����
	//	BITN_1(P1,BITN0|BITN1);				///
	//	BITN_1(P1_DS,BITN0|BITN1);			///��ǿ��
		
		////	 P1_DIR &= 	~(BIT0 |BIT1);	
		//I2C_Baud_Select(I2C_BAUD_1DIVIDED960);		// 4mʱ�� I2C_BAUD_1DIVIDED960 clk����120usx2
		I2C_Baud_Select(I2C_BAUD_1DIVIDED64);		// 4mʱ�� I2C_BAUD_1DIVIDED64 clk����18us
		//I2C_Baud_Select(I2C_BAUD_1DIVIDED90);		// 4mʱ�� I2C_BAUD_1DIVIDED64 clk����18us

		I2C_Baud_Counter_Run();		 
		I2C_Moudle_Enable();                //i2c part enable 			
		L2_i2c_debug_init();
//		L0_uart0_uc('A');
		//Lc_delay_ms(400);
		
	}else
	{
		BITN_0(PERI_CLK2,I2C_CLKEN); ///close the i2c clock
		BITN_0(AIE,Interrupt_AIE_i2cE_Msk);// close the interrupt of i2c
		 //interrupt1Configure(ENABLE,Interrupt_IE0_EA_Msk);/// ȫ���ж�
		// P10 SCL
		// p11 SDA
	///P10_SEL2,P10_SEL1:
	///00: P10 �����ó� GPIO
		BITN_0(P1_SEL2,BITN0);	BITN_0(P1_SEL1,BITN0);
		BITN_0(P1_SEL2,BITN1);	BITN_0(P1_SEL1,BITN1);

	///Px_PE  �˿�Px ��������ʹ�ܼĴ���
	///0 Px0_PE �˿� Px0 ��������ʹ���ź�
	///0������������
	///1�����ڲ���������
	//	BITN_1(P1_PE,BITN0|BITN1);		///1�����ڲ��������� ����ⲿ���ӵ�������
		BITN_0(P1_OD,BITN0|BITN1);		///1�����Ϊ��©(Open Drain)���

	///bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0 ��ַ ��ʼֵ ���� ֧�ֶ˿�
	///P0_DIR 0x0AC 11111111
	///R/W
	///P07--P00

	///1 PxDIR �˿� Px1 ����������üĴ���
	///1�����ó�����
	///0�����ó����
		BITN_1(P1_DIR,BITN0|BITN1);		///���ó�����  
	//	BITN_1(P1,BITN0|BITN1);				///
	//	BITN_1(P1_DS,BITN0|BITN1);			///��ǿ��

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

6 ENS1 I2C �ӿ�ʹ�ܡ�
	�� ENS1 �á� 1��ʱ��ʹ�� I2C �ӿڡ�
5 STA ��ʼ��־λ��
	�� STA=1 ʱ�� I2C �ӿڽ�����ģʽ������һ����ʼ����������Ѿ�����
	��ģʽ������һ���ظ���ʼ������
	�� STA=1 ���� I2C �ӿڻ�û������ģʽʱ�� I2C �ӿڽ�����ģʽ�����
	���߲������߿���ʱ����һ����ʼ�������������æ����ȴ�һ��ͣ
	ֹ�������ͷ����ߣ������ӳٰ���ڲ�ʱ�ӷ��������ں���һ����
	ʼ�������� I2C �ӿ��Ѿ�������ģʽ�в����ͻ����������ʱ�� I2C ��
	�ڻᷢ��һ���ظ�����ʼ������ STA �����κ�ʱ����λ���� I2C �ӿڴ�
	�ڿ�Ѱַ�Ĵ�ģʽʱ�� STA Ҳ������λ��
4 STO ֹͣ��־λ��
	����ģʽ�У� �� STO Ϊ 1 ʱ����ʹ I2C �ӿڷ���һ��ֹͣ�������ڴ�ģ
	ʽ�дӴ���״̬�лָ��������߼�⵽ֹͣ����ʱ�� STO �Զ����㡣
	�ڴ�ģʽ�У���λ STO λ�ɴӴ���״̬�лָ�����������²�������
	����ֹͣ������Ӳ���ı��־ͺ����ǽ��յ�һ��ֹͣ�������л�����
	��Ѱַ�Ĵӽ���ģʽ��
STO ��־��Ӳ���Զ�����	
3 SI I2C �жϱ�־��
	�� I2C ״̬�ı�ʱ SI ��λ��������״̬ F8 ����ʹ SI ��λ��
	�� SI ��λʱ�� SCL ���ϵĵ͵�ƽ����ʱ�����ڻᱻ��չ���Ҵ��д���
	����ֹ���� SCL Ϊ��ʱ�� SI ��־��״̬����Ӱ�졣
	SI ����ͨ�������λ��д�� 0������λ SI��д�� 1���������á�
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


	I2C ������ģʽ 
	���뽫I2CCON.ENS1�á� 1����ʹ��I2Cģ�顣���I2CCON.AAλ��λ������һ�������������
������ʱ�� I2Cģ�齫����Ӧ��������Ĵӻ���ַ��ͨ�õ��õ�ַ�� I2C�ӿھͲ��ܽ���ӻ�ģʽ��
I2CCON�Ĵ�����STA�� STO��SIλ���븴λ��
��ʱ����ͨ����λI2CCON.STAλ����������ģʽ��һ�����߿��У� I2C�߼������ϲ���I2C����
������һ����ʼ������

��������ʼ����ʱ�������жϱ�־�� SI����λ��״̬�Ĵ����� I2CSTAT���е�״̬����Ϊ0x08��
�жϷ���������ø�״̬���������Ӧ��״̬������򣬽��ӻ���ַ�����ݷ���λ�� SLA+W��װ��I2CDAT�� 
I2CCON��SIλ�����ڴ��д������֮ǰ��λ��
��������ӻ���ַ�ͷ���λ�ҽ��յ�һ��Ӧ��λʱ�������жϱ�־�� SI���ٴ���λ�� I2STAT
�п�����һϵ�в�ͬ��״̬���롣
����ģʽ��Ϊ0x18�� 0x20��0x38��
ÿ��״̬�����Ӧ�Ĳ������±�����ϸ���ܡ��ڷ������ظ���ʼ������״̬0x10���� 
I2Cģ��ͨ����SLA+Rװ��I2CDAT�л���������ģʽ��



��������ģʽ�У����������յ������ֽ����Դӷ���������������ģʽ�еķ�����ʼ�����䡣
����������ʼ�������жϷ����������7λ�ӻ���ַ�����ݷ���λ�� SLA+R��װ��I2CDAT��
���������I2CCON�е�SIλ���ټ���ִ�д��д��䡣
��������ӻ���ַ�����ݷ���λ�ҽ��յ�һ��Ӧ��λʱ�������жϱ�־SI�ٴ���λ����ʱ��
I2CSTAT�п�����һϵ�в�ͬ��״̬���롣
����ģʽ��Ϊ0x40�� 0x48��0x38��
ÿ��״̬�����Ӧ�Ĳ�������±��ڷ������ظ���ʼ������״̬0x10��
�� I2Cģ��ͨ����SLA+Wװ��I2CDAT�л���������ģʽ��

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
			case 0x08:// �ѷ�����ʼ����	
			//step 2 addr 
				L0_I2C_Write(s_task_i2c.pool.addr);
				gRegU_iic_return = 0x08;
				break;
			case 0x18://�ѷ��� SLA+W �ѽ��� ACK
			//step 3 addr 1st data = reg 
				L0_I2C_Write(s_task_i2c.pool.reg);	   //send the addr
			    L0_i2c_NOSP();//I2C_Control(START_0,STOP_0,NoACK);			
				gRegU_iic_return = 0x18; 	
				break;
			case 0x20:// �ѷ��� SLA +W �ѽ��շ� ACK
				L0_i2c_stop();//I2C_Control(START_0,STOP_1,NoACK); 
				break;
			case 0x28:// �ѷ��� I2CDAT�е�����;�ѽ��� ACK
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
			case 0x30://�ѷ��� I2CDAT�е�����;
				L0_i2c_stop();//I2C_Control(START_0,STOP_1,NoACK); 
				L0_i2c_end();
				break;
			case 0x38://�� SLA+R/W��д�����ֽ�ʱ��ʧ�ٲ�
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
			case 0x08:// �ѷ�����ʼ����	
			//step 2 addr 
				L0_I2C_Write(s_task_i2c.pool.addr);
				break;
			case 0x18://�ѷ��� SLA+W �ѽ��� ACK
			//step 3 addr 1st data = reg 
				L0_I2C_Write(s_task_i2c.pool.reg);	   //send the addr
			    L0_i2c_NOSP();//I2C_Control(START_0,STOP_0,NoACK);			 	
				break;
			case 0x28:// �ѷ��� I2CDAT�е�����;�ѽ��� ACK
				L0_i2c_start();s_task_i2c.pool.Rxcnt = 0;
				break;
			case 0x10://�� �� �� �� �� ��ʼ����	
				L0_I2C_Write(s_task_i2c.pool.addr|I2C_Read);			    //reverse to master receive mode 
				L0_i2c_NOSP();//I2C_Control(START_0,STOP_0,NoACK);	
				break;
			case 0x48:// ������ �� �� �� SLA+R �ѽ��շ� ACK
				I2C_Control(START_1,STOP_1,NoACK);	 
				break;
			case 0x40:// �ѷ��� SLA+R �ѽ��� ACK		// �˴���ȡ��ֵ��addr|0x01 
			case 0x50://�� �� �� �� �� �ֽ� ACK �ѷ��� 
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
			case 0x58://�� �� �� �� �� �ֽڷ� ACK �ѷ��� ��Ҫ����
			/// fixme: ���Ƕ�һ��ʱ������ �����
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
	I2C_Interrupt_Clean();	// SIд0 ��λ
}

	/********************************************************
	֮ǰ״̬Ϊ 0x08 �� 0x10 ��ʾ�ѷ��ʹӻ���ַ��д����λ����������Ӧ�𡣼�����
	�͵�һ�������ֽںͽ��� ACK λ��
	a���������ͻ������ĵ�һ�������ֽ�װ�� I2CDAT��
	b���� I2CCON д�� 0x04 ����λ AA λ��
	c���� I2CCON д�� !0x08 ����� SI ��־��
	d�������ͻ�����ָ��� 1��
	e���˳���
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
��ʼ������
�� I2C �ӿڳ�ʼ�������ӻ���/�����������ӡ�
a��������Ĵӻ���ַװ�� I2CADR��ʹ��ͨ�õ���ʶ�� I2CADR.GC�������Ҫ�Ļ�����
b��ʹ�� I2C �ж� AIE.I2CE��
c����Ĵ��� I2CCON д�� 0x44 ����λ ENS1 �� AA λ��ʹ�ܴӻ����ܡ�����������
�ܣ�����Ĵ��� I2CCON д�� 0x40��
************************************/

		if(L0_uart0_SendIntFree())
		{
 			Lc_print_buf(" \r\niic ");
		//	L1_i2c_Configure();
			L2_task_go(0);
		//	L1_task_idelay(1*D_idelay_1s);	//��Լ6s 
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
/// ֻ����дһ���Ĵ���������
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

//дһ������ƽ������428us  4MƵ�� I2C_Baud_Select(I2C_BAUD_1DIVIDED64);		
// 4mʱ�� I2C_BAUD_1DIVIDED64 clk����17us 
/// �������"�޵ȴ�"�����ᷢ��
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
/// cw63 ���� msa300��i2c����Ķ�ȡ ����˳�� 
/// step 1 �յ��ж� 
/// step 2 ���� i2c���������handdle�Ķ�ȡ ָ���, 
/// step 4 ����������handdle�� �ȴ��������
/// step 5 ��������� ������Ӧ��ȫ�ֱ�־λ�ṩ��ϵͳʹ��,����ֱ�ӵ��ü򵥺���,ʵ��ĳ�ֹ���
/// step 6 ��������handdle�ָ��ɿ���

void L1n_cw63_read(U8 addr,U8 reg)
{
	//L1n_i2c_read(D_i2c_addr_cw63xx,D_CW63X_REG_LDO1);
	

}

///  addr reg and the number which need to read
//num = 3  R addr+r,data1[reg[,data2[reg+1]
//дһ������ƽ������428us  4MƵ�� I2C_Baud_Select(I2C_BAUD_1DIVIDED64);		
// 4mʱ�� I2C_BAUD_1DIVIDED64 clk����17us 
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
/// ֻ�����ڵ�����ִ��ʱ����

//дһ������ƽ������428us  4MƵ�� I2C_Baud_Select(I2C_BAUD_1DIVIDED64);		
// 4mʱ�� I2C_BAUD_1DIVIDED64 clk����17us 
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
�����������͹���
ͨ��������������ָ������ݼ���Ȼ������ʼ�������ִ�������Ͳ�����
a����ʼ���������ݼ�������
b���������ݽ������͵��Ĵӻ���ַ���������дλ��
c���� I2CCON д�� 0x20 ����λ STA λ��
d���������ͻ������ڽ���Ҫ���͵����ݣ�
e����ʼ���������ݼ�������ƥ�����ڷ��͵���Ϣ���ȣ�
f���˳���

************************************/

/*************************************
ͨ��������������ָ������ݼ���Ȼ������ʼ�������ִ�������ղ�����
a����ʼ���������ݼ�������
b���������ݽ������͵��Ĵӻ���ַ��������Ӷ�λ��
c���� I2CCON д�� 0x20 ����λ STA λ��
d���������ջ������ڽ���Ҫ���͵����ݣ�
e����ʼ���������ݼ�������ƥ�����ڷ��͵���Ϣ���ȣ�
f���˳���

************************************/



