//	MIT License
//
//	Copyright (c) 2020 Alexey Borozdin
//  Base on library by Matej Artnak, https://github.com/martnak/STM32-ILI9341
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
#include "ILI9341_STM32_Driver.h"



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

volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;

//----------- Externals ------------//
//----------- Prototypes -----------//


//--------- Implementation ---------//


// Initialize SPI
void ILI9341_SPI_Init(void)
{
    // It is assumed that SPI module and GPIO are initialized already
    //MX_SPI1_Init();
    //MX_GPIO_Init();
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	//CS OFF
}


// Send data (char) to LCD
void ILI9341_SPI_Send(uint8_t data)
{
    HAL_SPI_Transmit(HSPI_INSTANCE, &data, 1, 1);
}


// Send command (single char) to LCD
void ILI9341_Write_Command(uint8_t command)
{
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(HSPI_INSTANCE, &command, 1, 1);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}


// Send Data (single char) to LCD
void ILI9341_Write_Data(uint8_t data)
{
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(HSPI_INSTANCE, &data, 1, 1);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}


// Send Data (array) to LCD
void ILI9341_Write_DataArray(uint8_t *data, uint32_t count)
{
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(HSPI_INSTANCE, data, count, 10);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}


// Set Address - Location block - to draw into
void ILI9341_Set_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    ILI9341_Write_Command(0x2A);
    ILI9341_Write_Data(x1 >> 8);
    ILI9341_Write_Data(x1);
    ILI9341_Write_Data(x2 >> 8);
    ILI9341_Write_Data(x2);

    ILI9341_Write_Command(0x2B);
    ILI9341_Write_Data(y1 >> 8);
    ILI9341_Write_Data(y1);
    ILI9341_Write_Data(y2 >> 8);
    ILI9341_Write_Data(y2);

    ILI9341_Write_Command(0x2C);
}


// HARDWARE RESET
void ILI9341_Reset(void)
{
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}


/*Ser rotation of the screen - changes x0 and y0*/
void ILI9341_Set_Rotation(uint8_t Rotation) 
{	
    uint8_t screen_rotation = Rotation;
    ILI9341_Write_Command(0x36);
    HAL_Delay(1);
    switch(screen_rotation)
	{
		case SCREEN_VERTICAL_1:
			ILI9341_Write_Data(0x40|0x08);
			LCD_WIDTH = 240;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_HORIZONTAL_1:
			ILI9341_Write_Data(0x20|0x08);
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 240;
			break;
		case SCREEN_VERTICAL_2:
			ILI9341_Write_Data(0x80|0x08);
			LCD_WIDTH  = 240;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_HORIZONTAL_2:
			ILI9341_Write_Data(0x40|0x80|0x20|0x08);
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 240;
			break;
		default:
			//EXIT IF SCREEN ROTATION NOT VALID!
			break;
	}
}

// Enable LCD display
void ILI9341_Enable(void)
{
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}

// Initialize LCD display
void ILI9341_Init(void)
{
    ILI9341_Enable();
    ILI9341_SPI_Init();
    ILI9341_Reset();

    //SOFTWARE RESET
    ILI9341_Write_Command(0x01);
    HAL_Delay(100);

    //POWER CONTROL A
    ILI9341_Write_Command(0xCB);
    ILI9341_Write_Data(0x39);
    ILI9341_Write_Data(0x2C);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x34);
    ILI9341_Write_Data(0x02);

    //POWER CONTROL B
    ILI9341_Write_Command(0xCF);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0xC1);
    ILI9341_Write_Data(0x30);

    //DRIVER TIMING CONTROL A
    ILI9341_Write_Command(0xE8);
    ILI9341_Write_Data(0x85);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x78);

    //DRIVER TIMING CONTROL B
    ILI9341_Write_Command(0xEA);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x00);

    //POWER ON SEQUENCE CONTROL
    ILI9341_Write_Command(0xED);
    ILI9341_Write_Data(0x64);
    ILI9341_Write_Data(0x03);
    ILI9341_Write_Data(0x12);
    ILI9341_Write_Data(0x81);

    //PUMP RATIO CONTROL
    ILI9341_Write_Command(0xF7);
    ILI9341_Write_Data(0x20);

    //POWER CONTROL,VRH[5:0]
    ILI9341_Write_Command(0xC0);
    ILI9341_Write_Data(0x23);

    //POWER CONTROL,SAP[2:0];BT[3:0]
    ILI9341_Write_Command(0xC1);
    ILI9341_Write_Data(0x10);

    //VCM CONTROL
    ILI9341_Write_Command(0xC5);
    ILI9341_Write_Data(0x3E);
    ILI9341_Write_Data(0x28);

    //VCM CONTROL 2
    ILI9341_Write_Command(0xC7);
    ILI9341_Write_Data(0x86);

    //MEMORY ACCESS CONTROL
    ILI9341_Write_Command(0x36);
    ILI9341_Write_Data(0x48);

    //PIXEL FORMAT
    ILI9341_Write_Command(0x3A);
    ILI9341_Write_Data(0x55);

    //FRAME RATIO CONTROL, STANDARD RGB COLOR
    ILI9341_Write_Command(0xB1);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x18);

    //DISPLAY FUNCTION CONTROL
    ILI9341_Write_Command(0xB6);
    ILI9341_Write_Data(0x08);
    ILI9341_Write_Data(0x82);
    ILI9341_Write_Data(0x27);

    //3GAMMA FUNCTION DISABLE
    ILI9341_Write_Command(0xF2);
    ILI9341_Write_Data(0x00);

    //GAMMA CURVE SELECTED
    ILI9341_Write_Command(0x26);
    ILI9341_Write_Data(0x01);

    //POSITIVE GAMMA CORRECTION
    ILI9341_Write_Command(0xE0);
    ILI9341_Write_Data(0x0F);
    ILI9341_Write_Data(0x31);
    ILI9341_Write_Data(0x2B);
    ILI9341_Write_Data(0x0C);
    ILI9341_Write_Data(0x0E);
    ILI9341_Write_Data(0x08);
    ILI9341_Write_Data(0x4E);
    ILI9341_Write_Data(0xF1);
    ILI9341_Write_Data(0x37);
    ILI9341_Write_Data(0x07);
    ILI9341_Write_Data(0x10);
    ILI9341_Write_Data(0x03);
    ILI9341_Write_Data(0x0E);
    ILI9341_Write_Data(0x09);
    ILI9341_Write_Data(0x00);

    //NEGATIVE GAMMA CORRECTION
    ILI9341_Write_Command(0xE1);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x0E);
    ILI9341_Write_Data(0x14);
    ILI9341_Write_Data(0x03);
    ILI9341_Write_Data(0x11);
    ILI9341_Write_Data(0x07);
    ILI9341_Write_Data(0x31);
    ILI9341_Write_Data(0xC1);
    ILI9341_Write_Data(0x48);
    ILI9341_Write_Data(0x08);
    ILI9341_Write_Data(0x0F);
    ILI9341_Write_Data(0x0C);
    ILI9341_Write_Data(0x31);
    ILI9341_Write_Data(0x36);
    ILI9341_Write_Data(0x0F);

    //EXIT SLEEP
    ILI9341_Write_Command(0x11);
    HAL_Delay(120);

    //TURN ON DISPLAY
    ILI9341_Write_Command(0x29);

    //STARTING ROTATION
    ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
}


// INTERNAL FUNCTION OF LIBRARY, USAGE NOT RECOMENDED, USE Draw_Pixel INSTEAD
// Sends single pixel colour information to LCD
void ILI9341_Draw_Colour(uint16_t colour)
{
    uint8_t TempBuffer[2] = {colour>>8, colour};
//    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
//    HAL_SPI_Transmit(HSPI_INSTANCE, TempBuffer, 2, 1);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    ILI9341_Write_DataArray(TempBuffer, 2);
}


// INTERNAL FUNCTION OF LIBRARY
// Sends block colour information to LCD
void ILI9341_Draw_Colour_Burst(uint16_t colour, uint32_t size)
{
    uint8_t burst_buffer[2 * BURST_MAX_SIZE];
    uint32_t burst_size;
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
 
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
        HAL_SPI_Transmit(HSPI_INSTANCE, burst_buffer, burst_size * 2, 10);
        size -= burst_size;
    }
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}


//FILL THE ENTIRE SCREEN WITH SELECTED COLOUR (either #define-d ones or custom 16bit)
// Sets address (entire screen) and Sends Height*Width ammount of colour information to LCD
void ILI9341_Fill_Screen(uint16_t colour)
{
    ILI9341_Set_Address(0, 0, LCD_WIDTH, LCD_HEIGHT);
    ILI9341_Draw_Colour_Burst(colour, LCD_WIDTH * LCD_HEIGHT);
}


//DRAW PIXEL AT XY POSITION WITH SELECTED COLOUR
//
//Location is dependant on screen orientation. x0 and y0 locations change with orientations.
//Using pixels to draw big simple structures is not recommended as it is really slow
//Try using either rectangles or lines if possible
//
void ILI9341_Draw_Pixel(uint16_t x, uint16_t y, uint16_t colour)
{
    if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;	//OUT OF BOUNDS!
	
    //ADDRESS
//    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
//    ILI9341_SPI_Send(0x2A);
//    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    ILI9341_Write_Command(0x2A);

    //XDATA
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    unsigned char Temp_Buffer[4] = {x>>8,x, (x+1)>>8, (x+1)};
//    HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer, 4, 1);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    ILI9341_Write_DataArray(Temp_Buffer, 4);


    //ADDRESS
//    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
//    ILI9341_SPI_Send(0x2B);
//    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    ILI9341_Write_Command(0x2B);

    //YDATA
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    unsigned char Temp_Buffer1[4] = {y>>8,y, (y+1)>>8, (y+1)};
//    HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer1, 4, 1);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    ILI9341_Write_DataArray(Temp_Buffer1, 4);

    //ADDRESS
//    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
//    ILI9341_SPI_Send(0x2C);
//    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    ILI9341_Write_Command(0x2C);

    //COLOUR
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    unsigned char Temp_Buffer2[2] = {colour>>8, colour};
//    HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer2, 2, 1);
//    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    ILI9341_Write_DataArray(Temp_Buffer2, 2);
}


//DRAW RECTANGLE OF SET SIZE AND HEIGTH AT X and Y POSITION WITH CUSTOM COLOUR
//
//Rectangle is hollow. X and Y positions mark the upper left corner of rectangle
//As with all other draw calls x0 and y0 locations dependant on screen orientation
//
void ILI9341_Draw_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colour)
{
    if ((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;
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


//DRAW LINE FROM X,Y LOCATION to X+Width,Y LOCATION
void ILI9341_Draw_Horizontal_Line(uint16_t x, uint16_t y, uint16_t width, uint16_t Colour)
{
    if ((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;
    if ((x + width - 1) >= LCD_WIDTH)
	{
        width = LCD_WIDTH - x;
	}
    ILI9341_Set_Address(x, y, x + width - 1, y);
    ILI9341_Draw_Colour_Burst(Colour, width);
}


//DRAW LINE FROM X,Y LOCATION to X,Y+Height LOCATION
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

