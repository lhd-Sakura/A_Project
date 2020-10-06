#ifndef TM1637_H
#define TM1637_H
 
#include "user_system.h"
 
 
#define DIO	PCout(3) 
#define SCLK PCout(2) 
#define RCLK PCout(0) 
 
//IO��������
#define TM1637_DIO_IN()     {GPIOC->CRL&=0XFFFF0FFF;GPIOC->CRL|=8<<12;}
#define TM1637_DIO_OUT()    {GPIOC->CRL&=0XFFFF0FFF;GPIOC->CRL|=3<<12;}
 
void TM1637_Init(void);		// ����ܳ�ʼ��
void LED4_Display (void);	// LED��ʾ
void LED_OUT(u16 X);		// LED���ֽڴ�����λ����
void Seconds(u32 *count);	// ���ϼ���
void SetNum(u16 x);			// ������λ��ʼ����
void PlayVoltage(float v);	// ���õ�ѹ ������
#endif
