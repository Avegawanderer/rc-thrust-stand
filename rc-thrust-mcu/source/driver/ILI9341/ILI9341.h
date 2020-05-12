//	MIT License
//
//	Copyright (c) 2020 Alexey Borozdin
//  Based on library by Matej Artnak, https://github.com/martnak/STM32-ILI9341
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.

#ifndef ILI9341_H
#define ILI9341_H

#include "stdint.h"
#include "global.h"

// Physical dimensions, disregarding rotation
#define ILI9341_SCREEN_HEIGHT       240
#define ILI9341_SCREEN_WIDTH        320

// Few standard colours
#define BLACK                       0x0000
#define NAVY                        0x000F
#define DARKGREEN                   0x03E0
#define DARKCYAN                    0x03EF
#define MAROON                      0x7800
#define PURPLE                      0x780F
#define OLIVE                       0x7BE0
#define LIGHTGREY                   0xC618
#define DARKGREY                    0x7BEF
#define BLUE                        0x001F
#define GREEN                       0x07E0
#define CYAN                        0x07FF
#define RED                         0xF800
#define MAGENTA                     0xF81F
#define YELLOW                      0xFFE0
#define WHITE                       0xFFFF
#define ORANGE                      0xFD20
#define GREENYELLOW                 0xAFE5
#define PINK                        0xF81F

// Rotation patterns
#define SCREEN_VERTICAL_1			0
#define SCREEN_HORIZONTAL_1         1
#define SCREEN_VERTICAL_2			2
#define SCREEN_HORIZONTAL_2         3


// Actual screen size depending on rotation
extern volatile uint16_t LCD_HEIGHT;
extern volatile uint16_t LCD_WIDTH;


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    //---------------------//
    // These platform-dependent function are external to library and must be implemented in a platform-specific driver file
    void ILI9341_SPI_Init(void);
    void ILI9341_SPI_Send(uint8_t data);
    void ILI9341_SPI_Write_Command(uint8_t command);
    void ILI9341_SPI_Write_Data(uint8_t data);
    void ILI9341_SPI_Write_DataArray(uint8_t *data, uint32_t count);
    void ILI9341_Reset(void);

    //---------------------//
    // Interface
    void ILI9341_Init(uint8_t rotation);
    void ILI9341_Set_Rotation(uint8_t rotation);
    void ILI9341_Set_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    void ILI9341_Draw_Colour(uint16_t colour);
    void ILI9341_Draw_Colour_Burst(uint16_t colour, uint32_t size);
    void ILI9341_Fill_Screen(uint16_t colour);
    void ILI9341_Draw_Pixel(uint16_t x, uint16_t y, uint16_t colour);
    void ILI9341_Draw_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colour);
    void ILI9341_Draw_Horizontal_Line(uint16_t x, uint16_t y, uint16_t width, uint16_t colour);
    void ILI9341_Draw_Vertical_Line(uint16_t x, uint16_t y, uint16_t height, uint16_t colour);
	

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ILI9341_H

