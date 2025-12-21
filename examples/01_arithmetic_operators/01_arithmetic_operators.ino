#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Arithmetic Operators (ตัวดำเนินการทางคณิตศาสตร์)
 * ===================================================================
 * 
 * ตัวดำเนินการทางคณิตศาสตร์ที่ใช้ใน Arduino:
 * + : บวก (Addition)
 * - : ลบ (Subtraction)
 * * : คูณ (Multiplication)
 * / : หาร (Division)
 * % : โมดูลัส (Modulus) - เอาเศษจากการหาร
 * 
 * โค้ดนี้จะแสดงผลการคำนวณทุกๆ 3 วินาที
 * ===================================================================
 */

// ประกาศตัวแปรสำหรับการคำนวณ
int a = 20;
int b = 7;

void setup() {
  // ตั้งค่า Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  delay(1000);  // รอให้ Serial Port พร้อม
  
  // แสดงข้อความเริ่มต้น
  Serial.println("===================================");
  Serial.println("Arithmetic Operators Demo");
  Serial.println("แสดงผลทุกๆ 3 วินาที");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // แสดงค่าตัวแปรที่ใช้คำนวณ
  Serial.print("ค่าที่ใช้: a = ");
  Serial.print(a);
  Serial.print(", b = ");
  Serial.println(b);
  Serial.println();
  
  // ===== การบวก (Addition) =====
  int resultAdd = a + b;
  Serial.print("บวก: ");
  Serial.print(a);
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(resultAdd);
  
  // ===== การลบ (Subtraction) =====
  int resultSub = a - b;
  Serial.print("ลบ:  ");
  Serial.print(a);
  Serial.print(" - ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(resultSub);
  
  // ===== การคูณ (Multiplication) =====
  int resultMul = a * b;
  Serial.print("คูณ: ");
  Serial.print(a);
  Serial.print(" * ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(resultMul);
  
  // ===== การหาร (Division) =====
  int resultDiv = a / b;  // ผลลัพธ์เป็นจำนวนเต็ม
  Serial.print("หาร: ");
  Serial.print(a);
  Serial.print(" / ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(resultDiv);
  
  // ===== การหารแบบทศนิยม =====
  float resultFloat = (float)a / (float)b;  // แปลงเป็น float
  Serial.print("หาร (ทศนิยม): ");
  Serial.print(a);
  Serial.print(" / ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(resultFloat, 2);  // แสดง 2 ตำแหน่งทศนิยม
  
  // ===== โมดูลัส (หาเศษ) =====
  int resultMod = a % b;
  Serial.print("เศษจากการหาร: ");
  Serial.print(a);
  Serial.print(" % ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(resultMod);
  
  Serial.println();
  Serial.println("-----------------------------------");
  Serial.println();
  
  // รอ 3 วินาที ก่อนแสดงผลรอบถัดไป
  delay(3000);
}
