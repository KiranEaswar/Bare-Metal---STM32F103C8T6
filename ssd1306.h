//----------------------------------Description
// @file    ssd1306.h
// @author  Kiran
// @desc    Header for the SSD1306 OLED Driver

//----------------------------------Instance Declaration
#ifndef SSD1306_H
#define SSD1306_H

//----------------------------------Libraries
#include <stdint.h>

//----------------------------------Defines
#define SSD1306_ADDR   0x3C
#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT 64
#define SSD1306_BUS    1

//----------------------------------Framebuffer
extern uint8_t ssd1306_fb[1024];

//----------------------------------Function Declarations
void SSD1306_Init(void);
void SSD1306_Clear(void);
void SSD1306_Fill(void);
void SSD1306_Update(void);
void SSD1306_SetPixel(uint8_t x, uint8_t y, uint8_t val);

//----------------------------------End of Header
#endif