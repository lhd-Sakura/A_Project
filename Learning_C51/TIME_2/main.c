//��ʵ��proteus����ʹ��TIME_1�ķ���ʵ��

#include<reg51.h>
#include"main.h"

sbit OUT_PIN = P2^0;

void timer0_inter() interrupt 1
{
	OUT_PIN = ~OUT_PIN;
	
}

void main()
{
	P2 = 0xFF;
	
	TL0 = 0x06;                 //��ʱ����ʼֵ 
	TH0 = 0x06;                 //TH0=256-250
	TMOD = 2;
	ET0 = 1;                    //��T0�ж�
	EA = 1;
	
	TR0 = 1;                    //����T0��ʱ��
	
	while(1);
	

}





