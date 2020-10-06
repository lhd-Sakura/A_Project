
#if 0
#include"reg51.h"

sbit LED = P0^0

void main()
{
P0 = 0xFE;    //总线操作

LED = 0;     //位操作



}

#endif











#include"stm32f10x.h"


int main()
{

#if 0 
	//打开 GPIO 端口时钟
	*(unsigned int *)0x40021018 |= ( (1)<<2);
	
	//配置IO口为输出模式,CRL寄存器,选定哪个GPIO口（GPIOA）
	*(unsigned int *)0x40010800 |= ( (0x0F) << (4*1));
	*(unsigned int *)0x40010800 |= ( (1) << (4*1));
	
	//控制ODR寄存器,LED点亮,(PA1)
	
	*(unsigned int *)0x4001080C &= ~(1<<1);
	
	#else
	
//打开 GPIO 端口时钟
	RCC_APB2ENR |= ( (1)<<2);
	
//配置IO口为输出模式,CRL寄存器
//CRL、CHR寄存器用来配置GPIO端口模式，CRL低八位（0-7）、CHR高八位（8-15）
	GPIOA_CRL |= ( (1) << (4*1));
	
//控制ODR寄存器,LED点亮,(PA1)，对于C8T6，点亮LED，PA1=0;
	
//	GPIOA_ODR &= ~(1<<1);	
//	GPIOA_ODR |= (1<<1);	


while(1)
{

	GPIOA_BRR  |= (1<<1);
	delay1s();
	GPIOA_BSRR |= (1<<1);	
  delay1s();
}


	#endif
	
	

}



//置位1  |=        ,    清0    &=~(1<<0);















void SystemInit()
{

     //函数调用，骗过编译器，初始文件的汇编语言，调用这个固件库中的函数

}


