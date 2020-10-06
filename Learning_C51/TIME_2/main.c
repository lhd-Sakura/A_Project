//本实验proteus仿真使用TIME_1的仿真实验

#include<reg51.h>
#include"main.h"

sbit OUT_PIN = P2^0;

void timer0_inter() interrupt 1
{
	OUT_PIN = ~OUT_PIN;
	
}

void main()
{
	P2 = 0xFF;
	
	TL0 = 0x06;                 //定时器初始值 
	TH0 = 0x06;                 //TH0=256-250
	TMOD = 2;
	ET0 = 1;                    //打开T0中断
	EA = 1;
	
	TR0 = 1;                    //启用T0定时器
	
	while(1);
	

}





