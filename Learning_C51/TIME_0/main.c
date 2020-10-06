#include<reg51.h>
#include"main.h"

sbit LED = P2^0;
uchar g_ucNum;

void int0_inter() interrupt 0 
{
	g_ucNum = 0;
	TL0 = 0x18;             //定时器赋初值TL0=（8192-5000）%32
	TH0 = 0x63;             //TH0=（8192-5000）/32  
	TR0 = 1;                //打开定时器T0
	
	
}




void int1_inter() interrupt 2
{
	TR0 = 0;                 //关闭定时器T0

}



void timer0_inter() interrupt 1
{
	g_ucNum++;
	
	TL0 = 0x18;              //定时器重新赋值
	TH0 = 0x63;
	
}


void main()
{
	g_ucNum = 0;
	P2 = 0xFF;
	
	//外部中断初始化
	IT0 = 1;                   //下降沿触发中断
	IT1 = 1;
	EX0 = 1;                    //打开外部中断
	EX1 = 1;
	
	//定时器T0初始化
	TMOD = 0;                   //定时器模式，工作方式0
	TL0 = 0x18;                 //定时器赋初值
	TH0 = 0x63;                 //TH0=（8192-5000）/32
	ET0 = 1;                    //使能T0中断
	
	EA = 1;
	
	while(1)
	{
		if(g_ucNum>=200)
		{
			g_ucNum = 0;
			LED = ~LED; 
		
		
		}
		
		
	
	}
	
	
	

}







