# Mini Project 3 – Smart Home Automation

A smart-home controller on the **ATmega32** built with a layered architecture (MCAL / HAL / application).

## Features
- **Lighting control** – LDR (ADC ch0) drives Red/Green/Blue LEDs by light intensity (<15 %: all on, 16–50 %: R+G, 51–70 %: R, >70 %: off)
- **Fan speed control** – LM35 (ADC ch1) sets a PWM duty cycle via an H-bridge (25 % / 50 % / 75 % / 100 % at 25 / 30 / 35 / 40 °C, off below 25 °C)
- **Fire detection** – flame sensor on PD2 triggers the buzzer and a "Critical alert!" message until the flame clears
- **16x2 LCD** (8-bit mode) shows fan status, temperature and light intensity

## Drivers
ADC, GPIO, PWM (Timer0), LCD, LM35, LDR, LED, DC motor, flame sensor, buzzer.

## Files
- `Mini Project3.pdf` – project specification
- `Project Smart home.rar` – source and simulation files

## Videos
- Project demo: https://youtu.be/Iyj7sOfwYLw
- Flame sensor: https://youtu.be/cD3n-Bz7liM
