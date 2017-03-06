/*****************************************************************************
 *   DEBUG_DRV.h:  Header file for  DEBUY DRIVER FILES
 *
 *
 *   Copyright(C) 2013, cc
 *   All rights reserved.
 *
 *   History
 *   2013.05.24  ver 1.00    Prelimnary version, first Release

******************************************************************************/
#ifndef __DEBUG_DRV_H 
#define __DEBUG_DRV_H

#include "../clib/type.h"
#include "../clib/clib.h"
//#include "../uartcom/uartlib.h"	
#include "../msp/uart0.h"
#include "debug_led.h"

void L3_debug_drv_init(void);
#define L3_debug_time() Lc_print_buf("\r\n%s,-%sL:%d,",__DATE__,__TIME__,__LINE__);
void extern L3_debug_cycle(void);

#if 0

#define UART_debug_reg	((LPC_UART1_TypeDef     *) LPC_UART1_BASE    )
//#define UART_debug	((LPC_UART1_TypeDef     *) LPC_UART1_BASE    )
//#define UART_debug	((LPC_UART_TypeDef     *) LPC_UART_BASE    )
//#define UART_debug	((LPC_UART_TypeDef     *) LPC_UART_BASE    )
#define UART_debug	1

#define L0_debugS_uc(x)				//L0_Usend_uc(UART_debug,x)
#define L0_debugS_uc_hex(x)			//L0_Usend_uc_hex(UART_debug,x)
#define L0_debug_uc_show(x,y); 		//L0_USART_print(UART_debug,x,y);
#define L0_debug_us_show(x,y); 		//L0_USART_print(UART_debug,x,y);
#define L0_debug_ul_show(x,y); 		//L0_USART_print(UART_debug,x,y);


//#define L2_debug_info(x) 				//L0_USART_print(UART_debug,x);
#define L2_debug_Au4B(x) 		//		L0_Usend_Au4B(UART_debug,x)
#define L0_debug_Au4B_show(x,y); 	//L0_USART_print(UART_debug,x,y);
#define L0_debug_Aus_show(x,y); 	//L0_USART_print(UART_debug,x,y);
#define L0_debug_A4B_show(x,y); 	//L0_USART_print(UART_debug,x,y);


//#define debug22(format...) 		Lc_print("%s (%d): ",__FILE__,__LINE__);

//#define LOG(format, args...) 	Lc_print(format, ##args)
//#define RTA_printf(...) Lc_print(__VA_ARGS__)

//#define L2_debug_info 	Lc_print

//#define L3_debug_time() Lc_print(L0_uart0_uc,"\r\n%s,-%sL:%d,",__DATE__,__TIME__,__LINE__);




#define L2_debug_info(...)			\
Lc_print(L0_uart_uc,__VA_ARGS__);

//do {
//Lc_print("%s (%d): ", __FILE__, __LINE__);
//Lc_print(format, __VA_ARGS__);
//} while (0)


#define CHECK1(x, ...) if (!(x)) { printf(__VA_ARGS__); }

#define LOG(...)  {\
    Lc_print(L0_uart_uc,"%s: Line %d:\t", __FILE__, __LINE__);\
    Lc_print(L0_uart_uc, __VA_ARGS__);\
    Lc_print(L0_uart_uc,"\n");\
}  

int main() {  
    int x = 3;  
    // Ò»Ð©´úÂë...  
    LOG("x = %d", x); // 2-1-5.cpp: Line 12:     x = 3 
}  
#endif
#endif /* end __DEBUG_DRV_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
