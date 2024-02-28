int num; // 數字
bool printed = false; // 判斷是否列印
void setup()
{
    Serial.begin(9600); // 設定溝通頻率
}
void loop()
{
    if(!printed) // 如果沒有被印過, 確保不會在沒輸入時重複輸出
    {
      Serial.println("請輸入一個整數：");
      printed = true;
    }
    if(Serial.available() > 0) // 如果有輸入東西
    {
      int num = Serial.parseInt(); // 讀取數字, 如果用Serial.read會只讀取一個字元
      if(num % 7 == 0) Serial.println("是"); // 是 7 的倍數
      else Serial.println("不是"); // 不是 7 的倍數
      printed = false; // 重置列印紀錄, 以免只詢問一次
    }
    while(Serial.available() > 0) //清除結尾沒讀到的部分, 避免出現錯誤
    {
      Serial.read();
    }
    delay(100);
}