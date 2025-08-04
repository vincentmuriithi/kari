/*
 * Copyright (c) 2025 Vincent Muriithi Karimi
 *
 * Kari Library - An Arduino Library for Asynchronous and Sensor-Based Applications
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Vincent Muriithi Karimi
 * Library: Kari
 * License: Apache License 2.0
 */


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