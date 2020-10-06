#ifndef  __DRIVER_MOTOR_H
#define  __DRIVER_MOTOR_H 
#include "user_system.h"
#include "stdlib.h"


//把之前所有用到的东西整合到一个电机类中
class motor_driver{
	public:
		motor_driver(
								uint8_t id,
								TIM_HandleTypeDef driverTimer,
								TIM_HandleTypeDef encode_driverTimer,
								uint32_t pwm_channelA,
								uint32_t pwm_channelB,	
								uint32_t encode_channel,	
								uint8_t direction,
								uint16_t pwm_max);//构造函数
		~motor_driver(){}//析构函数
		/*pid参数*/
		static float _p;//采用静态变量，在c++中每个电动机都是共享这些静态变量的，在cpp文件的开头就赋好值
		static float _i;
		static float _d;
		uint16_t tick_inc;
		/*误差数*/
		double err_total;
		double err_previous;
		/*当前转速*/
		float rpm_cur;
		/*电机的最大转速*/
		static float _motor_max_rpm;
		/*设置转速函数与设置PID函数*/
		void set_rpm(float rpm);
		static void set_pid(float p,float i,float d);
		/*测试用函数*/
		int16_t get_tick_inc();//获得当前tick，编码器增量
		double read_rpm();//获取转速
		void spin(int16_t pwm);//驱动左电机旋转
	
	
	private:
		uint8_t _id;
		TIM_HandleTypeDef _driverTimer;
		TIM_HandleTypeDef _encode_driverTimer;
		uint32_t _pwm_channelA;
		uint32_t _pwm_channelB;	
		uint32_t _encode_channel;		
		int8_t _direction;
		uint16_t _pwm_max;//PWM最大值
		int32_t tick_last;//输出的上一次tick
		int32_t tick_cur;//当前的编码器的tick
		int32_t tick_total;//总和
		int8_t _encoder_direction;//正转或反转方向值，填-1或1
		uint32_t last_milli_time;//计算转速用的上一次的时间
		static float _ticks_per_rev;//编码器转一圈的最大tick
};



#endif

