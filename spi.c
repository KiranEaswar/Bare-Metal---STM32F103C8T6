//----------------------------------Description
// @file    ssd1306.c
// @author  Kiran
// @desc    SSD1306 Driver

//----------------------------------Libraries
#include "ssd1306.h"
#include "i2c.h"
 


//----------------------------------Display Init Sequence
static uint8_t display[1024];

//----------------------------------Static Functions


//----------------------------------Function Definitions
static SPI_TypeDef* SPI_Get(uint8_t bus){
    switch (bus){
        case 1: return SPI1_BASE;
        case 2: return SPI2_BASE;
    }
}

void SPI_Init(uint8_t bus, SPI_Mode mode, SPI_BAUD_DIV baud){
    SPI_TypeDef* SPI = SPI_Get(bus);
    SPI->CR1 &= ~(0x3U << 0);
    SPI->CR1 |= (mode << 0);
    SPI->CR1 &= ~(0x7 << 3);
    SPI->CR1 |= (baud << 3);
    SPI->CR1 |= (1 << 2);
    SPI->CR1 |= (0x3U << 8);
    SPI->CR1 |= (1 << 6);
}

uint8_t SPI_TransferByte(uint8_t bus, uint8_t data){
    SPI_TypeDef* SPI = SPI_Get(bus);
    while (!((SPI->SR) & (1 << 1)));
    SPI->DR = (data);
    while (!((SPI->SR) & (1 << 0)));
    return SPI->DR;
}

void SPI_Receive(uint8_t bus, uint8_t *buf, uint16_t len){
    SPI_TypeDef* SPI = SPI_Get(bus);
    for (uint16_t i = 0; i < len; i++){
        while (!(SPI->SR & (1 << 1))); 
        SPI->DR = 0xFF;
        while (!((SPI->SR) & (1 << 0)));
        buf[i] = SPI->DR;
    }
    while (SPI->SR & (1 << 7));
}

void SPI_Transmit(uint8_t bus, const uint8_t *buf, uint16_t len){
    SPI_TypeDef* SPI = SPI_Get(bus);
    for (uint16_t i = 0; i < len; i++){
        while (!((SPI->SR) & (1 << 1)));
        SPI->DR = buf[i];
        while (!(SPI->SR & (1 << 0))); 
        (void)SPI->DR;
    }
    while (SPI->SR & (1 << 7));
}

void SPI_Transfer(uint8_t bus, const uint8_t *tx, uint8_t *rx, uint16_t len){
    SPI_TypeDef* SPI = SPI_Get(bus);
    for (uint16_t i = 0; i < len; i++){
        rx[i] = SPI_TransferByte(bus, tx[i]);
    }
    while (SPI->SR & (1 << 7));
}

//----------------------------------End of File