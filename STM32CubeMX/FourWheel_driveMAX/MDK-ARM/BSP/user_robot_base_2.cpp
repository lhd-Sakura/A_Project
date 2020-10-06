#include "user_robot_base_2.h"


/**
	�˶�ѧ�㷨
*/
float robot_base::wheel_circumference = 0.068 * PI;//��������õ���̥��68mm�ģ��ǵ�Ҫ����ʵ�������ܳ�=�� * ֱ�� = 2 * �� * �뾶
float robot_base::wgeel_base_width = 0.20;//������̥֮��ļ�࣬���ҲҪ����ʵ���޸�
//robot_base�๹�캯����ʵ��
robot_base::robot_base(){
	//�������ҪӦ�õ�����Ϳ���ֱ�Ӵ�������ͨ�����캯�����������д��ݼ���
	//�ѵ�������ӵı�������PWM�������Ϻô��뼴�ɣ���һ�������Ǳ�������������������PWM��ͨ����GPIOB�ǵ��������
	 /**** ��·ǰ�� ****
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,450);	//��1��
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,450);	//��1��
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,450);	//��2��
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,450);	//��2��
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);
	
		**********����4·���岶����*************
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
//robot_base������������ʵ��
robot_base::~robot_base(){
	delete motor_FL;//�������������
	delete motor_BL;
	delete motor_FR;//�������������
	delete motor_BR;
}

//���ٶ�����ٶ�ת����ת�� �㷨
void robot_base::velocity_to_RPM(float linear_vel_x,float angular_rad_z){
	/*��λת����m/s -> m/min*/
	static float linear_vel_x_min;
	/*��λת����rad/s -> rad/min*/
	static float angular_rad_z_min;
	/**/
	static float tangential_vel;
	float scale = 1;
	
	/* ��λת����m/s -> m/min */
	linear_vel_x_min = linear_vel_x *60;//�����ٶȴӵ�λ��תΪ���ӣ���ΪROS����ָ���ʱ������/ÿ��
	/* ��λת����rad/s -> rad/min */
	angular_rad_z_min = angular_rad_z * 60;
	//���������ٶ�
	tangential_vel = angular_rad_z_min * wgeel_base_width/2;
	/***/
	while(1){
		//ֱ���ٶ�-ת��Ľ��ٶ�Ȼ�������̥���ܳ��������������̥��ת���ˣ������̥������
		motor_prm_FL = (linear_vel_x_min - tangential_vel ) / wheel_circumference;
		//���������
		motor_prm_BR = (linear_vel_x_min + tangential_vel ) / wheel_circumference;
		//�������Ѿ�����ת���ˣ�������һ�����⣬��Ҫ�ж�һ��ת���Ƿ�������У��᲻�ᳬ�����������ٶ�
		//��Ϊ��������ڻ�������������ٶ���ֱ�ߣ������ͻȻҪת�䣬��ô���Ҫת��Ļ�����ô��Ȧ�ٶ�һ��Ҫ������Ȧ�ٶȣ���ȻҲת����ѽ
		//��ʱ�ͳ����˵��ת�ٵ����ֵ������while����Ĵ����ǽ������¼�����жϡ�
		//�ж�������̥������һ���Ƿ�ȵ��ת�ٵ����ֵ��Ҫ��
		//����ǣ���ô�������ٶȺͽ��ٶȳ�һ����Сϵ����
		//�����´�����һ�Σ�Ȼ�����жϣ�����ֱ��������ٶ�С�ˣ���break������Ȼ�����runȻ�����С�
		if(abs(motor_prm_FL) <= motor_driver::_motor_max_rpm//��Ϊ�����Ǹ�ֵ������Ҫȡһ�¾���ֵ�������Ƿ�����ת��Ҫ��
			&& abs(motor_prm_BR) <= motor_driver::_motor_max_rpm){
				break;
		}
			scale -= 0.0333334;//��Сϵ��
			linear_vel_x_min *= scale;
			tangential_vel *= scale;
	}
	run();
}

//���к�����ͨ������ת�٣������õ����������Ȼ�󽫻����˵����ٶ������
void robot_base::run(){
	motor_FL->set_rpm(motor_prm_FL);//������˵ĵ��ת��ͨ����������
	motor_BL->set_rpm(motor_prm_BL);
	motor_FR->set_rpm(motor_prm_FR);//������˵ĵ��ת��ͨ����������
	motor_BR->set_rpm(motor_prm_BR);
	//Ȼ�󽫻����˵��ƶ��ٶ���������������ӵĵ�ǰת�����Ȼ�����2�������������˵��ٶ���
	double average_rpm = (motor_FL->rpm_cur + motor_FL->rpm_cur)/2;
	double average_rps = average_rpm/60;//��ÿ���Ӷ���ת�ĵ�λ��ת������ת��ÿ�����ת
	//ֱ���ٶ��ϱ���ROSϵͳ
	robot_linear_vel_x = average_rps * wheel_circumference;//ÿ���Ӷ���ת��ת�ٳ�����̥�Ļ�����Ҳ����һȦ�ĳ��ȣ�����ת������ֱ���ٶ�
}


//ֹͣ���к���
void robot_base::stop(){
	motor_FL->set_rpm(0);
	motor_BL->set_rpm(0);
	motor_FR->set_rpm(0);
	motor_BR->set_rpm(0);
}


