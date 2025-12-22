/*
 * ตัวอย่าง: การควบคุม Relay ผ่านปุ่มกด Switch
 * 
 * คำอธิบาย:
 * - โปรแกรมนี้แสดงการควบคุม Relay Module 2 ตัวผ่านปุ่มกด SW1-SW4
 * - กดปุ่ม SW1 → Relay1 เปิด, Relay2 ปิด
 * - กดปุ่ม SW2 → Relay1 ปิด, Relay2 เปิด
 * - กดปุ่ม SW3 → Relay1 ปิด, Relay2 ปิด (ปิดทั้งคู่)
 * - กดปุ่ม SW4 → Relay1 เปิด, Relay2 เปิด (เปิดทั้งคู่)
 * - ทุกครั้งที่กดปุ่ม จะมีเสียง Buzzer beep 1 ครั้ง
 * - แสดงสถานะการทำงานผ่าน Serial Monitor
 * - ใช้ library esp32_iot ในการควบคุม
 * 
 * พินที่ใช้งาน:
 * - SW1-SW4: GPIO 32, 36, 35, 34
 * - Relay1: GPIO 25
 * - Relay2: GPIO 26
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
  
  // ปิด Relay ทั้งสองตัวเมื่อเริ่มต้นโปรแกรม
  board.relay1_Off();
  board.relay2_Off();
  
  // แสดงข้อความเริ่มต้นโปรแกรม
  Serial.println("\n=================================");
  Serial.println("โปรแกรมควบคุม Relay ผ่านปุ่มกด");
  Serial.println("ผ่าน library esp32_iot");
  Serial.println("=================================");
  Serial.println("SW1 = Relay1 ON,  Relay2 OFF");
  Serial.println("SW2 = Relay1 OFF, Relay2 ON");
  Serial.println("SW3 = Relay1 OFF, Relay2 OFF");
  Serial.println("SW4 = Relay1 ON,  Relay2 ON");
  Serial.println("=================================\n");
  Serial.println("สถานะเริ่มต้น:");
  Serial.println("⚡ Relay1: OFF | Relay2: OFF\n");
}

void loop() {
  // ตรวจสอบปุ่ม SW1
  if (board.read_SW1()) {
    // กดปุ่ม SW1: Relay1 เปิด, Relay2 ปิด
    Serial.println("🔘 SW1 กด");
    Serial.println("⚡ Relay1: ON  | Relay2: OFF");
    
    board.relay1_On();   // เปิด Relay1
    board.relay2_Off();  // ปิด Relay2
    board.buzzer_beep(1, 100);  // Buzzer beep 1 ครั้ง
    
    delay(300);  // Debounce delay
  }
  
  // ตรวจสอบปุ่ม SW2
  if (board.read_SW2()) {
    // กดปุ่ม SW2: Relay1 ปิด, Relay2 เปิด
    Serial.println("🔘 SW2 กด");
    Serial.println("⚡ Relay1: OFF | Relay2: ON");
    
    board.relay1_Off();  // ปิด Relay1
    board.relay2_On();   // เปิด Relay2
    board.buzzer_beep(1, 100);  // Buzzer beep 1 ครั้ง
    
    delay(300);  // Debounce delay
  }
  
  // ตรวจสอบปุ่ม SW3
  if (board.read_SW3()) {
    // กดปุ่ม SW3: Relay1 ปิด, Relay2 ปิด (ปิดทั้งคู่)
    Serial.println("🔘 SW3 กด");
    Serial.println("⚡ Relay1: OFF | Relay2: OFF (ปิดทั้งคู่)");
    
    board.relay1_Off();  // ปิด Relay1
    board.relay2_Off();  // ปิด Relay2
    board.buzzer_beep(1, 100);  // Buzzer beep 1 ครั้ง
    
    delay(300);  // Debounce delay
  }
  
  // ตรวจสอบปุ่ม SW4
  if (board.read_SW4()) {
    // กดปุ่ม SW4: Relay1 เปิด, Relay2 เปิด (เปิดทั้งคู่)
    Serial.println("🔘 SW4 กด");
    Serial.println("⚡ Relay1: ON  | Relay2: ON  (เปิดทั้งคู่)");
    
    board.relay1_On();   // เปิด Relay1
    board.relay2_On();   // เปิด Relay2
    board.buzzer_beep(1, 100);  // Buzzer beep 1 ครั้ง
    
    delay(300);  // Debounce delay
  }
  
  // หน่วงเวลาเล็กน้อยเพื่อลดการใช้งาน CPU
  delay(10);
}
