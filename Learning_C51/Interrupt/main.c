#include<reg51.h>
#include"main.h"
#include"delay.h"

uchar code DIS_CODE[12] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0xF3};

uint g_unDisNum;


//数码管上显示数字
void disp_num(uint num)
{
	uchar sep_num = 0;
	uchar ten_num = 0;
	uchar hund_num = 0;
	uchar thou_num = 0;
	
	sep_num = num%10;
	ten_num = (num%100)/10;
	hund_num = (num%1000)/100;
	thou_num = (num%10000)/1000;
	
	P2 = 0xFE;
	P0 = DIS_CODE[thou_num];
	delay_ms(1);
	
	P2 = 0xFD;
	P0 = DIS_CODE[hund_num];
	delay_ms(1);
	
	P2 = 0xFB;
	P0 = DIS_CODE[ten_num];
	delay_ms(1);
	
	P2 = 0xF7;
	P0 = DIS_CODE[sep_num];
	delay_ms(1);
	
	
}


//定义中断         外部中断 0、 1；分别由引脚/INT0、/INT1的电平信号引起 
/*
外部中断0            0
定时器T0             1
外部中断1            2
定时器T1             3
串口中断             4   
*/

void int0_inter()interrupt 0           //0是Int0的中断号
{
	g_unDisNum++;
	
}

void int1_inter()interrupt 2           //2是Int1的中断号
{
	g_unDisNum = 0;
}


void main()
{
	
	g_unDisNum = 0;
	
	//端口初始化
	P0 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	
	//中断初始化
	IT0 = 1;                   //设定中断触发方式
	IT1 = 1;      
	EX0 = 1;                   //打开Int0中断
	EX1 = 1;                   //打开Int1中断
	EA = 1;                    //打开全局中断
	
	while(1)
	{
		disp_num(g_unDisNum);
		
		
	}
	
	

}







