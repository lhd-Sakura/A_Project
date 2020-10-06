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
		class motor_driver* motor_FL;//��1��
		class motor_driver* motor_FR;//��1��		
  	class motor_driver* motor_BL;//��2��
		class motor_driver* motor_BR;//��2��
		float robot_linear_vel_x;//�������˶���󣬻�Ҫ����һ�����ٶ��Ƕ��٣����ֵҪ���ظ�ROS
		//���ٶ�ת��RPM��ת�٣�����һ�����������ٶȣ��ڶ��������ǽ��ٶȣ�Ҳ���Ǹ����ٶȺͽ��ٶȣ�����ͨ���˶�ѧ����ת����ÿһ���綯��Ӧ����ת����ת
		void velocity_to_RPM(float Liner_x,float angular_z);
		void run();//����
		void stop();//ֹͣ
	private:
		float motor_prm_FL;
		float motor_prm_BL;
		float motor_prm_FR;
		float motor_prm_BR;
		static float wheel_circumference;//��̥���ܳ����ٶ��й�
		static float wgeel_base_width;//��̥�ļ�࣬��ת���й�
};

#endif


