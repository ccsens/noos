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

P04 PW_IRQ �жϷ�ʽ
PW_PG P20  ��ѯ��ʽ
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
	BITN_1(AIE,PTE);	// �˿��ж�ȫ��ʹ��
	BITN_1(P0_IE,BITN4);// ѡ���˿��ж�ʹ��
	
	BITN_0(P0_INT_SEL,BITN4);// �˿��ж�Դ 1:��ƽ���� 0�ش���
	BITN_0(P0_EDGE_SEL,BITN4);// �˿��ж�ʹ�� 1 ����,�ߵ�ƽ 0�½��ش���

	BITN_1(P0_PE,BITN4);		///1�����ڲ��������� ����ⲿ���ӵ�������
		
		///0 PxDIR0 �˿� Px0 ����������üĴ���
///1�����ó�����
///0�����ó����
	BITN_1(P0_DIR,BITN4);	
	gRegU_AppFlag = 0;

	
}





