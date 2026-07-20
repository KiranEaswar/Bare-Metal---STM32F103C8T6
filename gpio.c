//----------------------------------Description
// @file    gpio.c
// @author  Kiran
// @desc    GPIO Driver

//----------------------------------Libraries
#include "gpio.h"
 
//----------------------------------Function Definitions
void GPIO_Init(GPIO_Port port, uint8_t pin, GPIO_CNF cnf, GPIO_Mode mode)
{
    uint32_t config = (cnf << 2) | mode;

    if (pin < 8)
    {
        GPIO(port)->CRL &= ~(0xFU << (pin * 4));
        GPIO(port)->CRL |=  (config << (pin * 4));
    }
    else
    {
        GPIO(port)->CRH &= ~(0xFU << ((pin - 8) * 4));
        GPIO(port)->CRH |=  (config << ((pin - 8) * 4));
    }
}

void GPIO_Write(GPIO_Port port, uint8_t pin, uint8_t value){
    if(value){
        GPIO(port)->BSRR = (1 << pin);
    } else {
        GPIO(port)->BSRR = (1 << (pin + 0x10U));
    }
}

uint8_t GPIO_Read(GPIO_Port port, uint8_t pin){
    return (GPIO(port)->IDR >> pin) & 1;
}

void GPIO_Toggle(GPIO_Port port, uint8_t pin){
    GPIO(port)->ODR ^= (1 << pin);
}

//----------------------------------End of File
