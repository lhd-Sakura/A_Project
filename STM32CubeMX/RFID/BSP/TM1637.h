#ifndef TM1637_H
#define TM1637_H
 
#include "user_system.h"
 
 
#define DIO	PCout(3) 
#define SCLK PCout(2) 
#define RCLK PCout(0) 
 
//IO方向设置
#define TM1637_DIO_IN()     {GPIOC->CRL&=0XFFFF0FFF;GPIOC->CRL|=8<<12;}
#define TM1637_DIO_OUT()    {GPIOC->CRL&=0XFFFF0FFF;GPIOC->CRL|=3<<12;}
 
void TM1637_Init(void);		// 数码管初始化
void LED4_Display (void);	// LED显示
void LED_OUT(u16 X);		// LED单字节串行移位函数
void Seconds(u32 *count);	// 向上计数
void SetNum(u16 x);			// 设置四位初始数字
void PlayVoltage(float v);	// 设置电压 浮点数
#endif
