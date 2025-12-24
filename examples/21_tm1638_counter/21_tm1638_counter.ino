/*
 * ตัวอย่างโปรแกรม: ทดสอบ TM1638 Module - นับเลข 0-10000000
 * -------------------------------------------------
 * โปรแกรมนี้แสดงการใช้งาน TM1638 module ผ่านไลบรารี esp32_iot
 * โดยจะนับเลขจาก 0 ถึง 10000000 เพิ่มขึ้นทีละ 1 ทุกๆ 0.1 วินาที
 * เมื่อถึง 10000000 แล้วจะเริ่มนับใหม่ที่ 0 อีกครั้ง
 * 
 * Hardware:
 * - ESP32 Tiny32 board
 * - TM1638 module (8-digit 7-segment display with 8 LEDs and 8 buttons)
 */

#include <Arduino.h>
#include <esp32_iot.h>

// สร้าง object สำหรับใช้งาน library esp32_iot
esp32_iot board;

// ตัวแปรสำหรับนับเลข
long counter = 0;

void setup() {
  // เริ่มต้น Serial communication ที่ baud rate 115200
  Serial.begin(115200);
  delay(1000);
  
  // เริ่มต้นการทำงานของ esp32_iot library
  board.begin();
  
  // เริ่มต้น TM1638 module
  board.tm1638_begin();
  
  // ล้างหน้าจอ TM1638
  board.tm1638_clear();
  
  // แสดงข้อความเริ่มต้น
  Serial.println("\n=================================");
  Serial.println("โปรแกรมทดสอบ TM1638 Module");
  Serial.println("นับเลข 0-1000 (เพิ่มทีละ 10)");
  Serial.println("=================================\n");
  
  // ตั้งค่าเริ่มต้นของตัวนับ
  counter = 0;
  
  // แสดงค่าเริ่มต้นบนจอ TM1638
  board.tm1638_number(counter);
  Serial.print("แสดงค่า: ");
  Serial.println(counter);
}

void loop() {
    
    // เพิ่มค่าตัวนับทีละ 1
    counter = counter + 1;
    
    // ถ้าเกิน 10000000 ให้เริ่มนับใหม่ที่ 0
    if (counter > 10000000) {
      counter = 0;
      Serial.println("\n--- เริ่มนับใหม่ ---\n");
    }
    
    // แสดงค่าบนจอ TM1638
    board.tm1638_number(counter);
    
    // แสดงค่าผ่าน Serial Monitor
    Serial.print("แสดงค่า: ");
    Serial.print(counter);
    Serial.println();
  
  
    // หน่วงเวลา 0.1 วินาที
    delay(100);
}
