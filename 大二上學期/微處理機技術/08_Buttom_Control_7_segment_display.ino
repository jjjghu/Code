const int strobe = 8;
const int clock = 9;
const int data = 10;
byte list[] = {0x21, 0x60, 0x44, 0x0c, 0x18, 0x50, 0x42, 0x03}; // 初始顯示狀態
bool pressed[8] = {false}; // 檢查是否被按下的陣列
bool minus = false; // true 為輸出到跑馬燈, false是LED
byte readByte() // 讀取輸入
{
  byte value = 0x00;
  pinMode(data, INPUT); // 將鍵盤更改為輸入
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(clock, LOW);
    if(digitalRead(data))
    {
      value |= (0x01 << i);
    }
    digitalWrite(clock, HIGH);
  }
  pinMode(data, OUTPUT); // 回復原樣
  return value;
}
void sendByte(byte value) // 傳送指令
{
  for(int i = 0; i < 8; i++) // 讀 8 bit 拼成 byte
  {
    digitalWrite(clock, LOW);
    digitalWrite(data, (value & 1? HIGH: LOW));
    digitalWrite(clock, HIGH);
    value = value >> 1;
  }
}
void sendCommand(byte value) // 簡化單個指令的輸入
{
  digitalWrite(strobe, LOW);
  sendByte(value);
  digitalWrite(strobe, HIGH);
}
byte readbutton() 讀取按鈕狀態
{
  byte value = 0x00;
  digitalWrite(strobe, LOW);
  sendByte(0x42); // 將鍵盤作為輸入來源
  for(int i = 0; i < 4; i++)
  {
    byte read = readByte();
    value |= (read << i);
  }
  digitalWrite(strobe, HIGH);
  return value;
}
void setLed(byte value, byte position) // 將 position 上的數值(跑馬燈或是LED) 改為 value
{
  pinMode(data, OUTPUT); // 輸出到七段顯示器
  sendCommand(0x44); // 固定地址
  digitalWrite(strobe, LOW);
  if(!minus) // False 為 LED
    sendByte(0xc1 + (position << 1));
  else // TRUE 為跑馬燈
    sendByte(0xc0 + (position << 1));
  sendByte(value); // 顯示數值
  digitalWrite(strobe, HIGH);
}
byte merge = 0x00; // 最後要顯示的樣子
bool vibration = false; // 控制閃爍
void updateLed(byte buttonState) // LED 更新
{
  if(buttonState == 3) // 按下前面兩個按鍵
  {
    for(int i = 0; i < 8; i++) // 將 or 運算的結果(merge) 顯示出來
    {
      minus = true; //更改的是跑馬燈 
      if(pressed[i]) // 如果是被按下的, 顯示merge
      {
        setLed(merge, i);
      }
      else
      {
        setLed(list[i], i); // 將其他顯示器重置為預設顯示狀態
      }
    }
    minus = false; // 更改上方 LED (方便觀察, 非必要)
    for(int i = 0; i < 8; i++)
    {
      setLed(LOW, i); // 關掉
      pressed[i] = false; // 重設選取狀態
    }
    merge = 0x00; // 重設輸出狀態
  }
  else // 沒有要顯示最後輸出
  {
    for(int i = 0; i < 8; i++) // 更新被選取按鈕的狀態
    {
      byte mask = 0x01 << i;
      if(buttonState & mask) // 查看按鈕是否被按下
      {
        pressed[i] = true; // 更新按鈕狀態陣列
        setLed(pressed[i], i); // 有就設置為亮 (上面的 LED, 方便觀察)
        merge |= list[i]; // or 運算
      }
    }
    minus = true; // 閃爍跑馬燈
    for(int i = 0; i < 8; i++)
    {
      if(pressed[i]) // 被選取到才要閃爍
      {
        if(vibration) // 透過 vibration 控制閃爍
        {
          setLed(list[i], i); // 閃爍狀態: 亮
        }
        else setLed(0x00, i); // 閃爍狀態: 暗
        
      }
    }
    minus = false; // 重設
    vibration = !vibration; // 閃爍狀態更新
  }
}
void setup() // 事前設定
{
  Serial.begin(9600); // 方便觀察, 非必要
  pinMode(strobe, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  digitalWrite(clock, HIGH); // 防止意外
  digitalWrite(strobe, HIGH); // 同上

  sendCommand(0x88); // 顯示器打開
  sendCommand(0x8f); // 亮度最亮

  sendCommand(0x40); // 遞增地址
  digitalWrite(strobe, LOW); // 指令起手
  sendByte(0xc0); // 設定初始位置
  for(byte i = 0; i <= 7; i++) // 預設狀態
  {
    // 每做一次指令地址會+1, 共16個
    sendByte(list[i]); // 跑馬燈為預設
    sendByte(0x00); // LED 關閉
  }
  digitalWrite(strobe, HIGH); // 指令結束
}
void loop()
{
  byte buttonState = readbutton(); // 讀取按鈕狀態
   // Serial.println(String("ButtonState = ") + buttonState); // 觀察, 非必要
  updateLed(buttonState); // 根據按鈕更新顯示狀態
  delay(250); // 閃爍頻率, 同時一定程度上確保不會反應過快
}
// 1000010 => 0100001 => 21
// 0000011 => 1100000 => 60
// 0010001 => 1000100 => 44
// 0011000 => 0001100 => C
// 0001100 => 0011000 => 18
// 0000101 => 1010000 => 50
// 0100001 => 1000010 => 42
// 1100000 => 0000011 => 3 
