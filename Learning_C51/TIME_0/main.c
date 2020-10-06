#include<reg51.h>
#include"main.h"

sbit LED = P2^0;
uchar g_ucNum;

void int0_inter() interrupt 0 
{
	g_ucNum = 0;
	TL0 = 0x18;             //��ʱ������ֵTL0=��8192-5000��%32
	TH0 = 0x63;             //TH0=��8192-5000��/32  
	TR0 = 1;                //�򿪶�ʱ��T0
	
	
}




void int1_inter() interrupt 2
{
	TR0 = 0;                 //�رն�ʱ��T0

}



void timer0_inter() interrupt 1
{
	g_ucNum++;
	
	TL0 = 0x18;              //��ʱ�����¸�ֵ
	TH0 = 0x63;
	
}


void main()
{
	g_ucNum = 0;
	P2 = 0xFF;
	
	//�ⲿ�жϳ�ʼ��
	IT0 = 1;                   //�½��ش����ж�
	IT1 = 1;
	EX0 = 1;                    //���ⲿ�ж�
	EX1 = 1;
	
	//��ʱ��T0��ʼ��
	TMOD = 0;                   //��ʱ��ģʽ��������ʽ0
	TL0 = 0x18;                 //��ʱ������ֵ
	TH0 = 0x63;                 //TH0=��8192-5000��/32
	ET0 = 1;                    //ʹ��T0�ж�
	
	EA = 1;
	
	while(1)
	{
		if(g_ucNum>=200)
		{
			g_ucNum = 0;
			LED = ~LED; 
		
		
		}
		
		
	
	}
	
	
	

}







