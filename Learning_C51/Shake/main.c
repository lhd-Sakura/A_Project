#include<reg51.h>
#include"main.h"
#include"delay.h"

//引脚定义
sbit K1 = P3^2;
sbit K2 = P3^3;
sbit LED1 = P2^5;
sbit LED2 = P2^6;

//数码管显示码
uchar code DIS_CODE[12]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0x0C};

void main()
{
	uchar key_val = 0;
	
	//端口初始化
	P0 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	
	key_val = 0xFF;      //覆盖两个按键，观察按键值有无变动
	P0 = DIS_CODE[11];
	while(1)
	{
		if(key_val != P3)
		{
			key_val = P3;
			
			if(K1==0)                   //延迟10ms消除抖动（错过抖动时间）再次判断
			{
				delay_ms(10);
				if(K1 == 0)
				{
					LED1 = 0;
					LED2 = 1;
					P0 = DIS_CODE[1];
				
				}
				
			}
			
			else if(K2==0)
			{
				delay_ms(10);              //
				if(K2==0)
				{
					LED1 = 1;
					LED2 = 0;
					P0 = DIS_CODE[2];
					
				}	
				
				
				
			}
			
		
		}
		
		delay_ms(20);
	}

}



