#include "user_system.h"

 
u16 fseg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
u16 segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
u16 disbuf[4]={0,0,0,0};
u16 LED_0F[] = 
{
// 	0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};
u16 LED_DOT[] = 
{	//带小数点的数字
// 	0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};
 
// 全局变量
u16 LED[8];	//用于LED的8位显示缓存
 
void TM1637_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
 
	GPIO_InitStructure.GPIO_PIN = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_0;				  
	GPIO_InitStructure.GPIO_MODE = GPIO_MODE_Out_PP; 		  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
	GPIO_Init(GPIOC, &GPIO_InitStructure);					  
 
}
void LED4_Display(void)
{
	u16 *led_table;          // 查表指针
	u16 i;
	//显示第1位
	led_table = LED_0F + LED[0];
	i = *led_table;
 
	LED_OUT(i);			
	LED_OUT(0x01);		
 
	RCLK = 0;
	RCLK = 1;
	//显示第2位
	led_table = LED_0F + LED[1];
	i = *led_table;
 
	LED_OUT(i);		
	LED_OUT(0x02);		
 
	RCLK = 0;
	RCLK = 1;
	//显示第3位
	led_table = LED_0F + LED[2];
	i = *led_table;
 
	LED_OUT(i);			
	LED_OUT(0x04);	
 
	RCLK = 0;
	RCLK = 1;
	//显示第4位
	led_table = LED_0F + LED[3];
	i = *led_table;
 
	LED_OUT(i);			
	LED_OUT(0x08);		
 
	RCLK = 0;
	RCLK = 1;
}
 
void LED_OUT(u16 X)
{
	u16 i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) 
			DIO=1; 
		else 
			DIO=0;
		X<<=1;
		SCLK = 0;
		SCLK = 1;
	}
}
 
void Seconds(u32 *count)	//数秒   向上计数
{
	if(++(*count)%5000==0 && (*count)!=0)	//count每增加5000   LED[0]增加1
		LED[0]++;
	if(LED[0]%10 == 0 && LED[0] != 0)		//LED[0]每增加10 LED[1]增加1 同时LED[0]清零   
	{
		LED[0] = 0;
		LED[1]++;	
	}	
	if(LED[1]%10 == 0 && LED[1] != 0)
	{
		LED[1] = 0;
		LED[2]++;	
	}	
	if(LED[2]%10 == 0 && LED[2] != 0)
	{
		LED[2] = 0;
		LED[3]++;	
	}
	if(LED[3]%10 == 0 && LED[3] != 0)	
	{
		LED[0]=0;
		LED[1]=0;
		LED[2]=0;
		LED[3]=0;	
	}			
	LED4_Display();
	delay_us(50);
}
void SetNum(u16 x)			//设置四位初始数字
{
	LED[0]=x%10;	//低位，最右边的位
	LED[1]=x/10%10;
	LED[2]=x/100%10;
	LED[3]=x/1000%10;
}
void PlayVoltage(float v)
{
	LED[0]=16;
	LED4_Display();
}
