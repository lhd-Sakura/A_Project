
#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8; 		// ����������u8�򻯴����д
typedef unsigned int u16;

sbit gA = P2^2;					// 38�����������A
sbit gB = P2^3;					// 38�����������B
sbit gC = P2^4;					// 38�����������C





unsigned char code gDuanMa[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};



void UartInit(void);
void UartSendByte(u8 c);


void delay10ms(void)   //��� 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}


void main(void)
{
	UartInit();
	while (1);
}

void UartInit(void)
{
    TMOD = 0x20;		// T1����Ϊ8λ�Զ���װ�ض�ʱ��			
    SCON = 0x50;		// ���ڹ�����ģʽ1��8λUART�����ʿɱ䣬���������
    TH1 = 0xE6;			// ��Ƭ��С����V1.3�����2400�������Ҳ�����
    TL1 = TH1;			// �ӱ�ʱ�Ķ�ʱ������ֵ��
    PCON = 0x80;		// ����Ϊ�����ʼӱ�
	EA = 1;				// �����ж�
	ES = 1;			    // �������ж�
	TR1 = 1;		    // ��ʱ��1��������
}


/*
void UartSendByte(u8 c)
{
    SBUF = c;
    while (!TI);
    TI = 0;
}
*/



void UartIsr(void) interrupt 4	// ע�⴮���жϵı����4
{
	u8 c = 0;				    // ��ʱ�������ڴ洢�����жϽ��յ��ַ�

    if (RI)						// ���ڽ����ж�
    {
        RI = 0;
        //add your code here!
		c = SBUF;				// ͨ�����ڽ����ⲿ���͵��ַ�
			
	gA = 1; gB = 1; gC = 1;		  		// λѡ�����0
	P0 = gDuanMa[c];
	delay10ms(); 						// ���һ����ʾʱ��	

			
			
			
			
//		UartSendByte(c + 1);	// ��1��ط���ȥ
			
			
			
    }
    else 						// ���ڷ����ж�
        TI = 0;					// if else�����ֻ��1�������ɲ��Ӵ�����
}








