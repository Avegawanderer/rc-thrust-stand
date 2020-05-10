/**********************************************************

**********************************************************/


#ifndef __LCD_LIB_PRIVATE_H_
#define __LCD_LIB_PRIVATE_H_

#include "stdint.h"
#include "lcd_lib.h"

extern color_t fillColor;            // Used for filling objects
extern lcd_pen_t pen;               // Pen is used for drawing lines, frames, circles, etc
extern lcd_pen_t altPen;
extern const tFont* currentFont;     // Font that is currently used
extern uint8_t fontOutputMode;       // Specifies text background print mode
extern uint8_t imageOutputMode;
extern uint8_t pixelOutputMode;
extern uint8_t lineStyle;

#endif //__LCD_LIB_PRIVATE_H_
