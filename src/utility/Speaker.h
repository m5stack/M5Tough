#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#include "Arduino.h"
#include <driver/i2s.h>

#include "FS.h"

extern void mp3Decode(File *fs);

#define CONFIG_I2S_BCK_PIN 12
#define CONFIG_I2S_LRCK_PIN 0
#define CONFIG_I2S_DATA_PIN 2
#define CONFIG_I2S_DATA_IN_PIN -1

#define SPAKER_I2S_NUMBER I2S_NUM_0

typedef struct beepParameters
{
    int rate;
    int freq;
    int maxval;
    size_t time;
    //beepParameters() :rate(44100),freq(2000),maxval(10000),time(500){}
    //beepParameters(int rate,int freq,int maxval,size_t time) :rate(rate),freq(freq),maxval(maxval),time(time){}
}beepParameters_t;

typedef struct
{
    void *pAudioData;
    int length;
    bool freeFlag;
}audioParameters_t;

enum playType
{
    kTypeNull = 0,
    kTypeAudio,
    kTypeBeep,
};

typedef struct
{
    int type;
    void *dataptr;
}i2sQueueMsg_t;

typedef struct audioList
{
    size_t _num;
    int type;
    void *dataptr;
    audioList *nextPtr;
}audioList_t;

class Speaker
{
    struct TrackChunkInfo
    {
        size_t seek;
        uint32_t length;
    };

    struct midiInfo
    {
        uint32_t HeaderChunkLength;
        uint16_t TrackChunkNum;
        uint16_t MidiType;
        uint16_t TickNum;
        TrackChunkInfo *ChunkInfo;
    };

    struct midiCmdData
    {
        uint32_t TickTime;
        uint8_t cmd;
        uint8_t *dataptr;
    };

    typedef struct midiTickTimeList
    {
        uint64_t tickNum;
        double tickTime;
        midiTickTimeList *nextPtr;

        midiTickTimeList() :tickNum(0),tickTime(0),nextPtr(nullptr){}
        midiTickTimeList(uint64_t _tickNum,double _tickTime,midiTickTimeList* _ptr) :tickNum(_tickNum),tickTime(_tickTime),nextPtr(_ptr){}
        void addtickTime2List( uint64_t _tickNum, double _tickTime )
        {
            midiTickTimeList* midiTickPtr = new midiTickTimeList(_tickNum,_tickTime,nullptr);
            //midiTickTimeList* midiTickPtr = (midiTickTimeList*)malloc(sizeof(midiTickTimeList));
            midiTickTimeList* last = this;
            while( last->nextPtr != nullptr )
            {
                last = last->nextPtr;
            }
            last->nextPtr = midiTickPtr;
        }
        int getLength()
        {
            midiTickTimeList* last = this;
            int count = 0;
            while( last->nextPtr != nullptr )
            {
                last = last->nextPtr;
                count++;
            }
            return count;
        }
        double getTickTime( uint64_t tickNum )
        {
            double save;
            if( this->nextPtr == nullptr ) return 1;
            midiTickTimeList* last = this->nextPtr;
            do
            {
                if( last->tickNum >= tickNum)
                {
                    return save;
                }
                save = last->tickTime;
                last = last->nextPtr;
            } while (last != nullptr);
            return save;
        }
    }midiTickTimeList_t;

    enum midiState{
        kIdle,
        kAnaTime,
        kAnaCMD,
        kAnaData,
    };
    
private:


    size_t _rate = 44100;
    size_t listLength = 0;

    uint8_t getint8DataFromMidi( const uint8_t* ptr, size_t* point );
    uint16_t getint16DataFromMidi( const uint8_t* ptr, size_t* point );
    uint32_t getint32DataFromMidi( const uint8_t* ptr, size_t* point );
    uint64_t getint64DataFromMidi( const uint8_t* ptr, size_t* point );
    uint8_t getArrayFromMidi( const uint8_t* ptr,size_t length, size_t* point );
    String getStringFromMidi( const uint8_t* ptr,size_t length, size_t* point );

public:

    struct midiCtrlCMD
    {
        enum{
            kStop = 0,
            kPaused,
        };
        int cmd;
        int volume;
    };

    Speaker(/* args */);
    ~Speaker();
    bool begin( int __rate = 44100, bool __threadEnable = false );
    size_t playRAW( const uint8_t* __audioPtr, size_t __size, bool __modal = false, bool freeFlag = true,TickType_t __ticksToWait = portMAX_DELAY );
    size_t playBeep( int __freq = 2000, int __timems = 1000,int __maxval = 10000, bool __modal = false );

    int playMidi(const uint8_t *data);
    
};

#endif