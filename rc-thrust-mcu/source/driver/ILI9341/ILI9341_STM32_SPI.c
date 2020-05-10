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
#include "ILI9341_STM32_SPI.h"


//----------- Definitions ----------//

// SPI INSTANCE
extern SPI_HandleTypeDef hspi1;
#define HSPI_INSTANCE							&hspi1

// CHIP SELECT PIN AND PORT, STANDARD GPIO
#define LCD_CS_PORT								GPIOA
#define LCD_CS_PIN								GPIO_PIN_4

// DATA COMMAND PIN AND PORT, STANDARD GPIO
#define LCD_DC_PORT								GPIOA
#define LCD_DC_PIN								GPIO_PIN_3

// RESET PIN AND PORT, STANDARD GPIO
#define	LCD_RST_PORT							GPIOA
#define	LCD_RST_PIN								GPIO_PIN_2

//----------- Variables ------------//
//----------- Externals ------------//
//----------- Prototypes -----------//
//--------- Implementation ---------//


// Initialize SPI
void ILI9341_SPI_Init(void)
{
    // It is assumed that SPI module and GPIO are initialized already
    //MX_SPI1_Init();
    //MX_GPIO_Init();
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
}


void ILI9341_SPI_SelectData(void)
{
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
}


void ILI9341_SPI_SelectCommand(void)
{
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
}


void ILI9341_SPI_Deselect(void)
{
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}


void ILI9341_SPI_SendRaw(uint8_t *data, uint32_t count)
{
    HAL_SPI_Transmit(HSPI_INSTANCE, data, count, 10);
}


void ILI9341_HwReset(void)
{
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(100);
}


void ILI9341_DelayMs(uint32_t ms)
{
    HAL_Delay(ms);
}
