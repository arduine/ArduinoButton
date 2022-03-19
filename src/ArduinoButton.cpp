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

#include "ArduinoButton.h"

ArduinoButton::ArduinoButton(const unsigned int pin, unsigned short mode, unsigned short flag) : mPin(pin), mButtonPressedFlag(flag) {
    pinMode(mPin, mode);
}

void ArduinoButton::loop() {
    const unsigned long _millis = millis();
    if (_millis - mLoopLatestMillis <= __ARDUINO_BUTTON_CLICK_MIN_MILLIS_)
        return;
    mLoopLatestMillis = _millis;

    if (digitalRead(mPin) == (int)mButtonPressedFlag)
        onLoopButtonPressed(_millis);
    else
        onLoopButtonReleased(_millis);
}

void ArduinoButton::onLoopButtonPressed(const unsigned long millis) {
    mIsJustInit = false;
    if (mButtonState == ButtonStateEnum::PRESSED)
        return;
    mButtonState   = ButtonStateEnum::PRESSED;
    mPressedMillis = millis;
}

void ArduinoButton::onLoopButtonReleased(const unsigned long millis) {
    if (mIsJustInit)
        return;

    if (mButtonState == ButtonStateEnum::RELEASED)
        return;

    mButtonState = ButtonStateEnum::RELEASED;
    if (millis - mPressedMillis >= __ARDUINO_BUTTON_LONG_CLICK_MILLS_) {
        if (mLongClickListener != nullptr)
            mLongClickListener();
        else if (mClickListener != nullptr)
            mClickListener();
    } else if (mClickListener != nullptr) {
        mClickListener();
    }
}

ArduinoButton ArduinoButton::setOnClickListener(ArduinoButtonListener listener) {
    mClickListener = listener;
    return *this;
}

ArduinoButton ArduinoButton::setOnLongClickListener(ArduinoButtonListener listener) {
    mLongClickListener = listener;
    return *this;
}


