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
/// Descriptions:	
//////////////////////////////////////////////////////////////////////////


//#include <stdint.h>

#ifndef __TYPE_H__
#define __TYPE_H__

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif
/*********************************************************************************************************
  ������������޹ص���������
*********************************************************************************************************/

typedef unsigned char 		u8;
typedef unsigned char 		U8;
typedef U8  				BOOLEAN;                                         /*  ��������                    */
typedef U8					*PU8;
typedef U8					BYTE;
typedef signed char			S8;
typedef signed char			*PS8;

#define bit	char

typedef unsigned short U16;                                          /*  �޷���16λ���ͱ���          */
typedef volatile U16 vU16;                                          /*  �޷���16λ���ͱ���          */
typedef signed short S16;
typedef volatile S16 vS16;                                          /*  �з���16λ���ͱ���          */

typedef unsigned short u16;
typedef signed long  S32; 
typedef unsigned long  U32;                                          /*  �޷���32λ���ͱ���          */
typedef volatile U32 vU32;                                          /*  �з���32λ���ͱ���          */
typedef volatile signed long  vS32; 

typedef float          FP32;                                            /*  �����ȸ�������32λ���ȣ�    */
typedef double         FP64;                                            /*  ˫���ȸ�������64λ���ȣ�    */


//typedef unsigned char  BOOLEAN;                                         // ��������                    
typedef unsigned char  INT8U;                                           // �޷���8λ���ͱ���           
typedef signed   char  INT8S;                                           // �з���8λ���ͱ���           
typedef unsigned short INT16U;                                          // �޷���16λ���ͱ���          
typedef signed   short INT16S;                                          // �з���16λ���ͱ���          
typedef unsigned long  INT32U;                                          // �޷���32λ���ͱ���          
typedef signed   long  INT32S;                                          // �з���32λ���ͱ���          

typedef unsigned int	FLAG_P;                                         // ��׼�����
typedef unsigned int	INTU;                                         // ��׼�����32BIT MCU 
/******************
**************************/



/*********************************************************************************************************
  ����ֵ����
*********************************************************************************************************/
#define     ZY_OK               0                                       /*  �����ɹ�                    */
#define     ZY_NOT_OK           1                                       /*  ����ʧ��                    */
#define     ZY_PARAMETER_ERR    2                                       /*  ��������                    */
#define     ZY_NO_FIND_FUNCTION 6                                       /*  û�з���ָ������            */
#define     ZY_NO_MEMORY        12                                      /*  �ڴ治��                    */
#define     ZY_TIME_OUT         13                                      /*  ��ʱ                        */
#define     ZY_NO_FIND_OBJECT   16                                      /*  û�з��ֶ���                */

/*********************************************************************************************************
  realView��������Ҫ��ӵ�ͷ�ļ�
*********************************************************************************************************/
#include    <ctype.h>
#include    <stdlib.h>
#include    <setjmp.h>
//#include    <rt_misc.h>
#define D_flag_lock		2
#define D_flag_clear		0
#define D_flag_CanUse		1


typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;




//>>>>>

typedef union 
{
	vU16 us;
	volatile U8 d[2];// d0 L   d1  H
}tu_us2uc;

typedef union 
{
	vU32 ui;
	vU16 s[2];
	U8 d[4];
}tu_ui4uc;

typedef union
{
    vU16 word;
    struct
    {   
        U8 l;
        U8 h;
    }BYTE2;
}U_U16;

typedef union
{
    vU32 dWord;
    struct
    {   
        U8 byte0;
        U8 byte1;
        U8 byte2;
        U8 byte3;
    }BYTE4;
}U_U32;
typedef union
{
    vU16 us;
	U8	uc[2];
}U_F16;

typedef union
{
    float fl;
	U8	uc[4];

}U_F32;

typedef struct
{
    U8 *buffer;
    U8 wpt;
    U8 rpt;
    U8 cnt;
}byte_len_fifo_struct;

typedef struct
{
    vU16 *buffer;
    vU16 wpt;
    vU16 rpt;
    vU16 cnt;
}word_len_fifo_struct;

typedef struct
{
    vU16 x;
    vU16 y;
}point_struct;


typedef struct
{
    vU16 x;
    vU16 y;
    vU16 width;
    vU16 height;
}rect_struct;


#define HIGHT   1
#define LOW     0

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b)       (((a) > (b)) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(a, b)       (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#endif


#define F_FINSIH	1
#define F_WORKING	0
#define F_WAITINGKEY	2


#define DF_var_up(v,step,max,init) (v) += (step);if((v) > (max)) (v) = (init);
//if step > 1 bug warning!!
#define DF_var_down(v,step,min,init) \
if((v) < ((min) + (step)))	\
{						\
	(v) = (init);				\
}else					\
{						\
	(v) -= (step);		\
}

#define D_us2uc_H(x)	(U8)(0x00ff&((x)>>8))
#define D_us2uc_L(x)	(U8)(0x00ff&(x))


#define D_ul2uc_0(xx)	(U8)(0x000000ff&(xx))
#define D_uc_low(ww) ((ww)>>4)
#define D_uc_high(ww) ((ww)&0x0f)

#define L0_type_byte(x)  ((U8 *) &(x))


//#define _nop_  __NOP
// #define _nop_ 


#endif  /* __TYPE_H__ */



