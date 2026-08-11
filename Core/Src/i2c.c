//----------------------------------Description
// @file    i2c.c
// @author  Kiran
// @desc    I2C Driver

//----------------------------------Libraries
#include "i2c.h"
 
//----------------------------------Static Functions
static I2C_TypeDef* I2C_Get(uint8_t bus){
    switch(bus){
        case 1: return I2C1_BASE;
        case 2: return I2C2_BASE;
        default: return 0;
    }
}

static void I2C_ClearAddr(uint8_t bus){
    I2C_TypeDef* I2C = I2C_Get(bus);
    (void)I2C->SR1; (void)I2C->SR2;
}

//----------------------------------Function Definitions

void I2C_Init(uint8_t bus, uint8_t freq, uint16_t ccr, uint8_t trise){
    I2C_TypeDef* I2C = I2C_Get(bus);
    I2C->CR2 &= ~(0x3F << 0);
    I2C->CR2 |= (freq << 0);
    I2C->CCR &= ~(0xFFF << 0);
    I2C->CCR |= (ccr << 0);
    I2C->TRISE &= ~(0x3F << 0);
    I2C->TRISE |= (trise << 0);
    I2C->CR1 |= (1 << 0);
}

void I2C_SendStart(uint8_t bus){
    I2C_TypeDef* I2C = I2C_Get(bus);
    I2C->CR1 |= (1 << 8);
    while (!(I2C->SR1 & (1 << 0)));
}

void I2C_SendStop(uint8_t bus){
    I2C_TypeDef* I2C = I2C_Get(bus);
    while (!(I2C->SR1 & (1 << 7)));
    while (!(I2C->SR1 & (1 << 2)));
    I2C->CR1 |= (1 << 9);
}

void I2C_WriteAddr(uint8_t bus, uint8_t addr, uint8_t rw){
    I2C_TypeDef* I2C = I2C_Get(bus);
    I2C->DR = ((addr << 1) | (rw));
    while(!(I2C->SR1 & (1 << 1)));
}

void I2C_WriteByte(uint8_t bus, uint8_t data){
    I2C_TypeDef* I2C = I2C_Get(bus);

    while(!(I2C->SR1 & (1 << 7)));   // Wait TXE
    I2C->DR = data;
}

uint8_t I2C_ReadByte(uint8_t bus, uint8_t ack){
    I2C_TypeDef* I2C = I2C_Get(bus);
    if(ack){
        I2C->CR1 |= (1 << 10);
    } else {
        I2C->CR1 &= ~(1 << 10);
    } 
    while(!(I2C->SR1 & (1 << 6)));
    return I2C->DR;
}

void I2C_Write(uint8_t bus, uint8_t addr, uint8_t reg, uint8_t data){
    I2C_TypeDef* I2C = I2C_Get(bus);
    I2C_SendStart(bus);
    I2C_WriteAddr(bus, addr, 0);
    I2C_ClearAddr(bus);
    I2C->DR = reg;
    while(!(I2C->SR1 & (1 << 2)));
    I2C_WriteByte(bus, data);
    I2C_SendStop(bus); 
}

uint8_t I2C_Read(uint8_t bus, uint8_t addr, uint8_t reg){
    I2C_TypeDef* I2C = I2C_Get(bus);
    I2C_SendStart(bus);
    I2C_WriteAddr(bus, addr, 0);
    I2C_ClearAddr(bus);
    I2C->DR = (reg);
    while(!(I2C->SR1 & (1 << 2)));

    I2C_SendStart(bus);
    I2C_WriteAddr(bus, addr, 1);
    I2C_ClearAddr(bus);

    uint8_t data = I2C_ReadByte(bus, 0);
    I2C_SendStop(bus);
    return data;
}

void I2C_ReadBuffer(uint8_t bus, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len){
    I2C_TypeDef* I2C = I2C_Get(bus);
    I2C_SendStart(bus);
    I2C_WriteAddr(bus, addr, 0);
    I2C_ClearAddr(bus);
    I2C->DR = reg;
    while(!(I2C->SR1 & (1 << 2)));

    I2C_SendStart(bus);
    I2C_WriteAddr(bus, addr, 1);
    I2C_ClearAddr(bus);

    for(uint16_t i = 0; i < len-1; i++){
        buf[i] = I2C_ReadByte(bus, 1);
    }
    buf[len-1] = I2C_ReadByte(bus, 0);
    I2C_SendStop(bus);
}

void I2C_WriteBuffer(uint8_t bus, uint8_t addr, uint8_t ctrl, uint8_t *buf, uint16_t len){
    I2C_SendStart(bus);
    I2C_WriteAddr(bus, addr, 0);
    I2C_ClearAddr(bus);
    I2C_WriteByte(bus, ctrl);
    for (uint16_t i = 0; i < len; i++){
        I2C_WriteByte(bus, buf[i]);
    }
    I2C_SendStop(bus);
}

//----------------------------------End of File
