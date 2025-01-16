# Kari Library

[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

**Kari** is a lightweight and efficient Arduino library designed for asynchronous execution, sensor-based applications, and efficient pin control. It simplifies the integration of various sensors (like ultrasonic, PIR, and infrared) and supports asynchronous task management to improve performance.

## 📌 Features
- 📡 **Asynchronous Execution** – Non-blocking tasks in the `loop()` function.
- 🔧 **Sensor Support** – Includes helper functions for PIR, ultrasonic, and infrared sensors.
- ⚡ **Pulse and Sequential Execution** – Manage digital pin pulses and sequences easily.
- 🚀 **Optimized for AVR & Non-AVR Boards** – Compatible with a wide range of Arduino-compatible boards.

## 📥 Installation
To install the **Kari Library**:

1. **Download from GitHub**
   - Go to the [Kari GitHub Repository](https://github.com/vincentmuriithi/kari) or [Kari Website](https://kari.netlify.app).
   - Download the `.zip` file of the latest release.

2. **Manual Installation**
   1. Extract the `.zip` file.
   2. Copy the **`Kari`** folder to your Arduino **`libraries`** folder.
      - On Windows, it's usually located at:  
        `Documents/Arduino/libraries/`
   3. Restart the Arduino IDE.

---

## 🛠 API Reference

### 📍 KariUltrasonic
- `kariUltrasonic(int trigPin, int echoPin);`
- `float measure();`
- `static void measureMulti();`
- `int onMeasure(float lowerBound, float upperBound, void (*callback)(), bool triggerOnUpperBound=false);`
- `void attach();`

### 🔥 **KariPIR**
- `kariPIR(int signalPin);`
- `void onMeasure(void (*callback)(), void (*fallbackCallback)() = nullptr);`

### 🌟 **KariInfrared**
- `kariInfrared(int signalPin);`
- `void onMeasure(void (*callback)());`
### ⚡ KariAsync
- `static void execute(void (*callback)(), unsigned int delay);`  
  *Use this function inside the `loop()` to run asynchronous tasks.*

## 🔁 KariPulse & KariSequential
- `void kariPulse(Pins array);`
- `void kariSequential(Pins array);`
## 📜 License
This library is licensed under the Apache License 2.0.
See the full license here: Apache-2.0 License.

## ✨ Author
**Vincent Muriithi Karimi**  
GitHub: [vincentmuriithi](https://github.com/vincentmuriithi)  
Email: vincentmuriithi06@gmail.com 

## 🌐 Website
For more information about **Kari** and updates, visit:  
[Kari Website](https://kari.netlify.app)