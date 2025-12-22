/*
 * ตัวอย่าง: การควบคุม Buzzer Module ผ่าน library esp32_iot
 * 
 * คำอธิบาย:
 * - โปรแกรมนี้แสดงการใช้งาน library esp32_iot ในการควบคุม Buzzer Module
 * - Buzzer จะส่งเสียงบี๊บ (beep) 3 ครั้ง แต่ละครั้ง 200ms จากนั้นหยุด 2 วินาที
 * - ใช้ฟังก์ชัน buzzer_beep(times, interval_ms) จาก library
 * - Buzzer Module ใช้ LEDC PWM ในการส่งเสียงที่ความถี่ 2048 Hz
 * - แสดงสถานะการทำงานผ่าน Serial Monitor
 * 
 * พินที่ใช้งาน:
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
  Serial.println("โปรแกรมทดสอบ Buzzer Module");
  Serial.println("ผ่าน library esp32_iot");
  Serial.println("=================================");
  Serial.println("Buzzer จะส่งเสียงบี๊บ 3 ครั้ง");
  Serial.println("จากนั้นหยุด 2 วินาที แล้วเริ่มใหม่\n");
}

void loop() {
  // ---- เปิด Buzzer ส่งเสียงบี๊บ 3 ครั้ง ----
  Serial.println("🔊 Buzzer: BEEP 3 ครั้ง");
  board.buzzer_beep(3, 200);      // ส่งเสียงบี๊บ 3 ครั้ง, แต่ละครั้ง 200ms
  
  // หน่วงเวลาก่อนรอบถัดไป
  Serial.println("🔇 Buzzer: หยุด 2 วินาที\n");
  delay(2000);                    // หน่วงเวลา 2000 มิลลิวินาที (2 วินาที)
  
  // แสดงข้อความแบ่งรอบ
  Serial.println("---");
  
  // โปรแกรมจะวนกลับไปเริ่มต้นใหม่
}
