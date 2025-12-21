/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Functions (ฟังก์ชัน)
 * ===================================================================
 * 
 * Function คือกลุ่มของคำสั่งที่รวมกันเพื่อทำงานเฉพาะอย่าง
 * ช่วยให้:
 * - โค้ดอ่านง่ายและเป็นระเบียบ
 * - ลดการเขียนโค้ดซ้ำ (Reusability)
 * - แก้ไขและดูแลรักษาได้ง่าย
 * - แบ่งโปรแกรมใหญ่เป็นส่วนเล็กๆ
 * 
 * ประเภทของ Function:
 * 1. Function ที่ไม่มี parameter และไม่ return ค่า (void)
 * 2. Function ที่มี parameter แต่ไม่ return ค่า (void)
 * 3. Function ที่ไม่มี parameter แต่ return ค่า
 * 4. Function ที่มี parameter และ return ค่า
 * 
 * รูปแบบ:
 * returnType functionName(parameter1, parameter2, ...) {
 *   // code
 *   return value; // ถ้า returnType ไม่ใช่ void
 * }
 * ===================================================================
 */

// ===================================================================
// ประกาศ Function (Function Declaration/Prototype)
// ต้องประกาศก่อนใช้งาน หรือวางโค้ดก่อน setup()
// ===================================================================

// 1. Function ไม่มี parameter ไม่ return ค่า
void sayHello();

// 2. Function มี parameter ไม่ return ค่า
void printNumber(int num);
void printSum(int a, int b);

// 3. Function ไม่มี parameter แต่ return ค่า
int getRandomNumber();
float getPi();

// 4. Function มี parameter และ return ค่า
int add(int x, int y);
float calculateAverage(int arr[], int size);
bool isEven(int num);

// 5. Function ที่ซับซ้อนขึ้น
float celsiusToFahrenheit(float celsius);
int factorial(int n);
String getGrade(int score);

void setup() {
  // เริ่มต้น Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("Functions Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== ตัวอย่าง 1: Function ไม่มี parameter ไม่ return ค่า =====
  Serial.println("----- ตัวอย่าง 1: Function แบบง่าย (void) -----");
  sayHello();  // เรียกใช้ฟังก์ชัน
  sayHello();  // เรียกได้หลายครั้ง
  Serial.println();
  
  // ===== ตัวอย่าง 2: Function มี parameter =====
  Serial.println("----- ตัวอย่าง 2: Function มี parameter -----");
  printNumber(42);
  printNumber(100);
  printSum(15, 25);
  printSum(7, 13);
  Serial.println();
  
  // ===== ตัวอย่าง 3: Function return ค่า =====
  Serial.println("----- ตัวอย่าง 3: Function return ค่า -----");
  
  int randomNum = getRandomNumber();
  Serial.print("เลขสุ่ม: ");
  Serial.println(randomNum);
  
  float pi = getPi();
  Serial.print("ค่า PI: ");
  Serial.println(pi, 5);
  Serial.println();
  
  // ===== ตัวอย่าง 4: Function คำนวณ =====
  Serial.println("----- ตัวอย่าง 4: Function คำนวณ -----");
  
  int result = add(10, 20);
  Serial.print("10 + 20 = ");
  Serial.println(result);
  
  // ใช้ผลลัพธ์ของ function ได้ทันที
  Serial.print("5 + 15 = ");
  Serial.println(add(5, 15));
  Serial.println();
  
  // ===== ตัวอย่าง 5: Function กับอาร์เรย์ =====
  Serial.println("----- ตัวอย่าง 5: Function คำนวณค่าเฉลี่ย -----");
  
  int scores[] = {85, 92, 78, 90, 88};
  int arraySize = 5;
  
  Serial.print("คะแนน: ");
  for (int i = 0; i < arraySize; i++) {
    Serial.print(scores[i]);
    if (i < arraySize - 1) Serial.print(", ");
  }
  Serial.println();
  
  float avg = calculateAverage(scores, arraySize);
  Serial.print("ค่าเฉลี่ย: ");
  Serial.println(avg, 2);
  Serial.println();
  
  // ===== ตัวอย่าง 6: Function return boolean =====
  Serial.println("----- ตัวอย่าง 6: Function return boolean -----");
  
  for (int i = 1; i <= 10; i++) {
    Serial.print(i);
    Serial.print(" เป็นเลข");
    Serial.println(isEven(i) ? "คู่" : "คี่");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 7: Function แปลงหน่วย =====
  Serial.println("----- ตัวอย่าง 7: แปลงอุณหภูมิ -----");
  
  float tempC[] = {0, 25, 37, 100};
  for (int i = 0; i < 4; i++) {
    float tempF = celsiusToFahrenheit(tempC[i]);
    Serial.print(tempC[i], 0);
    Serial.print(" °C = ");
    Serial.print(tempF, 1);
    Serial.println(" °F");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 8: Function แบบ Recursive =====
  Serial.println("----- ตัวอย่าง 8: Factorial (Recursive) -----");
  
  for (int i = 0; i <= 10; i++) {
    Serial.print(i);
    Serial.print("! = ");
    Serial.println(factorial(i));
  }
  Serial.println();
  
  // ===== ตัวอย่าง 9: Function return String =====
  Serial.println("----- ตัวอย่าง 9: Function return String -----");
  
  int testScores[] = {95, 75, 62, 48, 88};
  for (int i = 0; i < 5; i++) {
    Serial.print("คะแนน ");
    Serial.print(testScores[i]);
    Serial.print(" = เกรด ");
    Serial.println(getGrade(testScores[i]));
  }
  Serial.println();
  
  // ===== ตัวอย่าง 10: Function ซ้อน Function =====
  Serial.println("----- ตัวอย่าง 10: Function ซ้อน Function -----");
  
  int radius = 5;
  float circleArea = calculateCircleArea(radius);
  Serial.print("พื้นที่วงกลม (รัศมี ");
  Serial.print(radius);
  Serial.print("): ");
  Serial.println(circleArea, 2);
  
  float cylinderVol = calculateCylinderVolume(radius, 10);
  Serial.print("ปริมาตรทรงกระบอก (รัศมี ");
  Serial.print(radius);
  Serial.print(", สูง 10): ");
  Serial.println(cylinderVol, 2);
  Serial.println();
  
  // ===== ตัวอย่าง 11: Function กับตัวแปร Local =====
  Serial.println("----- ตัวอย่าง 11: Local Variables -----");
  demonstrateLocalVariables();
  Serial.println();
  
  // ===== ตัวอย่าง 12: Function Overloading (ไม่รองรับโดยตรงใน C) =====
  Serial.println("----- ตัวอย่าง 12: ฟังก์ชันหลายรูปแบบ -----");
  printValue(42);           // int version
  printValue(3.14);         // float version
  printValue("Hello");      // String version
  Serial.println();
  
  // ===== ตัวอย่าง 13: การใช้ Function ในชีวิตจริง =====
  Serial.println("----- ตัวอย่าง 13: ตัวอย่างการใช้งานจริง -----");
  
  // จำลองการอ่านเซ็นเซอร์อุณหภูมิ
  float temperature = readTemperature();
  Serial.print("อุณหภูมิ: ");
  Serial.print(temperature, 1);
  Serial.println(" °C");
  
  // ตรวจสอบและแสดงสถานะ
  if (isTemperatureNormal(temperature)) {
    Serial.println("✅ อุณหภูมิปกติ");
  } else {
    Serial.println("⚠️ อุณหภูมิผิดปกติ");
    sendAlert(temperature);
  }
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
  Serial.println();
  
  // สรุป
  Serial.println("สรุป:");
  Serial.println("- Function ช่วยจัดระเบียบโค้ดและลดการเขียนซ้ำ");
  Serial.println("- Parameter คือค่าที่ส่งเข้าฟังก์ชัน");
  Serial.println("- Return value คือค่าที่ฟังก์ชันส่งออกมา");
  Serial.println("- void หมายถึงไม่ return ค่า");
  Serial.println("- ตั้งชื่อฟังก์ชันให้สื่อความหมาย");
}

void loop() {
  // ไม่มีการทำงานใน loop() ในตัวอย่างนี้
}

// ===================================================================
// คำจำกัดความของ Function (Function Definition)
// ===================================================================

// 1. Function ไม่มี parameter ไม่ return ค่า
void sayHello() {
  Serial.println("สวัสดี! Hello from function!");
}

// 2. Function มี parameter ไม่ return ค่า
void printNumber(int num) {
  Serial.print("ตัวเลข: ");
  Serial.println(num);
}

void printSum(int a, int b) {
  int sum = a + b;
  Serial.print(a);
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(sum);
}

// 3. Function return ค่า
int getRandomNumber() {
  return random(1, 101);  // สุ่มเลข 1-100
}

float getPi() {
  return 3.14159;
}

// 4. Function คำนวณ
int add(int x, int y) {
  return x + y;
}

float calculateAverage(int arr[], int size) {
  float sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum / size;
}

bool isEven(int num) {
  return (num % 2 == 0);
}

// 5. Function แปลงหน่วย
float celsiusToFahrenheit(float celsius) {
  return (celsius * 9.0 / 5.0) + 32.0;
}

// 6. Function แบบ Recursive
int factorial(int n) {
  if (n <= 1) {
    return 1;
  }
  return n * factorial(n - 1);
}

// 7. Function return String
String getGrade(int score) {
  if (score >= 80) return "A";
  else if (score >= 70) return "B";
  else if (score >= 60) return "C";
  else if (score >= 50) return "D";
  else return "F";
}

// 8. Function คำนวณพื้นที่วงกลม
float calculateCircleArea(int radius) {
  float pi = getPi();  // เรียกใช้ฟังก์ชันอื่น
  return pi * radius * radius;
}

// 9. Function คำนวณปริมาตรทรงกระบอก (ใช้ฟังก์ชันอื่น)
float calculateCylinderVolume(int radius, int height) {
  float baseArea = calculateCircleArea(radius);  // เรียกใช้ฟังก์ชันอื่น
  return baseArea * height;
}

// 10. Function แสดงตัวแปร Local
void demonstrateLocalVariables() {
  int localVar = 100;  // ตัวแปร Local ใช้ได้เฉพาะในฟังก์ชันนี้
  Serial.print("ตัวแปร Local ในฟังก์ชัน: ");
  Serial.println(localVar);
  Serial.println("(ตัวแปรนี้ใช้ได้เฉพาะในฟังก์ชันนี้เท่านั้น)");
}

// 11. Function หลายรูปแบบ (ใช้ชื่อต่างกัน)
void printValue(int value) {
  Serial.print("Integer: ");
  Serial.println(value);
}

void printValue(float value) {
  Serial.print("Float: ");
  Serial.println(value, 2);
}

void printValue(String value) {
  Serial.print("String: ");
  Serial.println(value);
}

// 12. ตัวอย่างการใช้งานจริง - อ่านเซ็นเซอร์
float readTemperature() {
  // จำลองการอ่านค่าอุณหภูมิจากเซ็นเซอร์
  return 25.0 + random(-50, 150) / 10.0;  // สุ่มอุณหภูมิ 20-40 องศา
}

// 13. ตรวจสอบอุณหภูมิปกติ
bool isTemperatureNormal(float temp) {
  return (temp >= 20.0 && temp <= 30.0);
}

// 14. ส่งการแจ้งเตือน
void sendAlert(float temp) {
  Serial.println("━━━━━━━━━━━━━━━━━━━━");
  Serial.println("⚠️  แจ้งเตือน!");
  Serial.print("อุณหภูมิ ");
  Serial.print(temp, 1);
  Serial.println(" °C");
  
  if (temp < 20.0) {
    Serial.println("→ อุณหภูมิต่ำเกินไป");
  } else {
    Serial.println("→ อุณหภูมิสูงเกินไป");
  }
  Serial.println("━━━━━━━━━━━━━━━━━━━━");
}

// ===================================================================
// Tips สำหรับการเขียน Function:
// 1. ตั้งชื่อให้สื่อความหมาย (calculateSum, readSensor, turnOnLED)
// 2. Function ควรทำงานเดียว (Single Responsibility)
// 3. ใช้ parameter แทนการใช้ตัวแปร global
// 4. เขียน comment อธิบาย parameter และ return value
// 5. ทดสอบ function แยกจากโค้ดหลัก
// ===================================================================
