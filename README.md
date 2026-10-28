# Embedded Systems Projects

A collection of projects built during the **Edges For Training – Standard Embedded Systems Diploma**. Most target the **ATmega32** (16 MHz) and are written in C with a layered driver architecture (MCAL / HAL / application), simulated in **Proteus**.

| # | Project | Platform | Highlights |
|---|---------|----------|------------|
| 1 | [Student Management System](01-C-Student-Management-System) | C (PC) | Linked list, structs, pointers, dynamic memory |
| 2 | [Dual-Mode Stopwatch](02-Mini-Project-2-Stopwatch) | ATmega32 | Timer1 CTC, external interrupts, multiplexed 7-segment displays |
| 3 | [Smart Home Automation](03-Mini-Project-3-Smart-Home) | ATmega32 | ADC, PWM fan control, LCD, LM35, LDR, flame sensor |
| 4 | [Car Parking Sensor](04-Mini-Project-4-Parking-Sensor) | ATmega32 | ICU + HC-SR04 ultrasonic, LCD (4-bit), LEDs, buzzer |
| 5 | [Vehicle Fault Detection and Logging System](05-Final-Project-Vehicle-Fault-Detection) | 2 × ATmega32 | UART link between ECUs, I²C EEPROM fault log, keypad + LCD HMI |

## Repository layout

Each project folder follows the same structure:

```
NN-Project-Name/
├── README.md        Overview, hardware, behavior, how to run
├── docs/            Original project specification (PDF)
├── src/             C source code
├── firmware/        Compiled output (.hex / .elf) ready to load in Proteus
└── simulation/      Proteus project (.pdsprj)
```

## Tools

- **AVR-GCC** (Eclipse AVR plugin / Atmel toolchain) – building the firmware
- **Proteus** – circuit simulation (`.pdsprj` files)
- **GCC** – building the PC-side C project

## Author

**Ziad Moried** – [@ziadmoried](https://github.com/ziadmoried)

Released under the [MIT License](LICENSE).
