#ifndef __USER_SYSTEM_H
#define __USER_SYSTEM_H
/* HAL LIB */
#include "main.h"
//#include "adc.h"
//#include "dma.h"
//#include "iwdg.h"
//#include "rtc.h"
//#include "spi.h"
//#include "tim.h"
#include "usart.h"
#include "gpio.h"
/* C LIB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
//#include <AT89X51.H>


void user_system_init();
void user_system_thread_0();


#endif /* __USER_SYSTEM_H_ */
