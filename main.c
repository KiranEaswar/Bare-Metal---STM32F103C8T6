//----------------------------------Description
// @file    main.c
// @author  Kiran
// @desc    Main File

//----------------------------------Libraries
#include "rcc.h"
#include "gpio.h"
#include "flash.h"
#include "i2c.h"
#include <stdint.h>

//----------------------------------Functions

//----------------------------------Main Loop
int main(void){
    //__Setup__
    FLASH_SetLatency(FLASH_WAIT_2);
    RCC_Init(RCC_SYSCLK_HSE, RCC_APB2DIV_1, RCC_APB1DIV_2, RCC_AHBDIV_1, RCC_PLL_MUL_9);

    RCC_APB2_Enable(GPIOB);

    GPIO_Init(GPIO_PORT_B, 6, GPIO_CNF_OUT_AF_OD, GPIO_MODE_OUT_2M);
    GPIO_Init(GPIO_PORT_B, 7, GPIO_CNF_OUT_AF_OD, GPIO_MODE_OUT_2M);

    RCC_APB1_Enable(TIM2);
    RCC_APB1_Enable(I2C1EN);

    I2C_Init(1, 36, 180, 37);

    I2C_Write(1, 0x3C, 0x00, 0xAE);  // off
    I2C_Write(1, 0x3C, 0x00, 0x8D);  // charge pump
    I2C_Write(1, 0x3C, 0x00, 0x14);  // enable
    I2C_Write(1, 0x3C, 0x00, 0xAF);  // on

    
    //__Loop Forever__
    while(1){

    }
}