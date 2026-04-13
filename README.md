# Distance Monitoring System

Arduino-based system that measures distance using an ultrasonic sensor and displays results on an LCD.

## Features
- Real-time distance measurement
- LED status indicators (SAFE / MID / CLOSE)
- LCD display output
- Smoothed sensor readings

## Components
- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- 16x2 I2C LCD
- LEDs + resistors

## How it works
The system continuously measures distance and:
- Displays the value on the LCD
- Uses LEDs to indicate proximity levels
