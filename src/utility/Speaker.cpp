#include "Speaker.h"

const double sinmap[] = {
    0.0, 0.01745240643728351, 0.03489949670250097, 0.05233595624294383, 0.0697564737441253, 0.08715574274765817, 0.10452846326765346, 0.12186934340514748, 0.13917310096006544, 0.15643446504023087, 0.17364817766693033, 0.1908089953765448, 0.20791169081775931, 0.224951054343865, 0.24192189559966773, 0.25881904510252074, 0.27563735581699916, 0.29237170472273677, 0.3090169943749474, 0.32556815445715664, 0.3420201433256687, 0.35836794954530027, 0.374606593415912, 0.3907311284892737, 0.40673664307580015, 0.42261826174069944, 0.4383711467890774, 0.45399049973954675, 0.4694715627858908, 0.48480962024633706, 0.49999999999999994, 0.5150380749100542, 0.5299192642332049, 0.5446390350150271, 0.5591929034707469, 0.573576436351046, 0.5877852522924731, 0.6018150231520483, 0.6156614753256582, 0.6293203910498374, 0.6427876096865393, 0.6560590289905072, 0.6691306063588582, 0.6819983600624985, 0.6946583704589973, 0.7071067811865476, 0.7193398003386511, 0.7313537016191705,
    0.7431448254773941, 0.754709580222772, 0.766044443118978, 0.7771459614569708, 0.788010753606722, 0.7986355100472928, 0.8090169943749475, 0.8191520442889918, 0.8290375725550417, 0.8386705679454239, 0.8480480961564261, 0.8571673007021122, 0.8660254037844386, 0.8746197071393957, 0.8829475928589269, 0.8910065241883678, 0.898794046299167, 0.9063077870366499, 0.9135454576426009, 0.9205048534524403, 0.9271838545667874, 0.9335804264972017, 0.9396926207859083, 0.9455185755993167, 0.9510565162951535, 0.9563047559630354, 0.9612616959383189, 0.9659258262890683, 0.9702957262759965, 0.9743700647852352, 0.9781476007338056, 0.981627183447664, 0.984807753012208, 0.9876883405951378, 0.9902680687415703, 0.992546151641322, 0.9945218953682733, 0.9961946980917455, 0.9975640502598242, 0.9986295347545738, 0.9993908270190958, 0.9998476951563913,
    1.0, 0.9998476951563913, 0.9993908270190958, 0.9986295347545738, 0.9975640502598242, 0.9961946980917455, 0.9945218953682734, 0.9925461516413221, 0.9902680687415704, 0.9876883405951377, 0.984807753012208, 0.981627183447664, 0.9781476007338057, 0.9743700647852352, 0.9702957262759965, 0.9659258262890683, 0.9612616959383189, 0.9563047559630355, 0.9510565162951536, 0.9455185755993168, 0.9396926207859084, 0.9335804264972017, 0.9271838545667874, 0.9205048534524404, 0.913545457642601, 0.90630778703665, 0.8987940462991669, 0.8910065241883679, 0.8829475928589271, 0.8746197071393959, 0.8660254037844387, 0.8571673007021123, 0.8480480961564261, 0.838670567945424, 0.8290375725550417, 0.819152044288992, 0.8090169943749475, 0.7986355100472927, 0.788010753606722, 0.777145961456971, 0.766044443118978, 0.7547095802227718, 0.7431448254773942, 0.7313537016191706, 0.7193398003386514, 0.7071067811865476, 0.6946583704589971, 
    0.6819983600624985, 0.6691306063588583, 0.6560590289905073, 0.6427876096865395, 0.6293203910498377, 0.6156614753256584, 0.6018150231520482, 0.5877852522924732, 0.5735764363510464, 0.5591929034707469, 0.5446390350150269, 0.5299192642332049, 0.5150380749100544, 0.49999999999999994, 0.48480962024633717, 0.4694715627858911, 0.45399049973954686, 0.4383711467890773, 0.4226182617406995, 0.40673664307580043, 0.39073112848927416, 0.37460659341591224, 0.3583679495453002, 0.3420201433256689, 0.32556815445715703, 0.3090169943749475, 0.29237170472273705, 0.27563735581699966, 0.258819045102521, 0.24192189559966773, 0.22495105434386478, 0.20791169081775931, 0.19080899537654497, 0.17364817766693028, 0.15643446504023098, 0.13917310096006574, 0.12186934340514755, 0.10452846326765373, 0.08715574274765864, 0.06975647374412552, 0.05233595624294381, 0.0348994967025007, 0.01745240643728344,
    0.0, -0.017452406437283192, -0.0348994967025009, -0.052335956242943564, -0.06975647374412483, -0.08715574274765794, -0.10452846326765305, -0.12186934340514774, -0.13917310096006552, -0.15643446504023073, -0.17364817766693047, -0.19080899537654472, -0.20791169081775907, -0.22495105434386498, -0.2419218955996675, -0.25881904510252035, -0.275637355816999, -0.2923717047227364, -0.30901699437494773, -0.32556815445715676, -0.34202014332566866, -0.35836794954530043, -0.374606593415912, -0.39073112848927355, -0.4067366430757998, -0.4226182617406993, -0.43837114678907707, -0.45399049973954625, -0.46947156278589086, -0.48480962024633695, -0.5000000000000001, -0.5150380749100542, -0.5299192642332048, -0.5446390350150271, -0.5591929034707467, -0.5735764363510458, -0.587785252292473, -0.601815023152048, -0.6156614753256578, -0.6293203910498376, -0.6427876096865393, -0.6560590289905074, -0.6691306063588582, 
    -0.6819983600624984, -0.6946583704589973, -0.7071067811865475, -0.7193398003386509, -0.7313537016191701, -0.743144825477394, -0.7547095802227717, -0.7660444431189779, -0.7771459614569711, -0.7880107536067221, -0.7986355100472928, -0.8090169943749473, -0.8191520442889916, -0.8290375725550414, -0.8386705679454242, -0.848048096156426, -0.8571673007021121, -0.8660254037844385, -0.8746197071393959, -0.882947592858927, -0.8910065241883678, -0.8987940462991668, -0.9063077870366497, -0.913545457642601, -0.9205048534524403, -0.9271838545667873, -0.9335804264972016, -0.9396926207859082, -0.9455185755993168, -0.9510565162951535, -0.9563047559630353, -0.961261695938319, -0.9659258262890683, -0.9702957262759965, -0.9743700647852351, -0.9781476007338056, -0.9816271834476639, -0.984807753012208, -0.9876883405951377, -0.9902680687415704, -0.9925461516413221, -0.9945218953682734, -0.9961946980917455,-0.9975640502598242, -0.9986295347545738, -0.9993908270190957, -0.9998476951563913,
    -1.0, -0.9998476951563913, -0.9993908270190958, -0.9986295347545738, -0.9975640502598243, -0.9961946980917455, -0.9945218953682734, -0.992546151641322, -0.9902680687415704, -0.9876883405951378, -0.9848077530122081, -0.9816271834476641, -0.9781476007338058, -0.9743700647852352, -0.9702957262759966, -0.9659258262890682, -0.9612616959383188, -0.9563047559630354, -0.9510565162951536, -0.945518575599317, -0.9396926207859085, -0.9335804264972021, -0.9271838545667874, -0.9205048534524405, -0.9135454576426008, -0.9063077870366498, -0.898794046299167, -0.891006524188368, -0.8829475928589271, -0.8746197071393961, -0.8660254037844386, -0.8571673007021123, -0.8480480961564261, -0.8386705679454243, -0.8290375725550421, -0.8191520442889918, -0.8090169943749476, -0.798635510047293, -0.7880107536067218, -0.7771459614569708, -0.7660444431189781, -0.7547095802227722, -0.7431448254773946, -0.731353701619171, 
    -0.7193398003386517, -0.7071067811865477, -0.6946583704589976, -0.6819983600624983, -0.6691306063588581, -0.6560590289905074, -0.6427876096865396, -0.6293203910498378, -0.6156614753256588, -0.6018150231520483, -0.5877852522924734, -0.5735764363510465, -0.5591929034707473, -0.544639035015027, -0.5299192642332058, -0.5150380749100545, -0.5000000000000004, -0.4848096202463369, -0.4694715627858908, -0.45399049973954697, -0.438371146789077, -0.4226182617407, -0.40673664307580015, -0.3907311284892747, -0.37460659341591235, -0.35836794954530077, -0.3420201433256686, -0.32556815445715753, -0.3090169943749477, -0.29237170472273627, -0.2756373558169998, -0.2588190451025207, -0.24192189559966787, -0.22495105434386534, -0.20791169081775987, -0.19080899537654467, -0.17364817766693127, -0.1564344650402311, -0.13917310096006588, -0.12186934340514811, -0.10452846326765342, -0.08715574274765832, -0.06975647374412476, -0.05233595624294437, -0.034899496702500823, -0.01745240643728445
};

const float freqMap[] = {
    /*         C          C#          D           D#          E           F           F#          G           G#         A       A#           B     */
    /* C- */ 1,         1,          1,          1,          1,          1,          1,          1,          1,          1,      1,          1,      
    /* C0 */ 16.35,     17.32,      18.35,      19.45,      20.6,       21.83,      23.12,      24.5,       25.96,      27.5,   29.14,      30.87,
    /* C1 */ 32.7,      34.65,      36.71,      38.89,      41.2,       43.65,      46.25,      49,         51.91,      55,     58.27,      61.74,
    /* C2 */ 65.41,     69.3,       73.42,      77.78,      82.41,      87.31,      92.5,       98,         103.83,     110,    116.54,     123.47,
    /* C3 */ 130.81,    138.59,     146.83,     155.56,     164.81,     174.61,     185,        196,        207.65,     220,    233.08,     246.94,
    /* C4 */ 261.63,    277.18,     293.66,     311.13,     329.63,     349.23,     369.99,     392,        415.3,      440,    466.16,     493.88,
    /* C5 */ 523.25,    554.37,     587.33,     622.25,     659.25,     698.46,     739.99,     783.99,     830.61,     880,    932.33,     987.77,
    /* C6 */ 1046.5,    1108.73,    1174.66,    1244.51,    1318.51,    1396.91,    1479.98,    1567.98,    1661.22,    1760,   1864.66,    1975.53,
    /* C7 */ 2093,      2217.46,    2349.32,    2489.02,    2637.02,    2793.83,    2959.96,    3135.96,    3322.44,    3520,   3729.31,    3951.07,
    /* C8 */ 4186.01,   4434.92,    4698.63,    4978.03,    5274.04,    5587.65,    5919.91,    6271.93,    6644.88,    7040,   7458.62,    7902.13,
    /* C9 */ 1,         1,          1,          1,          1,          1,          1,          1
};

uint8_t midiPlayFreqMap[128];
uint16_t i2srawdata0[2048];
uint16_t i2srawdata1[2048];

IRAM_ATTR double fastSin(double deg)
{
    int integer = (int)deg%360;
    //int point = deg - integer;
    return sinmap[integer];
}

static QueueHandle_t i2sstateQueue = nullptr;
static QueueHandle_t i2sAudioEndQueue = nullptr;

void speakerPlayTask(void *arg)
{
    i2sQueueMsg_t QueueMsg;
    while (1)
    {
        if (xQueueReceive(i2sstateQueue, &QueueMsg, portMAX_DELAY) == pdTRUE)
        {
            if (QueueMsg.type == kTypeAudio)
            {
                audioParameters_t *pam = (audioParameters_t *)QueueMsg.dataptr;
                size_t bytes_written = 0;
                i2s_write(SPAKER_I2S_NUMBER, pam->pAudioData, pam->length, &bytes_written, portMAX_DELAY);
                //Serial.printf("point :%p\r\n",pam->pAudioData);
                if( pam->freeFlag == true ) xQueueSend(i2sAudioEndQueue, &pam->pAudioData, (TickType_t)0);
                //delay(1);
                //delete (uint16_t*)pam->pAudioData;
                delete pam;
            }
            else if (QueueMsg.type == kTypeBeep)
            {
                beepParameters_t *pam = (beepParameters_t *)QueueMsg.dataptr;
                size_t bytes_written = 0;
                size_t count = 0, length = 0;
            
                double t = (1 / (double)pam->freq) * (double)pam->rate;
                
                if (pam->time > 1000)
                {
                    length = pam->rate * (pam->time % 1000) / 1000;
                    count = pam->time / 1000;
                }
                else
                {
                    length = pam->rate * pam->time / 1000;
                    count = 0;
                }
                int rawLength = ( count == 0 ) ? length : pam->rate;
                rawLength -= (int)((int)(rawLength % (int)t));
                
                int16_t *raw = (int16_t *)ps_calloc(rawLength, sizeof(int16_t));
                for (int i = 0; i < rawLength; i++)
                {
                    double val = 0;
                    if( i < 1000 )
                    {
                        val = pam->maxval * i / 1000;
                    }
                    else if( i > ( rawLength - 1000 ))
                    {
                        val = pam->maxval - pam->maxval * ( 1000 - ( rawLength - i )) / 1000;
                    }
                    else
                    {
                        val = pam->maxval;
                    }
                    if( pam->freq == 0 )
                    {
                        raw[i] = 0;
                    }
                    else
                    {
                        raw[i] = (int16_t)(((fastSin(360 * i / t ) + 0 ) * val));
                    }
                }
                //for (int i = 0; i < count; i++)
                //{
                //    i2s_write(SPAKER_I2S_NUMBER, raw, pam->rate, &bytes_written, portMAX_DELAY);
                //}

                if (rawLength != 0)
                {
                    i2s_write(SPAKER_I2S_NUMBER, raw, ( rawLength ) * 2 , &bytes_written, portMAX_DELAY);
                    Serial.printf("I2S Write\r\n");
                }
                delete pam;
                delete raw;
            }
        }
        delay(1);
    }
}

Speaker::Speaker(/* args */)
{
}

Speaker::~Speaker()
{
}

bool Speaker::begin(int __rate, bool __threadEnable)
{
    esp_err_t err = ESP_OK;

    i2s_driver_uninstall(SPAKER_I2S_NUMBER);
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER),
        .sample_rate = __rate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 2,
        .dma_buf_len = 128,
    };
    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
    i2s_config.use_apll = false;
    i2s_config.tx_desc_auto_clear = true;

    err += i2s_driver_install(SPAKER_I2S_NUMBER, &i2s_config, 0, NULL);
    i2s_pin_config_t tx_pin_config;

    tx_pin_config.bck_io_num = CONFIG_I2S_BCK_PIN;
    tx_pin_config.ws_io_num = CONFIG_I2S_LRCK_PIN;
    tx_pin_config.data_out_num = CONFIG_I2S_DATA_PIN;
    tx_pin_config.data_in_num = CONFIG_I2S_DATA_IN_PIN;

    err += i2s_set_pin(SPAKER_I2S_NUMBER, &tx_pin_config);

    err += i2s_set_clk(SPAKER_I2S_NUMBER, __rate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

    _rate = __rate;
    i2sAudioEndQueue = xQueueCreate(1024, sizeof(uint16_t*));
    i2sstateQueue = xQueueCreate(1024, sizeof(i2sQueueMsg_t));
    if (i2sstateQueue == 0)
    {
        return false;
    }
    xTaskCreatePinnedToCore(speakerPlayTask, "speakerPlayTask", 4096, nullptr, 10, nullptr, 0);
    return (err == ESP_OK) ? true : false;
}

size_t Speaker::playRAW(const uint8_t *__audioPtr, size_t __size, bool modal, bool freeFlag,TickType_t __ticksToWait)
{
    size_t writeSize = 0;
    if (modal == false)
    {
        audioParameters_t *pam = (audioParameters_t *)malloc(sizeof(audioParameters_t));
        pam->pAudioData = (void *)__audioPtr;
        pam->length = __size;
        pam->freeFlag = freeFlag;
        i2sQueueMsg_t msg = {.type = kTypeAudio, .dataptr = pam};
        xQueueSend(i2sstateQueue, &msg, (TickType_t)0);
        //xTaskCreatePinnedToCore(speakerAudioTask, "speakerAudioTask", 4096, pam, 3, NULL, 0);
    }
    else
    {
        i2s_write(SPAKER_I2S_NUMBER, __audioPtr, __size, &writeSize, __ticksToWait);
    }
    return writeSize;
}

uint64_t time_a = 0;

size_t Speaker::playBeep(int __freq, int __timems, int __maxval, bool __modal)
{
    size_t writeSize = 0;

    if (__modal == false)
    {
        beepParameters_t *pam = (beepParameters_t *)malloc(sizeof(beepParameters_t));
        pam->freq = __freq;
        pam->time = __timems;
        pam->rate = _rate;
        pam->maxval = __maxval;

        i2sQueueMsg_t msg = {.type = kTypeBeep, .dataptr = pam};
        xQueueSend(i2sstateQueue, &msg, (TickType_t)0);
        //xTaskCreatePinnedToCore(speakerBeepTask, "speakerBeepTask", 4096, pam, 3, NULL, 0);
    }
    else
    {
        size_t bytes_written = 0;
        size_t count = 0, length = 0;

        double t = (1 / (double)__freq) * (double)_rate;

        if (__timems > 1000)
        {
            length = _rate * (__timems % 1000) / 1000;
            count = __timems / 1000;
        }
        else
        {
            length = _rate * __timems / 1000;
            count = 0;
        }
        int rawLength = ( count == 0 ) ? length : _rate;

        uint16_t *raw = (uint16_t *)ps_calloc(rawLength, sizeof(uint16_t));

        for (int i = 0; i < rawLength; i++)
        {
            int val = 0;
            if( i < 100 )
            {
                val = __maxval * i / 100;
            }
            else if( i > ( rawLength - 1000 ))
            {
                
                val = __maxval - __maxval * ( 1000 - ( rawLength - i )) / 1000;
            }
            else
            {
                val = __maxval;
            }
            raw[i] = (uint16_t)((fastSin(360 / t * i)) * val);
        }

        for (int i = 0; i < count; i++)
        {
            i2s_write(SPAKER_I2S_NUMBER, raw, _rate, &bytes_written, portMAX_DELAY);
        }
        if (length != 0)
        {
            i2s_write(SPAKER_I2S_NUMBER, raw, length, &bytes_written, portMAX_DELAY);
        }
        delete raw;
    }
    return writeSize;
}
uint8_t Speaker::getint8DataFromMidi( const uint8_t* ptr, size_t* point )
{
    uint8_t data =  (*( ptr + *point));
    point ++;
    return data;
}

uint16_t Speaker::getint16DataFromMidi( const uint8_t* ptr, size_t* point )
{
    uint32_t data = 0;
    for (int i = 0; i < 2; i++)
    {
        data <<= 8;
        data += (*( ptr + ( *point + i ))&0xff); 
    }
    *point += 2;
    return data;
}
uint32_t Speaker::getint32DataFromMidi( const uint8_t* ptr, size_t* point )
{
    uint32_t data = 0;
    for (int i = 0; i < 4; i++)
    {
        data <<= 8;
        data += (*( ptr + ( *point + i ))&0xff); 
    }
    *point += 4;
    return data;
}
uint64_t Speaker::getint64DataFromMidi( const uint8_t* ptr, size_t* point )
{
    uint64_t data = 0;
    for (int i = 0; i < 8; i++)
    {
        data <<= 8;
        data += (*( ptr + ( *point + i ))&0xff); 
    }
    *point += 8;
    return data;
}
uint8_t Speaker::getArrayFromMidi( const uint8_t* ptr, size_t length, size_t* point )
{
    return 0;
}
String Speaker::getStringFromMidi( const uint8_t* ptr, size_t length, size_t* point )
{
    char* strbuff = (char*)malloc(sizeof(char)*(length + 1 ));
    for (int i = 0; i < length; i++)
    {
        strbuff[i] = *( ptr + *point + i );
    }
    *point += length;
    strbuff[length] = '\0';
    String str(strbuff);
    delete strbuff;
    return str;
}

int Speaker::playMidi(const uint8_t *data)
{
    uint32_t phase[128];
    double valbuff[128];
    double tickTime = 0.874125;

    uint64_t tickCount = 0, ctrlCmdtickCount;
    size_t _readPoint = 0;
    String head = getStringFromMidi(data,4,&_readPoint);
    if( head != "MThd")
    {
        Serial.printf("[Error] Header Chunk header error\r\n");
        return -1;
    }
    struct midiInfo info;
    info.HeaderChunkLength = getint32DataFromMidi(data,&_readPoint);
    info.MidiType = getint16DataFromMidi(data,&_readPoint);
    info.TrackChunkNum = getint16DataFromMidi(data,&_readPoint);
    info.TickNum = getint16DataFromMidi(data,&_readPoint);

    Serial.printf("Header Chunk Length:%d\r\n",info.HeaderChunkLength );
    Serial.printf("Tick Numbet %d\r\n",info.TickNum);

    info.ChunkInfo = (TrackChunkInfo*)calloc(info.TrackChunkNum,sizeof(TrackChunkInfo));
    _readPoint = info.HeaderChunkLength + 8;

    midiTickTimeList_t *midiTickTimeHead = new midiTickTimeList_t();

    for( int i = 0; i < info.TrackChunkNum; i++ )
    {
        info.ChunkInfo[i].seek = _readPoint;
        String TrackChunkHead = getStringFromMidi(data,4,&_readPoint);
        if( TrackChunkHead != "MTrk")
        {
            Serial.printf("[Error] Track Chunk header error\r\n");
            return -1;
        }
        info.ChunkInfo[i].length = getint32DataFromMidi(data,&_readPoint);
        Serial.printf("Find Track Chunk %d at %d size:%d\r\n",i, info.ChunkInfo[i].seek, info.ChunkInfo[i].length );
        _readPoint = info.ChunkInfo[i].seek + info.ChunkInfo[i].length + 8 ;
    }

    for( int i = 0; i < 128; i++ )
    {
        valbuff[i] = 0;
        midiPlayFreqMap[i] = 0;
        phase[i] = 0;
    }
    struct midiCmdData miditrck;
    miditrck.TickTime = 0;

    for( int i = 0; i < info.TrackChunkNum; i++ )
    {
        tickCount = ctrlCmdtickCount = 0;
        _readPoint = info.ChunkInfo[i].seek + 8;
        while( _readPoint < ( info.ChunkInfo[i].seek + info.ChunkInfo[i].length ))
        {
            do
            {
                miditrck.TickTime <<= 7;
                miditrck.TickTime += *( data + _readPoint ) & 0x7f;
            } while ((*( data + ( _readPoint++ )))&0x80);

            miditrck.cmd = *( data + (_readPoint ++ ));

            if(( miditrck.TickTime != 0 )&&(( miditrck.cmd == 0x80 )||( miditrck.cmd == 0x90 )))
            {

                tickCount += miditrck.TickTime;
                tickTime = midiTickTimeHead->getTickTime(tickCount);

                //Serial.printf("%d Set tickTime to %f\r\n",tickCount,tickTime);

                uint32_t Delattime = (uint32_t)((float)miditrck.TickTime * tickTime);
                uint32_t length = _rate * Delattime / 1000;
                int16_t* audioDataPtr = (int16_t *)ps_calloc(length,sizeof(int16_t));

                memset( audioDataPtr,0,sizeof(int16_t) * length );
                for( int n = 0; n < 128; n++ )
                {
                    if( midiPlayFreqMap[n] == 0 )continue;
                    double clon = (1 / (double)freqMap[n]) * (double)_rate;
                    if( midiPlayFreqMap[n] & 0x80 )
                    {
                        double val = ( midiPlayFreqMap[n] & 0x7f ) * 100;
                        valbuff[n] = val;
                        for (uint32_t t = 0; t < length; t++)
                        {
                            audioDataPtr[t] += (int16_t)(( fastSin( ( 360 / clon ) * ( phase[n] + t ) ) * val ));
                        }
                        phase[n] += length;
                    }
                    else if(( midiPlayFreqMap[n] > 0 )&&( midiPlayFreqMap[n] <= 0x7f))
                    {
                        uint16_t gain = 50;
                        uint32_t attenuationTime = 0;
                        do{
                            attenuationTime = midiPlayFreqMap[n] * gain;
                            gain -= 2;
                        }while(( attenuationTime > length )&&( gain > 0 ));
                        
                        double val = valbuff[n];
                        
                        if( attenuationTime > length )
                        {
                            attenuationTime = length;
                        }
                        for (uint32_t t = 0; t < attenuationTime; t++)
                        {
                            audioDataPtr[t] += (int16_t)((fastSin(( 360 / clon ) * ( t + phase[n] )) * ( val * ( attenuationTime - t)) / attenuationTime));
                        }
                        midiPlayFreqMap[n] = 0;
                        phase[n] = 0;
                    }
                    else
                    {
                        phase[n] = 0;
                    }
                }
                if( uxQueueMessagesWaiting(i2sstateQueue) > 8 )
                {
                    while( uxQueueMessagesWaiting(i2sstateQueue) > 3 )
                    {
                        uint16_t *ptr = nullptr;
                        if (xQueueReceive(i2sAudioEndQueue, &ptr, portMAX_DELAY ) == pdTRUE )
                        {
                            delete ptr;
                        }
                    }
                }
                playRAW((uint8_t*)audioDataPtr,(size_t)length*2);
            }
            if( miditrck.cmd == 0xff )
            {
                uint8_t otherCMD = *( data + (_readPoint ++ ));
                uint8_t otherLength = *( data + (_readPoint ++ ));
                ctrlCmdtickCount += miditrck.TickTime;
                
                uint8_t *otherDataptr =(uint8_t*)ps_calloc(otherLength,sizeof(uint8_t));
                for (int count = 0; count < otherLength; count++)
                {
                    otherDataptr[count] = *( data + _readPoint + count );
                }
                if( otherCMD == 0x51 )
                {
                    uint32_t bpm = 0;
                    for( int num = 0; num < 3; num ++ )
                    {
                        bpm <<= 8;
                        bpm += otherDataptr[num];
                    }
                    double tickTimeSet = (double)bpm/1000/info.TickNum;
                    midiTickTimeHead->addtickTime2List(ctrlCmdtickCount,(double)tickTimeSet);
                    //Serial.printf("set tickTime %f on %d\r\n", tickTimeSet, ctrlCmdtickCount);
                }
                delete otherDataptr;
                
                _readPoint += otherLength;
            }
            else if (miditrck.cmd == 0xf0) 
            {
                uint8_t sysLength = *( data + (_readPoint ++ ));
                _readPoint += sysLength;
            }
            else
            {
                miditrck.cmd &= 0xf0;
                if( miditrck.cmd == 0x80 )
                {
                    uint8_t freq = *( data + (_readPoint ++ ));
                    uint8_t val = *( data + (_readPoint ++ ));
                    midiPlayFreqMap[freq] = val & 0x7f;
                }
                else if( miditrck.cmd == 0x90 )
                {
                    uint8_t freq = *( data + (_readPoint ++ ));
                    uint8_t val = *( data + (_readPoint ++ ));
                    midiPlayFreqMap[freq] = 0x80 + val;
                }
                else if( miditrck.cmd == 0xA0 )
                {
                    _readPoint += 2;
                }
                else if( miditrck.cmd == 0xB0 )
                {
                    _readPoint += 2;
                }
                else if( miditrck.cmd == 0xC0 )
                {
                    _readPoint += 1;
                }
                else if( miditrck.cmd == 0xD0 )
                {
                    _readPoint += 1;
                }
                else if( miditrck.cmd == 0xE0 )
                {
                    _readPoint += 2;
                }
                else
                {
                    Serial.printf("Unknow cmd %02X\r\n",miditrck.cmd);
                    //_readPoint += 1;
                    return -1;
                }
            }
            miditrck.TickTime = 0;
        }
    }
    while(1)
    {
        uint16_t *ptr = nullptr;
        if (xQueueReceive(i2sAudioEndQueue, &ptr, portMAX_DELAY ) == pdTRUE )
        {
            Serial.printf("delete point :%p\r\n",ptr);
            delete ptr;
        }
        if(uxQueueMessagesWaiting(i2sstateQueue) == 0 )
        {
            break;
        }
        delay(10);
    }
    return 0;
}
