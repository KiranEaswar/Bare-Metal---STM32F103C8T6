//----------------------------------Description
// @file    uart.c
// @author  Kiran
// @desc    UART Driver

//----------------------------------Libraries
#include "uart.h"
 
//----------------------------------Function Definitions
static UART_TypeDef* UART_Get(uint8_t bus){
    switch (bus){
        case 1: return UART1;
        case 2: return UART2;
        case 3: return UART3;
        case 4: return UART4;
        case 5: return UART5;
    }
}

void UART_Init(uint8_t bus, uint32_t freq, uint32_t baud){
    UART_TypeDef *UART = UART_Get(bus);
    uint32_t mantissa = freq / (16U * baud);
    uint32_t fraction = ((freq % (16U * baud)) * 16U) / (16U * baud);

    UART->BRR = (mantissa << 4) | fraction;
    UART->CR1 |= (1U << 13);
    UART->CR1 |= (1U << 3);
    UART->CR1 |= (1U << 2);
}

void UART_WriteByte(uint8_t bus, uint8_t byte){
    UART_TypeDef *UART = UART_Get(bus);
    while(!((UART->SR) & (1U << 7)));
    UART->DR = byte;
}

uint8_t UART_ReadByte(uint8_t bus){
    UART_TypeDef *UART = UART_Get(bus);
    while(!((UART->SR) & (1U << 5)));
    uint8_t data = UART->DR;
    return data;
}

void UART_WriteBuffer(uint8_t bus, uint8_t* byteArray, uint16_t length){
    for (uint16_t i = 0; i < length; i++){
        UART_WriteByte(bus, byteArray[i]);
    }
}

void UART_ReadBuffer(uint8_t bus, uint8_t* byteArray, uint16_t length){
    for (uint16_t i = 0; i < length; i++){
        byteArray[i] = UART_ReadByte(bus);
    }
}


//----------------------------------End of File
