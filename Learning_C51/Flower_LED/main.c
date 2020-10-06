#include<reg51.h>
#include"main.h"
#include"delay.h"
#include"delay.c"
#define uint unsigned int
#define uchar unsigned char


void main(void)
{
	while(1)
	{
		P1 = 0x04;
		delay_ms(800);
		P1 = 0x6D;
		delay_ms(800);
		P1=0x18;
		delay_ms(800);
		P1=0x48;
		delay_ms(800);
		
	}


}

