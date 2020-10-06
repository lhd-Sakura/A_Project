//用来存放STM32的寄存器映射的代码
//外设 perirhral
#ifndef _STM32F10X_H
#define _STM32F10X_H



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



//结构体
typedef unsigned int       uint32_t;
typedef unsigned int       uint16_t;


typedef struct
{
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_TypeDef;



#define GPIOA     ((GPIO_TypeDef*)GPIOA_BASE)


typedef struct
{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
}RCC_TypeDef;

#define RCC      ((RCC_TypeDef*)RCC_BASE)





#endif/* _STM32F10X_H */


