////////////////////////////////////////////////////////////////////////////  
///@copyright  Copyright (c) 2017, 传控科技 All rights reserved.  
///-------------------------------------------------------------------------  
/// @file            app_flow.c
/// @brief           应用程序里的流程,包括电源管理,上电顺序, 
///-------------------------------------------------------------------------  
/// @version		1.1  
/// @author		CC 
/// @date			20150102
/// @note			CC-PWR-VH01-m02.sch
///-------------------------------------------------------------------------
/// @version		1.2  
/// @author		CC 
/// @date			20170122
/// @note			cc_swhh_MD02
//////////////////////////////////////////////////////////////////////////////



///-------------------------------------------------------------------------
/// 下面是一个含有两个参数的函数的注释说明（简述）   
///     
///      @breif 这里写该函数的详述信息     
///      @param a 被测试的变量（param描述参数）     
///      @param s 指向描述测试信息的字符串     
///      @return     测试结果（return描述返回值）   
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
#include "app_flow.h"	
#include "app_fsk.h"	
#include "../bsp/bsp_led.h"
#include "../bsp/cw63xx.h"
#include "../msp/msp_adc.h"
extern RTC_Time_Struct RTC_Time; 

///-------------------------------------------------------------------------     
///      @breif L2_task_PWON_init     
///      @param a s_task_PWON
///      @param s "L2_task_PWON_init"
///      @return	
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
///-------------------------------------------------------------------------
void L1_PWON_init(void)
{
	
	L3_debug_time(); 
	#if 0
	//L1_cw63xx_get();  
	while(9)
	{
		
	L2_i2c_read(D_i2c_addr_cw63xx,D_Power_channel_LED,3);
		
	//L2_i2c_write(D_i2c_addr_cw63xx,D_Power_channel_LED,D_CW63XX_ON|D_CW63XX_2V1);
	Lc_delay_ms(1000);// 2000--7s
	}
//	L2_i2c_write(D_i2c_addr_cw63xx,D_Power_channel_VCC,D_CW63XX_ON|D_CW63XX_1V8);
	
//	L2_i2c_write(D_i2c_addr_cw63xx,D_CW63X_PW_BUZ,D_CW63XX_ON|D_CW63XX_1V8);
//	L2_i2c_write(D_i2c_addr_cw63xx,D_CW63X_PW_MIC,D_CW63XX_ON|D_CW63XX_1V8);
	//D_CW63XX_OFF|D_CW63XX_1V8
	#endif

}

///-------------------------------------------------------------------------     
///      @breif L2_task_PWON_init     
///      @param a s_task_PWON
///      @param s "L2_task_PWON_init"
///      @return	
///      @see     Test()     （本函数参考其它的相关的函数，这里作一个链接）  
///      @note     (note描述需要注意的问题) 
///-------------------------------------------------------------------------
void L2_task_PWON_init(void)
{
	
	L1_task_init(&s_task_PWON.task);
	L3_task_s_go(s_task_PWON,D_task_init);	
}


//>>>>>>>>>>>>>>>>>>>>>0开机task
#define D_task_PWON_STEP		0x30
#define D_task_PWON_heratbeat	0x70
#define D_task_PWON_power2		0x80
#define D_task_PWON_power3		0x81
#define D_task_PWON_power4		0x82
#define D_task_PWON_power5		0x83
#define D_task_PWON_power6		0x84
#define D_task_PWON_second		0x90
#define D_task_PWON_second2		0x92


#define D_task_PWON_CWinfo		0xa0
#define D_task_PWON_CWinfo2		0xa2
#define D_task_PWON_CWinfo3		0xa3



struct _s_task_PWON_ s_task_PWON;
void L2_task_PWON_handdle(struct _s_task_PWON_ *s)
{
	switch(s->task.sh)
	{
		case D_task_init://
			if(L0_uart0_SendIntFree())
			{
	 			Lc_print_buf(" \r\nSYTEM PWON");
				s->status = D_PWON_status_time;
				s->key = 0;
				L2_task_go(D_task_PWON_power2);
				L1_task_idelay(2*D_idelay_1s);	//大约6s 
			}	
		break;
//---------------------------------------------------------------------------------------------
		case D_task_PWON_power2://     bug

				L0_uart0_uc('a');
				L1_cw63xx_write(D_Power_channel_LED,D_CW63XX_ON|D_CW63XX_2V5);
				L2_task_go(D_task_PWON_power3);
		break;
		case D_task_PWON_power3://
				L0_uart0_uc('b');	
				L1_cw63xx_write(D_Power_channel_BUZ,D_CW63XX_ON|D_CW63XX_1V8);
				//L1n_i2c_write(D_i2c_addr_cw63xx,D_Power_channel_BUZ,D_CW63XX_ON|D_CW63XX_1V8);
				L2_task_go(D_task_PWON_power4);
		break;
		case D_task_PWON_power4://
				L0_uart0_uc('c');
				L1_cw63xx_write(D_Power_channel_MIC,D_CW63XX_ON|D_CW63XX_1V8);
				L2_task_go(D_task_PWON_power5);
		break;
		case D_task_PWON_power5://
				L0_uart0_uc('d');
				L1_cw63xx_write(D_Power_channel_VCC,D_CW63XX_ON|D_CW63XX_3V2);// for debug
				L2_task_go(D_task_PWON_power6);
				L1_task_idelay((20*D_idelay_10ms));
		break;
		case D_task_PWON_power6://
				if(L1_cw63xx_write_ok())
				{
					L0_uart0_uc('d');
					L1_cw63xx_write(D_Power_channel_VCC,D_CW63XX_ON|D_CW63XX_3V2);// for debug
					L2_task_go(D_task_PWON_heratbeat);
				}
		break;
	//------------------------------------------------------------------------------------------
	#if 0
		case D_task_PWON_heratbeat:

			if(1 == s_array_hd.savef)
			{
				s_array_hd.savef = 0;		
				L0_uart0_0d0a();
				//s_adc.val ++;
				L0_uart0_uchex(s_array_hd.hn);
				L0_uart0_uchex(s_array_hd.zn);
				
				L2_task_go(D_task_PWON_heratbeat);
				///L1_task_idelay((90*D_idelay_10ms));	
				L2_task_cycle_delay(50000);///		300000=2s	
			}
				
			break;


	#else
		case D_task_PWON_heratbeat:
			if(1 == s_nos_tick.t1s_heatbeart)// 心跳代码
			{s_nos_tick.t1s_heatbeart = 0;
				//D_led_debug_REV();//L0_uart0_uc(0xaa);  //L0_uart0_uc(0x55);
				if(0 == s_nos_tick.t_1s%5)
				{	//D_led_D4_REV();	
				//	L0_WDT_CleanAndStartWdt();
					//L0_uart0_uc('.');// 似乎对 下面的显示秒有影响
				}
			}
			L2_task_go(D_task_PWON_CWinfo);
		break;
//-----------------------------------------------------------------------------------------	
		case (D_task_PWON_CWinfo):
			if(L2_AppFlag_CWInt_is(D_AppFlag_CWInt))
			{
				L2_AppFlag_CWInt_clear(D_AppFlag_CWInt);
				L0_uart0_uc('.');
				L1_cw63xx_read(D_CW63X_REG_Interrupt);
				L2_task_go(D_task_PWON_CWinfo2);
			}else
			{
				L2_task_go(D_task_PWON_second);
			}
		break;
		case (D_task_PWON_CWinfo2):
				if(L1_cw63xx_get())
				{
					L0_uart0_uc('R');
					L0_uart0_uchex(gRegU_CWreg);
				}
			L2_task_go(D_task_PWON_second);
		break;
//-----------------------------------------------------------------------------------------		
		case (D_task_PWON_second):
			if(1 == s_nos_tick.t1s_rtc)
			{	//L0_WDT_init();
				s_nos_tick.t1s_rtc = 0;
				L0_uart0_uchex(RTC_Time.sec);	
			}

			if(1 == s_nos_tick.t1m_rtc)// /// 出现第一个1min
			{
				s_nos_tick.t1m_rtc = 0;
	 			Lc_print_buf(" \r\nre PW");
				L2_task_go(D_task_PWON_power2);
			}else
			{
				L2_task_go(D_task_PWON_heratbeat);
			}
		break;
	#endif
		L2_task_switch_flag_idelay(1,'p');
	}

}



			/****************


		case D_task_PWON_heratbeat:
			L0_uart0_0d0a();
			//s_adc.val ++;
			L0_uart0_uchex(s_adc.val);
			
			L2_task_go(D_task_PWON_heratbeat);
			L1_task_idelay((80*D_idelay_10ms));

			
		break;



		case (D_task_PWON_second):
				L2_task_go(D_task_PWON_second2);
			if(1 == s_nos_tick.t1s_rtc)
			{
				//s_nos_tick.t1s_rtc = 0;
				//L0_uart0_uchex(RTC_Time.sec);	
				s->sec = RTC_Time.sec;
				L0_uart0_uc(cguHex2Char[D_uc_low(s->sec)][0]);
				L1_task_idelay(D_idelay_100ms);
			}
		break;







			
			switch(s->status)
			{
				case D_PWON_status_time:
					break;
				case D_PWON_status_angle:
			
					break;
				case D_PWON_status_setup:
			
					break;
				case D_PWON_status_count:
			
					break;
				case D_PWON_status_erro:
			
					break;
				default:
					s->status = D_PWON_status_time;
					break;	
			};
			L2_task_go(D_task_PWON_status + s->status);			
		break;
			*****************/
/******************************************************************************
	case (D_task_PWON_status + D_PWON_status_time):
			if(1 == s_nos_tick.flag_1s2)// 心跳代码
			{s_nos_tick.flag_1s2 = 0;
				//L2_plcd_time();
				//L0_uart0_uc(RTC_Time.sec);	
			}
			// L0_uart0_uc('-');L0_uart0_uc
			// 1024 次进入
			if(s->key)//如果收到按键 进入设置状态
			{
				s->status =  D_PWON_status_setup;;
				L2_task_go(D_task_PWON_status + s->status);
			}		
			else
			{
				L2_task_go(D_task_PWON_heratbeat);
			}
		break;
		#define D_key_up		1
		#define D_key_down		2
		#define D_key_enter	3
		case (D_task_PWON_status + D_PWON_status_setup):
			switch(s->status)
			{
				case D_key_up:
					break;
				case D_key_down:
			
					break;
				case D_key_enter:
					s->status = D_PWON_status_time;		
					
					break;
				default:
					//s->status = D_PWON_status_time;
					break;	
			};
	
**                            End Of File
case D_task_PWON_STEP:
//"" SYTEM CHECK
	Lc_print_buf(" \r\n OSD_PWON version ");



	L2_task_go(D_task_PWON_STEP+1); 	  
	L1_task_idelay(3*D_idelay_100ms);
break;		
			

case D_task_PWON_STEP + 4:
	Lc_print_buf("	0.0 ppm\x00");
	Lc_print_buf(" \r\n OSD_PWON end");

	//RANGE:0..100	MAN
	//	  --.-- 	---.--
	//					0.0 ppm
//	L2_LCD_OutStruct(&ts_osd_area1[5]);//ppm
	
	L2_task_go(D_task_PWON_heratbeat);			
	//L3_task_s_go(s_task_OSD_MAIN,D_task_init); // 启动其他任务
	L1_task_idelay(5*D_idelay_100ms);
break;



******************************************************************************/
