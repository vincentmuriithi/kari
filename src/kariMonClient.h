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

#ifndef KARIMON_CLIENT_H
#define KARIMON_CLIENT_H

#include <Arduino.h>
#include "kariUtills.h"

#if defined(__AVR__)
#include "./avr_deps/map"
#include "./avr_deps/string"
#else
#include <map>
#include <string>
#endif

class kariMonClient;

#define GENERATE_METHOD(NAME) \
static void on##NAME(void (*callback)(), bool offState = false); 

#define CALLBACK_HANDLER(NAME, KEY1, KEY2) \
void kariMonClient::on##NAME(void (*callback)(), bool offState) {\
    if (!callback) return; \
    if (!offState){ \
         _myMap[#KEY1] = callback; \
    } else{ \
     _myMap[#KEY2] = callback; \
    } \
}

enum class Controls {
    FORWARD,
    REVERSE,
    LEFT_REVERSE,
    RIGHT_REVERSE,
    LEFT_FORWARD,
    RIGHT_FORWARD,
    STOP,
    T_FORWARD,
    T_REVERSE,
    T_LEFT_REVERSE,
    T_RIGHT_REVERSE,
    T_LEFT_FORWARD,
    T_RIGHT_FORWARD,
    T_STOP
};




class kariMonClient{
private:
using Callback = void(*)();
static std::map<std::string, void(*)()> _myMap;
public:
    kariMonClient() = delete;
    static void parse(const String &);
    static void onCommand(Callback, const char*);
    static void onTiltControls(Callback, Controls);
    static void onJoyStickControls(Callback, Controls);
    GENERATE_METHOD(Blue)
    GENERATE_METHOD(Green)
    GENERATE_METHOD(Red)
    GENERATE_METHOD(Toggle1)
    GENERATE_METHOD(Toggle2)
    GENERATE_METHOD(Toggle3)
    GENERATE_METHOD(Toggle4)
    GENERATE_METHOD(Toggle5)
    GENERATE_METHOD(Toggle6)
    GENERATE_METHOD(Toggle7)
    GENERATE_METHOD(Toggle8)
    GENERATE_METHOD(Toggle9)
    GENERATE_METHOD(Toggle0)
    
};

#endif // KARIMON_CLIENT_H