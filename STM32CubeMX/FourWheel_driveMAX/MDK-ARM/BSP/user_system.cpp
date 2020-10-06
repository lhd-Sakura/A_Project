#include "user_system.h"
uint32_t speed_FL,speed_FR,speed_BL,speed_BR;


	 float _p = 30;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 30;        //抑制惯性过调




void user_system_init()
{
	/**********开启4路脉冲捕获功能*************/
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_1);
	/******************************************/
	
	/**********开启8路PWM输出*************/
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,0);	 
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,0);	 
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);	 
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);	 
	
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,0);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,0);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);
	/******************************************/
	
	user_comm_init();
	
}






//PID控制
void pid_control_FL(double speed)
{
	 float set_rpm = 2;
	 float cur_rpm = speed;
	 float out_pwm;
//	 float err_previous = 0;
	 static double err_total_FL = 0;
	 double err;
	 static uint32_t i_FL=0;
	
	/*
	
	 float _p = 30;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 30;        //抑制惯性过调
		
	
		反应快精度不高
	 float _p = 28;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 25;        //抑制惯性过调



	*/
	 float _p = 28;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 25;        //抑制惯性过调


	
	//PID算法
	 static double error_FL[]={0.0,0.0,0.0};
	 err = set_rpm - cur_rpm;
	 error_FL[i_FL] = err;
	 err_total_FL += err;
	 out_pwm = _p*err + _i*err_total_FL + _d*(error_FL[i_FL-1]-error_FL[i_FL]);
//	 print_usart1("err_BR =%f,err_total_BR =%f,out_pwm_BR =%f\r\n",err,err_total_BR,out_pwm);
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,out_pwm); //右2轮

	 
}
void pid_control_FR(double speed)
{
	 float set_rpm = 2;
	 float cur_rpm = speed;
	 float out_pwm;
//	 float err_previous = 0;
	 static double err_total_FR = 0;
	 double err;
	 static uint32_t i_FR=0;
	
	/*
	
	 float _p = 30;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 30;        //抑制惯性过调
		
	
		反应快精度不高
	 float _p = 28;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 25;        //抑制惯性过调



	*/
	 float _p = 28;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 25;        //抑制惯性过调


	//PID算法
	 static double error_FR[]={0.0,0.0,0.0};
	 err = set_rpm - cur_rpm;
	 error_FR[i_FR] = err;
	 err_total_FR += err;
	 out_pwm = _p*err + _i*err_total_FR + _d*(error_FR[i_FR-1]-error_FR[i_FR]);
//	 print_usart1("err_BR =%f,err_total_BR =%f,out_pwm_BR =%f\r\n",err,err_total_BR,out_pwm);
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,out_pwm); //右2轮

	 
}


void pid_control_BL(double speed)
{
	 float set_rpm = 2;
	 float cur_rpm = speed;
	 float out_pwm;
//	 float err_previous = 0;
	 static double err_total_BL = 0;
	 double err;
	 static uint32_t i_BL=0;
	
	/*
	
	 float _p = 30;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 30;        //抑制惯性过调
		
	
		反应快精度不高
	 float _p = 28;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 25;        //抑制惯性过调



	*/
	 float _p = 28;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 25;        //抑制惯性过调


	//PID算法
	 static double error_BL[]={0.0,0.0,0.0};
	 err = set_rpm - cur_rpm;
	 error_BL[i_BL] = err;
	 err_total_BL += err;
	 out_pwm = _p*err + _i*err_total_BL + _d*(error_BL[i_BL-1]-error_BL[i_BL]);
//	 print_usart1("err_BR =%f,err_total_BR =%f,out_pwm_BR =%f\r\n",err,err_total_BR,out_pwm);
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,out_pwm); //右2轮

	 
}



void pid_control_BR(double speed)
{
	 float set_rpm = 2;
	 float cur_rpm = speed;
	 float out_pwm;
//	 float err_previous = 0;
	 static double err_total_BR = 0;
	 double err;
	 static uint32_t i_BR=0;
	
	/*
	
	 float _p = 30;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 30;        //抑制惯性过调
		
	
		反应快精度不高
	 float _p = 28;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 25;        //抑制惯性过调



	*/
	/*
	 float _p = 28;       //系统稳定度，上下波动
	 float _i = 60;       //系统相应速度，快速调节
	 float _d = 25;        //抑制惯性过调
*/

    float _p = 25;       //系统稳定度，上下波动
	  float _i = 50;       //系统相应速度，快速调节
	  float _d = 25;        //抑制惯性过调




	//PID算法
	 static double error_BR[]={0.0,0.0,0.0};
	 err = set_rpm - cur_rpm;
	 error_BR[i_BR] = err;
	 err_total_BR += err;
	 out_pwm = _p*err + _i*err_total_BR + _d*(error_BR[i_BR-1]-error_BR[i_BR]);
//	 print_usart1("err_BR =%f,err_total_BR =%f,out_pwm_BR =%f\r\n",err,err_total_BR,out_pwm);
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,out_pwm); //右2轮

	 
}




//PWM450速度2.0n/s,PWM999 4.0n/s
double read_rpm(uint8_t direction_FL,uint8_t direction_BL,uint8_t direction_FR,uint8_t direction_BR)
{
	
	//静态初始值为0
	int32_t tick_cur_FL,tick_cur_BL,tick_cur_FR,tick_cur_BR;
	static int32_t tick_last_FL = 0;
	static int32_t tick_last_BL = 0;
	static int32_t tick_last_FR = 0;
	static int32_t tick_last_BR = 0;
	
	//转动差值
	int32_t    tick_inc_FL,tick_inc_BL,tick_inc_FR,tick_inc_BR;
	
	//开始时间
	uint32_t cur_milli_time;
	static uint32_t last_milli_time = 0;

	
	
	//时间差值
	double delta_mins_time;
	
	
	
	double rpm_FL,rpm_BL,rpm_FR,rpm_BR;
	
	
	
	//四个轮子编码器计数
	tick_cur_FL = speed_FL;
	tick_cur_FR = speed_FR;	
	tick_cur_BL = speed_BL;
	tick_cur_BR = speed_BR;


   //获取转动时间
   cur_milli_time = HAL_GetTick();
		
		
	
	//确定正转反转，确定转动圈数
	
	
			if(tick_cur_FL < tick_last_FL) /*溢出了*/
		{
			tick_inc_FL = 0xefffffff - tick_last_FL + tick_cur_FL;
		}else /* 正转 */
		{
			tick_inc_FL = tick_cur_FL - tick_last_FL;
		}	
	if (direction_FL==1){
			tick_inc_FL *= -1; /* 软件调整编码器接反 */
	}
	
	
	
	
	if(tick_cur_FR < tick_last_FR) /*溢出了*/
		{
			tick_inc_FR = 0xefffffff - tick_last_FR + tick_cur_FR;
		}else /* 正转 */
		{
			tick_inc_FR = tick_cur_FR- tick_last_FR;
		}
		
	if (direction_FR==1){
			tick_inc_FR *= -1; /* 软件调整编码器接反 */
	}
	
	
	
	
	
	if(tick_cur_BL < tick_last_BL) /*溢出了*/
		{
			tick_inc_BL= 0xefffffff - tick_last_BL + tick_cur_BL;
		}else /* 正转 */
		{
			tick_inc_BL= tick_cur_BL- tick_last_BL;
		}		
	if (direction_BL==1){
			tick_inc_BL *= -1; /* 软件调整编码器接反 */
	}
	
	
	
	
	
		if(tick_cur_BR < tick_last_BR) /*溢出了*/
		{
			tick_inc_BR = 0xefffffff - tick_last_BR + tick_cur_BR;
		}else /* 正转 */
		{
			tick_inc_BR = tick_cur_BR - tick_last_BR;
		}	
	if (direction_BR==1){
		
		
		
		
			tick_inc_BR *= -1; /* 软件调整编码器接反 */
	}
	
	
	

	

	delta_mins_time = (cur_milli_time - last_milli_time)/1000.0;
	
	
	
	rpm_FL = tick_inc_FL/20.0/delta_mins_time;
	tick_last_FL = tick_cur_FL;
		
	rpm_FR = tick_inc_FR/20.0/delta_mins_time;
	tick_last_FR = tick_cur_FR;
	
	rpm_BL = tick_inc_BL/20.0/delta_mins_time;
	tick_last_BL = tick_cur_BL;

	rpm_BR = tick_inc_BR/20.0/delta_mins_time;
	tick_last_BR = tick_cur_BR;
	
	last_milli_time = cur_milli_time;
	
	print_usart1("time：%d\r\n",delta_mins_time);
	print_usart1("FL:%8.4f | %4d|%4d\r\n",rpm_FL, tick_inc_FL, tick_cur_FL);
	print_usart1("FR:%8.4f | %4d|%4d\r\n",rpm_FR, tick_inc_FR, tick_cur_FR);
  print_usart1("BL:%8.4f | %4d|%4d\r\n",rpm_BL, tick_inc_BL, tick_cur_BL);
	print_usart1("BR:%8.4f | %4d|%4d\r\n",rpm_BR, tick_inc_BR, tick_cur_BR);
	HAL_Delay(500);


	pid_control_FL(rpm_FL);
	pid_control_FR(rpm_FR);
	pid_control_BL(rpm_BL);
	pid_control_BR(rpm_BR);
	

}



//四个轮子移动方向，输入通道相反来实现前进、后退
uint8_t direction_control(uint8_t direction_set)
{
	
	switch(direction_set)
	{
		case 0:
	 /**** 四路前进 ****/
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,450);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,450);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,450);	//左2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,450);	//右2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);
	 /***************/
			break;
		case 1:
				 /**** 四路后退 ****/
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,0);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,900);
	 
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,900);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,0);	//左2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,900);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,0);	//右2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,900);
	 /***************/
			break;
		
		case 2:
				 	 /**** 四路停止 ****/
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,999);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,999);
	
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,999);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,999);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,999);	//左2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,999);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,999);	//右2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,999);
	 /***************/
			break;
		
		case 3:
			break;
		
		case 4:
			break;
		
		case 5:
			break;
	}
	
	
	return direction_set;
}




 void user_system_thread_0()
 {
	 int i = 0;
	 uint32_t tick_count;
	 uint32_t tick_cur;

	 float cur_rpm = 0;
	 uint8_t tick_direction = 0;   //移动方向（前进、后退、停止）	
	 direction_control(tick_direction);


	 while(1)
	 {
		 
//		 tick_count = HAL_GetTick();
//		 print_usart1("system run() %d=%d\r\n",i,HAL_GetTick()-tick_count);
//		 tick_cur = __HAL_TIM_GET_COUNTER(&htim4);
//		 print_usart1("%d\r\n",tick_cur);

		 
     read_rpm(tick_direction, tick_direction, tick_direction, tick_direction);

					 HAL_IWDG_Refresh(&hiwdg);


					 HAL_Delay(100);

	
	 }
 }























/*

 void user_system_thread_0()
 {
	 int i = 0;
	 uint32_t tick_count;
	 uint32_t tick_cur;

	 float cur_rpm = 0;
	 uint8_t tick_direction = 1;   //移动方向（前进、后退、停止）	
	 direction_control(tick_direction);


	 while(1)
	 {
		 
//		 tick_count = HAL_GetTick();
//		 print_usart1("system run() %d=%d\r\n",i,HAL_GetTick()-tick_count);
//		 tick_cur = __HAL_TIM_GET_COUNTER(&htim4);
//		 print_usart1("%d\r\n",tick_cur);

		 
//	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,999);	//左1轮
//	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);
		 
		 
	 float _p = 25;       //系统稳定度，上下波动
	 float _i = 50;       //系统相应速度，快速调节
	 float _d = 20;        //抑制惯性过调
		 
		 
		 
		 int h;
		 double g;


		 for(_d=20;_d<60;_d++)
		 {
			 for(_p=10;_p<50;_p++)
			 {
				 
				 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,999);	//左1轮
//	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);
				 	 HAL_Delay(500);
				 
				 for(h=50;h>0;h--)
				 {
				 
					 
				  g =   read_rpm(tick_direction,tick_direction,tick_direction,tick_direction);	
	
					 HAL_IWDG_Refresh(&hiwdg);
					 print_usart1("P:%6f,I:%6f,D:%6f\r\n",_p,_i,_d);
//					 print_usart1("%f\r\n",_i);
//					 print_usart1("%f\r\n",_d);
					 HAL_Delay(100);

					 pid_control_BR(g);
				 
				 }
			 
			 
			 }
			 	 
		 }
		 
	 }
 }
 
 */
 