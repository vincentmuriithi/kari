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