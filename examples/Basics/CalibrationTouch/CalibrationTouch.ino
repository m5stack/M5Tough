#include <M5Tough.h>

void setup()
{
    M5.begin(true, true, true, true);
    while (!M5.touch.calibrationTouch(&M5.Lcd));
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.print("Calibration Successfully");
}                                  

void loop()
{
    
}