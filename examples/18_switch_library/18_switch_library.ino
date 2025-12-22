/*
 * ตัวอย่าง: การอ่านค่าสถานะจากปุ่มกด (Switch) และควบคุม Buzzer
 * 
 * คำอธิบาย:
 * - โปรแกรมนี้แสดงการใช้งาน library esp32_iot ในการอ่านค่าจากปุ่มกด SW1-SW4
 * - เมื่อกดปุ่มแต่ละตัว จะแสดงข้อความและส่งเสียงบี๊บตามจำนวนที่กำหนด
 * - SW1 กด → แสดง "SW1 กด" + Buzzer beep 1 ครั้ง
 * - SW2 กด → แสดง "SW2 กด" + Buzzer beep 2 ครั้ง
 * - SW3 กด → แสดง "SW3 กด" + Buzzer beep 3 ครั้ง
 * - SW4 กด → แสดง "SW4 กด" + Buzzer beep 4 ครั้ง
 * - ปุ่มเป็นแบบ Active LOW (กดปุ่ม = สัญญาณ LOW)
 * 
 * พินที่ใช้งาน:
 * - SW1: GPIO 32
 * - SW2: GPIO 36 (VP)
 * - SW3: GPIO 35
 * - SW4: GPIO 34
 * - Buzzer: GPIO 13
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
  Serial.println("โปรแกรมทดสอบ Switch และ Buzzer");
  Serial.println("ผ่าน library esp32_iot");
  Serial.println("=================================");
  Serial.println("กดปุ่ม SW1-SW4 เพื่อทดสอบ");
  Serial.println("SW1 = Beep 1 ครั้ง");
  Serial.println("SW2 = Beep 2 ครั้ง");
  Serial.println("SW3 = Beep 3 ครั้ง");
  Serial.println("SW4 = Beep 4 ครั้ง\n");
}

void loop() {
  // ตรวจสอบปุ่ม SW1
  if (board.read_SW1()) {
    // แสดงข้อความผ่าน Serial Monitor
    Serial.println("🔘 SW1 กด");
    
    // ส่งเสียงบี๊บ 1 ครั้ง (interval 100ms)
    board.buzzer_beep(1, 100);
    
    // หน่วงเวลาเพื่อป้องกันการอ่านค่าซ้ำ (debounce)
    delay(300);
  }
  
  // ตรวจสอบปุ่ม SW2
  if (board.read_SW2()) {
    // แสดงข้อความผ่าน Serial Monitor
    Serial.println("🔘 SW2 กด");
    
    // ส่งเสียงบี๊บ 2 ครั้ง (interval 100ms)
    board.buzzer_beep(2, 100);
    
    // หน่วงเวลาเพื่อป้องกันการอ่านค่าซ้ำ (debounce)
    delay(300);
  }
  
  // ตรวจสอบปุ่ม SW3
  if (board.read_SW3()) {
    // แสดงข้อความผ่าน Serial Monitor
    Serial.println("🔘 SW3 กด");
    
    // ส่งเสียงบี๊บ 3 ครั้ง (interval 100ms)
    board.buzzer_beep(3, 100);
    
    // หน่วงเวลาเพื่อป้องกันการอ่านค่าซ้ำ (debounce)
    delay(300);
  }
  
  // ตรวจสอบปุ่ม SW4
  if (board.read_SW4()) {
    // แสดงข้อความผ่าน Serial Monitor
    Serial.println("🔘 SW4 กด");
    
    // ส่งเสียงบี๊บ 4 ครั้ง (interval 100ms)
    board.buzzer_beep(4, 100);
    
    // หน่วงเวลาเพื่อป้องกันการอ่านค่าซ้ำ (debounce)
    delay(300);
  }
  
  // หน่วงเวลาเล็กน้อยเพื่อลดการใช้งาน CPU
  delay(10);
}
