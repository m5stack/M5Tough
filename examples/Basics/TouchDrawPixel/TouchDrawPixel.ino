#include <M5Tough.h>

TouchZone clearBtn(0,0,50,50);

void setup()
{
    M5.begin(true, true, true, true);
    while (!M5.touch.calibrationTouch(&M5.Lcd));
    M5.lcd.drawString("CLEAR",5,5,4);
}                                  

void loop()
{
    M5.update();
    if(M5.touch.isPressed()){
        TouchPoint Point = M5.touch.getPoint();
        if(M5.touch.isMoving()){
            char buffer[24];
            sprintf(buffer, "X: %3d, Y: %3d", Point.x, Point.y);
            M5.Lcd.drawPixel(Point.x, Point.y ,TFT_GREEN);
            Serial.println(buffer);
        }
        if(clearBtn.contains(Point)){
            M5.lcd.fillScreen(TFT_BLACK);
            M5.lcd.drawString("CLEAR",5,5,4);
        }
    }
}

