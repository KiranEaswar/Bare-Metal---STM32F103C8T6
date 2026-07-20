//----------------------------------Description
// @file    rcc.h
// @author  Kiran
// @desc    Header for the RCC Driver

//----------------------------------Instance Declaration
#ifndef RCC_H
#define RCC_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------RCC Struct
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_TypeDef;

//----------------------------------Address Macros and Declaration
#define RCC_BASE ((RCC_TypeDef*) 0x40021000U)

//----------------------------------Defines and Enums for ease of use
typedef enum
{
    RCC_SYSCLK_HSI,
    RCC_SYSCLK_HSE,
} RCC_SYSCLK;

typedef enum{
    RCC_APB2DIV_1    = 0,
    RCC_APB2DIV_2    = 4,
    RCC_APB2DIV_4    = 5,
    RCC_APB2DIV_8    = 6, 
    RCC_APB2DIV_16   = 7,
} RCC_APB2DIV;

typedef enum{
    RCC_APB1DIV_1    = 0,
    RCC_APB1DIV_2    = 4,
    RCC_APB1DIV_4    = 5,
    RCC_APB1DIV_8    = 6, 
    RCC_APB1DIV_16   = 7,
} RCC_APB1DIV;

typedef enum{
    RCC_AHBDIV_1    = 0,
    RCC_AHBDIV_2    = 8,
    RCC_AHBDIV_4    = 9,
    RCC_AHBDIV_8    = 10, 
    RCC_AHBDIV_16   = 11,
    RCC_AHBDIV_64    = 12,
    RCC_AHBDIV_128   = 13,
    RCC_AHBDIV_256   = 14,
    RCC_AHBDIV_512   = 15,
} RCC_AHBDIV;

typedef enum{
    RCC_PLL_MUL_4 = 2,
    RCC_PLL_MUL_5 = 3,
    RCC_PLL_MUL_6 = 4,
    RCC_PLL_MUL_7 = 5,
    RCC_PLL_MUL_8 = 6,
    RCC_PLL_MUL_9 = 7,
    RCC_PLL_MUL_6_5 = 13,
} RCC_PLL_MUL;


//----------------------------------APB1ENR bits
#define TIM2           (1 << 0)
#define TIM3           (1 << 1)
#define TIM4           (1 << 2)
#define TIM5           (1 << 3)
#define TIM6           (1 << 4)
#define TIM7           (1 << 5)
#define TIM12          (1 << 6)
#define TIM13          (1 << 7)
#define TIM14          (1 << 8)
#define WWDGEN         (1 << 11)
#define SPI2           (1 << 14)
#define SPI3           (1 << 15)

//----------------------------------APB2ENR bits
#define AFIO           (1 << 0)
#define GPIOA          (1 << 2)
#define GPIOB          (1 << 3)
#define GPIOC          (1 << 4)
#define GPIOD          (1 << 5)
#define GPIOE          (1 << 6)
#define GPIOF          (1 << 7)
#define GPIOG          (1 << 8)
#define ADC1           (1 << 9)
#define ADC2           (1 << 10)
#define TIM1           (1 << 11)
#define SPI1           (1 << 12)
#define TIM8           (1 << 13)
#define USART1         (1 << 14)
#define ADC3           (1 << 15)
#define TIM9           (1 << 19)
#define TIM10          (1 << 20)
#define TIM11          (1 << 21)

//----------------------------------Function Definitions
void RCC_Init(RCC_SYSCLK sysclk, RCC_APB2DIV apb2div, RCC_APB1DIV apb1div, RCC_AHBDIV ahbdiv, RCC_PLL_MUL pllmul);
void RCC_APB2_Enable(uint32_t peripheral);
void RCC_APB1_Enable(uint32_t peripheral);

//----------------------------------End of Header
#endif