/*****************************************************
*							 *
*****************************************************/
//#include "STC_cc_8051.H"
//#include  "intrins.h"
#include  "task.h"
//任务命名规则: 
// 1:第一层
/// 0驱动芯片级                flash 
/// 1芯片应用级                save 
/// 2任务应用级                jilu_save 
//                                        
// 2:第二层/flash/i2c/7290/等各类芯片 
// 3:任务序号/不同的芯片/
//

void L1_task_init(TS_task  *s)
{
	s->en = 1;
//	s->pfun = 0;
	s->sh = 0;
	s->sh_next= 0;
	s->sh_pre= 0;
	s->n= 0;
}


//example : 
#ifdef doc_0809000



//L2_task_voice_handdle(&s_task_music.task);
//L1_task_go(D_task_close);
//if(L1_task_busy(s)){ L1_task_goout(s_task_music.task,D_task_voice_send_single) }
void L2_task_voice_handdle(struct _s_task_music_ *s)
{ //s_task_music.task.sh
	switch(s->task.sh)
	{

		case D_task_voice_init://

			s->sector = 0;
		break;
		case D_task_voice_cuimian  :
			s->sector = D_voice_music_wantsleep;	
			L2_task_go_son(D_task_voice_play,D_task_voice_cuimian1);
		break;		
		case D_task_voice_cuimian1://
			L2_task_go(D_task_voice_cuimian2);

		break;
		case D_task_voice_cuimian2://

			if(0 == s->volume_change)
			{
				//L3_voice_stop();
				s->sector = D_voice_stop;
				s->status = D_voice_status_stop; 
				//L2_task_go(D_task_voice_play);
				L2_task_go_son(D_task_voice_play,0);
			}else
			{
				s->volume_change --;
				s->volume_temp = s->volume;
				s->volume = s->volume_change*s->volume_pool/20;//
				if (s->volume_temp != s->volume)
				{
					s->sector = D_voice_volume|s->volume;	
					//s->status = D_voice_status_stop; 
					//L2_task_go(D_task_voice_volume3);
					L2_task_go_son(D_task_voice_play,D_task_voice_cuimian2);
				}
				//else
				{
					L2_task_delay(D_task_delay_1m);
				}
			}
			break;

		//>>>>>>>>>>>>>>>>>>	son function
		case D_task_voice_play://
			if(L3_task_s_busy(s_task_wt558d))
			{
			}else
			{
				s_task_wt558d.reg = s_task_music.sector;
				L3_task_s_go(s_task_wt558d,D_task_wt558d_fun);
				
				L2_task_go(D_task_voice_ask);
			}
			break;
		case D_task_voice_ask://
			if(L3_task_s_busy(s_task_wt558d))
			{
				
			}else
			{
				
				L2_task_go_father();//回到
			}
		break;	
		//<<<<<<<<<<<<<<<<<<<<<<	son function
		//-----------------------task standerd code
		case D_task_delay://----
			s->task.n--;
			if (s->task.n == 0)
			{
				s->task.n = 0;	
				L2_task_delay_over();	
			}		
			break;	

		default :
			break;
	}
	L2_task_wt558d_handdle(&s_task_wt558d);
}


void L2_task_voice_handdle(struct _s_task_music_ *s)
{ //s_task_music.task.sh
	switch(s->task.sh)
	{

		case D_task_voice_init://

			s->sector = 0;
		break;
		case D_task_voice_cuimian  :
			s->sector = D_voice_music_wantsleep;	
			L2_task_go_son(D_task_voice_play,D_task_voice_cuimian1);
		break;		
		case D_task_voice_cuimian1://
			L2_task_go(D_task_voice_cuimian2);

		break;

		//-----------------------task standerd code
		case D_task_delay://----
			s->task.n--;
			if (s->task.n == 0)
			{
				s->task.n = 0;	
				L2_task_delay_over();	
			}		
			break;	

		default :
			break;
	}
	L2_task_wt558d_handdle(&s_task_wt558d);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>记录task
struct _s_task_4ChuShengRiQi_
{
	_ts_task task;
	unsigned char pic_id;//画面ID


};
extern struct _s_task_4ChuShengRiQi_ s_task_4ChuShengRiQi_;

#define D_task_4ChuShengRiQi_init	0x10
#define D_task_4ChuShengRiQi_key	0x11


extern void L2_task_4ChuShengRiQi_handdle(struct _s_task_4ChuShengRiQi_ *s);
	
void L2_task_4ChuShengRiQi_handdle(struct _s_task_4ChuShengRiQi_ *s)
{
	switch(s->task.sh)
	{

		case D_task_4ChuShengRiQi_init://

			s->pic_id= 0;
		break;
		case D_task_4ChuShengRiQi_key  :
			if(1 == s_task_keyx1.down )
			{
				s_task_keyx1.down = 0;
				
				if(D_keyx_left == s_task_keyx1.key_value)
						{}

						
			}else if(1 == s_task_keyx_4.down)
			{
				s_task_keyx_4.down = 0;	

				
			}
			else {}

			//L2_task_go_son(D_task_4ChuShengRiQi_play,D_task_4ChuShengRiQi_cuimian1);
		break;		

		L0_task_delay();
	}
}



//<<<<<<<<<<<<<<<<<<<记录task





//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
















#endif


