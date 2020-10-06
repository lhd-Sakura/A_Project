#include<reg51.h>
#include"main.h"
#include"delay.h"

void main()
{
	uchar i=0;
	uchar key_val = 0;
	bit bFlash = 1;
	uchar i_val=0; 
	
	
	P3 = 0xFF;
	key_val = 0xFF;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			if(key_val != P3)
			{
				key_val = P3;
				
				if(0== (P3&0x04))      //只有当按键按下时才改变闪烁状态，抬起时不改变
				{
					if(bFlash)
					{
						i_val = i;
					
					}
					else
					{
						i= i_val;
					}
					
					
					bFlash = ~bFlash;
				
				}
				
				
			}
			if(bFlash)
			{
				P0 = ~(1<<i);
			
			}
			
/*
			if(bFlash == 0)
			{
				i--;
			
			}
			
			*/
			
			
			
			
			delay_ms(200);
				
		
		}
	
	}

}


