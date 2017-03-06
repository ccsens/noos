/*****************************************************************************
 *   uart.c:  UART API file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "type.h"
#include "clib.h"

#include <string.h>
#include "../msp/uart0.h"
#include "../msp/time.h"
//extern int strpos (  const char *string,char c);  
//char s_send_bath.buf[128];

void Lc_delay_us(vU16 i)
{
	vU16 m;
	i=i/10;
	for(m=i;m>0;m--)
	{
		Lc_delay_1us();
	}
}
//	D_1ms_delay_para
void Lc_delay_ms(vU16 i)
{
	vU16 m,n;
	for(m = 0;m < i;m++)
	{
		#ifdef D_debug_sim
		
		#else
		for(n = 0;n < 180; n++)
		{
			NOP();
		}
		#endif
	}
}
///  cguHex2Char[0][0] = 0x00  cguHex2Char[0][1] = 0x30  
unsigned char code cguHex2Char[16][2]
={
	0x00,'0',
	0x01,'1',
	0x02,'2',
	0x03,'3',
	0x04,'4',
	0x05,'5',
	0x06,'6',
	0x07,'7',
	0x08,'8',
	0x09,'9',
	0x0A,'A',
	0x0B,'B',
	0x0C,'C',
	0x0D,'D',
	0x0E,'E',
	0x0F,'F'
};

//  0--9   '0'
//      ABCEDF------0X41-- 87-6= 81
U8 Lc_Hex2Char(U8 CharStr)
{             
	U8  rd;	
	if (CharStr >9)//A   10-9+
	{
		rd = (CharStr - 10 + 'A') ; 
	}
	else
	{
		rd = (CharStr + '0') ; 
	}
	return rd;
}  
// 0x30'0'----'9'--> 0x0----0x09
//0x61--'a'---'f'--> 0x0a---0x0f 
//0x41 'A'--'F'--> 0x0a---0x0f
U8 Lc_Char2Hex(U8 CharStr)
{             
	U8  rd;	
	if (CharStr >= 'a')//0x61--'a'---'f'--> 0x0a---0x0f 
	{
		rd = (CharStr - 'a' + 0x0a) ; 
	}
	else if (CharStr >= 'A')//0x61--'a'---'f'--> 0x0a---0x0f 
	{
		rd = (CharStr - 'A' + 0x0a) ; 
	}
	else
	{
		rd = (CharStr - '0') ; 
	}
	return rd;
}  
//catch_protocol(s,d);
// �� d����ȡ��Э��,һ������Э������ĵ��Ժ�͸��,
// *s="iicsend:12 34 56 78 9a \r\n";
//  i:         012345678
// ����Э���ֽ�����
// extern int strpos (const char *s, char c);
unsigned char catch_protocol (const char *d_src,char d_protocol[]) 
{
	unsigned char n = 0,len = 0;//,i = 0;
	int i = 0;
	i = strpos(d_src, (char)':');
	i ++;
	len = strlen (d_src) - 2;
	while(i < len)
	{
		d_protocol[n] = Lc_Char2Hex(*(d_src+i))*16;
		i ++;
		d_protocol[n] += Lc_Char2Hex(*(d_src+i));
		i ++;i ++;
		n ++;
	}
	return n;
}
void Lc_buf_copy_uc(U8 *d,const U8 *s,U8 num)
{
	U8 i;
	for(i = 0; i < num; i ++)
	{
		*(d+i) = *(s+i);
	}

}


char *strstr(const char *str1, const char *str2)
{
    char *cp = (char*)str1;
    char *s1, *s2;
 
    if (!*str2)
        return((char *)str1);
 
    while (*cp)
    {
        s1 = cp;
        s2 = (char *)str2;
 
        while (*s1 && *s2 && !(*s1 - *s2))
            s1++, s2++;
 
        if (!*s2)
            return(cp);
 
        cp++;
    }
    return(NULL);
}
/*
 * ��������itoa  ��ͬ���͵�cpu��һ�� ����֧�ֵ��������ȡ����i = 1000000;
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART1_printf()����
 */
char *Lc_int2a(vS32 value, char *string, UN_TYPE radix)
{
	vS32     i, d;
	UN_TYPE     flag = 0;
	vU16    U16temp = 0;
	char    *ptr = string;
	
	/* This implementation only works for decimal numbers. */
	//value	
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}
	U16temp = value;
	switch(radix)
	{//%X2 %X4 %X6
		case '2':
			*ptr++ = Lc_Hex2Char((U16temp>>4)&0x0f);
			*ptr++ = Lc_Hex2Char((U16temp)&0x0f);
	    	*ptr = 0;
			return string;
			break;
		case '4':
			*ptr++ = Lc_Hex2Char((U16temp>>12)&0x0f);
			*ptr++ = Lc_Hex2Char((U16temp>>8)&0x0f);			
			*ptr++ = Lc_Hex2Char((U16temp>>4)&0x0f);
			*ptr++ = Lc_Hex2Char((U16temp)&0x0f);
	    	*ptr = 0;	
			return string;		
			break;
			#if 0
		case '8':
			*ptr++ = Lc_HexToChar((value>>24)&0x0f);
			*ptr++ = Lc_HexToChar((value>>20)&0x0f);			
			*ptr++ = Lc_HexToChar((value>>16)&0x0f);
			*ptr++ = Lc_HexToChar((value>>12)&0x0f);
			*ptr++ = Lc_HexToChar((value>>8 )&0x0f);			
			*ptr++ = Lc_HexToChar((value>>4 )&0x0f);
			*ptr++ = Lc_HexToChar((value)&0x0f);
	    	*ptr = 0;	
			return string;
			break;
			#endif
		case 10:
			/* if this is a negative value insert the minus sign. */
			if (value < 0)
			{
					*ptr++ = '-';
			
					/* Make the value positive. */
					value *= -1;
			}
			i = 1000000; 
			if (value > i)
			{
				value = i;
			}
			for (;i > 0; i /= 10)
			{
					d = value / i;
			
					if (d || flag)
					{
							*ptr++ = (char)(d + 0x30);
							value -= (d * i);
							flag = 1;
					}
			}
			
			/* Null terminate the string. */
			*ptr = 0;
			
			return string;			
			break;		
		default:
			*ptr++ = 0x30;
			*ptr = 0;
			return string;
			break;
	}


} /* NCL_Itoa */
//void (*L0_uart0_uc)(U8 ww);


/******************************************************************** 
*
* ����: L0_Usend_uc_hex
* ˵��: ����:L0_Usend_uc_hex(0x0c); output " 0c  " 
* ����: ��������
* ����: SendHUc����Lc_HexToChar����
* ����:
* ����ֵ: ��
***********************************************************************/
void Lc_uc_hex(char ww)
{
	L0_uart0_uc(Lc_Hex2Char((ww>>4)&0x0f));
	L0_uart0_uc(Lc_Hex2Char(ww&0x0f));		
}

void Lc_us_hex(U16 ww)
{//
	U8 t;	
	t = (U8)(((ww >> 8)&0x00ff));
	Lc_uc_hex(t);
	t = (U8)(((ww )&0x00ff));
	Lc_uc_hex(t);		
}

//#ifdef D_use_uart_buf


//  ��buf��printf  fixme:  ��Ҫ����ط� 
void Lc_print_buf(char *dat4,...)
{
	const char *s;
	vS32 d;   
	char buf[16];
	char n = 0;
	char *dat = 0;
	va_list ap;//va_list ��һ���ַ�ָ�룬�������Ϊָ��ǰ������һ��ָ�룬
	//ȡ�α���ͨ�����ָ����С�
//<Step 1> �ڵ��ò�����֮ǰ������һ�� va_list ���͵ı�����
//(����va_list ���ͱ���������Ϊap)��
	va_start(ap, dat);
//	Ȼ��Ӧ�ö�ap ���г�ʼ��������ָ��ɱ����������ĵ�һ��������
//����ͨ�� va_start ��ʵ�ֵģ���һ�������� ap �����ڶ�����������
//��α�ǰ������ŵ�һ������,����...��֮ǰ���Ǹ�������

	dat = dat4;
//	<Step 3> Ȼ���ǻ�ȡ����������va_arg�����ĵ�һ��������ap��
//�ڶ���������Ҫ��ȡ�Ĳ�����ָ�����ͣ�Ȼ�󷵻����ָ�����͵�ֵ��
//���Ұ� ap ��λ��ָ���α����һ������λ�ã�
	//"e645654675y73\0"
	while ( *dat != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *dat == 0x5c )  //'\'
		{									  
			switch ( *++dat )
			{
				case 'r':							          //�س���
					s_send_bath.buf[n ++] = 0x0d;//L0pf_send_uc(0x0d);
					dat ++;
				break;
				
				case 'n':							          //���з�
					s_send_bath.buf[n ++] = 0x0a;//L0pf_send_uc(0x0a);	
					dat ++;
				break;

				case 't':							          // 
					s_send_bath.buf[n ++] = 0x09;//L0pf_send_uc(0x09);	
					dat ++;
				break;				
				default:
					dat ++;
				break;
			}			 
		}
		else if ( *dat == '%')
		{									  //
			switch ( *++dat )
			{			
				case 'C':
				case 'c':										  //�ַ�
				//va_arg()���������Ǹ���ָ���Ĳ�������
				//ȡ�ñ�������ֵ�����Ұ�ָ�������һ
				//����������ʼ��ַ
				//#define va_arg(ap,t) 
				//( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) ) 

				//char *ap;   %c  " , 0x30,
					s = va_arg(ap, const char *);			//	0x30
					s_send_bath.buf[n ++] = (char)s;//	L0pf_send_uc((char)s);		//	'0'
					dat++;
				break;		
				case 'd':										//ʮ����
					//" %d",0x30,
					//" %d",48,
					// int i = 48;
					//" %d",i,

					d = va_arg(ap, int);		// 0x30 =48d
					Lc_int2a(d, buf, 10);			//"buf="48"  buf[0]='4'  buf[1]='8'
					for (s = buf; *s; s++) 			// "48"----'4'--'8'   '\0'--*s
					{			//\0
						s_send_bath.buf[n ++] = *s;//L0pf_send_uc(*s);
						//printf("%c",*s);
					}
					dat++;
				break;
				case 'X':				
				case 'x':										  //�ַ���
					d = va_arg(ap, int);		// 0x30 =48d
					dat++;//%X2 %X4 %X8
					Lc_int2a(d, buf, *dat);			//"buf="48"  buf[0]='4'  buf[1]='8'
					for (s = buf; *s; s++) 			// "48"----'4'--'8'   '\0'--*s
					{			//\0
						s_send_bath.buf[n ++] = *s;//L0pf_send_uc(*s);
					}
					dat++;
				break;			
				case 'S':				
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
					for ( ; *s; s++) 
					{
						s_send_bath.buf[n ++] = *s;//L0pf_send_uc(*s);
					}
					dat++;
				break;
				case 'f':										//ʮ����
					d = va_arg(ap, int);
					Lc_int2a(d, buf, 10);
					for (s = buf; *s; s++) 
					{
						s_send_bath.buf[n ++] = *s;//L0pf_send_uc(*s);

					}
					dat++;
				break;
				default:
					dat++;
				break;
			}		 
		} /* end of else if */
		else 
		{
			s_send_bath.buf[n ++] = (*dat++);//L0pf_send_uc( *dat++);
		}
	}//end while....
	s_send_bath.max = n;
	L0_uart0_sendbuf();

	
}//
void Lc_print_NC(char *dat,...)
{

}
//#else//#ifdef D_use_uart_buf
// �ǻ���ģʽ�Ĵ�ӡ fixme: ����16��������ʱ��bug
void Lc_print(char *dat4,...)
{
	const char *s;
	vS32 d;   
	char buf[16];//char t;
		char *dat = NULL;
	va_list ap;//va_list ��һ���ַ�ָ�룬�������Ϊָ��ǰ������һ��ָ�룬
	//ȡ�α���ͨ�����ָ����С�
//<Step 1> �ڵ��ò�����֮ǰ������һ�� va_list ���͵ı�����
//(����va_list ���ͱ���������Ϊap)��
	va_start(ap, dat4);
//	Ȼ��Ӧ�ö�ap ���г�ʼ��������ָ��ɱ����������ĵ�һ��������
//����ͨ�� va_start ��ʵ�ֵģ���һ�������� ap �����ڶ�����������
//��α�ǰ������ŵ�һ������,����...��֮ǰ���Ǹ�������
dat =dat4;
//	<Step 3> Ȼ���ǻ�ȡ����������va_arg�����ĵ�һ��������ap��
//�ڶ���������Ҫ��ȡ�Ĳ�����ָ�����ͣ�Ȼ�󷵻����ָ�����͵�ֵ��
//���Ұ� ap ��λ��ָ���α����һ������λ�ã�
	//"e645654675y73\0"
	while ( *dat != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *dat == 0x5c )  //'\'
		{									  
			switch ( *++dat )
			{
				case 'r':							          //�س���
					L0_uart0_uc(0x0d);
					dat ++;
				break;
				
				case 'n':							          //���з�
					L0_uart0_uc(0x0a);	
					dat ++;
				break;

				case 't':							          // 
					L0_uart0_uc(0x09);	
					dat ++;
				break;				
				default:
					dat ++;
				break;
			}			 
		}
		else if ( *dat == '%')
		{									  //
			switch ( *++dat )
			{			
				case 'C':
				case 'c':										  //�ַ�
				//va_arg()���������Ǹ���ָ���Ĳ�������
				//ȡ�ñ�������ֵ�����Ұ�ָ�������һ
				//����������ʼ��ַ
				//#define va_arg(ap,t) 
				//( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) ) 

				//char *ap;   %c  " , 0x30,
					s = va_arg(ap, const char *);			//	0x30
						L0_uart0_uc((char)s);		//	'0'
					dat++;
				break;		
				case 'd':										//ʮ����
					//" %d",0x30,
					//" %d",48,
					// int i = 48;
					//" %d",i,  //#define va_arg(ap,t) (((t *)ap)++[0])  //(((int *)ap)++[0])

					d = va_arg(ap, int);		// 0x30 =48d
					d >>= 8;
					Lc_int2a(d, buf, 10);			//"buf="48"  buf[0]='4'  buf[1]='8'
					for (s = buf; *s; s++) 			// "48"----'4'--'8'   '\0'--*s
					{			//\0
						L0_uart0_uc(*s);
						//printf("%c",*s);
					}
					dat++;
				break;
				case 'X':				
				case 'x':										  //�ַ���
					d = va_arg(ap, int);		// 0x30 =48d
					d >>= 8;
					dat++;//%X2 %X4 %X8
					Lc_int2a(d, buf, *dat);			//"buf="48"  buf[0]='4'  buf[1]='8'
					for (s = buf; *s; s++) 			// "48"----'4'--'8'   '\0'--*s
					{			//\0
						L0_uart0_uc(*s);
					}
					dat++;
				break;			
				case 'S':				
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
					for ( ; *s; s++) 
					{
						L0_uart0_uc(*s);
					}
					dat++;
				break;
				case 'f':										//ʮ����
					d = va_arg(ap, int);
					Lc_int2a(d, buf, 10);
					for (s = buf; *s; s++) 
					{
						L0_uart0_uc(*s);

					}
					dat++;
				break;
				default:
					dat++;
				break;
			}		 
		} /* end of else if */
		else 
		{
			L0_uart0_uc(*dat ++);
			//t = *dat;
			//L0pf_send_uc = L0_uart0_uc;
			//L0pf_send_uc(t);
			//L0_uart0_uc(t);
			//dat++;
		}
	}//end while....˹�ٷ�
}//

//#endif//#ifdef D_use_uart_buf

///����CRCУ����	
unsigned int CRC16(unsigned char *ptr, unsigned char len)
{
   unsigned int crc=0xffff;
   unsigned char i;
   while(len--)
   {
       crc ^=*ptr++;
       for(i=0;i<8;i++)
	   {
	       if(crc & 0x1)
		   {
		      crc>>=1;
			  crc^=0xa001;
		   }
		   else
		   {
		      crc>>=1;
		   }
	   }
   }
   return crc;
}
///���CRCУ�����Ƿ���ȷ
unsigned char CheckCRC(unsigned char *ptr,unsigned char len)
{
	unsigned int crc;
	crc = (unsigned int)CRC16(ptr,(len-2));
	if(ptr[len-1]==(crc>>8) && ptr[len-2]==(crc & 0x00ff))
	{
		return 0xff;
	}
	else
	{
		return 0x0;
	}
}
#ifdef doc_sdfjaskdjf3423
void L3_us_big(U16 *d)
{
	tu_us2uc tu,ta;
	tu.us = *d;
	ta.d[0] = tu.d[1];
	ta.d[1] = tu.d[0];
	*d = ta.us;
}

//void L3_ui_big(__packed INT32U *d)
void L3_ui_big(vU32 *d)
{
	tu_ui4uc tu,ta;
	tu.ui = *d;
	ta.d[0] = tu.d[3];
	ta.d[1] = tu.d[2];
	ta.d[2] = tu.d[1];
	ta.d[3] = tu.d[0];
	*d = ta.ui;
}
#endif




