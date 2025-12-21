#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน if-else if-else Statement
 * ===================================================================
 * 
 * if-else if-else ใช้เมื่อมีหลายเงื่อนไข:
 * - ตรวจสอบเงื่อนไขตามลำดับ
 * - เมื่อพบเงื่อนไขที่เป็นจริง จะทำงานแล้วข้ามส่วนอื่น
 * - ถ้าทุกเงื่อนไขเป็นเท็จ จะทำงานใน else
 * 
 * ใช้ปุ่ม 4 ปุ่ม (S1-S4) ควบคุม LED 4 สี
 * ===================================================================
 */

// กำหนดพิน (ตาม diagram.json)
const int BUTTON_S1 = 32;     // ปุ่ม S1
const int BUTTON_S2 = 36;     // ปุ่ม S2 (VP)
const int BUTTON_S3 = 35;     // ปุ่ม S3
const int BUTTON_S4 = 34;     // ปุ่ม S4
const int LED_RED = 4;        // LED สีแดง
const int LED_YELLOW = 12;    // LED สีเหลือง
const int LED_BLUE = 2;       // LED สีน้ำเงิน
const int LED_GREEN = 15;     // LED สีเขียว

void setup() {
  // ตั้งค่า Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพินปุ่ม
  pinMode(BUTTON_S1, INPUT);
  pinMode(BUTTON_S2, INPUT);
  pinMode(BUTTON_S3, INPUT);
  pinMode(BUTTON_S4, INPUT);
  
  // ตั้งค่าพิน LED
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("if-else if-else Statement Demo");
  Serial.println("กดปุ่ม S1-S4 เพื่อเปิด LED สีต่างๆ");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // อ่านค่าปุ่มทั้ง 4 (LOW = กด, HIGH = ไม่กด)
  bool btn1 = digitalRead(BUTTON_S1) == LOW;
  bool btn2 = digitalRead(BUTTON_S2) == LOW;
  bool btn3 = digitalRead(BUTTON_S3) == LOW;
  bool btn4 = digitalRead(BUTTON_S4) == LOW;
  
  // ปิด LED ทั้งหมดก่อน
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  
  // ===== if-else if-else statement =====
  if (btn1) {
    // กดปุ่ม S1 -> เปิด LED แดง
    digitalWrite(LED_RED, HIGH);
    Serial.println("S1 กด -> LED แดง");
  } else if (btn2) {
    // กดปุ่ม S2 -> เปิด LED เหลือง
    digitalWrite(LED_YELLOW, HIGH);
    Serial.println("S2 กด -> LED เหลือง");
  } else if (btn3) {
    // กดปุ่ม S3 -> เปิด LED น้ำเงิน
    digitalWrite(LED_BLUE, HIGH);
    Serial.println("S3 กด -> LED น้ำเงิน");
  } else if (btn4) {
    // กดปุ่ม S4 -> เปิด LED เขียว
    digitalWrite(LED_GREEN, HIGH);
    Serial.println("S4 กด -> LED เขียว");
  } else {
    // ไม่กดปุ่มใดๆ -> ปิด LED ทั้งหมด
    Serial.println("ไม่กดปุ่ม -> LED ปิดทั้งหมด");
  }
  
  // รอครึ่งวินาที
  delay(500);
}
