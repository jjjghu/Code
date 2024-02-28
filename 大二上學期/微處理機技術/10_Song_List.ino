#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
//音階列表 來自 https://dragaosemchama.com/en/2019/02/songs-for-arduino/
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
int chosen; // 選定的歌曲
const int buzzer = 3;
const int B = 5;
const int A = 6;
#define TFT_CS 8
#define TFT_RST 9
#define TFT_DC 10
#define TFT_MOSI 11
#define TFT_CLK 12
#define TFT_MISO 13
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
void setup()
{
  Serial.begin(9600);
  pinMode(A, INPUT_PULLUP); // 按鈕 A 選定歌曲
  pinMode(B, INPUT_PULLUP); // 按下 B 播放歌曲
  tft.begin();
  chosen = 0; // 預設選第一首
  tft.fillScreen(ILI9341_BLACK); // 將螢幕顯示黑
  tft.setTextSize(2.8); // 顯示字體大小
  Showlist(); // 顯示歌曲列表
}
int lastupdate = millis(); // 紀錄上次更新時間, 用於判斷按下按鈕的間隔
bool prevStateA = true; // 前狀態
bool prevStateB = true;
String name[] = {"Megalovania", "Shiny Smily Story", "NO MORE, i'll DIE", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "A", "B"}; // 顯示的歌單
void loop() 
{
    if(!digitalRead(A) /*&& prevStateA == true*/) //digitalRead判斷按下狀態 prevState 避免長按一直跳, 想要一直跳可略
    {
      chosen++; // 按下就移動選擇的清單
      chosen %= (sizeof(name) / sizeof(String));
      if(chosen%20 == 0) tft.fillScreen(ILI9341_BLACK); // 每20個切換下一頁
      lastupdate = millis(); // 更新「更新時間」
      Showlist(); // 顯示更新之後的列表
    }
    if(!digitalRead(B)) // 可以不需要 prevStateB, 可以播了又播
    {
      Serial.println("Play a song !"); // 方便觀察, 可略
      PlaySong(chosen); // 播放被選擇的歌曲
    }
    //prevStateA = digitalRead(A); // 更新狀態
}
void Showlist()
{
  tft.setCursor(0, 0); // 從左上開始顯示
  for(int i = 20*(chosen / 20); i < sizeof(name) / sizeof(String); i++)
  {
    if(chosen == i) tft.setTextColor(ILI9341_YELLOW); // 如果是被選中的歌曲就顯示黃色
    else  tft.setTextColor(ILI9341_WHITE); // 沒被選到白色
    tft.println((i+1) + String(":") +String(name[i])); // 顯示歌曲
  }
}
void PlaySong(int chosen)// 播放歌曲, 可以改用陣列  // wait to be edit in the future, I believe in myself
{ // 使用內建的 tone 指令
  if(chosen == 0)
  {
    tone(buzzer,523,125);//C5
    delay(125);
    tone(buzzer,523,125);//C5
    delay(125);
    tone(buzzer,1175,250);//D6
    delay(250);
    tone(buzzer,880,250);//A5
    delay(325);
    tone(buzzer,831,125);//Ab5
    delay(250);
    tone(buzzer,784,250);//G5
    delay(250);
    tone(buzzer,698,250);//F5
    delay(250);
    tone(buzzer,587,125);//D5
    delay(125);
    tone(buzzer,698,125);//F5
    delay(125);
    tone(buzzer,784,125);//G5
    delay(125);
  }
  else if(chosen == 1)
  {
    tone(buzzer, NOTE_DS4, 100);
    delay(180);
    tone(buzzer, NOTE_F4, 100);
    delay(180);
    tone(buzzer, NOTE_G4, 145);
    delay(220);
    tone(buzzer, NOTE_GS4, 180);
    delay(300);
    tone(buzzer, NOTE_DS4, 200);
    delay(300);
    tone(buzzer, NOTE_AS4, 250);
    delay(250);
    tone(buzzer, NOTE_GS4, 225);
    delay(225);
    tone(buzzer, NOTE_G4, 300);
    delay(300);
    tone(buzzer, NOTE_GS4, 180);
    delay(180);
    tone(buzzer, NOTE_AS4, 150);
    delay(180);
    tone(buzzer, NOTE_C5, 450);
    delay(650);

    tone(buzzer, NOTE_GS4, 180);
    delay(300);
    tone(buzzer, NOTE_DS4, 200);
    delay(300);
    tone(buzzer, NOTE_AS4, 250);
    delay(250);
    tone(buzzer, NOTE_GS4, 225);
    delay(225);
    tone(buzzer, NOTE_G4, 300);
    delay(300);
    tone(buzzer, NOTE_GS4, 180);
    delay(180);
    tone(buzzer, NOTE_AS4, 150);
    delay(180);
    tone(buzzer, NOTE_C5, 450);
    delay(650);
  }
  else if(chosen == 2) //以下略
  {
    //... 
  }

}