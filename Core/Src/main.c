//----------------------------------Description
// @file    main.c
// @author  Kiran
// @desc    Main File

//----------------------------------Libraries
#include "rcc.h"
#include "gpio.h"
#include "flash.h"
#include "i2c.h"
#include "ssd1306.h"
#include "tim.h"
#include <stdint.h>

//----------------------------------Functions

//----------------------------------Main Loop
int main(void){
    //__Setup__
    FLASH_SetLatency(FLASH_WAIT_2);
    RCC_Init(RCC_SYSCLK_HSE, RCC_APB2DIV_1, RCC_APB1DIV_2, RCC_AHBDIV_1, RCC_PLL_MUL_9);

    RCC_APB2_Enable(GPIOB);
    RCC_APB1_Enable(TIM2);
    RCC_APB1_Enable(I2C1EN);

    GPIO_Init(GPIO_PORT_B, 6, GPIO_CNF_OUT_AF_OD, GPIO_MODE_OUT_2M);
    GPIO_Init(GPIO_PORT_B, 7, GPIO_CNF_OUT_AF_OD, GPIO_MODE_OUT_2M);

    I2C_Init(1, 36, 180, 37);
    TIM_Init(2, 71, 999);
    TIM_Start(2);

    TIM_Delay_ms(2, 1000);

    SSD1306_Init(1);
    SSD1306_Fill();       // fill with 0xFF
    SSD1306_Update(1);    // should show all pixels ON

    TIM_Delay_ms(2, 1000);

    SSD1306_CheckerBoard(12);
    SSD1306_Update(1);

    //__Loop Forever__
    while(1){
        SSD1306_TestPatterns(1);
    }
}