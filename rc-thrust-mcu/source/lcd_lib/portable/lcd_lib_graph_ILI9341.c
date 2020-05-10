

#include "lcd_lib.h"
#include "lcd_lib_private.h"
#include "ILI9341.h"



#if LcdLibConfig_UseDefaultPutPixel == 0


void LCD_PutPixel(uint16_t x, uint16_t y, color_t color)
{
	ILI9341_Draw_Pixel(x, y, color);
}

#endif






