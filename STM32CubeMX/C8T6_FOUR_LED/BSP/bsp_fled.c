#include"bsp_user_system.h"
#include"bsp_fled.h"

//HAL_Delay ����������λΪ1ms   1ms = 1000us

///====================================== 
void I2CStart(void)             //1637 ��ʼ 
	{       
	  CLK_1  
		DIO_1  
		HAL_Delay(2);    
		DIO_0  
		
	} 
 
///============================================= 
void I2Cask(void)                 //1637Ӧ�� 
{ 
		CLK_0
		HAL_Delay(5);             //�ڵڰ˸�ʱ���½���֮����ʱ5us����ʼ�ж�ACK�ź�
  	while(DIO);  
			CLK_1
	  HAL_Delay(2);     
		CLK_0
}  ///======================================== 


void I2CStop(void)               // 1637 ֹͣ 
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
void I2CWrByte(unsigned char oneByte)  //дһ���ֽ� 
{  unsigned char i;      
	 for(i=0;i<8;i++)    
		{ 
			CLK_0      
			if(oneByte&0x01)   //��λ��ǰ       
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
		//������������
		I2CStart();
		I2CWrByte(0x40);
		I2Cask();
		I2CStop();
		
		
		//��ַ����
		I2CStart();
		I2CWrByte(0xC0);
		I2Cask();
		
		
		//������ʾ
		I2CWrByte( a );
		I2Cask();
		I2CWrByte( b );
		I2Cask();
		I2CWrByte( c );
		I2Cask();
		I2CWrByte( d );
		I2Cask();
		I2CStop();
		
		//��ʾ����
		I2CStart();
		I2CWrByte(0x8f);   //������ʾ
		I2Cask();
		I2CStop();
		

	} 
	
			
	
	
	
	
	
	
	
	
 
 










