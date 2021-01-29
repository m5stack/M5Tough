#include <M5Tough.h>
#include "WiFi.h"

#include "Fonts/EVA_24px.h"
#include "Fonts/EVA_20px.h"
#include "Fonts/EVA_11px.h"

#include "resource.h"

TFT_eSprite pageSprite = TFT_eSprite(&M5.Lcd);
TFT_eSprite timerSprite = TFT_eSprite(&M5.Lcd);
TFT_eSprite wifiSprite = TFT_eSprite(&M5.Lcd);
TFT_eSprite voiceSprite = TFT_eSprite(&M5.Lcd);

extern const unsigned char previewR[120264];

struct systemPam
{
    int voiceLevel;
    int second;
    bool flushPageFlag;

    RTC_TimeTypeDef timeSet;
    RTC_DateTypeDef dateSet;

}_systemPam = { .voiceLevel = 4,.second = 0,.flushPageFlag = true,.timeSet = {12,2,5},.dateSet = {1,12,30,2020} };

int second = 0;
RTC_TimeTypeDef timeSet = {12, 02, 05};

void drawingTable()
{
    pageSprite.drawJpg(touchPageJPEG, 28069, 0, 0, 320, 240);
    pageSprite.drawColorBitmapAlpha(281,200,32,32,
                                    (uint8_t*)image_eraser32x32,
                                    0xffffff,0x2e2e2e);
    pageSprite.pushSprite(0,0);
    TouchPoint pNow, pLast;
    TouchZone clear(277,198,40,40),exit(279,5,37,27);

    M5.touch.WaitRelease();

    while (1)
    {
        M5.update();
        if ( M5.touch.isPressed())
        {
            pNow = M5.touch.getPoint();
            if( !M5.touch.isMoving())
            {
                if( exit.contains(pNow))
                {
                    M5.speaker.playBeep(2000,100,_systemPam.voiceLevel * 2500,false);
                    pageSprite.drawJpg(mainPageJPEG,sizeof(mainPageJPEG),0,0,320,240);
                    pageSprite.pushSprite(0, 0);
                    return;
                }
                else if( clear.contains(pNow))
                {
                    pageSprite.drawJpg(touchPageJPEG, 28069, 0, 0, 320, 240);
                    pageSprite.drawColorBitmapAlpha(281,200,32,32,
                                                    (uint8_t*)image_eraser32x32,
                                                    0xffffff,0x2e2e2e);
                    pageSprite.pushSprite(0,0);
                }
            }
            else
            {
                //Serial.printf("[Touch] X: %d Y:%d\r\n", pNow.x, pNow.y);
                if ( pNow.x > 5 && pNow.x < 315 && pNow.y > 33 && pNow.y < 235 )
                {
                    if( pLast.x != -1 )
                    M5.Lcd.drawLine(pLast.x, pLast.y, pNow.x, pNow.y, TFT_WHITE);
                    pLast = pNow;
                }
            }
        }
        else
        {
            pLast.set(-1,-1);
        }
        delay(2);
    }
}

void scanWifi()
{
    pageSprite.drawJpg(touchPageJPEG, 28069, 0, 0, 320, 240);
    pageSprite.drawJpg(wifiScanPageTitle320x36, 18351, 0, 0, 320, 36);
    pageSprite.pushSprite(0,0);
    pageSprite.setTextFont(2);
    pageSprite.setTextSize(1);
    pageSprite.setTextColor(TFT_WHITE);
    pageSprite.setTextDatum(CL_DATUM);

    M5.touch.WaitRelease();

    TouchZone exit(279,5,37,27);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    WiFi.scanNetworks(true);

    uint16_t* ptr = (uint16_t*)ps_calloc(165*25,sizeof(uint16_t));


    while(1)
    {
        int WifiNumber = WiFi.scanComplete();

        if ( WifiNumber == -2 )
        {

        }
        else if( WifiNumber == - 1 )
        {

        }
        else if( WifiNumber == 0 )
        {
            WiFi.scanDelete();
            WiFi.scanNetworks(true);
        }
        else 
        {
            WifiNumber = ( WifiNumber > 6 ) ? 6 : WifiNumber;

            pageSprite.drawJpg(touchPageJPEG, 28069, 0, 0, 320, 240);
            pageSprite.drawJpg(wifiScanPageTitle320x36, 18351, 0, 0, 320, 36);

            for (int i = 0; i < WifiNumber; i++) 
            {
                //Disbuff.fillRect( 18,34+i*24 + 2,7,20,Disbuff.color565(0xff,0xa0,0));
                String SSIDStr = WiFi.SSID(i);
                if( SSIDStr.length() > 14 )
                {
                    SSIDStr = SSIDStr.substring(0,11);
                    SSIDStr += "...";
                }
                //Disbuff.setTextDatum(TL_DATUM);
                //Disbuff.drawString( SSIDStr,35,34+i*24 + 2 );

                pageSprite.getSprite2Buff(ptr,23,48 + 28 * i,165,25);

                for (size_t i = 0; i < (165*25); i++)
                {
                    *(ptr + i) = M5.Lcd.alphaBlend(30,TFT_WHITE,*(ptr + i));
                }
                pageSprite.setSwapBytes(false);
                pageSprite.pushImage(23,48 + 28 * i,165,25,ptr);
                pageSprite.fillRect(19,48 + 28 * i,4,25,pageSprite.color565(226,226,226));
                pageSprite.drawString(SSIDStr,33,60 + 28 * i);

                for( int n = 12; n >= 0; n-- )
                {
                    int32_t rssi = ( WiFi.RSSI(i) < -100 ) ? -100 : WiFi.RSSI(i);
                    rssi = map( rssi,-100,-20,-130,0);
                    uint16_t colorNow = pageSprite.color565(64,64,64);

                    if( rssi < ( n * -10))
                    {
                        colorNow = pageSprite.color565(64,64,64);
                    }
                    else
                    {
                        colorNow = pageSprite.color565(227,227,227);
                    }
                    pageSprite.fillRect(296-9*n,48+28*i,6,25,colorNow);
                }
            }
            pageSprite.pushSprite(0,0);

            WiFi.scanDelete();
            WiFi.scanNetworks(true);
        }

        if( M5.touch.isPressed() && (!M5.touch.isMoving()) && (exit.contains(M5.touch.getPoint())))
        {
            M5.speaker.playBeep(2000,100,_systemPam.voiceLevel * 2500,false);
            pageSprite.drawJpg(mainPageJPEG,sizeof(mainPageJPEG),0,0,320,240);
            pageSprite.pushSprite(0, 0);
            return;
        }
        M5.update();
        delay(2);
    }
    delete ptr;
}

void timeApp()
{
    pageSprite.drawJpg(touchPageJPEG, 28069, 0, 0, 320, 240);
    pageSprite.drawJpg(timePageTitle320x36, 18351, 0, 0, 320, 36);
    pageSprite.pushSprite(0,0);

    RTC_DateTypeDef rtcdate;
    M5.Rtc.GetData(&rtcdate);

    bool first = true;

    TouchZone exit(279,5,37,27);
    while(1)
    {
        M5.Rtc.GetData(&rtcdate);
        M5.Rtc.GetTime(&timeSet);
        if(( second != timeSet.Seconds)||( first == true ))
        {
            // 145
            pageSprite.drawJpg(touchPageJPEG, 28069, 0, 0, 320, 240);
            pageSprite.drawJpg(timePageTitle320x36, 18351, 0, 0, 320, 36);
            pageSprite.drawColorBitmapAlpha(45 , 68, 48, 70, num70x48[timeSet.Hours/10%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha(95 , 68, 48, 70, num70x48[timeSet.Hours%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha(144, 68, 30, 70, num70x48[10],(second % 2 == 0) ? 0xffffff:0x5f5f5f,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha(173, 68, 48, 70, num70x48[timeSet.Minutes/10%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha(223, 68, 48, 70, num70x48[timeSet.Minutes%10],0xffffff,0x2e2e2e);
            
            pageSprite.drawColorBitmapAlpha( 45  + 9, 164, 20, 32, num32x20[rtcdate.Year/1000%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 67  + 9, 164, 20, 32, num32x20[rtcdate.Year/100%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 89  + 9, 164, 20, 32, num32x20[rtcdate.Year/10%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 111 + 9, 164, 20, 32, num32x20[rtcdate.Year%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 133 + 9 + 2 , 164, 14, 32, num32x20[10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 149 + 9 + 4 , 164, 20, 32, num32x20[rtcdate.Month/10%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 171 + 9 + 4, 164, 20, 32, num32x20[rtcdate.Month%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 193 + 9 + 6, 164, 14, 32, num32x20[10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 209 + 9 + 8, 164, 20, 32, num32x20[rtcdate.Date/10%10],0xffffff,0x2e2e2e);
            pageSprite.drawColorBitmapAlpha( 231 + 9 + 8, 164, 20, 32, num32x20[rtcdate.Date%10],0xffffff,0x2e2e2e);
            pageSprite.pushSprite(0,0);
            second = timeSet.Seconds;
        }
        first =false;

        if( M5.touch.isPressed() && (!M5.touch.isMoving()) && (exit.contains(M5.touch.getPoint())))
        {
            M5.speaker.playBeep(2000,100,_systemPam.voiceLevel * 2500,false);
            return;
        }
        M5.update();
        delay(2);
    }
}

void flushTimeOnMainPage()
{
    char timeCharbuff[32];
    sprintf(timeCharbuff,"%02d:%02d:%02d",timeSet.Hours,timeSet.Minutes,timeSet.Seconds);
    timerSprite.pushInSprite(&pageSprite,32,122,107,107,0,0);
    timerSprite.drawString(timeCharbuff,54,75);
    pageSprite.pushInSprite(&timerSprite,0,0,107,107,32,122);
    //timerSprite.pushSprite(32, 122);
}

void flushVoiceOnMainPage()
{
    voiceSprite.pushInSprite(&pageSprite,144,66,107,51,0,0);
    if( _systemPam.voiceLevel == 0 )
    {
        voiceSprite.drawColorBitmapAlpha(15,14,24,30,
                                        (uint8_t*)image_mute,
                                        0xffffff, 0x2e2e2e );
    }
    else
    {
        voiceSprite.drawColorBitmapAlpha(15,14,24,30,
                                        (uint8_t*)image_voice,
                                        0xffffff, 0x2e2e2e);
        
        for ( int i = 0; i < _systemPam.voiceLevel; i++ )
        {
            voiceSprite.fillRect(48 + i * 12,31 - i * 7,7,9 + i * 7,TFT_WHITE);
        }
    }
    pageSprite.pushInSprite(&voiceSprite,0,0,107,51,144,66);
    //voiceSprite.pushSprite(144,66);
}

void flushWifiOnMainPage()
{
    wifiSprite.drawString("Wi-Fi",54,75);
    //.pushSprite(144,122);
    pageSprite.pushInSprite(&wifiSprite,0,0,107,107,144,122);
}

void drawInfoString(TFT_eSprite *p,String str,int *posy, uint16_t color)
{
    uint16_t colorLast = p->textcolor;
    p->setTextColor(color);
    p->drawString(str,15,*posy);
    p->setTextColor(colorLast);
    *posy += 20;
}


void hardwareTestApp()
{
    hardwareTest:;

    int yPos = 50;
    TouchZone retry(10,40,300,190),exit(279,5,37,27);


    pageSprite.drawJpg(touchPageJPEG, 28069, 0, 0, 320, 240);
    pageSprite.drawJpg(factoryTestsTitle320x36, 21938, 0, 0, 320, 36);
    pageSprite.pushSprite(0,0);

    pageSprite.setTextFont(2);
    pageSprite.setTextSize(1);
    pageSprite.setTextColor(TFT_WHITE);
    pageSprite.setTextDatum(CL_DATUM);

    sdcard_type_t Type = SD.cardType();
    Serial.printf("SD Type %d \r\n", Type);
    if(( Type == CARD_SD )||( Type == CARD_SDHC ))
    {
        drawInfoString(&pageSprite,"SDCard test pass",&yPos,TFT_GREEN);
        
    }
    else
    {
        drawInfoString(&pageSprite,"SDCard test fault",&yPos,TFT_RED);
    }
    pageSprite.pushSprite(0,0);
    
    pinMode(35,ANALOG);
    pinMode(36,ANALOG);
    analogSetPinAttenuation(35,ADC_11db);
    analogSetPinAttenuation(36,ADC_11db);

    uint32_t adcdatabuff[2] = {0,0};
    for( int i = 0; i < 8; i++ )
    {
        adcdatabuff[0] = analogRead(35);
        adcdatabuff[1] = analogRead(36);
    }

    adcdatabuff[0] >>= 3;
    adcdatabuff[1] >>= 3;
    Serial.printf("ADC35:%d ADC36:%d\r\n",adcdatabuff[0],adcdatabuff[1]);
    if(( adcdatabuff[0] > 300 )&&( adcdatabuff[0] < 340 )&&( adcdatabuff[1] > 130 )&&( adcdatabuff[1] < 170))
    {
        drawInfoString(&pageSprite,"ADCPin test pass",&yPos,TFT_GREEN);
    }
    else
    {
        drawInfoString(&pageSprite,"ADCPin test fault",&yPos,TFT_RED);
    }
    pageSprite.pushSprite(0,0);

    uint8_t foundFLag = 0;
    for( int i = 0; i < 128; i++ )
    {
        Wire.beginTransmission(i);
        if(( Wire.endTransmission() == I2C_ERROR_OK ))
        {
            if( i == 0x51 ) foundFLag |= 0x01;
            if( i == 0x76 ) foundFLag |= 0x04;
            Serial.printf("Wire0 Find %02X\r\n",i);
            //foundFLag |= 0x01;
        }
        //if(( Wire.endTransmission() == I2C_ERROR_OK )&&( i == 0x51 ))
        //{
        //    Serial.printf("Wire0 Find %02X\r\n",i);
        //    foundFLag |= 0x01;
        //}
    }

    for( int i = 0; i < 128; i++ )
    {
        Wire1.beginTransmission(i);
        if(( Wire1.endTransmission() == I2C_ERROR_OK )&&( i == 0x50 ))
        {
            Serial.printf("Wire1 Find %02X\r\n",i);
            foundFLag |= 0x02;
        }
    }

    if( foundFLag & 0x04 )
    {
        drawInfoString(&pageSprite,"Grove test pass",&yPos,TFT_GREEN);
    }
    else
    {
        drawInfoString(&pageSprite,"Grove test fault",&yPos,TFT_RED);
    }

    if( foundFLag & 0x01 )
    {
        drawInfoString(&pageSprite,"Wire test pass",&yPos,TFT_GREEN);
    }
    else
    {
        drawInfoString(&pageSprite,"Wire test fault",&yPos,TFT_RED);
    }

    if( foundFLag & 0x02 )
    {
        drawInfoString(&pageSprite,"Wire1 test pass",&yPos,TFT_GREEN);
    }
    else
    {
        drawInfoString(&pageSprite,"Wire1 test fault",&yPos,TFT_RED);
    }

    pageSprite.pushSprite(0,0);

    pinMode(27,INPUT);
    pinMode(34,INPUT);
    
    uint8_t pinList0[8] = {27,13,27,13,27,13,27,13};
    uint8_t pinList1[8] = {25,26,14,19,25,26,14,19};
    uint8_t pinResData[2] = {0,0};

    for (int i = 0; i < 8; i++)
    {
        pinMode(pinList0[i],OUTPUT);
        pinMode(pinList1[i],OUTPUT);
    }

    for (int i = 0; i < 8; i++)
    {
        pinResData[0] <<= 1;
        digitalWrite(pinList0[i],( i % 2 == 0 ) ? HIGH : LOW );
        delay(10);
        pinResData[0] += digitalRead(27);
        digitalWrite(pinList0[i], LOW );
        delay(10);
    }

    for (int i = 0; i < 8; i++)
    {
        pinResData[1] <<= 1;
        digitalWrite(pinList1[i],( i % 2 == 0 ) ? HIGH : LOW );
        delay(10);
        pinResData[1] += digitalRead(34);
        digitalWrite(pinList1[i], LOW );
        delay(10);
    }
    Serial.printf("PinData0 %02X PinData1 %02X\r\n",pinResData[0],pinResData[1]);
    if( pinResData[0] == 0xAA )
    {
        drawInfoString(&pageSprite,"GPIO Group0 test pass",&yPos,TFT_GREEN);
    }
    else
    {
        drawInfoString(&pageSprite,"GPIO Group0 test fault",&yPos,TFT_RED);
    }

    if( pinResData[1] == 0xAA )
    {
        drawInfoString(&pageSprite,"GPIO Group1 test pass",&yPos,TFT_GREEN);
    }
    else
    {
        drawInfoString(&pageSprite,"GPIO Group1 test fault",&yPos,TFT_RED);
    }

    pageSprite.pushSprite(0,0);

    while(1)
    {
        M5.update();
        delay(2);
        if( M5.touch.isPressed() && (!M5.touch.isMoving()))
        {
            if(exit.contains(M5.touch.getPoint()))
            {
                M5.speaker.playBeep(2000,100,_systemPam.voiceLevel * 2500,false);
                return;
            }
            else if(retry.contains(M5.touch.getPoint()))
            {
                M5.speaker.playBeep(2000,100,_systemPam.voiceLevel * 2500,false);
                goto hardwareTest;
            }
        }
    }
    //delay(100);
    //Serial.flush();
    //Serial.end();
    //delay(100);
    //Serial.begin(115200);
    //Serial.printf("End Hardware Test\r\n");
    //delay(2000);
}

void setup()
{
    M5.begin(true, true, true, true);

    M5.Axp.SetLDOVoltage(3, 3300);
    M5.Axp.SetLDOEnable(3, true);

    M5.Axp.SetSpkEnable(1);

    //EEPROM.write(TouchBasicAddress + TouchCalibrationFlag,0);

    while (!M5.touch.calibrationTouch(&M5.Lcd));
    /*
    for (int i = 0; i < 127; i++)
    {
        Wire.beginTransmission(i);
        if( Wire.endTransmission() == I2C_ERROR_OK )
        Serial.printf("Find %02X \r\n",i);
    }
    */
    pageSprite.createSprite(320, 240);
    M5.speaker.playRAW(previewR,sizeof(previewR),false,false);
    pageSprite.drawJpg(wellcomePageJPEG,sizeof(wellcomePageJPEG),0,0,320,240);
    pageSprite.pushSprite(0, 0);
    delay(500);
   
    pageSprite.createSprite(320, 240);
    pageSprite.setSwapBytes(true);
    pageSprite.drawJpg(mainPageJPEG,sizeof(mainPageJPEG),0,0,320,240);
    pageSprite.pushSprite(0, 0);

    timerSprite.createSprite(107,107); //32,122 107 107
    timerSprite.pushInSprite(&pageSprite,32,122,107,107,0,0);

    timerSprite.setFreeFont(&EVA_20px);
    timerSprite.setTextSize(1);
    timerSprite.setTextColor(TFT_WHITE);
    timerSprite.setTextDatum(TC_DATUM);

    wifiSprite.createSprite(107,107); //32,122 107 107
    wifiSprite.pushInSprite(&pageSprite,144,122,107,107,0,0);

    wifiSprite.setFreeFont(&EVA_20px);
    wifiSprite.setTextSize(1);
    wifiSprite.setTextColor(TFT_WHITE);
    wifiSprite.setTextDatum(TC_DATUM);

    voiceSprite.createSprite(107,51);

    //FF14disco.mid
    //FF14Lemon.mid
    //M5.speaker.playMidi(midiMusic);
    

    //if( Type == CARD_SD )
    //{
    //    File midiFile =  SD.open("/FF14Lemon.mid");
    //    
    //    uint8_t* midiAudioFileptr = (uint8_t*)ps_calloc(midiFile.size(),sizeof(uint8_t));
    //    midiFile.readBytes((char*)midiAudioFileptr,midiFile.size());
    //    midiFile.close();
    //    //M5.speaker.playMidi(midiAudioFileptr);
    //    delete midiAudioFileptr;
    //}
    //
    M5.Rtc.SetTime(&timeSet);
    M5.Rtc.GetTime(&timeSet);
    second = timeSet.Seconds;
}                                  

bool flushPageFlag = true;

TouchZone_t appDraw(32,10,107,107);
TouchZone_t bnReboot(256,10,51,51);
TouchZone_t bnShutdown(256,66,51,51);
TouchZone_t bnWifiScan(144,122,107,107);
TouchZone_t bnTime(32,122,107,107);
TouchZone_t bnVoice(144,66,107,51);
TouchZone_t bnMusic(144,10,51,51);
TouchZone_t bnHard(256,177,51,51);

void loop()
{
    M5.Rtc.GetTime(&timeSet);

    if( M5.touch.isPressed() && (!M5.touch.isMoving()))
    {
        TouchPoint point = M5.touch.getPoint();
        M5.speaker.playBeep(2000,100,_systemPam.voiceLevel * 2500,false);
        if( appDraw.contains(point))
        {
            drawingTable();
            flushPageFlag = true;
        }
        else if( bnReboot.contains(point))
        {
            esp_restart();
        }
        else if( bnShutdown.contains(point))
        {
            M5.Axp.SetSleep();
        }
        else if( bnWifiScan.contains(point))
        {
            scanWifi();
            flushPageFlag = true;
        }
        else if( bnTime.contains(point))
        {
            timeApp();
            flushPageFlag = true;
        }
        else if( bnVoice.contains(point))
        {
            _systemPam.voiceLevel++;
            _systemPam.voiceLevel = ( _systemPam.voiceLevel > 4 ) ? 0 : _systemPam.voiceLevel;
            flushPageFlag = true;
        }
        else if( bnMusic.contains(point))
        {
            M5.speaker.playMidi(midiMusic);
            //Serial.printf("%d",Speaker::midiCtrlCMD::kPaused);
        }
        else if( bnHard.contains(point))
        {
            hardwareTestApp();
            flushPageFlag = true;
        }
    }
    if( flushPageFlag == true )
    {
        pageSprite.drawJpg(mainPageJPEG,sizeof(mainPageJPEG),0,0,320,240);
        flushVoiceOnMainPage();
        flushTimeOnMainPage();
        flushWifiOnMainPage();
        pageSprite.pushSprite(0,0);
        flushPageFlag = false;
    }

    if( second != timeSet.Seconds)
    {
        char timeCharbuff[32];
        pageSprite.drawJpg(mainPageJPEG,sizeof(mainPageJPEG),0,0,320,240);
        sprintf(timeCharbuff,"%02d:%02d:%02d",timeSet.Hours,timeSet.Minutes,timeSet.Seconds);
        timerSprite.pushInSprite(&pageSprite,32,122,107,107,0,0);
        timerSprite.drawString(timeCharbuff,54,75);
        timerSprite.pushSprite(32, 122);
        second = timeSet.Seconds;
    }
    
    M5.update();
    delay(10);
}