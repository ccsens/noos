/*****************************************************************************
 *   uart.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2017,SensorControl
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *2017.01.10  ver 1.10    rename tick.h  tick.c
****************************************************************************************/
#include "tick.h"
		#ifdef D_debug_sim

		#include "../msp/msp_rtc.h"
		#endif
		
		#include "../debug/debug_led.h"
struct  _s_nos_tick_ s_nos_tick;

/*********************************************************************************************************
* Function Name:        timer0Isr
* Description:          TIMER0 �жϴ�����
* Input:                ��
* Output:               ��
* Return:               ��
*********************************************************************************************************/

void L1_tick_init(void)
{
	s_nos_tick.n_stamp = 0;  
//	s_nos_tick.t1s_heatbeart= 0;
//	s_nos_tick.t1s_flag[0] = 0;
//	s_nos_tick.t1s_flag[1] = 0;
//	s_nos_tick.t1s_flag[2] = 0;
//	s_nos_tick.t1s_flag[3] = 0;
//	s_nos_tick.t1s_flag[4] = 0;
//	s_nos_tick.t1s_flag[5] = 0;
	s_nos_tick.t_10ms = 0;
	s_nos_tick.t_1s = 0;
	s_nos_tick.t1s_heatbeart = 0;
	s_nos_tick.t1s_rtc= 0;
	s_nos_tick.t1s_rtc_n = 0;

	
	s_nos_tick.t1m_rtc = 0;
	s_nos_tick.t1m_rtc_one = 0;
}

void L1_tick_tick (void)
{/// ��ʱ������Ϊ10ms ����һ��
	/// s  5ms		 65535*65535 /3600/24/365=139nian/s 
	// 4,294,836,225 = 65535*65535  ;3600*24*60*60 = 31,536,000��/��
	// fixme:�˴� ������һ��497���������bug �Ǹ�ʱ��������ʹ��t_10ms
	/// ��һ��ϵͳ�Ƚ�ȷ����ʱ����s_nos_tick.t_10ms ��Ҫ������ �������͹���ģʽ֮ǰ 
	/// ������Զ��û������bug������ 201702  ����һ�ַ�ʽ��ӱ��� ʹ�õ�ʱ��++,��ʹ��ʱ
	/// -- �����ͷ�,������=0ʱ����û��������ʹ��t_10ms��ʱ���Իָ���ʼֵ=Ŀǰֵ%100
	s_nos_tick.t_10ms ++;//D_led_D1_REV(); 20160522 ��֤
	if(s_nos_tick.t_10ms%D_TIMER0_1S_COUNT == 0)
	{// 65535*65535/24/60/60/356/10 =12.7�� 
	//	

		s_nos_tick.t_1s ++;//
		s_nos_tick.t1s_heatbeart = 1;
		//led =~led;
		//s_nos_tick.t1s_flag[0] = 1;
		//s_nos_tick.t1s_flag[1] = 1;
		//s_nos_tick.t1s_flag[2] = 1;
		//s_nos_tick.t1s_flag[3] = 1;
		//s_nos_tick.t1s_flag[4] = 1;
		//s_nos_tick.t1s_flag[5] = 1;
		#ifdef D_debug_sim
			RTC_Time.sec ++;
			s_nos_tick.t1s_rtc = 1;
		#endif
	}
}




#if 0	///<1213123
// ��ʱ����:  ���ȶ���ĳ��ͨ��ch Ȼ����t_1s ��invent����  ,�������ʾ's'   
void L2_time_beat_heart(U32 ch,U8 invent,U8 s)
{
	/**********
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			//L0_debugS_uc(s);
		}
	}
	***********/
}

/***************
if(1 == s_nos_tick.t1s_heatbeart)// ����ʱ��
{s_nos_tick.t1s_heatbeart= 0;
	L0_debugS_uc('.');
	L2_task_go(D_task_stop);
}
***************/

/*********************************************************************************************************
** Function name:	    delayNS
** Descriptions:	    ��ʱ����
** input parameters:    ulDly:   ֵԽ����ʱʱ��Խ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void delayNS (U32 ulDly)
{
    U32 i; 
    
    for (; ulDly > 0; ulDly--) {
        for (i = 0; i < 50000; i++);
    }
}

/*

#if 0

LPC_SC->PCONP |= (1<<1);                       //�򿪹��ʿ���  
      
    LPC_TIM0->TCR |= (1<<1);                       //��λ��ʱ��  
    LPC_TIM0->PR   = 0x00;                           //Ԥ��Ƶ����  
    LPC_TIM0->MR0  = 10000;                          //ƥ��Ĵ����붨ʱ��������ֵ��Ƚ�  
    LPC_TIM0->IR  |= 0XFF;                           //�������жϱ�־λ  
    LPC_TIM0->MCR |= ((1<<1)|(1<<0));                //MR0��TCֵƥ��ʱ�������ж�,TC��λ  
    LPC_TIM0->TCR  = (1<<0);                       //������ʱ��  
  
    NVIC_EnableIRQ(TIMER0_IRQn);                    // enable irq in nvic             // 
	T0PR = 99;				 // ���ö�ʱ��0��ƵΪ100��Ƶ����160000Hz ���� 16M

#endif


void L0_timer0_Init (void)
{

}

// s_nos_tick.t1s_flag[1]




// ��ʱ����:  ���ȶ���ĳ��ͨ��ch Ȼ����t_1s ��invent����  ,�����ִ��*fun()   
void L2_time_beat_heart_fun(U32 ch,U8 invent,void (*fun)(void))
{
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			fun();
		}
	}
}


// ��ʱ����:  ���ȶ���ĳ��ͨ��ch Ȼ����t_1s ��invent����  ,�����ִ��*fun()   
U32 L2_tick_beat_heart_flag(U32 ch,U32 invent)
{
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			return 0;
		}
	}
	return 0;
}




void L2_time_show_tick(U8 ch)
{	
	#if 0
	if (s_time0.tmp != s_time0.t_10ms)
	{
		s_time0.tmp = s_time0.t_10ms;
		if(0 == s_time0.tmp%100)
		{
			//L0_debug_show_ul("\r\nt =\0x00",s_time0.tmp/100); 
			L0_putstr(0x09);L0_putstr('t');L0_send0_uc_hex(ch);
			L0_send0_uc('=');L0_send0_Aul(s_time0.tmp/100);
		}
	}	

	if(1 == s_time0.t1s_flag)
	{s_time0.t1s_flag = 0;
		//L0_debug_show_ul("\r\nt =\0x00",s_time0.tmp/100); 
		L0_putstr(0x09);L0_send0_uc('t');L0_send0_uc_hex(ch);
		L0_send0_uc('=');L0_send0_Aul(s_time0.t_10ms/100);
	}

	if(1 == s_time0.t1s_flag)
	{s_time0.t1s_flag = 0;
		if(0 == (s_time0.t_1s%D_showtick_value))
		{
			L0_putstr("\r\nt");L0_send0_uc_hex(ch);
			L0_send0_uc('=');L0_send0_Auc(s_time0.t_1s/60/60);L0_send0_uc('h');
			L0_send0_uc('=');L0_send0_Auc(s_time0.t_1s/60);	L0_send0_uc('m');
			L0_send0_uc(':');L0_send0_Auc(s_time0.t_1s%60);L0_send0_uc('s');
			L0_send0_uc_hex((U8)s_time0.tmp);
		}
	}

//	#else
	U32 m,n; 
	
#define D_showtick_value	5	
	
	

	if(1 == s_nos_tick.t1s_flag)
	{//s_nos_tick.t1s_flag = 0;
		if(0 == (s_nos_tick.t_1s%D_showtick_value))
		{

			s_nos_tick.m = (U8)(s_nos_tick.time_left/100/60/60);
			s_nos_tick.h = s_nos_tick.time_left/100/60 - s_nos_tick.m*60;



		L0_USART_print(UART_debug,"\r\n ",m,s_nos_tick.time_left/100/60-m*60;);

			
		L0_putstr("\r\nCH");L0_send0_uc_hex(ch);//			L0_send0_Aul();
			L0_send0_uc('\t');L0_send0_Auc(m);
			n=s_nos_tick.time_left/100/60-m*60;
			L0_send0_uc(':');L0_send0_Auc(n);
			L0_send0_uc(':');L0_send0_Auc((s_nos_tick.time_left/100)%60);
			L0_send0_uc(0x09);
			L0_send0_uc_hex((U8)s_nos_tick.tmp);
			s_nos_tick.ts_flag = 1;
			L0_send0_uc(0x09);

			L0_USART_print(UART_debug,x);

			
		}
	}
	#endif
}
*/


#endif	//#if 0	///<1213123


#if 0	///<1213123


/*********************************************************************************************************
** Function name:	    delayNS
** Descriptions:	    ��ʱ����
** input parameters:    ulDly:   ֵԽ����ʱʱ��Խ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void delayNS (U32 ulDly)
{
    U32 i; 
    
    for (; ulDly > 0; ulDly--) {
        for (i = 0; i < 50000; i++);
    }
}

/*

#if 0

LPC_SC->PCONP |= (1<<1);                       //�򿪹��ʿ���  
      
    LPC_TIM0->TCR |= (1<<1);                       //��λ��ʱ��  
    LPC_TIM0->PR   = 0x00;                           //Ԥ��Ƶ����  
    LPC_TIM0->MR0  = 10000;                          //ƥ��Ĵ����붨ʱ��������ֵ��Ƚ�  
    LPC_TIM0->IR  |= 0XFF;                           //�������жϱ�־λ  
    LPC_TIM0->MCR |= ((1<<1)|(1<<0));                //MR0��TCֵƥ��ʱ�������ж�,TC��λ  
    LPC_TIM0->TCR  = (1<<0);                       //������ʱ��  
  
    NVIC_EnableIRQ(TIMER0_IRQn);                    // enable irq in nvic             // 
	T0PR = 99;				 // ���ö�ʱ��0��ƵΪ100��Ƶ����160000Hz ���� 16M

#endif


void L0_timer0_Init (void)
{

}

// s_nos_tick.t1s_flag[1]




// ��ʱ����:  ���ȶ���ĳ��ͨ��ch Ȼ����t_1s ��invent����  ,�����ִ��*fun()   
void L2_time_beat_heart_fun(U32 ch,U8 invent,void (*fun)(void))
{
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			fun();
		}
	}
}


// ��ʱ����:  ���ȶ���ĳ��ͨ��ch Ȼ����t_1s ��invent����  ,�����ִ��*fun()   
U32 L2_time_beat_heart_flag(U32 ch,U32 invent)
{
	if(1 == s_nos_tick.t1s_flag[ch])
	{s_nos_tick.t1s_flag[ch] = 0;
		if(0 == (s_nos_tick.t_1s%invent))
		{
			return 0;
		}
	}
	return 0;
}




void L2_time_show_tick(U8 ch)
{	
	#if 0
	if (s_time0.tmp != s_time0.t_10ms)
	{
		s_time0.tmp = s_time0.t_10ms;
		if(0 == s_time0.tmp%100)
		{
			//L0_debug_show_ul("\r\nt =\0x00",s_time0.tmp/100); 
			L0_putstr(0x09);L0_putstr('t');L0_send0_uc_hex(ch);
			L0_send0_uc('=');L0_send0_Aul(s_time0.tmp/100);
		}
	}	

	if(1 == s_time0.t1s_flag)
	{s_time0.t1s_flag = 0;
		//L0_debug_show_ul("\r\nt =\0x00",s_time0.tmp/100); 
		L0_putstr(0x09);L0_send0_uc('t');L0_send0_uc_hex(ch);
		L0_send0_uc('=');L0_send0_Aul(s_time0.t_10ms/100);
	}

	if(1 == s_time0.t1s_flag)
	{s_time0.t1s_flag = 0;
		if(0 == (s_time0.t_1s%D_showtick_value))
		{
			L0_putstr("\r\nt");L0_send0_uc_hex(ch);
			L0_send0_uc('=');L0_send0_Auc(s_time0.t_1s/60/60);L0_send0_uc('h');
			L0_send0_uc('=');L0_send0_Auc(s_time0.t_1s/60);	L0_send0_uc('m');
			L0_send0_uc(':');L0_send0_Auc(s_time0.t_1s%60);L0_send0_uc('s');
			L0_send0_uc_hex((U8)s_time0.tmp);
		}
	}

//	#else
	U32 m,n; 
	
#define D_showtick_value	5	
	
	

	if(1 == s_nos_tick.t1s_flag)
	{//s_nos_tick.t1s_flag = 0;
		if(0 == (s_nos_tick.t_1s%D_showtick_value))
		{

			s_nos_tick.m = (U8)(s_nos_tick.time_left/100/60/60);
			s_nos_tick.h = s_nos_tick.time_left/100/60 - s_nos_tick.m*60;



		L0_USART_print(UART_debug,"\r\n ",m,s_nos_tick.time_left/100/60-m*60;);

			
		L0_putstr("\r\nCH");L0_send0_uc_hex(ch);//			L0_send0_Aul();
			L0_send0_uc('\t');L0_send0_Auc(m);
			n=s_nos_tick.time_left/100/60-m*60;
			L0_send0_uc(':');L0_send0_Auc(n);
			L0_send0_uc(':');L0_send0_Auc((s_nos_tick.time_left/100)%60);
			L0_send0_uc(0x09);
			L0_send0_uc_hex((U8)s_nos_tick.tmp);
			s_nos_tick.ts_flag = 1;
			L0_send0_uc(0x09);

			L0_USART_print(UART_debug,x);

			
		}
	}
	#endif
}
*/


#endif	//#if 0	///<1213123





