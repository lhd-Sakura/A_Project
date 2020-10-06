#include<reg51.h>
#include"main.h"
#include"delay.h"

sbit K1 = P3^2;

uchar code DIS_CODE[12]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0x0C};


//显示数字
void disp_num(uchar num)
{
	uchar sep_num;           //个位
	uchar ten_num;           //十位
	
	sep_num = num%10;
	ten_num = num/10;
	P2 = 0x02;
	P0 = DIS_CODE[sep_num];
	delay_ms(5);
	P2 = 0x01;
	P0 = DIS_CODE[ten_num];
	delay_ms(5);
	
}



void main()
{
	uchar key_val = 0;
	uchar num = 0;
	uchar dis_num = 0;
	
	P0 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	key_val = 0xFF;
	
	while(1)
	{
		if(key_val != P3)                 //判断按键状态的改变，按下和抬起
		{
			key_val = P3;                 
			disp_num(dis_num);
			while(K1 == 0)                  //按键按下，一直计时，抬起按键计时结束
			{
				disp_num(dis_num);
				if(++num>100)                 //临时充当计时器
				{
					num = 101;
				}
				
			}
			
			
			//根据num处理显示数字
			if(num>0 && num<=100)
			{
				dis_num++;
				
			}	
			else if(num>100)
			{
				dis_num +=10;
				
			}
			num = 0;
				
		}
		
		disp_num(dis_num);
		
		
	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

