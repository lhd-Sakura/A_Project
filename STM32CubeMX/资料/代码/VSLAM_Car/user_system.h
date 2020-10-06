#ifndef __USER_SYSTEM_H
#define __USER_SYSTEM_H
/* HAL LIB */
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "iwdg.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
/* C LIB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
/* USER LIB */
#include "user_comm.h"
/* 以下为系统全局量 */
#define SYSTEM_VER 0x1708 /* 系统版本号 */
#define DEBUG  /* printf开关，用于调试 */
#define PI 3.1415926535898

extern uint8_t cmd_flag;  /* ROS上位机指令标志 */
extern float cmd_liner_vel_x;  /* ROS上位机指令标志 */
extern float cmd_liner_vel_y;  /* ROS上位机指令标志 */
extern float cmd_angular_rad_z;  /* ROS上位机指令标志 */
extern float set_p;  /* ROS pid */
extern float set_i;
extern float set_d;
extern uint32_t speed1_L,speed2_L,speed1_R,speed2_R; /* 四路速度 */
void user_system_init();
void user_system_thread_0();


#endif /* __USER_SYSTEM_H_ */
