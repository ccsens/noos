/*****************************************************************************
 *   uart.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef _CLIB_H_ 
#define _CLIB_H_


#include <stdarg.h>
#include <stdlib.h>
#include "../bsp/hard_config.h"
//#include "../clib/Clib.h"
//#include "../debug/debug_drv.h"
//extern char guc_send[128];
extern unsigned char code cguHex2Char[16][2];

extern U8 Lc_Hex2Char(U8 CharStr);
//extern void Lc_int2str(U32 ui_in,UN_TYPE len,UN_TYPE point,char *d);

// input:  123456d
// output: '1' '2'  '3'.... 
//对应的点阵 为 0123456789. ，最后为空格，专为显示点阵类的数值使用
//extern void Lc_int2number(U32 ui_in,UN_TYPE len,UN_TYPE point,char *d);
//extern U32 L2_fun_number_show(int i,char str[4]);
#if 0

struct _s_temp_
{
	U8 d[16];

};

extern struct _s_temp_ s_temp22;
extern U8 s_temp[16];

extern U32 ul2fun2[10];
extern void Lc_Byte_cp(BYTE *src,BYTE *dis, int len);

extern void L1_buf22ui(volatile BYTE in[],vU32 *ui_t2,vU32 *ui_t3);

extern void Lc_2ui2buf(vU32 ui_t2,vU32 ui_t3,volatile BYTE out[]);
extern void Lc_int2str_3(U32 ui_in,char *d);
extern U32 Lc_abs(vU32 a,vU32 b,vU32 *diff);
extern void Lc_int2str_4(U32 ui_in,char *d);

extern void Lc_sint2str_3(int i_in,char *d);
#define Lc_WEI(WEIx,WEIn)	(U8)((WEIx/ul2fun2[WEIn])%10); 
#define Lc_eee(WEIn)		ul2fun2[WEIn]


#endif

extern char *Lc_int2a(vS32 value, char *string, UN_TYPE radix);
extern char *strstr(const char *str1, const char *str2);
extern unsigned char catch_protocol (const char d_src[],char d_protocol[]) ;
#define Lc_delay_1us()	L0_delay_1us()


extern void Lc_delay_us(vU16 i);
extern void Lc_delay_ms(vU16 i);

////////////////


//extern void (*L0_uart0_uc)(char ww);

extern void Lc_uc_hex(char ww);
extern void Lc_us_hex(U16 ww);	
//extern void Lc_print(void (*L0pf_send_uc)(char ww), char *dat,...);
extern void Lc_print(char *dat4,...);
extern void Lc_print_NC(char *dat,...);
extern void Lc_print_buf(char *dat4,...);

//extern void L0_uart0_uc(U8 ww);
//#define Ld_print	Lc_print
#define Ld_print	Lc_print_NC
//#define Ldi_print	L0pf_send_uc = L0_uart0_uc;Lc_print
//#define Ldi_print		Lc_print
#define Ldi_print		Lc_print_NC	

extern void L3_us_big(U16 *d);
extern void L3_ui_big(vU32 *d);
extern void Lc_buf_copy_uc(U8 *d,const U8 *s,U8 num);
#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
