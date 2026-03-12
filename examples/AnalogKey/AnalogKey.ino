#include <AnalogKey.h>
#include <Arduino.h>

const int16_t sigs[] = {1023, 925, 853, 787, 672, 632, 595, 562, 502, 479, 457, 437, 400, 322, 270, 231};
AnalogKey mx(0, sigs, sizeof(sigs) / sizeof(sigs[0]));

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