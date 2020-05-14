#ifndef __LCD_CONFIG_H_
#define __LCD_CONFIG_H_

#include "stdint.h"
#include "lcd_font_typedef.h"

// Values are arbitrary
#define LCD_LIB_COLOR_RGB233	0
#define LCD_LIB_COLOR_RGB565	1
#define LCD_LIB_COLOR_RGB888	2


// Mandatory
#define LCD_LIB_COLOR_MODE	LCD_LIB_COLOR_RGB565


#if LCD_LIB_COLOR_MODE == LCD_LIB_COLOR_RGB888
	typedef uint32_t color_t;
	#define colorFromRgb(red, green, blue) ( (((uint32_t)red & 0xFF) << 16) | (((uint32_t)green & 0xFF) << 8) | (((uint32_t)blue & 0xFF) << 0))
#elif LCD_LIB_COLOR_MODE == LCD_LIB_COLOR_RGB565
	typedef uint16_t color_t;
	#define colorFromRgb(red, green, blue) ( (((red >> 3) & 0x1F)<<11) | (((green >> 2) & 0x3F) << 5) | ((blue >> 3) & 0x1F) )
#elif LCD_LIB_COLOR_MODE == LCD_LIB_COLOR_RGB233
	typedef uint8_t color_t;
	#define colorFromRgb(red, green, blue) ( (red & 0xC0) | ((green >> 2) & 0x38) | ((blue >> 6) & 0x7) )
#endif



// Dashed and dotted line style settings
// Counter increments from 0 to LCD_xxx_PERIOD-1
// if counter < LCD_xxx_COMPARE, pixel is put unchaged
// if counter >= LCD_xxx_COMPARE, pixel is put inversed
#define LCD_DOT_PERIOD      4
#define LCD_DOT_COMPARE     2
#define LCD_DASH_PERIOD     7
#define LCD_DASH_COMPARE    5



// Default functions for LCD library
#define LcdLibConfig_UseDefaultPutPixel			0
#define LcdLibConfig_UseDefaultGetPixel			0
#define LcdLibConfig_UseDefaultDrawHorLine		1
#define LcdLibConfig_UseDefaultDrawVertLine		1
#define LcdLibConfig_UseDefaultDrawRectP		1
#define LcdLibConfig_UseDefaultFillRectP		0
#define LcdLibConfig_UseDefaultDrawPackedImage  0


// Screen size definitions in pixels
#define LCD_XSIZE 320
#define LCD_YSIZE 240


// Buffer
#define lcdBuffer guiLcdBuffer
extern uint32_t guiLcdBuffer[];



#endif //__LCD_CONFIG_H_
