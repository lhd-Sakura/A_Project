#include "driver_motor.h"
/*
电机类的方法与实现
*/
#define Millisecond() HAL_GetTick()
#define constrain(value,low,high) ((value)<(low)?(low):((value)>(high)?(high):(value)))
extern uint32_t speed1_L,speed2_L,speed1_R,speed2_R;
/*PID信息*///预先赋好值，因为pid在类中是静态的，所有电机可共享的数据
float motor_driver::_p = 0.2;//P比例数据
float motor_driver::_i = 0.5;//I积分数据
float motor_driver::_d = 0.3;//D微分数据

/* 电机参数 */
float motor_driver::_ticks_per_rev = 1560;//编码器转一圈的最大tick，轮胎390线的
float motor_driver::_motor_max_rpm = 350;//电机的最大转速，出厂有此参数，最好是测一下，否则pid算出来会超标

//motor_driver类的构造函数，将参数值直接赋值到类的成员值


motor_driver::motor_driver(
								uint8_t id,
								TIM_HandleTypeDef driverTimer,
								TIM_HandleTypeDef encode_driverTimer,
								uint32_t pwm_channelA,
								uint32_t pwm_channelB,		
								uint32_t encode_channel,								
								uint8_t direction,
								uint16_t pwm_max
)
{
		_id = id;
		_driverTimer = driverTimer;
	  _encode_driverTimer = encode_driverTimer;
		_pwm_channelA = pwm_channelA;
		_pwm_channelB = pwm_channelB;	
	  _encode_channel = encode_channel;							
		_direction=direction;
		/* PWM清零*/
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelA,0);	//轮IN1
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelB,0);	//轮IN2
	 HAL_TIM_PWM_Start(&_driverTimer,_pwm_channelA);
	 HAL_TIM_PWM_Start(&_driverTimer,_pwm_channelB);
	 HAL_TIM_IC_Start_IT(&_encode_driverTimer, _encode_channel);
		err_total = 0;
		err_previous = 0;
		_pwm_max = pwm_max;
		/* 编码器相关代码也清0 */
		_direction = direction;
		tick_total = 0; /* tick总里程 */
		tick_last = 0;
	
}


//1.9节设置转速函数，调节左边电机转速并输出pwm波
void motor_driver::set_rpm(float rpm){
	int16_t _pwm;
	double err;
	
	rpm_cur = read_rpm();
	/* pid 调节转速输出*/
	err = constrain(rpm,-_motor_max_rpm,_motor_max_rpm) - rpm_cur;
	err_total += err;
	
	err_total = constrain(err_total,-_pwm_max/_i,_pwm_max/_i);
	
	_pwm = _p*err + _i*err_total + _d*(err-err_previous);
	
	err_previous = err;
	
	/*pwm*/
	//这个函数是判断pwm波有没有超出最大值，宏定义，看是不是在中间值
	_pwm = constrain(_pwm,-_pwm_max,_pwm_max);
	/* <30 ~ 40的pwm电机根本不会转，但是在耗电 ,所以小于40直接置0*/
	if(abs(_pwm) < 40)_pwm = 0;
	/* spin */
	spin(_pwm);
}


//左电机，是TIM3的通道1，管脚是PA6，对应TIM2编码器的PA0通道1，PA1通道2
//右电机，是TIM3的通道2，管脚是PA7，对应TIM4编码器的PB6通道1，PB7通道2
//代码控制死区时间问题，驱动右电机旋转
/***********死区控制函数**************/
/*
由于用的是四驱小车，每个轮子两路PWM控制，总共八路PWM控制，根据死区控制理论：
当反向时，先使速度到零然后再反向，也就是先使PWM值为0，此时电机供电为0，电机停止驱动，但由于惯性可能还会转，
此时可以考虑转速是否为零，当为0时进行反转，能够防止突然反转，电路过大等问题。当然可以考虑S驱动算法，T驱动算法。

								**** 四路前进 ****
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,450);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,450);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,450);	//左2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,450);	//右2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);

				 **** 四路后退 ****
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,900);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,900);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,0);	//左2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,900);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,0);	//右2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,900)
*/
void motor_driver::spin(int16_t pwm){
	//通常代码都是这样写，在发出PWM波之前，要先进行死区时间的过滤
	/*死区时间*/
	if((rpm_cur > 0 && _direction ==1) || (rpm_cur < 0 && _direction == 0)){//判读当前转速与direction方向不一致，也就是开始正反转切换了
		////首先将两个通道的PWM进行清0，不然会有抖动
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelA,0);	//左1轮
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelB,0);	//左1轮
		//或者把点击驱动芯片的H桥中的两个晶体管都截止一下
	}
	if(_direction == 0)//正转
	{
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelA,0);	//左1轮
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelB,pwm);
	}
	if(_direction == 1)//反转
	{
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelB,0);	//左1轮
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelA,pwm);
	}
}

/*
1.7节所抄代码
*/
//读取左边电机转速rpm
double motor_driver::read_rpm(){
	uint32_t cur_milli_time;
	double delta_mins_time;
  int16_t tick_cur;
	tick_cur = get_tick_inc();	
	cur_milli_time = Millisecond();//获得当前的时间的毫秒值
	delta_mins_time = (cur_milli_time - last_milli_time)/60000.0;//把时间处理成分钟，因为转速单位是每分钟多少转
	rpm_cur = (tick_cur / _ticks_per_rev)/delta_mins_time;//读到的tick值除以转一圈的tick值然后再除以转过的分钟时间得到的就是转速值，转速值以每分钟为单位
	
	last_milli_time = cur_milli_time;
	return rpm_cur;
}


/*
1.7节
*/
//获取处理后的tick值,是读取左电机的tick
//读取右边电机处理后的tick
int16_t motor_driver::get_tick_inc()
{
	/* 获取当前编码器的tick */
		switch(_id)
	{
		case 1:
			tick_cur = speed1_L;//获取tick值
			break;
		case 2:
			tick_cur = speed2_L;//获取tick值
			break;
		case 3:
			tick_cur = speed1_R;//获取tick值
			break;
		case 4:
			tick_cur = speed2_R;//获取tick值
			break;
	}
	if(abs(tick_cur-tick_last)>0xefffffff/2)
	{
		if(tick_cur > tick_last) /*反转*/
		{
			tick_inc = -0xffff - tick_last + tick_cur;
		}else /* 正转 */
		{
			tick_inc = 0xffff - tick_last + tick_cur;
		}
	}else
	{
		tick_inc = tick_cur - tick_last;
	}
	tick_last = tick_cur;
	
	tick_inc *= _encoder_direction;/*软件调整编码器接反*/
	
	tick_total += tick_inc;/*里程计*/
	return tick_inc;
}

//设置pid函数
void motor_driver::set_pid(float p,float i,float d){
	_p = p;
	_i = i;
	_d = d;
}

