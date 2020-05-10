/**********************************************************

	Top-level header file for LCD utils library
	
	
**********************************************************/

#ifndef __LCD_LIB_H_
#define __LCD_LIB_H_

#include "stdint.h"
#include "lcd_font_typedef.h"
#include "lcd_lib_config.h"

// Typedefs
typedef struct {
    int16_t x1;
    int16_t y1;
    int16_t x2;
    int16_t y2;
} rect_t;

typedef struct {
    int16_t x;
    int16_t y;
} point_t;

typedef struct {
    color_t color;
    uint8_t mode;
} lcd_pen_t;


/*------- Obsolete --------//
// Pixel output modes
#define PIXEL_MODE_REWRITE  0x00
#define PIXEL_MODE_AND      0x01
#define PIXEL_MODE_OR       0x02
#define PIXEL_MODE_XOR      0x03

// Image output modes
#define IMAGE_MODE_NORMAL    0x01
#define IMAGE_MODE_INVERSE   0x00

// Aliases for fill rect
#define FILL_WITH_BLACK      0x01
#define FILL_WITH_WHITE      0x00

#define LCD_FillRect(x_pos, y_pos, width, height, mode) \
    LCD_DrawImage(0, x_pos, y_pos, width, height, mode)
//-------------------------*/

// Pen modes. If a pen is transparent, no pixels will be output with that pen.
#define PEN_TRANSPARENT 0
#define PEN_SOLID       1

// Align modes - required alignment mode is selected by
// combining these flags
#define ALIGN_CENTER    0x00
#define ALIGN_LEFT      0x01
#define ALIGN_RIGHT     0x02
#define ALIGN_TOP       0x04
#define ALIGN_BOTTOM    0x08
// Aliases
#define ALIGN_TOP_LEFT      (ALIGN_TOP | ALIGN_LEFT)
#define ALIGN_BOTTOM_LEFT   (ALIGN_BOTTOM | ALIGN_LEFT)
#define ALIGN_TOP_RIGHT     (ALIGN_TOP | ALIGN_RIGHT)
#define ALIGN_BOTTOM_RIGHT   (ALIGN_BOTTOM | ALIGN_RIGHT)

// Line drawing mode (not for all functions)
#define LINE_STYLE_SOLID      0x10
#define LINE_STYLE_DASHED     0x20
#define LINE_STYLE_DOTTED     0x30




// Some common colors
#define CL_BLACK 		colorFromRgb (0,	0,		0)
#define CL_BLUE 		colorFromRgb (0,	0,		255)
#define CL_GREEN 		colorFromRgb (0,	255,	0)
#define CL_CYAN 		colorFromRgb (0,	255,	255)
#define CL_RED 			colorFromRgb (255,	0,		0)
#define CL_MAGENTA 		colorFromRgb (255,	0,		255)
#define CL_YELLOW 		colorFromRgb (255,	255,	0)
#define CL_WHITE 		colorFromRgb (255,	255,	255)
#define CL_LIGHT_GREY 	colorFromRgb (200,	200,	200)
#define CL_DARK_GREY 	colorFromRgb (80,	80,		80)


// lcdBuffer should be defined in config.h as an external buffer
// Type of data in the buffer is platform-specific
#ifndef LCD_LIB_COLOR_MODE
#error "LCD_LIB_COLOR_MODE is not defined"
#endif


// Avaliable fonts (depending on actual files presence)
extern const tFont font_h12;
extern const tFont font_h32;
extern const tFont font_h10;
extern const tFont font_h10_bold;
extern const tFont font_6x8_mono;

// Prototypes
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
    
void LCD_SetPen(const uint8_t mode, const color_t newColor);
void LCD_SetPenColor(const color_t newColor);
void LCD_SetPenMode(const uint8_t mode);
void LCD_SetAltPen(const uint8_t mode, const color_t newColor);
void LCD_SetAltPenColor(const color_t newColor);
void LCD_SetAltPenMode(const uint8_t mode);
void LCD_SetFillColor(const color_t newColor);
void LCD_SetLineStyle(uint8_t newStyle);
void LCD_SetFont(const tFont *newFont);


void LCD_PutPixel(uint16_t x, uint16_t y, color_t color);
color_t LCD_GetPixel(uint16_t x, uint16_t y);
void LCD_DrawHorLine(uint16_t x, uint16_t y, uint16_t length);
void LCD_DrawVertLine(uint16_t x, uint16_t y, int16_t length);
void LCD_DrawRect(rect_t *rect);
void LCD_DrawRectP(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_DrawRectWH(uint16_t x, uint16_t y, int16_t width, int16_t height);
void LCD_FillRect(rect_t* rect);
void LCD_FillRectP(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_FillRectWH(uint16_t x, uint16_t y, int16_t width, int16_t height);
void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_DrawCircle(int16_t x0, int16_t y0, int16_t radius);
void LCD_DrawFilledCircle(int16_t x0, int16_t y0, int16_t radius);

void LCD_drawPackedImage(const uint8_t *img, int16_t x_pos, int16_t y_pos, uint16_t img_width, uint16_t img_height);
void LCD_PrintString(char *str, int16_t x, int16_t y);
void LCD_PrintStringAligned(char *str, rect_t *rect, uint8_t alignment);

#ifdef __cplusplus
}
#endif // __cplusplus




#endif //__LCD_LIB_H_
