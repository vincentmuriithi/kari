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
            Serial.println("I come after 2 seconds buddy");
        }
    , 2000);

}


void callback1(){
    Serial.println("Distance is below 10");
}

void callback2(){
    Serial.println("Distance is above  50");
}

void asyncTest(){
    Serial.println("async function testing 1");
}
void wrapper(){

            Serial.println("Using kariAsync\n");

            Serial.println(kari::getDistance<kariUltrasonic>(ultra1));

            ultra1->measure();
            ultra1->onMeasure(10, 10, callback1);
            ultra1->onMeasure(50, 50, callback2, true);
            ultra1->onMeasure(10, 30,
            [](){
                Serial.println("Distance is between 20 and 30");
            }
            );
        }