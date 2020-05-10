//=======================================================//
//  FONTS
//
//=======================================================//


#include "lcd_lib.h"
#include "lcd_lib_private.h"



//-------------------------------------------------------//
// Rerurns width and offset of a font item
// Font array MUST be sorted by code.
// If no item with such code is found, 0 is returned.
// Using binary search, http://kvodo.ru/dvoichnyiy-poisk.html
//-------------------------------------------------------//
uint8_t LCD_GetFontItem(const tFont *font, uint8_t code, uint8_t *width, uint16_t *offset)
{
    uint8_t itemCode;
    uint8_t start_index = 0;
    uint8_t end_index;
    uint8_t i;

    if (font->codeTable == 0)
    {
        // Font char set is a contiguous array
        start_index = font->firstCharCode;
        end_index = start_index + (font->charCount - 1);
        if ((code < start_index) || (code > end_index))
            return 0;
        else
        {
            i = code-start_index;
            if (offset != 0)
            {
                if (font->offsetTable == 0)
                    *offset = (uint16_t)i * font->bytesPerChar;
                else
                    *offset = font->offsetTable[i];
            }
            if (font->widthTable == 0)
                *width = font->width;
            else
                *width = font->widthTable[i];
            return 1;
        }
    }
    else
    {
        end_index = font->charCount;
        // Font char set is defined by charTable
        while (start_index < end_index)
        {
            i = start_index + (end_index - start_index) / 2;
            itemCode = font->codeTable[i];
            if (code < itemCode)
                end_index = i;
            else if (code > itemCode)
                start_index = i+1;
            else
            {
                // Found
                if (offset != 0)
                    // Font must have valid offsetTable when codeTable is used
                    *offset = font->offsetTable[i];
                if (font->widthTable == 0)
                    *width = font->width;
                else
                    *width = font->widthTable[i];
                return 1;
            }
        }
    }
    return 0;
}


//-------------------------------------------------------//
// Rerurns length of a string in pixels
//
//-------------------------------------------------------//
uint8_t LCD_GetStringWidth(const tFont *font, char *string)
{
    uint8_t length = 0;
    uint8_t index = 0;
    uint8_t charWidth;
    char c;

    while((c = string[index++]))
    {
        if (LCD_GetFontItem(currentFont, c, &charWidth, 0))
            length += charWidth + font->spacing;
    }

    length -= font->spacing;
    return length;
}


//-------------------------------------------------------//
// Prints a string with LCD_currentFont at current position
//
//-------------------------------------------------------//
void LCD_PrintString(char *str, int16_t x, int16_t y)
{
    uint8_t index = 0;
    uint8_t charWidth;
    uint16_t charOffset;
    char c;

    while((c = str[index++]))
    {
        if (LCD_GetFontItem(currentFont, c, &charWidth, &charOffset))
        {
            LCD_drawPackedImage(&currentFont->data[charOffset], x, y, charWidth, currentFont->height);
            x += charWidth + currentFont->spacing;
        }
    }
}


//-------------------------------------------------------//
// Prints a string with LCD_currentFont inside rectangle using
//  alignment
//-------------------------------------------------------//
void LCD_PrintStringAligned(char *str, rect_t *rect, uint8_t alignment)
{
    uint8_t index = 0;
    uint8_t charWidth;
    uint16_t charOffset;
    char c;
    int16_t x_aligned, y_aligned;
    int16_t strWidthPx;

    // Find horizontal position
    if (alignment & ALIGN_LEFT)
    {
        x_aligned = rect->x1;       // pretty simple - take left rect border as starting point
    }
    else
    {
        // We need to compute length of whole string in pixels
        strWidthPx = LCD_GetStringWidth(currentFont,str);
        if (alignment & ALIGN_RIGHT)
            x_aligned = (int16_t)rect->x2 + 1 - strWidthPx;
        else
            x_aligned = rect->x1 + ((int16_t)(rect->x2 - rect->x1 + 1) - strWidthPx) / 2;
    }

    // Find vertical position
    if (alignment & ALIGN_TOP)
    {
        y_aligned = rect->y1;
    }
    else if (alignment & ALIGN_BOTTOM)
    {
        y_aligned = (int16_t)rect->y2 + 1 - currentFont->height;
    }
    else
    {
        y_aligned = rect->y1 + ((int16_t)(rect->y2 - rect->y1 + 1) - currentFont->height) / 2;
    }

    // Now print the string
    while((c = str[index++]))
    {
        if (LCD_GetFontItem(currentFont, c, &charWidth, &charOffset))
        {
            LCD_drawPackedImage(&currentFont->data[charOffset], x_aligned, y_aligned, charWidth, currentFont->height);
            x_aligned += charWidth + currentFont->spacing;
        }
    }
}



