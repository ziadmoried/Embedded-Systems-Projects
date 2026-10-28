# Final Project – Vehicle Fault Detection and Logging System

A two-microcontroller embedded system (Proteus project `Vehicle Fault Detection and Logging System.pdsprj`):

- **HMI_ECU** – user interface: LCD, keypad, UART communication with the control unit
- **Control_ECU** – control logic: sensors, DC motor, buttons, external EEPROM logging over TWI (I²C), ultrasonic distance sensing

## Drivers used
GPIO, ADC, UART, TWI (I²C), ICU, Timer, PWM (Timer0), LCD, Keypad, Buttons, DC motor, LM35 sensor, Ultrasonic sensor, External EEPROM.

## Files
- `Project Code and drivers/` – C sources and headers for both ECUs, and the Proteus project
- Build outputs (`.o`, `.d`, `.lss`, `.map`) are intentionally excluded.

> Note: no specification PDF for this project was found in the Drive folder. Add one here as `Final Project.pdf` if you have it.
