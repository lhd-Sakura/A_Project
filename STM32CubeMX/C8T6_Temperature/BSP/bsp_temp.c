#include"bsp_user_system.h"


/**
  ******************************************************************************
  * @file    bsp_dht11.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��ʪ�ȴ�����Ӧ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 �Ե�  ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/*
 * ��������MX_GPIO_Init();
 * ����  ������DHT11�õ���I/O��
 * ����  ����
 * ���  ����
 */


static uint8_t                        DHT11_ReadByte                          ( void );




/* ����������ĺ궨���аѺ������ʱ�����滻��SysTick����ʱ���������������Ǹ��ͻ����Ǹ��� */


 /**
  * @brief  DHT11 ��ʼ������
  * @param  ��
  * @retval ��
  */
void DHT11_Init ( void )
{
	MX_GPIO_Init();
	
	Data_1;               // ����GPIOB10
}




void delay_us(u16 t)
{
	u16 i =0;
	for(i=0;i<t;i++);

}



/* 
 * ��DHT11��ȡһ���ֽڣ�MSB����
 */
static uint8_t DHT11_ReadByte ( void )
{
	uint8_t i, temp=0;
	

	for(i=0;i<8;i++)    
	{	 
		/*ÿbit��50us�͵�ƽ���ÿ�ʼ����ѯֱ���ӻ����� ��50us �͵�ƽ ����*/  
		while(Data==0);

		/*DHT11 ��26~28us�ĸߵ�ƽ��ʾ��0������70us�ߵ�ƽ��ʾ��1����
		 *ͨ����� x us��ĵ�ƽ��������������״ ��x ���������ʱ 
		 */
		delay_us(40); //��ʱx us �����ʱ��Ҫ��������0������ʱ�伴��	   	  

		if(Data==1)/* x us����Ϊ�ߵ�ƽ��ʾ���ݡ�1�� */
		{
			/* �ȴ�����1�ĸߵ�ƽ���� */
			while(Data==1);

			temp|=(uint8_t)(0x01<<(7-i));  //�ѵ�7-iλ��1��MSB���� 
		}
		else	 // x us��Ϊ�͵�ƽ��ʾ���ݡ�0��
		{			   
			temp&=(uint8_t)~(0x01<<(7-i)); //�ѵ�7-iλ��0��MSB����
		}
	}
	
	return temp;
	
}


/*
 * һ�����������ݴ���Ϊ40bit����λ�ȳ�
 * 8bit ʪ������ + 8bit ʪ��С�� + 8bit �¶����� + 8bit �¶�С�� + 8bit У��� 
 */
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef *DHT11_Data)
{  
	/*���ģʽ*/
	MX_GPIO_Init();
	/*��������*/
	Data_0;
	/*��ʱ18ms*/
	HAL_Delay(18);

	/*�������� ������ʱ30us*/
	Data_1;

	delay_us(30);   //��ʱ30us

	/*������Ϊ���� �жϴӻ���Ӧ�ź�*/ 
	MX_GPIO_OutInit();

	/*�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������*/   
	if(Data==0)     
	{
		/*��ѯֱ���ӻ����� ��80us �͵�ƽ ��Ӧ�źŽ���*/  
		while(Data==0);

		/*��ѯֱ���ӻ������� 80us �ߵ�ƽ �����źŽ���*/
		while(Data==1);

		/*��ʼ��������*/   
		DHT11_Data->humi_int= DHT11_ReadByte();

		DHT11_Data->humi_deci= DHT11_ReadByte();

		DHT11_Data->temp_int= DHT11_ReadByte();

		DHT11_Data->temp_deci= DHT11_ReadByte();

		DHT11_Data->check_sum= DHT11_ReadByte();


		/*��ȡ���������Ÿ�Ϊ���ģʽ*/
		MX_GPIO_Init();
		/*��������*/
		Data_1;

		/*����ȡ�������Ƿ���ȷ*/
		if(DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci)
			return SUCCESS;
		else 
			return ERROR;
	}
	
	else
		return ERROR;
	
}


void TEMP_FLED()
{
	DHT11_Data_TypeDef DHT11_Data;
	int a,b;
	a = DHT11_Data.temp_int/10;
	b = DHT11_Data.temp_int%10;
	
	FLED_ON(Tab[9],Tab[0],Tab[10],Tab[12]);
	

}








/*************************************END OF FILE******************************/
















/***********************************************************************************
unsigned char value_array[5]; 

void delay_us(u16 t)
{
	u16 i =0;
	for(i=0;i<t;i++);

}

unsigned char Data_ReadValue(void) 
{
	unsigned char value = 0, i;
	
	for(i = 8; i > 0; i--)
	{
		//��λ���� 
		value <<= 1; 
		
		//1bit��ʼ50us
    while(Data == 0); 
		
		delay_us(40); 
		if(Data == 1) 
			{ 
				//���������ʾ��λ��                 1 
				value++; 
			}
			
			//�ȴ�ʣ��(Լ 40us)�ĸߵ�ƽ���� 
			while(Data == 1);
//			delay_us(10);
//			while(Data == 0);

		}  
		
			return (value); 
		
} 


void Data_ReadTemp(void)
{
	//��ǰ�����ӳ�1s
	Data_1;
	HAL_Delay(1000);
	
	Data_0;
	HAL_Delay(20);
	Data_1;
	delay_us(30);
	MX_GPIO_OutInit();
	
	
	//DHT��Ӧ�ź�
	delay_us(10);
	while(Data == 0);
	while(Data == 1);
	
	//DHT��������
	for(uchar i=0;i<5;i++)
	{
		value_array[i] = Data_ReadValue();
		
	}
	
	MX_GPIO_Init();
	
}


void TEMP_FLED()
{
	uchar a,b;
	a = value_array[2]/10;
	b = value_array[2]/10;
	
	FLED_ON(Tab[0],Tab[0],Tab[a],Tab[b]);
	

}

*///********************************************************************










