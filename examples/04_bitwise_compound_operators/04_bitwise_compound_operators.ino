#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Bitwise และ Compound Operators
 * ===================================================================
 * 
 * Bitwise Operators: &, |, ^, ~, <<, >>
 * Compound Operators: +=, -=, *=, /=, %=
 * 
 * ตัวอย่างควบคุม LED 4 ดวง (D4, D12, D2, D15)
 * ===================================================================
 */

// กำหนดพิน LED (ตาม diagram.json)
const int LED_RED = 4;      // LED สีแดง
const int LED_YELLOW = 12;  // LED สีเหลือง
const int LED_BLUE = 2;     // LED สีน้ำเงิน
const int LED_GREEN = 15;   // LED สีเขียว

int counter = 0;  // ตัวนับ

void setup() {
  // ตั้งค่า Serial
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน LED เป็น OUTPUT
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  Serial.println("===================================");
  Serial.println("Bitwise & Compound Operators Demo");
  Serial.println("ควบคุม LED 4 ดวง");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // ===== Compound Operators (+=) =====
  counter += 1;  // เท่ากับ counter = counter + 1
  Serial.print("Counter: ");
  Serial.println(counter);
  
  // ===== Bitwise AND (&) =====
  // ใช้ตรวจสอบบิตที่ 0 (เลขคู่หรือคี่)
  int bit0 = counter & 1;  // ถ้าเป็น 1 = คี่, ถ้าเป็น 0 = คู่
  Serial.print("Bit 0 (คู่/คี่): ");
  Serial.println(bit0);
  
  // ควบคุม LED ตามค่าบิต
  digitalWrite(LED_RED, (counter & 1));      // บิตที่ 0
  digitalWrite(LED_YELLOW, (counter & 2));   // บิตที่ 1
  digitalWrite(LED_BLUE, (counter & 4));     // บิตที่ 2
  digitalWrite(LED_GREEN, (counter & 8));    // บิตที่ 3
  
  // แสดงสถานะ LED
  Serial.print("LED: R=");
  Serial.print((counter & 1) ? "ON" : "OFF");
  Serial.print(" Y=");
  Serial.print((counter & 2) ? "ON" : "OFF");
  Serial.print(" B=");
  Serial.print((counter & 4) ? "ON" : "OFF");
  Serial.print(" G=");
  Serial.println((counter & 8) ? "ON" : "OFF");
  
  Serial.println();
  
  // รีเซ็ตตัวนับเมื่อถึง 15
  if (counter >= 15) {
    counter = 0;
    Serial.println("--- รีเซ็ตตัวนับ ---");
    Serial.println();
  }
  
  // รอ 1 วินาที
  delay(1000);
}
