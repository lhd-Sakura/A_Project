#include<reg51.h>
#include"main.h"
#include"delay.h"
/*#define uint unsigned int
#define uchar unsigned char
*/

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








/*
sbit one=P1^0;


void main()
{
   while(1)
	 {
		 one = 0;
	 
	 
	 
	 }


}

*/