#ifndef __BSP_TEMP_H
#define __BSP_TEMP_H

#include"bsp_user_system.h"

#define OK 1 
#define ERROR 0 
 
//函数的返回值表示读取数据是否成功 OK 表示成功 ERROR 表示失败 
extern unsigned char DHT11_ReadTempAndHumi(void); 

typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable    无符号8位整型变量  */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable    有符号8位整型变量  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable    无符号16位整型变量 */

#define uchar unsigned char
#define uint unsigned int
	
#define      Data              HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)			//串行数据输入
#define      Data_1						 HAL_GPIO_WritePin(GPIOx,  GPIO_Pin_Data, GPIO_PIN_SET);  
#define      Data_0            HAL_GPIO_WritePin(GPIOx,  GPIO_Pin_Data, GPIO_PIN_RESET);  


#define      GPIOx              GPIOB
#define      GPIO_Pin_Data      GPIO_PIN_12




typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
} DHT11_Data_TypeDef;

void                     DHT11_Init                      ( void );
uint8_t                  DHT11_Read_TempAndHumidity      ( DHT11_Data_TypeDef * DHT11_Data );

#define DHT11_DELAY_US(us)  delay_us(u16 t)
#define DHT11_DELAY_MS(ms)  HAL_Delay(uint32_t Delay)









#endif /* __BSP_TEMP_H_ */

