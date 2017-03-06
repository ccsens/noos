

/*****************************************************************************
update by cc @201700110
Õë¶Ô¶à´®¿Ú ºÍ µ¥Ò»´®¿Ú ÓĞÇø±ğ Ã¿¸ö´®¿ÚÊÇ¶ÀÁ¢µÄ»¹ÊÇ·Ö¿ªµÄÓĞ½²¾¿ ³ÌĞòÊÇ¸´ÔÓµÄ»¹ÊÇÈí¼şÓ¦ÓÃ¼òµ¥ÊÇ
¸öĞèÒªÆ½ºâµÄÊÂÇé.

clib/clib.c:  
¹«ÓÃµÄº¯Êı 	ºÍÓ²¼şÎŞ¹Ø 
·ÅÖÃ´®ĞĞÄ£Ê½(´®¿ÚµÈÆäËûÍ¨Ñ¶×ÜÏßÀàµÄÊä³ö)Êä³öµÄº¯Êı,
Ò»Ğ©¸²¸ÇÄ£Ê½Êä³öµÄ(lcdµÈ¹ÌÆÁÊä³öµÄ)µÄÒ²¿ÉÊ¹ÓÃ  
					void Lc_print(void (*L0pf_send_uc)(char ww), char *dat,...)
-----------------------------------------------------------------------------------------
uartcom/Uprotocol2app  
  Ğ­Òéµ½Ó¦ÓÃ
  ÎªÁËÊÊÓ¦²»Í¬µÄÍ¨Ñ¶Ğ­ÒéĞèÒª²»Í¬µÄuart¿ÚÀ´¶ÔÓ¦ ºÍÓ¦ÓÃÏà¹Ø

typedef struct _ts_lcm_pro_; Ó¦ÓÃĞ­Òé°üµÄ¶¨Òå¼     LCMµÄĞ­Òé------------
											L3_UARTcom0_exp_protocol ½âÎöÓ¦ÓÃĞ­Òé
-----------------------------------------------------------------------------------------
uartcom/urec2protocol: ½ÓÊÕµ½µÄÊı¾İ·ÅÈëµ½Ö¸ÏòÌØ¶¨Ğ­ÒéµÄ»º´æÖĞ£¬ºÍĞ­ÒéµÄ¸ñÊ½ÓĞ¹Ø Ò»°ã·ÖÎª ±êÍ·Ê½»òÕß±êÎ²Ê½
¹«ÓÃµÄ´®¿ÚÍ¨Ñ¶¶¨Òå		
 	struct _s_protocol_ µÄ¹«¹²Ğ­Òé°ü(¹Ø¼üµÄ½á¹¹Ìå)µÄÉùÃ÷------struct _s_protocol_
 							void L1_uart_2buf(struct _s_protocol_ *p)´®ĞĞÊı¾İ±£´æµ½Ö¸ÏòÌØ¶¨Ğ­ÒéµÄ»º³åÖĞ
--------------------------------------------------------------------------------------------
msp/uartx.c    µ×²ã´úÂë	 ºÍcpuÏà¹Ø »º´æ·¢ËÍÒ²·ÅÔÚÀïÃæ
			L0_UART0_Init
						UART0_IRQHandler
						    	L0_Usend_uc------UserDef
-----------------------------------------------------------------------------------------
********************************************************************************/


#ifndef __uprotocol2app_H 
#define __uprotocol2app_H

#include "urec2protocol.h"
//#include "../debug/debug_drv.h"	
#include "../ctask/task.h"	


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//#define Array_ts_cmd_pro0  ((unsigned char *) &ts_cmd_pro0)
//#define Array_ts_cmd_pro0_temp  ((unsigned char *) &ts_cmd_pro0_temp)  


//L0_type_byte(ts_cmd_pro0)[]
//#define D_CMD_Filter1 	0xA5
//#define D_CMD_Filter2 	0x5A
#define D_CMD_Filter1 	0x0a
#define D_CMD_Filter2 	0x0d

#define D_CMD_cmd_write	 	0x90
//a5 5a 210 90 ......
#define D_CMD_cmd_adc	 	0x53
#define D_CMD_cmd_G5V	 	0x52	//¼ÌµçÆ÷´ò¿ª

typedef struct 
{//8byte
    U8 Filter1;	//Ö¡ Í· 
    U8 Filter2;	//Ö¡ Í· 
	U8 len;     //Êı¾İ³¤¶È
    U8 cmd; 	//ÃüÁî    
    U8 dat[(52+11)*4]; //Êı¾İ //fixme 
    vU16 ocr; //Ö¸ÁîºÍÊı¾İµÄCRC Ğ£Ñé 
}Ts_cmd_pro;

extern void L1_uart0_rx_handle(void);
extern struct _s_protocol_ s_at0;
extern void L3_UARTcom0_exp_protocol(struct _s_protocol_ *p);
extern void L0_UARTcom_Init(struct _s_protocol_ *p);


#endif /* end __uprotocol2app_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
