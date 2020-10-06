#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
/*	
//ÑÓ³Ùº¯Êý
void delay_ms(uint timer)
{
    uchar j=124;
	  while(timer--)
		{
		   for(j=124;j>0;j--)
			{
			    ;
			}
			
		}

}




void main(void)
{
    while(1)
		{
		  P1 &=0xFE;
			delay_ms(100);
			P1 |=0x01;
			delay_ms(100);
		
		
		}


}*/


sbit LED = P1^0; 

//ÑÓ³Ùº¯Êý
void delay_ms(uint timer)
{
    uchar j=124;
	  while(timer--)
		{
		   for(j=124;j>0;j--)
			{
			    ;
			}
			
		}

}


void main(void)
{
    while(1)
		{
		     LED = ~LED;
			delay_ms(100);
		
		}




}






