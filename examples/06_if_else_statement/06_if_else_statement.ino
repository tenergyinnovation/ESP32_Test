#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน if-else Statement
 * ===================================================================
 * 
 * if-else มี 2 ทางเลือก:
 * - ถ้าเงื่อนไขเป็นจริง ทำใน if { }
 * - ถ้าเงื่อนไขเป็นเท็จ ทำใน else { }
 * 
 * ใช้ปุ่ม S4 (D34) ควบคุม LED Yellow (D12)
 * ===================================================================
 */

// กำหนดพิน (ตาม diagram.json)
const int BUTTON_S4 = 34;     // ปุ่ม S4
const int LED_YELLOW = 12;    // LED สีเหลือง

void setup() {
  // ตั้งค่า Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน
  pinMode(BUTTON_S4, INPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("if-else Statement Demo");
  Serial.println("กดปุ่ม S4 เพื่อสลับ LED Yellow");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // อ่านค่าปุ่ม S4 (LOW = กด, HIGH = ไม่กด)
  bool buttonPressed = digitalRead(BUTTON_S4) == LOW;
  
  // แสดงสถานะ
  Serial.print("ปุ่ม S4: ");
  
  // ===== if-else statement =====
  if (buttonPressed) {
    // กรณีกดปุ่ม
    digitalWrite(LED_YELLOW, HIGH);
    Serial.println("กด -> LED เปิด");
  } else {
    // กรณีไม่กดปุ่ม
    digitalWrite(LED_YELLOW, LOW);
    Serial.println("ปล่อย -> LED ปิด");
  }
  
  // รอครึ่งวินาที
  delay(500);
}
