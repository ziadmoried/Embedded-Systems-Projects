#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/* 4-bit mode pins from spec */
#define LCD_RS_PORT_ID PORTA_ID
#define LCD_RS_PIN_ID  1
#define LCD_E_PORT_ID  PORTA_ID
#define LCD_E_PIN_ID   2
#define LCD_DATA_PORT_ID PORTA_ID
#define LCD_DB4_PIN_ID 3
#define LCD_DB5_PIN_ID 4
#define LCD_DB6_PIN_ID 5
#define LCD_DB7_PIN_ID 6

#define LCD_DATA_BITS_MODE 4

void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *str);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str);
void LCD_clearScreen(void);
void LCD_integerToString(int data);

#endif /* LCD_H_ */
