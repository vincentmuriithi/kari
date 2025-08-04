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