const int strobe = 8;  //閘門
const int clock = 9;  //時脈
const int dio = 10;  //輸入輸出
void sendByte(byte data)  //傳送指令
{
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(clock, LOW);
    digitalWrite(dio, (data & 1 ? HIGH : LOW));
    data = data >> 1;
    digitalWrite(clock, HIGH);
  }
}
void sendCommand(byte cmd)  //觸發傳送
{
  digitalWrite(strobe, LOW);
  sendByte(cmd);
  digitalWrite(strobe, HIGH);
}
void setSegNum(byte seg_address, byte pattern)
{
  digitalWrite(strobe, LOW);
  sendByte(seg_address);
  sendByte(pattern);
  digitalWrite(strobe, HIGH);
}
void setup()
{
  Serial.begin(9600);
  pinMode(dio, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(strobe, OUTPUT);
  digitalWrite(strobe, HIGH);
  digitalWrite(clock, HIGH);

  sendCommand(0x40);
  sendCommand(0xc0);
  for (byte i = 0; i < 16; i++) // 清空顯示內容
  {
    setSegNum(i,0x00);
  }
}

byte list[] = {0x50, 0x58, 0x18, 0x08, 0x00, 0x40, 0x60, 0x61, 0x21, 0x01, 0x00, 0x40};
byte list2[] = {0x40, 0x00, 0x08, 0x0c, 0x4c, 0x44, 0x40, 0x00, 0x01, 0x03, 0x43, 0x42};
int cnt = 0;
void loop()
{
  setSegNum(0xce, list2[cnt]);
  setSegNum(0xcc, list[cnt]);
  cnt = ++cnt % 12;
  delay(500);
}
/*
0x00 清空
0x4 数据命令设置, 0x40 = 寫數據
0x8 显示控制 
0xC 顯示器的地址
shiftOut(輸出, 時脈, 順序(LSB, MSB), 指令內容)
0000101 =1010000 =50
0001101 =1011000 =58
0001100 =0011000 =18
0001000 =0001000 =8
0000000 =0000000 =0
0000001 =1000000 =40
0000011 =1100000 =60
1000011 =1100001 =61
1000010 =0100001 =21
1000000 =0000001 =1
0000000 =0000000 =0
0000001 =1000000 =40

0000001 =1000000 =40
0000000 =0000000 =0
0001000 =0001000 =8
0011000 =0001100 =C
0011001 =1001100 =4C
0010001 =1000100 =44
0000001 =1000000 =40
0000000 =0000000 =0
1000000 =0000001 =1
1100000 =0000011 =3
1100001 =1000011 =43
0100001 =1000010 =42
*/
