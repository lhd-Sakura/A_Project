#include<reg51.h>
#include"main.h"
#include"delay.h"



void main()
{
     uchar i=0;
	while(1)
	{
	   for(i=0;i<8;i++)
		{
		   P1=(1<<i);
			delay_ms(200);
		
		
		}
	
	
	}

}