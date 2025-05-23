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

#ifndef KARI_H
#define KARI_H

// kari cells definitions go here 
#define __KARI_CELLS__
#define __KARI_SERIAL_BT__



#if !defined(__AVR__)
#include <type_traits>
#endif

#include <Arduino.h>
#if defined(__AVR__)
#include "./avr_deps/vector.h"
#else
#include <vector>
#endif

namespace kari{

class kariStream;
extern kariStream out;
    
struct Node{
    int data;
    Node *next;
};

struct EndlType{};
constexpr EndlType endl;

#if !defined(__AVR__)

#include <type_traits>

#else

template <bool Cond, typename T>
struct enable_if{};

template<typename T>
struct enable_if<true, T>{ 
    typedef T type;
    };

template <typename T>
struct is_member_object_pointer{
    static const bool value = false;
};

template <typename Class, typename Member>
struct is_member_object_pointer<Member Class::*>{
    static const bool value = true;
};

#endif

template<typename T, typename U>
#if !defined(__AVR__)
typename std::enable_if<std::is_member_object_pointer<U T::*>::value, U>::type
#else
typename kari::enable_if<kari::is_member_object_pointer<U T::*>::value, U>::type
#endif
getProperty(T &accessClass, U T::*property);

template<typename T, typename U>
#if !defined(__AVR__)
typename std::enable_if<std::is_member_object_pointer<U T::*>::value, U>::type
#else
typename kari::enable_if<kari::is_member_object_pointer<U T::*>::value, U>::type
#endif
getPropertyPtr(T *accessClass, U T::*property);

template<typename T, typename U = String>
int getClassProperty(U &data);

template<typename T, typename U = float>
U getDistance(T *accessClass);

struct Pins{
    std::vector<int> pins;
    const char *name;
};


template<typename T>
Node* createNode(Node *node, T &data);
void deleteNode(Node *node);
void kariPulse(Pins array);
void kariBegin(std::vector<int> pins, bool setAsInputs=false);
void kariSequential(Pins array);


class kariAsync{
private:

   struct kariTask{
    unsigned long int previous;
    void (*callback)();
   };

static std::vector<kariTask> kariTasks;
public:

    kariAsync() = delete;
    static void execute(void (*callback)(), unsigned int delay);

};


class kariPulse{
private:
    struct kariState{
        bool isHigh;
        char *name;
    };

    static std::vector<kariState> kariStates;
public:
    kariPulse() = delete;
    friend void kariPulse(Pins array);

};

class kariSequential{
private:
    struct pinRegister{
        unsigned int prevPin;
        unsigned int nextPin;
        unsigned int value;
        bool isHigh = true;
    };

    struct kariSequent{
        std::vector<pinRegister> pins;
        char* name;
    };

    static std::vector<kariSequent> kariSequents;
public:
    kariSequential() = delete;
    friend void kariSequential(Pins array);

};

class kariPID{
private:
    const float kp;
    const float ki;
    const float kd;
    const float setPoint;
    float error = 0.00f;
    float prevError = 0.00f;
    float integral = 0.00f;
    float derivative = 0.00f;
    long int previousTime = 0;
    long int currentTime = 0;
public:
    kariPID(const float setPoint, const float kp=0.00f, const float ki=0.00f, const float kd=0.00f);
    float evaluate(float feedBack);

};

class kariStream{
public:
    template<typename T>
    kariStream& operator<<(const T& value);
    kariStream& operator<<(const EndlType&);

};



}


class kariUltrasonic{
    private:
    int trigPin;
    int echoPin;
    static int num;
    static kari::Node *ultra;
    static kari::Node *current;
    static kari::Node *looper;
    unsigned long int duration = 0;
    float distance = 0.0f;
    static void traverseUltraNode(String status);
    public:
        kariUltrasonic(int trigPin, int echoPin);
        ~kariUltrasonic();
        float measure();
        static void measureMulti();
        int onMeasure(float lowerBound, float upperBound, void(*callback)(), bool triggerOnUpperBound=false);
        void attach();
        template<typename T, typename U>
        friend U kari::getProperty(T &accessClass, U T::*property);
        template<typename T, typename U>
        friend U kari::getPropertyPtr(T *accessClass, U T::*property);

        template<typename T, typename U>
        friend U kari::getDistance(T *accessClass);

        template<typename T, typename U>
        friend int kari::getClassProperty(U &data);


};

class kariPIR{
private:
    uint8_t signal;
public:
    kariPIR(int signal);
    void onMeasure(void(*callback)(), void(*fallbackCallback)() = 0);
    template<typename T, typename U>
    friend U kari::getProperty(T &accessClass, U T::*property);
    template<typename T, typename U>
    friend U kari::getProperty(T *accessClass, U T::*property);
};

class kariInfrared{
int signal;
public:
    kariInfrared(int signal);
    void onMeasure(void(*callback)());
    template<typename T, typename U>
    friend U kari::getProperty(T &accessClass, U T::*property);
    template<typename T, typename U>
    friend U kari::getProperty(T *accessClass, U T::*property);
};

class kariDrive{
    private:
    const int motor1_EN;
    const int motor1_InA;
    const int motor1_InB;

    const int motor2_EN;
    const int motor2_InA;
    const int motor2_InB;

    void accelerate(int speed);
    void changeover(bool value);
    void differentiate(int speedDifference, bool direction);

    public:
        kariDrive(const int motor1_EN, const int motor1_InA, const int motor1_InB, int motor2_EN, const int motor2_InA, const int motor2_InB);
        void drive(int speed = 100, bool directionStatus = 0);
        void right(int speed = 30, bool directionStatus = 0);
        void left(int speed = 30, bool directionStatus = 0);

};

#include "kariNamespace.tpp"

#endif 


