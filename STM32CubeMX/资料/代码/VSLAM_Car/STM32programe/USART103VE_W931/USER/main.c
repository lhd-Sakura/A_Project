#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "UART2.h"
#include "led.h"
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "JY901.h"
#include <string.h>
#include <stdio.h>
#include "IOI2C.h"
#include "REG.h"

struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;
//CopeSerialDataΪ����2�жϵ��ú���������ÿ�յ�һ�����ݣ�����һ�����������
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	//LED_REVERSE();					//���յ����ݣ�LED����˸һ��
	//USB_TxWrite(&ucData,1);			//��USB-HID�˿�ת���յ��Ĵ������ݣ���ֱ���ý���λ������ģ����������ݡ�
	ucRxBuffer[ucRxCnt++]=ucData;	//���յ������ݴ��뻺������
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		switch(ucRxBuffer[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		{
			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
			case 0x55:	memcpy(&stcDStatus,&ucRxBuffer[2],8);break;
			case 0x56:	memcpy(&stcPress,&ucRxBuffer[2],8);break;
			case 0x57:	memcpy(&stcLonLat,&ucRxBuffer[2],8);break;
			case 0x58:	memcpy(&stcGPSV,&ucRxBuffer[2],8);break;
			case 0x59:	memcpy(&stcQ,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;//��ջ�����
	}
}

void CopeSerial1Data(unsigned char ucData)
{	
	UART2_Put_Char(ucData);//ת������1�յ������ݸ�����2��JYģ�飩
}

//void ShortToChar(short sData,unsigned char cData[])
//{
//	cData[0]=sData&0xff;
//	cData[1]=sData>>8;
//}
//short CharToShort(unsigned char cData[])
//{
//	return ((short)cData[1]<<8)|cData[0];
//}

//int main(void)
//{  
//  unsigned char chrTemp[30];
//	unsigned char str[100];
//	float a[3],w[3],h[3],Angle[3];
//		
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
// 	LED_Init();			     //LED�˿ڳ�ʼ��
//	delay_init();
//	IIC_Init();
//	
//	while (1)
//	{
//		delay_ms(100);
//		IICreadBytes(0x50, AX, 24,&chrTemp[0]);
//		a[0] = (float)CharToShort(&chrTemp[0])/32768*16;
//		a[1] = (float)CharToShort(&chrTemp[2])/32768*16;
//		a[2] = (float)CharToShort(&chrTemp[4])/32768*16;
//		w[0] = (float)CharToShort(&chrTemp[6])/32768*2000;
//		w[1] = (float)CharToShort(&chrTemp[8])/32768*2000;
//		w[2] = (float)CharToShort(&chrTemp[10])/32768*2000;
//		h[0] = CharToShort(&chrTemp[12]);
//		h[1] = CharToShort(&chrTemp[14]);
//		h[2] = CharToShort(&chrTemp[16]);
//		Angle[0] = (float)CharToShort(&chrTemp[18])/32768*180;
//		Angle[1] = (float)CharToShort(&chrTemp[20])/32768*180;
//		Angle[2] = (float)CharToShort(&chrTemp[22])/32768*180;
//		
//		sprintf((char*)str,"0x50:  a:%.3f %.3f %.3f w:%.3f %.3f %.3f  h:%.0f %.0f %.0f  Angle:%.3f %.3f %.3f \r\n",a[0],a[1],a[2],w[0],w[1],w[2],h[0],h[1],h[2],Angle[0],Angle[1],Angle[2]);
//		UART1_Put_String(str);		

//	
//	
//    }
//}





int main(void)
{
	unsigned char str[100];
	unsigned char len,i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	delay_init();
	Initial_UART2(921600);//��JY-901ģ��Ĵ���	

	delay_ms(1000);//�ȵ�JY-91��ʼ�����
	
	while(1)
	{			
			delay_ms(500);
		//���ʱ��
//		sprintf((char*)str,"Time:20%d-%d-%d %d:%d:%.3f\r\n",stcTime.ucYear,stcTime.ucMonth,stcTime.ucDay,stcTime.ucHour,stcTime.ucMinute,(float)stcTime.ucSecond+(float)stcTime.usMiliSecond/1000);
//			UART1_Put_String(str);		
			delay_ms(10);
//		//������ٶ�
		printf("Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
//		sprintf((char*)str,"Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
//			UART1_Put_String(str);
//			delay_ms(10);
//		//������ٶ�
//		sprintf((char*)str,"Gyro:%.3f %.3f %.3f\r\n",(float)stcGyro.w[0]/32768*2000,(float)stcGyro.w[1]/32768*2000,(float)stcGyro.w[2]/32768*2000);
//			UART1_Put_String(str);
			delay_ms(10);
//		//����Ƕ�
//		sprintf((char*)str,"Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
		printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
//	
//		UART1_Put_String(str);
//			delay_ms(10);
//		//����ų�

//		sprintf((char*)str,"Mag:%d %d %d\r\n",stcMag.h[0],stcMag.h[1],stcMag.h[2]);
		printf("Mag:%d %d %d\r\n",stcMag.h[0],stcMag.h[1],stcMag.h[2]);
//			UART1_Put_String(str);		
//			delay_ms(10);
//		//�����ѹ���߶�
//		sprintf((char*)str,"Pressure:%ld Height%.2f\r\n",stcPress.lPressure,(float)stcPress.lAltitude/100);
//			UART1_Put_String(str); 
//			delay_ms(10);
//		//����˿�״̬
//		sprintf((char*)str,"DStatus:%d %d %d %d\r\n",stcDStatus.sDStatus[0],stcDStatus.sDStatus[1],stcDStatus.sDStatus[2],stcDStatus.sDStatus[3]);
//			UART1_Put_String(str);
//			delay_ms(10);
//		//�����γ��
//		sprintf((char*)str,"Longitude:%ldDeg%.5fm Lattitude:%ldDeg%.5fm\r\n",stcLonLat.lLon/10000000,(double)(stcLonLat.lLon % 10000000)/1e5,stcLonLat.lLat/10000000,(double)(stcLonLat.lLat % 10000000)/1e5);
//			UART1_Put_String(str);
//			delay_ms(10);
//		//�������
//		sprintf((char*)str,"GPSHeight:%.1fm GPSYaw:%.1fDeg GPSV:%.3fkm/h\r\n",(float)stcGPSV.sGPSHeight/10,(float)stcGPSV.sGPSYaw/10,(float)stcGPSV.lGPSVelocity/1000);
//			UART1_Put_String(str);
//			delay_ms(10);
//		//�����Ԫ��
//		sprintf((char*)str,"Four elements:%.5f %.5f %.5f %.5f\r\n\r\n",(float)stcQ.q[0]/32768,(float)stcQ.q[1]/32768,(float)stcQ.q[2]/32768,(float)stcQ.q[3]/32768);
//			UART1_Put_String(str);
//		    delay_ms(10);//�ȴ��������
	}//��ѭ��
}


