#include <Arduino.h>
#include <MatrixKey.h>

uint8_t rowPins[] = {9, 8, 7, 6};
uint8_t colPins[] = {5, 4, 3, 2};
MatrixKey mx(rowPins, 4, colPins, 4);

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (mx.tick()) {
        if (mx.click()) {
            Serial.print("click: ");
            Serial.println(mx.key());
        }
        if (mx.hold()) {
            Serial.print("hold: ");
            Serial.println(mx.key());
        }
        if (mx.step()) {
            Serial.print("step: ");
            Serial.println(mx.key());
        }
    }
}