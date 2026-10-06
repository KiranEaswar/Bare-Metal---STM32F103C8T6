//----------------------------------Description
// @file    uart.h
// @author  Kiran
// @desc    UART Driver

#ifndef UART_H
#define UART_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------UART Struct
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} UART_TypeDef;

//----------------------------------Address Macros and Declaration
#define UART1           ((UART_TypeDef*) 0x40013800U)
#define UART2           ((UART_TypeDef*) 0x40004400U)
#define UART3           ((UART_TypeDef*) 0x40004800U)

//----------------------------------Function Definitions

void UART_Init(uint8_t bus, uint32_t freq, uint32_t baud);
void UART_WriteByte(uint8_t bus, uint8_t byte);
uint8_t UART_ReadByte(uint8_t bus);
void UART_WriteBuffer(uint8_t bus, uint8_t* byteArray, uint16_t length);
void UART_ReadBuffer(uint8_t bus, uint8_t* byteArray, uint16_t length);

#endif

//----------------------------------End of File