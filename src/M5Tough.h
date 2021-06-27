// Copyright (c) M5Tough. All rights reserved.

// Licensed under the MIT license. See LICENSE file in the project root for full license information.
/**
 * \par Copyright (C), 2020-2021, M5Tough
 * \class M5Tough
 * \brief   M5Tough library.
 * @file    M5Tough.h
 * @author  M5Tough
 * @version V0.0.1 Beta
 * @date    2021/06/25
 * @brief   Header for M5Tough.cpp module
 *
 * \par Description
 * This file is a drive for M5Tough.
 *
 * \par Method List:
 *
 *  System:
        M5.begin();
    LCD:
        M5.lcd.setBrightness(uint8_t brightness);
        M5.Lcd.drawPixel(int16_t x, int16_t y, uint16_t color);
        M5.Lcd.drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
        M5.Lcd.fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        M5.Lcd.fillScreen(uint16_t color);
        M5.Lcd.drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        M5.Lcd.drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color);
        M5.Lcd.fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        M5.Lcd.fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,int16_t delta, uint16_t color);
        M5.Lcd.drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        M5.Lcd.fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        M5.Lcd.drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
        M5.Lcd.fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
        M5.Lcd.drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
        M5.Lcd.drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h),
        M5.Lcd.drawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size);
        M5.Lcd.setCursor(uint16_t x0, uint16_t y0);
        M5.Lcd.setTextColor(uint16_t color);
        M5.Lcd.setTextColor(uint16_t color, uint16_t backgroundcolor);
        M5.Lcd.setTextSize(uint8_t size);
        M5.Lcd.setTextWrap(boolean w);
        M5.Lcd.printf();
        M5.Lcd.print();
        M5.Lcd.println();
        M5.Lcd.drawCentreString(const char *string, int dX, int poY, int font);
        M5.Lcd.drawRightString(const char *string, int dX, int poY, int font);
        M5.Lcd.drawJpg(const uint8_t *jpg_data, size_t jpg_len, uint16_t x, uint16_t y);
        M5.Lcd.drawJpgFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);
        M5.Lcd.drawBmpFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);

 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * lovyan03          2021/06/25         0.0.1          Rebuild the new.
 * </pre>
 *
 */


#ifndef _M5Tough_H_
#define _M5Tough_H_

#if defined(ESP32)

 #if defined (ARDUINO)
  #include <Arduino.h>
  #include <Wire.h>
  #include <SPI.h>
  #include "FS.h"
  #include "SD.h"
 #endif

  #include <M5GFX.h>
  #include "utility/Config.h"
  #include "utility/Speaker.h"
  #include "utility/Touch.h"
  #include "utility/AXP192.h"
  #include "utility/RTC.h"

  class M5Tough
  {
    public:
      M5Tough();
      void begin(bool LCDEnable = true, bool SDEnable = true, bool SerialEnable = true, bool I2CEnable = false);
      void update();

      M5GFX Lcd;
      
      AXP192 Axp;

//      Touch touch;

      Speaker speaker;

      RTC  Rtc;

      //void setPowerBoostKeepOn(bool en) __attribute__((deprecated));
      //void setWakeupButton(uint8_t button) __attribute__((deprecated));
      //void powerOFF() __attribute__((deprecated));
    private:
      m5gfx::board_t _board;
      bool _isInited;
  };

  extern M5Tough M5;
#else
  #error “This library only supports boards with ESP32 processor.”
#endif
#endif
