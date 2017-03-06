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




/**************************

				P0_DIR = what.PX_DIR_Data;
				P0_Edge_Sel = what.PX_Edge_SEL_Data;
				P0_IE = what.PX_IE_Data;
				P0_PE = what.PX_PE_Data;
				P0_DS = what.PX_DS_Data;
				P0_OpenDrain = what.PX_Opendrain_Data;

aie.pie

P2_IFG[X]
AIPH AIPL 

P04 PW_IRQ 中断方式
PW_PG P20  查询方式
**********************/


/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "msp_io.h"	




void GPIO_IRQHandler (void) interrupt Interrupt_All_Port_Number// using 0
{//
	if(BITN_G(P0_IFG,BITN4))
	{
		gRegU_AppFlag = 1;

	}

}

void L0_gpioint_P04_init(void)
{
	BITN_1(AIE,PTE);	// 端口中断全局使能
	BITN_1(P0_IE,BITN4);// 选定端口中断使能
	
	BITN_0(P0_INT_SEL,BITN4);// 端口中断源 1:电平触发 0沿触发
	BITN_0(P0_EDGE_SEL,BITN4);// 端口中断使能 1 上升,高电平 0下降沿触发

	BITN_1(P0_PE,BITN4);		///1：有内部上拉功能 如果外部不加电阻上拉
		
		///0 PxDIR0 端口 Px0 输入输出配置寄存器
///1：配置成输入
///0：配置成输出
	BITN_1(P0_DIR,BITN4);	
	gRegU_AppFlag = 0;

	
}





