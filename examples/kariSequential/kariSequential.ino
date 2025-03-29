#include <kari.h>
using namespace kari;


void setup(){
    Serial.begin(9600);
    kariBegin({8, 7, 6, 5});
}

void loop(){
    kariAsync::execute(
        [](){
            kariSequential({ {8, 7, 6, 5}, "sequential1"});
        },
        1500
    );
   
}