/*
 * ตัวอย่าง: การควบคุม Relay Module ผ่าน library esp32_iot
 * 
 * คำอธิบาย:
 * - โปรแกรมนี้แสดงการใช้งาน library esp32_iot ในการควบคุม Relay Module 2 ตัว
 * - Relay1 และ Relay2 จะสลับกันเปิด-ปิดทุกๆ 1 วินาที
 * - เมื่อ Relay1 เปิด → Relay2 จะปิด และเมื่อ Relay2 เปิด → Relay1 จะปิด
 * - ใช้ฟังก์ชัน relay1_On(), relay1_Off(), relay2_On(), relay2_Off() จาก library
 * - Relay Module เป็นแบบ Active HIGH (ส่งสัญญาณ HIGH เพื่อเปิด)
 * - แสดงสถานะการทำงานผ่าน Serial Monitor
 * 
 * พินที่ใช้งาน:
 * - Relay1: GPIO 25
 * - Relay2: GPIO 26
 */

#include <Arduino.h>
#include <esp32_iot.h>

// สร้าง object สำหรับใช้งาน library esp32_iot
esp32_iot board;

void setup() {
  // เริ่มต้น Serial communication ที่ baud rate 115200
  Serial.begin(115200);
  delay(1000);
  
  // เริ่มต้นการทำงานของ esp32_iot library
  board.begin();
  
  // แสดงข้อความเริ่มต้นโปรแกรม
  Serial.println("\n=================================");
  Serial.println("โปรแกรมทดสอบ Relay Module");
  Serial.println("ผ่าน library esp32_iot");
  Serial.println("=================================");
  Serial.println("Relay1 และ Relay2 จะสลับกัน");
  Serial.println("เปิด-ปิดทุกๆ 1 วินาที\n");
}

void loop() {
  // ---- เปิด Relay1 และปิด Relay2 ----
  Serial.println("⚡ Relay1: ON  | Relay2: OFF");
  board.relay1_On();   // เปิด Relay1 (ส่งสัญญาณ HIGH)
  board.relay2_Off();  // ปิด Relay2 (ส่งสัญญาณ LOW)
  delay(1000);         // หน่วงเวลา 1000 มิลลิวินาที (1 วินาที)
  
  // ---- ปิด Relay1 และเปิด Relay2 ----
  Serial.println("⚡ Relay1: OFF | Relay2: ON");
  board.relay1_Off();  // ปิด Relay1 (ส่งสัญญาณ LOW)
  board.relay2_On();   // เปิด Relay2 (ส่งสัญญาณ HIGH)
  delay(1000);         // หน่วงเวลา 1000 มิลลิวินาที (1 วินาที)
  
  // แสดงข้อความแบ่งรอบ
  Serial.println("---");
  
  // โปรแกรมจะวนกลับไปเริ่มต้นใหม่
}
