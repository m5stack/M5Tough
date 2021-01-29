#include <M5Tough.h>

extern const unsigned char midiMusic[6757];

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
        M5.speaker.playMidi(midiMusic);
    }
    M5.update();
}