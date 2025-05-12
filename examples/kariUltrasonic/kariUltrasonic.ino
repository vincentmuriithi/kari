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
#define TRIG_PIN 8
#define ECHO_PIN 7
using namespace kari;

void callback1();
void callback2();
void asyncTest();
void wrapper();

kariUltrasonic *ultra1;



void setup(){
Serial.begin(9600);
ultra1 = new kariUltrasonic(TRIG_PIN, ECHO_PIN);
}


void loop(){
    kariAsync::execute(
       [](){
         
       },
        500
    );
    kariAsync::execute(wrapper, 1000);
    kariAsync::execute(
        [](){
            out << "I come after 2 seconds buddy" << endl;
            
            /* out is the kari equivalent of Serial.print and when used with endl its 
            equivalent to Serial.println hence both are the same.
            You can still use Serial.print or Serial.println but don't miss the fun of using the 
            kari out stream.
            */
        }
    , 2000);

}


void callback1(){
    out << "Distance is below 10" << endl;
}

void callback2(){
    out << "Distance is above  50" << endl;
}

void asyncTest(){
    out << "async function testing 1" << endl;
}
void wrapper(){

            out << "Using kariAsync" << endl;

            out << kari::getDistance<kariUltrasonic>(ultra1) << endl;

            ultra1->measure();
            ultra1->onMeasure(10, 10, callback1);
            ultra1->onMeasure(50, 50, callback2, true);
            ultra1->onMeasure(10, 30,
            [](){
                out << "Distance is between 20 and 30" << endl;
            }
            );
        }