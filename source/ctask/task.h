/********************************
2013.7.23 add dictionary and task step by cc


����:task
�����:task step
�����־:sh  ( struct handdle)

��һ�������sh_next
����������,sh_nextִ�����ִ��sh_pre



***************************/

#ifndef   _TASK_H_
#define   _TASK_H_	 

#include "../clib/type.h" 
#include "../msp/time.h"
#include "tick.h" 

typedef struct	
{	
	//void (*pfun)(void);
	//char *father;	
	volatile type_comm en;			//�ر�����,Ҳ�������Ϊ��ͣ,����ʹ��idelay�ĵط�ʱ���ں�̨������������ʱ���˺����ͣ,����delay�൱����ͣ
	volatile type_comm sh;			//��ǰ�����
	volatile type_comm sh_next;		//��һ�������,��������һ����һ�����һ������,�п����м������ʱ�������
	volatile type_comm sh_pre;		//ǰһ�������,һ��Ϊ�������������ʹ��
	vU32 n;
}TS_task;
//extern _ts_task ts_task_stcadc;
#define D_task_close		0
#define D_task_delay			0x01
#define D_task_stop			0x04
#define D_task_delay_cycle		0x09
#define D_task_init		0x10
#define D_task_quit		0xf0

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>�ڲ����� s->task
#define L2_task_delay_over()		s->task.sh = s->task.sh_next
#define L2_task_go(next)			s->task.sh = (next);
#define L2_task_en(onf)				s->task.en = (onf);

#define L2_task_busy(s)			(D_task_close != s.task.sh)
#define L2_task_free(s)			(D_task_close == s.task.sh)

///--------------------------------------------------------------------------
/// ��ת����������, fun��������ı��, pre����������Ҫ���صı��
/// ��Ҫ�� ���ʹ��
#define L2_task_go_son(fun,pre)			s->task.sh = (fun);s->task.sh_pre = (pre);
/// �ص�go_sonָ��ķ��ر�� pre 
#define L2_task_go_father()		s->task.sh = s->task.sh_pre;
/// ȫ����· ֻҪ�㶨��·���� ��ס����д�ķ�ʽ Ȼ������������Ӧ��,֮�����õĲ�����
///-------------------------------------------------------------------------
//>task ��ȷ��ʱ>>>>>>>>>>>>>>
///��Ҫ�����и���ʱ��Ԫ
//  Delay_cycle������ ʱ��̵�
#define L2_task_switch_default_idelay();	case D_task_delay:\
		if (s_nos_tick.t_10ms >= s->task.n)\
		{\
			L2_task_delay_over();\
		}\
		break;					\
		case D_task_delay_cycle:\
			s->task.n--;			\
			if (s->task.n == 0)		\
			{						\
				s->task.n = 0;		\
				L2_task_delay_over();\
				}	\
			break;\
	default :	\
		break;

#define L2_task_switch_flag_idelay(invent,ch)  L2_task_switch_default_idelay()
#define L2_task_switch_fun_idelay(invent,ch)  L2_task_switch_default_idelay()	

////>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//fix  201312 ��ֹs_time0.t_10ms ���
// �����з���
//>>L2_task_delayһ��Ҫ����L2_task_go֮��
/// ��ϵͳʱ��ƬΪ��С��������ʱ����, ��ʱʱ��Ϊdelay_n * 10ms ��Ҫ��ʱ���е�s_nos_tick.t_10ms���
/// �����жϺ���������Ӱ��(ȡ�����ж����ȼ�,),
/// ��Ӧ�������е�switch/case D_task_delay
/// ϵͳ��Ƶ���С���Ϊswitch/case�������ĺ�mainloop�������ĺ�10ms  ���������0.xxms---19.xxms֮��
/// ����delay_n <= 1 ��Σ�� ���ɿ�  �������ʱdelay_n > 2
#define L1_task_idelay(delay_n)		s->task.sh_next = s->task.sh;\
									s->task.sh = D_task_delay;\
									s->task.n = (delay_n) + s_nos_tick.t_10ms;


//>>L2_task_delayһ��Ҫ����L2_task_go֮��
/// ��������õ���ѵʱ��Ϊ��С��������ʱ����, ��ʱʱ��Ϊdelay_n * xxus ʱ��ȡ����������ȵ���������������
/// ��ʱ�ֽ�����������ĵ�ʱ��,ͬʱҲ�����жϺ�����Ӱ�� 
/// ��Ӧ�������е�switch/case D_task_delay_cycle
#define L2_task_cycle_delay(delay_n)		s->task.sh_next = s->task.sh;\
										s->task.sh = D_task_delay_cycle;\
										s->task.n = (delay_n)


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<�ڲ�����  s->task

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> �ⲿ����
#define L2_task_s_go_son(s,fun,pre)			(s).task.sh = (fun);(s).task.sh_pre = (pre);

#define L3_task_s_time_start(s,delay)			(s).task.n = (delay)+s_nos_tick.t_1s;
#define L3_task_s_go(s,next)			(s).task.sh = (next);
#define L3_task_s_en(s,onf)			(s).task.en = (onf;)
//L1_task_goout(s_task_music.task,D_task_close);

#define L3_task_s_busy(s)			(D_task_close != (s).task.sh)
#define L3_task_s_free(s)			(D_task_close == (s).task.sh)

#define L3_task_s_step(s)			((s).task.sh)

/*
#define L1_task_s_idelay(s,delay_n)		s.task.sh_next = s.task.sh;\
										s.task.sh = D_task_delay;\
										s.task.n = delay_n+s_nos_tick.t_10ms
*/
 //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<�ⲿ����
#if 0


#define L2_task_switch_default_idelay2();	case D_task_delay:\
		if (s_nos_tick.t_10ms >= s->task.n)\
		{\
			L2_task_delay_over();\
		}else\
		{\
			L2_time_beat_heart(D_TBH_ch0,3,'i');\
		}\
		break;					\
		case D_task_delay_cycle:\
			s->task.n--;			\
			if (s->task.n == 0)		\
			{						\
				s->task.n = 0;		\
				L2_task_delay_over();\
				}	\
			break;\
	default :	\
		break;

//�ڵȴ��Ĺ��������ü��ʱ��,��ʱ����funxx
//�����ڵȴ��Ŀ���ʱ����Զ�ʱ��ʾһЩ������Ϣ��
//ִ����������

#define L2_task_switch_fun_idelay0000(chhh,invent,funxx);	case D_task_delay:\
		if (s_nos_tick.t_10ms >= s->task.n)\
		{\
			L2_task_delay_over();\
		}else\
		{\
			L2_time_beat_heart_fun((chhh),(invent),(funxx));\
		}\
		break;					\
		case D_task_delay_cycle:\
			s->task.n--;			\
			if (s->task.n == 0)		\
			{						\
				s->task.n = 0;		\
				L2_task_delay_over();\
				}	\
			break;\
	default :	\
		break;



//�ڵȴ��Ĺ��������ü��ʱ��,��ʱ��ʾ�ַ�ch
//�����ڵȴ��Ŀ���ʱ����Զ�ʱ��ʾһЩ������Ϣch
// ͨ��ch����Ŀǰ���еĽ׶κ�������Ϣ

#define L2_task_switch_flag_idelay000(invent,ch);	case D_task_delay:\
		if (s_nos_tick.t_10ms >= s->task.n)\
		{\
			L2_task_delay_over();\
		}else\
		{\
			L2_time_beat_heart(D_TBH_ch0,(invent),(ch));\
		}\
		break;					\
		case D_task_delay_cycle:\
			s->task.n--;			\
			if (s->task.n == 0)		\
			{						\
				s->task.n = 0;		\
				L2_task_delay_over();\
				}	\
			break;\
	default :	\
		break;



//if(delay_n+s_time0.t_10ms > 655340)
//{s_time0.t_10ms = 0;}
#endif
//<<<<<<<<<<<<<<new
/****************************************************8
#define L1_task_delay_over()		s->sh = s->sh_next
#define L1_task_go(next)			s->sh = next;
#define L1_task_goout(s,next)			(s).sh = next;
//L1_task_goout(s_task_music.task,D_task_close);

#define L1_task_busy(s)			(D_task_close == s.sh)


//>>>>>>>>>>>L1_task_key_delayһ��Ҫ����L1_task_key_go֮��!!!
//ͬʱ��ʹ�� ���ƵĻ�������ʽ����ʱ�󲻿ɳ���sh ��sh_netxt�ĸ�ֵ���
#define L1_task_delay(delay_n)		s->sh_next = s->sh;\
									s->sh = D_task_delay;\
									s->n = delay_n
									//fixme :����Ҳ�������L2_time_show_tick �����
#define L0_task_delay()	case D_task_delay:\
	s->task.n--;			\
	if (s->task.n == 0)		\
	{						\
		s->task.n = 0;		\
		L2_task_delay_over();\
		}						\
	break;					\
default :					\
	break;	

****************************************************/

extern void L1_task_init(TS_task  *s);

#endif//_TASK_H_


