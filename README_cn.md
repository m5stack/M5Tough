# M5Tough Library

中文 | [English](README.md)

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/tough/tough_01.webp" alt="M5Tough_P1" width="350" height="350">

* **如果查看 M5Tough 的详细介绍文档，[点击这里](https://docs.m5stack.com/zh_CN/core/tough)**

<!-- * **如果想要购买 M5Tough 的话，[点击这里](https://item.taobao.com/item.htm?spm=a1z10.5-c-s.w4002-22404213529.29.5ada1d91KUL15v&id=623449145184)** -->

## 描述

**M5Tough** 是M5Stack开发套件系列中第二代主机，在原有一代主机基础上对功能进一步加强，硬件功能更加齐全。主控ESP32型号为D0WDQ6-V3，具有两个可以单独控制的 Xtensa® 32-bit LX6 处理器，主频高达240Mhz，支持WiFi与蓝牙功能，板载16MB Flash与8MB PSRAM，可通过TYPE-C接口下载程序，强劲的配置满足复杂应用的资源开销。正面搭载一块2.0寸一体化电容式触摸屏，为用户带来更流畅的人机交互体验。机身内置震动马达，可提供触觉回馈和震动提醒功能。内建的RTC模块可提供精准计时功能。电源部分搭载AXP192电源管理芯片可有效控制机身功耗，内置绿色电源指示灯，配备390mAh电池，续航时间更持久。同时机身内配备了SD卡槽与扬声器，为了保证获得更高质量的声音效果，采用I2S数字音频接口的功放芯片，能有效防止信号失真。在机身的左侧和底部配有独立的电源按键与重启(RST)按键，屏幕正面的3个圆点属于触摸屏的一部分，可通过编写程序设置热区映射为3个虚拟按键。

## 管脚映射

**LCD 屏幕 & TF Card**

LCD 像素：320x240
TF 卡最大支持 16GB

| ESP32 Chip  | GPIO38 | GPIO23 | GPIO18 | GPIO5 | GPIO15 |          |           |           |
| ----------- | ------ | ------ | ------ | ----- | ------ | -------- | --------- | --------- |
| AXP192 Chip |        |        |        |       |        | AXP\_IO4 | AXP\_LDO3 | AXP\_LDO2 |
| ILI9342C    | MISO   | MOSI   | SCK    | CS    | DC     | RST      | BL        | PWR       |


| ESP32 Chip | GPIO38 | GPIO23 | GPIO18 | GPIO4 |
| ---------- | ------ | ------ | ------ | ----- |
| TF Card    | MISO   | MOSI   | SCK    | CS    |

**CAP.TOUCH触摸屏**

| ESP32 chip | GPIO21 | GPIO22 | GPIO39 |          |
| ---------- | ------ | ------ | ------ | -------- |
| AXP192     |        |        |        | AXP\_IO4 |
| CHSC6540   | SDA    | SCL    | INT    | RST      |


**NS4168功放**

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


**USB转串口下载**

| ESP32 Chip | GPIO1 | GPIO3 |
| ---------- | ----- | ----- |
| CP2104     | RXD   | TXD   |


**内部I2C连接**

| ESP32 Chip | GPIO21 | GPIO22 |
| ---------- | ------ | ------ |
| AXP192     | SDA    | SCL    |
| BM8563     | SDA    | SCL    |
| CHSC6540   | SDA    | SCL    |

## M5Tough M-BUS示意图

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/core2/core2_mbus.webp" width = "50%">

## M5Tough 端口说明

| PORT           | PIN    | Note: |
| -------------- | ------ | ----- |
| PORT\-A\(Red\) | G32/33 | I2C   |

## 更多信息

[产品文档](https://docs.m5stack.com/zh_CN/core/tough)
