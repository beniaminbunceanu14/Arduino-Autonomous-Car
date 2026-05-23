# Arduino Autonomous Robot Car

A versatile robotic platform built for ETTI UPT coursework, featuring dual-mode functionality: autonomous navigation and manual Bluetooth control.

## Features
- **Autonomous Mode:** Uses an ultrasonic/IR sensor to detect obstacles, with automatic maneuver logic.
- **Visual Feedback:** RGB LED system indicating current state (Strobe Green for movement, Blue for obstacle alert, Disco mode when stopped).
- **Acoustic Feedback:** Integrated buzzer for immediate obstacle detection alert.
- **Manual Control:** Fully remote-controllable via Bluetooth (HC-05) using a smartphone app.
- **Multitasking:** Code optimized using `millis()` instead of `delay()` for smooth execution.

## Hardware Used
- Arduino Mega 2560
- L298N Motor Shield
- HC-05 Bluetooth Module
- Sharp Distance Sensor
- RGB LED Module & Buzzer

## Project Documentation
You can find the detailed presentation and circuit diagrams in the `docs/` folder of this repository.

## Usage
1. Connect via Bluetooth using the `1234` PIN.
2. Use the mobile app to send:
   - `F` - Forward
   - `B` - Backward
   - `S` - Stop
   - `A` - Switch to Autonomous Mode
