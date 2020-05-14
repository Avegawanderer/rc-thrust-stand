

#include "lcd_lib.h"
#include "lcd_lib_private.h"
#include "ILI9341.h"
#include "ILI9341_STM32_SPI.h"


#if LcdLibConfig_UseDefaultPutPixel == 0
void LCD_PutPixel(uint16_t x, uint16_t y, color_t color)
{
	ILI9341_Draw_Pixel(x, y, color);
}
#endif


//-------------------------------------------------------//
// Fills a rectangle with fillColor
//
//  Rectangle is specified by 2 points
//-------------------------------------------------------//
#if LcdLibConfig_UseDefaultFillRectP == 0
void LCD_FillRectP(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    ILI9341_Fill_Rectangle(x1, y1, x2 - x1, y2 - y1, fillColor);
}
#endif


//-------------------------------------------------------//
// Draws B/W packed image, coordinates are absolute.
// Image is printed using:
//  - penColor
//  - altPenColor
//  - imageOutputMode
//-------------------------------------------------------//
#if LcdLibConfig_UseDefaultDrawPackedImage == 0
void LCD_drawPackedImage(const uint8_t *img, int16_t x_pos, int16_t y_pos, uint16_t img_width, uint16_t img_height)
{
    uint8_t bit_mask = 0x01;
    uint8_t temp;
    uint16_t img_index;
    uint16_t img_start_index = 0;
    int16_t x;
    int16_t y_fin = y_pos + img_height;
    uint8_t penColorBuffer[2] = {pen.color >> 8, pen.color};
    uint8_t altPenColorBuffer[2] = {altPen.color >> 8, altPen.color};

    ILI9341_Set_Address(x_pos, y_pos, x_pos + img_width - 1, y_pos + img_height - 1);
    ILI9341_SPI_SelectData();

    while(y_pos < y_fin)
    {
        img_index = img_start_index;
        for (x = x_pos; x < x_pos + img_width; x++)
        {
            temp = img[img_index++];
            if (temp & bit_mask)
            {
                // Would require reading of pixels
                //if (pen.mode == PEN_SOLID)
                {
                    ILI9341_SPI_SendRaw(penColorBuffer, 2);
                }
            }
            else //if (altPen.mode == PEN_SOLID)
            {
                ILI9341_SPI_SendRaw(altPenColorBuffer, 2);
            }
        }
        y_pos++;
        if (bit_mask == 0x80)
        {
            bit_mask = 0x01;
            img_start_index += img_width;
        }
        else
        {
            bit_mask = bit_mask << 1;
        }
    }
    ILI9341_SPI_Deselect();
}
#endif //LcdLibConfig_UseDefaultDrawPackedImage






