#include "user_comm.h"

#define DEBUG
serialData serial_rx_data;
void user_comm_init(void){
		serial_rx_data.syn = serial_rx_data.syn_CR = serial_rx_data.syn_LF = serial_rx_data.type = 0;
	do{
	}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data,1));//只进行一个字节一个字节读取，因为又同步码和结束码
	
	print_usart1("user_comm_init() OK\r\n");
}

//通过串口3吧消息打印到串口
//可变参数...的数据会收到va_list ap里面，根据第二个参数的指定格式进行匹配
void print_usart1(const char *format,...)
{
#ifdef DEBUG
	static char buf[128];
	va_list ap;
	va_start(ap,format);
	//huart3是usart.c中定义的串口3，因为串口1用不了/没用到
	
	while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX); //循环发送,直到发送完毕
	if(vsprintf(buf,format,ap)>0){//把数据整合到buf里通过DMA发出去
		HAL_UART_Transmit_DMA(&huart1,(uint8_t *)buf,strlen(buf));
	}
#endif
}
//串口接收中断回调函数，一个字节一个字节接收，判断同步码，然后就是各种逻辑
void USART1_IRQHandler(UART_HandleTypeDef *huart){
	if(huart == &huart3){
		if(serial_rx_data.syn != _SERIAL_SYN_CODE_START){//判断是不是同步码，如果不是就再次接收一个，看是不是，如果还不是就结束程序，等待下一个接收的数据来，然后再判断
				do{
				}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data,1));//第二个参数是接收数据的缓冲区，第三个参数是接收数据的大小
				return ;
		}
		if(serial_rx_data.syn == _SERIAL_SYN_CODE_START && serial_rx_data.syn_CR !='\r' && serial_rx_data.syn_LF !='\n'){//如果在这个字节接收到了同步位，且还没有接收到数据位，那么这个字节也收了，然后程序结束
			do{
			}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data+1,sizeof(serialData)-1));//收一次，大小当然也要减少一个
			return ;
		}
		
		if(serial_rx_data.syn != _SERIAL_SYN_CODE_START//如果都不是，那么debug错误信息，然后将所有数据都置位0
			||serial_rx_data.syn_CR !='\r'
			||serial_rx_data.syn_CR !='\n')
		{
			print_usart1("serial data error \r\n");
			serial_rx_data.syn = serial_rx_data.syn_CR = serial_rx_data.syn_LF = serial_rx_data.type = 0;
			do{
			}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data,1));
			return;
		}
		
		if(serial_rx_data.type ==VAL_VEL){//VAL_VEL是枚举类型3，将数据存起来
			cmd_liner_vel_x = serial_rx_data.dat.vel.liner[0];
			cmd_liner_vel_y = serial_rx_data.dat.vel.liner[1];
			cmd_angular_rad_z = serial_rx_data.dat.vel.angular[2];
			cmd_flag = 0;
		}
		
		if(serial_rx_data.type == VAL_PID){//如果枚举类型是4，也就是PID，将数据存起来
			set_p = serial_rx_data.dat.pid[0];
			set_i = serial_rx_data.dat.pid[1];
			set_d = serial_rx_data.dat.pid[2];
		}
		serial_rx_data.syn = serial_rx_data.syn_CR = serial_rx_data.syn_LF = serial_rx_data.type = 0;
		do{
		}while(HAL_OK != HAL_UART_Receive_IT(&huart3,(uint8_t*)&serial_rx_data,sizeof(serialData)));

	}
}
