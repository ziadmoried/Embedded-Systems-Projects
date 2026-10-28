# 5 · Vehicle Fault Detection and Logging System

A two-ECU embedded system built on two **ATmega32** microcontrollers that monitors a vehicle, controls its windows and **logs faults to external EEPROM**.

```
 ┌────────────── HMI_ECU ──────────────┐   UART 9600 8N2   ┌──────────── Control_ECU ────────────┐
 │ 4×20 LCD · Keypad · Timer1 (1 s)    │ ◄───────────────► │ LM35 · Ultrasonic · 2 window motors │
 │ Menu, display, fault viewer         │                   │ Window buttons · I²C EEPROM log     │
 └─────────────────────────────────────┘                   └─────────────────────────────────────┘
```

## HMI_ECU – user interface

Keypad menu shown on the LCD:

| Key | Action |
|-----|--------|
| 1 – Start | Starts the car: sensors and motors are initialised on the Control ECU |
| 2 – Display | Live view of temperature, distance and the state of both windows |
| 3 – Faults | Scrolls through the faults stored in EEPROM |
| 4 – Stop | Stops the system and the motors |

If the car has not been started, Display and Faults ask the user to start it first.

## Control_ECU – control and logging

- Reads **temperature** (LM35 through the ADC, 2.56 V reference) and **distance** (ultrasonic through the ICU).
- Opens/closes **two windows** with DC motors (H-bridge, PWM on Timer0) driven by four push buttons.
- Detects and logs faults to the external **I²C (TWI) EEPROM**, once per occurrence:

| Code | Fault | Condition |
|------|-------|-----------|
| `P001` | Distance fault | distance < 10 |
| `P002` | Temperature fault | temperature > 90 °C |

### UART protocol

| Command (HMI → Control) | Value |
|-------------------------|-------|
| `START_CAR` | 1 |
| `DISPLAY` | 2 |
| `FAULTS` | 3 |
| `STOP_CAR` | 4 |
| `CONT` / `EXIT` | 5 |

Responses are framed with a `0xAA` start byte, for example the display frame `0xAA, temperature, distance, window1, window2`.

## Drivers

GPIO · ADC · UART · TWI (I²C) · ICU · Timer · PWM (Timer0) · LCD · Keypad · Buttons · DC motor · LM35 · Ultrasonic · External EEPROM.
