#ifndef Touch_h
#define Touch_h
// #if ARDUINO >= 100
#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

#include "In_eSPI.h"

#define NS2009_READ_X 0xc0
#define NS2009_READ_Y 0xd0
#define NS2009_READ_Z1 0xe0
#define NS2009_READ_Z2 0xf0

#define Precision 80
#define TouchBasicAddress 16
#define TouchCalibrationFlag 0
#define TouchKx 4
#define TouchBx 8
#define TouchKy 12
#define TouchBy 16

class TouchPoint
{
public:
    TouchPoint(int16_t x_ = -1, int16_t y_ = -1);
    bool operator==(const TouchPoint &p);
    bool operator!=(const TouchPoint &p);
    bool operator=(const TouchPoint &p);

    bool Equals(const TouchPoint &p);

    void set(int16_t x_ = -1, int16_t y_ = -1);
    bool vaild();

    int16_t x, y;
};

typedef struct TouchZone
{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    TouchZone() : x(-1), y(-1), w(0), h(0) {}
    TouchZone(uint16_t _x, uint16_t _y, uint16_t _w, uint16_t _h) : x(_x), y(_y), w(_w), h(_h){};
    bool contains(const TouchPoint &p)
    {
        if ((this->x == -1) || (this->y == -1) || (this->w == 0) || (this->h == 0))
            return false;
        if ((p.x >= this->x) && (p.x <= (this->x + this->w)) &&
            (p.y >= this->y) && (p.y <= (this->y + this->h)))
        {
            return true;
        }
        return false;
    }
} TouchZone_t;

class Touch
{
public:

    enum touchState
    {
        kRelease = 0,
        kPressed,
        kMoving,
    };

    Touch();
    ~Touch();
    void begin(bool EEPROMEnabled = true);
    void read();

    void SetCalibrationParm(float Kx, float Bx, float Ky, float By);
    bool calibrationTouch(TFT_eSPI *fb);

    int getTouchRawXData();
    int getTouchRawYData();

    int getTouchX();
    int getTouchY();
    bool isPressed(){return ( _state == kPressed || _state == kMoving ) ? true: false;}
    bool isRelease(){return ( _state == kRelease ) ? true: false;}
    bool isMoving(){return ( _state == kMoving ) ? true: false;}

    bool WaitRelease();
    bool WaitRelease(uint64_t AutoReleseTime);
    TouchPoint getPoint();

    int GetCalibrationMarkX(uint8_t Steps);
    int GetCalibrationMarkY(uint8_t Steps);
    void SetCalibrationTouchData(uint8_t Steps, int TouchXData, int TouchYData);
    bool CheckCalibrationMark(uint8_t Steps);
    bool CalculationCalibtion();

private:
    uint8_t getDataFromNs2009(const uint8_t *send_buf, size_t send_buf_len, uint8_t *receive_buf, size_t receive_buf_len);
    uint8_t getCmdDataFromNs2009(uint8_t cmd, int *val);

    bool _EnableE2PROM;
    int TouchMark[5][2] = {
        {32, 24},
        {32, 216},
        {288, 216},
        {288, 24},
        {160, 120}};
    int TouchData[5][2] = {
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
    };

    float _TouchKx = 0;
    float _TouchBx = 0;
    float _TouchKy = 0;
    float _TouchBy = 0;

    //bool _PressedFlag = false;
    touchState _state = kRelease;

    int _PressedX = 0;
    int _PressedY = 0;
    int _pressedZ = 0;
    int _PointX = -1;
    int _PointY = -1;

    double _alpha = 0.4;
    int _lastPX = -1;
    int _lastPY = -1;
};
#endif