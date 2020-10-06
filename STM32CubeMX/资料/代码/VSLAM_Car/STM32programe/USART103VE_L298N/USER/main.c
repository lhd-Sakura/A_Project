#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "L298N.h"	
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	delay_init();
	Motor_12_Config(); //298���������ʼ��
	while(1) 
	{
			printf("����ʱ�����㣡����,\r\n");
		  delay_ms(1000);
			LED_BLUE = 1;
			delay_ms(1000);
			LED_BLUE = 0;
			delay_ms(1000);
			Motor_1_PRun(); //��ת
			Motor_2_PRun();
			
			delay_ms(10000); //ת����
			delay_ms(10000);
			delay_ms(10000);
			
			Motor_1_NRun();  //��ת
			Motor_2_NRun();
				
			delay_ms(10000); //ת����
			delay_ms(10000);
			delay_ms(10000);
			
			Motor_1_STOP();  //ֹͣ
			Motor_2_STOP();
			
			delay_ms(10000);  //ͣ����
			delay_ms(10000);
			delay_ms(10000);

	}	
}
