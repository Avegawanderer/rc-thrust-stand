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


#include "stm32f1xx_hal.h"
#include "ILI9341.h"
#include "ILI9341_STM32_SPI.h"

//----------- Definitions ----------//

// Burst size does not make much difference since SPI is driven by core
// It is OK to have burst size ~twice the SPI FIFO size
#define BURST_MAX_SIZE 	16

//----------- Variables ------------//

volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;

//----------- Externals ------------//
//----------- Prototypes -----------//


//--------- Implementation ---------//

// Send command (single char) to LCD
static void ILI9341_SPI_Write_Command(uint8_t command)
{
    ILI9341_SPI_SelectCommand();
    ILI9341_SPI_SendRaw(&command, 1);
    ILI9341_SPI_Deselect();
}


// Send Data (single char) to LCD
static void ILI9341_SPI_Write_Data(uint8_t data)
{
    ILI9341_SPI_SelectData();
    ILI9341_SPI_SendRaw(&data, 1);
    ILI9341_SPI_Deselect();
}


// Send Data (array) to LCD
static void ILI9341_SPI_Write_DataArray(uint8_t *data, uint32_t count)
{
    ILI9341_SPI_SelectData();
    ILI9341_SPI_SendRaw(data, count);
    ILI9341_SPI_Deselect();
}


// Initialize LCD display
void ILI9341_Init(uint8_t rotation)
{
    ILI9341_SPI_Init();
    ILI9341_HwReset();

    //SOFTWARE RESET
    ILI9341_SPI_Write_Command(0x01);
    ILI9341_DelayMs(100);

    //POWER CONTROL A
    ILI9341_SPI_Write_Command(0xCB);
    ILI9341_SPI_Write_Data(0x39);
    ILI9341_SPI_Write_Data(0x2C);
    ILI9341_SPI_Write_Data(0x00);
    ILI9341_SPI_Write_Data(0x34);
    ILI9341_SPI_Write_Data(0x02);

    //POWER CONTROL B
    ILI9341_SPI_Write_Command(0xCF);
    ILI9341_SPI_Write_Data(0x00);
    ILI9341_SPI_Write_Data(0xC1);
    ILI9341_SPI_Write_Data(0x30);

    //DRIVER TIMING CONTROL A
    ILI9341_SPI_Write_Command(0xE8);
    ILI9341_SPI_Write_Data(0x85);
    ILI9341_SPI_Write_Data(0x00);
    ILI9341_SPI_Write_Data(0x78);

    //DRIVER TIMING CONTROL B
    ILI9341_SPI_Write_Command(0xEA);
    ILI9341_SPI_Write_Data(0x00);
    ILI9341_SPI_Write_Data(0x00);

    //POWER ON SEQUENCE CONTROL
    ILI9341_SPI_Write_Command(0xED);
    ILI9341_SPI_Write_Data(0x64);
    ILI9341_SPI_Write_Data(0x03);
    ILI9341_SPI_Write_Data(0x12);
    ILI9341_SPI_Write_Data(0x81);

    //PUMP RATIO CONTROL
    ILI9341_SPI_Write_Command(0xF7);
    ILI9341_SPI_Write_Data(0x20);

    //POWER CONTROL,VRH[5:0]
    ILI9341_SPI_Write_Command(0xC0);
    ILI9341_SPI_Write_Data(0x23);

    //POWER CONTROL,SAP[2:0];BT[3:0]
    ILI9341_SPI_Write_Command(0xC1);
    ILI9341_SPI_Write_Data(0x10);

    //VCM CONTROL
    ILI9341_SPI_Write_Command(0xC5);
    ILI9341_SPI_Write_Data(0x3E);
    ILI9341_SPI_Write_Data(0x28);

    //VCM CONTROL 2
    ILI9341_SPI_Write_Command(0xC7);
    ILI9341_SPI_Write_Data(0x86);

    //MEMORY ACCESS CONTROL
    ILI9341_SPI_Write_Command(0x36);
    ILI9341_SPI_Write_Data(0x48);

    //PIXEL FORMAT
    ILI9341_SPI_Write_Command(0x3A);
    ILI9341_SPI_Write_Data(0x55);

    //FRAME RATIO CONTROL, STANDARD RGB COLOR
    ILI9341_SPI_Write_Command(0xB1);
    ILI9341_SPI_Write_Data(0x00);
    ILI9341_SPI_Write_Data(0x18);

    //DISPLAY FUNCTION CONTROL
    ILI9341_SPI_Write_Command(0xB6);
    ILI9341_SPI_Write_Data(0x08);
    ILI9341_SPI_Write_Data(0x82);
    ILI9341_SPI_Write_Data(0x27);

    //3GAMMA FUNCTION DISABLE
    ILI9341_SPI_Write_Command(0xF2);
    ILI9341_SPI_Write_Data(0x00);

    //GAMMA CURVE SELECTED
    ILI9341_SPI_Write_Command(0x26);
    ILI9341_SPI_Write_Data(0x01);

    //POSITIVE GAMMA CORRECTION
    ILI9341_SPI_Write_Command(0xE0);
    ILI9341_SPI_Write_Data(0x0F);
    ILI9341_SPI_Write_Data(0x31);
    ILI9341_SPI_Write_Data(0x2B);
    ILI9341_SPI_Write_Data(0x0C);
    ILI9341_SPI_Write_Data(0x0E);
    ILI9341_SPI_Write_Data(0x08);
    ILI9341_SPI_Write_Data(0x4E);
    ILI9341_SPI_Write_Data(0xF1);
    ILI9341_SPI_Write_Data(0x37);
    ILI9341_SPI_Write_Data(0x07);
    ILI9341_SPI_Write_Data(0x10);
    ILI9341_SPI_Write_Data(0x03);
    ILI9341_SPI_Write_Data(0x0E);
    ILI9341_SPI_Write_Data(0x09);
    ILI9341_SPI_Write_Data(0x00);

    //NEGATIVE GAMMA CORRECTION
    ILI9341_SPI_Write_Command(0xE1);
    ILI9341_SPI_Write_Data(0x00);
    ILI9341_SPI_Write_Data(0x0E);
    ILI9341_SPI_Write_Data(0x14);
    ILI9341_SPI_Write_Data(0x03);
    ILI9341_SPI_Write_Data(0x11);
    ILI9341_SPI_Write_Data(0x07);
    ILI9341_SPI_Write_Data(0x31);
    ILI9341_SPI_Write_Data(0xC1);
    ILI9341_SPI_Write_Data(0x48);
    ILI9341_SPI_Write_Data(0x08);
    ILI9341_SPI_Write_Data(0x0F);
    ILI9341_SPI_Write_Data(0x0C);
    ILI9341_SPI_Write_Data(0x31);
    ILI9341_SPI_Write_Data(0x36);
    ILI9341_SPI_Write_Data(0x0F);

    //EXIT SLEEP
    ILI9341_SPI_Write_Command(0x11);
    ILI9341_DelayMs(120);

    //TURN ON DISPLAY
    ILI9341_SPI_Write_Command(0x29);

    //STARTING ROTATION
    ILI9341_Set_Rotation(rotation);
}


// Set rotation of the screen - changes x0 and y0
void ILI9341_Set_Rotation(uint8_t rotation)
{
    uint8_t screen_rotation = rotation;
    ILI9341_SPI_Write_Command(0x36);
    ILI9341_DelayMs(1);
    switch(screen_rotation)
    {
        case SCREEN_VERTICAL_1:
            ILI9341_SPI_Write_Data(0x40|0x08);
            LCD_WIDTH = 240;
            LCD_HEIGHT = 320;
            break;
        case SCREEN_HORIZONTAL_1:
            ILI9341_SPI_Write_Data(0x20|0x08);
            LCD_WIDTH  = 320;
            LCD_HEIGHT = 240;
            break;
        case SCREEN_VERTICAL_2:
            ILI9341_SPI_Write_Data(0x80|0x08);
            LCD_WIDTH  = 240;
            LCD_HEIGHT = 320;
            break;
        case SCREEN_HORIZONTAL_2:
            ILI9341_SPI_Write_Data(0x40|0x80|0x20|0x08);
            LCD_WIDTH  = 320;
            LCD_HEIGHT = 240;
            break;
        default:
            //EXIT IF SCREEN ROTATION NOT VALID!
            break;
    }
}


// Set Address - Location block - to draw into
void ILI9341_Set_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    ILI9341_SPI_Write_Command(0x2A);
    ILI9341_SPI_Write_Data(x1 >> 8);
    ILI9341_SPI_Write_Data(x1);
    ILI9341_SPI_Write_Data(x2 >> 8);
    ILI9341_SPI_Write_Data(x2);
    ILI9341_SPI_Write_Command(0x2B);
    ILI9341_SPI_Write_Data(y1 >> 8);
    ILI9341_SPI_Write_Data(y1);
    ILI9341_SPI_Write_Data(y2 >> 8);
    ILI9341_SPI_Write_Data(y2);
    ILI9341_SPI_Write_Command(0x2C);
}


// Sends block of colour information to LCD
// Address must be previously setup by ILI9341_Set_Address()
void ILI9341_Draw_Colour_Burst(uint16_t colour, uint32_t size)
{
    uint8_t burst_buffer[2 * BURST_MAX_SIZE];
    uint32_t burst_size;
    ILI9341_SPI_SelectData();
 
    // Fill the buffer
    burst_size = (size < BURST_MAX_SIZE) ? size : BURST_MAX_SIZE;
    for(uint32_t j = 0; j < burst_size * 2; j+=2)
    {
        burst_buffer[j] = colour >> 8;
        burst_buffer[j+1] = colour;
    }
    while (size)
    {
        burst_size = (size < BURST_MAX_SIZE) ? size : BURST_MAX_SIZE;
        ILI9341_SPI_SendRaw(burst_buffer, burst_size * 2);
        size -= burst_size;
    }
    ILI9341_SPI_Deselect();
}


// Put a pixel at selected location
// Quite slow method, consider filling big areas instead (to reduce overhead of address setup)
void ILI9341_Draw_Pixel(uint16_t x, uint16_t y, uint16_t colour)
{
    if ((x >=LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    ILI9341_Set_Address(x, y, x + 1, y + 1);
    unsigned char Temp_Buffer2[2] = {colour >> 8, colour};
    ILI9341_SPI_Write_DataArray(Temp_Buffer2, 2);
}


// Fill whole screen with specified color
void ILI9341_Fill_Screen(uint16_t colour)
{
    ILI9341_Set_Address(0, 0, LCD_WIDTH, LCD_HEIGHT);
    ILI9341_Draw_Colour_Burst(colour, LCD_WIDTH * LCD_HEIGHT);
}


// Fill a rectangle with specified color
void ILI9341_Fill_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colour)
{
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((x + width - 1) >= LCD_WIDTH)
	{
        width = LCD_WIDTH - x;
	}
    if ((y + height - 1) >= LCD_HEIGHT)
    {
        height = LCD_HEIGHT - y;
	}
    ILI9341_Set_Address(x, y, x + width - 1, y + height - 1);
    ILI9341_Draw_Colour_Burst(colour, height * width);
}


// Draw line (fast)
void ILI9341_Draw_Horizontal_Line(uint16_t x, uint16_t y, uint16_t width, uint16_t Colour)
{
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((x + width - 1) >= LCD_WIDTH)
	{
        width = LCD_WIDTH - x;
	}
    ILI9341_Set_Address(x, y, x + width - 1, y);
    ILI9341_Draw_Colour_Burst(Colour, width);
}


// Draw line (fast)
void ILI9341_Draw_Vertical_Line(uint16_t x, uint16_t y, uint16_t height, uint16_t colour)
{
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((y + height - 1) >= LCD_HEIGHT)
	{
        height = LCD_HEIGHT - y;
	}
    ILI9341_Set_Address(x, y, x, y + height - 1);
    ILI9341_Draw_Colour_Burst(colour, height);
}

