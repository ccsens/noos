//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            app_action.c
/// @brief           app_action driver app  
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
/// Descriptions:	
//////////////////////////////////////////////////////////////////////////



/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

#include "app_action.h"	
#include "../bsp/bsp_led.h"

void L2_task_ACTION_init(void)
{
	
	L1_task_init(&s_task_ACTION.task);
	L3_task_s_go(s_task_ACTION,D_task_init);	
	

}

struct _s_task_ACTION_ s_task_ACTION;
void L2_task_ACTION_handdle(struct _s_task_ACTION_ *s)
{
	switch(s->task.sh)
	{
		case D_task_init://
		
		///if(L3_task_s_free(s_task_uart0))
		{
 			Lc_print_buf(" \r\n L2_task_ACTION_init");
			//L2_plcd_time_pre();
			L2_task_go(D_task_ACTION_read);
		//	L1_task_idelay(1*D_idelay_1s);	//大约6s 
		}
		break;
		case D_task_ACTION_read:
			//读取三轴数据
			//ADXL362_GetXyz(&s->x,&s->y,&s->z);
			L2_task_go(D_task_ACTION_send);		
			break;
		case D_task_ACTION_send:
		//	Lc_print_buf("\r\n%d\t%d\t%d",s->x,s->y,s->z);	
			L2_task_go(D_task_ACTION_action);	
			L1_task_idelay((1*D_idelay_10ms));					
			break;
		case D_task_ACTION_action:
			//Lc_print_buf("\r\n%d\t%d\t%d",s->x,s->y,s->z);	

if(s->xa >= s->x)
{
	if((s->xa - s->x)> 300)
	{
Lc_print_buf("\r\n%d\t%d\t%d--",s->x,s->xa,s->z);	L1_bsp_led_onf(1,1);
	}
	else
	{
		L1_bsp_led_onf(1,0);
	}
}else
{
	if((s->x - s->xa)> 300)
	{
Lc_print_buf("\r\n%d\t%d\t%d--",s->x,s->xa,s->z);	L1_bsp_led_onf(1,1);
	}
	else
	{
		L1_bsp_led_onf(1,0);
	}
}
	/****
			
			if((s->xa - s->x)> 500)
			{//Lc_print_buf("\r\n%d\t%d\t%d",s->x,s->y,s->z);	
//Lc_print_buf("\r\n%d\t%d\t%d--",s->x,s->xa,s->z);	
//Lc_print_buf("\r\n--------------%d\t%d\t%d",s->xa,s->ya,s->za);				
				L1_bsp_led_onf(1,1);
			}else
			{
				L1_bsp_led_onf(1,0);
			}

		
			if((s->ya - s->y)> 500)
			{
				L1_bsp_led_onf(2,1);

			}else
			{
				L1_bsp_led_onf(2,0);

			}
			if((s->za - s->z)> 500)
			{
				L1_bsp_led_onf(3,1);

			}else
			{
				L1_bsp_led_onf(3,0);

			}		
			*********/
			//s->x,s->y,s->z
			s->xa = s->x;
			s->ya = s->y;
			s->za = s->z;
			
			L2_task_go(D_task_ACTION_read);	
			L1_task_idelay((1*D_idelay_10ms));					
			break;


			
		L2_task_switch_flag_idelay(1,'p');
	}

}


