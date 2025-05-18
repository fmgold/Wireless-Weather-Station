# 🌤️ Wireless Weather Station with Firebase Integration

A **low-cost**, **Wi-Fi-enabled** weather monitoring system that measures **temperature**, **humidity**, and **light intensity** in real time. The data is displayed on an **I2C LCD** and uploaded to **Firebase Realtime Database**, enabling remote monitoring via the internet.

---

## 📸 Project Overview

This system is based on the **ESP32** and uses a **DHT11 sensor**, **LDR**, and **LiquidCrystal_I2C LCD** to monitor environmental conditions. Data is sent to the **Firebase Realtime Database** over Wi-Fi for remote access and visualization.

---

## 📦 Components Used

| Component              | Quantity | Description                               |
|------------------------|----------|-------------------------------------------|
| ESP32 Dev Board        | 1        | Main microcontroller                      |
| DHT11 Temperature/Humidity Sensor | 1 | Measures temperature and humidity        |
| LDR (Light Dependent Resistor)    | 1 | Measures light intensity                 |
| 16x2 I2C LCD Display   | 1        | Displays readings                        |
| Firebase Account       | 1        | Realtime Database storage                 |
| Breadboard & Jumper Wires | -     | For prototyping                          |

---

## 📲 Features

- 🌡️ **Temperature & Humidity Monitoring** (via DHT11)
- 💡 **Light Intensity Detection** (via LDR)
- 🔁 **Live Data Display** on I2C LCD
- ☁️ **Real-Time Firebase Upload**
- 🌐 **Wi-Fi Connectivity**
- 🔧 Basic error handling for sensor failures

---

## 🔧 Circuit Connections

| Component | ESP32 Pin |
|----------|-----------|
| DHT11    | GPIO14    |
| LDR      | GPIO35 (analog) |
| LCD SDA  | GPIO21    |
| LCD SCL  | GPIO22    |

> 💡 *Use a voltage divider with the LDR to get an analog reading.*

---

## 🧰 Libraries Required

Install the following libraries from Arduino Library Manager:

- `Firebase_ESP_Client`
- `LiquidCrystal_I2C`
- `DHT sensor library`
- `Adafruit Unified Sensor`
- `addons/TokenHelper.h` and `RTDBHelper.h` (included with Firebase client)

---

## 🚀 Getting Started

1. **Set Your Wi-Fi and Firebase Credentials**

```cpp
#define WIFI_SSID "your-ssid"
#define WIFI_PASSWORD "your-password"

#define API_KEY "your-firebase-api-key"
#define DATABASE_URL "your-project-id.firebaseio.com"
