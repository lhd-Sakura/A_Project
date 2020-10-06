#include<reg51.h>
#include"main.h"

sbit OUT_A = P2^0;
sbit OUT_B = P2^1;

void timerTL0_inter() interrupt 1
{
	OUT_A = ~OUT_A;
	TL0 = 0;

}



void timerTH0_inter() interrupt 3
{
	OUT_B = ~OUT_B;
	TH0 = 128;
	
}


void main()
{
	P2 = 0xFF;
	
	//定时器T0初始化
	TL0 = 0;                   //TL0初始值
	TH0 = 128;                 //TH0初始值
	TMOD = 3;                  //定时器工作方式3
	ET0 = 1;                   //使能T0中断
	ET1 = 1;                   //T1中断
	EA = 1;                    //打开全局中断
	
	TR0 = 1;                   //启动TL0定时器
	TR1 = 1;                   //启动TL1定时器
	
	while(1);
	
}




