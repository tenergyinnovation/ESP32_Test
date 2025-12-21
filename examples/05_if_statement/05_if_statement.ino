#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน if Statement
 * ===================================================================
 * 
 * if statement ใช้ตรวจสอบเงื่อนไข
 * ถ้าเงื่อนไขเป็นจริง จะทำงานในบล็อก { }
 * 
 * ใช้ปุ่ม S3 (D35) ควบคุม LED Red (D4)
 * ===================================================================
 */

// กำหนดพิน (ตาม diagram.json)
const int BUTTON_S3 = 35;  // ปุ่ม S3
const int LED_RED = 4;     // LED สีแดง

void setup() {
  // ตั้งค่า Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน
  pinMode(BUTTON_S3, INPUT);
  pinMode(LED_RED, OUTPUT);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("if Statement Demo");
  Serial.println("กดปุ่ม S3 เพื่อเปิด LED Red");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // อ่านค่าปุ่ม S3 (LOW = กด, HIGH = ไม่กด)
  bool buttonPressed = digitalRead(BUTTON_S3) == LOW;
  
  // แสดงสถานะปุ่ม
  Serial.print("ปุ่ม S3: ");
  
  // ===== if statement =====
  // ถ้ากดปุ่ม (LOW) จะเปิด LED
  if (buttonPressed) {
    digitalWrite(LED_RED, HIGH);
    Serial.println("กด -> LED เปิด");
  }
  
  // ถ้าไม่กดปุ่ม (HIGH) จะปิด LED
  if (!buttonPressed) {
    digitalWrite(LED_RED, LOW);
    Serial.println("ปล่อย -> LED ปิด");
  }
  
  // รอครึ่งวินาที
  delay(500);
}
