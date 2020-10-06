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
/* ����Ϊϵͳȫ���� */
#define SYSTEM_VER 0x1708 /* ϵͳ�汾�� */
#define DEBUG  /* printf���أ����ڵ��� */
#define PI 3.1415926535898

extern uint8_t cmd_flag;  /* ROS��λ��ָ���־ */
extern float cmd_liner_vel_x;  /* ROS��λ��ָ���־ */
extern float cmd_liner_vel_y;  /* ROS��λ��ָ���־ */
extern float cmd_angular_rad_z;  /* ROS��λ��ָ���־ */
extern float set_p;  /* ROS pid */
extern float set_i;
extern float set_d;
extern uint32_t speed1_L,speed2_L,speed1_R,speed2_R; /* ��·�ٶ� */
void user_system_init();
void user_system_thread_0();


#endif /* __USER_SYSTEM_H_ */
