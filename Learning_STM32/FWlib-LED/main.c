#if 0
#include"reg51.h"

sbit LED = P0^0

void main()
{
P0 = 0xFE;    //���߲���

LED = 0;     //λ����



}

#endif




#include"stm32f10x.h"
#include"stm32f10x_gpio.h"
#include"delay.h"




int main()
{

#if 0 
	//�� GPIO �˿�ʱ��
	*(unsigned int *)0x40021018 |= ( (1)<<2);
	
	//����IO��Ϊ���ģʽ,CRL�Ĵ���,ѡ���ĸ�GPIO�ڣ�GPIOA��
	*(unsigned int *)0x40010800 |= ( (0x0F) << (4*1));
	*(unsigned int *)0x40010800 |= ( (1) << (4*1));
	
	//����ODR�Ĵ���,LED����,(PA1)
	
	*(unsigned int *)0x4001080C &= ~(1<<1);
	
#elif 0
	
//�� GPIO �˿�ʱ��
	RCC_APB2ENR |= ( (1)<<2);
	
//����IO��Ϊ���ģʽ,CRL�Ĵ���
//CRL��CHR�Ĵ�����������GPIO�˿�ģʽ��CRL�Ͱ�λ��0-7����CHR�߰�λ��8-15��
	GPIOA_CRL |= ( (1) << (4*1));
	
//����ODR�Ĵ���,LED����,(PA1)������C8T6������LED��PA1=0;
	
//	GPIOA_ODR &= ~(1<<1);	
//	GPIOA_ODR |= (1<<1);	


while(1)
{
	GPIOA_BRR  |= (1<<1);
	delay1s();
	GPIOA_BSRR |= (1<<1);	
  delay1s();
}


#elif 0
	RCC->APB2ENR |= ( (1)<<2);
	GPIOA->CRL |= ( (1) << (4*1));

while(1)
{
	GPIOA->BRR  |= (1<<1);
	delay1s();
	GPIOA->BSRR |= (1<<1);	
  delay1s();
}



#elif 0
	RCC->APB2ENR |= ( (1)<<2);
	GPIOA->CRL |= ( (1) << (4*1));

while(1)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	delay1s();
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
  delay1s();
}



#elif 1
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC->APB2ENR |= ( (1)<<2);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	


while(1)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	delay1s();
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
  delay1s();
}






	#endif
	
	














}



//��λ1  |=        ,    ��0    &=~(1<<0);















void SystemInit()
{

     //�������ã�ƭ������������ʼ�ļ��Ļ�����ԣ���������̼����еĺ���

}


