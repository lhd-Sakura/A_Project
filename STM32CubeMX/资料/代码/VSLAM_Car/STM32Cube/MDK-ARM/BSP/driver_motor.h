#ifndef  __DRIVER_MOTOR_H
#define  __DRIVER_MOTOR_H 
#include "user_system.h"
#include "stdlib.h"


//��֮ǰ�����õ��Ķ������ϵ�һ���������
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
								uint16_t pwm_max);//���캯��
		~motor_driver(){}//��������
		/*pid����*/
		static float _p;//���þ�̬��������c++��ÿ���綯�����ǹ�����Щ��̬�����ģ���cpp�ļ��Ŀ�ͷ�͸���ֵ
		static float _i;
		static float _d;
		uint16_t tick_inc;
		/*�����*/
		double err_total;
		double err_previous;
		/*��ǰת��*/
		float rpm_cur;
		/*��������ת��*/
		static float _motor_max_rpm;
		/*����ת�ٺ���������PID����*/
		void set_rpm(float rpm);
		static void set_pid(float p,float i,float d);
		/*�����ú���*/
		int16_t get_tick_inc();//��õ�ǰtick������������
		double read_rpm();//��ȡת��
		void spin(int16_t pwm);//����������ת
	
	
	private:
		uint8_t _id;
		TIM_HandleTypeDef _driverTimer;
		TIM_HandleTypeDef _encode_driverTimer;
		uint32_t _pwm_channelA;
		uint32_t _pwm_channelB;	
		uint32_t _encode_channel;		
		int8_t _direction;
		uint16_t _pwm_max;//PWM���ֵ
		int32_t tick_last;//�������һ��tick
		int32_t tick_cur;//��ǰ�ı�������tick
		int32_t tick_total;//�ܺ�
		int8_t _encoder_direction;//��ת��ת����ֵ����-1��1
		uint32_t last_milli_time;//����ת���õ���һ�ε�ʱ��
		static float _ticks_per_rev;//������תһȦ�����tick
};



#endif

