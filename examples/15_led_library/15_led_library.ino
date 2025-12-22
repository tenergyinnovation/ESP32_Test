/*
 * ตัวอย่าง: การควบคุม LED Module ทั้ง 4 ดวงผ่าน library esp32_iot
 * 
 * คำอธิบาย:
 * - โปรแกรมนี้แสดงการใช้งาน library esp32_iot ในการควบคุม LED Module ทั้ง 4 ดวง
 * - LED จะติดดับสลับกันทีละดวงตามลำดับ LED1 -> LED2 -> LED3 -> LED4
 * - ใช้ฟังก์ชัน led1_On(), led1_Off(), led2_On(), led2_Off() ฯลฯ จาก library
 * - LED Module เป็นแบบ Active LOW (ส่งสัญญาณ LOW เพื่อติดไฟ, HIGH เพื่อดับไฟ)
 * - แสดงสถานะการทำงานผ่าน Serial Monitor
 * 
 * พินที่ใช้งาน:
 * - LED1: GPIO 12
 * - LED2: GPIO 4
 * - LED3: GPIO 2
 * - LED4: GPIO 15
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
  Serial.println("โปรแกรมทดสอบ LED Module");
  Serial.println("ผ่าน library esp32_iot");
  Serial.println("=================================");
  Serial.println("LED จะติดดับสลับกันทีละดวง");
  Serial.println("LED1 -> LED2 -> LED3 -> LED4\n");
}

void loop() {
  // ---- ติด LED1 ----
  Serial.println("LED1: ON");    // แสดงสถานะผ่าน Serial
  board.led1_On();               // เปิด LED1 (ส่งสัญญาณ LOW)
  delay(500);                    // หน่วงเวลา 500 มิลลิวินาที
  
  // ดับ LED1
  Serial.println("LED1: OFF");   // แสดงสถานะผ่าน Serial
  board.led1_Off();              // ปิด LED1 (ส่งสัญญาณ HIGH)
  delay(500);                    // หน่วงเวลา 500 มิลลิวินาที
  
  // ---- ติด LED2 ----
  Serial.println("LED2: ON");    // แสดงสถานะผ่าน Serial
  board.led2_On();               // เปิด LED2 (ส่งสัญญาณ LOW)
  delay(500);                    // หน่วงเวลา 500 มิลลิวินาที
  
  // ดับ LED2
  Serial.println("LED2: OFF");   // แสดงสถานะผ่าน Serial
  board.led2_Off();              // ปิด LED2 (ส่งสัญญาณ HIGH)
  delay(500);                    // หน่วงเวลา 500 มิลลิวินาที
  
  // ---- ติด LED3 ----
  Serial.println("LED3: ON");    // แสดงสถานะผ่าน Serial
  board.led3_On();               // เปิด LED3 (ส่งสัญญาณ LOW)
  delay(500);                    // หน่วงเวลา 500 มิลลิวินาที
  
  // ดับ LED3
  Serial.println("LED3: OFF");   // แสดงสถานะผ่าน Serial
  board.led3_Off();              // ปิด LED3 (ส่งสัญญาณ HIGH)
  delay(500);                    // หน่วงเวลา 500 มิลลิวินาที
  
  // ---- ติด LED4 ----
  Serial.println("LED4: ON");    // แสดงสถานะผ่าน Serial
  board.led4_On();               // เปิด LED4 (ส่งสัญญาณ LOW)
  delay(500);                    // หน่วงเวลา 500 มิลลิวินาที
  
  // ดับ LED4
  Serial.println("LED4: OFF");   // แสดงสถานะผ่าน Serial
  board.led4_Off();              // ปิด LED4 (ส่งสัญญาณ HIGH)
  delay(500);                    // หน่วงเวลา 500 มิลลิวินาที
  
  // แสดงข้อความแบ่งรอบ
  Serial.println("---");
  
  // โปรแกรมจะวนกลับไปเริ่มต้นใหม่ที่ LED1
}
