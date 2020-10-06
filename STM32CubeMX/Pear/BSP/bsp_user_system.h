#ifndef __USER_SYSTEM_H
#define __USER_SYSTEM_H




/* C LIB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


/* project LIB */
#include "main.h"
//#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stm32l4xx_hal.h"

#include "lcd.h"




/* function define */
//LED.c
void LED_ON( void );
uint32_t hcsr04_read(void);





/* define */
#define RXBUFFERSIZE  256

#define TRIG GPIO_PIN_9
#define ECHO GPIO_PIN_8

#define LCDSIZE       36
#define BASIC_X       10
#define BASIC_Y       50



















#endif /* __USER_SYSTEM_H_ */
