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
#include <ESP32Servo.h>
using namespace kari;

#define TRIG 21
#define ECHO 22
#define DIST 50

void checker();
void resetServo();


kariDrive *car;
kariUltrasonic *ultrasonic;
Servo servo;
unsigned int angle = 0;
int dir = 1;
bool isTurning = false;

void setup(){
  kariBegin({2, 4, 16, 17, 18, 19, 21, 22, 27});
  car = new kariDrive(2, 4, 16, 17, 18, 19);
  servo.attach(27);
  ultrasonic = new kariUltrasonic(TRIG, ECHO);
  servo.write(90);
}

void loop(){
  kariAsync::execute(
    [](){

      float distance = ultrasonic->measure();
      ultrasonic->onMeasure(DIST, DIST, checker);

      if ( distance > DIST && !isTurning){
        int degree = servo.read();
        if ( degree > 92){
          isTurning = true;
          car->right(90);
          car->left(200);
        }
        else if (degree >= 88 && degree <= 92)
          car->drive(230);
        else if (degree < 88) {
          isTurning = true;
          car->left(200);
          car->right(90);
        }
      }
    },
    100
  );

  kariAsync::execute(resetServo, 2000);

}


void checker(){

  if (angle >= 180 )
    dir = -1;

  if (angle <= 0 )
  dir = 1;

  angle += 10 * dir;
  servo.write(angle);
  
}

void resetServo(){
  if (isTurning){
  servo.write(90);
  isTurning = false;
  }
}
