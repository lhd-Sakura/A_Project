#include"bsp_system.h"



void LED_ON(uint16_t GPIO_Pin)
{
	 HAL_GPIO_WritePin(GPIOx,GPIO_Pin, GPIO_PIN_RESET);
	
}


void LED_OFF(uint16_t GPIO_Pin)
{
	 HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	
}






