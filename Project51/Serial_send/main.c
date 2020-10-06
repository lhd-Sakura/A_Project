#include <reg51.h>

void InitUART(void)
{
    TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xF3;
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;
}

void SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

void main(void)
{
    InitUART();
	while(1);
}

void UARTInterrupt(void) interrupt 4
{
	P1 = 0x0f;
    if(P1 != 0x0f)
    {
      
			SendOneByte('Y');
			
			P1 = 0x0f;
			
        //add your code here!
    }
    else
        TI = 0;
}










