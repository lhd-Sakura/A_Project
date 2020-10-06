#ifndef __BSP_SYSTEM_H
#define __BSP_SYSTEM_H

//include
#include "main.h"
#include "usart.h"
#include "gpio.h"

#include"bsp_temp.h"





//led config
#define   GPIOx             GPIOC
#define   GPIO_PIN_x        LED_4_Pin
#define   GPIO_PIN_y        LED_5_Pin



//usart config
#define   USART_x    &huart1
#define   size       8
#define   Timeout    3   








/*
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
*/




void LED_ON(uint16_t GPIO_Pin);
void LED_OFF(uint16_t GPIO_Pin);
void USART_TX(uint8_t data[size]);







#endif /* __BSP_SYSTEM_H */












