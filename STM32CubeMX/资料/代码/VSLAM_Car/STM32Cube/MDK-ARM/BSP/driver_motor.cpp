#include "driver_motor.h"
/*
�����ķ�����ʵ��
*/
#define Millisecond() HAL_GetTick()
#define constrain(value,low,high) ((value)<(low)?(low):((value)>(high)?(high):(value)))
extern uint32_t speed1_L,speed2_L,speed1_R,speed2_R;
/*PID��Ϣ*///Ԥ�ȸ���ֵ����Ϊpid�������Ǿ�̬�ģ����е���ɹ��������
float motor_driver::_p = 0.2;//P��������
float motor_driver::_i = 0.5;//I��������
float motor_driver::_d = 0.3;//D΢������

/* ������� */
float motor_driver::_ticks_per_rev = 1560;//������תһȦ�����tick����̥390�ߵ�
float motor_driver::_motor_max_rpm = 350;//��������ת�٣������д˲���������ǲ�һ�£�����pid������ᳬ��

//motor_driver��Ĺ��캯����������ֱֵ�Ӹ�ֵ����ĳ�Աֵ


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
		/* PWM����*/
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelA,0);	//��IN1
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelB,0);	//��IN2
	 HAL_TIM_PWM_Start(&_driverTimer,_pwm_channelA);
	 HAL_TIM_PWM_Start(&_driverTimer,_pwm_channelB);
	 HAL_TIM_IC_Start_IT(&_encode_driverTimer, _encode_channel);
		err_total = 0;
		err_previous = 0;
		_pwm_max = pwm_max;
		/* ��������ش���Ҳ��0 */
		_direction = direction;
		tick_total = 0; /* tick����� */
		tick_last = 0;
	
}


//1.9������ת�ٺ�����������ߵ��ת�ٲ����pwm��
void motor_driver::set_rpm(float rpm){
	int16_t _pwm;
	double err;
	
	rpm_cur = read_rpm();
	/* pid ����ת�����*/
	err = constrain(rpm,-_motor_max_rpm,_motor_max_rpm) - rpm_cur;
	err_total += err;
	
	err_total = constrain(err_total,-_pwm_max/_i,_pwm_max/_i);
	
	_pwm = _p*err + _i*err_total + _d*(err-err_previous);
	
	err_previous = err;
	
	/*pwm*/
	//����������ж�pwm����û�г������ֵ���궨�壬���ǲ������м�ֵ
	_pwm = constrain(_pwm,-_pwm_max,_pwm_max);
	/* <30 ~ 40��pwm�����������ת�������ںĵ� ,����С��40ֱ����0*/
	if(abs(_pwm) < 40)_pwm = 0;
	/* spin */
	spin(_pwm);
}


//��������TIM3��ͨ��1���ܽ���PA6����ӦTIM2��������PA0ͨ��1��PA1ͨ��2
//�ҵ������TIM3��ͨ��2���ܽ���PA7����ӦTIM4��������PB6ͨ��1��PB7ͨ��2
//�����������ʱ�����⣬�����ҵ����ת
/***********�������ƺ���**************/
/*
�����õ�������С����ÿ��������·PWM���ƣ��ܹ���·PWM���ƣ����������������ۣ�
������ʱ����ʹ�ٶȵ���Ȼ���ٷ���Ҳ������ʹPWMֵΪ0����ʱ�������Ϊ0�����ֹͣ�����������ڹ��Կ��ܻ���ת��
��ʱ���Կ���ת���Ƿ�Ϊ�㣬��Ϊ0ʱ���з�ת���ܹ���ֹͻȻ��ת����·��������⡣��Ȼ���Կ���S�����㷨��T�����㷨��

								**** ��·ǰ�� ****
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,450);	//��1��
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,450);	//��1��
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,450);	//��2��
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,450);	//��2��
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);

				 **** ��·���� ****
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);	//��1��
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,900);
	 
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);	//��1��
	 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,900);
	 
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,0);	//��2��
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,900);
	 
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,0);	//��2��
	 __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,900)
*/
void motor_driver::spin(int16_t pwm){
	//ͨ�����붼������д���ڷ���PWM��֮ǰ��Ҫ�Ƚ�������ʱ��Ĺ���
	/*����ʱ��*/
	if((rpm_cur > 0 && _direction ==1) || (rpm_cur < 0 && _direction == 0)){//�ж���ǰת����direction����һ�£�Ҳ���ǿ�ʼ����ת�л���
		////���Ƚ�����ͨ����PWM������0����Ȼ���ж���
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelA,0);	//��1��
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelB,0);	//��1��
		//���߰ѵ������оƬ��H���е���������ܶ���ֹһ��
	}
	if(_direction == 0)//��ת
	{
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelA,0);	//��1��
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelB,pwm);
	}
	if(_direction == 1)//��ת
	{
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelB,0);	//��1��
	 __HAL_TIM_SET_COMPARE(&_driverTimer,_pwm_channelA,pwm);
	}
}

/*
1.7����������
*/
//��ȡ��ߵ��ת��rpm
double motor_driver::read_rpm(){
	uint32_t cur_milli_time;
	double delta_mins_time;
  int16_t tick_cur;
	tick_cur = get_tick_inc();	
	cur_milli_time = Millisecond();//��õ�ǰ��ʱ��ĺ���ֵ
	delta_mins_time = (cur_milli_time - last_milli_time)/60000.0;//��ʱ�䴦��ɷ��ӣ���Ϊת�ٵ�λ��ÿ���Ӷ���ת
	rpm_cur = (tick_cur / _ticks_per_rev)/delta_mins_time;//������tickֵ����תһȦ��tickֵȻ���ٳ���ת���ķ���ʱ��õ��ľ���ת��ֵ��ת��ֵ��ÿ����Ϊ��λ
	
	last_milli_time = cur_milli_time;
	return rpm_cur;
}


/*
1.7��
*/
//��ȡ������tickֵ,�Ƕ�ȡ������tick
//��ȡ�ұߵ��������tick
int16_t motor_driver::get_tick_inc()
{
	/* ��ȡ��ǰ��������tick */
		switch(_id)
	{
		case 1:
			tick_cur = speed1_L;//��ȡtickֵ
			break;
		case 2:
			tick_cur = speed2_L;//��ȡtickֵ
			break;
		case 3:
			tick_cur = speed1_R;//��ȡtickֵ
			break;
		case 4:
			tick_cur = speed2_R;//��ȡtickֵ
			break;
	}
	if(abs(tick_cur-tick_last)>0xefffffff/2)
	{
		if(tick_cur > tick_last) /*��ת*/
		{
			tick_inc = -0xffff - tick_last + tick_cur;
		}else /* ��ת */
		{
			tick_inc = 0xffff - tick_last + tick_cur;
		}
	}else
	{
		tick_inc = tick_cur - tick_last;
	}
	tick_last = tick_cur;
	
	tick_inc *= _encoder_direction;/*��������������ӷ�*/
	
	tick_total += tick_inc;/*��̼�*/
	return tick_inc;
}

//����pid����
void motor_driver::set_pid(float p,float i,float d){
	_p = p;
	_i = i;
	_d = d;
}

