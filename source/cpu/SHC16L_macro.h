//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            4802_reg_user2.h
/// @brief        补充的宏定义 和251reg冲突的前面添加d避免 
///  
///  必须结合芯片规格书定义
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
加载要测试的IP
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
中断使能
*************************************************/
//AIE
#define		RTCE	BIT6						 //RTC中断
#define		ADCE	BIT5						 //ADC中断
#define		VCE		BIT4						 //VC中断
#define		LVD		BIT3						 //LVD中断
#define		ISOE	BIT2						 //7816中断
#define		I2CE	BIT1						 //I2C中断
#define		PTE		BIT0						 //端口中断

#define		AIE_RTCE	BITN6						 //RTC中断
#define		AIE_ADCE	BITN5						 //ADC中断
#define		AIE_VCE		BITN4						 //VC中断
#define		AIE_LVD		BITN3						 //LVD中断
#define		AIE_ISOE	BITN2						 //7816中断
#define		AIE_I2CE	BITN1						 //I2C中断
#define		AIE_PTE		BITN0						 //端口中断

/*************************************************
SYS
*************************************************/
//LPM
#define 	LPMIN	LPM|=0X01;LPM|=0X02			 //进入低功耗模式

//PCON
#define		IDLE	BIT0
#define		IDLEIN	PCON |= IDLE				 //进入空闲模式

/*************************************************
CLK
*************************************************/
//CLKC
#define		LCDCLK		BIT7					 //LCD时钟选择
#define		LCDCLKX32	CLKC &= ~LCDCLK			 //外部
#define		LCDCLKIRC	CLKC |= LCDCLK			 //内部

#define		WDTCLK		BIT6					 //WDT时钟选择
#define		WDTCLKX32	CLKC &= ~WDTCLK			 //外部
#define		WDTCLKIRC	CLKC |= WDTCLK			 //内部

#define		RTCCLK		BIT5					 //RTC时钟选择
#define		RTCCLKX32	CLKC &= ~RTCCLK			 //外部
#define		RTCCLKIRC	CLKC |= RTCCLK			 //内部

#define		SYSDS1		BIT4					 //系统时钟从主频时钟分频选择1
#define 	SYSDS0		BIT3					 //系统时钟从主频时钟分频选择0
#define 	SYSDS_0		0x00					 //系统时钟为主频时钟
#define 	SYSDS_1		SYSDS0					 //系统时钟为主频时钟2分频
#define 	SYSDS_2		SYSDS1					 //系统时钟为主频时钟4分频
#define 	SYSDS_3		SYSDS0 + SYSDS1		 	 //系统时钟为主频时钟8分频

#define		X32KEN		BIT2					 //外部32K使能

#define		IRCEN		BIT1					 //内部RC使能

#define		SYSCLK		BIT0					 //系统时钟选择

//CLKC1
#define 	CLKFS1		BIT7					 //主频时钟频率选择1
#define 	CLKFS0		BIT6					 //主频时钟频率选择0
#define		CLKF_2M		0X00					 //主频时钟频率2M
#define		CLKF_4M		CLKFS0					 //主频时钟频率4M
#define		CLKF_8M		CLKFS1					 //主频时钟频率8M
#define		CLKF_16M	CLKFS0 + CLKFS1			 //主频时钟频率16M

//CLKC2
#define		X32STB		BIT7					 //外部32K稳定标志位
#define		IRCSTB		BIT6					 //内部16M稳定标志位

//PERICLK0

/*************
#define VC_CLKEN	BITN4
#define LVD_CLKEN	BITN3
#define BGR_CLKEN	BITN2
#define ADC_CLKEN	BITN1
#define LCD_CLKEN	BITN0

#define		VCCLKEN		BIT4					 //外围模块时钟允许
#define		LVDCLKEN	BIT3		
#define		BGRCLKEN	BIT2
#define		ADCCLKEN	BIT1
#define		LCDCLKEN	BIT0
4 VC_CLKEN 电压比较器时钟使能
1：电压比较器有时钟输入
0：电压比较器无时钟输入
3 LVD_CLKEN 低电压侦测器时钟使能
1：低电压侦测器有时钟输入
0：低电压侦测器无时钟输入
2 BGR_CLKEN BGR 时钟使能， BGR 产生内部参考电压，供给 ADC， VC， LVD
1： BGR 有时钟输入
0： BGR 无时钟输入
1 ADC_CLKEN ADC 时钟使能
1： ADC 有时钟输入
0： ADC 无时钟输入
0 LCD_CLKEN LCD 时钟使能
1： LCD 有时钟输入
0： LCD 无时钟输入
*************/


//PERICLK1  
/************************
#define		SPI_CLKEN	BITN6                                       
#define		DES_CLKEN	BITN5                                       
#define		RNG_CLKEN	BITN4					 //外围模块时钟允许
#define		CRC_CLKEN	BITN3		                               
#define		DMA_CLKEN	BITN2                                       
#define		RTC_CLKEN	BITN1                                       
#define		FLASH_CLKEN	BITN0     
#define		SPICLKEN	BIT6
#define		DESCLKEN	BIT5
#define		RNGCLKEN	BIT4					 //外围模块时钟允许
#define		CRCCLKEN	BIT3		
#define		DMACLKEN	BIT2
#define		RTCCLKEN	BIT1
#define		FLASHCLKEN	BIT0
6 SPI_CLKEN SPI 时钟使能
1： SPI 有时钟输入
0： SPI 无时钟输入
5 DES_CLKEN DES 时钟使能
1： DES 有时钟输入
0： DES 无时钟输入
4 RNG_CLKEN RNG 时钟使能
1： RNG 有时钟输入
0： RNG 无时钟输入
3 CRC_CLKEN CRC 时钟使能
1： CRC 有时钟输入
0： CRC 无时钟输入
2 DMA_CLKEN DMA 时钟使能
1： DMA 有时钟输入
0： DMA 无时钟输入
1 RTC_CLKEN 实时时钟时钟使能
1：实时时钟有时钟输入
0：实时时钟无时钟输入
0 Flash_CLKEN Flash 时钟使能
1： Flash 有时钟输入
0： Flash 无时钟输入
注意事项：
在配置 Flash 控制寄存器时才需要 Flash 时钟使能，其余在读模
式下， Flash 时钟使能可以关闭。
*************/
//PERICLK2                     
/******

#define		X7816_CLKEN	BITN7
#define		I2C_CLKEN		BITN6
#define		UART0_CLKEN	BITN5
#define		UART1_CLKEN	BITN4					 //外围模块时钟允许
#define		TIMER_CLKEN	BITN3		
#define		PCA_CLKEN		BITN2
#define		WDT_CLKEN		BITN1
#define		PORT_CLKEN		BITN0           


7 7816_CLKEN 7816 时钟使能
1： 7816 有时钟输入
0： 7816 无时钟输入
6 I2C_CLKEN I2C 时钟使能
1： I2C 有时钟输入
0： I2C 无时钟输入
5 UART0_CLKEN UART0 时钟使能
1： UART0 有时钟输入
0： UART0 无时钟输入
4 UART1_CLKEN UART1 时钟使能
1： UART1 有时钟输入
0： UART1 无时钟输入
3 Timer_CLKEN 定时器时钟使能
1：定时器有时钟输入
0：定时器无时钟输入
注意事项：
Timer_CLKEN 控制了 4 个计数器模块（定时器 0 - 定时器 3）
2 PCA_CLKEN PCA 时钟使能
1： PCA 有时钟输入
0： PCA 无时钟输入
1 WDT_CLKEN WDT 时钟使能
1： WDT 有时钟输入
0： WDT 无时钟输入
0 PORT_CLKEN 端口时钟使能
1：端口有时钟输入
0：端口无时钟输入
******/
/*************************************************
LCD
*************************************************/
//LCDRC0
#define 	LCDDUTY1	BIT7					 //LCDDUTY模式
#define 	LCDDUTY0	BIT6
#define		LCDDUTY_1	0X00				     //LCD静态显示模式
#define		LCDDUTY_2	LCDDUTY0				 //LCD1/2段码显示
#define		LCDDUTY_3	LCDDUTY1				 //LCD1/3段码显示
#define		LCDDUTY_4	LCDDUTY0 + LCDDUTY1		 //LCD1/4段码显示

#define		LCDBIAS		BIT5					 //LCD偏压模式
#define		LCDBIAS_2	LCDBIAS					 //LCD1/2偏压			  	
#define		LCDBIAS_3	0X00					 //LCD1/3偏压

#define		LCDFRQ1		BIT4				     //LCD电荷泵时钟频率选择
#define		LCDFRQ0		BIT3
#define		LCDFRQ_2K  	0X00					 //LCD电荷泵时钟频率选择2K
#define		LCDFRQ_4K	LCDFRQ0					 //LCD电荷泵时钟频率选择4K
#define		LCDFRQ_8K	LCDFRQ1					 //LCD电荷泵时钟频率选择8K
#define		LCDFRQ_16K	LCDFRQ0 + LCDFRQ1		 //LCD电荷泵时钟频率选择16K


#define 	LCDFRA1		BIT2					 //LCD帧刷新频率选择
#define		LCDFRA0		BIT1
#define		LCDFRA_64	0X00					 //默认
#define		LCDFRA_128	LCDFRA0					 //128/4 = 32K
#define		LCDFRA_256	LCDFRA1					 //
#define		LCDFRA_512	LCDFRA0 + LCDFRA1		 //

#define 	LCDEN		BIT0					 //LCD使能

//LCDRC1
#define		LCDBUF1		BIT6					 //LCD驱动能力选择
#define		LCDBUF0		BIT5
#define		LCDBUF_0	0X00					 //最弱（推荐值）	
#define		LCDBUF_1	LCDBUF0					 //	 ~
#define		LCDBUF_2	LCDBUF1					 //	 ~
#define		LCDBUF_3	LCDBUF0 + LCDBUF1		 //最强

#define		LCDCPEN		BIT0					 //LCD电荷泵使能
/*************************************************
UART
*************************************************/
//SCON SCON1
#define		UXSM0		BIT7					 //串口工作模式位选择
#define		UXSM1		BIT6
#define		UXSM_0		0X00					 //串口工作模式0 移位寄存器
#define     UXSM_1		UXSM1					 //串口工作模式1 8位传输 波特率可调
#define		UXSM_2		UXSM0					 //串口工作模式2 9位传输 CLK/32 CLK/64
#define		UXSM_3		UXSM0 + UXSM1			 //串口工作模式3 9位传输 波特率可调

#define		UXSM2		BIT5					 //多级通信及地址匹配
#define     UXREN		BIT4			    	 //启动接收模式
#define		UXTB8		BIT3				     //模式2或3下的第9位数据											 		
#define		UXRB8		BIT2				 	 //模式2或3下接收的第9位数据

//SCON
#define		U0TI		BIT1					 //UART0 发送标志
#define		U0RI		BIT0					 //UART0 接收标志

//SCON1
#define		U1TI		BIT1					 //UART1 发送标志
#define		U1RI		BIT0					 //UART1 接收标志

//U0_TMR U1_TMR
#define		UXTMR		BIT0				 	 //启动UART波特率发生器

//PCON
#define		U0BRD		BIT7				 	 //U0波特率翻倍
#define		U0FE7		BIT6				     //U0SM0功能选择 1:FE(帧错误检测)		 
#define		U1BRD		BIT3				 	 //U1波特率翻倍				
#define		U1FE7		BIT2					 //U1SM0功能选择 1:FE(帧错误检测)

//波特率计数初值
#define		BPS9600		243

/*************************************************
TIMER
*************************************************/
//TMOD
#define 	T1GATE		BIT7	  				 //T1门控
#define 	T1CT		BIT6					 //T1计数定时选择
												 //0定时 主频1/12
												 //1计数 （P1.1或P2.1 下降沿计数）

#define 	T1MS1		BIT5					 //T1工作方式
#define 	T1MS0		BIT4
#define		T1MS_0		0X00					 //方式0 13位计数定时器
#define		T1MS_1		T1MS0					 //方式1 16位计数定时器
#define		T1MS_2		T1MS1					 //方式2 8位自动重装载
#define		T1MS_3		T1MS0 + T1MS1			 //定时器1停止运行

#define 	T0GATE		BIT3					 //T0门控
#define 	T0CT		BIT2					 //T0计数定时选择
												 //0定时 主频1/12
												 //1计数 （P1.1或P2.1 下降沿计数）

#define 	T0MS1		BIT1					 //T0工作方式
#define 	T0MS0		BIT0
#define		T0MS_0		0X00					 //方式0 13位计数定时器
#define		T0MS_1		T0MS0					 //方式1 16位计数定时器
#define		T0MS_2		T0MS1					 //方式2 8位自动重装载
#define		T0MS_3		T0MS0 + T0MS1			 //方式3 两个8位定时计数器

//TCON2
#define		T3MS		BIT3					 //方式0 16位计数定时器  方式1 8位自动重装载					 
#define		T2MS		BIT1

/*************************************************
PCA
*************************************************/
//CCON
#define		dCR			BIT6					 //PCA启动
#define		dCCF4		BIT4					 //捕获器4中断标志
#define		dCCF3		BIT3					 //捕获器3中断标志
#define		dCCF2		BIT2					 //捕获器2中断标志	
#define		dCCF1		BIT1					 //捕获器1中断标志
#define		dCCF0		BIT0					 //捕获器0中断标志


//CMOD
#define		CWDT		BIT6					 //PCA看门狗功能使能

#define		CCPS0		BIT1					 //PCA时钟输入选择
#define		CCPS1		BIT2					 //
#define		CCPS_0		0X00					 //PCA时钟输入 系统时钟12分频	
#define		CCPS_1		CCPS0					 //PCA时钟输入 系统时钟4分频
#define		CCPS_2		CCPS1					 //PCA时钟输入 TIMER0溢出
#define		CCPS_3		CCPS0 + CCPS1			 //PCA时钟输入 外部引脚ECI（最高系统时钟8分频）
#define		EPCA		BIT0					 //PCA计数定时中断使能

//CCAPMX
#define		ECOM		BIT6					 //允许比较功能（包括软件计数，WDT,PWM,高速输出功能）
#define		CAPP		BIT5					 //允许上升沿捕获
#define		CAPN		BIT4					 //允许下降沿捕获
#define		CAPPN		CAPP + CAPN				 //上升沿下降沿都捕获
#define		CMAT		BIT3					 //允许匹配控制位
#define		CTOG		BIT2					 //高速输出模式 允许引脚翻转
#define		CPWM		BIT1					 //PWM模式 允许引脚作为PWM输出
#define		ECCF		BIT0					 //PCA比较捕获中断使能	

/*************************************************
I2C
*************************************************/
//I2CADR
#define 	I2CGC		BIT0					 //是否响应通用调用地址

//I2CSTAT

//I2CCON
#define		I2CENS		BIT6					 //I2C接口使能
#define		I2CSTR		BIT5					 //起始标志位
#define		I2CSTO		BIT4					 //停止标志位
#define		I2CSI		BIT3					 //I2C中断标志
#define		I2CAA		BIT2					 //应答标志位

//I2C波特率
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
#define		I2CBPS_BLK	 I2CCR2 + I2CCR1 +I2CCR0 //根据timer计数初值决定BPS
//I2CTM
//I2CTMR
/*************************************************
SPI
*************************************************/
//SPICTR
#define		SPIFCLR		BIT2					 //置位此位将FIFO清空
#define		SPIM1		BIT1					 //工作模式控制1
#define		SPIM0		BIT0					 //工作模式控制0
#define		SPIM_NO		0X00					 //SPI禁止
#define		SPIM_S		SPIM0					 //SPI发送模式
#define		SPIM_R		SPIM1					 //SPI接收模式
#define		SPIM_SR		SPIM0 + SPIM1			 //SPI全双工

//SPICON
#define		SPIMASTER	BIT7					 //SPI主从设置，置位为MASTER 复位为SLAVE	

#define		SPIFLEN2	BIT6					 //帧数据长度控制  只在MASTER下有效
#define		SPIFLEN1	BIT5
#define		SPIFLEN0	BIT4
#define		SPIFLEN_4	SPIFLEN0 + SPIFLEN1
#define		SPIFLEN_5	SPIFLEN2
#define		SPIFLEN_6	SPIFLEN2 + SPIFLEN0
#define		SPIFLEN_7	SPIFLEN2 + SPIFLEN1
#define		SPIFLEN_8	SPIFLEN2 + SPIFLEN1 + SPIFLEN0 
												 
#define		SPICPHA1	BIT3					 //时钟沿选择
#define		SPICPHA0	BIT2
#define		SPICPHA_0   0X00					 //奇数收 偶数发
#define		SPICPHA_1  	SPICPHA0				 //偶数收 奇数发
#define		SPICPHA_2   SPICPHA1				 //奇数收 奇数发
#define		SPICPHA_3	SPICPHA0 + SPICPHA1		 //偶数收 偶数发

#define		SPICPOL		BIT1					 //同步时钟极性

#define		SPILSBF		BIT0					 //先传控制位 1低位先传 0高位先传

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
7:5 OPT[2:0] BGR 工作选项
4 BGR_Auto BGR 低功耗自动关闭设置
1： BGR 在进入低功耗模式时，自动关闭；工作模式时自动开启。
0： BGR 开关由 BGR_EN 控制.
3:1 -- 保留位
0 BGR_EN BGR 使能位
1： BGR 使能
0： BGR 关闭
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
注意事项：当使用 32pin 芯片时，需要把未使用的 GPIO 通过端口寄存器设置为内部上拉模式或
输出低电平模式，以防止漏电

****************************************************************/
#endif	///#ifndef __4802REG2_H__		

