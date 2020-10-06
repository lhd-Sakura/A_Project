#include<reg51.h>
#include"main.h"
#include"delay.h"

void timer1_init()
{
	TMOD = 0x20;                //��ʱ��T1��������ʽ2
	TL1 = 0xFD;                 //T1��ʼֵ253
	TH1 = 0xFD;                 
	TR1 = 1;                    //��ʱ��T1����������TCON|0x40��

}



void serial_init()
{
	PCON = 0;                  //�趨SMODλΪ0
	SCON = 0x40;               //�趨���ڹ�����ʽ1��REN=0����������

}


void main()
{
	uchar send_data = 0;                //��������
	uchar i = 0;
	
	timer1_init();                       //��ʼ����ʱ��T1
	serial_init();                       //��ʼ������
	IE = 0x00;                           //�ر������ж�
	

	while(1)
	{
		send_data = 'A';
		for(i=0;i<26;i++)
		{
			SBUF = send_data;                //���ͻ��帳ֵ
			while(TI == 0);                  //�ȴ����ͱ�־TI��λΪ1
			TI = 0;                          //��շ��ͱ�־λTI
			send_data++;
			delay_ms(100);
		
		}
		
		delay_ms(3000);
			
	
	}
		

}





d