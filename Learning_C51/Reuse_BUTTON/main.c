#include<reg51.h>
#include"main.h"
#include"delay.h"

sbit K1 = P3^2;

uchar code DIS_CODE[12]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0x0C};


//��ʾ����
void disp_num(uchar num)
{
	uchar sep_num;           //��λ
	uchar ten_num;           //ʮλ
	
	sep_num = num%10;
	ten_num = num/10;
	P2 = 0x02;
	P0 = DIS_CODE[sep_num];
	delay_ms(5);
	P2 = 0x01;
	P0 = DIS_CODE[ten_num];
	delay_ms(5);
	
}



void main()
{
	uchar key_val = 0;
	uchar num = 0;
	uchar dis_num = 0;
	
	P0 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	key_val = 0xFF;
	
	while(1)
	{
		if(key_val != P3)                 //�жϰ���״̬�ĸı䣬���º�̧��
		{
			key_val = P3;                 
			disp_num(dis_num);
			while(K1 == 0)                  //�������£�һֱ��ʱ��̧�𰴼���ʱ����
			{
				disp_num(dis_num);
				if(++num>100)                 //��ʱ�䵱��ʱ��
				{
					num = 101;
				}
				
			}
			
			
			//����num������ʾ����
			if(num>0 && num<=100)
			{
				dis_num++;
				
			}	
			else if(num>100)
			{
				dis_num +=10;
				
			}
			num = 0;
				
		}
		
		disp_num(dis_num);
		
		
	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

