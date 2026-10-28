#include "buzzer.h"
#include "gpio.h"

void Buzzer_init(void)
{
    GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW); /* OFF initially */
}

void Buzzer_on(void)
{
    /* Active-LOW through transistor → pull pin LOW to turn ON */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,  LOGIC_HIGH);
}

void Buzzer_off(void)
{
    /* Drive pin HIGH to turn transistor OFF → buzzer OFF */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
