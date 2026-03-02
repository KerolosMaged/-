#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LINE_1  0                         //For Line Number One
#define LINE_2  1                         //For Line Number Two                           

#define PATTERN_0 0
#define PATTERN_1 1
#define PATTERN_2 2
#define PATTERN_3 3
#define PATTERN_4 4
#define PATTERN_5 5
#define PATTERN_6 6
#define PATTERN_7 7



void LCD_voidInit (void);

void LCD_VoidWriteCommand(u8 Copy_u8command);
void LCD_VoidWriteChar(u8 Copy_u8char);
void LCD_VoidWriteString(u8 *Copy_u8arr);
void LCD_VoidWrite_u32Number ( u32 Copy_u32number);

void LCD_VoidGoTo_XY(u8 Copy_u8line,u8 Copy_position);

void LCD_VoidDrawPattern(u8 Copy_u8pattern_number,u8 *Copy_u8arr_pattern);
void LCD_VoidWritePattern(u8 Copy_u8pattern,u8 Copy_u8line,u8 Copy_position);


void LCD_VoidShiftLeft(void);
void LCD_VoidShiftRight(void);

void LCD_VoidClearDisplay(void);
void LCD_VoidClearGrid(u8 Copy_u8line,u8 Copy_position);
void LCD_VoidClearLine(u8 Copy_u8line);

void LCD_VoidWriteFloatNumber(f32 num);


#endif