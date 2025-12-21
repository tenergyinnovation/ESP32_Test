#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการสร้าง Function และ Return Value
 * ===================================================================
 * 
 * Function (ฟังก์ชัน) คือ บล็อกโค้ดที่ทำงานเฉพาะอย่าง
 * ช่วยให้โค้ดเป็นระเบียบและใช้ซ้ำได้
 * 
 * ใช้ปุ่ม S1 และ S2 เรียกใช้ฟังก์ชันต่างๆ
 * ===================================================================
 */

// กำหนดพิน (ตาม diagram.json)
const int BUTTON_S1 = 32;
const int BUTTON_S2 = 36;
const int LED_RED = 4;
const int LED_YELLOW = 12;

// ===== Function Prototypes (ต้นแบบฟังก์ชัน) =====
void blinkLed(int pin, int times);
int addNumbers(int a, int b);
float calculateCircleArea(float radius);
void printValue(int value);
void printValue(float value);

void setup() {
  // ตั้งค่า Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพิน
  pinMode(BUTTON_S1, INPUT);
  pinMode(BUTTON_S2, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("Functions Demo");
  Serial.println("S1: เรียกใช้ blinkLed และ addNumbers");
  Serial.println("S2: เรียกใช้ calculateCircleArea");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // อ่านค่าปุ่ม
  bool btn1 = digitalRead(BUTTON_S1);
  bool btn2 = digitalRead(BUTTON_S2);
  
  // ===== เมื่อกดปุ่ม S1 =====
  if (btn1 == HIGH) {
    Serial.println("--- กดปุ่ม S1 ---");
    
    // เรียกใช้ฟังก์ชันกระพริบ LED
    Serial.println("เรียก blinkLed(LED_RED, 3)");
    blinkLed(LED_RED, 3);
    
    // เรียกใช้ฟังก์ชันบวกเลข
    int sum = addNumbers(15, 25);
    Serial.print("15 + 25 = ");
    Serial.println(sum);
    
    Serial.println();
    delay(1000);
  }
  
  // ===== เมื่อกดปุ่ม S2 =====
  if (btn2 == HIGH) {
    Serial.println("--- กดปุ่ม S2 ---");
    
    // เรียกใช้ฟังก์ชันคำนวณพื้นที่วงกลม
    float area = calculateCircleArea(5.0f);
    Serial.print("พื้นที่วงกลม รัศมี 5 = ");
    Serial.println(area);
    
    // ทดสอบ Function Overloading
    Serial.println("ทดสอบ printValue:");
    printValue(42);
    printValue(3.14f);
    
    Serial.println();
    delay(1000);
  }
  
  delay(100);
}

// ===== ฟังก์ชันกระพริบ LED =====
void blinkLed(int pin, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(200);
    digitalWrite(pin, LOW);
    delay(200);
  }
}

// ===== ฟังก์ชันบวกเลข (มี return) =====
int addNumbers(int a, int b) {
  return a + b;
}

// ===== ฟังก์ชันคำนวณพื้นที่วงกลม =====
float calculateCircleArea(float radius) {
  float pi = 3.14159f;
  return pi * radius * radius;
}

// ===== Function Overloading (ชื่อเดียวกัน แต่ parameter ต่างกัน) =====
void printValue(int value) {
  Serial.print("Integer: ");
  Serial.println(value);
}

void printValue(float value) {
  Serial.print("Float: ");
  Serial.println(value);
}
