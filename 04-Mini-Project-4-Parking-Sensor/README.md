# Mini Project 4 – Car Parking Sensor

A parking-assist system on the **ATmega32** using an **HC-SR04 ultrasonic sensor**, a 16x2 LCD (4-bit mode), three LEDs and a buzzer.

## Behavior
| Distance | LEDs | Buzzer | LCD |
|----------|------|--------|-----|
| ≤ 5 cm | R+G+B flashing | ON | "Stop" |
| 6–10 cm | R+G+B on | off | distance |
| 11–15 cm | R+G on | off | distance |
| 16–20 cm | R on | off | distance |
| > 20 cm | all off | off | distance |

## Drivers
GPIO, ICU (F_CPU/8, rising edge first), Ultrasonic (`Ultrasonic_init`, `Ultrasonic_Trigger`, `Ultrasonic_readDistance`, `Ultrasonic_edgeProcessing`), Buzzer, LCD (4-bit).

## Files
- `Mini_Project4.pdf` – project specification
- `ziad Moried mini_project4.rar` – source and simulation files

## Reference video
https://youtu.be/bhtyP1ZBiJg
