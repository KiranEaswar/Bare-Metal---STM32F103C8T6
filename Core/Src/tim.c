//----------------------------------Description
// @file    tim.c
// @author  Kiran
// @desc    Timer Driver

//----------------------------------Libraries
#include "tim.h"

//----------------------------------Private Function Definitions
static TIM_TypeDef* TIM_Get_Clock(uint8_t timer){
    switch (timer){
        case 2: return TIM2_BASE;
        case 3: return TIM3_BASE;
        case 4: return TIM4_BASE;
        case 5: return TIM5_BASE;
        default: return 0;
    }
}

//----------------------------------Public Function Definitions
void TIM_Init(uint8_t timer, uint32_t psc, uint32_t arr){
    TIM_TypeDef* TIM = TIM_Get_Clock(timer);
    TIM->PSC = psc;
    TIM->ARR = arr;
    TIM->DIER |= (1 << 0);
}

void TIM_Start(uint8_t timer){
    TIM_TypeDef* TIM = TIM_Get_Clock(timer);
    TIM->CR1 |= (1 << 0);
}

void TIM_Stop(uint8_t timer){
    TIM_TypeDef* TIM = TIM_Get_Clock(timer);
    TIM->CR1 &= ~(1 << 0);
}

void TIM_Delay_ms(uint8_t timer, uint32_t ms){
    
    //Polling
    TIM_TypeDef* TIM = TIM_Get_Clock(timer);
    for (uint32_t i = 0; i < ms; i++){
        while(!(TIM->SR & (1 << 0)));
        TIM->SR &= ~(1 << 0);   
    }
}   

//----------------------------------End of File