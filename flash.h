//----------------------------------Description
// @file    flash.h
// @author  Kiran
// @desc    Header for the Flash Driver

//----------------------------------Instance Declaration
#ifndef FLASH_H
#define FLASH_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------Flash Struct
typedef struct
{
    volatile uint32_t ACR;      // 0x00 Flash Access Control Register
    volatile uint32_t KEYR;     // 0x04 Flash Key Register
    volatile uint32_t OPTKEYR;  // 0x08 Flash Option Key Register
    volatile uint32_t SR;       // 0x0C Status Register
    volatile uint32_t CR;       // 0x10 Control Register
    volatile uint32_t AR;       // 0x14 Address Register
    volatile uint32_t RESERVED;
    volatile uint32_t OBR;      // 0x1C Option Byte Register
    volatile uint32_t WRPR;     // 0x20 Write Protection Register
} FLASH_TypeDef;

//----------------------------------Address Macros and Declaration
#define FLASH_BASE ((FLASH_TypeDef*) 0x40022000U)


//----------------------------------Defines and Enums for ease of use
typedef enum{
    FLASH_WAIT_0,
    FLASH_WAIT_1,
    FLASH_WAIT_2,
} FLASH_WAIT;

//----------------------------------Function Definitions
void FLASH_SetLatency(FLASH_WAIT wait_state);

//----------------------------------End of Header
#endif