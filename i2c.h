//----------------------------------Description
// @file    i2c.h
// @author  Kiran
// @desc    Header for the I2C Driver

//----------------------------------Instance Declaration
#ifndef I2C_H
#define I2C_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------Flash Struct
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
} I2C_TypeDef;

//----------------------------------Address Macros and Declaration
#define I2C1_BASE ((I2C_TypeDef*) 0x40005400U)


//----------------------------------Defines and Enums for ease of use


//----------------------------------Function Definitions
void I2C_Init(uint8_t freq,//----------------------------------Description
// @file    i2c.h
// @author  Kiran
// @desc    Header for the I2C Driver

//----------------------------------Instance Declaration
#ifndef I2C_H
#define I2C_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------Flash Struct
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
} I2C_TypeDef;

//----------------------------------Address Macros and Declaration
#define I2C1_BASE ((I2C_TypeDef*) 0x40005400U)
#define I2C2_BASE ((I2C_TypeDef*) 0x40005800U)

//----------------------------------Defines and Enums for ease of use


//----------------------------------Function Declaration
void I2C_Init(uint8_t bus, uint8_t freq, uint16_t ccr, uint8_t trise);
void I2C_Start(uint8_t bus);
void I2C_Stop(uint8_t bus);
void I2C_WriteAddr(uint8_t bus, uint8_t addr, uint8_t rw);
void I2C_WriteByte(uint8_t bus, uint8_t data);
uint8_t I2C_ReadByte(uint8_t bus, uint8_t ack);
void I2C_Write(uint8_t bus, uint8_t addr, uint8_t reg, uint8_t data);
uint8_t I2C_Read(uint8_t bus, uint8_t addr, uint8_t reg);
void I2C_WriteBuffer(uint8_t bus, uint8_t addr, uint8_t ctrl, uint8_t *buf, uint16_t len);

//----------------------------------End of Header
#endif 
