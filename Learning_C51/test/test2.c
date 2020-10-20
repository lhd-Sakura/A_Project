#include <reg51.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char 
void delay (uint t)
	{
		uint i,j;
		for(i=0;i<t;i++)
		for(j=0;j<120;j++);
	}
	
	
	
	void main()
	{
		uchar k;
		k=0xfe;
		
		P1=0x00;
			delay(100);
		
		while(1){
			P1=k;
			delay(100);
			k=_crol_(k,1);
		}
	}