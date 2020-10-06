#include<reg51.h>
#include"main.h"
#include"delay.h"


uchar code DIS_CODE[12] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0xF3};

void disp_num(uchar num)
{
	uchar sep_num = 0;
	uchar ten_num = 0;
	
	sep_num = num%10;
	ten_num = (num%100)/10;
	
	P2 = 0xFE;
	P0 = DIS_CODE[ten_num];
	delay_ms(5);
	
	P2 = 0xFD;
	P0 = DIS_CODE[sep_num];
	delay_ms(5);

}



void int0_inter() interrupt 0 
{
	TL1 = 0;

}


void timer_inter() interrupt 3
{
	TL1 = 0;
	
}


void main()
{
	uchar num = 0;
	P0 = 0xFF;
	P2 = 0xFF;
	
	
	//Int0初始化
	IT0 = 1;
	EX0 = 1;
	
	//计数器C1初始化
	TL1 = 0;
	TH1 = 0;
	TMOD = 0x60;
	ET1 = 1;
	EA = 1;
	
	
	TR1 = 1;
	
	while(1)
	{
		num = TL1;
		disp_num(num);
		

	}
	

}






















