//----------------------------------Description
// @file    flash.c
// @author  Kiran
// @desc    Flash Driver

//----------------------------------Libraries
#include "flash.h"
 
//----------------------------------Function Definitions
void FLASH_SetLatency(FLASH_WAIT wait_state){
    FLASH_BASE->ACR &= ~(0x7 << 0);
    FLASH_BASE->ACR |= (wait_state << 0);
}

//----------------------------------End of File
