
/*****************************************************************************
update by cc @201700110
Õë¶Ô¶à´®¿Ú ºÍ µ¥Ò»´®¿Ú ÓÐÇø±ð Ã¿¸ö´®¿ÚÊÇ¶ÀÁ¢µÄ»¹ÊÇ·Ö¿ªµÄÓÐ½²¾¿ ³ÌÐòÊÇ¸´ÔÓµÄ»¹ÊÇÈí¼þÓ¦ÓÃ¼òµ¥ÊÇ
¸öÐèÒªÆ½ºâµÄÊÂÇé.

clib/clib.c:  
¹«ÓÃµÄº¯Êý 	ºÍÓ²¼þÎÞ¹Ø 
·ÅÖÃ´®ÐÐÄ£Ê½(´®¿ÚµÈÆäËûÍ¨Ñ¶×ÜÏßÀàµÄÊä³ö)Êä³öµÄº¯Êý,
Ò»Ð©¸²¸ÇÄ£Ê½Êä³öµÄ(lcdµÈ¹ÌÆÁÊä³öµÄ)µÄÒ²¿ÉÊ¹ÓÃ  
					void Lc_print(void (*L0pf_send_uc)(char ww), char *dat,...)
-----------------------------------------------------------------------------------------
uartcom/Uprotocol2app  
  Ð­Òéµ½Ó¦ÓÃ
  ÎªÁËÊÊÓ¦²»Í¬µÄÍ¨Ñ¶Ð­ÒéÐèÒª²»Í¬µÄuart¿ÚÀ´¶ÔÓ¦ ºÍÓ¦ÓÃÏà¹Ø

typedef struct _ts_lcm_pro_; Ó¦ÓÃÐ­Òé°üµÄ¶¨Òå¼     LCMµÄÐ­Òé------------
											L3_UARTcom0_exp_protocol ½âÎöÓ¦ÓÃÐ­Òé
-----------------------------------------------------------------------------------------
uartcom/urec2protocol: ½ÓÊÕµ½µÄÊý¾Ý·ÅÈëµ½Ö¸ÏòÌØ¶¨Ð­ÒéµÄ»º´æÖÐ£¬ºÍÐ­ÒéµÄ¸ñÊ½ÓÐ¹Ø Ò»°ã·ÖÎª ±êÍ·Ê½»òÕß±êÎ²Ê½
¹«ÓÃµÄ´®¿ÚÍ¨Ñ¶¶¨Òå		
 	struct _s_protocol_ µÄ¹«¹²Ð­Òé°ü(¹Ø¼üµÄ½á¹¹Ìå)µÄÉùÃ÷------struct _s_protocol_
 							void L1_uart_2buf(struct _s_protocol_ *p)´®ÐÐÊý¾Ý±£´æµ½Ö¸ÏòÌØ¶¨Ð­ÒéµÄ»º³åÖÐ
--------------------------------------------------------------------------------------------
msp/uartx.c    µ×²ã´úÂë	 ºÍcpuÏà¹Ø »º´æ·¢ËÍÒ²·ÅÔÚÀïÃæ
			L0_UART0_Init
						UART0_IRQHandler
						    	L0_Usend_uc------UserDef
-----------------------------------------------------------------------------------------
********************************************************************************/


#include "uprotocol2app.h"
//#include "../bsp/adxl362.h"	
#include "../msp/uart0.h"
#include "../msp/time.h"
#include "../msp/msp_i2c.h"
#include "../msp/msp_buzz.h"
#include "../msp/msp_adc.h"

#include "../bsp/cw63xx.h"
#include "../app/App_flow.h"
#if 0	// for app
#include "../bsp/am2320.h"
#include "../app/app_yeelink_para.h"
#endif 
///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>exp>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//struct _ts_cmd_pro_ ts_CMD_pro0_temp;
//struct _ts_cmd_pro_ ts_CMD_pro0; 	

typedef struct 
{
    vU16 iFilter;       //¹ýÂËÐ­ÒéÍ· 
    U8 len; 	// y position  ¶ÔÓ¦uartxµÄbuf : s_atx.buf[2]  ´ÓcOrder µ½ d2
    U8 cOrder;       //ÃüÁîÖ¸Áî ²»¿É³öÏÖ66 55
    U8 x; 	// x position
    U8 y; 	// x position
 //   vU8 d2;       //data
//    vU8 d3;       //data
}TS_lcm_PRO;
//TS_lcm_PRO_ *plcm;//ts_pr_pool;
//U16 x,y,z;
void L0_UARTcom_Init(struct _s_protocol_ *p)
{
	p->head = 0;
	p->ok = 0;
	p->data_ok = 0;
	p->sub_num= 0;
	p->num = 0;
	p->close = 0;
	p->filter1 = D_CMD_Filter1;
	p->filter2 = D_CMD_Filter2;
	p->pfun_get= L0_uart0_get;

 //  ÈÎÎñ³õÊ¼»¯
///	L1_task_init(&s_task_uart0.task);
///	L3_task_s_go(s_task_uart0,D_task_init);	

}
#define D_receive_data_OK	1
#define D_receive_data_NONE	0

// iicsend" 

//L3_UARTcom0_exp_protocol(&s_at0);
void L3_UARTcom0_exp_protocol(struct _s_protocol_ *p)
{  // array[]="ok\r\n"//p->max  5  -->  [0][1][2][3][4]
//	if (1 != p->close)
	{
		if(1 == p->ok)
		{
			if(strstr( p->array,"statusE") != NULL)
			{// statusE:1000000		// [0]:
			
				L0_uart0_uc('E');	
				D_led_P22_ONF(p->array[8] - '0');
				D_led_P23_ONF(p->array[9] - '0');
				D_led_P24_ONF(p->array[10] - '0');
				D_led_P25_ONF(p->array[11] - '0');
				D_led_P26_ONF(p->array[12] - '0');
				D_led_P27_ONF(p->array[13] - '0');
			}else if(strstr( p->array,"buzPlay") != NULL)
			{// iicSend:
			//  buzPlay:12
				L0_uart0_uc('B');	
				catch_protocol(p->array,p->pro);							
				L1_buzz_play(p->pro[0]);
				L0_uart0_uchex(p->pro[0]);
			}else if(strstr( p->array,"buzzSet") != NULL)
			{//  iicSend:
			 //  buzzSet:12 
			 /// L2_task_BUZZ_run(channel,uchigh,uclow,ucrepeat)
				catch_protocol(p->array,p->pro);
				L0_uart0_uc('z');	
				L0_uart0_uchex(p->pro[0]);	
				L0_uart0_uchex(p->pro[1]);	
				L0_uart0_uchex(p->pro[2]);	
				L0_uart0_uchex(p->pro[3]);	
				
				L2_task_BUZZ_run(p->pro[0],p->pro[1],p->pro[2],p->pro[3]);//U8 uchigh,U8 uclow,U8 ucrepeat);
			}
			else if(strstr( p->array,"iicSend") != NULL)
			{//// iicsend:12 0a bc";
			///¶ÁÈ¡addÎª0x12µÄÉè±¸µÄ¼Ä´æÆ÷0x34¼°ÒÔºóÐ´Èë56 78 9a
			//// *s="iicsend:12 34 56\r\n";
			///¶ÁÈ¡addÎª0x12µÄÉè±¸µÄ¼Ä´æÆ÷0x34¼°ÒÔºóÐ´Èë56
				L0_uart0_uc('i');
				catch_protocol(p->array,p->pro);
				L0_uart0_uchex(p->pro[0]);	
				L0_uart0_uchex(p->pro[1]);	
				L0_uart0_uchex(p->pro[2]);	
				L2_i2c_write(p->pro[0],p->pro[1],p->pro[2]);
			}
			else if(strstr( p->array,"iicRead") != NULL)
			{/// *s="iicread:12 01 06\r\n";
			/// iicread:12 00 01
			///¶ÁÈ¡addÎª0x12µÄÉè±¸µÄ¼Ä´æÆ÷0x01¼°ÒÔºóµÃ0x06¸öÊý¾Ý
				L0_uart0_uc('r');
				catch_protocol(p->array,p->pro);
				L2_i2c_read(p->pro[0],p->pro[1],p->pro[2]);
			}

			else if(strstr( p->array,"adcRead") != NULL)
			{/// *s="iicread:12 01 06\r\n";
			/// iicread:12 00 01
			///¶ÁÈ¡addÎª0x12µÄÉè±¸µÄ¼Ä´æÆ÷0x01¼°ÒÔºóµÃ0x06¸öÊý¾Ý
				L0_uart0_uc('r');
				catch_protocol(p->array,p->pro);
				//L2_i2c_read(p->pro[0],p->pro[1],p->pro[2]);
				if(0x01 == p->pro[0])
				{L0_uart0_uc('1');
					L0_ADC_STOP();	/// ¿ªÊ¼²ÉÑù
				}else if(0x02 == p->pro[0])
				{L0_uart0_uc('2');
					L0_ADC_START();	/// ¿ªÊ¼²ÉÑù

				}else if(0x03 == p->pro[0])
				{L0_uart0_uc('3');
				L0_adc_EIO_close(1);	/// ¿ªÊ¼²ÉÑù

				}else if(0x04 == p->pro[0])
				{L0_uart0_uc('4');
					L0_adc_EIO_close(0);	/// ¿ªÊ¼²ÉÑù
				}else
				{		//adc ÏûºÄ 1.21mA  ÔÚ3.1vµçÔ´ÏÂ
						//3.014--1.804
						///ËùÓÐµçÔ´¶¼ÊÇ1.8v ºó 2.624  - 1.654= 0.97 mA
				}
					
			}

			else 			
			{
				//no 
			};
			p->ok = 0;
		}
	}
}

// *s="iicsend:12 34 56 78 9a \r\n";
//  i:         012345678
//void catch_protocol (char d_src[],char d_protocol[]) 

//  Ð­Òé½âÎö³ÌÐò
/// L3_UARTcom0_exp_protocol(&s_at0);

#if 0	


if(strstr( p->array,"waken") != NULL)
		{
			//L1_task_AM2320_waken();
			p->ok = 0;
		}else if(strstr( p->array,"write") != NULL)
		{
			//L1_task_AM2320_write();
			p->ok = 0;
		}else if(strstr( p->array,"read") != NULL)
		{
			//L1_task_AM2320_read();
			p->ok = 0;
		}else if(strstr( p->array,"all") != NULL)
		{
			//L1_task_AM2320_waken();
			//L1_task_AM2320_write();
			Ldi_print("all");
			//Lc_delay_ms(3);	
			//L1_task_AM2320_read();

			
			p->ok = 0;
		}
		else
		{
			//no 
		}
void L3_UARTcom0_exp_protocol(struct _s_protocol_ *p)
{  // array[]="ok\r\n"
	if (1 == p->ok )
	{	//fixme :²¢Î´Ìí¼ÓµØÖ·ÅÐ¶¨
		//Lc_print("exp_protocol..");
		//D_led_D0_REV();
		s_nos_tick.n = 1;// ÔÝÊ±¹Ø±ÕÐÄÌø4s ×óÓÒ
		switch (p->buf[3])
		{
		
				case 0x00:
			break;	

					
/******************************************************************************
			case 0x10:
				//5a a5 05 10 01 02 03 04 05 
				//5a a5 05 10 ff ff ff ff ff 
				//5a a5 05 10 00 00 00 00 00 
				L0_uart0_uc(0x10);			
				ts_Lcd_data.plcd = (TS_lcd_cc_ *)(p->buf);
				ts_Lcd_data.reg[0] = ts_Lcd_data.plcd->reg[0];
				ts_Lcd_data.reg[1] = ts_Lcd_data.plcd->reg[1];
				ts_Lcd_data.reg[2] = ts_Lcd_data.plcd->reg[2];
				ts_Lcd_data.reg[3] = ts_Lcd_data.plcd->reg[3];
				ts_Lcd_data.reg[4] = ts_Lcd_data.plcd->reg[4];
				//ts_Lcd_data.reg[5] = ts_Lcd_data.plcd->reg[5];
				L0_pLcd_WriteReg(ts_Lcd_data.reg);
			break;			
			case 0x11:				
				//5a a5 03 11 01 02  
				// 0  1  2  3  4  5
				L0_uart0_uc(0x11);	
				L2_plcd_number(p->buf[4],p->buf[5]);
				L0_pLcd_WriteReg(ts_Lcd_data.reg);
			break;	

			case 0x12:				
				//5a a5 03 11 01 02  
				// 0  1  2  3  4  5
				L0_uart0_uc(0x12);	
				//L2_plcd_number(p->buf[4],p->buf[5]);
			//	L0_pLcd_WriteReg(ts_Lcd_data.reg);
				L0_uart0_sendbuf((char *)&RTC_Time,7);
				
			break;	

			
			case 0xe0:
				//5a a5 03 e0 00 00 
				L0_uart0_uc(0x00);				
				//s_adc_vc.flag = D_flag_lock;
				//L0_uart0_uc(s_adc_vc.n);	
						
			#ifdef D_open_save_buf
			
				L0_uart0_sendbuf(&s_adc_vc.ucArray[0],255);
			#endif
				//L2_task_go(D_task_stop);			
			break;
			case 0xe1:
				//5a a5 03 e1 00 00 
				L0_uart0_uc(0x00);			
				//if(1 == s_array_hd.savef )
				{
				//	s_array_hd.savef = 0;
				//	L0_uart0_sendbuf16(&s_array_hd.ucArray_f[0],1023);	

				}
				//L0_uart0_uc(s_array_hd.n);	
				//L2_task_go(D_task_stop);	
			break;
				
				case 0xe2:
					//5a a5 03 e2 00 00 
					L0_uart0_uc(0x80);			
					s_array_hd.savef = 0;
				//	D_led_debug_OFF();
					s_array_hd.zn = 0;
					s_array_hd.hn = 0;
					s_array_bit.usTime = 0;
					s_array_bit.ucByte_shift = 0;
					s_array_bit.ucByte_n = 0;
					s_array_bit.usN = 0;

					
				break;


				

			case 0xA1:
				//5a a5 03 a1 00 00 ¶ÁÈ¡ÈýÖáÊý¾Ý
				ADXL362_GetXyz(&x,&y,&z);
				//s_nos_tick.n = 2;Lc_print("\n\r%x4	%d	%x4	%d	%x4	%d	",x,x,y,y,z,z);
				s_nos_tick.n = 2;
			//	Lc_print("\r\n%d\t%d\t%d",x,y,z);
				Lc_print_buf("\r\n%d\t%d\t%d",x,y,z);
			break;

			case 0xb0:
				//5a a5 03 b0 00 00 ·äÃùÆ÷²¥·Å
				//Lc_print("0xb0\r\n");
				
				plcm = (TS_lcm_PRO_ *)(p->buf);
				Lc_print("\r\n Play=%d ",plcm->x);
				L1_buzz_play(plcm->x);	
			break;
			case 0xb1:
				//5a a5 03 b1 00 00 ·äÃùÆ÷¹Ü½Å²âÊÔ
				//Lc_print("0xb0\r\n");
				plcm = (TS_lcm_PRO_ *)(p->buf);
				Lc_print("\r\n P21=%d ",plcm->x);
				L1_buzz_play(plcm->x);	
				P21 = plcm->x;
			break;			
			case 0xc0:				
				Lc_print("0xc0\r\n");
				//L2_LCD_GotoXY(p->x,p->y);
				//L0_LCM_WriteData(p->d2);
				//L0_USART_print(UART_debug,"\r\nWriteData (%d,%d)=%x <%d>",p->x,p->y,p->d2,s_lcm108.cs);
			break;
			case 0xc1:
				Lc_print("0xc1 ADXL362_Init\r\n");
				n =  ADXL362_Init();
				
				L0_uart0_uc('x');
				Lc_uc_hex(L0_uart0_uc,n);
				L0_uart0_uc(0x09);
			    if(0 != n)
			    {
					Lc_print("id=%d \r\n",n);
				   // ADI_Component("ADXL362 OK");
			    }
			    else
			    {
					Lc_print("Err\r\n");
			       // ADI_Component("ADXL362 Err");
			    }
				//L2_LCD_GotoXY(p->x,p->y);
				//L0_LCM_WriteData(p->d2);
				//L0_USART_print(UART_debug,"\r\nWriteData (%d,%d)=%x <%d>",p->x,p->y,p->d2,s_lcm108.cs);
			break;	
			case 0xc2:
				Lc_print("0xc2\r\n");
				L0_uart0_uc('s');
				n = plcm->x;
				Lc_uc_hex(L0_uart0_uc,n);
				ADXL362_SetRegisterValue(n, ADXL362_REG_TIME_ACT, 1);
			break;
			case 0xc3:
				n =0;
				ADXL362_GetRegisterValue(&n, ADXL362_REG_TIME_ACT, 1);
				L0_uart0_uc('R');
				Lc_uc_hex(L0_uart0_uc,n);
			break;
			case 0xd2://d2 x y   x = reg y =value
			// d2 22 45
			Lc_print("\r\ncmd %x2 %x2 ",plcm->x,plcm->y);
				n =0;
				//L0_uart0_uc('S');
				Lc_print("\r\nset reg %x2 = %x2",plcm->x,plcm->y);
				ADXL362_SetRegisterValue(plcm->y,plcm->x, 1);

			break;
			case 0xd3://d3 x y   x = reg y =value
			Lc_print("\r\ncmd %x2 %x2 ",plcm->x,plcm->y);
				n =0;
				//ADXL362_SetRegisterValue(plcm->y,plcm->x, 1);
				ADXL362_GetRegisterValue(&n, plcm->x, 1);
				
				Lc_print("\r\nGet reg %x2 ",plcm->x);L0_uart0_uc('R');
				Lc_uc_hex(L0_uart0_uc,n);
			break;
			case 0xc4:
				for(n = 0;n<254 ;n ++)
				{
				  L0_uart0_uc((U8)n);
				 // Lc_uc_hex(L0_uart0_uc,(U8)n);
				 // Lc_us_hex(L0_uart0_uc,(U16)n);
				}
				for(n = 0;n<254 ;n ++)
				{
				  //L0_uart0_uc((U8)n);
				  Lc_uc_hex(L0_uart0_uc,(U8)n);
				 // Lc_us_hex(L0_uart0_uc,(U16)n);
				}
			break;
			case 0xc5:

				for(n = 0;n<254 ;n ++)
				{
				 // L0_uart0_uc((U8)n);
				 // Lc_uc_hex(L0_uart0_uc,(U8)n);
				  Lc_us_hex(L0_uart0_uc,(vU16)n);
				}
			break;
			****************************************************************/
			default:
			//	L1_uart0_putstr("\r\ninvaliad command!");
			//	L0_send0_uc_hex(p->cOrder);
				break;
		}
		p->ok = 0;
	}
}//L1_exp_protocol
#endif
///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<exp<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>task>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


/******************************************************************************
**                            End Of File
******************************************************************************/
