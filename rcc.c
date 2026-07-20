//----------------------------------Description
// @file    rcc.c
// @author  Kiran
// @desc    RCC Driver

//----------------------------------Libraries
#include "rcc.h"

//----------------------------------Function Definitions
void RCC_Init(RCC_SYSCLK sysclk, RCC_APB2DIV apb2div, RCC_APB1DIV apb1div, RCC_AHBDIV ahbdiv, RCC_PLL_MUL pllmul){
    switch(sysclk){
        case 0: {
            RCC_BASE->CR |= (1 << 0);
            while (!(RCC_BASE->CR & (1 << 1)));
            break;
        }
        case 1: {
            RCC_BASE->CR |= (1 << 16); 
            while (!(RCC_BASE->CR & (1 << 17)));
            break;
        }
    }

    RCC_BASE->CFGR &= ~(0x3FF << 4);
    RCC_BASE->CFGR |= (ahbdiv << 4); 
    RCC_BASE->CFGR |= (apb1div << 8);
    RCC_BASE->CFGR |= (apb2div << 11);

    switch(sysclk){
        case 0: RCC_BASE->CFGR &= ~(1 << 16); break;
        case 1: RCC_BASE->CFGR |= (1 << 16); break;
    }

    RCC_BASE->CFGR &= ~(0xF << 18);
    RCC_BASE->CFGR |= (pllmul << 18);

    RCC_BASE->CR |= (1 << 24);
    while (!(RCC_BASE->CR & (1 << 25)));

    RCC_BASE->CFGR &= ~(3 << 0);
    RCC_BASE->CFGR |= (2 << 0);
    while ((RCC_BASE->CFGR & (3 << 2)) != (2 << 2));
}

void RCC_APB2_Enable(uint32_t peripheral){
    RCC_BASE->APB2ENR |= peripheral;
}

void RCC_APB1_Enable(uint32_t peripheral){
    RCC_BASE->APB1ENR |= peripheral;
}

//----------------------------------End of File