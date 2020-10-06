#include"bsp_system.h"


//������Լ���     Data �ӵ�  IO �����Ķ�λ���� 
//��ֹ����Ӳ��ͨ��ʱ������ѭ���ļ�����Χ 
#define NUMBER   20 
#define SIZE 5 
static unsigned char status; 
//������ֽ����ݵ����� 
static unsigned char value_array[SIZE]; 
/*�����������ļ�������ʪ��ֵ,ʵ�����¶ȵ������� 10 �� 
��  Data ���ص��¶���     26,�� temp_value = 260, ʪ��ͬ��*/ 
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
 
/*��һ���ֽڵ�����*/ 
static unsigned char Data_ReadValue(void) 
{ 
    unsigned char count, value = 0, i; 
    status = OK;     //�趨��־Ϊ����״̬ 
    for(i = 8; i > 0; i--) 
 { 
  //��λ���� 
  value <<= 1; 
  count = 0; 
  //ÿһλ����ǰ����һ��               50us �ĵ͵�ƽʱ��.�ȴ�       50us �͵�ƽ���� 
        while(Data == 0 && count++ < NUMBER); 
  if(count >= NUMBER) 
  { 
   status = ERROR;   //�趨�����־ 
   return 0;    //����ִ�й��̷���������˳����� 
  } 
  //26-28us     �ĸߵ�ƽ��ʾ��λ��         0,Ϊ 70us �ߵ�ƽ���λ     1 
  Data_Delay_10us(); 
  Data_Delay_10us(); 
  Data_Delay_10us(); 
  //��ʱ       30us �����������Ƿ��Ǹߵ�ƽ 
  if(Data != 0) 
  { 
   //���������ʾ��λ��                 1 
   value++; 
   //�ȴ�ʣ��(Լ             40us)�ĸߵ�ƽ���� 
            while(Data != 0 && count++ < NUMBER) 
   { 
    Data_1; 
   } 
   if(count >= NUMBER) 
   { 
    status = ERROR;   //�趨�����־ 
    return 0; 
   }  
  } 
 }  
 return (value); 
} 
 
 




//���¶Ⱥ�ʪ�Ⱥ�������һ�ε�����,�����ֽڣ������ɹ���������    OK, ���󷵻�    ERROR 
unsigned char Data_ReadTempAndHumi(void) 
{  
    unsigned char i = 0, check_value = 0,count = 0; 
//    EA = 0; 
    Data_0;       //���������ߴ���    18ms ���Ϳ�ʼ�ź� 
    Delay_1ms(20);   //����� 18 ���� 
    Data_1;       //�ͷ�������,���ڼ��͵�ƽ��Ӧ���ź� 
 //��ʱ     20-40us,�ȴ�һ��ʱ�����Ӧ���ź�,Ӧ���ź��Ǵӻ�����������                      80us 
 Data_Delay_10us(); 
 Data_Delay_10us(); 
 Data_Delay_10us(); 
 Data_Delay_10us();  
   if(Data != 0)    //���Ӧ���ź�,Ӧ���ź��ǵ͵�ƽ 
{ 
  //ûӦ���ź� 
// EA = 1; 
 return ERROR; 
} 
else 
{ 
 //��Ӧ���ź� 
       while(Data == 0 && count++ < NUMBER);    //�ȴ�Ӧ���źŽ��� 
 if(count >= NUMBER)  //���������Ƿ񳬹����趨�ķ�Χ 
 { 
  Data_1; 
//  EA = 1; 
  return ERROR;   //�����ݳ���,�˳����� 
 } 
 count = 0; 
 Data_1;//�ͷ�������  
 //Ӧ���źź����һ��              80us �ĸߵ�ƽ���ȴ��ߵ�ƽ����  
       while(Data != 0 && count++ < NUMBER); 
 if(count >= NUMBER) 
 { 
  Data_1; 
//  EA = 1; 
  return ERROR;  //�˳����� 
 } 
                  
 //����ʪ.�¶�ֵ   
       for(i = 0; i < SIZE; i++) 
 { 
  value_array[i] = Data_ReadValue(); 
  if(status == ERROR)//����        ReadValue()�����ݳ�����趨       status Ϊ ERROR 
  { 
   Data_1; 
//   EA = 1;    
   return ERROR;  
  } 
  //���������һ��ֵ��У��ֵ�������ȥ 
  if(i != SIZE - 1)  
  { 
   //���������ֽ������е�ǰ���ֽ����ݺ͵��ڵ����ֽ����ݱ�ʾ�ɹ� 
   check_value += value_array[i];  
  } 
 }//end for 
  //��û�÷�����������ʧ��ʱ����У�� 
  if(check_value == value_array[SIZE - 1]) 
  { 
   //����ʪ������  10 ����������ÿһλ 
   humi_value = value_array[0] * 10; 
   temp_value = value_array[2] * 10; 
		
		return value_array[2];
		
   Data_1; 
//   EA = 1; 
   return OK;     //��ȷ�Ķ���           Data ���������   
  } 
  else 
  { 
   //У�����ݳ��� 
//   EA = 1; 
   return ERROR; 
  } 
 }         
} 















/*
//2.0 data

//sbit  P2_1  = P2^1 ;
//----------------------------------------------//
//----------------������--------------------//
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


void delay(unsigned int num)//��ʱ����
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




//��������  
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
  //��ʱ������forѭ��    
  if(U8FLAG==1)break;
  //�ж�����λ��0����1  
  
  // ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
  
  U8comdata<<=1;
  U8comdata|=U8temp;        //0
 }//rof

}

 //--------------------------------
 //-----ʪ�ȶ�ȡ�ӳ��� ------------
 //--------------------------------
 //----���±�����Ϊȫ�ֱ���--------
 //----�¶ȸ�8λ== U8T_data_H------
 //----�¶ȵ�8λ== U8T_data_L------
 //----ʪ�ȸ�8λ== U8RH_data_H-----
 //----ʪ�ȵ�8λ== U8RH_data_L-----
 //----У�� 8λ == U8checkdata-----
 //----��������ӳ�������----------
 //---- Delay();, Delay_10us();,COM(); 
 //--------------------------------

void RH(void)
{
  //��������18ms 
   Data_0;
   Delay(180);
   Data_1;
 //������������������ ������ʱ20us
   Delay_10us();
   Delay_10us();
   Delay_10us();
   Delay_10us();
 //������Ϊ���� �жϴӻ���Ӧ�ź� 
   Data_1;
 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������   
   if(!Data)   //T !   
    {
    U8FLAG=2;////////////////////////////////////////////////////
  //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����  
    while((!Data)&&U8FLAG++);
    U8FLAG=2;
  //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
    while((Data)&&U8FLAG++);
  //���ݽ���״̬   
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
  //����У�� 
  
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





FLED_TEMP()//��ʾ�¶�
{
 unsigned char  n=0;

//  display[4]=temp_data[0]&0x0f;
//  display[0]=ditab[display[4]];     //����С��λ��ֵ
  
//  display[4]=((temp_data[0]&0xf0)>>4)|((temp_data[1]&0x0f)<<4);

 display[4]=U8RH_data_H; 
 display[4]=display[4]%100;
 display[3]=display[4]/10;
 display[2]=display[1]%10;
 
 display[4]=U8T_data_H;
 display[4]=display[4]%100;
 display[1]=display[4]/10;
 display[0]=display[4]%10;
 
 if(!display[3])        //��λΪ0������ʾ
 { 
  display[3]=0x0a;              
  if(!display[1])      //�δθ�λΪ0������ʾ
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
 //��ȡģ���������ڲ���С�� 2S 
 Delay(20000);
  }
}

*/




