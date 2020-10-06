#include"bsp_user_system.h"
#include"bsp_fled.h"

//HAL_Delay 函数参数单位为1ms   1ms = 1000us

///====================================== 
void I2CStart(void)             //1637 开始 
	{       
	  CLK_1  
		DIO_1  
		HAL_Delay(2);    
		DIO_0  
		
	} 
 
///============================================= 
void I2Cask(void)                 //1637应答 
{ 
		CLK_0
		HAL_Delay(5);             //在第八个时钟下降沿之后延时5us，开始判断ACK信号
  	while(DIO);  
			CLK_1
	  HAL_Delay(2);     
		CLK_0
}  ///======================================== 


void I2CStop(void)               // 1637 停止 
{       
	CLK_0 
	HAL_Delay(2);
  DIO_0   
	HAL_Delay(2);  
  CLK_1 
	HAL_Delay(2);    
	DIO_1
} 
 
///=========================================
void I2CWrByte(unsigned char oneByte)  //写一个字节 
{  unsigned char i;      
	 for(i=0;i<8;i++)    
		{ 
			CLK_0      
			if(oneByte&0x01)   //低位在前       
			{              
				DIO_1    
			}           
			else   
			{              
				DIO_0   
			}        
			HAL_Delay(3);  
			oneByte=oneByte>>1;    
			CLK_1    
			HAL_Delay(3); 
			}  
		} 
 
///============================================== 
void FLED_ON(int8_t a,int8_t b,int8_t c,int8_t d)
	{  
		//数据命令设置
		I2CStart();
		I2CWrByte(0x40);
		I2Cask();
		I2CStop();
		
		
		//地址设置
		I2CStart();
		I2CWrByte(0xC0);
		I2Cask();
		
		
		//数据显示
		I2CWrByte( a );
		I2Cask();
		I2CWrByte( b );
		I2Cask();
		I2CWrByte( c );
		I2Cask();
		I2CWrByte( d );
		I2Cask();
		I2CStop();
		
		//显示控制
		I2CStart();
		I2CWrByte(0x8f);   //开启显示
		I2Cask();
		I2CStop();
		

	} 
	
			
	
	
	
	
	
	
	
	
 
 










