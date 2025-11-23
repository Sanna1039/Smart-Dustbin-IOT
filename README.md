# Smart Dustbin IoT System

## Project Overview
The Smart Dustbin IoT project automates waste monitoring by using an ultrasonic sensor to measure the fill level of a dustbin. The ESP32 microcontroller communicates sensor data to the Blynk IoT cloud platform via WiFi, allowing real-time remote monitoring through a mobile app. An IR sensor enables touchless lid operation via a servo motor, promoting hygiene and convenience.

## Features
- Real-time dustbin fill level monitoring (0-100%)
- Bin status display (Empty, Half Filled, Full)
- Touchless lid operation using IR sensor and servo motor
- Notifications sent to mobile app when the bin is full
- Easy-to-use Blynk IoT dashboard with gauges and status labels
- IP address display on app for network diagnostics

## Components
- ESP32 Dev Module
- HC-SR04 Ultrasonic Sensor
- IR Motion Sensor
- SG90 Servo Motor
- Breadboard and jumper wires

## Wiring Diagram
| Component      | ESP32 Pin | Description                       

Ultrasonic Trig  - GPIO 5    - Trigger pin for ultrasonic sensor 
 Ultrasonic Echo - GPIO 19   = Echo pin for ultrasonic sensor    
 IR Sensor       - GPIO 21   - Motion detection for lid control  
 Servo Signal    - GPIO 23   - PWM signal for servo motor        
 Power           - 5V        - Common power supply               
 Ground          - GND       - Common ground                     

## Firmware
Firmware is written in Arduino IDE using the following libraries:
- BlynkSimpleEsp32.h
- ESP32Servo.h
- WiFi.h

The main tasks include:
- Reading ultrasonic sensor distance and calculating fill level
- Reading IR sensor for lid control
- Sending sensor data and statuses to Blynk virtual pins
- Handling servo motor control based on sensor input
- Sending notifications when dustbin is full

## Blynk IoT Setup
- Template ID: (Replace with your Blynk template ID)
- Device authentication token: (Replace with your Blynk auth token)
- Virtual pins used:
  - V0: Dustbin fill level (percentage)
  - V1: Bin status text
  - V2: ESP32 IP address

## How to Use
1. Connect components as per wiring table.
2. Update credentials (WiFi SSID, password, Blynk auth token) in the code.
3. Upload the firmware to ESP32 using Arduino IDE.
4. Open Blynk app dashboard configured with widgets linked to virtual pins.
5. Monitor fill level and status, receive notifications when the bin is full.
6. Use IR sensor to open/close servo-operated lid for touchless operation.

## Future Improvements
- Battery operation with solar power
- Multiple bin monitoring with centralized dashboard
- Machine learning for predictive fill-level estimation
- GPS integration for smart waste collection routing

## License
This project is open source and available under the MIT License.

---

Feel free to customize according to your team details and specific links.

If you want, I can also provide this as a ready-to-upload markdown file.
