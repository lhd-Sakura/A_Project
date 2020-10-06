#include "bsp_user_system.h"



void delay_us(uint32_t udelay)
{
  __IO uint32_t Delay = udelay * 72 / 8;//(SystemCoreClock / 8U / 1000000U)
    //见stm32f1xx_hal_rcc.c -- static void RCC_Delay(uint32_t mdelay)
  do
  {
    __NOP();
  }
  while (Delay --);
}




//发送脉冲
uint32_t hcsr04_read()
{
	uint32_t local_time = 0;
	uint32_t sensor_time = 0;
	uint16_t distance = 0;
	
	HAL_GPIO_WritePin(GPIOC, TRIG_Pin, GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(GPIOC, TRIG_Pin, GPIO_PIN_RESET);
	
	//等待高电平
	while( !(HAL_GPIO_ReadPin(GPIOA,ECHO_Pin)) );
	while( HAL_GPIO_ReadPin(GPIOA,ECHO_Pin) ) 
	{
		local_time++;
		delay_us(1);
	}
	
	sensor_time = local_time;
	distance = sensor_time * .034/2;
	
	
	
	return distance;
	
}












