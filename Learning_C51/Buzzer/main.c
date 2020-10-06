#include<reg51.h>
#include"main.h"
#include"delay.h"

sbit LED = P0^1;
sbit SOUND = P2^0;
sbit KEY1 = P3^0;
sbit KEY2 = P3^2;
sbit KEY3 = P3^4;

void speak(uchar timer)
{
	uint i = 0;
	uchar j = 0;
	for(i = 400;i>0;i--)
	{
		SOUND = ~SOUND;
		LED = ~LED ;
		for(j=timer;j>0;j--);                     //用延时长度来控制频率

	}
	LED = 1;
	SOUND = 0;

}


void main()
{
	uchar key_num = 0;
	LED = 1;
	SOUND = 0;
	
	
	while(1)
	{
		if(key_num != P3)
		{
			key_num = P3;
			delay_ms(10);
			if(key_num == P3)
			{
				if(KEY1 == 0)
				{
					speak(80);
					
				}
				
				if(KEY2==0)
				{
					speak(160);
				}
				
				if(KEY3==0)
				{
					speak(240);
				
				}
				
			
			}	
			
		
		}
	
	
	
	}
	

}



















