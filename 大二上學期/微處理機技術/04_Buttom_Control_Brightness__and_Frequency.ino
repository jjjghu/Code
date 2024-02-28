const int A = 3; 
const int B = 12;
const int LED = 5;
int interval = 500; // 閃爍延遲
int lightlevel = 128; // 亮度
int startTime, prevTime = 0;
unsigned int cnt = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(LED, OUTPUT); // LED 輸出
}
void loop()
{
    if(!digitalRead(A))
    {
      int pressedTime = 1;
      do
      {
        // Serial.println("Apressed ! "); //方便測試
        delay(200); // 放開道再次按下的緩衝期
        if(!digitalRead(A))
           pressedTime += 1;
      }
      while(!digitalRead(A) && pressedTime <= 5); // if not let go the buttom, pressed instead
      if(pressedTime > 5) // 長按 A 鍵時，直接變最亮
      {
        // Serial.println("You just pressed the buttom for more than 1000ms ! "); // 方便測試
        lightlevel = 255;
      }
      else if(pressedTime == 2) // 連續按壓 A 鍵兩次時，減少些許亮度
      {
        lightlevel = constrain(lightlevel - 10, 0, 255); // 限制亮度不超過範圍
      }
      else if(pressedTime == 1) // 每按壓 A 鍵一次，增加些許亮度
      {
        lightlevel = constrain(lightlevel + 10, 0, 255); // 限制亮度不超過範圍
      }
      // Serial.print("You press the buttom for "); // 方便測試
      // Serial.print(pressedTime);
      // Serial.println(" TImes ! ");
    }
    if(!digitalRead(B))
    {
      int bpressed = 1;
      do
      {
        // Serial.println("Bpressed ! "); //方便測試
        delay(200);
        if(!digitalRead(B))
           bpressed += 1;

      }while(!digitalRead(B) && bpressed <= 5);
      if(bpressed > 5)
      {
        interval = 0;
      }
      else if(bpressed == 2)
      {
        interval = max(interval - 100, 0);
      }
      else if(bpressed == 1)
      {
        interval += 100;
      }
      
      // Serial.print("You press the buttom for "); // 方便測試
      // Serial.print(bpressed);
      // Serial.println(" TImes ! ");
    }
    // Serial.print("Interval = ");
    // Serial.println(interval);
    // Serial.print("lightleve = ");
    // Serial.println(lightlevel);
    int i = 0;
    startTime = millis();
    if(interval == 0)
    {
      digitalWrite(LED, lightlevel);
    }
    else if(startTime - prevTime >= interval)
    {
      prevTime = millis();
      digitalWrite(LED, !digitalRead(LED));
      if(cnt & 1) analogWrite(LED, 0);
      else analogWrite(LED, lightlevel);
      cnt++;
    }
}