//----------------------------------Description
// @file    ssd1306.c
// @author  Kiran
// @desc    SSD1306 Driver

//----------------------------------Libraries
#include "ssd1306.h"
#include "i2c.h"
 


//----------------------------------Display Init Sequence
static const uint8_t init[] = {
    0xA8, 0x3F,
    0xD3, 0x00,
    0x40,
    0xA1,
    0xC8,
    0xDA, 0x12,
    0x81, 0x7F,
    0xA4,
    0xA6,
    0xD5, 0x80,
    0x8D, 0x14,
    0xAF
};

//----------------------------------Static Functions


//----------------------------------Function Definitions
void SSD1306_SetType(uint8_t width, uint8_t height){
    _width = width;
    _height = height;
    _pages = height / 8;
}

void SSD1306_Init(uint8_t bus){
    I2C_WriteBuffer(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, init, sizeof(init));
}

void SSD1306_Update(void){
    I2C_WriteBuffer(bus, SSD1306_ADDR, SSD1306_CTRL_DATA, display, 1024);
}

void SSD1306_Fill(void){
    for (uint16_t a = 0; a <= 1024; a++){
        display[a] = 1;
    }
}

void SSD1306_Clear(void){
    for (uint16_t a = 0; a <= 1024; a++){
        display[a] = 0;
    }
}

void SSD1306_SetPixel(uint8_t x, uint8_t y, uint8_t val){
    // x is horizontal, 0 - 127
    // y is vertical, 0 - 63
    uint8_t page = (y >> 3);
    uint16_t index = (page * 128) + x;
    uint8_t bit = y & 0x07;
    if (val){
        display[index] |= (1 << bit);
    } else {
        display[index] &= ~(1 << bit);
    }
}


//----------------------------------End of File