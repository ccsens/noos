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

//===============================================
//����������ɾ��
//===============================================
unsigned char code reserved_trap[6] _at_ 0x7A;//
unsigned char  code flashlockbit_reserve[8] _at_ 0x86= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};            
unsigned short  code password_reserve[0x08] _at_ 0x90={0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};


