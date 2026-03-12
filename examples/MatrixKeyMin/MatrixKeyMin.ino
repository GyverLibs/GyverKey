#include <Arduino.h>
#include <MatrixKey.h>

uint8_t rowPins[] = {9, 8, 7, 6};
uint8_t colPins[] = {5, 4, 3, 2};
MatrixKeyMin mx(rowPins, 4, colPins, 4);
const char* keys = "123A456B789C*0#D";

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (mx.tick()) {
        Serial.print(mx.key());
        Serial.print(": '");
        Serial.print(mx.key(keys));
        Serial.println("'");
    }
}