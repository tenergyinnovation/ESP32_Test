/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Comparison Operators (ตัวดำเนินการเปรียบเทียบ)
 * ===================================================================
 * 
 * ตัวดำเนินการเปรียบเทียบที่ใช้ใน Arduino:
 * == : เท่ากับ (Equal to)
 * != : ไม่เท่ากับ (Not equal to)
 * <  : น้อยกว่า (Less than)
 * >  : มากกว่า (Greater than)
 * <= : น้อยกว่าหรือเท่ากับ (Less than or equal to)
 * >= : มากกว่าหรือเท่ากับ (Greater than or equal to)
 * 
 * ผลลัพธ์ของการเปรียบเทียบจะเป็นค่า Boolean (true หรือ false)
 * true = 1, false = 0
 * ===================================================================
 */

// ประกาศตัวแปรสำหรับการเปรียบเทียบ
int x = 15;
int y = 20;
int z = 15;
bool comparisonResult;

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("Comparison Operators Demo");
  Serial.println("===================================");
  Serial.println();
  
  // แสดงค่าตัวแปรเริ่มต้น
  Serial.print("x = ");
  Serial.println(x);
  Serial.print("y = ");
  Serial.println(y);
  Serial.print("z = ");
  Serial.println(z);
  Serial.println();
  
  // ===== ตัวดำเนินการ == (เท่ากับ) =====
  Serial.println("----- Equal to (==) -----");
  comparisonResult = (x == y);
  Serial.print("x == y : ");
  Serial.print(x);
  Serial.print(" == ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  
  comparisonResult = (x == z);
  Serial.print("x == z : ");
  Serial.print(x);
  Serial.print(" == ");
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  Serial.println();
  
  // ===== ตัวดำเนินการ != (ไม่เท่ากับ) =====
  Serial.println("----- Not equal to (!=) -----");
  comparisonResult = (x != y);
  Serial.print("x != y : ");
  Serial.print(x);
  Serial.print(" != ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  
  comparisonResult = (x != z);
  Serial.print("x != z : ");
  Serial.print(x);
  Serial.print(" != ");
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  Serial.println();
  
  // ===== ตัวดำเนินการ < (น้อยกว่า) =====
  Serial.println("----- Less than (<) -----");
  comparisonResult = (x < y);
  Serial.print("x < y : ");
  Serial.print(x);
  Serial.print(" < ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  
  comparisonResult = (y < x);
  Serial.print("y < x : ");
  Serial.print(y);
  Serial.print(" < ");
  Serial.print(x);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  Serial.println();
  
  // ===== ตัวดำเนินการ > (มากกว่า) =====
  Serial.println("----- Greater than (>) -----");
  comparisonResult = (y > x);
  Serial.print("y > x : ");
  Serial.print(y);
  Serial.print(" > ");
  Serial.print(x);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  
  comparisonResult = (x > y);
  Serial.print("x > y : ");
  Serial.print(x);
  Serial.print(" > ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  Serial.println();
  
  // ===== ตัวดำเนินการ <= (น้อยกว่าหรือเท่ากับ) =====
  Serial.println("----- Less than or equal to (<=) -----");
  comparisonResult = (x <= y);
  Serial.print("x <= y : ");
  Serial.print(x);
  Serial.print(" <= ");
  Serial.print(y);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  
  comparisonResult = (x <= z);
  Serial.print("x <= z : ");
  Serial.print(x);
  Serial.print(" <= ");
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  Serial.println();
  
  // ===== ตัวดำเนินการ >= (มากกว่าหรือเท่ากับ) =====
  Serial.println("----- Greater than or equal to (>=) -----");
  comparisonResult = (y >= x);
  Serial.print("y >= x : ");
  Serial.print(y);
  Serial.print(" >= ");
  Serial.print(x);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  
  comparisonResult = (x >= z);
  Serial.print("x >= z : ");
  Serial.print(x);
  Serial.print(" >= ");
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(comparisonResult ? "true" : "false");
  Serial.println();
  
  // ===== ตัวอย่างการใช้งานจริง =====
  Serial.println("===================================");
  Serial.println("ตัวอย่างการใช้งานจริง");
  Serial.println("===================================");
  
  // ตัวอย่าง: ตรวจสอบอุณหภูมิ
  int temperature = 28;
  int minTemp = 20;
  int maxTemp = 30;
  
  Serial.print("อุณหภูมิปัจจุบัน: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("ช่วงอุณหภูมิที่เหมาะสม: ");
  Serial.print(minTemp);
  Serial.print(" - ");
  Serial.print(maxTemp);
  Serial.println(" °C");
  
  if (temperature >= minTemp && temperature <= maxTemp) {
    Serial.println("สถานะ: อุณหภูมิอยู่ในเกณฑ์ปกติ");
  }
  Serial.println();
  
  // ตัวอย่าง: ตรวจสอบคะแนนสอบ
  int examScore = 75;
  int passingScore = 60;
  
  Serial.print("คะแนนสอบ: ");
  Serial.println(examScore);
  Serial.print("คะแนนผ่าน: ");
  Serial.println(passingScore);
  Serial.print("ผลการสอบ: ");
  Serial.println(examScore >= passingScore ? "ผ่าน" : "ไม่ผ่าน");
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
}
