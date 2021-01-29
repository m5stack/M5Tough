#include "Touch.h"

TouchPoint::TouchPoint(int16_t x_, int16_t y_)
{
    x = x_;
    y = y_;
}
bool TouchPoint::operator==(const TouchPoint &p)
{
    return (Equals(p));
}

bool TouchPoint::operator!=(const TouchPoint &p)
{
    return (!Equals(p));
}

bool TouchPoint::operator=(const TouchPoint &p)
{
    x = p.x;
    y = p.y;
    return true;
}

bool TouchPoint::Equals(const TouchPoint &p)
{
    return (x == p.x && y == p.y);
}

void TouchPoint::set(int16_t x_, int16_t y_)
{
    x = x_;
    y = y_;
}
bool TouchPoint::vaild()
{
    return (x != -1);
}


Touch::Touch()
{
}

Touch::~Touch()
{
}

void Touch::begin(bool EEPROMEnabled)
{
    Wire1.begin(21, 22);
    _EnableE2PROM = EEPROMEnabled;
    if (_EnableE2PROM)
    {
        EEPROM.begin(64);
    }
}

uint8_t Touch::getDataFromNs2009(const uint8_t *send_buf, size_t send_buf_len,
                                 uint8_t *receive_buf, size_t receive_buf_len)
{
    Wire1.beginTransmission(0x48);
    Wire1.write(send_buf, send_buf_len);
    Wire1.endTransmission();
    Wire1.requestFrom(0x48, receive_buf_len);
    while (Wire1.available())
    {
        *receive_buf++ = Wire1.read();
    }
    return 0;
}

uint8_t Touch::getCmdDataFromNs2009(uint8_t cmd, int *val)
{
    uint8_t ret, buf[2];
    ret = getDataFromNs2009(&cmd, 1, buf, 2);
    if (ret != 0)
        return 0;
    if (val)
        *val = (buf[0] << 4) | (buf[1] >> 4);
    return 1;
}

void Touch::SetCalibrationParm(float Kx, float Bx, float Ky, float By)
{
    _TouchKx = Kx;
    _TouchBx = Bx;
    _TouchKy = Ky;
    _TouchBy = By;
}

void Touch::read()
{
    int z;
    getCmdDataFromNs2009(NS2009_READ_Z1, &z);
    getCmdDataFromNs2009(NS2009_READ_X, &_PressedX);
    getCmdDataFromNs2009(NS2009_READ_Y, &_PressedY);

    if(( z > 50 )&&( z < 4000 ))
    {
        _PointX = (_PressedX - _TouchBx) / _TouchKx;
        _PointX = (_PointX < 0) ? 0 : _PointX;
        _PointX = (_PointX > 320) ? 320 : _PointX;

        _PointY = (_PressedY - _TouchBy) / _TouchKy;
        _PointY = (_PointY < 0) ? 0 : _PointY;
        _PointY = (_PointY > 240) ? 240 : _PointY;
        
        if( _state == kMoving )
        {
            if(( abs( _lastPX - _PointX ) > 30 )||( abs( _lastPY - _PointY ) > 30 ))
            {
                _PointY = _lastPY;
                _PointX = _lastPX;
            }
            else
            {
                _PointY = (int)(_alpha * (double)_PointY + ( 1.00 - _alpha ) * (double)_lastPY );
                _PointX = (int)(_alpha * (double)_PointX + ( 1.00 - _alpha ) * (double)_lastPX );
            }
        }
        _lastPY = _PointY;
        _lastPX = _PointX;
        
        _state = ( _state == kRelease ) ? kPressed : kMoving;
        _pressedZ = z;
    }
    else
    {
        _lastPX = -1;
        _lastPY = -1;
        _state = kRelease;
    }
}

int Touch::getTouchRawXData()
{
    int Data;
    getCmdDataFromNs2009(NS2009_READ_X, &Data);
    return Data;
}

int Touch::getTouchRawYData()
{
    int Data;
    getCmdDataFromNs2009(NS2009_READ_Y, &Data);
    return Data;
}

int Touch::getTouchX()
{
    return _PointX;
}
int Touch::getTouchY()
{
    return _PointY;
}

bool Touch::WaitRelease()
{
    do{
        this->read();
        delay(5);
    } while ( _state != kRelease );
    return true;
}

bool Touch::WaitRelease(uint64_t AutoReleseTime)
{
    uint64_t StartTime = millis();
    do{
        this->read();
        delay(5);
    } while (( _state != kRelease ) && (millis() < AutoReleseTime + StartTime));
    return true;
}

TouchPoint Touch::getPoint()
{
    return TouchPoint(_PointX,_PointY);
}

bool Touch::calibrationTouch(TFT_eSPI *fb)
{
    if (EEPROM.read(TouchBasicAddress + TouchCalibrationFlag) == 0x15)
    {
        float Kx, Bx, Ky, By;
        Kx = EEPROM.readFloat(TouchBasicAddress + TouchKx);
        Bx = EEPROM.readFloat(TouchBasicAddress + TouchBx);
        Ky = EEPROM.readFloat(TouchBasicAddress + TouchKy);
        By = EEPROM.readFloat(TouchBasicAddress + TouchBy);
        this->SetCalibrationParm(Kx, Bx, Ky, By);
        return true;
    }
    
    fb->fillRect(0, 0, 320, 240, TFT_RED);

    int i = 0;
    for (i = 0; i < 5; i++)
        fb->fillEllipse(this->GetCalibrationMarkX(i),
                        this->GetCalibrationMarkY(i),
                        5, 5, TFT_BLACK);

    for (i = 0; i < 4; i++)
    {
        fb->fillEllipse(this->GetCalibrationMarkX(i),
                        this->GetCalibrationMarkY(i),
                        5, 5, WHITE);
        this->read();
        while (!isPressed())
        {
            this->read();
            delay(50);
        }
        fb->fillEllipse(this->GetCalibrationMarkX(i),
                        this->GetCalibrationMarkY(i),
                        5, 5, BLACK);

        this->SetCalibrationTouchData(i, this->getTouchRawXData(), this->getTouchRawYData());

        while (this->isPressed())
        {
            this->read();
            delay(50);
        }
        delay(200);
    }

    if (this->CheckCalibrationMark(1) == false)
        return false;

    i = 4;

    fb->fillEllipse(this->GetCalibrationMarkX(i),
                    this->GetCalibrationMarkY(i),
                    5, 5, WHITE);
    this->read();
    while (!this->isPressed())
    {
        this->read();
        delay(50);
    }
    fb->fillEllipse(this->GetCalibrationMarkX(i),
                    this->GetCalibrationMarkY(i),
                    5, 5, BLACK);
    this->SetCalibrationTouchData(i, this->getTouchRawXData(), this->getTouchRawYData());
    this->read();
    while (this->isPressed())
    {
        this->read();
        delay(50);
    }
    delay(200);

    if (this->CheckCalibrationMark(2) == false)
        return false;

    this->CalculationCalibtion();

    return true;
}

void Touch::SetCalibrationTouchData(uint8_t Steps, int TouchXData, int TouchYData)
{
    TouchData[Steps][0] = TouchXData;
    TouchData[Steps][1] = TouchYData;
}
int Touch::GetCalibrationMarkX(uint8_t Steps)
{
    return TouchMark[Steps][0];
}

int Touch::GetCalibrationMarkY(uint8_t Steps)
{
    return TouchMark[Steps][1];
}
bool Touch::CheckCalibrationMark(uint8_t Steps)
{
    if (Steps == 1)
    {
        if ((abs(TouchData[0][0] - TouchData[1][0]) > Precision) ||
            (abs(TouchData[1][1] - TouchData[2][1]) > Precision) ||
            (abs(TouchData[2][0] - TouchData[3][0]) > Precision) ||
            (abs(TouchData[0][1] - TouchData[3][1]) > Precision))
            return false;
    }
    else if (Steps == 2)
    {
        float PamX1 = (TouchData[3][0] + TouchData[0][0]) / 2;
        float PamX2 = (TouchData[2][0] + TouchData[1][0]) / 2;
        float PamY1 = (TouchData[1][1] + TouchData[0][1]) / 2;
        float PamY2 = (TouchData[2][1] + TouchData[3][1]) / 2;

        float PamX = (PamX1 + PamX2) / 2;
        float PamY = (PamY1 + PamY2) / 2;

        Serial.printf("%f,%f,%f,%f,%f,%f\r\n", PamX1, PamX2, PamY1, PamY2, PamX, PamY);

        if ((abs(PamX1 - PamX2) > Precision) ||
            (abs(PamY1 - PamY2) > Precision) ||
            (abs(PamX1 - PamX) > Precision) ||
            (abs(PamY1 - PamY) > Precision))
            return false;
    }
    return true;
}

bool Touch::CalculationCalibtion()
{
    float PamX1 = (TouchData[0][0] + TouchData[1][0]) / 2;
    float PamX2 = (TouchData[3][0] + TouchData[2][0]) / 2;
    float PamY1 = (TouchData[0][1] + TouchData[3][1]) / 2;
    float PamY2 = (TouchData[1][1] + TouchData[2][1]) / 2;

    _TouchKx = (PamX2 - PamX1) / (TouchMark[2][0] - TouchMark[1][0]);
    _TouchBx = PamX2 - (_TouchKx * TouchMark[2][0]);

    _TouchKy = (PamY2 - PamY1) / (TouchMark[1][1] - TouchMark[0][1]);
    _TouchBy = PamY2 - (_TouchKy * TouchMark[1][1]);

    EEPROM.writeByte(TouchBasicAddress + TouchCalibrationFlag, 0x15);
    EEPROM.writeFloat(TouchBasicAddress + TouchKx, _TouchKx);
    EEPROM.writeFloat(TouchBasicAddress + TouchBx, _TouchBx);
    EEPROM.writeFloat(TouchBasicAddress + TouchKy, _TouchKy);
    EEPROM.writeFloat(TouchBasicAddress + TouchBy, _TouchBy);
    EEPROM.commit();

    return true;
}
