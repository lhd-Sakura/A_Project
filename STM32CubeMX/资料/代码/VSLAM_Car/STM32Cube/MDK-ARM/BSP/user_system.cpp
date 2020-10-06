#include "user_system.h"
uint32_t speed1_L,speed2_L,speed1_R,speed2_R;
/**********PID参数5************/
	 float _p = 35;
	 float _i = 35;
	 float _d = 10;
/******************************/	
void user_system_init()
{
	/**********开启4路脉冲捕获功能*************/
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_4);
	/******************************************/
	
	/**********开启8路PWM输出*************/
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);	 
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);	 
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);	 
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);	 
	
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,0);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,0);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);
	/******************************************/
	
	user_comm_init();
	
}



//double read_rpm(uint8_t direction,uint32_t count)
//{
//	int32_t tick_cur;
//	int32_t tick_last;
//	
//	int32_t tick_inc;
//	uint32_t cur_milli_time;
//	uint32_t last_milli_time = HAL_GetTick();
//	double delta_mins_time;
//	double rpm;
//	HAL_Delay(1000);
//	cur_milli_time = HAL_GetTick();
//	/**********获取四轮编码计数*************/
//	tick_cur = count;
//	/******************************************/
//	if(tick_cur < tick_last) /*溢出了*/
//		{
//			tick_inc = 0xefffffff - tick_last  + tick_cur;
//		}else /* 正转 */
//		{
//			tick_inc  = tick_cur  - tick_last;
//		}
//		
//	if (direction==1){
//			tick_inc *= -1; /* 软件调整编码器接反 */
//	}
//	
//	delta_mins_time = (cur_milli_time - last_milli_time)/60000.0;
//	rpm = tick_inc/1560.0/delta_mins_time;
//	tick_last = tick_cur;
//	last_milli_time = cur_milli_time;
//	print_usart1("[%8.4f | %4d|%4d]\r\n",rpm, tick_inc, tick_cur);
//	return rpm;
//}


void pid_control1_L(double speed)
{
	 float set_rpm = 0.85;
	 float cur_rpm = speed;
	 float out_pwm;
	 float err_previous = 0;
	 static double err_total1_L = 0;
	 double err;
	 static uint32_t i1_L=0;
/**********PID参数1************
	 float _p = 35;
	 float _i = 35;
	 float _d = 10;
******************************/	
/**********PID参数2************	 
	 float _p = 100;
	 float _i = 90;
	 float _d = 20;
******************************/	
/**********PID参数3************
	 float _p = 200;
	 float _i = 90;
	 float _d = 20;
******************************/	
/**********PID参数4************
	 float _p = 300;
	 float _i = 180;
	 float _d = 20;
******************************/	
/**********PID参数5************
	 float _p = 200;
	 float _i = 120;
	 float _d = 20;
/******************************/	
	 static double error1_L[]={0.0,0.0,0.0};
	 		 err = set_rpm - cur_rpm;

		 error1_L[i1_L] = err;

		 err_total1_L += err;
		

		 if(i1_L>3)
		 {
			 //	print_usart1("error[i-1]=%f,error[i] =%f\r\n",error[i-1],error[i-2]);

			      out_pwm = _p*err + _i*err_total1_L + _d*(error1_L[i1_L-1]-error1_L[i1_L]);
		 }else
		 {
			 out_pwm = _p*err + _i*err_total1_L + _d*(err-err_previous);
		 }

			 //out_pwm = _p*err + _i*err_total + _d*(err-err_previous);

		 
		 	print_usart1("err1_L =%f,err_total1_L =%f,out_pwm1_L =%f\r\n",err,err_total1_L,out_pwm);

		 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,out_pwm);	//左1轮
		 //__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,out_pwm);	//右1轮
		 //__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,out_pwm);	//左2轮
			// __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,out_pwm); //右2轮
}

void pid_control2_L(double speed)
{
	 float set_rpm = 0.85;
	 float cur_rpm = speed;
	 float out_pwm;
	// float err_previous = 0;
	 static double err_total2_L = 0;
	 double err;
	 static uint32_t i2_L=0;

/**********PID参数5************
	 float _p = 200;
	 float _i = 120;
	 float _d = 20;
/******************************/	
	 static double error2_L[]={0.0,0.0,0.0};
	 err = set_rpm - cur_rpm;

	 error2_L[i2_L] = err;

		err_total2_L += err;

		out_pwm = _p*err + _i*err_total2_L + _d*(error2_L[i2_L-1]-error2_L[i2_L]);
		print_usart1("err2_L =%f,err_total2_L =%f,out_pwm2_L =%f\r\n",err,err_total2_L,out_pwm);
		 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,out_pwm);	//左2轮

}
void pid_control1_R(double speed)
{
		 float set_rpm = 0.85;
	 float cur_rpm = speed;
	 float out_pwm;
	// float err_previous = 0;
	 static double err_total1_R = 0;
	 double err;
	 static uint32_t i1_R=0;
/**********PID参数5************
	 float _p = 200;
	 float _i = 120;
	 float _d = 20;
/******************************/	
	 static double error[]={0.0,0.0,0.0};
	 err = set_rpm - cur_rpm;
		 error[i1_R] = err;
		 err_total1_R += err;
		  out_pwm = _p*err + _i*err_total1_R + _d*(error[i1_R-1]-error[i1_R]);
		 	print_usart1("err1_R =%f,err_total1_R =%f,out_pwm1_R =%f\r\n",err,err_total1_R,out_pwm);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,out_pwm);	//右1轮
}
void pid_control2_R(double speed)
{
	 float set_rpm = 0.85;
	 float cur_rpm = speed;
	 float out_pwm;
//	 float err_previous = 0;
	 static double err_total2_R = 0;
	 double err;
	 static uint32_t i2_R=0;
/**********PID参数5************/
	 float _p = 200;
	 float _i = 120;
	 float _d = 20;
/******************************/	
	 static double error2_R[]={0.0,0.0,0.0};
	 err = set_rpm - cur_rpm;
	 error2_R[i2_R] = err;
	 err_total2_R += err;
	 out_pwm = _p*err + _i*err_total2_R + _d*(error2_R[i2_R-1]-error2_R[i2_R]);
	 print_usart1("err2_R =%f,err_total2_R =%f,out_pwm2_R =%f\r\n",err,err_total2_R,out_pwm);
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,out_pwm); //右2轮
}

//void pid_control2_R(double speed)
//{
//	 float set_rpm = 0.85;
//	 float cur_rpm = speed;
//	 float out_pwm;
////	 float err_previous = 0;
//	 static double err_total = 0;
//	 double err;
//	 static uint32_t i=0;
///**********PID参数5************/
//	 float _p = 200;
//	 float _i = 120;
//	 float _d = 20;
///******************************/	
//	 static double error[]={0.0,0.0,0.0};
//	 err = set_rpm - cur_rpm;
//	 error[i] = err;
//	 err_total += err;
//	 out_pwm = _p*err + _i*err_total + _d*(error[i-1]-error[i]);
//	 print_usart1("err2_R =%f,err_total2_R =%f,out_pwm2_R =%f\r\n",err,err_total,out_pwm);
//	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,out_pwm); //右2轮
//}
double read_rpm(uint8_t direction1_L,uint8_t direction2_L,uint8_t direction1_R,uint8_t direction2_R)
{
	int32_t tick_cur1_L,tick_cur2_L,tick_cur1_R,tick_cur2_R;
	static int32_t tick_last1_L = 0;
	static int32_t tick_last2_L = 0;
	static int32_t tick_last1_R = 0;
	static int32_t tick_last2_R = 0;
	
	int32_t tick_inc1_L,tick_inc2_L,tick_inc1_R,tick_inc2_R;
	uint32_t cur_milli_time;
	static uint32_t last_milli_time = 0;
//	static uint32_t last_milli_time2_L = 0;
//	static uint32_t last_milli_time1_R = 0;
//	static uint32_t last_milli_time2_R = 0;
	double delta_mins_time;
	double rpm1_L,rpm2_L,rpm1_R,rpm2_R;
	cur_milli_time = HAL_GetTick();
	/**********获取四轮编码计数*************/
	tick_cur1_L = speed1_L;
	tick_cur2_L = speed2_L;
	tick_cur1_R = speed1_R;
	tick_cur2_R = speed2_R;
	/******************************************/
	if(tick_cur1_L < tick_last1_L) /*溢出了*/
		{
			tick_inc1_L = 0xefffffff - tick_last1_L + tick_cur1_L;
		}else /* 正转 */
		{
			tick_inc1_L = tick_cur1_L - tick_last1_L;
		}		
	if (direction1_L==1){
			tick_inc1_L *= -1; /* 软件调整编码器接反 */
	}
	
	
	
		if(tick_cur2_L < tick_last2_L) /*溢出了*/
		{
			tick_inc2_L = 0xefffffff - tick_last2_L + tick_cur2_L;
		}else /* 正转 */
		{
			tick_inc2_L = tick_cur2_L - tick_last2_L;
		}
		
	if (direction2_L==1){
			tick_inc2_L *= -1; /* 软件调整编码器接反 */
	}
	
	
	
		if(tick_cur1_R < tick_last1_R) /*溢出了*/
		{
			tick_inc1_R = 0xefffffff - tick_last1_R + tick_cur1_R;
		}else /* 正转 */
		{
			tick_inc1_R = tick_cur1_R - tick_last1_R;
		}
		
	if (direction1_R==1){
			tick_inc1_R *= -1; /* 软件调整编码器接反 */
	}
	
	
	
		if(tick_cur2_R < tick_last2_R) /*溢出了*/
		{
			tick_inc2_R = 0xefffffff - tick_last2_R + tick_cur2_R;
		}else /* 正转 */
		{
			tick_inc2_R = tick_cur2_R - tick_last2_R;
		}
		
	if (direction2_R==1){
			tick_inc2_R *= -1; /* 软件调整编码器接反 */
	}
//	if(abs(tick_cur1-tick_last1)>0xefffffff/2)
//	{
//		if(tick_cur1 > tick_last1) /*反转*/
//		{
//			tick_inc = -0xffff - tick_last1 + tick_cur1;
//		}else /* 正转 */
//		{
//			tick_inc = 0xffff - tick_last1 + tick_cur1;
//		}
//	}else
//	{
//		tick_inc = tick_cur1 - tick_last1;
//	}
	
	delta_mins_time = (cur_milli_time - last_milli_time)/60000.0;
	rpm1_L = tick_inc1_L/1560.0/delta_mins_time;
	tick_last1_L = tick_cur1_L;
	
	rpm2_L = tick_inc2_L/1560.0/delta_mins_time;
	tick_last2_L = tick_cur2_L;
	
	rpm1_R = tick_inc1_R/1560.0/delta_mins_time;
	tick_last1_R = tick_cur1_R;
	
	rpm2_R = tick_inc2_R/1560.0/delta_mins_time;
	tick_last2_R = tick_cur2_R;
	
	last_milli_time = cur_milli_time;
	print_usart1("[%8.4f | %4d|%4d]\r\n",rpm1_L, tick_inc1_L, tick_cur1_L);
	print_usart1("[%8.4f | %4d|%4d]\r\n",rpm2_L, tick_inc2_L, tick_cur2_L);
	print_usart1("[%8.4f | %4d|%4d]\r\n",rpm1_R, tick_inc1_R, tick_cur1_R);
	print_usart1("[%8.4f | %4d|%4d]\r\n",rpm2_R, tick_inc2_R, tick_cur2_R);
	
	pid_control1_L(rpm1_L);
	pid_control2_L(rpm2_L);
	pid_control1_R(rpm1_R);
	pid_control2_R(rpm2_R);
}

uint8_t direction_control(uint8_t direction_set)
{
	switch(direction_set)
	{
		case 0:
	 /**** 四路前进 ****/
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,450);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,450);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,450);	//左2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,450);	//右2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);
	 /***************/
			break;
		case 1:
				 /**** 四路后退 ****/
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,900);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,900);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,0);	//左2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,900);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,0);	//右2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,900);
	 /***************/
			break;
		
		case 2:
				 	 /**** 四路停止 ****/
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,999);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,999);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,999);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,999);
	 
	 
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
//	 int i = 0;
//	 uint32_t tick_count;
	 //uint32_t tick_cur;
	 uint8_t tick_direction = 0;
	 float cur_rpm = 0;
	 direction_control(tick_direction);
//	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,300);	//左1轮
//	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
	 

	 while(1)
	 {
//		 tick_count = HAL_GetTick();
		 //print_usart1("system run() %d=%d\r\n",i,HAL_GetTick()-tick_count);
		 


     HAL_Delay(3000);
		 read_rpm(tick_direction,tick_direction,tick_direction,tick_direction);		 
		 HAL_IWDG_Refresh(&hiwdg);
		 
//		 //HAL_Delay(1000);
//		 HAL_IWDG_Refresh(&hiwdg);
//		 cur_rpm = read_rpm(tick_direction,speed2_L);
//		 pid_control2_L(cur_rpm);
//		 
//		 //HAL_Delay(1000);
//		 HAL_IWDG_Refresh(&hiwdg);
//		 cur_rpm = read_rpm(tick_direction,speed1_R);
//		 pid_control1_R(cur_rpm);

//		 //HAL_Delay(1000);
//		 HAL_IWDG_Refresh(&hiwdg);
//		 cur_rpm = read_rpm(tick_direction,speed2_R);
//		 pid_control2_R(cur_rpm);
		 
		 //tick_cur = __HAL_TIM_GET_COUNTER(&htim2);
		 //print_usart1("tick_cur =%d\r\n",tick_cur);
		 //print_usart1("speed1_L =%d,speed2_L =%d,speed1_R =%d,speed2_R =%d\r\n",speed1_L,speed2_L,speed1_R,speed2_R);
		 
//		 speed1_L=0;
//		 speed2_L=0;
//		 speed1_R=0;
//			speed2_R=0;
	 }
 }
 