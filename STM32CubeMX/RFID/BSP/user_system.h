#ifndef __USER_SYSTEM_H
#define __USER_SYSTEM_H
/* HAL LIB */
#include "main.h"
#include "iwdg.h"
#include "gpio.h"



/* C LIB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
//#include <AT89X51.H>


/*other LIB*/
 
#include "TM1637.h"




void user_system_init();
void user_system_thread_0();

#define u8 unsigned char 
#define u16 unsigned short 
#define u32 unsigned long


#endif /* __USER_SYSTEM_H_ */
