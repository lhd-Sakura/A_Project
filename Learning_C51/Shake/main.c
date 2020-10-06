#include<reg51.h>
#include"main.h"
#include"delay.h"

//���Ŷ���
sbit K1 = P3^2;
sbit K2 = P3^3;
sbit LED1 = P2^5;
sbit LED2 = P2^6;

//�������ʾ��
uchar code DIS_CODE[12]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0x0C};

void main()
{
	uchar key_val = 0;
	
	//�˿ڳ�ʼ��
	P0 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	
	key_val = 0xFF;      //���������������۲찴��ֵ���ޱ䶯
	P0 = DIS_CODE[11];
	while(1)
	{
		if(key_val != P3)
		{
			key_val = P3;
			
			if(K1==0)                   //�ӳ�10ms�����������������ʱ�䣩�ٴ��ж�
			{
				delay_ms(10);
				if(K1 == 0)
				{
					LED1 = 0;
					LED2 = 1;
					P0 = DIS_CODE[1];
				
				}
				
			}
			
			else if(K2==0)
			{
				delay_ms(10);              //
				if(K2==0)
				{
					LED1 = 1;
					LED2 = 0;
					P0 = DIS_CODE[2];
					
				}	
				
				
				
			}
			
		
		}
		
		delay_ms(20);
	}

}



