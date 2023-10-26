#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
volatile byte stateA = HIGH; // 避免最佳化
volatile byte stateB = HIGH; // 因為 PULLUP, 預設為HIGH, LOW 表示被按壓
unsigned long prevtimeA; // 按鈕上次的更新時間
unsigned long prevtimeB; // 使用unsigned long 確保不會 overflow
bool HITA = false; // 判斷是否有出現音符
bool HITB = false;
int gradeA = 0; // 藍紅分數計算
int gradeB = 0;
const byte buttomA = 2; // 利用硬體中斷, 因此必須使用 2 和 3 腳位
const byte buttomB = 3;
#define TFT_CS 8
#define TFT_RST 9
#define TFT_DC 10
#define TFT_MOSI 11
#define TFT_CLK 12
#define TFT_MISO 13
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO); // LCD 設定
void setup()
{
  // Serial.begin(9600); // 方便觀察 可略
  tft.begin(); // 開啟LCD
  tft.fillScreen(ILI9341_BLACK); // 背景更改為黑
  tft.setTextSize(2.5); // 字體大小設定
  showGrade(); // 顯示初始分數  
  tft.fillCircle(60, 240, 30, ILI9341_PINK); // 紅音符,預設為粉色, 表示未出現
  tft.fillCircle(180, 240, 30, ILI9341_PINK); // 藍音符  
  pinMode(buttomA, INPUT_PULLUP); // 按鈕設定為 PULLUP
  pinMode(buttomB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttomA), flashA, FALLING); // 當buttom狀態從HIGH到LOW, 觸發flash, 也可用 CHANGE
  attachInterrupt(digitalPinToInterrupt(buttomB), flashB, FALLING);
  prevtimeA = millis(); // 紀錄上次按鈕更新時間
  prevtimeB = millis();
  random(analogRead(0)); // 隨機種子, 用於產生音符
}
void loop()
{
  int choose = random(0, 2); // 0 1 隨機
  if(choose)
  {
    tft.fillCircle(60, 240, 30, ILI9341_RED); // 將左邊顯示紅色
    tft.fillCircle(180, 240, 30, ILI9341_PINK); // 將右邊顯示粉色
    HITA = true; // 左邊打了加分
    HITB = false;
  }
  else
  {
    tft.fillCircle(60, 240, 30, ILI9341_PINK);// 將左邊顯示粉色
    tft.fillCircle(180, 240, 30, ILI9341_BLUE);// 將右邊顯示藍色
    HITA = false;
    HITB = true; // 右邊打了加分
  }
  // Serial.println(String("HITA: ") + HITA + String(" HITB") + HITB); // 方便觀察 可略
  // Serial.println(String("StateA: ") + stateA + String(" StateB") + stateB);
  stateA = HIGH; // 將按鈕狀態回復成未敲擊, 如果為 CHANGE 可略
  stateB = HIGH;
  HITMOMENT(); // 打擊時間  
}
void HITMOMENT()
{
  unsigned long start = millis(); // arduino 當中的 int 只到 32727 ms, 避免overflow使用 unsigned long
  while(millis() - start < 500) // 打擊的緩衝時間為500ms
  {
    if(HITA && stateA == LOW) // 如果打了可以加分並且有敲擊
    {
      gradeA++; // 紅色分數+1
      tft.fillCircle(60, 240, 30, ILI9341_PINK); // 打了之後回復原狀, 才有 "被打到 "的感覺
      HITA = false;
      showGrade(); // 顯示更新後的分數
    }
    else if(HITB && stateB == LOW)
    {
      gradeB++;// 藍色分數+1
      tft.fillCircle(180, 240, 30, ILI9341_PINK);
      HITB = false;
      showGrade();
    }
    if(!HITA && !HITB) break; // 如果都打過了, break, 前往下一輪
  }
}
void showGrade() // 顯示分數
{
  tft.fillRect(0, 0, 180, 50, ILI9341_BLACK); // 將原本的分數覆蓋掉, 避免分數疊在一起
  tft.setCursor(0,0); // 座標設定左上角
  tft.setTextColor(ILI9341_RED); // 紅色分數
  tft.println(String(" Red: ") + gradeA);
  tft.setTextColor(ILI9341_BLUE); // 藍色分數
  tft.println(String("Blue: ") + gradeB);
}
void flashA()
{
  if(millis() - prevtimeA > 50) // 彈跳時會觸發數次, 利用 millis 防彈跳
  {
    stateA = LOW; // FALLING 時觸發, 故設定為 LOW, 如果是 CHANGE, 設定為 digitalRead(buttomA) 或是!stateA
    prevtimeA = millis(); // 更新「更新時間」
  }
}
void flashB() // 同flashA
{
  if(millis() - prevtimeB > 50)
  {
    stateB = LOW;
    prevtimeB = millis();
  }
}