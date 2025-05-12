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

#ifndef KARIBT_H
#define KARIBT_H

#include <Arduino.h>

#if !defined(__AVR__)
#if defined(__KARI_SERIAL_BT__)

template <typename  T>
class kariSerialBluetooth{
    T kariBT;
    String name;
    String data;
    bool status;
    public:

    kariSerialBluetooth(T kariBT, String name = "kariBT");
    void isConnected(void(*callback)());
    void isDisconnected(void(*callback)());
    void begin();

    void write();
    String listen(void(*callback)(String &data));
    
};

#include "kari_espbluetooth.tpp"

#endif
#endif

#endif