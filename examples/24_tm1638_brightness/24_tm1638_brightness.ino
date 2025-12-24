/*
 * ตัวอย่างโปรแกรม: TM1638 Module - ควบคุมความสว่างด้วยปุ่มกด
 * -------------------------------------------------
 * โปรแกรมนี้แสดงการควบคุมความสว่างของจอ TM1638
 * โดยใช้ปุ่ม S1-S8 ควบคุมความสว่าง 8 ระดับ (0-7)
 * แสดงตัวเลข "88888888" บนจอตลอดเวลาเพื่อทดสอบความสว่าง
 * 
 * Hardware:
 * - ESP32 Tiny32 board
 * - TM1638 module (8-digit 7-segment display with 8 LEDs and 8 buttons)
 * 
 * ปุ่มควบคุม:
 * - S1 = ความสว่างระดับ 0 (มืดที่สุด)
 * - S2 = ความสว่างระดับ 1
 * - S3 = ความสว่างระดับ 2
 * - S4 = ความสว่างระดับ 3
 * - S5 = ความสว่างระดับ 4
 * - S6 = ความสว่างระดับ 5
 * - S7 = ความสว่างระดับ 6
 * - S8 = ความสว่างระดับ 7 (สว่างที่สุด)
 */

#include <Arduino.h>
#include <esp32_iot.h>

// สร้าง object สำหรับใช้งาน library esp32_iot
esp32_iot board;

// ตัวแปรสำหรับเก็บระดับความสว่างปัจจุบัน
uint8_t currentBrightness = 7;  // เริ่มต้นที่ความสว่างสูงสุด

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
  
  // ตั้งค่าความสว่างเริ่มต้น
  board.tm1638_setBrightness(currentBrightness);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("\n=================================");
  Serial.println("โปรแกรมทดสอบ TM1638 Module");
  Serial.println("ควบคุมความสว่างด้วยปุ่ม S1-S8");
  Serial.println("=================================");
  Serial.println("📌 ปุ่มควบคุมความสว่าง:");
  Serial.println("   S1 = ระดับ 0 (มืดที่สุด)");
  Serial.println("   S2 = ระดับ 1");
  Serial.println("   S3 = ระดับ 2");
  Serial.println("   S4 = ระดับ 3");
  Serial.println("   S5 = ระดับ 4");
  Serial.println("   S6 = ระดับ 5");
  Serial.println("   S7 = ระดับ 6");
  Serial.println("   S8 = ระดับ 7 (สว่างที่สุด)");
  Serial.println("=================================\n");
  
  Serial.print("ความสว่างเริ่มต้น: ");
  Serial.print(currentBrightness);
  Serial.println(" (ระดับ 7)\n");
  
  // แสดงตัวเลข 88888888 บนจอ TM1638
  board.tm1638_number(88888888);
}

void loop() {
  // อ่านค่าปุ่มกดจาก TM1638
  // คืนค่า 0 = ไม่มีการกด, 1-8 = ปุ่มที่ถูกกด (S1-S8)
  uint8_t button = board.tm1638_button();
  
  // ตรวจสอบว่ามีการกดปุ่มหรือไม่
  if (button != 0) {
    // ตรวจสอบว่าเป็นการกดปุ่มใหม่หรือไม่ (เพื่อไม่ให้ตั้งค่าซ้ำ)
    if (button != lastButton) {
      // คำนวณระดับความสว่างจากปุ่มที่กด (S1=0, S2=1, ..., S8=7)
      currentBrightness = button - 1;
      
      // ตั้งค่าความสว่างของ TM1638
      board.tm1638_setBrightness(currentBrightness);
      
      // แสดงข้อความเมื่อเปลี่ยนความสว่าง
      Serial.println("─────────────────────────────────");
      Serial.print("🔘 กดปุ่ม S");
      Serial.print(button);
      Serial.println();
      Serial.print("💡 ตั้งความสว่าง: ระดับ ");
      Serial.print(currentBrightness);
      Serial.print(" (");
      
      // แสดงคำอธิบายระดับความสว่าง
      if (currentBrightness == 0) {
        Serial.print("มืดที่สุด");
      } else if (currentBrightness == 7) {
        Serial.print("สว่างที่สุด");
      } else {
        Serial.print("ปานกลาง");
      }
      Serial.println(")");
      
      // เปิด LED ตามปุ่มที่กด
      for (int i = 1; i <= 8; i++) {
        board.tm1638_led(i, false);
      }
      board.tm1638_led(button, true);
      
      Serial.println("─────────────────────────────────\n");
      
      // บันทึกสถานะปุ่มปัจจุบัน
      lastButton = button;
      
      // แสดงตัวเลข 88888888 บนจอ TM1638 อีกครั้ง
      board.tm1638_number(88888888);
    }
  } else {
    // ถ้าไม่มีการกดปุ่ม (ปล่อยปุ่ม) ให้รีเซ็ตสถานะ
    if (lastButton != 0) {
      lastButton = 0;
    }
  }
  
  // หน่วงเวลาเล็กน้อยเพื่อไม่ให้อ่านค่าบ่อยเกินไป
  delay(50);
}
