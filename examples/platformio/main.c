/*
 * Copyright (C) 2022. sollyu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Arduino.h>
#include <ArduinoButton.h>

static ArduinoButton sTestButton(DD2, INPUT_PULLUP, LOW);

void onButtonClick() {
    digitalWrite(DD3, digitalRead(DD3) == HIGH ? LOW : HIGH);
}

void onButtonLongClick() {
    digitalWrite(DD4, digitalRead(DD4) == HIGH ? LOW : HIGH);
}

void setup() {
    pinMode(DD3, OUTPUT);
    pinMode(DD4, OUTPUT);
    digitalWrite(DD3, LOW);
    digitalWrite(DD4, LOW);

    sTestButton.setOnClickListener(onButtonClick);
    sTestButton.setOnLongClickListener(onButtonLongClick);
}

void loop() {
    sTestButton.loop();
}