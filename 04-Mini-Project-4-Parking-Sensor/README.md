# 4 · Car Parking Sensor

A parking-assist system on the **ATmega32**. An **HC-SR04 ultrasonic sensor** measures the distance to an obstacle; a 16×2 LCD shows it in centimetres while three LEDs and a buzzer warn the driver as the obstacle gets closer.

## Behavior

| Distance | LEDs | Buzzer | LCD |
|----------|------|--------|-----|
| ≤ 5 cm | R + G + B | ON | `STOP!` |
| 6 – 10 cm | R + G + B | off | distance |
| 11 – 15 cm | R + G | off | distance |
| 16 – 20 cm | R | off | distance |
| > 20 cm | all off | off | distance |

The application averages three readings per update and shows `No Echo` if the sensor times out.

## Hardware

| Part | Pins |
|------|------|
| LCD (4-bit) | RS PA1, E PA2, D4–D7 PA3–PA6, RW to GND |
| LEDs | Red PC0, Green PC1, Blue PC2 |
| Buzzer (via transistor) | PC5 |
| Ultrasonic | Echo PD6 (ICP1), Trigger PD7 |

## Architecture

```
Application  app.c
HAL          ultrasonic · lcd · led · buzzer
MCAL         gpio · icu
```

- **ICU** runs at `F_CPU/8` and captures the echo pulse from the rising edge; `Ultrasonic_init` initialises the ICU and registers the edge-processing callback.
- System clock **16 MHz**.

## Files

| Path | Description |
|------|-------------|
| [`docs/Mini_Project4.pdf`](docs/Mini_Project4.pdf) | Project specification |
| [`src/`](src) | C sources and headers |
| [`firmware/mini_project4.hex`](firmware/mini_project4.hex) | Firmware to load in Proteus / flash |
| [`simulation/ultrasonic.pdsprj`](simulation/ultrasonic.pdsprj) | Proteus circuit |

## Reference video

https://youtu.be/bhtyP1ZBiJg
