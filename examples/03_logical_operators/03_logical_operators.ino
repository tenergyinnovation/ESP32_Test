#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Logical Operators (ตัวดำเนินการเชิงตรรกะ)
 * ===================================================================
 * 
 * ตัวดำเนินการเชิงตรรกะ:
 * && : AND (และ) - เป็นจริงเมื่อทั้งสองเงื่อนไขเป็นจริง
 * || : OR (หรือ) - เป็นจริงเมื่ออย่างน้อยหนึ่งเงื่อนไขเป็นจริง
 * !  : NOT (ไม่) - กลับค่าความจริง
 * 
 * ตัวอย่างใช้ปุ่มกด S1 (D32) และ S2 (VP/D36) จาก diagram.json
 * ===================================================================
 */

// กำหนดพินสำหรับปุ่มกด (ตาม diagram.json)
const int BUTTON_S1 = 32;  // ปุ่ม S1
const int BUTTON_S2 = 36;  // ปุ่ม S2 (VP)

void setup() {
  // ตั้งค่า Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพินปุ่มกดเป็น INPUT
  pinMode(BUTTON_S1, INPUT);
  pinMode(BUTTON_S2, INPUT);
  
  Serial.println("===================================");
  Serial.println("Logical Operators Demo");
  Serial.println("ใช้ปุ่ม S1(D32) และ S2(VP)");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // อ่านค่าจากปุ่มกด (LOW = กด, HIGH = ไม่กด)
  bool button1 = digitalRead(BUTTON_S1) == LOW;
  bool button2 = digitalRead(BUTTON_S2) == LOW;
  
  // แสดงสถานะปุ่ม
  Serial.print("ปุ่ม S1: ");
  Serial.print(button1 ? "กด" : "ปล่อย");
  Serial.print(" | ปุ่ม S2: ");
  Serial.println(button2 ? "กด" : "ปล่อย");
  Serial.println();
  
  // ===== ตัวดำเนินการ AND (&&) =====
  bool resultAND = button1 && button2;
  Serial.print("S1 && S2 : ");
  Serial.println(resultAND ? "true (กดทั้ง 2 ปุ่ม)" : "false");
  
  // ===== ตัวดำเนินการ OR (||) =====
  bool resultOR = button1 || button2;
  Serial.print("S1 || S2 : ");
  Serial.println(resultOR ? "true (กดอย่างน้อย 1 ปุ่ม)" : "false");
  
  // ===== ตัวดำเนินการ NOT (!) =====
  bool resultNOT1 = !button1;
  Serial.print("!S1      : ");
  Serial.println(resultNOT1 ? "true (ไม่กด S1)" : "false (กด S1)");
  
  Serial.println();
  Serial.println("-----------------------------------");
  Serial.println();
  
  // รอครึ่งวินาที
  delay(500);
}
