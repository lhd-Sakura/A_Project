#include<reg51.h>
#include"main.h"
#include"delay.h"

void timer1_init()
{
	TMOD = 0x20;                //定时器T1，工作方式2
	TL1 = 0xFD;                 //T1初始值253
	TH1 = 0xFD;                 
	TR1 = 1;                    //定时器T1启动工作（TCON|0x40）

}



void serial_init()
{
	PCON = 0;                  //设定SMOD位为0
	SCON = 0x40;               //设定串口工作方式1，REN=0不接收数据

}


void main()
{
	uchar send_data = 0;                //发送数据
	uchar i = 0;
	
	timer1_init();                       //初始化定时器T1
	serial_init();                       //初始化串口
	IE = 0x00;                           //关闭所有中断
	

	while(1)
	{
		send_data = 'A';
		for(i=0;i<26;i++)
		{
			SBUF = send_data;                //发送缓冲赋值
			while(TI == 0);                  //等待发送标志TI置位为1
			TI = 0;                          //清空发送标志位TI
			send_data++;
			delay_ms(100);
		
		}
		
		delay_ms(3000);
			
	
	}
		

}





d