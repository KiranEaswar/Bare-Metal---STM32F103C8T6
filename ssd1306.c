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
void SSD1306_Init(uint8_t bus){
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xAE);  // Display OFF

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x20);  // Set Memory Addressing mode
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x00);  // Horizontal Addressing Mode

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xB0);  // Set Page Start Address for Page Addressing Mode

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xC8);  // Set COM Output Scan Direction

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x00);  // Set low column address
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x10);  // Set high column address

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x40);  // Set start line address

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xFF);  // Set contrast control register

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xA1);  // Set segment re-map 0 to 127

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xA6);  // Set normal display

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xA8);  // Set multiplex ratio(1 to 64)

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x3F);  // 1/64 duty

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xA4);  // Output RAM to Display

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xD3);  // Set display offset
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x00);  // No offset

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xD5);  // Set display clock divide ratio/oscillator frequency
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xF0);  // Set divide ratio

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xD9);  // Set pre-charge period
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x22);  // Set pre-charge period (0x22)

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xDA);  // Set com pins hardware configuration
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x12);  // Set com pins hardware configuration (0x12)

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xDB);  // Set vcomh
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x20);  // Set vcomh (0x20)

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x8D);  // Set DC-DC enable
    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x14);  // Set DC-DC enable (0x14)

    I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xAF);  // Display ON

    SSD1306_Clear();

    SSD1306_Update(bus);

}

void SSD1306_Update(uint8_t bus){
    for (uint8_t page = 0; page < 8; page++){
        I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0xB0 + page);  // Set Page Start Address for Page Addressing Mode
        I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x00);         // Set low column address
        I2C_Write(bus, SSD1306_ADDR, SSD1306_CTRL_CMD, 0x10);         // Set high column address
        I2C_WriteBuffer(bus, SSD1306_ADDR, SSD1306_CTRL_DATA, &display[128*page], 128);
    }

}

void SSD1306_Fill(void){
    for (uint16_t a = 0; a < 1024; a++){
        display[a] = 0xFF;
    }
}

void SSD1306_Clear(void){
    for (uint16_t a = 0; a < 1024; a++){
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

void SSD1306_CheckerBoard(uint8_t size){
    for(uint8_t y = 0; y < 64; y++)
    {
        for(uint8_t x = 0; x < 128; x++)
        {
            uint8_t pixel = ((x / size) + (y / size)) & 1;

            uint16_t index = (y >> 3) * 128 + x;
            uint8_t bit = y & 7;

            if(pixel)
                display[index] |= (1 << bit);
            else
                display[index] &= ~(1 << bit);
        }
    }
}

//----------------------------------End of File