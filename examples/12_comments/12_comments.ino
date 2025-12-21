#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Comments (คอมเมนต์)
 * ===================================================================
 * 
 * Comments คือข้อความที่อธิบายโค้ด ไม่มีผลต่อการทำงาน
 * มี 2 แบบ:
 * 1. Single-line comment: // ข้อความในบรรทัดเดียว
 * 2. Multi-line comment: เครื่องหมาย slash-asterisk ข้อความ asterisk-slash
 * 
 * ใช้ปุ่ม S1 เพื่อทดสอบฟังก์ชัน
 * ===================================================================
 */

// กำหนดพิน
const int BUTTON_S1 = 32;
const int LED_GREEN = 15;

// ค่าคงที่ PI สำหรับคำนวณพื้นที่วงกลม
const float PI_VALUE = 3.14159f;

// Function Prototype
float calculateCircleArea(float radius);

void setup() {
  // ตั้งค่า Serial
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน
  pinMode(BUTTON_S1, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("Comments Demo");
  Serial.println("กดปุ่ม S1 เพื่อคำนวณพื้นที่วงกลม");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // ตรวจสอบปุ่ม S1
  if (digitalRead(BUTTON_S1) == HIGH) {
    Serial.println("--- คำนวณพื้นที่วงกลม ---");
    
    // คำนวณพื้นที่วงกลมรัศมี 5
    float radius = 5.0f;
    float area = calculateCircleArea(radius);
    
    // แสดงผลลัพธ์
    Serial.print("รัศมี: ");
    Serial.println(radius);
    Serial.print("พื้นที่: ");
    Serial.println(area);
    
    // กระพริบ LED สีเขียว
    digitalWrite(LED_GREEN, HIGH);
    delay(500);
    digitalWrite(LED_GREEN, LOW);
    
    Serial.println();
    delay(1000);
  }
  
  delay(100);
}

// ฟังก์ชันคำนวณพื้นที่วงกลม
float calculateCircleArea(float radius) {
  return PI_VALUE * radius * radius;
}
