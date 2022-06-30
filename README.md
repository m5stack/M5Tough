# M5Tough Library

English | [中文](README_cn.md)

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/tough/tough_01.webp" alt="M5Tough_P1" width="350" height="350">

* **For the Detailed documentation of M5Tough, please [Click here](https://docs.m5stack.com/en/core/tough)**

* **In order to buy M5Tough，please [Click here](https://shop.m5stack.com/collections/m5-controllers/products/m5stack-tough-esp32-iot-development-board-kit)**

## Description

**M5Tough** is the second generation core device in the M5Stack development kit series, which further enhances the functions of the original generation of cores. 

The MCU is an ESP32 model D0WDQ6-V3 and has dual core Xtensa® 32-bit 240Mhz LX6 processors that can be controlled separately. WiFi and Bluetooth are supported as standard and it includes an on board 16MB Flash and 8MB PSRAM, USB TYPE-C interface for charging, downloading of programs and serial communication, a 2.0-inch integrated capacitive touch screen, and a built-in vibration motor. 

M5Tough also features a built-in RTC module which can provide accurate timing. The power supply is managed by an AXP192 power management chip, which can effectively control the power consumption of the base and a built-in green LED power indicator helps to notify the user of battery level. The battery capacity has been upgraded to 390mAh, which can power the core for much longer than the previous model. 

The M5Tough retains the SD card slot and speakers. However, in order to ensure higher quality sound output, the I2S digital audio interface power amplifier chip is used to effectively prevent signal distortion. There are independent power and reset buttons on the left side and bottom of the base. 

The 3 icons on the front of the screen are capacitive buttons which are programmable.

## PinMap

**LCD & TF card**

LCD ：320x240
TF card Maximum size 16GB

| ESP32 Chip  | GPIO38 | GPIO23 | GPIO18 | GPIO5 | GPIO15 |          |           |           |
| ----------- | ------ | ------ | ------ | ----- | ------ | -------- | --------- | --------- |
| AXP192 Chip |        |        |        |       |        | AXP\_IO4 | AXP\_LDO3 | AXP\_LDO2 |
| ILI9342C    | MISO   | MOSI   | SCK    | CS    | DC     | RST      | BL        | PWR       |


| ESP32 Chip | GPIO38 | GPIO23 | GPIO18 | GPIO4 |
| ---------- | ------ | ------ | ------ | ----- |
| TF Card    | MISO   | MOSI   | SCK    | CS    |

**CAP.TOUCH**

| ESP32 chip | GPIO21 | GPIO22 | GPIO39 |          |
| ---------- | ------ | ------ | ------ | -------- |
| AXP192     |        |        |        | AXP\_IO4 |
| CHSC6540   | SDA    | SCL    | INT    | RST      |



**NS4168**

| ESP32 Chip | GPIO12 | GPIO0 | GPIO2 | AXP\_IO2 |
| ---------- | ------ | ----- | ----- | -------- |
| NS4168     | BCLK   | LRCK  | DATA  | SPK\_EN  |



**AXP Control**

| AXP192     | AXP\_IO1 | AXP\_IO2 | AXP\_IO4 | AXP\_LDO3 |
| ---------- | -------- | -------- | -------- | --------- |
| TouchPanel | RST      |          |          |           |
| SPEAKER    |          | EN       |          |           |
| LCD        |          |          | RST      | backright |


**RTC**

| ESP32 Chip | GPIO21 | GPIO22 |          |
| ---------- | ------ | ------ | -------- |
| AXP192     |        |        | AXP\_PWR |
| BM8563     | SDA    | SCL    | INT      |



**USB to serial chip**

| ESP32 Chip | GPIO1 | GPIO3 |
| ---------- | ----- | ----- |
| CP2104     | RXD   | TXD   |

**Internal I2C connection**

| ESP32 Chip | GPIO21 | GPIO22 |
| ---------- | ------ | ------ |
| AXP192     | SDA    | SCL    |
| BM8563     | SDA    | SCL    |
| CHSC6540   | SDA    | SCL    |

## M5Tough M-BUS Schematic diagram

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/core2/core2_mbus.webp" width = "50%">

## M5PORT EXPLAIN

| PORT           | PIN    | Note: |
| -------------- | ------ | ----- |
| PORT\-A\(Red\) | G32/33 | I2C   |


## More Information

[Product docs](https://docs.m5stack.com/en/core/tough)