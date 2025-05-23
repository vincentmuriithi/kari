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

#include "kariBT.h"


template <typename T>
kariSerialBluetooth<T>::kariSerialBluetooth(T kariBT, String name): name(name), kariBT(kariBT) {}

template <typename T>
void kariSerialBluetooth<T>::begin(){
  this->kariBT.begin(this->name, false);
}

template <typename T>
String kariSerialBluetooth<T>::listen(void(*callback)(String &data)){

    if (this->kariBT.available()){

      this->data = this->kariBT.readString();
      callback(this->data);
      return this->data;
    }
    return "";
  }

template <typename T>
void kariSerialBluetooth<T>::isConnected(void(*callback)()){
  if (this->kariBT.hasClient() && this->status == false){
    this->status = true;
    callback();
  }
}

template <typename T>
void kariSerialBluetooth<T>::isDisconnected(void(*callback)()){
  if (!this->kariBT.hasClient() && this->status == true){
    this->status = false;
    callback();
  }
}