
#include "lcd_lib.h"
#include "lcd_lib_private.h"


lcd_pen_t pen;                  // Pen is used for drawing lines, frames, circles, etc
lcd_pen_t altPen;
color_t fillColor;              // Used for filling objects
uint8_t lineStyle;
const tFont* currentFont;       // Font that currently used



//-------------------------------------------------------//
// Sets pen mode and color
//-------------------------------------------------------//
void LCD_SetPen(const uint8_t mode, const color_t newColor)
{
    pen.color = newColor;
    pen.mode = mode;
}


//-------------------------------------------------------//
// Sets pen color
//-------------------------------------------------------//
void LCD_SetPenColor(const color_t newColor)
{
    pen.color = newColor;
}


//-------------------------------------------------------//
// Sets pen mode
//-------------------------------------------------------//
void LCD_SetPenMode(const uint8_t mode)
{
    pen.mode = mode;
}


//-------------------------------------------------------//
// Sets alternate pen mode and color
//-------------------------------------------------------//
void LCD_SetAltPen(const uint8_t mode, const color_t newColor)
{
    altPen.color = newColor;
    altPen.mode = mode;
}


//-------------------------------------------------------//
// Sets alternate pen color
//-------------------------------------------------------//
void LCD_SetAltPenColor(const color_t newColor)
{
    altPen.color = newColor;
}


//-------------------------------------------------------//
// Sets alternate pen mode
//-------------------------------------------------------//
void LCD_SetAltPenMode(const uint8_t mode)
{
    altPen.mode = mode;
}

//-------------------------------------------------------//
// Sets filling color
//-------------------------------------------------------//
void LCD_SetFillColor(const color_t newColor)
{
    fillColor = newColor;
}


//-------------------------------------------------------//
// Sets line style
//-------------------------------------------------------//
void LCD_SetLineStyle(uint8_t newStyle)
{
    lineStyle = newStyle;
}


//-------------------------------------------------------//
// Sets current font for text printing
//-------------------------------------------------------//
void LCD_SetFont(const tFont *newFont)
{
    currentFont = newFont;
}

