/*
 * ตัวอย่างโปรแกรม: TM1638 Module - อ่านค่าปุ่มกด
 * -------------------------------------------------
 * โปรแกรมนี้แสดงการอ่านค่าปุ่มกดทั้ง 8 ปุ่มบน TM1638 module
 * ผ่านไลบรารี esp32_iot และแสดงผลสถานะการกดปุ่มผ่าน Serial Monitor
 * พร้อมกับเปิด LED ตามปุ่มที่กดด้วย
 * 
 * Hardware:
 * - ESP32 Tiny32 board
 * - TM1638 module (8-digit 7-segment display with 8 LEDs and 8 buttons)
 * 
 * ปุ่มบน TM1638:
 * - S1, S2, S3, S4, S5, S6, S7, S8 (ปุ่มกดทั้ง 8 ปุ่ม)
 */

#include <Arduino.h>
#include <esp32_iot.h>

// สร้าง object สำหรับใช้งาน library esp32_iot
esp32_iot board;

// ตัวแปรสำหรับเก็บสถานะปุ่มก่อนหน้า
uint8_t lastButton = 0;

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
  
  // ปิด LED ทั้งหมดก่อนเริ่มต้น
  for (int i = 1; i <= 8; i++) {
    board.tm1638_led(i, false);
  }
  
  // แสดงข้อความเริ่มต้น
  Serial.println("\n=================================");
  Serial.println("โปรแกรมทดสอบ TM1638 Module");
  Serial.println("อ่านค่าปุ่มกด S1 - S8");
  Serial.println("=================================");
  Serial.println("กดปุ่มบนบอร์ด TM1638 เพื่อทดสอบ");
  Serial.println("=================================\n");
  
  // แสดงคำแนะนำ
  Serial.println("📌 ปุ่มที่สามารถกดได้:");
  Serial.println("   S1, S2, S3, S4, S5, S6, S7, S8");
  Serial.println("   LED จะติดตามปุ่มที่กด\n");
}

void loop() {
  // อ่านค่าปุ่มกดจาก TM1638
  // คืนค่า 0 = ไม่มีการกด, 1-8 = ปุ่มที่ถูกกด (S1-S8)
  uint8_t button = board.tm1638_button();
  
  // ตรวจสอบว่ามีการกดปุ่มหรือไม่
  if (button != 0) {
    // ตรวจสอบว่าเป็นการกดปุ่มใหม่หรือไม่ (เพื่อไม่ให้แสดงซ้ำ)
    if (button != lastButton) {
      // แสดงข้อความเมื่อกดปุ่ม
      Serial.println("─────────────────────────────────");
      Serial.print("🔘 กดปุ่ม S");
      Serial.print(button);
      Serial.println();
      
      // ปิด LED ทั้งหมดก่อน
      for (int i = 1; i <= 8; i++) {
        board.tm1638_led(i, false);
      }
      
      // เปิด LED ตามปุ่มที่กด
      board.tm1638_led(button, true);
      Serial.print("💡 LED ");
      Serial.print(button);
      Serial.println(" เปิด");
      
      // แสดงตัวเลขบนจอ 7-segment
      board.tm1638_number(button);
      
      Serial.println("─────────────────────────────────\n");
      
      // บันทึกสถานะปุ่มปัจจุบัน
      lastButton = button;
    }
  } else {
    // ถ้าไม่มีการกดปุ่ม (ปล่อยปุ่ม) ให้รีเซ็ตสถานะ
    if (lastButton != 0) {
      Serial.println("✋ ปล่อยปุ่มแล้ว\n");
      lastButton = 0;
      
      // ปิด LED ทั้งหมด
      for (int i = 1; i <= 8; i++) {
        board.tm1638_led(i, false);
      }
    }
  }
  
  // หน่วงเวลาเล็กน้อยเพื่อไม่ให้อ่านค่าบ่อยเกินไป
  delay(50);
}
