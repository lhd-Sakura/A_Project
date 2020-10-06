#include"bsp_system.h"


//请根据自己的     Data 接的  IO 口来改动位定义 
//防止在与硬件通信时发生死循环的计数范围 
#define NUMBER   20 
#define SIZE 5 
static unsigned char status; 
//存放五字节数据的数组 
static unsigned char value_array[SIZE]; 
/*可在其他的文件引用温湿度值,实际是温度的整数的 10 倍 
如  Data 读回的温度是     26,则 temp_value = 260, 湿度同理*/ 
int temp_value, humi_value;   
 
 
static unsigned char ReadValue(void); 
 
extern void Delay_1ms(unsigned int ms) 
{ 
    unsigned int x, y; 
    for(x = ms; x > 0; x--) 
 { 
        for(y = 124; y > 0; y--); 
 } 
} 
 
static void Data_Delay_10us(void) 
{ 
    unsigned char  i; 
    i--; 
    i--; 
    i--; 
    i--; 
    i--; 
    i--; 
} 
 
/*读一个字节的数据*/ 
static unsigned char Data_ReadValue(void) 
{ 
    unsigned char count, value = 0, i; 
    status = OK;     //设定标志为正常状态 
    for(i = 8; i > 0; i--) 
 { 
  //高位在先 
  value <<= 1; 
  count = 0; 
  //每一位数据前会有一个               50us 的低电平时间.等待       50us 低电平结束 
        while(Data == 0 && count++ < NUMBER); 
  if(count >= NUMBER) 
  { 
   status = ERROR;   //设定错误标志 
   return 0;    //函数执行过程发生错误就退出函数 
  } 
  //26-28us     的高电平表示该位是         0,为 70us 高电平表该位     1 
  Data_Delay_10us(); 
  Data_Delay_10us(); 
  Data_Delay_10us(); 
  //延时       30us 后检测数据线是否还是高电平 
  if(Data != 0) 
  { 
   //进入这里表示该位是                 1 
   value++; 
   //等待剩余(约             40us)的高电平结束 
            while(Data != 0 && count++ < NUMBER) 
   { 
    Data_1; 
   } 
   if(count >= NUMBER) 
   { 
    status = ERROR;   //设定错误标志 
    return 0; 
   }  
  } 
 }  
 return (value); 
} 
 
 




//读温度和湿度函数，读一次的数据,共五字节，读出成功函数返回    OK, 错误返回    ERROR 
unsigned char Data_ReadTempAndHumi(void) 
{  
    unsigned char i = 0, check_value = 0,count = 0; 
//    EA = 0; 
    Data_0;       //拉低数据线大于    18ms 发送开始信号 
    Delay_1ms(20);   //需大于 18 毫秒 
    Data_1;       //释放数据线,用于检测低电平的应答信号 
 //延时     20-40us,等待一段时间后检测应答信号,应答信号是从机拉低数据线                      80us 
 Data_Delay_10us(); 
 Data_Delay_10us(); 
 Data_Delay_10us(); 
 Data_Delay_10us();  
   if(Data != 0)    //检测应答信号,应答信号是低电平 
{ 
  //没应答信号 
// EA = 1; 
 return ERROR; 
} 
else 
{ 
 //有应答信号 
       while(Data == 0 && count++ < NUMBER);    //等待应答信号结束 
 if(count >= NUMBER)  //检测计数器是否超过了设定的范围 
 { 
  Data_1; 
//  EA = 1; 
  return ERROR;   //读数据出错,退出函数 
 } 
 count = 0; 
 Data_1;//释放数据线  
 //应答信号后会有一个              80us 的高电平，等待高电平结束  
       while(Data != 0 && count++ < NUMBER); 
 if(count >= NUMBER) 
 { 
  Data_1; 
//  EA = 1; 
  return ERROR;  //退出函数 
 } 
                  
 //读出湿.温度值   
       for(i = 0; i < SIZE; i++) 
 { 
  value_array[i] = Data_ReadValue(); 
  if(status == ERROR)//调用        ReadValue()读数据出错会设定       status 为 ERROR 
  { 
   Data_1; 
//   EA = 1;    
   return ERROR;  
  } 
  //读出的最后一个值是校验值不需加上去 
  if(i != SIZE - 1)  
  { 
   //读出的五字节数据中的前四字节数据和等于第五字节数据表示成功 
   check_value += value_array[i];  
  } 
 }//end for 
  //在没用发生函数调用失败时进行校验 
  if(check_value == value_array[SIZE - 1]) 
  { 
   //将温湿度扩大  10 倍方便分离出每一位 
   humi_value = value_array[0] * 10; 
   temp_value = value_array[2] * 10; 
		
		return value_array[2];
		
   Data_1; 
//   EA = 1; 
   return OK;     //正确的读出           Data 输出的数据   
  } 
  else 
  { 
   //校验数据出错 
//   EA = 1; 
   return ERROR; 
  } 
 }         
} 















/*
//2.0 data

//sbit  P2_1  = P2^1 ;
//----------------------------------------------//
//----------------定义区--------------------//
//----------------------------------------------//
U8  U8FLAG;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;    
U8  indata[5];
U8  count, count_r=0;
U16 U16temp1,U16temp2;


uchar display[5] =   {0x00,0x00,0x00,0x00,0x00};

void Delay(U16 j)
{   
 U8 i;
 for(;j>0;j--)
 {  
  for(i=0;i<27;i++); 
 }
}


void delay(unsigned int num)//延时函数
{
  while( --num );
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




//串行总线  
void COM(void)
{

 U8 i;
 for(i=0;i<8;i++)    
 {
 
  U8FLAG=2;
  //----------------------
  P2_1=0 ;  //T
  P2_1=1 ;  //T
  //---------------------- 
  
  while((!Data)&&U8FLAG++);
  Delay_10us();
  Delay_10us();
  // Delay_10us();
  U8temp=0;
  if(Data)U8temp=1;
  U8FLAG=2;
  while((Data)&&U8FLAG++);
  
  //----------------------
  P2_1=0 ;  //T
  P2_1=1 ;  //T
  //----------------------
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
   Data_0;
   Delay(180);
   Data_1;
 //总线由上拉电阻拉高 主机延时20us
   Delay_10us();
   Delay_10us();
   Delay_10us();
   Delay_10us();
 //主机设为输入 判断从机响应信号 
   Data_1;
 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行   
   if(!Data)   //T !   
    {
    U8FLAG=2;////////////////////////////////////////////////////
  //判断从机是否发出 80us 的低电平响应信号是否结束  
    while((!Data)&&U8FLAG++);
    U8FLAG=2;
  //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
    while((Data)&&U8FLAG++);
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
    Data_1;
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





FLED_TEMP()//显示温度
{
 unsigned char  n=0;

//  display[4]=temp_data[0]&0x0f;
//  display[0]=ditab[display[4]];     //查表得小数位的值
  
//  display[4]=((temp_data[0]&0xf0)>>4)|((temp_data[1]&0x0f)<<4);

 display[4]=U8RH_data_H; 
 display[4]=display[4]%100;
 display[3]=display[4]/10;
 display[2]=display[1]%10;
 
 display[4]=U8T_data_H;
 display[4]=display[4]%100;
 display[1]=display[4]/10;
 display[0]=display[4]%10;
 
 if(!display[3])        //高位为0，不显示
 { 
  display[3]=0x0a;              
  if(!display[1])      //次次高位为0，不显示
    display[1]=0x0a;
 }

 d1=1;
 P0=Tab[display[0]]; 
 delay(5);
 d1=0;

 d2=1;
 P0=Tab[display[1]]; 
 delay(5);
 d2=0;

 d3=1;
 P0=Tab[display[2]]; 
 delay(5);
 d3=0;
 
 d4=1;
 P0=Tab[display[3]]; 
 delay(5);
 d4=0;
 
}

void main(void)
{
  while(1)
  {
    RH();           
 Disp_Temperature();
 //读取模块数据周期不易小于 2S 
 Delay(20000);
  }
}

*/




