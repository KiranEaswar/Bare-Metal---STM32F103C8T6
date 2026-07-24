//----------------------------------Description
// @file    i2c.c
// @author  Kiran
// @desc    I2C Driver

//----------------------------------Libraries
#include "i2c.h"
 
//----------------------------------Function Definitions
static I2C_TypeDef* I2C_Get(uint8_t bus){
    switch(bus){
        case(1): return I2C1_BASE;
        case(2): return I2C2_BASE;
        default: return 0;
    }
}

void I2C_Init(uint8_t bus, uint8_t freq, uint16_t ccr, uint8_t trise){
    switch(bus){
        case(1): {
            I2C1_BASE->CR2 &= ~(0x3F << 0);
            I2C1_BASE->CR2 |= (freq << 0);
            I2C1_BASE->CCR &= ~(0xFFF << 0);
            I2C1_BASE->CCR |= (ccr << 0);
            I2C1_BASE->TRISE &= ~(0x3F << 0);
            I2C1_BASE->TRISE |= (trise << 0);
            break;
        }
    I2C_Get(bus)
}

void I2C_Start(uint8_t bus){
    switch(bus){
        case(1): I2C1_BASE->CR1 |= (1 << 0); break;
        case(2): I2C2_BASE->CR1 |= (1 << 0); break;
    }
}

void I2C_Stop(uint8_t bus){
    I2C_TypeDef* i2c = I2C_Get(bus);
    while(!(i2c->SR1 & (1 << 2)));
    while(!(i2c->SR2 & (1 << 1)));
    i2c->CR1 &= ~(1 << 0);
}

void I2C_Write(uint8_t bus, uint8_t addr, uint8_t reg, uint8_t data)
{
    I2C_TypeDef *i2c = I2C_Get(bus);
    i2c->CR1 |= (1 << 8);
    while(!(i2c->SR1 & (1 << 0)));
    i2c->DR = (addr << 1);
    while(!(i2c->SR1 & (1 << 1)));
    (void)i2c->SR1;
    (void)i2c->SR2;
    i2c->DR = reg;
    while(!(i2c->SR1 & (1 << 7)));
    i2c->DR = data;
    while(!(i2c->SR1 & (1 << 2)));
    i2c->CR1 |= (1 << 9);
}

void I2C_WriteByte(uint8_t bus, uint8_t data);
uint8_t I2C_ReadByte(uint8_t bus, uint8_t ack);
void I2C_WriteAddr(uint8_t bus, uint8_t addr, uint8_t rw);
uint8_t I2C_Read(uint8_t bus, uint8_t addr, uint8_t reg);
void I2C_WriteBuffer(uint8_t bus, uint8_t addr, uint8_t ctrl, uint8_t *buf, uint16_t len);

//----------------------------------End of File
 