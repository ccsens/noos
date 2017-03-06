//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, ���ؿƼ�
/// All rights reserved.  
///  
/// @file            4802_reg_user2.h
/// @brief        ����ĺ궨�� ��251reg��ͻ��ǰ�����d���� 
///  
///  ������оƬ����鶨��
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
/// Descriptions:	
//////////////////////////////////////////////////////////////////////////

#ifndef __SHC16L_macro_H__
#define __SHC16L_macro_H__	
#include "SHC16L.h"
#include "../clib/bit.h"
#include "../clib/Type.h"



sbit P07   = P0^7;
sbit P06   = P0^6;
sbit P05   = P0^5;
sbit P04   = P0^4;
sbit P03   = P0^3;
sbit P02   = P0^2;
sbit P01   = P0^1;
sbit P00   = P0^0;



sbit P17   = P1^7;
sbit P16   = P1^6;
sbit P15   = P1^5;
sbit P14   = P1^4;
sbit P13   = P1^3;
sbit P12   = P1^2;
sbit P11   = P1^1;
sbit P10   = P1^0;




sbit P27   = P2^7;
sbit P26   = P2^6;
sbit P25   = P2^5;
sbit P24   = P2^4;
sbit P23   = P2^3;
sbit P22   = P2^2;
sbit P21   = P2^1;
sbit P20   = P2^0;



sbit P37   = P3^7;
sbit P36   = P3^6;
sbit P35   = P3^5;
sbit P34   = P3^4;
sbit P33   = P3^3;
sbit P32   = P3^2;
sbit P31   = P3^1;
sbit P30   = P3^0;




sbit P47   = P4^7;
sbit P46   = P4^6;
sbit P45   = P4^5;
sbit P44   = P4^4;
sbit P43   = P4^3;
sbit P42   = P4^2;
sbit P41   = P4^1;
sbit P40   = P4^0;





sbit P57   = P5^7;
sbit P56   = P5^6;
sbit P55   = P5^5;
sbit P54   = P5^4;
sbit P53   = P5^3;
sbit P52   = P5^2;
sbit P51   = P5^1;
sbit P50   = P5^0;




sbit P67   = P6^7;
sbit P66   = P6^6;
sbit P65   = P6^5;
sbit P64   = P6^4;
sbit P63   = P6^3;
sbit P62   = P6^2;
sbit P61   = P6^1;
sbit P60   = P6^0;

                  
sbit P77   = P7^7;
sbit P76   = P7^6;
sbit P75   = P7^5;
sbit P74   = P7^4;
sbit P73   = P7^3;
sbit P72   = P7^2;
sbit P71   = P7^1;
sbit P70   = P7^0;             


                  
sbit P87   = P8^7;
sbit P86   = P8^6;
sbit P85   = P8^5;
sbit P84   = P8^4;
sbit P83   = P8^3;
sbit P82   = P8^2;
sbit P81   = P8^1;
sbit P80   = P8^0;



/*************************************************
����Ҫ���Ե�IP
*************************************************/
#define		START	 0X00
#define		CLK	 	 0X01
//#define 	LCD		 0X10
#define		RTC		 0X11
#define		TIMER	 0X20
#define		PCA		 0X21
#define		SPI		 0X30
//#define	UART	 0X31
#define		I2C		 0X70
#define		I2CA	 0X71
#define		WDT		 0X80
#define		GPIO	 0X90


/*************************************************
�ж�ʹ��
*************************************************/
//AIE
#define		RTCE	BIT6						 //RTC�ж�
#define		ADCE	BIT5						 //ADC�ж�
#define		VCE		BIT4						 //VC�ж�
#define		LVD		BIT3						 //LVD�ж�
#define		ISOE	BIT2						 //7816�ж�
#define		I2CE	BIT1						 //I2C�ж�
#define		PTE		BIT0						 //�˿��ж�

#define		AIE_RTCE	BITN6						 //RTC�ж�
#define		AIE_ADCE	BITN5						 //ADC�ж�
#define		AIE_VCE		BITN4						 //VC�ж�
#define		AIE_LVD		BITN3						 //LVD�ж�
#define		AIE_ISOE	BITN2						 //7816�ж�
#define		AIE_I2CE	BITN1						 //I2C�ж�
#define		AIE_PTE		BITN0						 //�˿��ж�

/*************************************************
SYS
*************************************************/
//LPM
#define 	LPMIN	LPM|=0X01;LPM|=0X02			 //����͹���ģʽ

//PCON
#define		IDLE	BIT0
#define		IDLEIN	PCON |= IDLE				 //�������ģʽ

/*************************************************
CLK
*************************************************/
//CLKC
#define		LCDCLK		BIT7					 //LCDʱ��ѡ��
#define		LCDCLKX32	CLKC &= ~LCDCLK			 //�ⲿ
#define		LCDCLKIRC	CLKC |= LCDCLK			 //�ڲ�

#define		WDTCLK		BIT6					 //WDTʱ��ѡ��
#define		WDTCLKX32	CLKC &= ~WDTCLK			 //�ⲿ
#define		WDTCLKIRC	CLKC |= WDTCLK			 //�ڲ�

#define		RTCCLK		BIT5					 //RTCʱ��ѡ��
#define		RTCCLKX32	CLKC &= ~RTCCLK			 //�ⲿ
#define		RTCCLKIRC	CLKC |= RTCCLK			 //�ڲ�

#define		SYSDS1		BIT4					 //ϵͳʱ�Ӵ���Ƶʱ�ӷ�Ƶѡ��1
#define 	SYSDS0		BIT3					 //ϵͳʱ�Ӵ���Ƶʱ�ӷ�Ƶѡ��0
#define 	SYSDS_0		0x00					 //ϵͳʱ��Ϊ��Ƶʱ��
#define 	SYSDS_1		SYSDS0					 //ϵͳʱ��Ϊ��Ƶʱ��2��Ƶ
#define 	SYSDS_2		SYSDS1					 //ϵͳʱ��Ϊ��Ƶʱ��4��Ƶ
#define 	SYSDS_3		SYSDS0 + SYSDS1		 	 //ϵͳʱ��Ϊ��Ƶʱ��8��Ƶ

#define		X32KEN		BIT2					 //�ⲿ32Kʹ��

#define		IRCEN		BIT1					 //�ڲ�RCʹ��

#define		SYSCLK		BIT0					 //ϵͳʱ��ѡ��

//CLKC1
#define 	CLKFS1		BIT7					 //��Ƶʱ��Ƶ��ѡ��1
#define 	CLKFS0		BIT6					 //��Ƶʱ��Ƶ��ѡ��0
#define		CLKF_2M		0X00					 //��Ƶʱ��Ƶ��2M
#define		CLKF_4M		CLKFS0					 //��Ƶʱ��Ƶ��4M
#define		CLKF_8M		CLKFS1					 //��Ƶʱ��Ƶ��8M
#define		CLKF_16M	CLKFS0 + CLKFS1			 //��Ƶʱ��Ƶ��16M

//CLKC2
#define		X32STB		BIT7					 //�ⲿ32K�ȶ���־λ
#define		IRCSTB		BIT6					 //�ڲ�16M�ȶ���־λ

//PERICLK0

/*************
#define VC_CLKEN	BITN4
#define LVD_CLKEN	BITN3
#define BGR_CLKEN	BITN2
#define ADC_CLKEN	BITN1
#define LCD_CLKEN	BITN0

#define		VCCLKEN		BIT4					 //��Χģ��ʱ������
#define		LVDCLKEN	BIT3		
#define		BGRCLKEN	BIT2
#define		ADCCLKEN	BIT1
#define		LCDCLKEN	BIT0
4 VC_CLKEN ��ѹ�Ƚ���ʱ��ʹ��
1����ѹ�Ƚ�����ʱ������
0����ѹ�Ƚ�����ʱ������
3 LVD_CLKEN �͵�ѹ�����ʱ��ʹ��
1���͵�ѹ�������ʱ������
0���͵�ѹ�������ʱ������
2 BGR_CLKEN BGR ʱ��ʹ�ܣ� BGR �����ڲ��ο���ѹ������ ADC�� VC�� LVD
1�� BGR ��ʱ������
0�� BGR ��ʱ������
1 ADC_CLKEN ADC ʱ��ʹ��
1�� ADC ��ʱ������
0�� ADC ��ʱ������
0 LCD_CLKEN LCD ʱ��ʹ��
1�� LCD ��ʱ������
0�� LCD ��ʱ������
*************/


//PERICLK1  
/************************
#define		SPI_CLKEN	BITN6                                       
#define		DES_CLKEN	BITN5                                       
#define		RNG_CLKEN	BITN4					 //��Χģ��ʱ������
#define		CRC_CLKEN	BITN3		                               
#define		DMA_CLKEN	BITN2                                       
#define		RTC_CLKEN	BITN1                                       
#define		FLASH_CLKEN	BITN0     
#define		SPICLKEN	BIT6
#define		DESCLKEN	BIT5
#define		RNGCLKEN	BIT4					 //��Χģ��ʱ������
#define		CRCCLKEN	BIT3		
#define		DMACLKEN	BIT2
#define		RTCCLKEN	BIT1
#define		FLASHCLKEN	BIT0
6 SPI_CLKEN SPI ʱ��ʹ��
1�� SPI ��ʱ������
0�� SPI ��ʱ������
5 DES_CLKEN DES ʱ��ʹ��
1�� DES ��ʱ������
0�� DES ��ʱ������
4 RNG_CLKEN RNG ʱ��ʹ��
1�� RNG ��ʱ������
0�� RNG ��ʱ������
3 CRC_CLKEN CRC ʱ��ʹ��
1�� CRC ��ʱ������
0�� CRC ��ʱ������
2 DMA_CLKEN DMA ʱ��ʹ��
1�� DMA ��ʱ������
0�� DMA ��ʱ������
1 RTC_CLKEN ʵʱʱ��ʱ��ʹ��
1��ʵʱʱ����ʱ������
0��ʵʱʱ����ʱ������
0 Flash_CLKEN Flash ʱ��ʹ��
1�� Flash ��ʱ������
0�� Flash ��ʱ������
ע�����
������ Flash ���ƼĴ���ʱ����Ҫ Flash ʱ��ʹ�ܣ������ڶ�ģ
ʽ�£� Flash ʱ��ʹ�ܿ��Թرա�
*************/
//PERICLK2                     
/******

#define		X7816_CLKEN	BITN7
#define		I2C_CLKEN		BITN6
#define		UART0_CLKEN	BITN5
#define		UART1_CLKEN	BITN4					 //��Χģ��ʱ������
#define		TIMER_CLKEN	BITN3		
#define		PCA_CLKEN		BITN2
#define		WDT_CLKEN		BITN1
#define		PORT_CLKEN		BITN0           


7 7816_CLKEN 7816 ʱ��ʹ��
1�� 7816 ��ʱ������
0�� 7816 ��ʱ������
6 I2C_CLKEN I2C ʱ��ʹ��
1�� I2C ��ʱ������
0�� I2C ��ʱ������
5 UART0_CLKEN UART0 ʱ��ʹ��
1�� UART0 ��ʱ������
0�� UART0 ��ʱ������
4 UART1_CLKEN UART1 ʱ��ʹ��
1�� UART1 ��ʱ������
0�� UART1 ��ʱ������
3 Timer_CLKEN ��ʱ��ʱ��ʹ��
1����ʱ����ʱ������
0����ʱ����ʱ������
ע�����
Timer_CLKEN ������ 4 ��������ģ�飨��ʱ�� 0 - ��ʱ�� 3��
2 PCA_CLKEN PCA ʱ��ʹ��
1�� PCA ��ʱ������
0�� PCA ��ʱ������
1 WDT_CLKEN WDT ʱ��ʹ��
1�� WDT ��ʱ������
0�� WDT ��ʱ������
0 PORT_CLKEN �˿�ʱ��ʹ��
1���˿���ʱ������
0���˿���ʱ������
******/
/*************************************************
LCD
*************************************************/
//LCDRC0
#define 	LCDDUTY1	BIT7					 //LCDDUTYģʽ
#define 	LCDDUTY0	BIT6
#define		LCDDUTY_1	0X00				     //LCD��̬��ʾģʽ
#define		LCDDUTY_2	LCDDUTY0				 //LCD1/2������ʾ
#define		LCDDUTY_3	LCDDUTY1				 //LCD1/3������ʾ
#define		LCDDUTY_4	LCDDUTY0 + LCDDUTY1		 //LCD1/4������ʾ

#define		LCDBIAS		BIT5					 //LCDƫѹģʽ
#define		LCDBIAS_2	LCDBIAS					 //LCD1/2ƫѹ			  	
#define		LCDBIAS_3	0X00					 //LCD1/3ƫѹ

#define		LCDFRQ1		BIT4				     //LCD��ɱ�ʱ��Ƶ��ѡ��
#define		LCDFRQ0		BIT3
#define		LCDFRQ_2K  	0X00					 //LCD��ɱ�ʱ��Ƶ��ѡ��2K
#define		LCDFRQ_4K	LCDFRQ0					 //LCD��ɱ�ʱ��Ƶ��ѡ��4K
#define		LCDFRQ_8K	LCDFRQ1					 //LCD��ɱ�ʱ��Ƶ��ѡ��8K
#define		LCDFRQ_16K	LCDFRQ0 + LCDFRQ1		 //LCD��ɱ�ʱ��Ƶ��ѡ��16K


#define 	LCDFRA1		BIT2					 //LCD֡ˢ��Ƶ��ѡ��
#define		LCDFRA0		BIT1
#define		LCDFRA_64	0X00					 //Ĭ��
#define		LCDFRA_128	LCDFRA0					 //128/4 = 32K
#define		LCDFRA_256	LCDFRA1					 //
#define		LCDFRA_512	LCDFRA0 + LCDFRA1		 //

#define 	LCDEN		BIT0					 //LCDʹ��

//LCDRC1
#define		LCDBUF1		BIT6					 //LCD��������ѡ��
#define		LCDBUF0		BIT5
#define		LCDBUF_0	0X00					 //�������Ƽ�ֵ��	
#define		LCDBUF_1	LCDBUF0					 //	 ~
#define		LCDBUF_2	LCDBUF1					 //	 ~
#define		LCDBUF_3	LCDBUF0 + LCDBUF1		 //��ǿ

#define		LCDCPEN		BIT0					 //LCD��ɱ�ʹ��
/*************************************************
UART
*************************************************/
//SCON SCON1
#define		UXSM0		BIT7					 //���ڹ���ģʽλѡ��
#define		UXSM1		BIT6
#define		UXSM_0		0X00					 //���ڹ���ģʽ0 ��λ�Ĵ���
#define     UXSM_1		UXSM1					 //���ڹ���ģʽ1 8λ���� �����ʿɵ�
#define		UXSM_2		UXSM0					 //���ڹ���ģʽ2 9λ���� CLK/32 CLK/64
#define		UXSM_3		UXSM0 + UXSM1			 //���ڹ���ģʽ3 9λ���� �����ʿɵ�

#define		UXSM2		BIT5					 //�༶ͨ�ż���ַƥ��
#define     UXREN		BIT4			    	 //��������ģʽ
#define		UXTB8		BIT3				     //ģʽ2��3�µĵ�9λ����											 		
#define		UXRB8		BIT2				 	 //ģʽ2��3�½��յĵ�9λ����

//SCON
#define		U0TI		BIT1					 //UART0 ���ͱ�־
#define		U0RI		BIT0					 //UART0 ���ձ�־

//SCON1
#define		U1TI		BIT1					 //UART1 ���ͱ�־
#define		U1RI		BIT0					 //UART1 ���ձ�־

//U0_TMR U1_TMR
#define		UXTMR		BIT0				 	 //����UART�����ʷ�����

//PCON
#define		U0BRD		BIT7				 	 //U0�����ʷ���
#define		U0FE7		BIT6				     //U0SM0����ѡ�� 1:FE(֡������)		 
#define		U1BRD		BIT3				 	 //U1�����ʷ���				
#define		U1FE7		BIT2					 //U1SM0����ѡ�� 1:FE(֡������)

//�����ʼ�����ֵ
#define		BPS9600		243

/*************************************************
TIMER
*************************************************/
//TMOD
#define 	T1GATE		BIT7	  				 //T1�ſ�
#define 	T1CT		BIT6					 //T1������ʱѡ��
												 //0��ʱ ��Ƶ1/12
												 //1���� ��P1.1��P2.1 �½��ؼ�����

#define 	T1MS1		BIT5					 //T1������ʽ
#define 	T1MS0		BIT4
#define		T1MS_0		0X00					 //��ʽ0 13λ������ʱ��
#define		T1MS_1		T1MS0					 //��ʽ1 16λ������ʱ��
#define		T1MS_2		T1MS1					 //��ʽ2 8λ�Զ���װ��
#define		T1MS_3		T1MS0 + T1MS1			 //��ʱ��1ֹͣ����

#define 	T0GATE		BIT3					 //T0�ſ�
#define 	T0CT		BIT2					 //T0������ʱѡ��
												 //0��ʱ ��Ƶ1/12
												 //1���� ��P1.1��P2.1 �½��ؼ�����

#define 	T0MS1		BIT1					 //T0������ʽ
#define 	T0MS0		BIT0
#define		T0MS_0		0X00					 //��ʽ0 13λ������ʱ��
#define		T0MS_1		T0MS0					 //��ʽ1 16λ������ʱ��
#define		T0MS_2		T0MS1					 //��ʽ2 8λ�Զ���װ��
#define		T0MS_3		T0MS0 + T0MS1			 //��ʽ3 ����8λ��ʱ������

//TCON2
#define		T3MS		BIT3					 //��ʽ0 16λ������ʱ��  ��ʽ1 8λ�Զ���װ��					 
#define		T2MS		BIT1

/*************************************************
PCA
*************************************************/
//CCON
#define		dCR			BIT6					 //PCA����
#define		dCCF4		BIT4					 //������4�жϱ�־
#define		dCCF3		BIT3					 //������3�жϱ�־
#define		dCCF2		BIT2					 //������2�жϱ�־	
#define		dCCF1		BIT1					 //������1�жϱ�־
#define		dCCF0		BIT0					 //������0�жϱ�־


//CMOD
#define		CWDT		BIT6					 //PCA���Ź�����ʹ��

#define		CCPS0		BIT1					 //PCAʱ������ѡ��
#define		CCPS1		BIT2					 //
#define		CCPS_0		0X00					 //PCAʱ������ ϵͳʱ��12��Ƶ	
#define		CCPS_1		CCPS0					 //PCAʱ������ ϵͳʱ��4��Ƶ
#define		CCPS_2		CCPS1					 //PCAʱ������ TIMER0���
#define		CCPS_3		CCPS0 + CCPS1			 //PCAʱ������ �ⲿ����ECI�����ϵͳʱ��8��Ƶ��
#define		EPCA		BIT0					 //PCA������ʱ�ж�ʹ��

//CCAPMX
#define		ECOM		BIT6					 //����ȽϹ��ܣ��������������WDT,PWM,����������ܣ�
#define		CAPP		BIT5					 //���������ز���
#define		CAPN		BIT4					 //�����½��ز���
#define		CAPPN		CAPP + CAPN				 //�������½��ض�����
#define		CMAT		BIT3					 //����ƥ�����λ
#define		CTOG		BIT2					 //�������ģʽ �������ŷ�ת
#define		CPWM		BIT1					 //PWMģʽ ����������ΪPWM���
#define		ECCF		BIT0					 //PCA�Ƚϲ����ж�ʹ��	

/*************************************************
I2C
*************************************************/
//I2CADR
#define 	I2CGC		BIT0					 //�Ƿ���Ӧͨ�õ��õ�ַ

//I2CSTAT

//I2CCON
#define		I2CENS		BIT6					 //I2C�ӿ�ʹ��
#define		I2CSTR		BIT5					 //��ʼ��־λ
#define		I2CSTO		BIT4					 //ֹͣ��־λ
#define		I2CSI		BIT3					 //I2C�жϱ�־
#define		I2CAA		BIT2					 //Ӧ���־λ

//I2C������
#define 	I2CCR2		BIT7
#define		I2CCR1		BIT1
#define		I2CCR0		BIT0

#define		I2CBPS_256	 0X00
#define		I2CBPS_224	 I2CCR0
#define		I2CBPS_198	 I2CCR1
#define		I2CBPS_170	 I2CCR1 + I2CCR0
#define		I2CBPS_960	 I2CCR2
#define		I2CBPS_150	 I2CCR2 + I2CCR0
#define		I2CBPS_90	 I2CCR2 + I2CCR1
#define		I2CBPS_BLK	 I2CCR2 + I2CCR1 +I2CCR0 //����timer������ֵ����BPS
//I2CTM
//I2CTMR
/*************************************************
SPI
*************************************************/
//SPICTR
#define		SPIFCLR		BIT2					 //��λ��λ��FIFO���
#define		SPIM1		BIT1					 //����ģʽ����1
#define		SPIM0		BIT0					 //����ģʽ����0
#define		SPIM_NO		0X00					 //SPI��ֹ
#define		SPIM_S		SPIM0					 //SPI����ģʽ
#define		SPIM_R		SPIM1					 //SPI����ģʽ
#define		SPIM_SR		SPIM0 + SPIM1			 //SPIȫ˫��

//SPICON
#define		SPIMASTER	BIT7					 //SPI�������ã���λΪMASTER ��λΪSLAVE	

#define		SPIFLEN2	BIT6					 //֡���ݳ��ȿ���  ֻ��MASTER����Ч
#define		SPIFLEN1	BIT5
#define		SPIFLEN0	BIT4
#define		SPIFLEN_4	SPIFLEN0 + SPIFLEN1
#define		SPIFLEN_5	SPIFLEN2
#define		SPIFLEN_6	SPIFLEN2 + SPIFLEN0
#define		SPIFLEN_7	SPIFLEN2 + SPIFLEN1
#define		SPIFLEN_8	SPIFLEN2 + SPIFLEN1 + SPIFLEN0 
												 
#define		SPICPHA1	BIT3					 //ʱ����ѡ��
#define		SPICPHA0	BIT2
#define		SPICPHA_0   0X00					 //������ ż����
#define		SPICPHA_1  	SPICPHA0				 //ż���� ������
#define		SPICPHA_2   SPICPHA1				 //������ ������
#define		SPICPHA_3	SPICPHA0 + SPICPHA1		 //ż���� ż����

#define		SPICPOL		BIT1					 //ͬ��ʱ�Ӽ���

#define		SPILSBF		BIT0					 //�ȴ�����λ 1��λ�ȴ� 0��λ�ȴ�

//SPILEN
//SPIBPS
//SPISTA1
#define		SPIRFNE		BIT3
#define		SPISFNF		BIT2
#define		SPIREND		BIT1
#define		SPISEND		BIT0

//SPISTA2
#define		SPISOV		BIT5
#define		SPIROV		BIT4
#define		SPIAERR		BIT3
#define		SPIQERR		BIT2
#define		SPITRDY		BIT1
#define		SPIRRDY		BIT0

/*****************************************************************
************************** struct and enum**********************  
*****************************************************************/
typedef struct SPI_Para
{
	U8 SPI_MODE_SE:1;
	U8 SPI_FRAME_LEN_SE:3;
	U8 SPI_CPHA_SE:2;
	U8 SPI_CPOL_SE:1;
	U8 SPI_LSBF_SE:1;
	//unsigned char spi_Buad_Para;
}SPI_Para;

typedef enum SPI_MODE
{
	SPI_SLAVE_MODE,
	SPI_MASTER_MODE,
	SPI_MAX_MODE
}SPI_MODE;

typedef enum SPI_FRAME_LEN
{
	SPI_FRAME_LEN_8BIT,
	SPI_FRAME_LEN_4BIT = 0x03,
	SPI_FRAME_LEN_5BIT,
	SPI_FRAME_LEN_6BIT,
	SPI_FRAME_LEN_7BIT,
	SPI_FRAME_LEN_MAX
}SPI_FRAME_LEN; 

typedef enum SPI_CPHA
{
	SPI_SCK_ODD_RV_EVN_SED,
	SPI_SCK_EVN_RV_ODD_SED,
	SPI_SCK_ODD_RV_ODD_SED,
	SPI_SCK_EVN_RV_EVN_SED,
	SPI_SCK_MAX	
}SPI_CPHA;

typedef enum SPI_CPOL
{
	SPI_SCK_LOW_IN_IDLE,
	SPI_SCK_HIGH_IN_IDLE,
	SPI_CPOL_MAX	
}SPI_CPOL;

typedef enum SPI_LSBF
{
	SPI_HIGH_BIT_FIRST,
	SPI_LOW_BIT_FIRST,
	SPI_BIT_MAX	
}SPI_LSBF;

typedef enum
{
	TRASFER_FORBID,
	SEND_MODE,
	RECEIVE_MODE,
	SEND_AND_RECEIVE_MODE,
	SPI_WORK_MAX
}SPI_WORK_MODE;

/*****************simple function********************************/
#define SPI_CONFIG_Master_Pos 7
#define SPI_CONFIG_Master_Msk (U8)(0x01<<SPI_CONFIG_Master_Pos)

#define SPI_CONFIG_Frame_Len_Pos 4
#define SPI_CONFIG_Frame_Len_Msk (U8)(0x07<<SPI_CONFIG_Frame_Len_Pos)

#define SPI_CONFIG_CPHA_Pos 2 
#define SPI_CONFIG_CPHA_Msk (U8)(0x03<<SPI_CONFIG_CPHA_Pos)

#define SPI_CONFIG_CPOL_Pos 1
#define SPI_CONFIG_CPOL_Msk (U8)(0x01<<SPI_CONFIG_CPOL_Pos)

#define SPI_CONFIG_LSBF_Pos 0
#define SPI_CONFIG_LSBF_Msk (U8)(0x01<<SPI_CONFIG_LSBF_Pos)

#define SPI_CTRL_MODE_Pos 0
#define SPI_CTRL_MODE_Msk (U8)(0x03<<SPI_CTRL_MODE_Pos)

#define SPI_CTRL_FIFO_CLR_Pos 2
#define SPI_CTRL_FIFO_CLR_Msk (U8)(0x01<<SPI_CTRL_FIFO_CLR_Pos)

#define SPI_Work_Mode_Select(a) (SPI_CTRL = (SPI_CTRL & ~SPI_CTRL_MODE_Msk) | (a<<SPI_CTRL_MODE_Pos))
#define Clean_Fifo() SPI_CTRL &= (~SPI_CTRL_FIFO_CLR_Msk)

#define IsSendFifoFull()  ((SPI_STATUS1&0x04) == 0x04)


#define IsSendDataEnd() ((SPI_STATUS1 & 0x01) == 0x01)
#define IsReceiveFifoEmpty() (((SPI_STATUS1&0x08) == 0x08))

#define IsReceiveDataEnd() ((SPI_STATUS1 & 0x02) == 0x02)

/*************************************************
WDT
*************************************************/
//WDTRST
#define		WDTEAT		WDTRST = 0X1E;WDTRST = 0XE1	

//WDTCON
#define		WDTWOV2		BIT2
#define		WDTWOV1		BIT1
#define		WDTWOV0		BIT0		

#define		WDT_250MS	0X00
#define		WDT_500MS	WDTWOV0
#define		WDT_1S		WDTWOV1
#define		WDT_2S		WDTWOV0 + WDTWOV1
#define		WDT_4S		WDTWOV2
#define		WDT_8S		WDTWOV2	+ WDTWOV0
#define		WDT_16S		WDTWOV2 + WDTWOV1
#define		WDT_32S		WDTWOV2 + WDTWOV1 + WDTWOV0

/***********************************************************************************
ADC
*************************************************************************************/
/**********************
7:5 OPT[2:0] BGR ����ѡ��
4 BGR_Auto BGR �͹����Զ��ر�����
1�� BGR �ڽ���͹���ģʽʱ���Զ��رգ�����ģʽʱ�Զ�������
0�� BGR ������ BGR_EN ����.
3:1 -- ����λ
0 BGR_EN BGR ʹ��λ
1�� BGR ʹ��
0�� BGR �ر�
**********************/

#define	BGR_Auto 	BITN4
#define	BGR_EN 		BITN0












/// must include type
//define p0.n out or in      
//#define D_P0_OUT(N)		BIT_1(LPC_GPIO0->FIODIR ,N)
//#define D_P0_IN(N)		BIT_0(LPC_GPIO0->FIODIR ,N)
#define D_P0_OFF(N)		BIT_0(P0 ,N)
#define D_P0_ON(N)		BIT_1(P0,N)
#define D_P0_AT(N)		BIT_G(P0,N)

#define D_P07_REV()		P07 = ~P07
#define D_P06_REV()		P06 = ~P06
#define D_P05_REV()		P05 = ~P05
#define D_P04_REV()		P04 = ~P04
#define D_P03_REV()		P03 = ~P03
#define D_P02_REV()		P02 = ~P02
#define D_P01_REV()		P01 = ~P01
#define D_P00_REV()		P00 = ~P00
            
#define D_P17_REV()		P17 = ~P17
#define D_P16_REV()		P16 = ~P16
#define D_P15_REV()		P15 = ~P15
#define D_P14_REV()		P14 = ~P14
#define D_P13_REV()		P13 = ~P13
#define D_P12_REV()		P12 = ~P12
#define D_P11_REV()		P11 = ~P11
#define D_P10_REV()		P10 = ~P10


// 	7654		3210
/// PORT SEL    
#define D_P15_S2_0			0X00
#define D_P15_S2_SPI_CS	0X00
#define D_P15_S2_7816RST	BIT5
#define D_P15_S2_PCA3		BIT5
#define D_P15_S1_0			0X00
#define D_P15_S1_SPI_CS	BIT5
#define D_P15_S1_7816RST	0X00
#define D_P15_S1_PCA3		BIT5


#define D_P14_S2_0	        0X00
#define D_P14_S2_SPI_CLK	0X00
#define D_P14_S2_MASTERCLK	BIT4
#define D_P14_S2_PCA2		BIT4
#define D_P14_S1_0	        0X00
#define D_P14_S1_SPI_CLK	BIT4
#define D_P14_S1_MASTERCLK	0X00
#define D_P14_S1_PCA2		BIT4

#define D_P13_S2_0			0X00
#define D_P13_S2_SPI_MOSI	0X00
#define D_P13_S2_RTCOUT1	BIT3
#define D_P13_S2_PCA1		BIT3
#define D_P13_S1_0			0X00
#define D_P13_S1_SPI_MOSI	BIT3
#define D_P13_S1_RTCOUT1	0X00
#define D_P13_S1_PCA1		BIT3


#define D_P12_S2_0	        0X00
#define D_P12_S2_SPI_MISO	0X00
#define D_P12_S2_RTCOUT0	BIT2
#define D_P12_S2_PCAIN		BIT2
#define D_P12_S1_0	        0X00
#define D_P12_S1_SPI_MISO	BIT2
#define D_P12_S1_RTCOUT0	0X00
#define D_P12_S1_PCAIN		BIT2


#define D_P27_REV()		P27 = ~P27
#define D_P26_REV()		P26 = ~P26
#define D_P25_REV()		P25 = ~P25
#define D_P24_REV()		P24 = ~P24
#define D_P23_REV()		P23 = ~P23
#define D_P22_REV()		P22 = ~P22
#define D_P21_REV()		P21 = ~P21
#define D_P20_REV()		P20 = ~P20  

#define D_P37_REV()		P37 = ~P37
#define D_P36_REV()		P36 = ~P36
#define D_P35_REV()		P35 = ~P35
#define D_P34_REV()		P34 = ~P34
#define D_P33_REV()		P33 = ~P33
#define D_P32_REV()		P32 = ~P32
#define D_P31_REV()		P31 = ~P31
#define D_P30_REV()		P30 = ~P30  

#define D_P47_REV()		P47 = ~P47
#define D_P46_REV()		P46 = ~P46
#define D_P45_REV()		P45 = ~P45
#define D_P44_REV()		P44 = ~P44
#define D_P43_REV()		P43 = ~P43
#define D_P42_REV()		P42 = ~P42
#define D_P41_REV()		P41 = ~P41
#define D_P40_REV()		P40 = ~P40  

#define D_P57_REV()		P57 = ~P57
#define D_P56_REV()		P56 = ~P56
#define D_P55_REV()		P55 = ~P55
#define D_P54_REV()		P54 = ~P54
#define D_P53_REV()		P53 = ~P53
#define D_P52_REV()		P52 = ~P52
#define D_P51_REV()		P51 = ~P51
#define D_P50_REV()		P50 = ~P50  

#define D_P67_REV()		P67 = ~P67
#define D_P66_REV()		P66 = ~P66
#define D_P65_REV()		P65 = ~P65
#define D_P64_REV()		P64 = ~P64
#define D_P63_REV()		P63 = ~P63
#define D_P62_REV()		P62 = ~P62
#define D_P61_REV()		P61 = ~P61
#define D_P60_REV()		P60 = ~P60  





#define D_led_P20_REV()      D_P20_REV()
#define D_led_P20_ONF(x)       P20 = x
#define D_led_P20_init()	   P20 = 1;\
							BITN_0(P2_PE,  BITN0);\
							BITN_0(P2_OD,  BITN0);\
							BITN_0(P2_DS,  BITN0);\
							BITN_0(P2_DIR, BITN0);\
							BITN_0(P2_SEL2,BITN0);\
							BITN_0(P2_SEL1,BITN0);\
							BITN_0(P2_SEL0,BITN0);\
							 P20 = 1;

#define D_led_P21_REV()      D_P21_REV()
#define D_led_P21_ONF(x)       P21 = x
#define D_led_P21_init()	   P21 = 1;\
							BITN_0(P2_PE,  BITN1);\
							BITN_0(P2_OD,  BITN1);\
							BITN_0(P2_DS,  BITN1);\
							BITN_0(P2_DIR, BITN1);\
							BITN_0(P2_SEL2,BITN1);\
							BITN_0(P2_SEL1,BITN1);\
							BITN_0(P2_SEL0,BITN1);\
							 P21 = 1;


#define D_led_P22_REV()      D_P22_REV()
#define D_led_P22_ONF(x)       P22 = x
#define D_led_P22_init()	   P22 = 1;\
							BITN_0(P2_PE,  BITN2);\
							BITN_0(P2_OD,  BITN2);\
							BITN_0(P2_DS,  BITN2);\
							BITN_0(P2_DIR, BITN2);\
							BITN_0(P2_SEL2,BITN2);\
							BITN_0(P2_SEL1,BITN2);\
							BITN_0(P2_SEL0,BITN2);\
							 P22 = 1;

#define D_led_P23_REV()     D_P23_REV()
#define D_led_P23_ONF(x)      P23 = x
#define D_led_P23_init()	  P23 = 1;\
							BITN_0(P2_PE,  BITN3);\
							BITN_0(P2_OD,  BITN3);\
							BITN_0(P2_DS,  BITN3);\
							BITN_0(P2_DIR, BITN3);\
							BITN_0(P2_SEL2,BITN3);\
							BITN_0(P2_SEL1,BITN3);\
							BITN_0(P2_SEL0,BITN3);\
							 P23 = 1;

#define D_led_P24_REV()      D_P24_REV()
#define D_led_P24_ONF(x)       P24 = x
#define D_led_P24_init()       P24 = 1;\
							BITN_0(P2_PE,  BITN4);\
							BITN_0(P2_OD,  BITN4);\
							BITN_0(P2_DS,  BITN4);\
							BITN_0(P2_DIR, BITN4);\
							BITN_0(P2_SEL2,BITN4);\
							BITN_0(P2_SEL1,BITN4);\
							BITN_0(P2_SEL0,BITN4);\
							 P24 = 1;

#define D_led_P25_REV()      D_P25_REV()
#define D_led_P25_ONF(x)       P25 = x
#define D_led_P25_init()       P25 = 1;\
							BITN_0(P2_PE,  BITN5);\
							BITN_0(P2_OD,  BITN5);\
							BITN_1(P2_DS,  BITN5);\
							BITN_0(P2_DIR, BITN5);\
							BITN_0(P2_SEL2,BITN5);\
							BITN_0(P2_SEL1,BITN5);\
							BITN_0(P2_SEL0,BITN5);\
							 P25 = 1;

#define D_led_P26_REV()      D_P26_REV()
#define D_led_P26_ONF(x)       P26 = x
#define D_led_P26_init()       P26 = 1;\
							BITN_0(P2_PE,  BITN6);\
							BITN_0(P2_OD,  BITN6);\
							BITN_0(P2_DS,  BITN6);\
							BITN_0(P2_DIR, BITN6);\
							BITN_0(P2_SEL2,BITN6);\
							BITN_0(P2_SEL1,BITN6);\
							BITN_0(P2_SEL0,BITN6);\
							 P26 = 1;

#define D_led_P27_REV()      D_P27_REV()
#define D_led_P27_ONF(x)       P27 = x
#define D_led_P27_init()       P27 = 1;\
							BITN_0(P2_PE,  BITN7);\
							BITN_0(P2_OD,  BITN7);\
							BITN_0(P2_DS,  BITN7);\
							BITN_0(P2_DIR, BITN7);\
							BITN_0(P2_SEL2,BITN7);\
							BITN_0(P2_SEL1,BITN7);\
							BITN_0(P2_SEL0,BITN7);\
							 P27 = 1;






/*****************************************************************
ע�������ʹ�� 32pin оƬʱ����Ҫ��δʹ�õ� GPIO ͨ���˿ڼĴ�������Ϊ�ڲ�����ģʽ��
����͵�ƽģʽ���Է�ֹ©��

****************************************************************/
#endif	///#ifndef __4802REG2_H__		

