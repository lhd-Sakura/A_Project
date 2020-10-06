#include "user_robot_base_2.h"


/**
	运动学算法
*/
float robot_base::wheel_circumference = 0.068 * PI;//在这里采用的轮胎是68mm的，记得要按照实际来，周长=π * 直径 = 2 * π * 半径
float robot_base::wgeel_base_width = 0.20;//两个轮胎之间的间距，这个也要根据实际修改
//robot_base类构造函数的实现
robot_base::robot_base(){
	//这样如果要应用到电机就可以直接创建对象，通过构造函数将参数进行传递即可
	//把电机所连接的编码器，PWM波等整合好传入即可，第一个参数是编码器，第三个参数是PWM的通道，GPIOB是电机的引脚
	 /**** 四路前进 ****
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,450);	//左1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,450);	//右1轮
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,450);	//左2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,450);	//右2轮
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);
	
		**********开启4路脉冲捕获功能*************
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_4);
	******************************************/
	
	motor_FL = new motor_driver(1,htim1,htim2,TIM_CHANNEL_1,TIM_CHANNEL_2,TIM_CHANNEL_1,0,900);
	motor_BL = new motor_driver(2,htim1,htim3,TIM_CHANNEL_3,TIM_CHANNEL_4,TIM_CHANNEL_1,0,900);
	motor_FR = new motor_driver(3,htim8,htim4,TIM_CHANNEL_1,TIM_CHANNEL_2,TIM_CHANNEL_1,0,900);
	motor_BR = new motor_driver(3,htim8,htim5,TIM_CHANNEL_3,TIM_CHANNEL_4,TIM_CHANNEL_4,0,900);

	robot_linear_vel_x = 0;
}
//robot_base类析构函数的实现
robot_base::~robot_base(){
	delete motor_FL;//将两个对象回收
	delete motor_BL;
	delete motor_FR;//将两个对象回收
	delete motor_BR;
}

//线速度与角速度转化成转速 算法
void robot_base::velocity_to_RPM(float linear_vel_x,float angular_rad_z){
	/*单位转换：m/s -> m/min*/
	static float linear_vel_x_min;
	/*单位转换：rad/s -> rad/min*/
	static float angular_rad_z_min;
	/**/
	static float tangential_vel;
	float scale = 1;
	
	/* 单位转换：m/s -> m/min */
	linear_vel_x_min = linear_vel_x *60;//把线速度从单位秒转为分钟，因为ROS发出指令的时候是米/每秒
	/* 单位转换：rad/s -> rad/min */
	angular_rad_z_min = angular_rad_z * 60;
	//计算切向速度
	tangential_vel = angular_rad_z_min * wgeel_base_width/2;
	/***/
	while(1){
		//直线速度-转弯的角速度然后除以轮胎的周长，求出来就是轮胎的转速了，这个轮胎是左轮
		motor_prm_FL = (linear_vel_x_min - tangential_vel ) / wheel_circumference;
		//这个是右轮
		motor_prm_BR = (linear_vel_x_min + tangential_vel ) / wheel_circumference;
		//到这里已经可以转动了，但存在一个问题，需要判断一下转速是否可以运行，会不会超过电机的最大速度
		//因为如果你现在机器人在以最大速度跑直线，如果他突然要转弯，那么如果要转弯的话，那么外圈速度一定要大于内圈速度，不然也转不过呀
		//这时就超出了电机转速的最大值，所以while里面的代码是进行重新计算和判断。
		//判断两个轮胎的其中一个是否比电机转速的最大值还要大，
		//如果是，那么将把线速度和角速度乘一个缩小系数，
		//这样下次再来一次，然后再判断，依次直到比最大速度小了，才break跳出，然后调用run然后运行。
		if(abs(motor_prm_FL) <= motor_driver::_motor_max_rpm//因为可能是负值，所以要取一下绝对值，看他是否比最大转速要大
			&& abs(motor_prm_BR) <= motor_driver::_motor_max_rpm){
				break;
		}
			scale -= 0.0333334;//缩小系数
			linear_vel_x_min *= scale;
			tangential_vel *= scale;
	}
	run();
}

//运行函数，通过设置转速，真正让电机动起来，然后将机器人的线速度算出来
void robot_base::run(){
	motor_FL->set_rpm(motor_prm_FL);//将算好了的电机转速通过参数传递
	motor_BL->set_rpm(motor_prm_BL);
	motor_FR->set_rpm(motor_prm_FR);//将算好了的电机转速通过参数传递
	motor_BR->set_rpm(motor_prm_BR);
	//然后将机器人的移动速度算出来，两个轮子的当前转速相加然后除以2就是真正机器人的速度了
	double average_rpm = (motor_FL->rpm_cur + motor_FL->rpm_cur)/2;
	double average_rps = average_rpm/60;//把每分钟多少转的单位给转回来，转成每秒多少转
	//直线速度上报给ROS系统
	robot_linear_vel_x = average_rps * wheel_circumference;//每秒钟多少转的转速乘以轮胎的弧长，也就是一圈的长度，就是转换成了直线速度
}


//停止运行函数
void robot_base::stop(){
	motor_FL->set_rpm(0);
	motor_BL->set_rpm(0);
	motor_FR->set_rpm(0);
	motor_BR->set_rpm(0);
}


