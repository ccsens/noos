/********************************
2013.7.23 add dictionary and task step by cc


任务:task
任务段:task step
任务标志:sh  ( struct handdle)

下一个任务段sh_next
缓存的任务段,sh_next执行完后执行sh_pre



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
	volatile type_comm en;			//关闭任务,也可以理解为暂停,但是使用idelay的地方时间在后台计数任务在延时到了后才暂停,而的delay相当于暂停
	volatile type_comm sh;			//当前任务段
	volatile type_comm sh_next;		//下一个任务段,并不代表一定下一任务段一定是他,有可能中间插入延时等任务段
	volatile type_comm sh_pre;		//前一个任务段,一般为调出缓存任务段使用
	vU32 n;
}TS_task;
//extern _ts_task ts_task_stcadc;
#define D_task_close		0
#define D_task_delay			0x01
#define D_task_stop			0x04
#define D_task_delay_cycle		0x09
#define D_task_init		0x10
#define D_task_quit		0xf0

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>内部调用 s->task
#define L2_task_delay_over()		s->task.sh = s->task.sh_next
#define L2_task_go(next)			s->task.sh = (next);
#define L2_task_en(onf)				s->task.en = (onf);

#define L2_task_busy(s)			(D_task_close != s.task.sh)
#define L2_task_free(s)			(D_task_close == s.task.sh)

///--------------------------------------------------------------------------
/// 跳转到子任务中, fun是子任务的标号, pre是子任务需要返回的标号
/// 需要和 配对使用
#define L2_task_go_son(fun,pre)			s->task.sh = (fun);s->task.sh_pre = (pre);
/// 回到go_son指向的返回标号 pre 
#define L2_task_go_father()		s->task.sh = s->task.sh_pre;
/// 全是套路 只要搞定套路即可 记住几种写的方式 然后就是先需求后应用,之后套用的步骤了
///-------------------------------------------------------------------------
//>task 精确定时>>>>>>>>>>>>>>
///需要额外有个定时单元
//  Delay_cycle适用于 时间短的
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
//fix  201312 防止s_time0.t_10ms 溢出
// 但是有风险
//>>L2_task_delay一定要放在L2_task_go之后
/// 以系统时间片为最小颗粒做计时处理, 延时时间为delay_n * 10ms 需要定时器中的s_nos_tick.t_10ms配合
/// 会受中断函数的有限影响(取决于中断优先级,),
/// 对应程序框架中的switch/case D_task_delay
/// 系统设计的最小误差为switch/case调度消耗和mainloop调度消耗和10ms  绝对误差在0.xxms---19.xxms之间
/// 所以delay_n <= 1 很危险 不可控  建议调用时delay_n > 2
#define L1_task_idelay(delay_n)		s->task.sh_next = s->task.sh;\
									s->task.sh = D_task_delay;\
									s->task.n = (delay_n) + s_nos_tick.t_10ms;


//>>L2_task_delay一定要放在L2_task_go之后
/// 以任务调用的轮训时间为最小颗粒做计时处理, 延时时间为delay_n * xxus 时间取决于任务调度的数量和其他任务
/// 当时分解后的任务段消耗的时间,同时也会受中断函数的影响 
/// 对应程序框架中的switch/case D_task_delay_cycle
#define L2_task_cycle_delay(delay_n)		s->task.sh_next = s->task.sh;\
										s->task.sh = D_task_delay_cycle;\
										s->task.n = (delay_n)


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<内部调用  s->task

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 外部调用
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
 //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<外部调用
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

//在等待的过程中设置间隔时间,定时调用funxx
//这样在等待的空闲时间可以定时显示一些心跳信息和
//执行心跳功能

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



//在等待的过程中设置间隔时间,定时显示字符ch
//这样在等待的空闲时间可以定时显示一些待机信息ch
// 通过ch表明目前运行的阶段和心跳信息

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


//>>>>>>>>>>>L1_task_key_delay一定要放在L1_task_key_go之后!!!
//同时当使用 类似的缓存命令式的延时后不可出现sh 或sh_netxt的赋值语句
#define L1_task_delay(delay_n)		s->sh_next = s->sh;\
									s->sh = D_task_delay;\
									s->n = delay_n
									//fixme :里面也可以添加L2_time_show_tick 来监控
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


