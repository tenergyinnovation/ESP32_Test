/*
 * ตัวอย่าง: การอ่านค่าสถานะจากปุ่มกด (Switch) โดยไม่ใช้ library
 * 
 * คำอธิบาย:
 * - โปรแกรมนี้แสดงการอ่านค่าปุ่มกด SW1-SW4 โดยใช้คำสั่ง Arduino พื้นฐาน
 * - ไม่ใช้ library esp32_iot แต่ใช้ digitalRead() โดยตรง
 * - ปุ่มเป็นแบบ Active LOW (กดปุ่ม = สัญญาณ LOW, ไม่กด = สัญญาณ HIGH)
 * - ใช้ INPUT_PULLUP เพื่อเปิดใช้งาน Pull-up Resistor ภายใน
 * - แสดงสถานะปุ่มที่ถูกกดผ่าน Serial Monitor
 * 
 * พินที่ใช้งาน:
 * - SW1: GPIO 32
 * - SW2: GPIO 36 (VP)
 * - SW3: GPIO 35
 * - SW4: GPIO 34
 */

#include <Arduino.h>

// กำหนดหมายเลขพินสำหรับปุ่มกด SW1-SW4
const int SW1_PIN = 32;  // ปุ่ม SW1
const int SW2_PIN = 36;  // ปุ่ม SW2 (VP)
const int SW3_PIN = 35;  // ปุ่ม SW3
const int SW4_PIN = 34;  // ปุ่ม SW4

void setup() {
  // เริ่มต้น Serial communication ที่ baud rate 115200
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพินปุ่มกดเป็น INPUT_PULLUP
  // INPUT_PULLUP จะเปิดใช้งาน Pull-up Resistor ภายใน
  // ทำให้เมื่อไม่กดปุ่ม ค่าจะเป็น HIGH (3.3V)
  // เมื่อกดปุ่ม ค่าจะเป็น LOW (0V) - Active LOW
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(SW4_PIN, INPUT_PULLUP);
  
  // แสดงข้อความเริ่มต้นโปรแกรม
  Serial.println("\n=================================");
  Serial.println("โปรแกรมทดสอบ Switch (Active LOW)");
  Serial.println("โดยไม่ใช้ library");
  Serial.println("=================================");
  Serial.println("กดปุ่ม SW1-SW4 เพื่อทดสอบ");
  Serial.println("ปุ่มเป็นแบบ Active LOW");
  Serial.println("(กดปุ่ม = LOW, ไม่กด = HIGH)\n");
}

void loop() {
  // อ่านค่าสถานะของปุ่ม SW1
  // digitalRead() จะคืนค่า LOW (0) เมื่อกดปุ่ม
  // และคืนค่า HIGH (1) เมื่อไม่กดปุ่ม
  int sw1_state = digitalRead(SW1_PIN);
  
  // ตรวจสอบว่าปุ่ม SW1 ถูกกดหรือไม่
  if (sw1_state == LOW) {
    // ถ้าค่าเป็น LOW แสดงว่ากดปุ่ม
    Serial.println("🔘 SW1 กด (สถานะ: LOW)");
    delay(300);  // หน่วงเวลาเพื่อป้องกันการอ่านค่าซ้ำ (debounce)
  }
  
  // อ่านค่าสถานะของปุ่ม SW2
  int sw2_state = digitalRead(SW2_PIN);
  
  // ตรวจสอบว่าปุ่ม SW2 ถูกกดหรือไม่
  if (sw2_state == LOW) {
    // ถ้าค่าเป็น LOW แสดงว่ากดปุ่ม
    Serial.println("🔘 SW2 กด (สถานะ: LOW)");
    delay(300);  // หน่วงเวลาเพื่อป้องกันการอ่านค่าซ้ำ (debounce)
  }
  
  // อ่านค่าสถานะของปุ่ม SW3
  int sw3_state = digitalRead(SW3_PIN);
  
  // ตรวจสอบว่าปุ่ม SW3 ถูกกดหรือไม่
  if (sw3_state == LOW) {
    // ถ้าค่าเป็น LOW แสดงว่ากดปุ่ม
    Serial.println("🔘 SW3 กด (สถานะ: LOW)");
    delay(300);  // หน่วงเวลาเพื่อป้องกันการอ่านค่าซ้ำ (debounce)
  }
  
  // อ่านค่าสถานะของปุ่ม SW4
  int sw4_state = digitalRead(SW4_PIN);
  
  // ตรวจสอบว่าปุ่ม SW4 ถูกกดหรือไม่
  if (sw4_state == LOW) {
    // ถ้าค่าเป็น LOW แสดงว่ากดปุ่ม
    Serial.println("🔘 SW4 กด (สถานะ: LOW)");
    delay(300);  // หน่วงเวลาเพื่อป้องกันการอ่านค่าซ้ำ (debounce)
  }
  
  // หน่วงเวลาเล็กน้อยเพื่อลดการใช้งาน CPU
  delay(10);
}
