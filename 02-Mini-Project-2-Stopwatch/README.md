# Mini Project 2 – Stopwatch with Dual Mode (Increment / Countdown)

A digital stopwatch on the **ATmega32** with six multiplexed common-anode seven-segment displays (one 7447 decoder, NPN transistors on PA0–PA5).

## Features
- **Increment mode** (default): counts up from zero, red LED on PD4
- **Countdown mode**: user sets hours/minutes/seconds, counts down, yellow LED on PD5, buzzer on PD0 at zero
- Reset (INT0, falling edge), Pause (INT1, rising edge), Resume (INT2, falling edge)
- Mode toggle on PB7, time-adjust buttons on PB0–PB6

## Key points
- Timer1 in CTC mode generates the 1-second tick
- 16 MHz system clock, 7447 on the lower 4 bits of PORTC

## Files
- `Mini Project2.pdf` – project specification
- `ziad Moried project2.rar` – source and simulation files

## Reference video
https://youtu.be/-7c2NCQg5r4
