//****************************************************************//
//	   DHT21使用范例 
//单片机 AT89S52 或 STC89C52RC 
//功能   串口发送温湿度数据 晶振 11.0592M 波特率 9600 
//硬件   P2.0口为通讯口连接DHT11,DHT11的电源和地连接单片机的电源和地，单片机串口加MAX232连接电脑 
//公司  雁凌电子    
//****************************************************************//
#include"bsp_user_system.h"



//

#define uchar unsigned char
#define uint unsigned int
#define   Data_0_time    4

//----------------------------------------------//
//----------------IO口定义区--------------------//
//----------------------------------------------//

//----------------------------------------------//
//----------------定义区--------------------//
//----------------------------------------------//
U8  U8FLAG,k;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;
U8  outdata[5];  //定义发送的字节数	   
U8  indata[5];
U8  count, count_r=0;
U8  str[6]={"RS232\n"};
U16 U16temp1,U16temp2;

void SendData(U8 *a)
{
	outdata[0] = a[0]; 
	outdata[1] = a[1];
	outdata[2] = a[2];
	outdata[3] = a[3];
	outdata[4] = a[4];
	count = 1;
  HAL_UART_Transmit( &huart1, outdata , 5, 100);
}


void Delay(U16 j)
{      U8 i;
	    for(;j>0;j--)
	  { 	
		for(i=0;i<27;i++);

	  }
    }
       void  Delay_10us(void)
      {
        U8 i;
        i--;
        i--;
        i--;
        i--;
        i--;
        i--;
       }
	
        void  COM(void)
      {
     
	        U8 i;
          
       for(i=0;i<8;i++)	   
	    {
		
	   	    U8FLAG=2;	
	   	while((!P2_0)&&U8FLAG++);
			Delay_10us();
		    Delay_10us();
			Delay_10us();
	  		U8temp=0;
	     if(P2_0)U8temp=1;
		    U8FLAG=2;
		 while((P2_0)&&U8FLAG++);
	   	//超时则跳出for循环		  
	   	 if(U8FLAG==1)break;
	   	//判断数据位是0还是1	 
	   	   
		// 如果高电平高过预定0高电平值则数据位为 1 
	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;        //0
	     }//rof
	   
	}

	//--------------------------------
	//-----湿度读取子程序 ------------
	//--------------------------------
	//----以下变量均为全局变量--------
	//----温度高8位== U8T_data_H------
	//----温度低8位== U8T_data_L------
	//----湿度高8位== U8RH_data_H-----
	//----湿度低8位== U8RH_data_L-----
	//----校验 8位 == U8checkdata-----
	//----调用相关子程序如下----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------

	void RH(void)
	{
	  //主机拉低18ms 
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	   Delay(180);
	  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	 //总线由上拉电阻拉高 主机延时20us
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	 //主机设为输入 判断从机响应信号 
	  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	   if(!P2_0)		 //T !	  
	   {
	   U8FLAG=2;
	 //判断从机是否发出 80us 的低电平响应信号是否结束	 
	   while((!P2_0)&&U8FLAG++);
	   U8FLAG=2;
	 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
	   while((P2_0)&&U8FLAG++);
	 //数据接收状态		 
	   COM();
	   U8RH_data_H_temp=U8comdata;
	   COM();
	   U8RH_data_L_temp=U8comdata;
	   COM();
	   U8T_data_H_temp=U8comdata;
	   COM();
	   U8T_data_L_temp=U8comdata;
	   COM();
	   U8checkdata_temp=U8comdata;
	   HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	 //数据校验 
	 
	   U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	   if(U8temp==U8checkdata_temp)
	   {
	   	  U8RH_data_H=U8RH_data_H_temp;
	   	  U8RH_data_L=U8RH_data_L_temp;
		  U8T_data_H=U8T_data_H_temp;
	   	  U8T_data_L=U8T_data_L_temp;
	   	  U8checkdata=U8checkdata_temp;
	   }//fi
	   }//fi

	}
	
//----------------------------------------------
//main()功能描述:  AT89C51  11.0592MHz 	串口发 
//送温湿度数据,波特率 9600 
//----------------------------------------------
void USER_INIT()
{
	U8  i,j;
	
	//uchar str[6]={"RS232"};
	/* 系统初始化 */
  HAL_UART_Transmit( &huart1, str , 5, 100);
	HAL_Delay(1000);
	
/*
	SendData(str) ;   //发送到串口 
	Delay(1);         //延时100US（12M晶振)
	while(1)
	{  

	   //------------------------
	   //调用温湿度读取子程序 
	   RH();
	   //串口显示程序 
	   //--------------------------

	   str[0]=U8RH_data_H;
	   str[1]=U8RH_data_L;
	   str[2]=U8T_data_H;
	   str[3]=U8T_data_L;
	   str[4]=U8checkdata;
	   SendData(str) ;  //发送到串口  
	   //读取模块数据周期不易小于 2S 
	   Delay(200000);
	}//elihw
	
	
	*/
	
}// main







/*
void RSINTR() interrupt 4 using 2
{
	U8 InPut3;
	if(TI==1) //发送中断	  
	{
		TI=0;
		if(count!=5) //发送完5位数据	 
		{
			SBUF= outdata[count];
			count++;
		}
	}

	if(RI==1)	 //接收中断		  
	{	
		InPut3=SBUF;
		indata[count_r]=InPut3;
		count_r++;
		RI=0;								 
		if (count_r==5)//接收完4位数据 
		{
		//数据接收完毕处理。
			count_r=0;
		str[0]=indata[0];
		 str[1]=indata[1];
		   str[2]=indata[2];
			 str[3]=indata[3];
				 str[4]=indata[4];
				 P0=0;
		}
	}
}

*/