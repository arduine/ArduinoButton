//
// Created by Sollyu on 2022/3/5.
//

#include <Arduino.h>

#include <ArduinoButton.h>

ArduinoButton sTestButton(14, INPUT_PULLUP, LOW);

void onButtonClick() {
    Serial.printf("[*] button click %lu\n", millis());
}

void setup() {
    Serial.begin(115200);
    sTestButton.setOnClickListener(onButtonClick);
    sTestButton.setOnLongClickListener([] {
        Serial.printf("[*] button long click %lu\n", millis());
    });
}

void loop() {
    sTestButton.loop();
}
