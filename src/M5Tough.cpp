// Copyright (c) M5Tough. All rights reserved.

// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "M5Tough.h"

M5Tough::M5Tough() : _isInited(0)
{
#if defined ( ARDUINO_M5Stack_Core_ESP32 ) || defined ( ARDUINO_M5STACK_FIRE )

    _board = m5gfx::board_t::board_M5Stack;

#elif defined ( ARDUINO_M5STACK_Core2 )

    _board = m5gfx::board_t::board_M5StackCore2;

#elif defined ( ARDUINO_M5Stick_C )

    _board = m5gfx::board_t::board_M5StickC;

#elif defined ( ARDUINO_M5Stick_C_Plus )

    _board = m5gfx::board_t::board_M5StickCPlus;

#elif defined ( ARDUINO_M5Stack_CoreInk )

    _board = m5gfx::board_t::board_M5StackCoreInk;

#elif defined ( ARDUINO_M5STACK_Paper )

    _board = m5gfx::board_t::board_M5Paper;

#elif defined ( ARDUINO_M5STACK_TOUGH )

    _board = m5gfx::board_t::board_M5Tough;

#endif
}

void M5Tough::begin(bool LCDEnable, bool SDEnable, bool SerialEnable, bool I2CEnable)
{
    // Correct init once
    if (_isInited == true)
    {
        return;
    }
    else
    {
        _isInited = true;
    }

    // UART
    if (SerialEnable == true)
    {
        Serial.begin(115200);
        Serial.flush();
        delay(50);
        Serial.print("M5Tough initializing...");
    }

    Axp.begin();

    // LCD INIT
    if (LCDEnable == true)
    {
        Lcd.begin();
        _board = Lcd.getBoard();
    }

    // I2C init
    if (I2CEnable == true)
    {
        Wire.begin(32, 33);
    }

    // Touch init
    //Touch.begin(); // Touch begin after AXP begin. (Reset at the start of AXP)

    // Speaker init
    speaker.begin();

    // TF Card
    if (SDEnable == true)
    {
        SD.begin(TFCARD_CS_PIN, SPI, 40000000);
    }

    //touch.begin();

    // TONE

    if (SerialEnable == true)
    {
        Serial.println("OK");
    }

    Rtc.begin();
}

void M5Tough::update()
{

    //touch.read();
    //yield();
}

M5Tough M5;
