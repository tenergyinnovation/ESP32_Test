/*
 * ตัวอย่างโปรแกรม: TM1638 Module - LED วิ่งซ้าย-ขวา
 * -------------------------------------------------
 * โปรแกรมนี้แสดงการใช้งาน LED บน TM1638 module ผ่านไลบรารี esp32_iot
 * โดยให้ LED ทั้ง 8 ดวงวิ่งจากซ้ายไปขวา และจากขวาไปซ้าย สลับกันไปมา
 * หน่วงเวลา 200 มิลลิวินาที ระหว่างการเปลี่ยนสถานะของ LED แต่ละดวง
 * 
 * Hardware:
 * - ESP32 Tiny32 board
 * - TM1638 module (8-digit 7-segment display with 8 LEDs and 8 buttons)
 * 
 * LED บน TM1638:
 * - LED1 (ซ้ายสุด) ถึง LED8 (ขวาสุด)
 */

#include <Arduino.h>
#include <esp32_iot.h>

// สร้าง object สำหรับใช้งาน library esp32_iot
esp32_iot board;

// ตัวแปรสำหรับจัดการ LED
int currentLED = 1;        // LED ปัจจุบันที่กำลังติด (1-8)
bool goingRight = true;    // ทิศทางการวิ่ง: true=ซ้ายไปขวา, false=ขวาไปซ้าย

void setup() {
  // เริ่มต้น Serial communication ที่ baud rate 115200
  Serial.begin(115200);
  delay(1000);
  
  // เริ่มต้นการทำงานของ esp32_iot library
  board.begin();
  
  // เริ่มต้น TM1638 module
  board.tm1638_begin();
  
  // ปิด LED ทั้งหมดก่อนเริ่มต้น
  for (int i = 1; i <= 8; i++) {
    board.tm1638_led(i, false);
  }
  
  // แสดงข้อความเริ่มต้น
  Serial.println("\n=================================");
  Serial.println("โปรแกรมทดสอบ TM1638 Module");
  Serial.println("LED วิ่งซ้าย-ขวา (Running LED)");
  Serial.println("=================================\n");
  
  // ตั้งค่าเริ่มต้น
  currentLED = 1;
  goingRight = true;
  
  // เปิด LED ดวงแรก
  board.tm1638_led(currentLED, true);
  Serial.print("LED ");
  Serial.print(currentLED);
  Serial.println(" เปิด");
}

void loop() {
  // ปิด LED ดวงปัจจุบัน
  board.tm1638_led(currentLED, false);
  
  // เลื่อนไปยัง LED ดวงถัดไป ตามทิศทางการวิ่ง
  if (goingRight) {
    // วิ่งจากซ้ายไปขวา
    currentLED++;
    
    // ถ้าถึงดวงขวาสุด (LED 8) ให้เปลี่ยนทิศทาง
    if (currentLED > 8) {
      currentLED = 8;
      goingRight = false;  // เปลี่ยนทิศทางเป็นขวาไปซ้าย
      Serial.println("--- เปลี่ยนทิศทาง: ขวาไปซ้าย ---");
    }
  } else {
    // วิ่งจากขวาไปซ้าย
    currentLED--;
    
    // ถ้าถึงดวงซ้ายสุด (LED 1) ให้เปลี่ยนทิศทาง
    if (currentLED < 1) {
      currentLED = 1;
      goingRight = true;   // เปลี่ยนทิศทางเป็นซ้ายไปขวา
      Serial.println("--- เปลี่ยนทิศทาง: ซ้ายไปขวา ---");
    }
  }
  
  // เปิด LED ดวงใหม่
  board.tm1638_led(currentLED, true);
  
  // แสดงสถานะผ่าน Serial Monitor
  Serial.print("LED ");
  Serial.print(currentLED);
  Serial.print(" เปิด (ทิศทาง: ");
  Serial.print(goingRight ? "ซ้าย→ขวา" : "ขวา→ซ้าย");
  Serial.println(")");
  
  // หน่วงเวลา 200 มิลลิวินาที ก่อนเปลี่ยนไปยัง LED ดวงถัดไป
  delay(200);
}
