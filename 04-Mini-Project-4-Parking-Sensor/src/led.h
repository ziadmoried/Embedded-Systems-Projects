#ifndef LED_H_
#define LED_H_
#include"gpio.h"
#include "std_types.h"
#define RED_LED_PORT_ID    PORTC_ID
#define RED_LED_PIN_ID     PIN0_ID
#define GREEN_LED_PORT_ID  PORTC_ID
#define GREEN_LED_PIN_ID   PIN1_ID
#define BLUE_LED_PORT_ID   PORTC_ID
#define BLUE_LED_PIN_ID    PIN2_ID

typedef enum {RED, GREEN, BLUE} LED_ID;

void LEDS_init(void);
void LED_on(LED_ID id);
void LED_off(LED_ID id);

#endif /* LED_H_ */
