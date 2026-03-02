/* 
 * File:   OLED_INTERFACE.h
 * Author: 111
 *
 * Created on November 15, 2025, 11:04 PM
 */

#ifndef OLED_INTERFACE_H
#define	OLED_INTERFACE_H

#include "../../LIB/DATA_TYPES.h"

/* ====== Configure your pins here ======
   Edit these to match your wiring */
#define ST7789_PORT    PORTC
#define ST7789_PIN_DC  PIN0   // Data/Command
#define ST7789_PIN_RST PIN1   // Reset
#define ST7789_PIN_CS  PIN2   // Chip Select (optional, can tie low)
                                     
/* Display size */
#define ST7789_WIDTH   240
#define ST7789_HEIGHT  240

/* Color helper (RGB565) */
#define RGB565(r,g,b)  (u16)((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | (((b) & 0xF8) >> 3))

/* Basic API */
void ST7789_Init(void);
void ST7789_FillScreen(u16 color);
void ST7789_DrawPixel(u16 x, u16 y, u16 color);
void ST7789_FillRect(u16 x, u16 y, u16 w, u16 h, u16 color);
void ST7789_DrawImage(u16 x, u16 y, u16 w, u16 h, const u16 *img); // img in RGB565
void ST7789_SetRotation(u8 m);




#endif	/* OLED_INTERFACE_H */

