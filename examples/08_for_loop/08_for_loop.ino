#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน for Loop
 * ===================================================================
 * 
 * for loop ใช้ทำซ้ำจำนวนครั้งที่กำหนด
 * รูปแบบ: for (ค่าเริ่มต้น; เงื่อนไข; การเพิ่มค่า) { }
 * 
 * ใช้ LED 4 สี วิ่งตามลำดับ
 * ===================================================================
 */

// กำหนดพิน LED (ตาม diagram.json)
const int LED_RED = 4;
const int LED_YELLOW = 12;
const int LED_BLUE = 2;
const int LED_GREEN = 15;

// อาร์เรย์เก็บพิน LED ทั้ง 4
const int ledPins[] = {LED_RED, LED_YELLOW, LED_BLUE, LED_GREEN};
const int numLeds = 4;

void setup() {
  // ตั้งค่า Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน LED ทั้งหมด
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("for Loop Demo");
  Serial.println("LED วิ่งตามลำดับ Red->Yellow->Blue->Green");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // ===== for loop =====
  // วน LED ทีละดวงตามลำดับ
  for (int i = 0; i < numLeds; i++) {
    // แสดงลำดับ LED ที่เปิด
    Serial.print("LED ดวงที่ ");
    Serial.print(i + 1);
    Serial.println(" เปิด");
    
    // เปิด LED ดวงปัจจุบัน
    digitalWrite(ledPins[i], HIGH);
    delay(500);
    
    // ปิด LED ดวงปัจจุบัน
    digitalWrite(ledPins[i], LOW);
    delay(200);
  }
  
  // แสดงข้อความว่าครบรอบ
  Serial.println("--- ครบรอบ ---");
  Serial.println();
  delay(1000);
}
