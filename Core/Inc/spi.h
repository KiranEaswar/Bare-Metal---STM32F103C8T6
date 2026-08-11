//----------------------------------Description
// @file    spi.h
// @author  Kiran
// @desc    Header for the SPI Driver

//----------------------------------Instance Declaration
#ifndef SPI_H
#define SPI_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------SPI Register Layout (minimal)
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;
} SPI_TypeDef;

//----------------------------------Base Address Declaration
#define SPI1_BASE ((SPI_TypeDef*) 0x40013000U)
#define SPI2_BASE ((SPI_TypeDef*) 0x40003800U)

//----------------------------------Address Macros and Declaration
typedef enum {
    SPI_MODE_0 = 0, // CPOL=0, CPHA=0
    SPI_MODE_1,     // CPOL=0, CPHA=1
    SPI_MODE_2,     // CPOL=1, CPHA=0
    SPI_MODE_3      // CPOL=1, CPHA=1
} SPI_Mode;

typedef enum {
    SPI_BAUD_DIV2   = 0,
    SPI_BAUD_DIV4   = 1,
    SPI_BAUD_DIV8   = 2,
    SPI_BAUD_DIV16  = 3,
    SPI_BAUD_DIV32  = 4,
    SPI_BAUD_DIV64  = 5,
    SPI_BAUD_DIV128 = 6,
    SPI_BAUD_DIV256 = 7
} SPI_BAUD_DIV;

//----------------------------------Function Prototypes

void SPI_Init(uint8_t bus, SPI_Mode mode, SPI_BAUD_DIV baud);
uint8_t SPI_TransferByte(uint8_t bus, uint8_t data);
void SPI_Transmit(uint8_t bus, const uint8_t *buf, uint16_t len);
void SPI_Receive(uint8_t bus, uint8_t *buf, uint16_t len);
void SPI_Transfer(uint8_t bus, const uint8_t *tx, uint8_t *rx, uint16_t len);

//----------------------------------End of Header 
#endif