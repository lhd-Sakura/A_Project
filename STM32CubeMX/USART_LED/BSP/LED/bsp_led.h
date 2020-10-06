#ifndef __BSP_LED_H
#define __BSP_LED_H



#include "stm32f1xx_hal.h"
#include "main.h"
#include "gpio.h"



#define   GPIOx             GPIOC
#define   GPIO_PIN_x        LED_4_Pin
#define   GPIO_PIN_y        LED_5_Pin






void LED_ON(uint16_t GPIO_Pin);
void LED_OFF(uint16_t GPIO_Pin);



/* void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)*/







#endif /* __BSP_LED_H */












