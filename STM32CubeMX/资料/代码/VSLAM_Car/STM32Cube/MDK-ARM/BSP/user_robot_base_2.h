#ifndef  __USER_ROBOT_BASE_2_H_
#define  __USER_ROBOT_BASE_2_H_

#include "driver_motor.h"
#include "user_system.h"
#include "stdlib.h"
#include <math.h>
/**
���ֻ����˵��̵�������
��̥���֣�ǰ���֣�FL������FR��������RL������RR
*/

class robot_base{
	
	public:
		robot_base();
		~robot_base();
		class motor_driver* motor1_L;//��1��
		class motor_driver* motor2_L;//��2��
		class motor_driver* motor1_R;//��1��
		class motor_driver* motor2_R;//��2��
		float robot_linear_vel_x;//�������˶���󣬻�Ҫ����һ�����ٶ��Ƕ��٣����ֵҪ���ظ�ROS
		//���ٶ�ת��RPM��ת�٣�����һ�����������ٶȣ��ڶ��������ǽ��ٶȣ�Ҳ���Ǹ����ٶȺͽ��ٶȣ�����ͨ���˶�ѧ����ת����ÿһ���綯��Ӧ����ת����ת
		void velocity_to_RPM(float Liner_x,float angular_z);
		void run();//����
		void stop();//ֹͣ
	private:
		float motor_prm_1L;
		float motor_prm_2L;
		float motor_prm_1R;
		float motor_prm_2R;
		static float wheel_circumference;//��̥���ܳ����ٶ��й�
		static float wgeel_base_width;//��̥�ļ�࣬��ת���й�
};

#endif


