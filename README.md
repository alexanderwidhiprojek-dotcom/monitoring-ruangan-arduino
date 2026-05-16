# Monitoring Ruangan Arduino

Arduino-based room monitoring system for temperature, humidity, and light intensity using DHT11, LDR, RGB LED, buzzer, and LCD I2C.

---

## Overview

This project was developed as a final project for the Microprocessor and Microcontroller course at Universitas Brawijaya. The system is designed to monitor environmental conditions in real-time and provide both visual and audio indicators based on sensor readings.

The system uses:

* DHT11 sensor for temperature and humidity monitoring
* LDR sensor for light intensity detection
* RGB LED for temperature status indication
* Active buzzer for humidity alerts
* LCD 16x2 I2C for real-time display

The device continuously reads environmental data and updates the LCD display every 5 seconds.

---

## Features

* Real-time temperature monitoring
* Real-time humidity monitoring
* Light intensity monitoring
* RGB LED temperature indicator
* Humidity warning alarm
* LCD I2C display output
* Simple and low-cost embedded monitoring system

---

## Hardware Components

| Component      | Quantity |
| -------------- | -------- |
| Arduino Uno R3 | 1        |
| DHT11 Sensor   | 1        |
| LDR Sensor     | 1        |
| LCD 16x2 I2C   | 1        |
| RGB LED        | 1        |
| Active Buzzer  | 1        |
| Breadboard     | 1        |
| Jumper Wires   | Several  |
| 220Ω Resistor  | 3        |
| 10kΩ Resistor  | 1        |

---

## System Logic

### Temperature Indicator

| Temperature | RGB LED Status |
| ----------- | -------------- |
| < 20°C      | Blue           |
| 20°C - 30°C | Green          |
| > 30°C      | Red            |

### Humidity Alarm

| Humidity  | Buzzer  |
| --------- | ------- |
| < 40%     | 3 Beeps |
| 40% - 60% | Silent  |
| > 60%     | 5 Beeps |

---

## Libraries Used

```cpp
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

---

## Project Structure

```text
monitoring-ruangan-arduino/
│
├── code/
│   └── monitoring_ruangan.ino
│
├── docs/
│   └── laporan.pdf
│
├── images/
│   ├── alat.jpg
│   ├── wiring.jpg
│   └── flowchart.png
│
├── LICENSE
└── README.md
```

---

## Installation

1. Open Arduino IDE
2. Install required libraries:

   * DHT Sensor Library
   * LiquidCrystal I2C
3. Connect all components based on the wiring diagram
4. Upload `monitoring_ruangan.ino` to Arduino Uno
5. Open Serial Monitor if needed

---

## Output Example

LCD Display:

```text
T:28.0C H:55%
Cahaya:6/10
```

---

## Future Improvements

* Upgrade DHT11 to DHT22 or BME280
* Add IoT connectivity using ESP8266/ESP32
* Add cloud monitoring support
* Add data logging using MicroSD
* Improve enclosure and portability

---

## Authors
Alexander Agung Widhi P.


---

## License

This project is licensed under the MIT License.
