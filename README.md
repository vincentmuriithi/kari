# Kari Library

[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

**Kari** is a lightweight and efficient Arduino library designed for asynchronous execution, sensor-based applications, and efficient pin control. It simplifies the integration of various sensors (like ultrasonic, PIR, and infrared) and supports asynchronous task management to improve performance.

## 📌 Features
- ⚡ **Asynchronous Execution** – Non-blocking tasks in the `loop()` function.
- 🔧 **Sensor Support** – Includes helper functions for PIR, ultrasonic, and infrared sensors.
- 🔁 **Pulse and Sequential Execution** – Manage digital pin pulses and sequences easily.
- 🚀 **Optimized for AVR & Non-AVR Boards** – Compatible with a wide range of Arduino-compatible boards.

## 📥 Installation
To install the **Kari Library**:

1. **Download from GitHub**
   - Go to the [Kari GitHub Repository](https://github.com/vincentmuriithi/kari) or [Kari Website](https://kariIOT.netlify.app).
   - Download the `.zip` file of the latest release.

2. **Manual Installation**
   1. Extract the `.zip` file.
   2. Copy the **`Kari`** folder to your Arduino **`libraries`** folder.
      - On Windows, it's usually located at:  
        `Documents/Arduino/libraries/`
   3. Restart the Arduino IDE.

---

## 🛠 API Reference

### 🧭 KariUltrasonic
- `kariUltrasonic(int trigPin, int echoPin);`
- `float measure();`
- `static void measureMulti();`
- `int onMeasure(float lowerBound, float upperBound, void (*callback)(), bool triggerOnUpperBound=false);`
- `void attach();`

### 📡 **KariPIR**
- `kariPIR(int signalPin);`
- `void onMeasure(void (*callback)(), void (*fallbackCallback)() = nullptr);`

### 📡 **KariInfrared**
- `kariInfrared(int signalPin);`
- `void onMeasure(void (*callback)());`
### ⚡ KariAsync
- `static void execute(void (*callback)(), unsigned int delay);`  
  *Use this function inside the `loop()` to run asynchronous tasks.*

### 🔁 KariPulse & KariSequential
- `void kariPulse(Pins array);`
- `void kariSequential(Pins array);`

## 🔨 Usage

### 1️⃣ **Basic Example: Measuring Distance with KariUltrasonic**
```cpp
#include <kari.h>
#define TRIG_PIN 8
#define ECHO_PIN 7
using namespace kari;

void callback1();
void callback2();
void wrapper();

kariUltrasonic *ultra1;

void setup(){
Serial.begin(9600);
ultra1 = new kariUltrasonic(TRIG_PIN, ECHO_PIN);
}


void loop(){
    kariAsync::execute(wrapper, 1000);
}

void wrapper(){

            Serial.println("Using kariAsync\n");

            Serial.println(kari::getDistance<kariUltrasonic>(ultra1));

            ultra1->measure();
            ultra1->onMeasure(10, 10, callback1);
            ultra1->onMeasure(50, 50, callback2, true);
            ultra1->onMeasure(10, 30,
            [](){
                Serial.println("Distance is between 20 and 30");
            }
            );
        }

void callback1(){
    Serial.println("Distance is below 10");
}

void callback2(){
    Serial.println("Distance is above 50");
} 
```

### 2️⃣ **Basic Example: Use case of kariPIR**
```cpp
#include <kari.h>
using namespace kari;

kariPIR *pir;
void setup(){
    kariBegin({7});
    pir = new kariPIR(8);
}


void loop(){
    kariAsync::execute(
        [](){
            pir->onMeasure(
                [](){ digitalWrite(7, HIGH); },
                [](){ digitalWrite(7, LOW); }
            );

        },10
    );
} 
```

### 3️⃣ **Basic Example: Use case of kariInfrared**
```cpp
#include <kari.h>

using namespace kari;

int pin = 5;
kariInfrared *irSensor;

void onDetection() {
    Serial.println("Infrared signal detected!");
}

void setup() {
    Serial.begin(9600);
    kariBegin({pin});
    irSensor = new kariInfrared(pin); // Initialize infrared sensor on pin 5
}

void loop() {
    kariAsync::execute(
    [] () {
        irSensor->onMeasure(onDetection); // Check for infrared signal continuously
    },
    100
    );
}
```

### 4️⃣ **Basic Example: Use case of kariAsync**
```cpp    
#include <kari.h>
using namespace kari;

void printToScreen();

void setup(){
    Serial.begin(9600);
    kariBegin({9, 8, 7, 6, 5, 4, 3, 2});
}

void loop(){
    kariAsync::execute(
        [](){
            kariSequential({ {9, 8, 7, 6}, "sequential1"});
        },
        1500
    );

    kariAsync::execute(
        [](){
            kariPulse({ {5, 4, 3, 2}, "pulse1"});
        },
        500
    );

    kariAsync::execute(
        [](){
           Serial.println("Task executed after every 3 seconds"); 
        },
        3000
    );
    kariAsync::execute(printToScreen, 2500);
   
}

void printToScreen(){
	Serial.println("This is executed after each 2.5 seconds");
}
```

### 5️⃣ **Basic Example: Use case of kariPulse**
```cpp
#include <kari.h>
using namespace kari;


void setup(){
    kariBegin({7,4,2});
}

void loop(){
    kariAsync::execute(
        [](){
            kariPulse({ {7, 4, 2}, "pulse1"});
        },
        1000
    );

}
```

### 6️⃣ **Basic Example: Use case of kariSequential**
```cpp
#include <kari.h>
using namespace kari;


void setup(){
    Serial.begin(9600);
    kariBegin({8, 7, 6, 5});
}

void loop(){
    kariAsync::execute(
        [](){
            kariSequential({ {8, 7, 6, 5}, "sequential1"});
        },
        1500
    );
   
}
```

## 📜 License
This library is licensed under the Apache License 2.0.
See the full license here: [Apache-2.0 License.](https://opensource.org/licenses/Apache-2.0)

## ✨ Author
**Vincent Muriithi Karimi**  
GitHub: [vincentmuriithi](https://github.com/vincentmuriithi)  
Email: vincentmuriithi06@gmail.com 

## 🌐 Website
For more information about **Kari** and updates, visit:  
[Kari Website](https://kariiot.netlify.app)
