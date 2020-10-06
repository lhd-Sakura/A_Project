#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "L298N.h"	
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	delay_init();
	Motor_12_Config(); //298电机驱动初始化
	while(1) 
	{
			printf("假期时间余额不足！！！,\r\n");
		  delay_ms(1000);
			LED_BLUE = 1;
			delay_ms(1000);
			LED_BLUE = 0;
			delay_ms(1000);
			Motor_1_PRun(); //正转
			Motor_2_PRun();
			
			delay_ms(10000); //转三秒
			delay_ms(10000);
			delay_ms(10000);
			
			Motor_1_NRun();  //反转
			Motor_2_NRun();
				
			delay_ms(10000); //转三秒
			delay_ms(10000);
			delay_ms(10000);
			
			Motor_1_STOP();  //停止
			Motor_2_STOP();
			
			delay_ms(10000);  //停三秒
			delay_ms(10000);
			delay_ms(10000);

	}	
}
