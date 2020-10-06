/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "./led/bsp_led.h" 
#include "./usart/bsp_usart.h" 

static void Show_Message(void);
  
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  char ch;
  
  /* LED GPIO ��ʼ�� */
  LED_GPIO_Config();
  
  /* ��ʼ��USART ����ģʽΪ 115200 8-N-1 */
  USART_Config();
	
  /* ��ӡָ��������ʾ��Ϣ */
  Show_Message();
  while(1)
	{	
    /* ��ȡ�ַ�ָ�� */
    ch=getchar();
    printf("���յ��ַ���%c\n",ch);
    
    /* �����ַ�ָ�����RGB�ʵ���ɫ */
    switch(ch)
    {
      case '1':
        LED1_ON;
      break;
      case '2':
        LED2_ON;
      break;
      case '3':
        LED1_OFF;
				LED2_OFF;
      break;
      default:
        /* �������ָ��ָ���ַ�����ӡ��ʾ��Ϣ */
        Show_Message();
        break;      
    }   
	}	
}


/**
  * @brief  ��ӡָ��������ʾ��Ϣ
  * @param  ��
  * @retval ��
  */
static void Show_Message(void)
{
  printf("\r\n   ����һ��ͨ������ͨ��ָ�����LED��ʵ�� \n");
  printf("ʹ��  USART  ����Ϊ��%d 8-N-1 \n",DEBUG_USART_BAUDRATE);
  printf("������ӵ�ָ������LED����ɫ��ָ���Ӧ���£�\n");
  printf("   ָ��   ------ LED�ƺ� \n");
  printf("     1    ------    LED1 \n");
  printf("     2    ------    LED2 \n");
  printf("     3    ------    �� \n");  
}

/*********************************************END OF FILE**********************/
