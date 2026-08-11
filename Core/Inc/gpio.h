//----------------------------------Description
// @file    gpio.h
// @author  Kiran
// @desc    Header for the GPIO Driver

//----------------------------------Instance Declaration
#ifndef GPIO_H
#define GPIO_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------GPIO Struct
typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

//----------------------------------Address Macros and Declaration
#define GPIO_BASE 0x40010800U
#define GPIO(port) ((GPIO_TypeDef*)(GPIO_BASE + ((port) * 0x400U)))

//----------------------------------Defines and Enums for ease of use
typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_Port;

typedef enum
{
    GPIO_CNF_ANALOG = 0,     
    GPIO_CNF_FLOAT_IN = 1,
    GPIO_CNF_IN_PUPD = 2,
    GPIO_CNF_RES = 3,

    GPIO_CNF_OUT_GP_PUPD = 0,
    GPIO_CNF_OUT_GP_OD = 1,
    GPIO_CNF_OUT_AF_PUPD = 2,
    GPIO_CNF_OUT_AF_OD = 3

} GPIO_CNF;

typedef enum
{
    GPIO_MODE_IN = 0,
    GPIO_MODE_OUT_10M = 1,
    GPIO_MODE_OUT_2M = 2,
    GPIO_MODE_OUT_50M = 3
} GPIO_Mode;

//----------------------------------Function Definitions
void GPIO_Init(GPIO_Port port, uint8_t pin, GPIO_CNF cnf, GPIO_Mode mode);
void GPIO_Write(GPIO_Port port, uint8_t pin, uint8_t value);
uint8_t GPIO_Read(GPIO_Port port, uint8_t pin);
void GPIO_Toggle(GPIO_Port port, uint8_t pin);

//----------------------------------End of Header
#endif