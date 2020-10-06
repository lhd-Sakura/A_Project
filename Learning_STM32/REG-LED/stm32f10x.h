//用来存放STM32的寄存器映射的代码

//外设 perirhral


#define PERIPH_BASE      ((unsigned int)0x40000000)
#define APB1PERIPH_BASE      PERIPH_BASE
#define APB2PERIPH_BASE      (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE      (PERIPH_BASE + 0x20000)


#define RCC_BASE             (AHBPERIPH_BASE + 0x1000)
#define GPIOA_BASE           (APB2PERIPH_BASE + 0x0800)


#define RCC_APB2ENR          *(unsigned int*)(RCC_BASE + 0x18)

#define GPIOA_CRL            *(unsigned int*)(GPIOA_BASE + 0x00)
#define GPIOA_CRH            *(unsigned int*)(GPIOA_BASE + 0x04)
#define GPIOA_ODR            *(unsigned int*)(GPIOA_BASE + 0x0C)



#define GPIOA_BSRR           *(unsigned int*)(GPIOA_BASE + 0x10)
#define GPIOA_BRR            *(unsigned int*)(GPIOA_BASE + 0x14)


void delay1s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=46;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
 //   _nop_();  //if Keil,require use intrins.h
}



