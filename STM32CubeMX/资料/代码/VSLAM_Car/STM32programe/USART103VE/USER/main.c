#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
	
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	delay_init();
	while(1) 
	{
			printf("����ʱ�����㣡����,\r\n");
		  delay_ms(1000);
			LED_BLUE = 1;
			delay_ms(1000);
			LED_BLUE = 0;
			delay_ms(1000);

	}	
}

