/******************************************************************************
 *
 * File Name: app.c
 *
 * Description: Application layer for Car Parking System (steady behavior)
 *
 *******************************************************************************/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "std_types.h"
#include "gpio.h"
#include "lcd.h"
#include "buzzer.h"
#include "ultrasonic.h"
#include"led.h"

/* LED connections (as in your project) */
#define LED_PORT   PORTC_ID
#define LED_RED    0
#define LED_GREEN  1
#define LED_BLUE   2

/* Helper: set LEDs (0 = off, 1 = on) */

int main(void)
{
    /* Configure LED pins as outputs */


    /* Initialize peripherals */
    Buzzer_init();
    LCD_init();
    Ultrasonic_init();
    LEDS_init();


    /* enable global interrupts (ICU uses ISR) */
    sei();

    /* Splash then clear */
    LCD_clearScreen();
    LCD_displayStringRowColumn(0, 0, "Car Parking Sys");
    _delay_ms(800);
    LCD_clearScreen();

    while (1)
    {
        /* Get averaged distance (3 samples) */
        uint16 dist = Ultrasonic_readDistanceAvg(3);

        /* Clear and show result */
        LCD_clearScreen();

        if (dist == 0xFFFF) /* timeout/no echo */
        {
            LCD_displayStringRowColumn(0, 0, "No Echo");
            Buzzer_off();
            LED_off(RED);
              LED_off(GREEN);
              LED_off(BLUE);
        }
        else
        {
            /* Row 0: distance */
            LCD_displayStringRowColumn(0, 0, "Dist: ");
            LCD_integerToString(dist);   /* writes at current cursor */
            LCD_displayString(" cm");

            /* Row 1: steady status and LED/Buzzer mapping */
            if (dist <= 5)
            {
                LCD_displayStringRowColumn(1, 0, "STOP!");
                Buzzer_on();
                LED_on(RED);
                  LED_on(GREEN);
                  LED_on(BLUE);
            }
            else if (dist <= 10)
            {
                LCD_displayStringRowColumn(1, 0, "Close");
                Buzzer_off();
                LED_on(RED);
                  LED_on(GREEN);
                  LED_on(BLUE);
            }
            else if (dist <= 15)
            {
                LCD_displayStringRowColumn(1, 0, "Medium");
                Buzzer_off();
                LED_on(RED);
                  LED_on(GREEN);
                  LED_off(BLUE); /* red + green */
            }
            else if (dist <= 20)
            {
                LCD_displayStringRowColumn(1, 0, "Far");
                Buzzer_off();
                LED_on(RED);
                  LED_off(GREEN);
                  LED_off(BLUE); /* red only */
            }
            else
            {
                LCD_displayStringRowColumn(1, 0, "Safe");
                Buzzer_off();
                LED_off(RED);
                  LED_off(GREEN);
                  LED_off(BLUE); /* all off */
            }
        }

        _delay_ms(120); /* update interval */
    }

    return 0;
}
