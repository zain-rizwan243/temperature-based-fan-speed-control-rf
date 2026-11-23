# Communication System for Fan Speed Control Based on Temperature

A wireless system that measures temperature at one point and adjusts the
speed of a 12V DC brushless fan at another, automatically. A transmitter
Arduino reads a DS18B20 temperature sensor and sends the value over an
RF link (FS100A), and a receiver Arduino converts it into a PWM signal
that controls the fan through a MOSFET.

Developed for the Communication Systems Lab (2023).

## Introduction
Temperature changes throughout a hot summer day, and we adjust the
fans in our homes and offices to match: low in the early morning and at
night, moderate in the morning, and high in the afternoon.

## Problem Statement
Adjusting a fan's speed by hand, again and again through the day, is
tiring. This project adjusts the fan speed automatically based on the
room or outside temperature, using a wireless transmitter and receiver.

## Objective
To design a communication system that sends temperature data to a fan
module and controls its speed accordingly, creating a comfortable
environment.

## System Overview
The system has two parts, each built around an Arduino Uno.

**Transmitter module**
- DS18B20 temperature sensor, read every second
- 16x2 LCD showing the current temperature in real time
- FS100A RF transmitter, which sends the temperature wirelessly using
  ASK (Amplitude Shift Keying)

**Receiver module**
- FS100A RF receiver, which passes the received temperature to the
  Arduino
- 16x2 LCD showing the received temperature, the fan speed, and the PWM
  value
- CEP3205 n-channel MOSFET, driven by the Arduino's PWM output, with a
  pull-down resistor at the gate
- 12V DC brushless fan, powered from an external supply

The Arduino only generates the PWM signal for the MOSFET gate. It can
supply just 5 V and very little current, so the fan gets its power
from a separate supply through the MOSFET, which acts as a fast switch.

## How It Works
The DS18B20 can measure from -55 to 125 °C, but for everyday use the
0-50 °C range is enough, so the control algorithm is designed for that
range. The transmitter only measures and sends the temperature. The main
algorithm runs on the receiver side, which sets the fan speed with PWM
according to this table:

| Temperature (°C) | PWM value (0-255) | Fan          |
|------------------|-------------------|--------------|
| 15 or below      | 0                 | Off          |
| above 15 to 20   | 40                | Low          |
| above 20 to 25   | 70                |              |
| above 25 to 30   | 110               |              |
| above 30 to 35   | 150               |              |
| above 35 to 40   | 190               |              |
| above 40 to 45   | 220               |              |
| above 45 to 50   | 255               | Maximum      |

The Arduino sends this PWM signal to the MOSFET gate, which switches
the fan on and off very fast. The average power to the fan changes with
the PWM value, so the fan speed follows the temperature.

## Components
- 2 x Arduino Uno
- FS100A RF transmitter and receiver module
- DS18B20 temperature sensor
- CEP3205 n-channel MOSFET with a pull-down resistor at the gate
- 12V DC brushless fan
- 2 x 16x2 LCD (one on each side)

## Software
- Arduino IDE
- OneWire library (DS18B20)
- VirtualWire library (FS100A RF module)

## Screenshots & Images
<img width="438" height="305" alt="image" src="https://github.com/user-attachments/assets/81af3486-6152-4471-a6cc-9de47ead56a5" />
<img width="430" height="258" alt="image" src="https://github.com/user-attachments/assets/bd9032d7-be4d-4c15-b3c1-2dd663ad051b" />
<img width="691" height="444" alt="image" src="https://github.com/user-attachments/assets/98c64af5-6b46-41ac-b2b3-6be576148b83" />
<img width="692" height="414" alt="image" src="https://github.com/user-attachments/assets/27319227-5a7b-4ec2-a246-8b02e4284502" />


## Repository Contents
- `ASK_transmitter/ASK_transmitter.ino` - transmitter code (sensor reading, LCD, RF sending)
- `ASK_receiver/ASK_receiver.ino` - receiver code (RF receiving, PWM algorithm, LCD)
- `images/` - photos of the project

## Author
Zain Rizwan - Electrical Engineer<br>
Communication Systems Lab project, University (2023)
