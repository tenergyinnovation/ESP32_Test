#include <Arduino.h>

/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Comparison Operators (ตัวดำเนินการเปรียบเทียบ)
 * ===================================================================
 * 
 * ตัวดำเนินการเปรียบเทียบ:
 * == : เท่ากับ
 * != : ไม่เท่ากับ
 * <  : น้อยกว่า
 * >  : มากกว่า
 * <= : น้อยกว่าหรือเท่ากับ
 * >= : มากกว่าหรือเท่ากับ
 * 
 * ผลลัพธ์จะเป็น true (1) หรือ false (0)
 * ===================================================================
 */

// ตัวแปรสำหรับเปรียบเทียบ
int x = 15;
int y = 20;

void setup() {
  // ตั้งค่า Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("Comparison Operators Demo");
  Serial.println("แสดงผลทุกๆ 3 วินาที");
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // แสดงค่าที่ใช้เปรียบเทียบ
  Serial.print("ค่าที่ใช้: x = ");
  Serial.print(x);
  Serial.print(", y = ");
  Serial.println(y);
  Serial.println();
  
  // ===== เท่ากับ (==) =====
  bool result1 = (x == y);
  Serial.print("x == y : ");
  Serial.print(x);
  Serial.print(" == ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(result1 ? "true" : "false");
  
  // ===== ไม่เท่ากับ (!=) =====
  bool result2 = (x != y);
  Serial.print("x != y : ");
  Serial.print(x);
  Serial.print(" != ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(result2 ? "true" : "false");
  
  // ===== น้อยกว่า (<) =====
  bool result3 = (x < y);
  Serial.print("x < y  : ");
  Serial.print(x);
  Serial.print(" < ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(result3 ? "true" : "false");
  
  // ===== มากกว่า (>) =====
  bool result4 = (x > y);
  Serial.print("x > y  : ");
  Serial.print(x);
  Serial.print(" > ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(result4 ? "true" : "false");
  
  // ===== น้อยกว่าหรือเท่ากับ (<=) =====
  bool result5 = (x <= y);
  Serial.print("x <= y : ");
  Serial.print(x);
  Serial.print(" <= ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(result5 ? "true" : "false");
  
  // ===== มากกว่าหรือเท่ากับ (>=) =====
  bool result6 = (x >= y);
  Serial.print("x >= y : ");
  Serial.print(x);
  Serial.print(" >= ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(result6 ? "true" : "false");
  
  Serial.println();
  Serial.println("-----------------------------------");
  Serial.println();
  
  // รอ 3 วินาที
  delay(3000);
}
