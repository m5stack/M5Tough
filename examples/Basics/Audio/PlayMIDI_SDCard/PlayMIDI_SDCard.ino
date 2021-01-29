/*
    Description: The MIDI file (supermario.mid) used in the example is in the same path as the program, please install Fonts file in TF card before compiling.
*/


#include <M5Tough.h>
#include "SD.h"

uint8_t* midiAudioFileptr;

void setup()
{

    M5.begin(true, true, true, true);
    M5.Lcd.fillTriangle(130,50,130,150,210,100,TFT_GREEN);
    M5.lcd.drawString("Click to Play!",100,180,4);
    M5.Axp.SetSpkEnable(1);
    File midiFile =  SD.open("/supermario.mid");
    midiAudioFileptr = (uint8_t*)ps_calloc(midiFile.size(),sizeof(uint8_t));
    midiFile.readBytes((char*)midiAudioFileptr,midiFile.size());
    midiFile.close();
}

void loop()
{
    if(M5.touch.isPressed()){
       M5.speaker.playMidi(midiAudioFileptr);
    }
    M5.update();
}