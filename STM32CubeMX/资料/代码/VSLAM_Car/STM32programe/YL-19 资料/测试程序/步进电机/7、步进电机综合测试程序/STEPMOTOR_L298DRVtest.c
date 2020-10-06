/*************************************************************************************************************
*												测试说明
*1、MCU:STC89C52RC
*2、测试频率:11.0592Mhz
*2、编程语言:C51
*2、编译环境:Keil C
*2、功能:全速正转、全速反转、停止、调速运行
*************************************************************************************************************/

#include <reg52.h>

//L298输入控制端定义
sbit IN1 = P1^0;
sbit IN2 = P1^1;	
sbit IN3 = P1^2;	
sbit IN4 = P1^3;
sbit ENA = P1^4;	
sbit ENB = P1^5;

sbit CW = P3^0;		//正转运行按键
sbit STOP = P3^1;	//停止运行按键
sbit CCW = P3^2;	//反转运行按键
sbit ADJ = P3^3;	//调速运行按键

bit Run_Status;		//运行状态位标志，
					//=0表示电机在停止状态，可以按键正转、反转均可
					//=1表示电机在运行状态，不支持正反转按键，只有先停止。防止强行换向带来的电流过大。

unsigned char Run_Dir;	//电机运行方向

#define	F_DIR	0		//正转
#define	B_DIR	1		//反转

unsigned int CYCLE; //周期变量

unsigned char code F_Rotation[8]={0x3a,0x28,0x39,0x11,0x35,0x24,0x36,0x12};	//正转表格 半步方式
unsigned char code B_Rotation[8]={0x12,0x36,0x24,0x35,0x11,0x39,0x28,0x3a};	//反转表格 半步方式


/********************************/
/*      延时函数               */
/********************************/
void Delay(unsigned int cnt)
{
 	while(--cnt);
}
/********************************/
/*      主函数		             */
/********************************/
main()
{ 
	Run_Status=0;
	CYCLE=1000; 	//脉冲频率
	
	TMOD |=0x01;	//定时器设置 1ms in 12M crystal
	TH0=(65536-CYCLE)/256; 
	TL0=(65536-CYCLE)%256;
	IE= 0x82;  		//打开中断		

	while(1)
  	{
		if(!STOP)			//任何时候按停止键，电机停止运行
		{	
			Delay(1000);	//延时去抖动
			if(!STOP)			
			{		
				Run_Status=0;	//电机正在停止的状态标志
				P1=F_Rotation[0]; 
				TR0=0;
			}
		}
		if(!CW&&!Run_Status)//按正转键同时电机不是正在运行时，电机正转运行
		{
			Delay(1000);	//延时去抖动
			if(!CW&&!Run_Status)			
			{	
				Run_Status=1;//电机正在运行的状态标志
				TR0=1;
				CYCLE=1000;
				Run_Dir=F_DIR;//电机运行方向正转				
			}
		}
  		if(!CCW&&!Run_Status)//按反转键同时电机不是正在运行时，电机反转运行
		{
			Delay(1000);	//延时去抖动
			if(!CCW&&!Run_Status)			
			{	
				Run_Status=1;//电机正在运行的状态标志
				TR0=1;
				CYCLE=1000;
				Run_Dir=B_DIR;//电机运行方向反转
			}
		}
	   	if(!ADJ)
		{
			Delay(10000);	//延时去抖动
			if(!ADJ)
			{	
				if(CYCLE<5000)	CYCLE+=500;	
				else			CYCLE=1000;
				Run_Status=1;
				TR0=1;
		 	}
		}
   }
}/********************************/
/*      定时器0中断服务函数     */
/********************************/
void Timer0(void) interrupt 1 using 1
{
	static unsigned char Cnt;

	TH0=(65536-CYCLE)/256; 
	TL0=(65536-CYCLE)%256;
	
	if(Run_Dir==F_DIR)//电机运行方向正转    	
	{
		if(Cnt<8)	Cnt++;
		else		Cnt=0;
		P1=F_Rotation[Cnt];  //输出对应的相 
	}
	if(Run_Dir==B_DIR)//电机运行方向反转    	
	{
		if(Cnt<8)	Cnt++;
		else		Cnt=0;
		P1=B_Rotation[Cnt];  //输出对应的相 
	}
}
