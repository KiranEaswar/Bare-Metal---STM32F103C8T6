//----------------------------------Description
// @file    tim.h
// @author  Kiran
// @desc    Header for the Timer Driver

//----------------------------------Instance Declaration
#ifndef TIM_H
#define TIM_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------Timer Struct
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RESERVED0;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t RESERVED1;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
} TIM_TypeDef;

//----------------------------------Address Macros and Declaration
#define TIM2_BASE ((TIM_TypeDef*) 0x40000000U)
#define TIM3_BASE ((TIM_TypeDef*) 0x40000400U)
#define TIM4_BASE ((TIM_TypeDef*) 0x40000800U)
#define TIM5_BASE ((TIM_TypeDef*) 0x40000C00U)

//----------------------------------Function Definitions
void TIM_Init(uint8_t timer, uint32_t psc, uint32_t arr);
void TIM_Start(uint8_t timer);
void TIM_Stop(uint8_t timer);
void TIM_Delay_ms(uint8_t timer, uint32_t ms);

//----------------------------------End of Header
#endif