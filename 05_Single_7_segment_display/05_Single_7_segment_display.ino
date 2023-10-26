const int strobe = 8; // 閘門
const int clock = 9; // 時脈
const int dio = 10; // 輸入輸出
void sendByte(byte data) // 傳送指令 == shiftOut
{
 for(int i = 0; i < 8; i++)
 {
  digitalWrite(clock, LOW);
  digitalWrite(dio, (data & 1 ? HIGH : LOW));
  data = data >> 1;
  digitalWrite(clock, HIGH);
 }
}
void sendCommand(byte cmd) // 觸發傳送
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

byte list[] = {0x21, 0x60, 0x44, 0x0c, 0x18, 0x50, 0x42, 0x03};
int cnt = 0;
void loop()
{
  Serial.println("DOINGJOBS");
 setSegNum(0xce, list[cnt]);
 delay(1000);
}
/*
0x00 清空
0x4 数据命令设置, 0x40 = 寫數據
0x8 显示控制
0xC 顯示器的地址
shiftOut(輸出, 時脈, 順序(LSB, MSB), 指令內容)
1000010 => 0100001 => 21
0000011 => 1100000 => 60
0010001 => 1000100 => 44
0011000 => 0001100 => C
0001100 => 0011000 => 18
0000101 => 1010000 => 50
0100001 => 1000010 => 42
1100000 => 0000011 => 3
*/