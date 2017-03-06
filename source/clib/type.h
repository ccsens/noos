//////////////////////////////////////////////////////////////////////////  
/// COPYRIGHT NOTICE  
/// Copyright (c) 2015, 传控科技
/// All rights reserved.  
///  
/// @file            main.c
/// @brief           main app  
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
  定义与编译器无关的数据类型
*********************************************************************************************************/

typedef unsigned char 		u8;
typedef unsigned char 		U8;
typedef U8  				BOOLEAN;                                         /*  布尔变量                    */
typedef U8					*PU8;
typedef U8					BYTE;
typedef signed char			S8;
typedef signed char			*PS8;

#define bit	char

typedef unsigned short U16;                                          /*  无符号16位整型变量          */
typedef volatile U16 vU16;                                          /*  无符号16位整型变量          */
typedef signed short S16;
typedef volatile S16 vS16;                                          /*  有符号16位整型变量          */

typedef unsigned short u16;
typedef signed long  S32; 
typedef unsigned long  U32;                                          /*  无符号32位整型变量          */
typedef volatile U32 vU32;                                          /*  有符号32位整型变量          */
typedef volatile signed long  vS32; 

typedef float          FP32;                                            /*  单精度浮点数（32位长度）    */
typedef double         FP64;                                            /*  双精度浮点数（64位长度）    */


//typedef unsigned char  BOOLEAN;                                         // 布尔变量                    
typedef unsigned char  INT8U;                                           // 无符号8位整型变量           
typedef signed   char  INT8S;                                           // 有符号8位整型变量           
typedef unsigned short INT16U;                                          // 无符号16位整型变量          
typedef signed   short INT16S;                                          // 有符号16位整型变量          
typedef unsigned long  INT32U;                                          // 无符号32位整型变量          
typedef signed   long  INT32S;                                          // 有符号32位整型变量          

typedef unsigned int	FLAG_P;                                         // 标准类变量
typedef unsigned int	INTU;                                         // 标准类变量32BIT MCU 
/******************
**************************/



/*********************************************************************************************************
  返回值定义
*********************************************************************************************************/
#define     ZY_OK               0                                       /*  操作成功                    */
#define     ZY_NOT_OK           1                                       /*  操作失败                    */
#define     ZY_PARAMETER_ERR    2                                       /*  参数错误                    */
#define     ZY_NO_FIND_FUNCTION 6                                       /*  没有发现指定函数            */
#define     ZY_NO_MEMORY        12                                      /*  内存不足                    */
#define     ZY_TIME_OUT         13                                      /*  超时                        */
#define     ZY_NO_FIND_OBJECT   16                                      /*  没有发现对象                */

/*********************************************************************************************************
  realView编译器需要添加的头文件
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



