# 3 · Smart Home Automation

A smart-home controller on the **ATmega32** that adjusts lighting and fan speed from sensor readings and raises a fire alarm. It follows a layered architecture (MCAL → HAL → application).

## Behavior

**Lighting (LDR on ADC0)**

| Light intensity | LEDs on |
|-----------------|---------|
| < 15 % | Red, Green, Blue |
| 16 – 50 % | Red, Green |
| 51 – 70 % | Red |
| > 70 % | none |

**Fan (LM35 on ADC1, PWM through an H-bridge)**

| Temperature | Fan speed |
|-------------|-----------|
| ≥ 40 °C | 100 % |
| 35 – 39 °C | 75 % |
| 30 – 34 °C | 50 % |
| 25 – 29 °C | 25 % |
| < 25 °C | off |

**Fire detection** – the flame sensor (PD2) triggers the buzzer (PD3) and shows **"Critical alert!"** on the LCD until the flame is gone.

**LCD (16×2, 8-bit)** – row 1: `FAN is ON/OFF`; row 2: `Temp= xxC LDR= xxx%`.

## Hardware

| Part | Pins |
|------|------|
| LDR | PA0 (ADC0) |
| LM35 | PA1 (ADC1) |
| LCD | RS PD0, E PD1, data PORTC |
| Motor driver | IN1 PB0, IN2 PB1, EN1 PB3 (OC0 / PWM) |
| LEDs | Red PB5, Green PB6, Blue PB7 |
| Flame sensor | PD2 |
| Buzzer | PD3 |

Drivers: ADC (2.56 V reference, prescaler 128), GPIO, PWM (Timer0), LCD, LM35, LDR, LED, DC motor, flame sensor, buzzer.

## Files

| Path | Description |
|------|-------------|
| [`docs/Mini Project3.pdf`](docs/Mini%20Project3.pdf) | Project specification |
| [`firmware/home3.elf`](firmware/home3.elf) | Compiled firmware |
| [`simulation/Smart home proteus.pdsprj`](simulation/Smart%20home%20proteus.pdsprj) | Proteus circuit |

> **Note:** the C source files were not part of the archive this repository was built from, so `src/` is not included yet.

## Videos

- Project demo: https://youtu.be/Iyj7sOfwYLw
- Flame sensor: https://youtu.be/cD3n-Bz7liM
- Flame sensor Proteus library: https://www.mediafire.com/file/cnrdckfrdxun270/Flame-Sensor-Library-For-Proteus-main.zip/file
