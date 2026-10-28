# 2 · Dual-Mode Stopwatch (Increment / Countdown)

A digital stopwatch on the **ATmega32** that counts **up** or **down**, showing hours:minutes:seconds on six multiplexed common-anode seven-segment displays.

## Features

- **Increment mode** (default) – counts up from 00:00:00, red LED on PD4
- **Countdown mode** – user sets the start time, then counts down; yellow LED on PD5 and a buzzer on PD0 when it reaches zero
- **Reset / Pause / Resume** through external interrupts
- Time adjustment with six push buttons (hours, minutes, seconds, ±)

## Hardware

| Function | Pin | Notes |
|----------|-----|-------|
| 7447 BCD decoder | PC0–PC3 | Shared by all six displays |
| Display enable (NPN transistors) | PA0–PA5 | Multiplexing |
| Reset | PD2 / INT0 | Falling edge, internal pull-up |
| Pause | PD3 / INT1 | Rising edge, external pull-down |
| Resume | PB2 / INT2 | Falling edge, internal pull-up |
| Mode toggle | PB7 | Increment ↔ Countdown |
| Hours ± | PB1 / PB0 | Internal pull-ups |
| Minutes ± | PB4 / PB3 | Internal pull-ups |
| Seconds ± | PB6 / PB5 | Internal pull-ups |
| Buzzer | PD0 | Countdown finished |
| LEDs | PD4 (red) / PD5 (yellow) | Mode indicators |

## Implementation notes

- System clock **16 MHz**.
- **Timer1 in CTC mode**, prescaler 1024, `OCR1A = 15625` → one interrupt per second.
- Displays are refreshed by multiplexing; the 7447 drives the segments while the transistor on PA0–PA5 selects the active digit.

## Countdown usage

1. Press **Pause** (PD3).
2. Press **Mode toggle** (PB7).
3. Set the start time with the hour / minute / second buttons.
4. Press **Resume** (PB2) – the buzzer sounds at zero.

## Files

| Path | Description |
|------|-------------|
| [`docs/Mini Project2.pdf`](docs/Mini%20Project2.pdf) | Project specification |
| [`src/project.c`](src/project.c) | Firmware source |
| [`firmware/project.elf`](firmware/project.elf) | Compiled firmware |
| [`simulation/watch project.pdsprj`](simulation/watch%20project.pdsprj) | Proteus circuit |

## Reference video

https://youtu.be/-7c2NCQg5r4
