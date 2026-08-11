//----------------------------------Description
// @file    main.c
// @author  Kiran
// @desc    Main File

//----------------------------------Libraries
#include "rcc.h"
#include "gpio.h"
#include "tim.h"
#include "flash.h"
#include <stdlib.h>

//----------------------------------Functions

//----------------------------------Main Loop
int main(void){
    //__Setup__
    FLASH_SetLatency(FLASH_WAIT_2);
    RCC_Init(RCC_SYSCLK_HSE, RCC_APB2DIV_1, RCC_APB1DIV_2, RCC_AHBDIV_1, RCC_PLL_MUL_9);
    RCC_APB2_Enable(GPIOC);
    RCC_APB1_Enable(TIM2);
    GPIO_Init(GPIO_PORT_C, 13, GPIO_CNF_OUT_GP_PUPD, GPIO_MODE_OUT_2M);
    GPIO_Write(GPIO_PORT_C, 13, 0);
    TIM_Init(2, 71, 999);
    TIM_Start(2);
    //__Loop Forever__
    while(1){
        GPIO_Toggle(GPIO_PORT_C, 13);
        TIM_Delay_ms(2, 1000);
    }
}