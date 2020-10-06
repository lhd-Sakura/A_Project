#ifndef __USER_SYSTEM_H
#define __USER_SYSTEM_H




#include "main.h"
#include "usart.h"
#include "gpio.h"



//������ֲ

#define  P2_0     HAL_GPIO_ReadPin(GPIOA,  GPIO_PIN_11 ) 
#define  Data_0_time    4


typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  �޷���8λ���ͱ���  */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable		  �з���8λ���ͱ���  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	  �޷���16λ���ͱ��� */
typedef signed   int   S16;      /* defined for signed 16-bits integer variable 	  �з���16λ���ͱ��� */
typedef unsigned long  U32;      /* defined for unsigned 32-bits integer variable 	  �޷���32λ���ͱ��� */
typedef signed   long  S32;      /* defined for signed 32-bits integer variable 	  �з���32λ���ͱ��� */
typedef float          F32;      /* single precision floating point variable (32bits) �����ȸ�������32λ���ȣ� */
typedef double         F64;      /* double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ� */







/* C LIB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


//GPIO����
#define  GPIOx      GPIOA
#define  GPIO_Pin   GPIO_PIN_11



//��������
void Delay(U16 j);
void  Delay_10us(void);
void  COM(void);
void RH(void);
void USER_INIT(void);	
void SendData(U8 *a);


#endif /* __USER_SYSTEM_H_ */
