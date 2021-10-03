# M5Tough Library

中文 | [English](README.md)

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/tough/tough_01.webp" alt="M5Tough_P1" width="350" height="350">


## 描述

**M5Tough** 是M5Stack开发套件系列中第二代主机，在原有一代主机基础上对功能进一步加强，硬件功能更加齐全。主控ESP32型号为D0WDQ6-V3，具有两个可以单独控制的 Xtensa® 32-bit LX6 处理器，主频高达240Mhz，支持WiFi与蓝牙功能，板载16MB Flash与8MB PSRAM，可通过TYPE-C接口下载程序，强劲的配置满足复杂应用的资源开销。正面搭载一块2.0寸一体化电容式触摸屏，为用户带来更流畅的人机交互体验。机身内置震动马达，可提供触觉回馈和震动提醒功能。内建的RTC模块可提供精准计时功能。电源部分搭载AXP192电源管理芯片可有效控制机身功耗，内置绿色电源指示灯，配备390mAh电池，续航时间更持久。同时机身内配备了SD卡槽与扬声器，为了保证获得更高质量的声音效果，采用I2S数字音频接口的功放芯片，能有效防止信号失真。在机身的左侧和底部配有独立的电源按键与重启(RST)按键，屏幕正面的3个圆点属于触摸屏的一部分，可通过编写程序设置热区映射为3个虚拟按键。

## 管脚映射

**LCD 屏幕 & TF Card**

LCD 像素：320x240
TF 卡最大支持 16GB

<table>
 <tr><td>ESP32 Chip</td><td>GPIO38</td><td>GPIO23</td><td>GPIO18</td><td>GPIO5</td><td>GPIO15</td><td></td><td> </td><td> </td></tr>
 <tr><td>AXP192 Chip</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>AXP_IO4</td><td>AXP_LDO3</td><td>AXP_LDO2</td></tr>
 <tr><td>ILI9342C</td><td>MISO</td><td>MOSI</td><td>SCK</td><td>CS</td><td>DC</td><td>RST</td><td>BL</td><td>PWR</td></tr>
</table>

<table>
<tr><td>ESP32 Chip</td><td>GPIO38</td><td>GPIO23</td><td>GPIO18</td><td>GPIO4</td></tr>
<tr><td>TF Card</td><td>MISO</td><td>MOSI</td><td>SCK</td><td>CS</td></tr>
</table>

**CAP.TOUCH触摸屏**

<table>
 <tr><td>ESP32 chip</td><td>GPIO21</td><td>GPIO22</td><td>GPIO39</td></tr>
 <tr><td>AXP192</td><td></td><td></td><td></td><td>AXP_IO4</td></tr>
 <tr><td>CHSC6540</td><td>SDA</td><td>SCL</td><td>INT</td><td>RST</td></tr>
</table>

**NS4168功放**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO12</td><td>GPIO0</td><td>GPIO2</td><td>AXP_IO2</td></tr>
 <tr><td>NS4168</td><td>BCLK</td><td>LRCK</td><td>DATA</td><td>SPK_EN</td> </td></tr>
</table>

**AXP Control**

<table>
 <tr><td>AXP192</td><td>AXP_IO1</td><td>AXP_IO2</td><td>AXP_IO4</td><td>AXP_LDO3</td></tr>
 <tr><td>TouchPanel</td><td>RST</td><td></td><td></td><td></td></tr>
 <tr><td>SPEAKER</td><td></td><td>EN</td><td></td></tr>
 <tr><td>LCD</td><td></td><td></td><td>RST</td><td>backright</td></tr>
</table>

**RTC**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO21</td><td>GPIO22</td><td></td></tr>
 <tr><td>AXP192</td><td></td><td></td><td>AXP_PWR</td></tr>
 <tr><td>BM8563</td><td>SDA</td><td>SCL</td><td>INT</td></tr>
</table>

**USB转串口下载**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO1</td><td>GPIO3</td></tr>
 <tr><td>CP2104</td><td>RXD</td><td>TXD</td></tr>
</table>


**内部I2C连接**

<table>
 <tr><td>ESP32 Chip</td><td>GPIO21</td><td>GPIO22</td></tr>
 <tr><td>AXP192</td><td>SDA</td><td>SCL</td></tr>
 <tr><td>BM8563</td><td>SDA</td><td>SCL</td></tr>
 <tr><td>CHSC6540</td><td>SDA</td><td>SCL</td></tr>
</table>

## M5Tough M-BUS示意图

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/core2/core2_mbus.webp" width = "50%">

## M5Tough 端口说明

<table>
      <thead>
         <th>PORT</th>
         <th>PIN</th>
         <th>备注:</th>
      </thead>
      <tbody>
      <tr>
         <td>PORT-A(红色)</td>
         <td>G32/33</td>
         <td>I2C</td>
      </tr>
    </tbody>
</table>

## 更多信息

[产品文档](https://docs.m5stack.com/zh_CN/core/tough)
