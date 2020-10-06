#include"bsp_user_system.h"


/**
  ******************************************************************************
  * @file    bsp_dht11.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   温湿度传感器应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 霸道  开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/*
 * 函数名：MX_GPIO_Init();
 * 描述  ：配置DHT11用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */


static uint8_t                        DHT11_ReadByte                          ( void );




/* 可以在下面的宏定义中把后面的延时函数替换换SysTick的延时函数，就是想用那个就换成那个的 */


 /**
  * @brief  DHT11 初始化函数
  * @param  无
  * @retval 无
  */
void DHT11_Init ( void )
{
	MX_GPIO_Init();
	
	Data_1;               // 拉高GPIOB10
}




void delay_us(u16 t)
{
	u16 i =0;
	for(i=0;i<t;i++);

}



/* 
 * 从DHT11读取一个字节，MSB先行
 */
static uint8_t DHT11_ReadByte ( void )
{
	uint8_t i, temp=0;
	

	for(i=0;i<8;i++)    
	{	 
		/*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/  
		while(Data==0);

		/*DHT11 以26~28us的高电平表示“0”，以70us高电平表示“1”，
		 *通过检测 x us后的电平即可区别这两个状 ，x 即下面的延时 
		 */
		delay_us(40); //延时x us 这个延时需要大于数据0持续的时间即可	   	  

		if(Data==1)/* x us后仍为高电平表示数据“1” */
		{
			/* 等待数据1的高电平结束 */
			while(Data==1);

			temp|=(uint8_t)(0x01<<(7-i));  //把第7-i位置1，MSB先行 
		}
		else	 // x us后为低电平表示数据“0”
		{			   
			temp&=(uint8_t)~(0x01<<(7-i)); //把第7-i位置0，MSB先行
		}
	}
	
	return temp;
	
}


/*
 * 一次完整的数据传输为40bit，高位先出
 * 8bit 湿度整数 + 8bit 湿度小数 + 8bit 温度整数 + 8bit 温度小数 + 8bit 校验和 
 */
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef *DHT11_Data)
{  
	/*输出模式*/
	MX_GPIO_Init();
	/*主机拉低*/
	Data_0;
	/*延时18ms*/
	HAL_Delay(18);

	/*总线拉高 主机延时30us*/
	Data_1;

	delay_us(30);   //延时30us

	/*主机设为输入 判断从机响应信号*/ 
	MX_GPIO_OutInit();

	/*判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行*/   
	if(Data==0)     
	{
		/*轮询直到从机发出 的80us 低电平 响应信号结束*/  
		while(Data==0);

		/*轮询直到从机发出的 80us 高电平 标置信号结束*/
		while(Data==1);

		/*开始接收数据*/   
		DHT11_Data->humi_int= DHT11_ReadByte();

		DHT11_Data->humi_deci= DHT11_ReadByte();

		DHT11_Data->temp_int= DHT11_ReadByte();

		DHT11_Data->temp_deci= DHT11_ReadByte();

		DHT11_Data->check_sum= DHT11_ReadByte();


		/*读取结束，引脚改为输出模式*/
		MX_GPIO_Init();
		/*主机拉高*/
		Data_1;

		/*检查读取的数据是否正确*/
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
		//高位在先 
		value <<= 1; 
		
		//1bit开始50us
    while(Data == 0); 
		
		delay_us(40); 
		if(Data == 1) 
			{ 
				//进入这里表示该位是                 1 
				value++; 
			}
			
			//等待剩余(约 40us)的高电平结束 
			while(Data == 1);
//			delay_us(10);
//			while(Data == 0);

		}  
		
			return (value); 
		
} 


void Data_ReadTemp(void)
{
	//提前拉高延迟1s
	Data_1;
	HAL_Delay(1000);
	
	Data_0;
	HAL_Delay(20);
	Data_1;
	delay_us(30);
	MX_GPIO_OutInit();
	
	
	//DHT响应信号
	delay_us(10);
	while(Data == 0);
	while(Data == 1);
	
	//DHT发送数据
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










