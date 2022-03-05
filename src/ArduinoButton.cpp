//
// Created by Sollyu on 2022/3/5.
//

#include "ArduinoButton.h"

ArduinoButton::ArduinoButton(const unsigned int pin, unsigned short mode, unsigned short flag) : mPin(pin), mButtonPressedFlag(flag) {
    pinMode(mPin, mode);
}

void ArduinoButton::loop() {
    const unsigned long _millis = millis();
    if (_millis - mLoopLatestMillis <= __ARDUINO_BUTTON_CLICK_MIN_MILLIS_)
        return;
    mLoopLatestMillis = _millis;

    if (digitalRead(mPin) == mButtonPressedFlag)
        onLoopButtonPressed(_millis);
    else
        onLoopButtonReleased(_millis);
}

void ArduinoButton::onLoopButtonPressed(const unsigned long millis) {
    if (mButtonState == ButtonStateEnum::PRESSED)
        return;
    mButtonState = ButtonStateEnum::PRESSED;
    mPressedMillis = millis;
}

void ArduinoButton::onLoopButtonReleased(const unsigned long millis) {
    if (mButtonState == ButtonStateEnum::RELEASED)
        return;

    mButtonState = ButtonStateEnum::RELEASED;
    if (millis - mPressedMillis >= __ARDUINO_BUTTON_LONG_CLICK_MILLS_) {
        if (mLongClickListener != nullptr) mLongClickListener();
    } else if (mClickListener != nullptr) {
        mClickListener();
    }
}

ArduinoButton ArduinoButton::setOnClickListener(const std::function<void()> &listener) {
    mClickListener = listener;
    return *this;
}

ArduinoButton ArduinoButton::setOnLongClickListener(const std::function<void()> &listener) {
    mLongClickListener = listener;
    return *this;
}

