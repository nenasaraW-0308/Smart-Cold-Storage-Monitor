# 🌿 Smart Cold Storage / Greenhouse Temperature Monitor

An IoT-based environmental monitoring system powered by **ESP32** and **DHT22**, featuring real-time automated alerts and a built-in web dashboard. Designed for precision agriculture (greenhouses) and cold-chain storage facilities.

---

## 🚀 Key Features
* **Real-Time Monitoring:** Tracks ambient temperature and humidity using a DHT22 sensor.
* **Automated Alert System:** Instantly triggers a Red LED and an active Buzzer when the temperature exceeds safety thresholds (e.g., >30°C).
* **ESP32 Web Server Dashboard:** Streams live sensor data directly to a local web browser interface over Wi-Fi.
* **Simulation Ready:** Fully tested and operational in the Wokwi IoT simulator.

---

## 🛠️ Tech Stack & Components
* **Microcontroller:** ESP32 NodeMCU
* **Sensor:** DHT22 (Temperature & Humidity Sensor)
* **Actuators:** Red LED (GPIO 2), Buzzer (GPIO 4)
* **Framework:** Arduino IDE / C++
* **Protocols:** Wi-Fi (HTTP Server)

---

## ⚙️ Circuit Connections
| Component | ESP32 Pin | Description |
| :--- | :--- | :--- |
| **DHT22 (Data)** | GPIO 15 | Single-wire data communication |
| **Red LED (+)** | GPIO 2 | High temperature visual warning |
| **Buzzer (+)** | GPIO 4 | Audio alert generation via `tone()` |
| **GND / VCC** | GND / 3V3 | Power and common ground |

---

## 💻 Firmware Code (`main.ino`)
You can find the complete source code in the `main.ino` file within this repository. 

---

## 🌐 How to Run (Wokwi Simulation)
1. Open [Wokwi](https://wokwi.com/) and create a new ESP32 project.
2. Add a **DHT22 sensor**, an **LED**, and a **Buzzer** connecting them to the respective GPIO pins listed above.
3. Paste the code from `main.ino` into the editor.
4. Click **Start Simulation** and open the browser using the generated IP address to view the live dashboard!
