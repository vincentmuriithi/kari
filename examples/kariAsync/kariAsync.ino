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