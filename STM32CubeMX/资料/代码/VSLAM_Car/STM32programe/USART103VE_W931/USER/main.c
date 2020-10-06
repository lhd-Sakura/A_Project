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
//CopeSerialData为串口2中断调用函数，串口每收到一个数据，调用一次这个函数。
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	//LED_REVERSE();					//接收到数据，LED灯闪烁一下
	//USB_TxWrite(&ucData,1);			//向USB-HID端口转发收到的串口数据，可直接用接上位机看到模块输出的数据。
	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
		{
			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
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
		ucRxCnt=0;//清空缓存区
	}
}

void CopeSerial1Data(unsigned char ucData)
{	
	UART2_Put_Char(ucData);//转发串口1收到的数据给串口2（JY模块）
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
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//	uart_init(115200);	 //串口初始化为115200
// 	LED_Init();			     //LED端口初始化
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	delay_init();
	Initial_UART2(921600);//接JY-901模块的串口	

	delay_ms(1000);//等等JY-91初始化完成
	
	while(1)
	{			
			delay_ms(500);
		//输出时间
//		sprintf((char*)str,"Time:20%d-%d-%d %d:%d:%.3f\r\n",stcTime.ucYear,stcTime.ucMonth,stcTime.ucDay,stcTime.ucHour,stcTime.ucMinute,(float)stcTime.ucSecond+(float)stcTime.usMiliSecond/1000);
//			UART1_Put_String(str);		
			delay_ms(10);
//		//输出加速度
		printf("Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
//		sprintf((char*)str,"Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
//			UART1_Put_String(str);
//			delay_ms(10);
//		//输出角速度
//		sprintf((char*)str,"Gyro:%.3f %.3f %.3f\r\n",(float)stcGyro.w[0]/32768*2000,(float)stcGyro.w[1]/32768*2000,(float)stcGyro.w[2]/32768*2000);
//			UART1_Put_String(str);
			delay_ms(10);
//		//输出角度
//		sprintf((char*)str,"Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
		printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
//	
//		UART1_Put_String(str);
//			delay_ms(10);
//		//输出磁场

//		sprintf((char*)str,"Mag:%d %d %d\r\n",stcMag.h[0],stcMag.h[1],stcMag.h[2]);
		printf("Mag:%d %d %d\r\n",stcMag.h[0],stcMag.h[1],stcMag.h[2]);
//			UART1_Put_String(str);		
//			delay_ms(10);
//		//输出气压、高度
//		sprintf((char*)str,"Pressure:%ld Height%.2f\r\n",stcPress.lPressure,(float)stcPress.lAltitude/100);
//			UART1_Put_String(str); 
//			delay_ms(10);
//		//输出端口状态
//		sprintf((char*)str,"DStatus:%d %d %d %d\r\n",stcDStatus.sDStatus[0],stcDStatus.sDStatus[1],stcDStatus.sDStatus[2],stcDStatus.sDStatus[3]);
//			UART1_Put_String(str);
//			delay_ms(10);
//		//输出经纬度
//		sprintf((char*)str,"Longitude:%ldDeg%.5fm Lattitude:%ldDeg%.5fm\r\n",stcLonLat.lLon/10000000,(double)(stcLonLat.lLon % 10000000)/1e5,stcLonLat.lLat/10000000,(double)(stcLonLat.lLat % 10000000)/1e5);
//			UART1_Put_String(str);
//			delay_ms(10);
//		//输出地速
//		sprintf((char*)str,"GPSHeight:%.1fm GPSYaw:%.1fDeg GPSV:%.3fkm/h\r\n",(float)stcGPSV.sGPSHeight/10,(float)stcGPSV.sGPSYaw/10,(float)stcGPSV.lGPSVelocity/1000);
//			UART1_Put_String(str);
//			delay_ms(10);
//		//输出四元素
//		sprintf((char*)str,"Four elements:%.5f %.5f %.5f %.5f\r\n\r\n",(float)stcQ.q[0]/32768,(float)stcQ.q[1]/32768,(float)stcQ.q[2]/32768,(float)stcQ.q[3]/32768);
//			UART1_Put_String(str);
//		    delay_ms(10);//等待传输完成
	}//主循环
}


