#include <kari.h>
using namespace kari;

kariPIR *pir;
void setup(){
    kariBegin({7});
    pir = new kariPIR(8);
}


void loop(){
    kariAsync::execute(
        [](){
            pir->onMeasure(
                [](){ digitalWrite(7, HIGH); },
                [](){ digitalWrite(7, LOW); }
            );

        },10
    );
}