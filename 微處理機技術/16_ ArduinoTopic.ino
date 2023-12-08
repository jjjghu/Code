#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
int ChooseSize; // 選單大小
int choose; // 當前選擇
int state = 0; // 場景切換變數
int BuildIndex = 0; // 啟動的場景
const int buttom = 2; // 硬體中斷
const int buttomB = 3; // 硬體中斷B
unsigned long long prevtime = 0; // 按鈕更新時間
unsigned long long prevtimeB = 0; // 按鈕B更新時間
int duration = 200; // 硬體中斷的debouncing time 
String Command = "none"; // 指令預設為無
int BridgeSize = 0; // 橋梁長度
int cx = 20; // 位置 x
int cy = 130; // 位置 y
#define TFT_CS 4
#define TFT_RST 7
#define TFT_DC 8
#define TFT_MOSI 11
#define TFT_CLK 12
#define TFT_MISO 13
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); # 顯示加速
void setup()
{
  Serial.begin(9600); // 溝通頻率
  pinMode(buttom, INPUT_PULLUP); // 上拉電阻
  pinMode(buttomB, INPUT_PULLUP); // 上拉電阻
  attachInterrupt(digitalPinToInterrupt(buttom), flash, FALLING); // 硬體中斷觸發
  attachInterrupt(digitalPinToInterrupt(buttomB), flashB, FALLING); // 硬體中斷觸發
  tft.begin(); // 啟動
  tft.setRotation(3); // 角度旋轉
  randomSeed(analogRead(0));
  startUI(); // 啟動UI 
}
void loop() // 沒用的東西
{
}
void flash() // 選擇按鈕的硬體中斷
{
  if(millis() - prevtime > duration) // 硬體中斷
  {
    prevtime = millis();
    choose = (choose+1) % ChooseSize; // 根據當前選單的大小進行切換
    // Serial.println(String("choose: ") + choose);
    UpdateUI(); // 更新顯示 UI
  }
}
void flashB() // 確認按鈕的硬體中斷
{
  if(millis() - prevtimeB > duration) // 距離上次按下的時間超過duration
  {
    prevtimeB = millis();
    if(state) // -1 0 1
    {
      BuildIndex += state; // 跟據 state 切換場景
      state = 0; // 重置
      duration = 5000; // 避免場景轉換未完成誤觸
      startUI(); // 渲染新場景
    }
    else if(BuildIndex == 1) // 場景一 遊戲內容 state = 0
    {
      if(Command == "Build")
      {
        BridgeSize = min(BridgeSize+5, cy); // 蓋橋的最大值
        tft.drawLine(cx+5, cy+5, cx+5, cy+5-BridgeSize, ILI9341_BLACK);
      }
      else if(Command == "GO")
      {
        DrawAnimation(cx, cy); // 橋落下 + 角色 + 地圖的動畫
      }
      else if(Command == "RST") // 重置當前畫面
      {
        startUI();
      }
    }
  }
}
const String list[2] = {"      PLAY     ", "      QUIT     "}; // 場景 1
const String chosenlist[2] = {"     [PLAY]    ", "     [QUIT]    "}; // 場景1

const int Build1x[] = {3, 63, 123, 183}; // 場景 2
const int Build1y[] = {187, 187, 187, 187};// 場景 2
const String text[] = {"GO!", "BLD", "RST", "ESC"}; // 按鈕文字

const int mnSize = 5; // 橋梁最小的長度
int lastspace = cx; // 一開始的產生起點, 角色的腳下一開始一定要有可以踩的地點
bool Map[320] = {false}; // 產生地圖
int MapSize = 320; // 地圖大小
void GenerateMap() // 產生地圖
{
  int begin;
  for(int i = 0; i < cx+5; ++i) // 角色最初站立的位置必定有平台
  {
    Map[i] = true; // 設定為有平台
  }
  for(int i = 0; i < MapSize; ++i) // 從上次紀錄的最後位置(最後一個平台的尾端)開始產生後續地圖
  {
    if(Map[i]) // 如果地圖是可以走的
    {
      begin = i; // 將下一格設定為起點, +1沒有關係
    }
  }
  int leftSpace = MapSize - begin; // 剩下可產生地板的空格
  bool b = false; // 平台和空格交錯排列
  while(leftSpace > mnSize) // 若剩下的位置可以產生地板
  {
    int curSize = 5 * random(1, (min(cy, leftSpace) + 1)/5); // 產生隨機長度的地板
    for(int i = 0; i < curSize; ++i) // 將地板狀態更新
    {
      Map[begin + i] = b; // 更新
    }
    b = !b; // 交錯產生
    leftSpace -= curSize; // 剩下的位置被用掉
    begin += curSize; // 起點更新
  }
  printMap(ILI9341_BLACK, ILI9341_WHITE); // 將地圖顯示出來
}
void printMap(uint16_t color, uint16_t emptycolor)
{ // 可設定顏色
  for(int i = 0; i < MapSize; ++i) // 印出地圖
  {
    if(i && !Map[i-1] && Map[i]) tft.drawLine(i, cy+5, i, 169, color); // 左邊界
    if(i && Map[i-1] && !Map[i]) tft.drawLine(i, cy+5, i, 169, color); // 右邊界
    if(Map[i]) // 若是地板就畫出黑色
    {
      tft.drawPixel(i, cy+5, color);
    }
    else // 空區就畫出白色
    {
      tft.drawPixel(i, cy+5, emptycolor);
    } 
  }
}
void MapAnimation(int &cx, int &cy, uint16_t color, uint16_t emptycolor)
{ // 地圖轉移動畫, 使用三變數的宣告應較好, 還未試過
  for(int i = 0; i < cx - 20; i++) // 目標是將角色移動到 20
  {
    printMap(emptycolor, emptycolor); // 清掉上一步
    DrawCharacter(cx--, cy, emptycolor); // 清掉上一步, 更新角色位置
    for(int j = 0; j < MapSize - i; ++j) // 更新地圖陣列一步
    {
      Map[j] = Map[j+1];
    }
    printMap(color, emptycolor); // 顯示下一步
    DrawCharacter(cx, cy, ILI9341_BLACK); // 顯示下一步
  }
  GenerateMap(); // 動畫結束之後, 產生新地圖
}
void DrawCharacter(int x, int y, uint16_t color) // 使用 utit8_t 承接 ILI9341_color會出現顏色錯誤的問題
{ // 之後看要不要改成 rgb 自選顏色
  tft.fillRect(x,y,5,5,color);
}
void DrawAnimation(int &cx, int &cy) // 橋梁動畫, 為了要讓角色座標在這裡的修改也有用, 使用指標
{
  cx += 5, cy += 5; // 取得角色右下角的位置
  int r = BridgeSize; // 化緣(:D) 的半徑
  if(Map[cx+BridgeSize]) // 地圖當中的那個位置有地方採 => 成功踏上橋
  {
    for(int angle = 270; angle <= 360; angle++) // 使用三角函數更新橋落下的動畫過程
    {
      tft.drawLine(cx, cy, cx+r*cos((angle-1)*DEG_TO_RAD), cy+r*sin((angle-1)*DEG_TO_RAD), ILI9341_WHITE); // 清掉舊的
      tft.drawLine(cx, cy, cx+r*cos(angle*DEG_TO_RAD), cy+r*sin(angle*DEG_TO_RAD), ILI9341_BLACK); // 畫出新的
      delay(50);
    }
    cx-=5, cy-=5; // 變回角色左上角的座標
    DrawCharacter(cx,cy,ILI9341_WHITE); // 原本角色清除
    cx += BridgeSize; // 角色位置更新
    BridgeSize = 0; // 橋梁長度 reset
    DrawCharacter(cx,cy,ILI9341_BLACK); // 畫上新的角色
    MapAnimation(cx,cy,ILI9341_BLACK, ILI9341_WHITE); // 地圖更新動畫, 傳入角色的位置, 顏色
  }
  else // 失敗
  {
    for(int angle = 270; angle <= 450; angle++)
    {
      tft.drawLine(cx, cy, cx+r*cos((angle-1)*DEG_TO_RAD), min(169,cy+r*sin((angle-1)*DEG_TO_RAD)), ILI9341_WHITE); // 清掉舊的
      tft.drawLine(cx, cy, cx+r*cos(angle*DEG_TO_RAD), min(169, cy+r*sin((angle)*DEG_TO_RAD)), ILI9341_BLACK); // 畫出新的, 不可以覆蓋掉下面的按鈕介面, 因此要使用min
      delay(50); // 更新頻率
    }
    cx -= 5, cy -=5;
    BridgeSize = 0; //可略
    // Serial.println("D") // 通知播音樂的Arduino播放死亡音效
    // 記得要死掉喔!
  }
}
void startUI() // 啟動 UI 介面
{
  choose = 0; // 預設選擇為第一個, 不可以放到 UpdateUI 當中, 因為硬體中斷的時候會觸發
  if(BuildIndex == 0)
  { // 場景 0
    ChooseSize = sizeof(list) / sizeof(String); // 更新當前場景的選擇數
    tft.fillScreen(ILI9341_BLACK); // 清空畫面
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK); // 設定該場景的顯示顏色
    tft.setTextSize(3); // 設定文字大小
    UpdateUI(); // 時時更新的介面
  }
  else if(BuildIndex == 1)
  { // 場景 1
    BridgeSize = 0; // 橋的大小預設值
    cx = 20;
    // cy = 130 角色永遠都在預設的高度, 除非落下
    Command = "none"; // 避免出錯, 大概率可略

    ChooseSize = sizeof(Build1x) / sizeof(int); // 更新當前場景的選擇數
    //Serial.println(ChooseSize);
    tft.fillScreen(ILI9341_WHITE); // 清空畫面
    DrawCharacter(cx, cy, ILI9341_BLACK); //角色初始位置
    tft.drawFastHLine(0,170,tft.width(),ILI9341_BLACK); // 下邊界
    for(int i =0; i < MapSize; ++i) Map[i] = false; // 重新設定地圖
    GenerateMap(); // 產生地圖
    UpdateUI(); // 時時更新的UI 
  }
}
void UpdateUI() // 更新 UI
{
  duration = 200; // 設定回預設值
  if(BuildIndex == 0)
  { // 場景 0
    state = 0; // 切換場景訂為 0
    tft.setCursor(0,100); // 屬標位置
    for(int i = 0; i < ChooseSize; i++)
    {
      if(i == choose) // 如果是被選重的選項
      {
        tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK); // 文字顏色
        tft.println(chosenlist[i]);
        if(i == 0) state = 1; // 切換場景的準備工作
      }
      else // 沒有被選中的選項
      {
        tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK); // 文字顏色設定
        tft.println(list[i]); // 印出選項
      }
    }
  }
  else if(BuildIndex == 1) 
  { // 場景 1
    state = 0;
    tft.setTextSize(2);
    for(int i = 0; i < ChooseSize; i++)
    {
      if(i == choose) // 目前選項
      {
        for(int j = 0; j < 3; j++) // 渲染按鈕
        {
          tft.drawRoundRect(Build1x[i]+j,Build1y[i]+j,50-j,50-j,3,ILI9341_BLUE); // 按鈕外框, 顏色藍
          tft.setCursor(Build1x[i]+10, Build1y[i]+20); // 指標位置 
          tft.setTextColor(ILI9341_BLUE); // 文字顏色
          tft.print(text[i]); // 顯示內容
        }

        state = 0; // 場景轉換預設為 0 
        switch(i)
        {
          case 0: Command = "GO";break;// 選擇 GO
          case 1: Command = "Build";break; // 選擇BLD
          case 2: Command = "RST";break;
          case 3: state = -1; break; // 選擇 ESC
          default: Command = "none"; // 例外處理,大概率用不到
        }
      }
      else // 不是目前選項
      {
        for(int j = 0; j < 3; j++) // 渲染按鈕
        {
          tft.drawRoundRect(Build1x[i]+j,Build1y[i]+j,50-j,50-j,3,ILI9341_BLACK); // 按鈕外框
          tft.setCursor(Build1x[i]+10, Build1y[i]+20); // 指標位置
          tft.setTextColor(ILI9341_BLACK); // 文字顏色
          tft.print(text[i]); // 印出內容
        }
      }
    }
  }
  //Serial.println(String("State: ") + state); // 顯示狀態
}
/*
代辦事項
角色設計動畫: 不關我的事, 我不需要做這個, 對吧? ...對吧!
死亡及背景音效: 會使用Serial發出訊號通知另一台Arduino要做的事情

地圖產生
角色每走一步, 地圖就要更新一遍, 並且產生新的平台 (不只有一個), (2023/12/8 已完成), 地圖動畫還有一些小瑕疵
新的平台要有一個最小的數值, 如果空閒區域沒有最小值那樣長, 停止產生

角色的更新: 角色如果從頭到尾都訂在一個位置可以減少動畫移動角色花費的效能
*/