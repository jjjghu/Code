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

const int BUZZ1 = 3;

#define DEATH_MELODY_SIZE 12
const short deathMelody_freq[DEATH_MELODY_SIZE] = {
    C4, G4, 00, G4, G4, G4, F4, E4, D4, G3, G3, C3
};
const short deathMelody_duration[DEATH_MELODY_SIZE] = {
     1,  1,  1,  1,  2,  2,  2,  2,  1,  3,  1,  8
};
const bool deathMelody_break[DEATH_MELODY_SIZE] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

#define MENU_MELODY_SIZE 36
const short menu_freq[MENU_MELODY_SIZE] = {
    G4, A4, B4, C5, G4, D5, C5, B4, C5, D5, E5,
    C5, G4, D5, C5, B4, C5, D5, E5,
    E5, F5, E5, C5, 00, F5, E5, 00, C5, 00,
    F5, E5, D5, C5, C5, D5, D5,
};
const short menu_duration[MENU_MELODY_SIZE] = {
     2,  2,  2,  4,  4,  2,  4,  4,  2,  2, 10,
     4,  4,  2,  4,  4,  2,  2, 10,
     2,  2,  4,  8,  2,  2,  2,  2,  8,  2,
     4,  4,  4,  4,  6,  2,  8,
};
const bool menu_break[MENU_MELODY_SIZE] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  1,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  1,  0,  1,  0,
};

#define YORUKAKE_MELODY_SIZE 50
const short yorukake_freq[YORUKAKE_MELODY_SIZE] = {
    E4, G4, A4, F4, E4, D4,
    C4, D4, A4, G4, A4, E4, D4, C4,
    A3, B3, C4, 00, B3, 00, F4, E4, 
    C5, B4, G4, A4, 00, G4, D4, E4
};
const short yorukake_duration[YORUKAKE_MELODY_SIZE] = {
     2,  2,  3,  3,  2,  2,
     2,  2,  2,  2,  1,  3,  2,  4,
     2,  2,  2, 01,  2, 01,  2,  2,
     2,  2,  2,  2, 01,  3,  2,  2
};
const bool yorukake_break[MENU_MELODY_SIZE] = {
     0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0, 
     0,  0,  0,  0,  0,  0,  0,  0
};

#define SUS_MELODY_SIZE 293
const short sus_freq[SUS_MELODY_SIZE] = {
    00, D4, 00, D4, 00, D4, 00, D4, 00, D4, 00, D4, 00, D4, 00, D4,
    00, D4, 00, D4, 00, D4, 00, D4, 00, D4, 00, D4, 00, D5, C5, D5,
    D5,GS5, G5, F5, G5, A5, G5, F5, E5, D5, 03, A4,CS5, D5,
    E5, F5, G5,GS5, A5, G5, F5, E5, D5, E5, D5,CS5, C5,AS5, A4, D5,

    F5, D5, 00, F5, D5, 00, F5, D5, 00, F5, D5, 00, F5, G5,GS5, A5,
    D6, C6,CS6, G5, A5, G5, F5, D5, A5, G5, F5, D5, C5, D5,
    C6, D6, C6,GS5, G5, F5, G5, A5, G5, F5, E5, D5, 00, A4,CS5, D5,
    E5, F5, G5,GS5, A5, G5, F5, E5, D5, E5, D5,CS5, C5,AS4, A4, D5,

    F5, D5, 00, F5, D5, 00, F5, D5, 00, F5, D5, 00, F5, G5,GS5, A5,
    D6, C6,CS6, G5, A5, G5, F5, G5,GS5, G5, F5, G5, 00, D5, D4,
    A4, G4, F4, G4, F4, D4, D4, C4, A3,
    C4, A3, C4, C4, C4, C4, C4, D4, D4,

    GS4,G4, F4, G4, F4, D4, D4, A3,
    C4, C4, C4, A3, F4, D4, D4, 00,
    00, D4, F4, G4,GS4, G4, F4, D5,
    C4/*5*/, G4, A4, G4, G4, A4,

    00, A4, G4, F4, G4, F4, C4, D4, 00,

    D4, D5, C5, D5, A4, F4, F4, G4, A4, G4, F4, D4,
    00, A4, A4, A4, A4, G4, G4, F4, G4, F4, F4, G4, G4, 00, A4,// gorgious here

    D4, D5, C5, D5, A4, F4, F4, F4, C5,CS5, D5, 00,
    F4, F4, F4, G4, A4, G4, G4, F4, A4, G4, 00,

    D4, D4, 00, C4, C4, 00, A4, A4, G4, G4, A4, 00,
    D4, D4, 00, C4, C4, 00, A4, A4, G4, G4, F4, A4,
    C5, D5, 00, A4, G4, F4, D4,
};
const short sus_duration[SUS_MELODY_SIZE] = {
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
     2,  2,  2,  2,  1,  2,  2,  2,  1,
     2,  2,  2,  2,  1,  1,  1,  4,  1,

     2,  2,  2,  2,  1,  2,  4,  1,
     2,  2,  1,  1,  1,  1,  6,  2,
     2,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  4,  2,  2,  4,

     2,  2,  2,  2,  2,  2,  2,  2,  16,

     4,  4,  2,  4,  4,  2,  2,  2,  2,  2,  2,  2,
     2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  4,

     4,  4,  2,  4,  4,  2,  2,  2,  4,  4,  2,  2,
     2,  8,  1,  1,  2,  2,  2,  2,  4,  4,  4,

     2,  2,  4,  2,  2,  2,  2,  2,  2,  4,  4,  4,
     2,  2,  4,  2,  2,  2,  2,  2,  2,  2,  2,  4,
     2,  2,  2,  2,  2,  4,  16,
};
const bool sus_break[SUS_MELODY_SIZE] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,

     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,

     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  1,  0,  0,  0,
     0,  0,  1,  1,  1,  1,  1,  0,  0,

     0,  0,  0,  0,  0,  1,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,

     0,  0,  0,  0,  0,  0,  0,  0,  0,

     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,

     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,

     1,  0,  0,  1,  0,  0,  1,  0,  1,  0,  0,  0,
     1,  0,  0,  1,  0,  0,  1,  0,  1,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,
};

volatile bool startTone = true;
const short* curSong, *curSongDuration;
const bool* songBreak;

volatile int scaler = 1;
volatile int curPosition = 0;
volatile int curSongLength;
volatile short progress = 0;
bool playing;

void setup()
{
    pinMode(BUZZ1, OUTPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);

    Serial.begin(9600);

    // playing = true;
    // curSong = menu_freq;
    // curSongDuration = menu_duration;
    // songBreak = menu_break;
    // curSongLength = MENU_MELODY_SIZE;
}

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
            curSong = sus_freq;
            curSongDuration = sus_duration;
            songBreak = sus_break;
            curSongLength = SUS_MELODY_SIZE;
        }
        if(pin6 && pin7){
            curSong = deathMelody_freq;
            curSongDuration = deathMelody_duration;
            songBreak = deathMelody_break;
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
        noTone(BUZZ1);
        tone(BUZZ1, curSong[curPosition], curSongDuration[curPosition]*125 -25*songBreak[curPosition]);
        delay(curSongDuration[curPosition]*125);
        curPosition++;
        if(curPosition == curSongLength){
            playing = false;
            noTone(BUZZ1);
        }
    }
}
