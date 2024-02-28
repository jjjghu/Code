#define B0 31
#define C1 33
#define CS1 35
#define D1 37
#define DS1 39
#define E1 41
#define F1 44
#define FS1 46
#define G1 49
#define GS1 52
#define A1 55
#define AS1 58
#define B1 62
#define C2 65
#define CS2 69
#define D2 73
#define DS2 78
#define E2 82
#define F2 87
#define FS2 93
#define G2 98
#define GS2 104
#define A2 110
#define AS2 117
#define B2 123
#define C3 131
#define CS3 139
#define D3 147
#define DS3 156
#define E3 165
#define F3 175
#define FS3 185
#define G3 196
#define GS3 208
#define A3 220
#define AS3 233
#define B3 247
#define C4 262
#define CS4 277
#define D4 294
#define DS4 311
#define E4 330
#define F4 349
#define FS4 370
#define G4 392
#define GS4 415
#define A4 440
#define AS4 466
#define B4 494
#define C5 523
#define CS5 554
#define D5 587
#define DS5 622
#define E5 659
#define F5 698
#define FS5 740
#define G5 784
#define GS5 831
#define A5 880
#define AS5 932
#define B5 988
#define C6 1047
#define CS6 1109
#define D6 1175
#define DS6 1245
#define E6 1319
#define F6 1397
#define FS6 1480
#define G6 1568
#define GS6 1661
#define A6 1760
#define AS6 1865
#define B6 1976
#define C7 2093
#define CS7 2217
#define D7 2349
#define DS7 2489
#define E7 2637
#define F7 2794
#define FS7 2960
#define G7 3136
#define GS7 3322
#define A7 3520
#define AS7 3729
#define B7 3951
#define C8 4186
#define CS8 4435
#define D8 4699
#define DS8 4978
const int BUZZ2 = 3;

#define DEATH_MELODY_SIZE 12
const short buzz2_deathMelody_freq[DEATH_MELODY_SIZE] = {
    00, C4, 00, C4, C4, C4, A3, G3, F3, 00, 00, 00, 
};
const short deathMelody_duration[DEATH_MELODY_SIZE] = {
     1,  1,  1,  1,  2,  2,  2,  2,  1,  3,  1,  8
};
const bool deathMelody_continuous[DEATH_MELODY_SIZE] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

#define MENU_MELODY_SIZE 37
const short menu_freq[MENU_MELODY_SIZE] = {
    00, 00, 00, E4, 00, F4, 00, E4, F4, G4, 00,
    E4, 00, F4, 00, E4, F4, G4, 00,
    00, G4, 00, E4, 00, A4, A4, 00, E4, 00,
    00, 00, 00, 00, E4, A3, G4, G4,
};
const short menu_duration[MENU_MELODY_SIZE] = {
     2,  2,  2,  4,  4,  4,  2,  4,  4,  4,  6,
     4,  4,  4,  2,  4,  4,  4,  6,
     2,  6,  0,  8,  2,  2,  2,  2,  8,  2,
     4,  4,  4,  4,  4,  2,  2,  8,
};
const bool menu_break[MENU_MELODY_SIZE] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  1,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  1,  0,  1,  1,  0
};
#define SUSPECT_MELODY_SIZE 310//293
const short melody_freq[SUSPECT_MELODY_SIZE] = {
    D3, 00,CS3, 00, B2, A2, G2, 00, D3, 00,CS3, 00, B2, A2, G2, 00,
    D3, 00,CS3, 00, B2, A2, G2, 00, D3, 00, B2, 00, B1, 00, B2, 00,
    G4, G4, D4, D4, D4, D4, D4, D4, G4, G4, 00, A4,CS5, D5,
    B3, B3, B2, B2, B3, B3, B2, B2, B3, B3, B2, B2, B3, B3, A4, D5,

    00, 00, G3, 00, 00, G3, 00, 00, A3, 00, 00, G3, A3, D4, F4, F4,
    G4, G4, E4, E4, D4, D4, A3, A3, D4, C4, A3, G3, G3, A3,
    B4, B4, F5, F5, B4, B4, F5, F5, B4, B4, F5, F5, 00, A4,CS5, D5,
    G4, G4, E4, E4, D4, D4, A3, A3, D4, C4, A3, G3, G3, A3, A4, D5,

    00, 00, G3, 00, 00, G3, 00, 00, A3, 00, 00, G3, A3, D4, F4, F4,
    G3, G3, E3, E3, D3, D3, A2, A2, D3, C3, A2, G2, G2, D5, D4,
    G3, C3, G3, C3, B3, E3, B3, E3, F4, D4, D4, C4, A3,
    C4, A3, C4, G3, C4, G3, C4, C4, C4, D4, D4,

    G3, C3, G3, C3, B3, E3, B3, E3, F4, D4, D4, A3, 00,
    C4, A3, C4, G3, C4, G3, C4, C4, C4, D4, D4,
    00, G3, A3, G4, D4, G3, A4, D4,
    C5, D4, D4, D4, D4, D4,

    00, D4, C4, A3, C4, A3, C3, D3, 00,

    D4, D4, E4, D4, C4, F4, F4, G4, D4, C4, A3, F3,
    00, F4, F4, F4, F4, C4, C4, A3, C4, A3, A3, C4, E4, 00, F4,

    D4, D4, E4, D5, D4, A3, A3, A3, E4, F4, D4, 00,
    D4, D4, D4, E4, F4, E4, E4, F4, A4, C4, 00,

    D4, G3, 00, C4, G3, 00, D4, D4, E4, E4, D4, 00,
    D4, D4, 00, C4, C4, 00, A4, A4, G4, G4, F4, A4,
    E4, F4, 00, D4, G4, A3, G3
};

const short melody_duration[SUSPECT_MELODY_SIZE] = {
     2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  1,  4,
     4,  4,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,
     3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,

     2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  2,  2,  2,  2,  2,  2,  4,  4,  2,  2,  2,  2,
     3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,
     3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3,  1,

     2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  4,
     1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  1,
     2,  2,  1,  1,  1,  1,  1,  1,  1,  4,  1,

     1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  1,  2,
     2,  2,  1,  1,  1,  1,  1,  1,  1,  4,  1,
     2,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  4,  2,  2,  4,

     2,  2,  2,  2,  2,  2,  2,  2,  16,

     4,  4,  2,  4,  4,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  4,

     4,  4,  2,  4,  4,  2,  2,  2,  4,  4,  2,  2,
     2,  8,  1,  1,  2,  2,  2,  2,  4,  4,  4,

     2,  2,  4,  2,  2,  2,  2,  2,  2,  4,  4,  4,
     2,  2,  4,  2,  2,  2,  2,  2,  2,  2,  2,  4,
     2,  2,  2,  2,  2,  4, 16
};

const bool melody_break[SUSPECT_MELODY_SIZE] = {0};

volatile bool startTone = false;
const short* curSong, *curSongDuration;
const bool* songBreak;

volatile int curPosition = 0;
volatile int curSongLength = DEATH_MELODY_SIZE;
volatile short progress = 0;

void setup()
{
    pinMode(BUZZ2, OUTPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);

    // Serial.begin(9600);
    // curSong = melody_freq;
    // songBreak = menu_break;
    // curSongDuration = melody_duration;
    // curSongLength = SUSPECT_MELODY_SIZE;
    // curPosition = 0;
}

bool playing = false;
int record = 0B0010;
bool songChanged = false;

void loop()
{
    // init buffer and pointer
    bool pin6 = digitalRead(6)==HIGH;
    bool pin7 = digitalRead(7)==HIGH;

    // check recieved message, and it's different song
    if(record != ((1<<1)*(pin6)|(1*pin7))){
        // inform its partner
        digitalWrite(12, pin6*HIGH);
        digitalWrite(13, pin7*HIGH);

        // update state
        record = ((1<<1)*(pin6)|(1*pin7));
        songChanged = true;

        if(pin6 && !pin7){
            curSong = menu_freq;
            curSongDuration = menu_duration;
            songBreak = menu_break;
            curSongLength = MENU_MELODY_SIZE;
        }
        if(!pin6 && pin7){
            curSong = melody_freq;
            curSongDuration = melody_duration;
            songBreak = melody_break;
            curSongLength = SUSPECT_MELODY_SIZE;
        }
        if(pin6 && pin7){
            curSong = buzz2_deathMelody_freq;
            curSongDuration = deathMelody_duration;
            songBreak = deathMelody_continuous;
            curSongLength = DEATH_MELODY_SIZE;
        }
    }
    
    
    if(!playing || songChanged){
        songChanged = false;

        playing = true;
        curPosition = 0;
    }
    if(playing){
        // play the theme
        noTone(BUZZ2);
        tone(BUZZ2, curSong[curPosition], curSongDuration[curPosition]*125 -25*songBreak[curPosition]);
        delay(curSongDuration[curPosition]*125);
        curPosition++;
        if(curPosition == curSongLength){
            playing = false;
            noTone(BUZZ2);
        }
    }
}
