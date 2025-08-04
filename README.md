# Kari Library

[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/vincentmuriithi/library/Kari.svg)](https://registry.platformio.org/libraries/vincentmuriithi/Kari)

**Kari** is a lightweight and efficient Arduino library designed for asynchronous execution, sensor-based applications, and efficient pin control. It simplifies the integration of various sensors (like ultrasonic, PIR, and infrared) and supports asynchronous task management to improve performance.

## 📚 Table of Contents
- [📌 Features](#-features)
- [📥 Installation](#-installation)
- [🛠 API Reference](#-api-reference)
- [🔨 Usage](#-usage)
- [🧩 Modular Extensions: kariCells](#-modular-extensions-karicells)
- [📜 License](#-license)
- [✨ Author](#-author)
- [🌐 Website](#-website)


## 📌 Features
- ⚡ **Asynchronous Execution** – Non-blocking tasks in the `loop()` function.
- 🔧 **Sensor Support** – Includes helper functions for PIR, ultrasonic, and infrared sensors.
- 🔁 **Pulse and Sequential Execution** – Manage digital pin pulses and sequences easily.
- 🚀 **Optimized for AVR & Non-AVR Boards** – Compatible with a wide range of Arduino-compatible boards.

## 📥 Installation
To install the **Kari Library**:

1. **Download from Arduino Library Manager**
    - Open the Arduino IDE.
    - Go to Sketch > Include Library > Manage Libraries.
    - In the Library Manager, search for **`Kari`**.
    - Click **`Install`**

2. **Download from PlatformIO**
    - Using CLI command:
        ```bash
        pio pkg install --library  vincentmuriithi/kari
        ```
     Or:
        
    - Alternatively add the library to your project like this:
        ```ini
        lib_deps =
            vincentmuriithi/Kari
        ```
    - For specific library version e.g v1.2.0 you specify as follows:
        ```ini
        lib_deps =
            vincentmuriithi/Kari@^1.2.0
        ```
    - In platformIO you need to configure `kari` to use its static libraries accordingly as follows:
        ```ini
        build_flags =
            -I.pio/libdeps/YOUR_ENV/kari/src
            -L.pio/libdeps/YOUR_ENV/kari/src/YOUR_PLATFORM
            -lkari_YOUR_PLATFORM.a
        ```

     Replace:
     - YOUR_ENV with your environment (e.g., esp32dev, web, uno)
     - YOUR_PLATFORM with the architecture which are such as (esp32, esp8266, atmega328p, atmega2560, etc.)
     
    ### Example for ESP8266:
     ```ini
     build_flags =
        -ID:\Documents2\Arduino2\webServer\.pio\libdeps\web\kari\src
        -LD:\Documents2\Arduino2\webServer\.pio\libdeps\web\kari\src\esp8266
        -lkari_esp8266.a
     ```

    ⚠️ Note that for the following  ESP32-family boards (ESP32, ESP32-S2, ESP32-S3):
    All use the same static library file `-lkari_esp32.a`.
    The **-I** path always remains:
     ```ini
        -I.pio/libdeps/YOUR_ENV/kari/src
     ```

    Only the -L path changes to match the board variant subfolder:
     ```ini
        -L.pio/libdeps/YOUR_ENV/kari/src/esp32     ; for ESP32
        -L.pio/libdeps/YOUR_ENV/kari/src/esp32s2   ; for ESP32-S2
        -L.pio/libdeps/YOUR_ENV/kari/src/esp32s3   ; for ESP32-S3
     ```
     

3. **Download from GitHub**
   - Go to the [Kari GitHub Repository](https://github.com/vincentmuriithi/kari) or [Kari Website](https://kariIOT.netlify.app).
   - Download the `.zip` file of the latest release.

4. **Manual Installation**
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
- `Self isConnected(void(*callback)());`
- `Self isDisconnected(void(*callback)());`
- `Self initialize();`

 *Here `Self` is used to mean `kariSerialBlueTooth&` which is a reference to object which allows for method chaining.*

### 📲 kariMonClient
- `static void parse(String &);`
- `static void onCommand(Callback, const char*);`
- `static void onTiltControls(Callback, Controls);`
- `static void onJoyStickControls(Callback, Controls);`
- `static void onBlue(void (*callback)(), bool offState = false);`
- `static void onRed(void (*callback)(), bool offState = false);`
- `static void onGreen(void (*callback)(), bool offState = false);`
- `static void onToggle0(void (*callback)(), bool offState = false);`
- `static void onToggle1(void (*callback)(), bool offState = false);`
- `static void onToggle2(void (*callback)(), bool offState = false);`
- `static void onToggle3(void (*callback)(), bool offState = false);`
- `static void onToggle4(void (*callback)(), bool offState = false);`
- `static void onToggle5(void (*callback)(), bool offState = false);`
- `static void onToggle6(void (*callback)(), bool offState = false);`
- `static void onToggle7(void (*callback)(), bool offState = false);`
- `static void onToggle8(void (*callback)(), bool offState = false);`
- `static void onToggle9(void (*callback)(), bool offState = false);`

### 📄 kariGSheetClient
- `template <typename T, typename U>`
  `kariGSheetClient(T &gsheet, const char * client_email, const char * project_id, const char * private_key, const char * spreadsheet_id);`
- `Self setHeadings(std::initializer_list<std::string> headings);`
- `Self initialize(int = 10,const char* = "ROWS");`
- `template <typename dataType = String>`
  `Self attach(dataType);`
- `Self transmit();`
- `Self onSuccess(Callback);`
- `Self onError(Callback);`

 *Here `Self` is used to mean `kariGSheetClient&` which is a reference to object which allows for method chaining.*

### :joystick: kariJoyStick
- `kariJoyStick(int vrx, int vry, int sw, int sensitivity = 10, int threshold = 512);`
- `kariJoyStick(kariJoyStick&) = delete;`
- `kariJoyStick(const kariJoyStick&) = delete;`
- `kariJoyStick(kariJoyStick&&) = delete;`
- `kariJoyStick(const kariJoyStick&&) = delete;`
- `Self onX(Callback, bool = false) const;`
- `Self onY(Callback, bool = false) const;`

 *Here `Self` is used to mean `kariJoyStick&` which is a reference to object which allows for method chaining.*

### :thermometer: kariTempSensor
- `template <typename T, typename U>`
  `kariTempSensor(int signal);`
- `Self measure();`
- `Self onMeasureC(void(*)(float data));`
- `Self onMeasureF(void(*)(float data));`

 *Here `Self` is used to mean `kariTempSensor&` which is a reference to object which allows for method chaining.*

### 🅱️ kariHCBluetooth
- `kariHCBluetooth(int tx, int rx, int state = -1, int enable = -1);`
- `Self initialize(bool commandMode = false);`
- `Self listen(listenCallback);`
- `template <typename T = String>`
- `Self send(T);`
- `Self isConnected(Callback);`
- `Self isDisconnected(Callback);`

 *Here `Self` is used to mean `kariHCBluetooth&` which is a reference to object which allows for method chaining.*

### 🌊🧪 kariPH
- `kariPH(int signal, int iterationCount= 10);`
- `Self getRaw(bool = true);`
- `Self measure();`
- `Self onMeasure(Callback);`

 *Here `Self` is used to mean `kariPH&` which is a reference to object which allows for method chaining.*

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
    bt.initialize();
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

### 🔟 **Basic Example: Use case of kariMonClient**
```cpp
#include <kari.h>
#include <kariBT.h>
#include <kariMonClient.h>
#include <BluetoothSerial.h>
using namespace kari;

void register_colorCommands();
void register_toggleCommands();
void register_kariMonClient();
void register_customCommands();

BluetoothSerial serialBT;

kariSerialBluetooth<BluetoothSerial> bt(serialBT, "kari_esp");

void setup(){
Serial.begin(9600);
register_kariMonClient();
bt.initialize();
out << "Connecting to Bluetooth..." << endl; 
}


void loop(){
    bt
    .isConnected([](){
        out << "Connected to kariMon IoT App" << endl;
    })
    .listen([](String &data){
        out << data << endl;
        kariMonClient::parse(data);
    })
    .isDisconnected([](){
        out << "Bluetooth disconnected!" << endl;
    });

    kariAsync::execute([](){
        bt.send("Hello from kariMonClient");
    },1000);

}


void register_kariMonClient(){
    register_colorCommands();
    register_toggleCommands();
    register_customCommands();

    kariMonClient::onJoyStickControls([](){
        out << "REVERSE command received" << endl;
    }, Controls::REVERSE);

    kariMonClient::onJoyStickControls([](){
        out << "FORWARD command received" << endl;
    }, Controls::FORWARD);
}


void register_colorCommands(){
    kariMonClient::onBlue([](){
        out << "Blue on signal received" << endl;
    });
    kariMonClient::onBlue([](){
        out << "Blue off signal received" << endl;
    }, true);
    kariMonClient::onRed([](){
        out << "Red on signal received" << endl;
    });
    kariMonClient::onRed([](){
        out << "Red off signal received" << endl;
    }, true);
    kariMonClient::onGreen([](){
        out << "Green on signal received" << endl;
    });
    kariMonClient::onGreen([](){
out << "Green off signal received" << endl;
    }, true);
}
void register_toggleCommands(){
    kariMonClient::onToggle0([](){
        out << "Toggle0 on signal received" << endl;
    });
    kariMonClient::onToggle0([](){
        out << "Toggle0 off signal received" << endl;
    }, true);
    kariMonClient::onToggle1([](){
        out << "Toggle1 on signal received" << endl;
    });
    kariMonClient::onToggle1([](){
        out << "Toggle1 off signal received" << endl;
    }, true);
    kariMonClient::onToggle2([](){
        out << "Toggle2 on signal received" << endl;
    });
    kariMonClient::onToggle2([](){
        out << "Toggle2 off signal received" << endl;
    }, true);
    kariMonClient::onToggle3([](){
        out << "Toggle3 on signal received" << endl;
    });
    kariMonClient::onToggle3([](){
        out << "Toggle3 off signal received" << endl;
    }, true);
}


void register_customCommands(){
    kariMonClient::onCommand([](){
        out << "hello there, how may i help you?" << endl;
    }, "hello");
}
```

### #️⃣ **Basic Example: Use case of kariGSheetClient**
```cpp
#include <kari.h>
#include <kariCells.h>
#include <ESP_Google_Sheet_Client.h>
#include <WiFi.h>
// Use #include <ESP8266WiFi.h> for esp8266 boards
using namespace kari;

const char* ssid = "your ssid";
const char* password = "your password";
const char* client_email = "your client email";
const char* project_id = "your project_id";
const char* spreadsheet_id = "your spreadsheet id";
const char* private_key = "your private_key";

kariGSheetClient<ESP_Google_Sheet_Client, FirebaseJson> google(GSheet, client_email, project_id, private_key, spreadsheet_id);
int itemCount{1};

void setup(){
Serial.begin(9600);
WiFi.setAutoConnect(true);
WiFi.begin(ssid, password);

while(WiFi.status() != WL_CONNECTED){
    kariAsync::execute([](){
        out << ". ";
    }, 400);
}

out << "Connected to: " << WiFi.localIP() << endl;
if (!google) out << "kariGSheet instance is not ready" << endl;
google.initialize();
if (google) out << "kariGSheet instance is ready" << endl;
google.setHeadings({"Country", "Profession", "Name", "Count", "Library"});
}


void loop(){
    kariAsync::execute([](){
        google.attach("Kenya")
        .attach("Engineering")
        .attach("Vincent")
        .attach<int>(itemCount)
        .attach("Kari")
        .transmit()
        .onSuccess([](String response){
            out << "Success" << response << endl;
            itemCount++;
        })
        .onError([](String error){
            out << error << endl;
        });
    }, 1000);
}
```

### #️⃣ **Basic Example: Use case of kariJoyStick**
```cpp
#include <kari.h>
using namespace kari;

kariJoyStick joystick(A0, A1, 8, 500);
void setup(){
Serial.begin(9600);
out << "JoyStick Example" << endl;
}

void loop(){
joystick

.onX([](float &_x){
    out << _x << endl;
})

.onY([](float &_y){
    out << _y << endl;
});
}
```

### #️⃣ **Basic Example: Use case of kariTempSensor**
```cpp
#include <kari.h>
#include <kariCells.h>
#include <OneWire.h>
#include <DallasTemperature.h>
using namespace kari;

// must use a pointer since kariTempConstructor calls methods which needs to be in setup
kariTempSensor<OneWire, DallasTemperature> *temp;

void setup(){
Serial.begin(9600);
temp = new kariTempSensor<OneWire, DallasTemperature>(8);
}

void loop(){
    kariAsync::execute([](){
        temp
    ->measure()
    .onMeasureC([](float data){
        out << "Temperature in degrees celcius: " << data << endl;
    })
    .onMeasureF([](float data){
        out << "Temperature in Farenheits: " << data << endl;
    });
    }, 2000);
}
```
### #️⃣ **Basic Example: Use case of kariHCBluetooth**
```cpp
#include <kari.h>
#include <kariMonClient.h>
using namespace kari;

kariHCBluetooth hc(0, 1);

void setup(){
Serial.begin(9600);
hc.initialize();
}


void loop(){
    hc.listen([](String &data){
        out << data << endl;
    });

    kariAsync::execute([](){
        hc.send("Hello to the world");
    }, 1500);

}
```

### #️⃣ **Basic Example: Use case of kariTempSensor**
```cpp
#include <kari.h>
using namespace kari;

kariPH ph(A0);

void setup(){
Serial.begin(9600);
out << "kariPH example sketch" << endl;
}


void loop(){
    kariAsync::execute([](){
        ph
        .measure()
        .onMeasure([](float &phData){
            out << phData << endl;
    });

    }, 1500);
}
```

## 🧩 Modular Extensions: `kariCells`
A **`kariCell`** is a modular component in the **Kari** library ecosystem that wraps other Arduino libraries to provide enhanced functionality. `kariCells` allow you to easily extend Kari’s capabilities while keeping the core lightweight.
- `kariCells` are **not automatically included** when importing the main `kari.h` header.
- Some `kariCells` have their own header files, while others are included through a shared `kariCells.h` file.
- They depend on the **core `kari` library** to function correctly.
- First introduced in **Kari v1.1.0**, `kariCells` are ideal for plug-and-play integration with existing ecosystems like Bluetooth, temperature sensors, and more.

### ✅ Example `kariCells`

- `kariSerialBluetooth` – wraps `BluetoothSerial`
- `kariTempSensor` – wraps `OneWire` and `DallasTemperature`
- `kariGSheetClient` – wraps `ESP_Google_Sheet_Client`

## 📜 License
This library is licensed under the Apache License 2.0.
See the full license here: [Apache-2.0 License.](https://opensource.org/licenses/Apache-2.0)

## ✨ Author
**Vincent Muriithi Karimi**  
GitHub: [vincentmuriithi](https://github.com/vincentmuriithi)  
Email: kari.clientdesk@gmail.com 

## 🌐 Website
For more information about **Kari** and updates, visit:  
[Kari Website](https://kari_IOT.netlify.app)