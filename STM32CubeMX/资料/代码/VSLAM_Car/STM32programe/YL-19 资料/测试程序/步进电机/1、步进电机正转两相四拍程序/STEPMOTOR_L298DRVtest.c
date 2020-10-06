/*************************************************************************************************************
*												测试说明
*1、MCU:STC89C52RC
*2、测试频率:11.0592Mhz
*2、编程语言:C51
*2、编译环境:Keil C
*2、功能:步进电机正转两相四拍程序
*************************************************************************************************************/

#include <reg52.h>

//L298输入控制端定义
sbit IN1 = P1^0;
sbit IN2 = P1^1;	
sbit IN3 = P1^2;	
sbit IN4 = P1^3;
sbit ENA = P1^4;	
sbit ENB = P1^5;

unsigned int CYCLE; //周期变量

unsigned char code F_Rotation[4]={0x3a,0x39,0x35,0x36};	//正转表格 全步方式

//如果步进电机是1.8度的 那么走一圈360度，全步方式需要200步 半步方式需要400步 自己可根据步进电机参数来设计


/********************************/
/*      主函数		             */
/********************************/
main()
{ 
	CYCLE=1000; 	//脉冲频率
	
	TMOD |=0x01;	//定时器设置 1ms in 12M crystal
	TH0=(65536-CYCLE)/256; 
	TL0=(65536-CYCLE)%256;
	IE= 0x82;  		//打开中断		
	TR0=1;
	while(1);  
}
/********************************/
/*      定时器0中断服务函数     */
/********************************/
void Timer0(void) interrupt 1 using 1
{
	static unsigned char Cnt;

	TH0=(65536-CYCLE)/256; 
	TL0=(65536-CYCLE)%256;
	
	if(Cnt<4)	Cnt++;
	else		Cnt=0;
	P1=F_Rotation[Cnt];  //输出对应的相 
	
}
