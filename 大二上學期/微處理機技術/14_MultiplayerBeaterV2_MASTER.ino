// 這是效率優先, 閹割顯示品質的版本, 但也優化了很多地方
// S1154041 邱立宇
// 在按下按鈕的時候, 就算顏色不隊也可能會加分,
// 像是在index++之後才按下按鈕, 螢幕還沒更新, 就會出現這樣的狀況
#define C3 131
#define G3 196
#define B3 247
#define C4 262
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880
#define none 0
// 定義頻率, 方便寫音樂
const int song[] = {none, none, none,
              C4, B4, G4, B4, C4, B4, G4, B4, C4, B4, G4, B4, C4, B4, G4, B4,
              C3, B3, G3, B3, C3, B3, G3, B3, B4, C5, D5, E5, E5, D5, B4, C5, B4, G4, B4,
              B4, E5, D5, E5, E5, G5, G5, E5, E5, D5, none, B4, 
              F5, E5, E5, C5, C5, A4, C5, B4, G4, G4, E5, D5, none,
              F5, E5, E5, C5, C5, A4, A5, G5, E5, D5, B4, G4, none,
              G5, E5, G5, none, G5, E5, G5, none, G5, E5, G5, none, G5, E5, G5, none};
              //歌曲內容
const int a = 61250; // 1 sec
const int b = 50000; // 800 ms
const int c = 25000; // 400 ms
const int tempo[] = { c,c,c,
                b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,
                b,b,b,b,b,b,b,b,c,c,c,c,c,c,b,b,b,b,b,
                c,c,c,c,c,c,c,c,b,b,b,b,
                c,c,c,c,c,c,b,c,c,c,b,b,c,
                c,c,c,c,c,c,b,b,c,b,b,c,b,
                b,b,b,b,b,b,b,b,b,b,b,b,b,b,a,a};
                //對應速度
#include<Adafruit_GFX.h>
#include<Adafruit_ILI9341.h>
const int buttom = 2; // Player 1按鈕
const int buttomB = 3; // Player 2按鈕B
#define buzzer A0 //蜂鳴器
#define TFT_CS 4
#define TFT_RST 7
#define TFT_DC 8
#define TFT_MOSI 11
#define TFT_CLK 12
#define TFT_MISO 13
// 避免連接 clock 使用到的針腳
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
int index = 0; // 顯示音符的起始 index
int score = 0; // 玩家 1 分數
int score2 = 0; // 玩家 2 分數
int move = 0; // 位置偏移量
unsigned long prevtime = 0; // 硬體中斷當中用於debouncing 的變數
unsigned long prevtimeB = 0;
int SongSize = sizeof(song) / sizeof(int); // 方便使用的變數, 可略
int centers[sizeof(song) / sizeof(int)] = {}; // 紀錄音符位置的陣列
bool appears[sizeof(song) / sizeof(int)] = {}; // 判斷是否顯示音符的陣列
int colors[sizeof(song) / sizeof(int)] = {}; // 紀錄音符顏色的陣列
void setup()
{
  Serial.begin(9600); // 方便觀察 可略
  pinMode(buttom, INPUT_PULLUP); // Player 1 按鈕
  pinMode(buttomB, INPUT_PULLUP); // Player 1 按鈕B
  attachInterrupt(digitalPinToInterrupt(buttom), flash, FALLING); // 硬體中斷: 按鈕被按下時呼叫 Flash
  attachInterrupt(digitalPinToInterrupt(buttomB), flashB, FALLING); // 硬體中斷: 按鈕被按下時呼叫 Flash
  pinMode(buzzer, OUTPUT); // 設定蜂鳴器
  tft.begin(); // 顯示器設定
  tft.fillScreen(ILI9341_BLACK); // 背景顏色
  tft.setRotation(1); // 螢幕旋轉 橫向擺放
  tft.setTextSize(2.5); // 文字大小
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);;
  tft.println(String("1's Score: ") + score); // 顯示分數初始
  tft.println(String("2's Score: ") + score2);
  randomSeed(analogRead(0)); // 隨機種子, 用於生成音符顏色

  reset(); // 重置
}
void HitPlace() // 打擊點渲染
{
  tft.drawCircle(20, 120, 18, tft.color565(75,75,75)); // 打擊外框
  tft.drawCircle(20, 120, 8, tft.color565(60,60,60));
}
void reset() // 重置
{
  tft.drawCircle(20, 120, 18, tft.color565(75,75,75)); // 打擊外框
  tft.drawCircle(20, 120, 13, tft.color565(120,120,120)); // 打擊內框
  tft.fillCircle(20,120, 12, tft.color565(60,60,60)); // 實心內框
  move = 0; // 偏移量重置
  int temp = 20; // 第一個音符的初始位置
  for(int i = 0; i < sizeof(song) / sizeof(int); i++) // 將三個陣列的內容產生出來 (centers appears colors)
  {
    centers[i] = temp;
    temp += 40; // 每個音符的間距都為 40
    if(song[i] == none) // 沒有要播
    {
      appears[i] = false; // 若 song 當中沒有要播, 則不顯示音符
      colors[i] = -1; // 沒有顏色
    }
    else
    {
      appears[i] = true; // 反之則顯示
      colors[i] = random(0, 2); // 隨機產生顏色
    }
  }
  cli();
  TCCR1A = 0; // reset
  TCCR1B = 0; // reset
  TCCR1B |= B00000100; //將 Prescalar 設定為 256
  TIMSK1 |= B00000010; // 啟動 A 的比對模式
  OCR1A = 18750; // 50000 個週期, 代表 800 ms (Prescalar = 256)
  sei();
}
void loop()
{
}
void UpdateScore(bool player) // 更新分數, 在打中的時候被呼叫, 根據布林值判斷哪一個Player
{
  //tft.fillCircle(20, 120, 15, ILI9341_YELLOW); // 顯示外框
  //tft.fillCircle(20, 120, 10, ILI9341_ORANGE); // 顯示內框
  tft.drawCircle(20, 120, 18, ILI9341_YELLOW); // 方便觀察是否打中
  if(player) // true 表示 player2
    score2++; // 分數增加
  else
    score++;
  tft.setCursor(0,0);
  tft.println(String("1's Score: ") + score);// 顯示更新後的分數
  tft.println(String("2's Score: ") + score2);
}
// const int ylist[] = {123,124,124,124,123,123,124,124,124,123}; // 用於畫音符的陣列
void inline drawBeat(int center, bool color) // 畫音符
{
  //tft.drawCircle(center, 120, 10, tft.color565(150,150,150)); // 半徑為 10 的圓外框
  //tft.drawCircle(center, 120, 9, ILI9341_WHITE); // 半徑為 9 的內層外框
  tft.drawCircle(center, 120, 8, color ? tft.color565(250, 71, 43):tft.color565(108, 191, 194)); // 填滿顏色

  // tft.drawRect(center - 4, 118, 2, 2, ILI9341_BLACK); // 畫眼睛
  // tft.drawRect(center + 2, 118, 2, 2, ILI9341_BLACK); // 畫眼睛

  // for(int i = center - 5, index = 0; i <= center + 5;i++, index++) // 畫嘴巴
  // {
  //   tft.drawPixel(i, ylist[index], ILI9341_BLACK);
  // }
}
void flash() // 按下按鈕時觸發
{
  if(millis() - prevtime > 100 && colors[index] == 0)// 硬體中斷 debouncing
  { // 被按下 且顏色對的上, 分數增加
    prevtime = millis(); // 更新按下時間
    UpdateScore(false);
  }
}
void flashB() // 按下按鈕時觸發
{
  if(millis() - prevtimeB > 100 && colors[index] == 1) // 硬體中斷 debouncing
  { // 同flash A
    prevtimeB = millis(); // 更新按下時間
    UpdateScore(false);
  }
}
ISR(TIMER1_COMPA_vect) // 音符左移 / 控制分數 / 音符產生
{
  HitPlace(); // 打擊點渲染
  char cur; // 讀取第二玩家的輸入
  while(Serial.available() > 0) // Player 2 打擊
  {
    cur = Serial.read(); // 清掉前面多餘的打擊紀錄 獲取最後一個輸入
  }
  if((cur == '1' && colors[index] == 0)|| (cur == '2' && colors[index] == 1))
  { // 顏色對的上按鍵就加分
    UpdateScore(true);
  }
  TCNT1 = 0; // 重置計時器
  OCR1A = tempo[index]; // 播放速度更改
  if(index + 8 > SongSize) // 清除多餘物件
  {
      for(int i = 40 + centers[SongSize-1] + move; i <= tft.width(); i += 40) // 清除多餘的
      {
        tft.fillCircle(i, 120, 10, ILI9341_BLACK);
      }
  }
  for(int i = index; i < min(SongSize, index + 8); i++) // 顯示音符, index 為起始值, 只顯示八個音, 減少執行次數, 非必要
  {
      //Serial.println(String("SongSize: ") + SongSize);
      if(appears[i])
      {
        drawBeat(centers[i] + move,colors[i]);
        // 如果有出現就畫
      }
      else
      { 
        centers[i]+move == 20 ? HitPlace():tft.fillCircle(centers[i] + move, 120, 10, ILI9341_BLACK);
        // 沒有出現就畫黑色, 但黑色不能畫在打擊點上
      }
  }
  tone(buzzer, song[index++]); // 播放音樂 (包含 none)
  move -= 40; // 偏移量更新
  index %= SongSize; // 用於循環播放
  if(index==0) reset(); // 當循環一圈之後重置
}