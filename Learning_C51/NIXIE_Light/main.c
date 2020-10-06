#include<reg51.h>
#include"main.h"
#include"delay.h"

//7段共阳数码管显示码
uchar code DIS_CODE[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};

void main()
{
	uchar i=0;
	while(1)
	{
		P2 = DIS_CODE[i];
		delay_ms(800);
		i = (i+1)%10;
		
	
	
	}



}

