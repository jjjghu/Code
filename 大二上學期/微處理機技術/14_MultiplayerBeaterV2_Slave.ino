unsigned long prevtime = 0; // 硬體中斷當中用於debouncing 的變數
unsigned long prevtimeB = 0;
const int buttom =  2;
const int buttomB = 3; // 硬體中斷必須要接在 2 3 其一
void setup()
{
  Serial.begin(9600); // 輸出目的地
  pinMode(buttom, INPUT_PULLUP);
  pinMode(buttomB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttom), flash, FALLING); // 硬體中斷: 按鈕被按下時呼叫 Flash
  attachInterrupt(digitalPinToInterrupt(buttomB), flashB, FALLING); // 硬體中斷: 按鈕被按下時呼叫 Flash
}
void loop()
{
}
void flash() // 按下按鈕時觸發
{
  if(millis() - prevtime > 100) // 硬體中斷 debouncing
  {
    prevtime = millis(); // 更新按下時間, 故不可使用 if(rightPlace && millis() - prevtime > 50)
    Serial.write("1"); // 輸入打擊
  }
}
void flashB() // 按下按鈕時觸發
{
  if(millis() - prevtimeB > 100) // 硬體中斷 debouncing
  {
    prevtimeB = millis(); // 更新按下時間, 故不可使用 if(rightPlace && millis() - prevtime > 50)
    Serial.write("2"); // 輸入打擊
  }
}