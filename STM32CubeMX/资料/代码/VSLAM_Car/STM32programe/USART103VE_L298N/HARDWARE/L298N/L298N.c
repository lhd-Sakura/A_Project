#include "L298N.h"  //����ledͷ�ļ�
#include "stm32f10x.h"  //����STM32�ٷ���
#include "stm32f10x_rcc.h"  //����STM32��RCCʱ�ӿ�
#include "delay.h"       //��ʱ��
 
void Motor_12_Config(void)  //�����ʼ������
{
	GPIO_InitTypeDef GPIO_InitStructure;   //����GPIO_InitTypeDef�ṹ��
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);  //��������ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //����IN����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //ͨ���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��GPIOA�����Ų���,д��
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5); //������������
}
 
void Motor_1_STOP(void)
{
	IN1(High);
	IN2(High);
}
 
void Motor_1_PRun(void)
{
	IN1(Low);
	IN2(High);
}
 
void Motor_1_NRun(void)
{
	IN1(High);
	IN2(Low);
}
 
void Motor_2_STOP(void)
{
	IN3(High);
	IN4(High);
}
 
void Motor_2_PRun(void)
{
	IN3(Low);
	IN4(High);
}
 
void Motor_2_NRun(void)
{
	IN3(High);
	IN4(Low);
}