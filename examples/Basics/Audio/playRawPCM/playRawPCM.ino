#include <M5Tough.h>

extern const unsigned char chocobo[582120];

void setup()
{

    M5.begin(true, true, true, true);
    M5.Lcd.fillTriangle(130,50,130,150,210,100,TFT_GREEN);
    M5.lcd.drawString("Click to Play!",100,180,4);
    M5.Axp.SetSpkEnable(1);
}

void loop()
{
    if(M5.touch.isPressed()){
        while(1) M5.speaker.playRAW(chocobo, sizeof(chocobo),true,false);
    }
    M5.update();
}
