#include <kari.h>
using namespace kari;


void setup(){
    Serial.begin(9600);
    kariBegin({7,4,2});
}

void loop(){
    kariAsync::execute(
        [](){
            
            kariPulse({ {7, 4, 2}, "pulse1"});
        },
        1000
    );

}