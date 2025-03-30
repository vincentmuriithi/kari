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


#include "kari.h"

namespace kari{

template<typename T, typename U>
#if !defined(__AVR__)
typename std::enable_if<std::is_member_object_pointer<U T::*>::value, U>::type
#else
typename kari::enable_if<kari::is_member_object_pointer<U T::*>::value, U>::type
#endif
getProperty(T &accessClass, U T::*property){
    return accessClass.*property;
}

template<typename T, typename U>
#if !defined(__AVR__)
typename std::enable_if<std::is_member_object_pointer<U T::*>::value, U>::type
#else
typename kari::enable_if<kari::is_member_object_pointer<U T::*>::value, U>::type
#endif
getPropertyPtr(T *accessClass, U T::*property){
    return accessClass->*property;
}

template<typename T, typename U>
int getClassProperty(U &data){
    if (strcmp(data, "num") == 0)
        return T::num;

    return (0);
}


template<typename T, typename U>
U getDistance(T *accessClass){
    return accessClass->distance;
}

template <typename T>
Node* createNode(Node *node, T &data){
    if (node == NULL){
        node = new Node;
        node->data = data;
        node->next = NULL;
        return node;
    }
    else
        return node;

}



}
