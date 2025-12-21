#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน switch-case Statement
 * ===================================================================
 * 
 * switch-case ใช้เมื่อต้องการเลือกทำงานจากหลายๆ กรณี
 * เหมาะกับการเปรียบเทียบค่าคงที่
 * 
 * ใช้ปุ่ม 4 ปุ่ม (S1-S4) เลือก LED สีต่างๆ
 * ===================================================================
 */

// กำหนดพิน
const int BUTTON_S1 = 32;
const int BUTTON_S2 = 36;
const int BUTTON_S3 = 35;
const int BUTTON_S4 = 34;
const int LED_RED = 4;
const int LED_YELLOW = 12;
const int LED_BLUE = 2;
const int LED_GREEN = 15;

void setup() {
  // ตั้งค่า Serial
  Serial.begin(115200);
  delay(1000);
  
  // ตั้งค่าพินปุ่ม
  pinMode(BUTTON_S1, INPUT);
  pinMode(BUTTON_S2, INPUT);
  pinMode(BUTTON_S3, INPUT);
  pinMode(BUTTON_S4, INPUT);
  
  // ตั้งค่าพิน LED
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("switch-case Demo");
  Serial.println("S1: LED แดง | S2: LED เหลือง");
  Serial.println("S3: LED น้ำเงิน | S4: LED เขียว");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // อ่านค่าปุ่ม (LOW = กด, HIGH = ไม่กด)
  int selectedButton = 0;
  
  if (digitalRead(BUTTON_S1) == LOW) selectedButton = 1;
  else if (digitalRead(BUTTON_S2) == LOW) selectedButton = 2;
  else if (digitalRead(BUTTON_S3) == LOW) selectedButton = 3;
  else if (digitalRead(BUTTON_S4) == LOW) selectedButton = 4;
  
  // ปิด LED ทั้งหมดก่อน
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  
  // ===== switch-case =====
  switch (selectedButton) {
    case 1:
      digitalWrite(LED_RED, HIGH);
      Serial.println("กดปุ่ม S1 -> LED แดง");
      delay(500);
      break;
      
    case 2:
      digitalWrite(LED_YELLOW, HIGH);
      Serial.println("กดปุ่ม S2 -> LED เหลือง");
      delay(500);
      break;
      
    case 3:
      digitalWrite(LED_BLUE, HIGH);
      Serial.println("กดปุ่ม S3 -> LED น้ำเงิน");
      delay(500);
      break;
      
    case 4:
      digitalWrite(LED_GREEN, HIGH);
      Serial.println("กดปุ่ม S4 -> LED เขียว");
      delay(500);
      break;
      
    default:
      // กรณีไม่กดปุ่มใดเลย
      break;
  }
  
  delay(100);
}
