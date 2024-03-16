const int A = 12;
const int B = 11;
int interval = 500;
void setup()
{
  Serial.begin(9600); //溝通頻率
  pinMode(12,INPUT_PULLUP); // 按鈕A
  pinMode(11,INPUT_PULLUP); // 按鈕B
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(0)); //設定隨機種子
}
bool Astate, Bstate; // 按鈕狀態
void loop()
{
  delay(100); // Just inccase dont spanm the command 
  if(!digitalRead(A) && !digitalRead(B)) // 同時按AB鍵
  {
    delay(200); // 放開兩按鍵的緩衝時間
    interval = 500;
    // Serial.println("Same Fre: "); // 輔助
    while(digitalRead(A) && digitalRead(B)) // LED以固定頻率閃爍
    {
      for(int i = 0; i < interval; i++) // 如果中途偵測到變化就 break
      {
        delay(1);
        if(!digitalRead(A) || !digitalRead(B)) break;
      }
      digitalWrite(LED_BUILTIN, HIGH);
      for(int i = 0; i < interval; i++)
      {
        delay(1);
        if(!digitalRead(A) || !digitalRead(B)) break;
      }
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  else if(!digitalRead(A))
  {
    int pressedTime = 1;
    do
    {
      // Serial.println("A is pressed ! "); // 輔助
      delay(200);
      if(!digitalRead(A))
        pressedTime += 1;
    }
    while(!digitalRead(A) && pressedTime <= 5);
    if(pressedTime == 1) // 按下 A 
      // Serial.println("Light: ");
      digitalWrite(LED_BUILTIN, HIGH);
    while(!digitalRead(A) && pressedTime > 5)
    {
      if(digitalRead(A)) break; // 長按 A 之後放開
      else if(!digitalRead(B)) // 長按 A 之後按下 B
      {
        delay(200); // 防止執行太多次
        // Serial.println("Random: ");// 輔助
        while(digitalRead(A) && digitalRead(B)) // LED以隨機頻率閃爍
        {
          interval = random(100,1000);
          for(int i = 0; i < interval; i++) // 如果中途偵測到變化就 break
          {
            delay(1);
            if(!digitalRead(A) || !digitalRead(B)) break;
          }
          digitalWrite(LED_BUILTIN, HIGH);
          for(int i = 0; i < interval; i++)
          {
            delay(1);
            if(!digitalRead(A) || !digitalRead(B)) break;
          }
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
    }
  }
  else if(!digitalRead(B)) // 按下 B
  {
    // Serial.println("Dark: "); // 輔助
    digitalWrite(LED_BUILTIN, LOW);
  }
}
/*
A = On
B = Off
A + B = same frequencyt
A then B = random frequency
*/
