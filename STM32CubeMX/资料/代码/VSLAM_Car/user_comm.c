#include "user_comm.h"

#define DEBUG
serialData serial_rx_data;
void user_comm_init(void){
		serial_rx_data.syn = serial_rx_data.syn_CR = serial_rx_data.syn_LF = serial_rx_data.type = 0;
	do{
	}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data,1));//ֻ����һ���ֽ�һ���ֽڶ�ȡ����Ϊ��ͬ����ͽ�����
	
	print_usart1("user_comm_init() OK\r\n");
}

//ͨ������3����Ϣ��ӡ������
//�ɱ����...�����ݻ��յ�va_list ap���棬���ݵڶ���������ָ����ʽ����ƥ��
void print_usart1(const char *format,...)
{
#ifdef DEBUG
	static char buf[128];
	va_list ap;
	va_start(ap,format);
	//huart3��usart.c�ж���Ĵ���3����Ϊ����1�ò���/û�õ�
	
	while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX); //ѭ������,ֱ���������
	if(vsprintf(buf,format,ap)>0){//���������ϵ�buf��ͨ��DMA����ȥ
		HAL_UART_Transmit_DMA(&huart1,(uint8_t *)buf,strlen(buf));
	}
#endif
}
//���ڽ����жϻص�������һ���ֽ�һ���ֽڽ��գ��ж�ͬ���룬Ȼ����Ǹ����߼�
void USART1_IRQHandler(UART_HandleTypeDef *huart){
	if(huart == &huart3){
		if(serial_rx_data.syn != _SERIAL_SYN_CODE_START){//�ж��ǲ���ͬ���룬������Ǿ��ٴν���һ�������ǲ��ǣ���������Ǿͽ������򣬵ȴ���һ�����յ���������Ȼ�����ж�
				do{
				}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data,1));//�ڶ��������ǽ������ݵĻ������������������ǽ������ݵĴ�С
				return ;
		}
		if(serial_rx_data.syn == _SERIAL_SYN_CODE_START && serial_rx_data.syn_CR !='\r' && serial_rx_data.syn_LF !='\n'){//���������ֽڽ��յ���ͬ��λ���һ�û�н��յ�����λ����ô����ֽ�Ҳ���ˣ�Ȼ��������
			do{
			}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data+1,sizeof(serialData)-1));//��һ�Σ���С��ȻҲҪ����һ��
			return ;
		}
		
		if(serial_rx_data.syn != _SERIAL_SYN_CODE_START//��������ǣ���ôdebug������Ϣ��Ȼ���������ݶ���λ0
			||serial_rx_data.syn_CR !='\r'
			||serial_rx_data.syn_CR !='\n')
		{
			print_usart1("serial data error \r\n");
			serial_rx_data.syn = serial_rx_data.syn_CR = serial_rx_data.syn_LF = serial_rx_data.type = 0;
			do{
			}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data,1));
			return;
		}
		
		if(serial_rx_data.type ==VAL_VEL){//VAL_VEL��ö������3�������ݴ�����
			cmd_liner_vel_x = serial_rx_data.dat.vel.liner[0];
			cmd_liner_vel_y = serial_rx_data.dat.vel.liner[1];
			cmd_angular_rad_z = serial_rx_data.dat.vel.angular[2];
			cmd_flag = 0;
		}
		
		if(serial_rx_data.type == VAL_PID){//���ö��������4��Ҳ����PID�������ݴ�����
			set_p = serial_rx_data.dat.pid[0];
			set_i = serial_rx_data.dat.pid[1];
			set_d = serial_rx_data.dat.pid[2];
		}
		serial_rx_data.syn = serial_rx_data.syn_CR = serial_rx_data.syn_LF = serial_rx_data.type = 0;
		do{
		}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data,sizeof(serialData)));

	}
}
