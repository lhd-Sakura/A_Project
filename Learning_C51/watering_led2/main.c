#include <reg51.h>
#include "main.h"
#include "delay.h"

void main()
{
	while (1)
	{
		uchar i;
		P1 = 0x00;
		for (i = 0; i < 8; i++)
		{
			P1 = ~(P1 + (1 << i));
			delay_ms(200);
			P1 = ~P1;
		}

		//unsignedû�з���λ���޷��ж�iС��0ʱ��ֵ���������
		P1 = 0xff;
		for (i = 8; i > 0; i--)
		{
			P1 = ~(P1 - (1 << i - 1));
			delay_ms(200);
			P1 = ~P1;
		}
	}
}
