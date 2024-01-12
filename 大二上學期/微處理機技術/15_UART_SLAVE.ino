const int buttom = 2; // 按鈕
bool LEDMODE = false; // 閃爍模式
bool LEDSTATE = false; // 控制亮暗
void setup()
{
  Serial.begin(9600);
  pinMode(buttom, INPUT_PULLUP); // 按鈕設定
  attachInterrupt(digitalPinToInterrupt(buttom), flash, FALLING);
  pinMode(LED_BUILTIN, OUTPUT); // LED 設定
  digitalWrite(LED_BUILTIN, LEDSTATE); // 預設為暗
  cli();
  TCCR1A = 0; // reset
  TCCR1B = 0; // reset
  TCCR1B |= B00000100; //將 Prescalar 設定為 256
  TIMSK1 |= B00000010; // 啟動 A 的比對模式
  OCR1A = 18750; // 50000 個週期, 代表 800 ms (Prescalar = 256)
  sei();
}
void flash() // 按下按鈕, 傳指令
{
  Serial.write('M'); // 傳指令
}
ISR(TIMER1_COMPA_vect)
{
  TCNT1 = 0; // reset timer
  char cur;
  while(Serial.available() > 0)//讀取指令
  {
    cur = Serial.read();
  }
  if(cur == 'M') Serial.write('M');// 拿錯指令, 輸回去
  if(cur == 'S') // 收到指令
  {
    LEDMODE = !LEDMODE; // 更換模式
  }
  if(LEDMODE) // 如果閃爍模式開啟就閃爍
  {
    digitalWrite(LED_BUILTIN, LEDSTATE);
    LEDSTATE = !LEDSTATE;
  }
  else // 閃爍模式關閉, 恆暗
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
void loop()
{

}