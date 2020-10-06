#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
	
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	delay_init();
	while(1) 
	{
			printf("假期时间余额不足！！！,\r\n");
		  delay_ms(1000);
			LED_BLUE = 1;
			delay_ms(1000);
			LED_BLUE = 0;
			delay_ms(1000);

	}	
}

