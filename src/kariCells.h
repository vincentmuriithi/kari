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

#ifndef KARI_CELLS_H
#define KARI_CELLS_H

#include <Arduino.h>

#if defined(__AVR__)
#include "./avr_deps/string"
#else
#include <string>
#endif

#if defined( __KARI_CELLS__)

template <typename T, typename U>
class kariTempSensor {
private:
    using Self = kariTempSensor&;
    using Callback = void(*)(float data);
    T oneWire;
    U sensor;
public:
    kariTempSensor(int signal);
    kariTempSensor(kariTempSensor&&) = delete;
    kariTempSensor(const kariTempSensor&&) = delete;
    kariTempSensor(kariTempSensor&) = delete;
    kariTempSensor(const kariTempSensor&) = delete;
    Self measure();
    Self onMeasureC(Callback);
    Self onMeasureF(Callback);


};

#if !defined(__AVR__)

template <typename T, typename U>
class kariGSheetClient{
    private:
    T gsheet;
    U response;
    U valueRange;
    using Self = kariGSheetClient&;
    using Callback = void(*)(String data);
    const char *client_email;
    const char * project_id;
    const char * private_key;
    const char * spreadsheet_id;
    String error_reason;
    String response_data;
    bool _isSuccess;
    bool _status = false;
    int elementCount{0}, _data{0};

    public:
    kariGSheetClient(T &gsheet, const char * client_email, const char * project_id, const char * private_key, const char * spreadsheet_id);
    Self setHeadings(std::initializer_list<std::string> headings);
    Self initialize(int = 10,const char* = "ROWS");
    template <typename dataType = String>
    Self attach(dataType);
    Self transmit();
    Self onSuccess(Callback);
    Self onError(Callback);
    explicit operator bool() const;
};

#endif

#include "kariCells.tpp"

#endif

#endif