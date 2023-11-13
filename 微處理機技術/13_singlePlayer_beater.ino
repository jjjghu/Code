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
#define none 0
// 定義頻率, 方便寫音樂
int song[] = {none, none, none,
              C4, B4, G4, B4, C4, B4, G4, B4, C4, B4, G4, B4, C4, B4, G4, B4,
              C3, B3, G3, B3, C3, B3, G3, B3, B4, C5, D5, E5, E5, D5, B4, C5, B4, G4, B4,
              B4, E5, D5, E5, E5, G5, G5, E5, E5, D5, none,
              B4, F5, E5, E5, C5, C5, A4, C5, B4, G4, G4, E5, D5,
              F5, E5, E5, C5, C5, A4, A5, G5, E5, D5, B4,
              G4, none, G5, E5, G5, none, G5, E5, G5, none, G5, E5, G5};
              //歌曲內容
#include<Adafruit_GFX.h>
#include<Adafruit_ILI9341.h>
const int buttom =  2;
const int buttomB = 3; // 硬體中斷必須要接在 2 3 其一
#define buzzer A0
#define TFT_CS 4
#define TFT_RST 7
#define TFT_DC 8
#define TFT_MOSI 11
#define TFT_CLK 12
#define TFT_MISO 13
// 避免連接 clock 使用到的針腳
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
int index = 0; // 顯示音符的起始 index
int beat = 0; // 播放音樂使用的變數
int score = 0; //分數
unsigned long prevtime = 0; // 硬體中斷當中用於debouncing 的變數
unsigned long prevtimeB = 0;
volatile int rightPlace = 0; // 檢查音符是否在打擊點的變數
int centers[sizeof(song) / sizeof(int)] = {}; // 紀錄音符位置的陣列
bool appears[sizeof(song) / sizeof(int)] = {}; // 判斷是否顯示音符的陣列
bool colors[sizeof(song) / sizeof(int)] = {}; // 紀錄音符顏色的陣列
void setup()
{
  Serial.begin(9600); // 方便觀察 可略
  pinMode(buzzer, OUTPUT); // 設定蜂鳴器
  pinMode(buttom, INPUT_PULLUP); // 設定按鍵
  attachInterrupt(digitalPinToInterrupt(buttom), flash, FALLING); // 硬體中斷: 按鈕被按下時呼叫 Flash
  attachInterrupt(digitalPinToInterrupt(buttomB), flashB, FALLING); // 硬體中斷: 按鈕被按下時呼叫 Flash
  tft.begin(); // 顯示器設定
  tft.fillScreen(ILI9341_BLACK); // 背景顏色
  tft.setRotation(1); // 螢幕旋轉 橫向擺放
  tft.setTextSize(2.5); // 文字大小
  tft.print(String("Score: ") + score); // 顯示分數初始
  randomSeed(analogRead(0)); // 隨機種子, 用於生成音符顏色

  reset(); // 重置
  cli();
  TCCR1A = 0; // reset 關閉P
  TCCR1B = 0; // reset
  TCCR1B |= B00000100; //將 Prescalar 設定為 256
  TIMSK1 |= B00000010; // 啟動 A 的比對模式
  OCR1A = 50000; // 50000 個週期, 代表 800 ms (Prescalar = 256)
  sei();
}
void HitPlace() // 打擊點渲染
{
  tft.drawCircle(20, 120, 18, tft.color565(75,75,75)); // 打擊外框
  tft.drawCircle(20, 120, 13, tft.color565(120,120,120)); // 打擊內框
  tft.fillCircle(20,120, 12, tft.color565(60,60,60)); // 實心內框
}
void reset() // 重置
{
  HitPlace(); // 打擊點渲染
  index = 0; // 初始顯示位置為index
  int temp = 20; // 第一個音符的初始位置
  for(int i = 0; i < sizeof(song) / sizeof(int); i++) // 將三個陣列的內容產生出來 (centers appears colors)
  {
    centers[i] = temp; 
    temp += 40; // 每個音符的間距都為 40
    if(song[i] == none) appears[i] = false; // 若 song 當中沒有要播, 則不顯示音符
    else appears[i] = true; // 反之則顯示
    colors[i] = random(0, 2); // 隨機產生顏色
  }
}
void loop()
{
}
void UpdateScore() // 更新分數, 在打中的時候被呼叫
{
  tft.fillCircle(20, 120, 15, ILI9341_YELLOW); // 顯示外框
  tft.fillCircle(20, 120, 10, ILI9341_ORANGE); // 顯示內框
  score++; // 分數增加
  tft.fillRect(0,0, 150, 20, ILI9341_BLACK); // 清除原本分數
  tft.setCursor(0,0); 
  tft.print(String("Score: ") + score);// 顯示更新後的分數
}
int ylist[] = {123,124,124,124,123,123,124,124,124,123}; // 用於畫音符的陣列
void drawBeat(int center, bool color) // 畫音符
{
  tft.drawCircle(center, 120, 10, tft.color565(150,150,150)); // 半徑為 10 的圓外框
  tft.drawCircle(center, 120, 9, ILI9341_WHITE); // 半徑為 9 的內層外框
  tft.fillCircle(center, 120, 8, color ? tft.color565(250, 71, 43):tft.color565(108, 191, 194)); // 填滿顏色

  tft.drawRect(center - 4, 118, 2, 2, ILI9341_BLACK); // 畫眼睛
  tft.drawRect(center + 2, 118, 2, 2, ILI9341_BLACK); // 畫眼睛

  for(int i = center - 5, index = 0; i <= center + 5;i++, index++) // 畫嘴巴
  {
    tft.drawPixel(i, ylist[index], ILI9341_BLACK);
  }
}
int pressed = 0; // 判斷是否有按下按鈕的變數
void flash() // 按下按鈕時觸發
{
  if(millis() - prevtime > 50) // 硬體中斷 debouncing
  {
    //Serial.println(String("PRESSED") + ttime); //判斷 可略
    prevtime = millis(); // 更新按下時間, 故不可使用 if(rightPlace && millis() - prevtime > 50)
    if(rightPlace == 1) // 可以打且有打 => 播放音樂
    {
      rightPlace = 0; // 重置變數
      pressed = 1; // 更新變數
    }
  }
}
void flashB() // 按下按鈕時觸發
{
  if(millis() - prevtimeB > 50) // 硬體中斷 debouncing
  {
    //Serial.println(String("PRESSED") + ttime); //判斷 可略
    prevtimeB = millis(); // 更新按下時間, 故不可使用 if(rightPlace && millis() - prevtime > 50)
    if(rightPlace == 2) // 可以打且有打 => 播放音樂
    {
      rightPlace = 0; // 重置變數
      pressed = 2; // 更新變數
    }
  }
}
ISR(TIMER1_COMPA_vect) // 音符左移 / 控制分數 / 音符產生
{
  if(pressed) // 如果有按下按鈕 (由於flash, 故必然在正確位置上)
  {
    UpdateScore(); //更新分數 
  }
  TCNT1 = 0; // 重置計時器
  rightPlace = 0; // 重置變數
  pressed = 0; // 重置變數
  HitPlace();
  for(int i = 60; i <= tft.width(); i += 40) // 清除舊有畫面
  {
    tft.fillCircle(i, 120, 10, ILI9341_BLACK);
  }
  for(int i = index; i < sizeof(song) / sizeof(int); i++) // 顯示音符, index 為起始值, 減少執行次數, 非必要
  {
    if(centers[i] != 0 && centers[i] <= tft.width()) // 在範圍內就"可以"顯示音符
    {
      if(appears[i]) // 非 none(用於停頓) 就要畫出來
      {
        drawBeat(centers[i], colors[i]);
      }
      if(centers[i] == 20) // 若出現在打擊點上
      {
        tone(buzzer, song[beat++], 125); // 播放音樂 (包含 none)
        if(appears[i]) // 若播放的內容不是 none(停頓)
        {
          rightPlace = colors[i] ? 1:2;
          // rightPlace = true; // 表示在正確的位置上, 可以打擊
        }
      }
    }
    if(centers[i] > 20) // 打擊點以後內容都向左移動一個單位 (40 pixel)
    {
      centers[i] -= 40;
    }
    else centers[i] = 0; // 打擊點以前的centers[]設定為 0
  }
  index++; // 每一步後起始值必定 + 1, "一定一定"要放在下行的前面, 避免循環時出錯
  beat %= sizeof(song) / sizeof(int); // 用於循環播放
  if(beat == 0) reset(); // 當循環一圈之後重置
}