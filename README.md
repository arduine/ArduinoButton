# ArduinoButton

## 说明

一个几乎支持全部Arduino的按钮点击事件库。

> ⚠️ 注意：
>
> 有些板子的IO对输入模式不支持，比如ESP32的`GPIO_34`、`GPIO_35`。
>
> 在使用库的时候请查使用的IO接口是否支持输入模式。
>

## 导入

#### PlatformIO

```text
; Library options
lib_deps =
    https://github.com/arduine/ArduinoButton.git#main
```

#### ArduinoIDE

TODO

## 使用

1. 增加头文件导入：

```c++
#include <Arduino.h>
```

2. 声明变量并设置回调

```c++
ArduinoButton sTestButton(14, INPUT_PULLUP, LOW);

/* 设置点击事件回调 */
sTestButton.setOnClickListener(...);

/* 设置长按事件回调（默认按住1.5秒） */
sTestButton.setOnLongClickListener(...);
```

3. 增加LOOP函数

```c++
void loop() {
    sTestButton.loop(); // <--- 调用按钮的loop函数
}
```

## 进阶

1. 重新定义宏`__ARDUINO_BUTTON_CLICK_MIN_MILLIS_`可调整去抖动的时间。默认：130ms
2. 重新定义宏`__ARDUINO_BUTTON_LONG_CLICK_MILLS_`可调长按触发的时间。默认：1.5s

## LICENSE

```text
                                 Apache License
                           Version 2.0, January 2004
                        http://www.apache.org/licenses/

   TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION
```