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

//===============================================
//保留区域（勿删）
//===============================================
unsigned char code reserved_trap[6] _at_ 0x7A;//
unsigned char  code flashlockbit_reserve[8] _at_ 0x86= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};            
unsigned short  code password_reserve[0x08] _at_ 0x90={0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};


