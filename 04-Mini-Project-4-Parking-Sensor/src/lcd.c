#include "lcd.h"
#include "gpio.h"
#include "common_macros.h"
#include <util/delay.h>
#include <stdlib.h>

static void lcd_send4bits(uint8 data)
{
    GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
    GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
    GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
    GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));
    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
    _delay_us(1);
    GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
    _delay_us(1);
}

void LCD_sendCommand(uint8 command)
{
    GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
    lcd_send4bits(command>>4);
    lcd_send4bits(command & 0x0F);
    _delay_ms(2);
}

void LCD_displayCharacter(uint8 data)
{
    GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
    lcd_send4bits(data>>4);
    lcd_send4bits(data & 0x0F);
    _delay_ms(1);
}

void LCD_displayString(const char* str)
{
    while(*str) LCD_displayCharacter(*str++);
}

void LCD_init(void)
{
    GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);
    _delay_ms(20);
    LCD_sendCommand(0x02);
    LCD_sendCommand(0x28);
    LCD_sendCommand(0x0C);
    LCD_sendCommand(0x01);
    _delay_ms(2);
    LCD_sendCommand(0x06);
}

void LCD_moveCursor(uint8 row,uint8 col)
{
    uint8 address;
    switch(row){
        case 0: address=col; break;
        case 1: address=0x40+col; break;
        default: address=col; break;
    }
    LCD_sendCommand(0x80|address);
}
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char*str){ LCD_moveCursor(row,col); LCD_displayString(str);}
void LCD_clearScreen(void){ LCD_sendCommand(0x01);}
void LCD_integerToString(int data){ char buff[16]; itoa(data,buff,10); LCD_displayString(buff);}
