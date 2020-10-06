#include<reg51.h>
#include"main.h"

sbit OUT_PIN = P2^0;



void timer0_inter() interrupt 1
{
	OUT_PIN = ~OUT_PIN;
	TL0 = 0x78;
	TH0 = 0xEC;

}


void main()
{
	P0 = 0xFF;
	
	TL0 = 0x78;
	TH0 = 0xEC;
	TMOD = 1;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
	
	while(1);
	


}