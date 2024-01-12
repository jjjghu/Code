int num;
bool first = true; // 判斷是否第一次列印
bool printed = false; // 判斷是否列印過問題(輸入數字之後重置), 必須要有, 以免無限詢問
void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN,OUTPUT); // 將內建 LED 設定為輸出
}
void print()
{
    if(!printed) // 沒被印過
    {   
        if(first) // 第一次印
        { 
            Serial.print("請輸入一個整數(0~100):");
            first = false; // 更新 first 判斷
        }
        else Serial.print("請輸入一個整數:");
        printed = true; // 更新列印狀態
    }
}
void loop(){
    print(); // 詢問
    if(Serial.available() > 0)
    {
        num = Serial.parseInt(); // 獲取輸入數字
        Serial.println(num); // 顯示輸入內容
        while(Serial.available() > 0) // 清除數字之外的輸入
        {
            Serial.read(); 
        }
        if(num > 100 || num < 0) // 範圍外
        {
            Serial.println("Invalid");
            printed = false;
        }
        else 
        {
          printed = false; //取得這輪數字之後, 重置詢問狀態並且再次詢問問題 
          print();
        }
        while(Serial.available() == 0 && 0 <= num && num <= 100) // 沒有額外輸入並且在範圍之內，更新閃爍頻率
        {
            delay(num * 10);
            digitalWrite(13,HIGH); // 明
            delay(num * 10);
            digitalWrite(13,LOW); // 暗
        }
    }
    delay(100); // 延遲
}