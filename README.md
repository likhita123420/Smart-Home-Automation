# Smart Home Automation System

This project is an **Arduino-based Smart Home Automation System** that monitors and responds to environmental changes using multiple sensors. It provides real-time alerts on the LCD display and via Bluetooth, and allows basic remote control of devices.

---

## **Features**
- Detects motion using **IR and PIR sensors**  
- Monitors temperature and humidity with **DHT11 sensor**  
- Detects **flames** and **gas leaks**  
- Sends alerts via **buzzer, LEDs, and Bluetooth**  
- Controls a **servo motor** based on sensor inputs  
- Displays sensor readings and alerts on **16x2 I2C LCD**

---

## **Components Required**
- Arduino Uno  
- DHT11 Temperature & Humidity Sensor  
- IR Sensor  
- PIR Motion Sensor  
- Flame Sensor  
- Gas Sensor (e.g., MQ2 or MQ135)  
- Servo Motor  
- 16x2 I2C LCD  
- Buzzer and LEDs  
- Jumper Wires and Breadboard  
- Bluetooth Module (HC-05 or HC-06)  

---

## **Wiring Overview**
- **IR Sensor:** Digital Pin 2 → Sensor output  
- **IR LED:** Digital Pin 13 → LED  
- **PIR Sensor:** Digital Pin 3 → Sensor output  
- **Servo Motor:** Digital Pin 9  
- **DHT11 Sensor:** Digital Pin 4  
- **Flame Sensor:** Digital Pin 5  
- **Gas Sensor:** Analog Pin A0  
- **Buzzer:** Digital Pin 8  
- **LED:** Digital Pin 6  
- **Bluetooth TX/RX:** Pins 11/1  



## **Usage**
1. Open `Smart_Home_Automation.ino` in Arduino IDE  
2. Connect the Arduino board and components as per wiring  
3. Upload the code to Arduino  
4. Monitor LCD for real-time readings and alerts  
5. Pair with Bluetooth module to receive notifications on mobile or control external devices  

---

## **Bluetooth Commands**
- Send `'H'` → Turns on external LED (Pin 7)  
- Send `'L'` → Turns off external LED (Pin 7)  
- More commands can be added in the code if needed  

---

## **How It Works**
1. **Motion Detection:**  
   - IR and PIR sensors detect movement.  
   - LCD displays “MOTION DETECTED: YES/NO”.  
   - PIR LED lights up when motion is detected.  

2. **Environmental Monitoring:**  
   - DHT11 reads temperature and humidity.  
   - LCD shows current T°C / T°F and humidity %.  

3. **Fire & Gas Alerts:**  
   - Flame sensor triggers buzzer and LED on flame detection.  
   - Gas sensor triggers buzzer and LED when gas concentration crosses threshold.  
   - Alerts are sent to Bluetooth app in real-time.  

4. **Servo Motor Control:**  
   - Servo rotates to 90° if IR sensor detects movement, otherwise returns to 0°.  
