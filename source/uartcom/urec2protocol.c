
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



#include "urec2protocol.h"
/*
void L1_UProtocol_init(void)
{
	//L0_UARTcom0_Init();


}

*/
/// ÔÚ´®¿ÚÖÐ¶ÏÖÐµ÷ÓÃ uart hardware to buffer  ´®¿Úµ½»º´æÖÐ
void L1_uart_2hexbuf(struct _s_protocol_ *p)
{
//		unsigned int i;
		//p->cashe[3] = p->cashe[2];
		//p->cashe[2] = p->cashe[1];
		p->cashe[1] = p->cashe[0];
		p->cashe[0] = p->pfun_get();// 
		//p->cashe[0] = SBUF;// 
		//D_led_debug_REV();
	//	p->ok = 1;
		//	D_led_D2_ON();D_led_D2_OFF();D_led_D2_ON();
		if (p->head||((p->cashe[0] == p->filter1)&&(p->cashe[1] == p->filter2)))
		{		// p->ok = 1;//ÊÕµ½ ±êÖ¾ÖÃ1	; 55 aa 44 55
			p->head = 1;
			p->num ++;			
			p->buf[p->num] = p->cashe[0];	
			if(p->num >= D_s_protocol_len)
			{
				p->num = 0;
			}
			//D_led_D2_OFF();

			if(p->num > 8)
			{// protect
				p->head = 0;p->ok = 0;p->num = 0; 
				{
					//while(9)
					{
						//	D_led_D1_ON();D_led_D1_REV();D_led_D1_ON();	D_led_D2_ON();D_led_D2_REV();D_led_D2_ON();
					}
				}

			}else
			{
				if (p->num >= (p->buf[2]+2))
				{// aa 55 (03) 11 22 33
				
					if (p->ok != 1)
					{	  
					//	D_led_D2_ON();
						p->buf[0] = p->filter2;
						p->ok = 1;//ÊÕµ½ ÃüÁî½áÊø,±ØÐëÓÐ¸öµØ·½Çå0£¬·ñÔòÎÞ·¨ÔÙ´Î½ÓÊÜ±¨ÎÄ
					//	D_led_D2_OFF();
					}		
					p->num = 0; 	//·ÅÔÚif (p->ok != 1) Íâ
					p->head = 0;	//·ÅÔÚif (p->ok != 1) Íâ
				}


			}

		}
		else {} 
}
//L1_uart_2strbuf(&s_at0);
void L1_uart_2strbuf(struct _s_protocol_ *p)
{
//		unsigned int i;
		//p->cashe[3] = p->cashe[2];
		//p->cashe[2] = p->cashe[1];
		p->cashe[1] = p->cashe[0];
		p->cashe[0] = p->pfun_get();// 		
		p->buf[p->num] = p->cashe[0];	
		p->num ++;	
		if(p->num >= D_s_protocol_len)
		{
			p->num = 0;
		}
		if ((p->cashe[0] == p->filter1)&&(p->cashe[1] == p->filter2))// 0d0a
		{	//               0a                 0d
			p->max = p->num;
			p->buf[p->max] = 0;
			if(0 == p->ok)
			{
				for(;0 != p->num;p->num --)
				{
					p->array[p->num] = p->buf[p->num];
				}
				p->array[0] = p->buf[0];
			}
			p->ok = 1;//ÊÕµ½ ÃüÁî½áÊø,±ØÐëÓÐ¸öµØ·½Çå0£¬·ñÔòÎÞ·¨ÔÙ´Î½ÓÊÜ±¨ÎÄ
			p->num = 0;		
		}
}


/******************************************************************************
**                            End Of File
******************************************************************************/
