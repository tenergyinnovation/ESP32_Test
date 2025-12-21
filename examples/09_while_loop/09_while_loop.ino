#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน while Loop
 * ===================================================================
 * 
 * while loop ใช้วนซ้ำตราบเท่าที่เงื่อนไขเป็นจริง
 * 
 * ใช้ปุ่ม S1 (D32) เพื่อเริ่มการนับขึ้น
 * และปุ่ม S2 (VP) เพื่อเริ่มการนับถอยหลัง
 * ===================================================================
 */

// กำหนดพิน
const int BUTTON_S1 = 32;
const int BUTTON_S2 = 36;
const int LED_RED = 4;
const int LED_YELLOW = 12;

void setup() {
  // ตั้งค่า Serial
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน
  pinMode(BUTTON_S1, INPUT);
  pinMode(BUTTON_S2, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("while Loop Demo");
  Serial.println("S1: นับขึ้น 1-10 พร้อมกระพริบ LED แดง");
  Serial.println("S2: นับถอยหลัง 5-1 พร้อมกระพริบ LED เหลือง");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // ===== กดปุ่ม S1: นับขึ้น =====
  if (digitalRead(BUTTON_S1) == HIGH) {
    Serial.println("--- นับขึ้น 1-10 ---");
    
    int counter = 1;
    while (counter <= 10) {
      Serial.print("Counter: ");
      Serial.println(counter);
      digitalWrite(LED_RED, HIGH);
      delay(200);
      digitalWrite(LED_RED, LOW);
      delay(300);
      counter++;
    }
    
    Serial.println("เสร็จสิ้น");
    Serial.println();
    delay(1000);
  }
  
  // ===== กดปุ่ม S2: นับถอยหลัง =====
  if (digitalRead(BUTTON_S2) == HIGH) {
    Serial.println("--- นับถอยหลัง 5-1 ---");
    
    int countdown = 5;
    while (countdown > 0) {
      Serial.print("Countdown: ");
      Serial.println(countdown);
      digitalWrite(LED_YELLOW, HIGH);
      delay(200);
      digitalWrite(LED_YELLOW, LOW);
      delay(300);
      countdown--;
    }
    
    Serial.println("🚀 Blast off!");
    Serial.println();
    delay(1000);
  }
  
  delay(100);
}
