#include<reg51.h>
#include"main.h"

sbit OUT_A = P2^0;
sbit OUT_B = P2^1;

void timerTL0_inter() interrupt 1
{
	OUT_A = ~OUT_A;
	TL0 = 0;

}



void timerTH0_inter() interrupt 3
{
	OUT_B = ~OUT_B;
	TH0 = 128;
	
}


void main()
{
	P2 = 0xFF;
	
	//��ʱ��T0��ʼ��
	TL0 = 0;                   //TL0��ʼֵ
	TH0 = 128;                 //TH0��ʼֵ
	TMOD = 3;                  //��ʱ��������ʽ3
	ET0 = 1;                   //ʹ��T0�ж�
	ET1 = 1;                   //T1�ж�
	EA = 1;                    //��ȫ���ж�
	
	TR0 = 1;                   //����TL0��ʱ��
	TR1 = 1;                   //����TL1��ʱ��
	
	while(1);
	
}




