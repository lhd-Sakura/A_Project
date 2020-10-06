#include<reg51.h>
#include"main.h"
#include"delay.h"

//共阴极数码管显示码
uchar code DIS_CODE[]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00};


//优化程序
void show_data(uint year,uchar month,uchar day)
{
	uint tmp;
	
	//年份显示
	tmp=year/1000;
	P1=0xFE;
	P2=DIS_CODE[tmp];
	delay_ms(1);
	
	tmp=year%1000;
	tmp=tmp/100;
	P1=0xFD;
	P2=DIS_CODE[tmp];
	delay_ms(1);
	
	tmp=year%100;
	tmp=tmp/10;
	P1=0xFB;
	P2=DIS_CODE[tmp];
	delay_ms(1);
	
	tmp=year%10;
	P1=0xF7;
	P2=DIS_CODE[tmp];
	delay_ms(1);
	
	//月份显示
	tmp=month/10;
	P1=0xEF;
	P2=DIS_CODE[tmp];
	delay_ms(1);
	
	tmp=month%10;
	P1=0xDF;
	P2=DIS_CODE[tmp];
	delay_ms(1);
	
	//日期显示
	tmp=day/10;
	P1=0xBF;
	P2=DIS_CODE[tmp];
	delay_ms(1);
	
	tmp=day%10;
	P1=0x7F;
	P2=DIS_CODE[tmp];
	delay_ms(1);
	

}


void main()
{
	while(1)
	{
		show_data(2019,7,19);
	
	}

}


















/*
//显示日期
void main()
{
	while(1)
	{
		P1=0xFE;
		P2=DIS_CODE[2];
		delay_ms(1);
		P1=0xFD;
		P2=DIS_CODE[0];
		delay_ms(1);
		P1=0xFB;
		P2=DIS_CODE[1];
		delay_ms(1);
		P1=0xF7;
		P2=DIS_CODE[9];
		delay_ms(1);
		P1=0xEF;
		P2=DIS_CODE[0];
		delay_ms(1);
		P1=0xDF;
		P2=DIS_CODE[9];
		delay_ms(1);
		P1=0xBF;
		P2=DIS_CODE[0];
		delay_ms(1);
		P1=0x7F;
		P2=DIS_CODE[6];
		delay_ms(1);
		
		
		
	}

}
*/
