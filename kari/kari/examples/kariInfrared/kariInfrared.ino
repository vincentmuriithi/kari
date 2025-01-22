#include <kari.h>

using namespace kari;

int pin = 5;
kariInfrared *irSensor;

void onDetection() {
    Serial.println("Infrared signal detected!");
}

void setup() {
    Serial.begin(9600);
    kariBegin({pin});
    irSensor = new kariInfrared(pin); // Initialize infrared sensor on pin 5
}

void loop() {
    kariAsync::execute(
    [] () {
        irSensor->onMeasure(onDetection); // Check for infrared signal continuously
    },
    100
    );
}

    