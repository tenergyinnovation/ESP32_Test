#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน do-while Loop
 * ===================================================================
 * 
 * do-while loop จะทำงานอย่างน้อย 1 ครั้งเสมอ
 * จากนั้นจึงตรวจสอบเงื่อนไข
 * 
 * ใช้ปุ่ม S3 (D35) เพื่อแสดงตัวอย่าง do-while
 * LED Blue (D2) จะกระพริบตามจำนวนครั้ง
 * ===================================================================
 */

// กำหนดพิน
const int BUTTON_S3 = 35;
const int LED_BLUE = 2;

void setup() {
  // ตั้งค่า Serial
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน
  pinMode(BUTTON_S3, INPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("do-while Loop Demo");
  Serial.println("กดปุ่ม S3 เพื่อทดสอบ do-while");
  Serial.println("LED Blue จะกระพริบ 3 ครั้ง");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // ===== กดปุ่ม S3: do-while =====
  if (digitalRead(BUTTON_S3) == LOW) {
    Serial.println("--- ทดสอบ do-while ---");
    
    // do-while จะทำงานอย่างน้อย 1 ครั้งเสมอ
    int count = 1;
    do {
      Serial.print("รอบที่ ");
      Serial.println(count);
      
      // กระพริบ LED
      digitalWrite(LED_BLUE, HIGH);
      delay(300);
      digitalWrite(LED_BLUE, LOW);
      delay(300);
      
      count++;
    } while (count <= 3);  // ตรวจสอบเงื่อนไขหลังทำงาน
    
    Serial.println("เสร็จสิ้น - ทำงาน 3 ครั้ง");
    Serial.println();
    delay(1000);
  }
  
  delay(100);
}
