const int strobe = 8;
const int clock = 9;
const int data = 10;
int grade = 0;
byte list[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f}; // 顯示數字的陣列
byte Monster[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // completely unecessary
byte readByte() // 讀取資料
{
  byte value = 0x00; // 預設為 0x00
  pinMode(data, INPUT); // 將七段改為輸入
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(clock, LOW);
    if(digitalRead(data)) // 讀到 1 就用 or 更新
    {
      value |= (0x01 << i);
    }
    digitalWrite(clock, HIGH);
  }
  pinMode(data, OUTPUT); // 將七段改回輸出
  return value; //回傳輸入
}
void sendByte(byte value) // 傳送指令
{
  for(byte i = 0; i < 8; i++)
  {
    digitalWrite(clock, LOW);
    digitalWrite(data, (value & 1 ? HIGH : LOW)); //如果是 true 就 HIGH, 反則 LOW
    value = value >> 1;
    digitalWrite(clock, HIGH);
  }
}
void sendCommand(byte cmd) // 傳送一項指令, 用於簡短程式碼
{
  digitalWrite(strobe, LOW);
  sendByte(cmd);
  digitalWrite(strobe, HIGH);
}
void reset()
{
  sendCommand(0x40); // 自動增加的地址
  digitalWrite(strobe, LOW); // 關閉閘門才可傳送指令
  sendByte(0xc0); // 設定初始地址
  for(byte i = 0; i <= 16; i++) //給定預設值, 全部設為關閉
  {
    sendByte(0x00);
  }
  digitalWrite(strobe, HIGH);
  grade = 0; // 分數重設
  delay(2000); // 遊戲重置之後等待 2 秒, 方便觀察
}
void setup()
{
  Serial.begin(9600);
  pinMode(strobe, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  digitalWrite(strobe, HIGH);
  digitalWrite(clock, HIGH);

  sendCommand(0x88); // 設定顯示開關
  sendCommand(0x8f); // 設定亮度最亮
  sendCommand(0x40); // 設定初始位置

  reset();

  randomSeed(analogRead(0)); //隨機種子
}
byte readbutton() // 讀取按鈕
{
  byte value = 0x00;
  digitalWrite(strobe, LOW);
  sendByte(0x42); // 從鍵盤輸入
  for(byte i = 0; i < 4; i++)
  {
    byte read = readByte();
    value |= (read << i);
  }
  digitalWrite(strobe, HIGH);
  return value;
}
void setLed(byte value, byte position) // 設定 LED 狀態
{
  pinMode(data, OUTPUT); // 將七段設定為輸出
  sendCommand(0x44); // 固定地址

  digitalWrite(strobe, LOW);
  sendByte(0xc1 + (position << 1)); // 找出地址
  sendByte(value); // 設定為亮或暗
  digitalWrite(strobe, HIGH);
}
void setGrade(int grade)
{
  grade = grade % 100; // 避免超過 100 出錯
  sendCommand(0x44); // 固定位置
  int cur = grade / 10; // 十位數
  grade %= 10; // 個位數

  digitalWrite(strobe, LOW);
  sendByte(0xcc); // 在第七個顯示器 顯示十位數
  sendByte(list[cur]);
  digitalWrite(strobe, HIGH);

  digitalWrite(strobe, LOW);
  sendByte(0xce);// 在第八個顯示器 顯示個位數
  sendByte(list[grade]);
  digitalWrite(strobe, HIGH);
}
void UpdateLED() //更新 LED
{
   byte buttonState = readbutton(); // 讀取按鈕
   for(int i = 0; i < 8; i++)
   {
      byte mask = 0x01 << i;
      if(i == 7 && buttonState & mask) // 最右邊按鈕重置
      {
        reset();
      }
      else
      {
        setLed((buttonState & mask ? 1:0), i); // 如果是被按下的 => 亮
        if(Monster[i] == 0x40) //有怪 然後有按下按鈕
        {
          if(buttonState & mask)//有怪且按下按鈕
            grade++; // 分數增加

          sendCommand(0x44); //固定地址
          digitalWrite(strobe, LOW);
          sendByte(0xc0 + (i << 1)); // 將被打的顯示器關閉
          sendByte(0x00);
          Monster[i] = 0x00; // 更新怪物陣列
          digitalWrite(strobe, HIGH);
        }
        setGrade(grade); // 顯示分數
      }
   }
  // Serial.println(String("button: ") + buttonState);
}
void MonsterFarm() // 生怪場
{
    byte i = random(0,6); //出現怪物的位置
    Monster[i] = 0x40; //設定顯示, 一定要用陣列, 否則場上會有一堆怪

    sendCommand(0x44); // 固定地址
    digitalWrite(strobe, LOW);
    sendByte(0xc0 + (i << 1)); // 設定地址
    sendByte(0x40);  // 顯示
    digitalWrite(strobe, HIGH);
    //Serial.println(String("i = ") + (i << 1));
}
void loop()
{
   MonsterFarm(); // 生地鼠
   delay(600); // 地鼠出現間隔
   UpdateLED(); // 更新顯示
   //Serial.println("One Time");
}
/*
0x40 遞增位置
0x42 鍵盤輸入
0x44 固定位置
*/