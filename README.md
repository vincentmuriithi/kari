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

### :dart: kariPID
- `kariPID(const float setPoint, const float kp=0.00f, const float ki=0.00f, const float kd=0.00f);`
- `float evaluate(float feedBack);`

### :car: kariDrive
- `kariDrive(const int motor1_EN, const int motor1_InA, const int motor1_InB, int motor2_EN, const int motor2_InA, const int motor2_InB);`
- `void drive(int speed = 100, bool directionStatus = 0);`
- `void right(int speed = 30, bool directionStatus = 0);`
- `void left(int speed = 30, bool directionStatus = 0);`

### :signal_strength: kariSerialBlueTooth
- `kariSerialBluetooth(T kariBT, String name = "kariBT");`
- `void isConnected(void(*callback)());`
- `void isDisconnected(void(*callback)());
- `void begin();`

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

### 7️⃣ **Basic Example: Use case of kariPID**
```cpp
#include <kari.h>
using namespace kari;

float correction = 0.00f;
float feedback = 50;
int k = 0;

kariPID pid(100, 0.5, 0.0001, 80);

void setup(){
    Serial.begin(9600);
}

void loop(){
    kariAsync::execute(
        [](){ 
            // in this example we are simulating possible real world system to show kariPID potential
            float correction = pid.evaluate(feedback);
            feedback += correction * 0.5f; 
            out << "Step" + String(k) + "- Correction: " + String(correction) + ", Feedback: " + String(feedback) << endl;
            k++;
        },
        100
    );

}
```

### 8️⃣ **Basic Example: Use case of kariDrive**
```cpp
#include <kari.h>
#include <ESP32Servo.h>
using namespace kari;

#define TRIG 21
#define ECHO 22
#define DIST 50

void checker();
void resetServo();


kariDrive *car;
kariUltrasonic *ultrasonic;
Servo servo;
unsigned int angle = 0;
int dir = 1;
bool isTurning = false;

void setup(){
  kariBegin({2, 4, 16, 17, 18, 19, 21, 22, 27});
  car = new kariDrive(2, 4, 16, 17, 18, 19);
  servo.attach(27);
  ultrasonic = new kariUltrasonic(TRIG, ECHO);
  servo.write(90);
}

void loop(){
  kariAsync::execute(
    [](){

      float distance = ultrasonic->measure();
      ultrasonic->onMeasure(DIST, DIST, checker);

      if ( distance > DIST && !isTurning){
        int degree = servo.read();
        if ( degree > 92){
          isTurning = true;
          car->right(90);
          car->left(200);
        }
        else if (degree >= 88 && degree <= 92)
          car->drive(230);
        else if (degree < 88) {
          isTurning = true;
          car->left(200);
          car->right(90);
        }
      }
    },
    100
  );

  kariAsync::execute(resetServo, 2000);

}

void checker(){

  if (angle >= 180 )
    dir = -1;

  if (angle <= 0 )
  dir = 1;

  angle += 10 * dir;
  servo.write(angle);
  
}

void resetServo(){
  if (isTurning){
  servo.write(90);
  isTurning = false;
  }
}
```

### 9️⃣ **Basic Example: Use case of kariSerialBlueTooth**
```cpp
#include <kari.h>
#include <kariBT.h>
#include <BluetoothSerial.h>
using namespace kari;
BluetoothSerial SerialBT;

enum class Data{
    KARI,
    OTHER
};

Data mapToEnum(String &mappedItem);
void dataCallback(String &data);
void connectCallback();

kariSerialBluetooth<BluetoothSerial> bt(SerialBT, "kari esp");

void setup(){
    Serial.begin(9600);
    out<<"Initializing bluetooth with kariBT" << endl << 45 << endl;
    bt.begin();
}

void loop(){

bt.isConnected(
    [](){ Serial.println("Connection callback");}
);

bt.listen(dataCallback);

bt.isDisconnected(
    [](){ Serial.println("Disconnected callback");}
);


}


void dataCallback(String &data){
    if (!data.isEmpty()){
        
        switch(mapToEnum(data)){
            case Data::KARI:
                Serial.println("Dream, visualize, Idealize and Implement");
                break;
            default:
                Serial.println(data);
        }
    }
    else
        Serial.println("...");

}

Data mapToEnum(String &mappedItem){
    mappedItem.trim();
    mappedItem.toLowerCase();

    if (mappedItem == "kari")
        return Data::KARI;
    else 
        return Data::OTHER;
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
[Kari Website](https://kari_IOT.netlify.app)