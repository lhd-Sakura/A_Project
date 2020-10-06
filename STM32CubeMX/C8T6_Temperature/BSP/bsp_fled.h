#ifndef __BSP_FLED_H
#define __BSP_FLED_H

#include"bsp_user_system.h"

//头文件定义
#define      DIO               HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)			//串行数据输入
#define      CLK            	 HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)		//打入信号————上升沿有效
#define      DIO_1						 HAL_GPIO_WritePin(GPIOx,  GPIO_Pin_DIO, GPIO_PIN_SET);  
#define      DIO_0             HAL_GPIO_WritePin(GPIOx,  GPIO_Pin_DIO, GPIO_PIN_RESET);  
#define      CLK_1             HAL_GPIO_WritePin(GPIOx,  GPIO_Pin_CLK, GPIO_PIN_SET);  
#define      CLK_0             HAL_GPIO_WritePin(GPIOx,  GPIO_Pin_CLK, GPIO_PIN_RESET);  

#define      GPIOx              GPIOB
#define      GPIO_Pin_CLK       GPIO_PIN_8
#define      GPIO_Pin_DIO       GPIO_PIN_9


#define uchar unsigned char
	

//段码表
static int8_t Tab[] = {0x3f,0x06,0x5b,0x4f,
                       0x66,0x6d,0x7d,0x07,
                       0x7f,0x6f,0x77,0x7c,
                       0x39,0x5e,0x79,0x71};//0~9,A,b,C,d,E,F      


//function
void I2CStart(void);                                   //1637 开始 
void I2Cask(void);               					  	         //1637应答 
void I2CStop(void);            							           // 1637 停止 
void I2CWrByte(unsigned char oneByte);                 //写一个字节 
void FLED_ON(int8_t a,int8_t b,int8_t c,int8_t d);     //数码管显示




#endif /* __BSP_FLED_H_ */
