//
// Created by Sollyu on 2022/3/5.
//

#ifndef __ARDUINO_BUTTON_H_
#define __ARDUINO_BUTTON_H_

#include <Arduino.h>
#include <functional>

#ifndef __ARDUINO_BUTTON_CLICK_MIN_MILLIS_
#define __ARDUINO_BUTTON_CLICK_MIN_MILLIS_  130     // 点击一次最小间隔（主要为了去抖动）, 小于这个间隔的将被忽略
#endif

#ifndef __ARDUINO_BUTTON_LONG_CLICK_MILLS_
#define  __ARDUINO_BUTTON_LONG_CLICK_MILLS_ 1500    // 长按时间间隔
#endif

class ArduinoButton {
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
    ArduinoButton setOnClickListener(const std::function<void()> &listener);

    /**
     * 设置长按回调
     * @param listener
     * @return
     */
    ArduinoButton setOnLongClickListener(const std::function<void()> &listener);

private:
    enum ButtonStateEnum {
        PRESSED, RELEASED
    };


private:
    unsigned int mPin;

    std::function<void()> mClickListener = nullptr;

    std::function<void()> mLongClickListener = nullptr;

    ButtonStateEnum mButtonState = ButtonStateEnum::PRESSED;

private:
    volatile unsigned long mLoopLatestMillis = 0;
    volatile unsigned long mPressedMillis = 0;

private:
    const unsigned short int mButtonPressedFlag = HIGH;

private:
    void onLoopButtonPressed(unsigned long millis);

    void onLoopButtonReleased(unsigned long millis);

};


#endif //__ARDUINO_BUTTON_H_
