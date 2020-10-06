#ifndef  __USER_ROBOT_BASE_2_H_
#define  __USER_ROBOT_BASE_2_H_

#include "driver_motor.h"
#include "user_system.h"
#include "stdlib.h"
#include <math.h>
/**
两轮机器人底盘底座基座
轮胎名字：前左轮：FL，右轮FR，后左轮RL，右轮RR
*/

class robot_base{
	
	public:
		robot_base();
		~robot_base();
		class motor_driver* motor_FL;//左1轮
		class motor_driver* motor_FR;//右1轮		
  	class motor_driver* motor_BL;//左2轮
		class motor_driver* motor_BR;//右2轮
		float robot_linear_vel_x;//机器人运动完后，还要返回一下线速度是多少，这个值要返回给ROS
		//线速度转成RPM（转速），第一个参数是线速度，第二个参数是角速度，也就是给线速度和角速度，他就通过运动学计算转化成每一个电动机应该是转多少转
		void velocity_to_RPM(float Liner_x,float angular_z);
		void run();//运行
		void stop();//停止
	private:
		float motor_prm_FL;
		float motor_prm_BL;
		float motor_prm_FR;
		float motor_prm_BR;
		static float wheel_circumference;//轮胎的周长与速度有关
		static float wgeel_base_width;//轮胎的间距，与转弯有关
};

#endif


