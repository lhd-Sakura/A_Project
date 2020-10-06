#include<reg51.h>
#include"main.h"
#include"delay.h"

uchar code DIS_CODE[12] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0xF3};

uint g_unDisNum;


//���������ʾ����
void disp_num(uint num)
{
	uchar sep_num = 0;
	uchar ten_num = 0;
	uchar hund_num = 0;
	uchar thou_num = 0;
	
	sep_num = num%10;
	ten_num = (num%100)/10;
	hund_num = (num%1000)/100;
	thou_num = (num%10000)/1000;
	
	P2 = 0xFE;
	P0 = DIS_CODE[thou_num];
	delay_ms(1);
	
	P2 = 0xFD;
	P0 = DIS_CODE[hund_num];
	delay_ms(1);
	
	P2 = 0xFB;
	P0 = DIS_CODE[ten_num];
	delay_ms(1);
	
	P2 = 0xF7;
	P0 = DIS_CODE[sep_num];
	delay_ms(1);
	
	
}


//�����ж�         �ⲿ�ж� 0�� 1���ֱ�������/INT0��/INT1�ĵ�ƽ�ź����� 
/*
�ⲿ�ж�0            0
��ʱ��T0             1
�ⲿ�ж�1            2
��ʱ��T1             3
�����ж�             4   
*/

void int0_inter()interrupt 0           //0��Int0���жϺ�
{
	g_unDisNum++;
	
}

void int1_inter()interrupt 2           //2��Int1���жϺ�
{
	g_unDisNum = 0;
}


void main()
{
	
	g_unDisNum = 0;
	
	//�˿ڳ�ʼ��
	P0 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	
	//�жϳ�ʼ��
	IT0 = 1;                   //�趨�жϴ�����ʽ
	IT1 = 1;      
	EX0 = 1;                   //��Int0�ж�
	EX1 = 1;                   //��Int1�ж�
	EA = 1;                    //��ȫ���ж�
	
	while(1)
	{
		disp_num(g_unDisNum);
		
		
	}
	
	

}







