
#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8; 		// 重命名类型u8简化代码编写
typedef unsigned int u16;

sbit gA = P2^2;					// 38译码器输入口A
sbit gB = P2^3;					// 38译码器输入口B
sbit gC = P2^4;					// 38译码器输入口C





unsigned char code gDuanMa[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};



void UartInit(void);
void UartSendByte(u8 c);


void delay10ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}


void main(void)
{
	UartInit();
	while (1);
}

void UartInit(void)
{
    TMOD = 0x20;		// T1设置为8位自动重装载定时器			
    SCON = 0x50;		// 串口工作在模式1：8位UART波特率可变，且允许接收
    TH1 = 0xE6;			// 单片机小精灵V1.3算出的2400波特率且波特率
    TL1 = TH1;			// 加倍时的定时器设置值。
    PCON = 0x80;		// 设置为波特率加倍
	EA = 1;				// 开总中断
	ES = 1;			    // 开串口中断
	TR1 = 1;		    // 定时器1开启计数
}


/*
void UartSendByte(u8 c)
{
    SBUF = c;
    while (!TI);
    TI = 0;
}
*/



void UartIsr(void) interrupt 4	// 注意串口中断的编号是4
{
	u8 c = 0;				    // 临时变量用于存储串口中断接收的字符

    if (RI)						// 串口接收中断
    {
        RI = 0;
        //add your code here!
		c = SBUF;				// 通过串口接收外部发送的字符
			
	gA = 1; gB = 1; gC = 1;		  		// 位选数码管0
	P0 = gDuanMa[c];
	delay10ms(); 						// 间隔一段显示时间	

			
			
			
			
//		UartSendByte(c + 1);	// 加1后回发出去
			
			
			
    }
    else 						// 串口发送中断
        TI = 0;					// if else中如果只有1句代码则可不加大括号
}








