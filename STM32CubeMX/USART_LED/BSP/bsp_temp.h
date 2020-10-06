#ifndef __BSP_TEMP_H
#define __BSP_TEMP_H




#define OK 1 
#define ERROR 0 
 
//�����ķ���ֵ��ʾ��ȡ�����Ƿ�ɹ� OK ��ʾ�ɹ� ERROR ��ʾʧ�� 
extern unsigned char DHT11_ReadTempAndHumi(void); 

typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable    �޷���8λ���ͱ���  */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable    �з���8λ���ͱ���  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable    �޷���16λ���ͱ��� */

#define uchar unsigned char
#define uint unsigned int
	
#define      Data              HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)			//������������
#define      Data_1						 HAL_GPIO_WritePin(GPIOx,  GPIO_Pin_Data, GPIO_PIN_SET);  
#define      Data_0            HAL_GPIO_WritePin(GPIOx,  GPIO_Pin_Data, GPIO_PIN_RESET);  


#define      GPIOx              GPIOB
#define      GPIO_Pin_Data      GPIO_PIN_12












#endif /* __BSP_TEMP_H_ */

