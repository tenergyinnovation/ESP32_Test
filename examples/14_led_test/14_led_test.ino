#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการทดสอบ LED Module ทั้ง 4 ดวง
 * ===================================================================
 * 
 * โปรแกรมนี้ทดสอบการทำงานของ LED ทั้ง 4 ดวง โดย:
 * - LED ติดดับสลับกันทีละดวง
 * - หน่วงเวลา 500ms (0.5 วินาที) ระหว่างการติดดับ
 * - แสดงสถานะผ่าน Serial Monitor
 * 
 * LED Module (Active LOW):
 * - LED1: Yellow (D12) - LOW=เปิด, HIGH=ปิด
 * - LED2: Red (D4)     - LOW=เปิด, HIGH=ปิด
 * - LED3: Blue (D2)    - LOW=เปิด, HIGH=ปิด
 * - LED4: Green (D15)  - LOW=เปิด, HIGH=ปิด
 * ===================================================================
 */

// กำหนดหมายเลขพิน LED (ตาม diagram.json)
const int LED1_PIN = 12;  // Yellow LED
const int LED2_PIN = 4;   // Red LED
const int LED3_PIN = 2;   // Blue LED
const int LED4_PIN = 15;  // Green LED

void setup() {
  // เริ่มต้น Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน LED ทั้งหมดเป็น OUTPUT
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  
  // ปิด LED ทั้งหมดตอนเริ่มต้น (Active LOW = HIGH = ปิด)
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  digitalWrite(LED3_PIN, HIGH);
  digitalWrite(LED4_PIN, HIGH);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("LED Module Test - 4 LEDs");
  Serial.println("Yellow -> Red -> Blue -> Green");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // ===== LED1: Yellow (เหลือง) =====
  Serial.println("LED1 (Yellow) - เปิด");
  digitalWrite(LED1_PIN, LOW);   // เปิด LED (Active LOW)
  delay(500);                    // รอ 0.5 วินาที
  
  Serial.println("LED1 (Yellow) - ปิด");
  digitalWrite(LED1_PIN, HIGH);  // ปิด LED
  delay(500);                    // รอ 0.5 วินาที
  Serial.println();
  
  // ===== LED2: Red (แดง) =====
  Serial.println("LED2 (Red) - เปิด");
  digitalWrite(LED2_PIN, LOW);   // เปิด LED (Active LOW)
  delay(500);                    // รอ 0.5 วินาที
  
  Serial.println("LED2 (Red) - ปิด");
  digitalWrite(LED2_PIN, HIGH);  // ปิด LED
  delay(500);                    // รอ 0.5 วินาที
  Serial.println();
  
  // ===== LED3: Blue (น้ำเงิน) =====
  Serial.println("LED3 (Blue) - เปิด");
  digitalWrite(LED3_PIN, LOW);   // เปิด LED (Active LOW)
  delay(500);                    // รอ 0.5 วินาที
  
  Serial.println("LED3 (Blue) - ปิด");
  digitalWrite(LED3_PIN, HIGH);  // ปิด LED
  delay(500);                    // รอ 0.5 วินาที
  Serial.println();
  
  // ===== LED4: Green (เขียว) =====
  Serial.println("LED4 (Green) - เปิด");
  digitalWrite(LED4_PIN, LOW);   // เปิด LED (Active LOW)
  delay(500);                    // รอ 0.5 วินาที
  
  Serial.println("LED4 (Green) - ปิด");
  digitalWrite(LED4_PIN, HIGH);  // ปิด LED
  delay(500);                    // รอ 0.5 วินาที
  Serial.println();
  
  // แสดงข้อความครบรอบ
  Serial.println("--- ครบรอบ 1 ครั้ง ---");
  Serial.println();
  delay(1000);                   // หยุดพัก 1 วินาที ก่อนเริ่มรอบใหม่
}
