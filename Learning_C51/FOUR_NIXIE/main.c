#include<reg51.h>
#include"main.h"
#include"delay.h"
//不显示小数点
uchar code DIS_CODE[ ]={0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void main()
{
	uchar i=0;
	while(1)
	{
		for(i=0;i<4;i++)
		{
			P1=(1<<i);
			P2=DIS_CODE[i];
			delay_ms(1500);
		
		}
	}

}






/*实验程序


//数码管显示码（显示小数点）
uchar code DIS_CODE[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};

void main()
{
	uchar i=0;
	while(1)
	{
		for(i=0;i<10;i++)
		{
			P1=0x0F;                   //同时位选四位数码管
			P2=DIS_CODE[i];
			delay_ms(1500);
			P1=0x00;
			P2=DIS_CODE[i];
			delay_ms(1500);
		
		
		}
	
	}




}


*/

