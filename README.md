# 🚗 Smart Parking Management System Using NodeMCU & KiwisIoT

An IoT-based Smart Parking Management System that detects vehicle presence using an ultrasonic sensor, indicates parking conditions through LED lights, and monitors real-time sensor data using the KiwisIoT platform.

## 📌 Project Overview

The Smart Parking Management System is designed to monitor parking space conditions automatically using a NodeMCU ESP8266 and an HC-SR04 ultrasonic sensor.

The ultrasonic sensor measures the distance between the sensor and an object or vehicle. Based on the measured distance, the system determines whether the parking area is SAFE or NOT SAFE.

Two LED indicators display the parking condition:

- 🟢 Green LED – SAFE: Parking area is clear.
- 🔴 Red LED – NOT SAFE: Vehicle or object detected within the predefined distance.

The system is integrated with the **KiwisIoT platform** through Wi-Fi connectivity. Distance measurements and parking status are transmitted to the IoT dashboard for remote monitoring.

## 🎯 Project Objectives

- Detect vehicle presence using an ultrasonic sensor.
- Measure parking distance in centimetres.
- Identify parking conditions using a 20 cm threshold.
- Indicate parking status through LED lights.
- Connect NodeMCU ESP8266 to KiwisIoT.
- Monitor live sensor readings through an IoT dashboard.

## 🛠️ Components Required

| S.No | Component | Quantity |
|---|---|---|
| 1 | NodeMCU ESP8266 | 1 |
| 2 | Ultrasonic Sensor (HC-SR04) | 1 |
| 3 | Red LED | 1 |
| 4 | Green LED | 1 |
| 5 | Jumper Wires | As required |
| 6 | USB Cable | 1 |

## 💻 Software Requirements

- Arduino IDE
- ESP8266 Board Package
- ESP8266WiFi Library
- KiwisIoT Library
- KiwisIoT Platform
- Wi-Fi Network

## 🔌 Hardware Connections

### 1. Ultrasonic Sensor (HC-SR04) to NodeMCU

| HC-SR04 Pin | NodeMCU Pin |
|---|---|
| VCC | VIN (5V) |
| GND | GND |
| TRIG | D5 |
| ECHO | D6 |

### 2. LED Connections

| Component | NodeMCU Pin |
|---|---|
| Red LED (+) | D1 |
| Green LED (+) | D2 |
| LED (-) | GND |

**Hardware Safety:** The HC-SR04 Echo output is approximately 5V, while ESP8266 GPIO pins operate at 3.3V. Use a suitable 3.3V logic-level shifter between ECHO and D6. Use LEDs with built-in current limiting for direct GPIO connections.

## ⚙️ Working Principle

1. The HC-SR04 ultrasonic sensor emits ultrasonic sound waves.
2. The sound waves reflect when they encounter a vehicle or object.
3. The sensor measures the time taken for the waves to return.
4. NodeMCU calculates the distance in centimetres.
5. The measured distance is compared with the predefined 20 cm threshold.
6. If the distance is greater than 20 cm:
   - Green LED turns ON.
   - Red LED turns OFF.
   - Parking status becomes SAFE.
7. If the distance is less than or equal to 20 cm:
   - Red LED turns ON.
   - Green LED turns OFF.
   - Parking status becomes NOT SAFE.
8. The distance and parking status are transmitted to the KiwisIoT platform through Wi-Fi.

## 📊 KiwisIoT Platform Integration

The project uses the KiwisIoT platform to monitor parking conditions remotely.

NodeMCU ESP8266 connects to the platform using the KiwisIoT library and sends sensor readings through the configured dashboard topic.

### Dashboard Configuration

| Dashboard ID | Parameter | Data |
|---|---|---|
| 1 | Parking Status | SAFE / NOT SAFE |
| 2 | Distance Monitoring | Distance in cm |

### Dashboard Features

- Real-time parking status monitoring.
- Live ultrasonic distance readings.
- SAFE and NOT SAFE status visualization.
- Remote parking condition monitoring.

## 📏 Detection Threshold

The system uses a predefined threshold of 20 cm.

| Distance Condition | Parking Status | Red LED | Green LED |
|---|---|---|---|
| Greater than 20 cm | SAFE | OFF | ON |
| Less than or equal to 20 cm | NOT SAFE | ON | OFF |
| Invalid sensor reading | Sensor Error | OFF | OFF |

## 🚀 Installation and Setup

### Step 1: Install Arduino IDE

Download and install Arduino IDE on your computer.

### Step 2: Configure ESP8266

Install the ESP8266 board package and select:

`NodeMCU 1.0 (ESP-12E Module)`

### Step 3: Install Required Libraries

Install or configure the following libraries:

- ESP8266WiFi
- KiwisIoT

### Step 4: Connect Hardware

Connect the ultrasonic sensor and LED indicators according to the hardware connection tables.

### Step 5: Configure Wi-Fi Credentials

Update the following values in the Arduino code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
const char* topic = "YOUR_KIWISIOT_TOPIC";
```

Use your actual KiwisIoT dashboard topic.

### Step 6: Upload the Code

1. Connect NodeMCU to your computer.
2. Select the appropriate board and COM port.
3. Upload the Arduino program.
4. Open Serial Monitor.
5. Set baud rate to 115200.

### Step 7: Configure KiwisIoT Dashboard

Configure two dashboard telemetry fields:

- ID 1 – Parking Status
- ID 2 – Distance

Verify that the incoming values are displayed correctly.

## 🧑‍💻 Arduino Source Code

```cpp
#include <ESP8266WiFi.h>
#include <KiwisIoT.h>

const char* ssid = "abcd";
const char* pass = "12345678";
const char* topic = "dash_1795241697023";

#define TRIG D5
#define ECHO D6
#define RED_LED D1
#define GREEN_LED D2

long duration;
float distance;

KiwisIoT kiwisiot(ssid, pass, topic);

void setup() {

  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  kiwisiot.begin();

  Serial.println("SMART PARKING SYSTEM");
}

void loop() {

  kiwisiot.run();

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) {

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("Sensor Error");

  }

  else {

    distance = duration * 0.0343 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    kiwisiot.send("2", String(distance, 2));

    if (distance > 20) {

      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);

      Serial.println("Status: SAFE");

      kiwisiot.send("1", "SAFE");

    }

    else {

      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);

      Serial.println("Status: NOT SAFE");

      kiwisiot.send("1", "NOT SAFE");

    }
  }

  Serial.println("--------------------");

  delay(1000);
}
```

## 🧪 Testing and Expected Results

### Test Case 1: SAFE Condition

- Keep the parking detection area clear.
- Ensure the measured distance is greater than 20 cm.
- Green LED turns ON.
- KiwisIoT displays SAFE.

### Test Case 2: NOT SAFE Condition

- Place a vehicle or object within 20 cm.
- Ultrasonic sensor detects the object.
- Red LED turns ON.
- KiwisIoT displays NOT SAFE.

### Test Case 3: Sensor Error

- Disconnect or obstruct the sensor connection to produce an invalid reading.
- Both LEDs turn OFF.
- Serial Monitor displays Sensor Error.
- No new telemetry status is sent for that invalid reading.

## 🌍 Applications

- Shopping mall parking areas.
- College and university parking facilities.
- Office parking management.
- Residential parking spaces.
- Smart city infrastructure.
- Small-scale vehicle monitoring systems.

## ⭐ Advantages

- Low-cost IoT implementation.
- Automatic vehicle detection.
- Real-time distance measurement.
- LED-based parking status indication.
- Wi-Fi-based remote monitoring.
- KiwisIoT dashboard integration.
- Easy to expand for multiple parking slots.

## 🔮 Future Enhancements

- Monitor multiple parking slots using additional ultrasonic sensors.
- Display total available parking spaces.
- Develop a mobile application.
- Integrate automatic parking gate control.
- Maintain vehicle entry and exit records.
- Generate parking availability notifications.
- Implement parking occupancy analytics.

## 📌 Conclusion

The Smart Parking Management System demonstrates how IoT technology can be used to monitor parking conditions automatically.

By integrating NodeMCU ESP8266 with an HC-SR04 ultrasonic sensor and LED indicators, the system identifies vehicle presence and displays the parking condition based on a predefined distance threshold.

The integration with KiwisIoT enables remote monitoring of parking status and distance measurements through an IoT dashboard.

This project provides a simple and affordable foundation for developing intelligent parking monitoring solutions.

## 👨‍💻 Technologies Used

- **Microcontroller:** NodeMCU ESP8266
- **Sensor:** HC-SR04 Ultrasonic Sensor
- **Indicators:** Red LED and Green LED
- **Programming:** Arduino C++
- **IoT Platform:** KiwisIoT
- **Connectivity:** Wi-Fi

---

**Project:** Smart Parking Management System

**Platform:** KiwisIoT

**Category:** Internet of Things (IoT)

Github link : https://github.com/Sudhakarkrish2002/Smart-Parking-with-NodeMCU-KiwisIoT
KiwisIoT Website : https://kiwisiot.in
