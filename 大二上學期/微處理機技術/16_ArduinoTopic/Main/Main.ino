#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
int ChooseSize; // 選單大小
int choose; // 當前選擇
int state = 0; // 場景切換變數
int PressedTime = 0; // 按下的次數 / 用於選擇顏色
int BuildIndex = 0; // 初始啟動的場景
const int buttom = 2; // 硬體中斷
const int buttomB = 3; // 硬體中斷B
unsigned long long prevtime = 0; // 按鈕更新時間
unsigned long long prevtimeB = 0; // 按鈕B更新時間
int duration = 200; // 硬體中斷的debouncing time 
String Command = "none"; // 指令預設為無
int BridgeSize = 0; // 橋梁長度
int cx = 20; // 位置 x
int cy = 130; // 位置 y
#define buzzer 5
#define TFT_CS -1
#define TFT_RST 8
#define TFT_DC 9 
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_MISO 13
int widthCell; // 定位座標
int heightCell; // 定位座標, 用於畫場景
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); //顯示加速
const String list[2] = {"       PLAY     ", "       QUIT     "}; // 場景 0

int Build1x[5] = {0}; // 場景 2
int Build1y[5] = {0};// 場景 2
const uint16_t BACKGROUND[] = {ILI9341_WHITE, 0x07ff, 0xf60f, 0xffef, 0x87f0}; // 顏色選單
const uint16_t colors[] = {ILI9341_BLACK, 0xc165, 0x5c67, 0x23b9, 0x8336}; // 顏色選單
uint16_t backgroundColor = ILI9341_WHITE; // 玩家選擇的顏色
uint16_t characterColor = ILI9341_BLACK;
const uint16_t renderColor = 0x21ee; // 渲染場景時的背景顏色

const int Build2x[] = {3, 63, 123, 183}; // 場景 2
const int Build2y[] = {187, 187, 187, 187};// 場景 2
const String text[] = {"BLD", "GO!", "RST", "ESC"}; // 按鈕文字

int score = 0; //分數
const int mnSize = 15; // 橋梁最小的長度
int lastspace = cx; // 一開始的產生起點, 角色的腳下一開始一定要有可以踩的地點
bool Map[320] = {false}; // 產生地圖
int MapSize = 320; // 地圖大小

void setup()
{
  // 設定溝通pin腳
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  Serial.begin(9600); // 溝通頻率
  pinMode(buttom, INPUT_PULLUP); // 上拉電阻
  pinMode(buttomB, INPUT_PULLUP); // 上拉電阻
  attachInterrupt(digitalPinToInterrupt(buttom), flash, FALLING); // 硬體中斷觸發
  attachInterrupt(digitalPinToInterrupt(buttomB), flashB, FALLING); // 硬體中斷觸發
  tft.begin(); // 啟動
  tft.setRotation(3); // 角度旋轉
  randomSeed(analogRead(0));
  widthCell = tft.width() / 10;
  heightCell = tft.height() / 10;
  int r = heightCell * 3;
  for(int i = 270, count = 0; i < 270+360; i+=360/5, ++count)
  {
    Build1x[count] = widthCell*5+r*cos(i*DEG_TO_RAD) + 5;
    Build1y[count] = heightCell*5+r*sin(i*DEG_TO_RAD) + 5;
  }
  startUI(); // 啟動UI 
}
void loop() // 沒用的東西
{
}
void flash() // 選擇按鈕的硬體中斷
{
  if(millis() - prevtime > duration) // 硬體中斷
  {
    tone(buzzer, 442, 100);
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
    tone(buzzer, 587, 100);
    prevtimeB = millis();
    if(state) // -1 0 1
    {
      BuildIndex += state; // 跟據 state 切換場景
      state = 0; // 重置
      duration = 5000; // 避免場景轉換未完成誤觸
      // TODO: send msg.
      startUI(); // 渲染新場景
    }
    else if(BuildIndex == 1) // 場景1 顏色選擇
    { // 場景1
      PressedTime += 1;
      for(int j = 0; j < 3; j++)
      {
        tft.drawRoundRect(Build1x[choose]-(20-j),Build1y[choose]-(21-j), 26-j, 26-j, 3, colors[choose]);
      }
      if(PressedTime == 2) // 按下兩次表示確認
      {
        BuildIndex += 1; // 更新BuildIndex
        backgroundColor = BACKGROUND[choose];
        characterColor = colors[choose];
        startUI(); // 啟動下一個頁面
      }
    }
    else if(BuildIndex == 2) // 場景二 遊戲內容 state = 0
    {
      if(Command == "Build")
      {
        BridgeSize = min(BridgeSize+5, cy); // 蓋橋的最大值
        tft.drawLine(cx+5, cy+5, cx+5, cy+5-BridgeSize, characterColor);
      }
      else if(Command == "GO")
      {
        DrawAnimation(cx, cy); // 橋落下 + 角色 + 地圖的動畫
        choose = 0; // 選擇改回BUILD
        UpdateUI(); // 更新選單顯示
      }
      else if(Command == "RST") // 重置當前畫面
      {
        startUI();
      }
    }
  }
}
void GenerateMap() // 產生地圖
{
  int begin;
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
    int curSize = 5 * random(3, (min(cy, leftSpace) + 1)/5); // 產生隨機長度的地板
    for(int i = 1; i <= curSize; ++i) // 將地板狀態更新
    {
      Map[begin + i] = b; // 更新
    }
    b = !b; // 交錯產生
    leftSpace -= curSize; // 剩下的位置被用掉
    begin += curSize; // 起點更新
  }
  printMap(characterColor, backgroundColor); // 將地圖顯示出來
}
void WalkAnimation(int &cx, int &cy, int &BridgeSize) // 變數都是全域
{
  while(BridgeSize > 0)
  {
    DrawCharacter(cx++, cy, backgroundColor); // 清掉上一步
    DrawCharacter(cx, cy, characterColor); // 畫出下一步
    showScore(ILI9341_RED, backgroundColor);
    delay(50);
    BridgeSize--;
  }    
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
  //cx += 11;
  for(int i=1;cx > 20;i++) // 目標是將角色移動到 20
  {
    printMap(emptycolor, emptycolor); // 清掉上一步
    DrawCharacter(cx--, cy, emptycolor); // 清掉上一步, 更新角色位置
    for(int j = 0; j < MapSize - i ; ++j) // 更新地圖陣列一步
    {
      Map[j] = Map[j+1];
    }
    if(i==1)
    {//避免尾端的true延續
      Map[319] = false;
      i--;
    }
    printMap(color, emptycolor); // 顯示下一步
    DrawCharacter(cx, cy, characterColor); // 顯示下一步
  }
  for(int i=1;Map[25];i++) // 目標是將角色移動到邊緣(角色不動)
  {
    printMap(emptycolor, emptycolor); // 清掉上一步
    for(int j = 0; j < MapSize - i ; ++j) // 更新地圖陣列一步
    {
      Map[j] = Map[j+1];
    }
    printMap(color, emptycolor); // 顯示下一步
  }
  GenerateMap(); // 動畫結束之後, 產生新地圖
}
void DrawBackGround()
{
  tft.fillScreen(0x39a7);
  tft.fillRoundRect(widthCell, heightCell, widthCell*8, heightCell*8, 5, 0x4f39);
  for(int i = 0; i < 3; i++)
  {
    tft.drawRoundRect(widthCell-i, heightCell-i, widthCell*8+2*i, heightCell*8+2*i, 5, 0xd4eb);
  }
}
bool flag = false;
void DrawCharacter(int x, int y, uint16_t color) // 使用 utit8_t 承接 ILI9341_color會出現顏色錯誤的問題
{ // 之後看要不要改成 rgb 自選顏色
   x=x-11;
   tft.fillRect(x,y-5,6,5,color);
   tft.fillRect(x-2,y-5,2,4,color);
   tft.fillRect(x-4,y-6,2,4,color);
   tft.fillRect(x-5,y-10,1,6,color);
   tft.fillRect(x+1,y-7,3,2,color);
   tft.fillRect(x+4,y-9,2,4,color);
   tft.fillRect(x+6,y-4,2,2,color);
   tft.fillRect(x+6,y-10,3,6,color);
   tft.fillRect(x+5,y-17,10,7,color);
   tft.fillRect(x+9,y-7,3,1,color);
   tft.fillRect(x+12,y-6,1,1,color);
   flag?tft.fillRect(x+7,y-15,2,1,ILI9341_WHITE):tft.fillRect(x+7,y-15,1,1,ILI9341_WHITE); // 眼睛永白, 閉眼? 
   tft.fillRect(x,y,1,4,color);
   tft.fillRect(x+5,y,1,4,color);
   //x-=5;
   //y-=5;
  //tft.fillRect(x,y,10, 10, color);
}
void DrawAnimation(int &cx, int &cy) // 橋梁動畫, 為了要讓角色座標在這裡的修改也有用, 使用指標
{
  cx += 5, cy += 5; // 取得角色右下角的位置
  int r = BridgeSize; // 化緣(:D) 的半徑
  for(int angle = 270; angle <= 360; angle++) // 使用三角函數更新橋落下的動畫過程
  {
    tft.drawLine(cx, cy, cx+r*cos((angle-1)*DEG_TO_RAD), cy+r*sin((angle-1)*DEG_TO_RAD), backgroundColor); // 清掉舊的
    tft.drawLine(cx, cy, cx+r*cos(angle*DEG_TO_RAD), cy+r*sin(angle*DEG_TO_RAD), characterColor); // 畫出新的
  }
  if(Map[cx+BridgeSize]||Map[cx+BridgeSize-1]) // 地圖當中的那個位置有地方採 => 成功踏上橋
  {
    cx-=5, cy-=5; // 變回角色左上角的座標  
    if(!Map[cx+BridgeSize+4]) BridgeSize += 11; //避免角色看起來懸空
    if(!Map[cx+BridgeSize-1]) BridgeSize += 6;
    showScore(ILI9341_RED, backgroundColor);
    WalkAnimation(cx, cy, BridgeSize); // 走動動畫
    MapAnimation(cx,cy,characterColor, backgroundColor); // 地圖更新動畫, 傳入角色的位置, 顏色
  }
  else // 失敗
  {
    deathAnimation();    
    delay(100000);
    startUI();
  }
}
void showScore(uint16_t color, uint16_t emptycolor)
{  //顯示分數
    if(BridgeSize==0) score--;
    score++;
    tft.setCursor(190,10);
    tft.setTextColor(color, emptycolor);
    tft.print(score);
}
void deathAnimation()
{ //死亡動畫
    flag = true;// 眼睛改變
    DrawCharacter(cx+BridgeSize,cy+29,characterColor); // 畫上新的角色
    flag = false;
    cx -= 5, cy -=5;
    DrawCharacter(cx,cy,backgroundColor); // 原本角色清除
    tft.setCursor(100,50);
    tft.setTextColor(ILI9341_RED);
    tft.setTextSize(2);
    tft.println(F("You failed."));
    
    // 傳送播放死亡音樂之訊號
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    // 等待死亡音樂播放,此參數經精心校調
    delay(6*90000);
}
void startUI() // 啟動 UI 介面
{
  PressedTime = 0; // 重置按下狀態
  choose = 0; // 預設選擇為第一個, 不可以放到 UpdateUI 當中, 因為硬體中斷的時候會觸發
  if(BuildIndex == 0)
  { // 場景 0
    // 送播放開始畫面音樂的訊號
    // Serial.write(SONG_0, 2);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    ChooseSize = sizeof(list) / sizeof(String); // 更新當前場景的選擇數
    DrawBackGround(); // 顯示畫面
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK); // 設定該場景的顯示顏色
    tft.setTextSize(3); // 設定文字大小
    UpdateUI(); // 時時更新的介面
  }
  else if(BuildIndex == 1) // 場景1 顏色選擇
  {
    // 送播音樂的訊號
    // Serial.write(SONG_0, 2);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    ChooseSize = sizeof(colors) / sizeof(uint16_t); // 更新選單大小
    // tft.fillScreen(renderColor); // 螢幕背景畫面
    tft.fillRoundRect(widthCell, heightCell, widthCell*8, heightCell*8, 5, 0x07fa);
    for(int r = -1; r <= 1; ++r)
    {
      tft.drawCircle(widthCell*5, heightCell*5, heightCell*3 + r, 0xee18);
    }
    for(int i = 0; i < ChooseSize; ++i) // 顯示角色
    {
      DrawCharacter(Build1x[i], Build1y[i], colors[i]);
    }
    UpdateUI();
  }
  else if(BuildIndex == 2)
  { // 場景 2
    // 送播音樂的訊號
    // Serial.write(SONG_1, 2);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    BridgeSize = 0; // 橋的大小預設值
    cx = 20;
    // cy = 130 角色永遠都在預設的高度, 除非落下
    Command = "none"; // 避免出錯, 大概率可略
    score = 0;

    ChooseSize = sizeof(Build2x) / sizeof(int); // 更新當前場景的選擇數
    //Serial.println(ChooseSize);
    tft.fillScreen(backgroundColor); // 清空畫面
    DrawCharacter(cx, cy, characterColor); //角色初始位置
    tft.drawFastHLine(0,170,tft.width(),characterColor); // 下邊界
    for(int i =0; i < MapSize; ++i) Map[i] = false; // 重新設定地圖
    for(int i = 0; i < cx+5; ++i) // 角色最初站立的位置必定有平台
        Map[i] = true; // 設定為有平台
    GenerateMap(); // 產生地圖
    tft.setCursor(120,10);
    tft.setTextColor(ILI9341_RED, backgroundColor);
    tft.setTextSize(2);
    tft.print(F("Score:"));
    showScore(ILI9341_RED, backgroundColor);
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
      if(i == choose) // 如果是被選中的選項
      {
        tft.setTextColor(ILI9341_YELLOW); // 文字顏色
        tft.println(list[i]);
        if(i == 0) state = 1; // 切換場景的準備工作
      }
      else // 沒有被選中的選項
      {
        tft.setTextColor(ILI9341_WHITE); // 文字顏色設定
        tft.println(list[i]); // 印出選項
      }
    }
  }
  else if(BuildIndex == 1) // 場景 2 顏色選擇
  {
    PressedTime = 0; // 更換選擇角色才會進入, 因此要歸零
    state = 0;
    for(int i = 0; i < ChooseSize; ++i)
    {
      if(i == choose)
      {
        tft.fillRoundRect(Build1x[i]-18,Build1y[i]-19, 23, 23, 3, ILI9341_WHITE);
        DrawCharacter(Build1x[i], Build1y[i], colors[i]);
      }
      else
      {
        tft.fillRoundRect(Build1x[i]-18,Build1y[i]-19, 23, 23, 3, renderColor);
        DrawCharacter(Build1x[i], Build1y[i], colors[i]);
        for(int j = 0; j < 3; j++)
        {
          tft.drawRoundRect(Build1x[i]-(20-j),Build1y[i]-(21-j), 26-j, 26-j, 3, renderColor);
        }
      }
    }
  }
  else if(BuildIndex == 2) 
  { // 場景 2
    state = 0;
    tft.setTextSize(2);
    for(int i = 0; i < ChooseSize; i++)
    {
      if(i == choose) // 目前選項
      {
        for(int j = 0; j < 3; j++) // 渲染按鈕
        {
          tft.drawRoundRect(Build2x[i]+j,Build2y[i]+j,50-j,50-j,3,ILI9341_BLUE); // 按鈕外框, 顏色藍
          tft.setCursor(Build2x[i]+10, Build2y[i]+20); // 指標位置 
          tft.setTextColor(ILI9341_BLUE); // 文字顏色
          tft.print(text[i]); // 顯示內容
        }

        state = 0; // 場景轉換預設為 0 
        switch(i)
        {
          case 0: Command = "Build";break;// 選擇 GO
          case 1: Command = "GO";;break; // 選擇BLD
          case 2: Command = "RST";break; // RESET
          case 3: state = -2; break; // 選擇 ESC
          default: Command = "none"; // 例外處理,大概率用不到
        }
      }
      else // 不是目前選項
      {
        for(int j = 0; j < 3; j++) // 渲染按鈕
        {
          tft.drawRoundRect(Build2x[i]+j,Build2y[i]+j,50-j,50-j,3,ILI9341_BLACK); // 按鈕外框
          tft.setCursor(Build2x[i]+10, Build2y[i]+20); // 指標位置
          tft.setTextColor(ILI9341_BLACK); // 文字顏色
          tft.print(text[i]); // 印出內容
        }
      }
    }
  }
  //Serial.println(String("State: ") + state); // 顯示狀態
}
