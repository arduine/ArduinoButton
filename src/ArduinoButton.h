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

#ifndef __ARDUINO_BUTTON_H_
#define __ARDUINO_BUTTON_H_

#include <Arduino.h>

#ifndef __ARDUINO_BUTTON_CLICK_MIN_MILLIS_
#define __ARDUINO_BUTTON_CLICK_MIN_MILLIS_  130     // 点击一次最小间隔（主要为了去抖动）, 小于这个间隔的将被忽略
#endif

#ifndef __ARDUINO_BUTTON_LONG_CLICK_MILLS_
#define __ARDUINO_BUTTON_LONG_CLICK_MILLS_ 1300    // 长按时间间隔
#endif


class ArduinoButton {
public:
    typedef void(*ArduinoButtonListener)();

public:
    /**
     * 构造函数
     * @param pin   按钮控制引脚
     * @param mode  按钮输入模式
     * @param flag  按钮被按下的标记
     * @since 1.0.0
     */
    explicit ArduinoButton(unsigned int pin, unsigned short mode = INPUT_PULLUP, unsigned short flag = LOW);

public:
    void loop();

public:
    /**
     * 设置点击回调
     * @param listener
     * @since 1.0.0
     */
    ArduinoButton setOnClickListener(ArduinoButtonListener listener);

    /**
     * 设置长按回调
     * @param listener
     * @return
     */
    ArduinoButton setOnLongClickListener(ArduinoButtonListener listener);

private:
    enum ButtonStateEnum {
        PRESSED, RELEASED
    };


private:
    unsigned int mPin;

    ArduinoButtonListener mClickListener = nullptr;

    ArduinoButtonListener mLongClickListener = nullptr;

    ButtonStateEnum mButtonState = ButtonStateEnum::PRESSED;

private:
    /**
     * loop函数上次执行的时间
     * @since 1.0.0
     */
    volatile unsigned long mLoopLatestMillis = 0;

    /**
     * 当前按钮被下的时间
     * @since 1.0.0
     */
    volatile unsigned long mPressedMillis = 0;

private:
    /**
     * 按钮按下时的标记
     * @since 1.0.0
     */
    const unsigned short int mButtonPressedFlag = HIGH;

    /**
     * 是否初始化
     */
    bool mIsJustInit = true;

private:
    void onLoopButtonPressed(unsigned long millis);

    void onLoopButtonReleased(unsigned long millis);

};


#endif //__ARDUINO_BUTTON_H_
