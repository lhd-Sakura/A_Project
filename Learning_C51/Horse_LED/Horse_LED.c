#include<reg51.h>
#include<main.h>
#define uint unsigned int
#define uchar unsigned char
	

void delay_ms(uint timer)
{
     uchar j = 124;
	 while(timer--)
	 {
	    for(j=124;j>0;j--)
		{
		   ;
		}
	 	 
	 }

}


void main()
{
	uchar i=0;
	while(1)
	{
		P1 =1;
/*		for(i=0;i<8;i++)
		{
			delay_ms(200);
			P1<<1;
			
		
		}
*/

		
	}


}



