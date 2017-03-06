/*****************************************************************************
 *   debug_drv.c:  debug app
 *
 *   Copyright(C) 2013, cc
 *   All rights reserved.
 *
 *   History
 *   2013.05.24  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/

#include "debug_drv.h"

void L3_debug_drv_init(void)
{
	Lc_print("\r\n debug shell init:\t");
/// io 设置的标准写法

	#ifdef D_debug_sim
		Lc_print(" debug");
	#else
	//D_debug_time_using
		Lc_print(" normal");
	#endif
}

/******************************************************************************
**                            End Of File
******************************************************************************/
