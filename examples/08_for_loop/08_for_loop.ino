/*
 * ===================================================================
 * ตัวอย่างการใช้งาน for Loop
 * ===================================================================
 * 
 * for loop ใช้สำหรับทำซ้ำคำสั่งจำนวนครั้งที่กำหนด
 * 
 * รูปแบบ:
 * for (initialization; condition; increment) {
 *   // code to repeat
 * }
 * 
 * - initialization: กำหนดค่าเริ่มต้นของตัวแปร (ทำครั้งเดียวตอนเริ่มต้น)
 * - condition: เงื่อนไขในการทำซ้ำ (ถ้าเป็น true จะทำต่อ)
 * - increment: เปลี่ยนค่าตัวแปรหลังจากทำซ้ำแต่ละรอบ
 * ===================================================================
 */

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("for Loop Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== ตัวอย่าง 1: นับเลข 1-10 =====
  Serial.println("----- ตัวอย่าง 1: นับเลข 1-10 -----");
  for (int i = 1; i <= 10; i++) {
    Serial.print("รอบที่ ");
    Serial.print(i);
    Serial.print(": i = ");
    Serial.println(i);
  }
  Serial.println();
  
  // ===== ตัวอย่าง 2: นับถอยหลัง =====
  Serial.println("----- ตัวอย่าง 2: นับถอยหลัง 10-1 -----");
  for (int i = 10; i >= 1; i--) {
    Serial.print("Count down: ");
    Serial.println(i);
  }
  Serial.println("🚀 Launch!");
  Serial.println();
  
  // ===== ตัวอย่าง 3: นับเลขคู่ =====
  Serial.println("----- ตัวอย่าง 3: แสดงเลขคู่ 0-20 -----");
  for (int i = 0; i <= 20; i += 2) {  // เพิ่มทีละ 2
    Serial.print(i);
    if (i < 20) Serial.print(", ");
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 4: นับเลขคี่ =====
  Serial.println("----- ตัวอย่าง 4: แสดงเลขคี่ 1-19 -----");
  for (int i = 1; i < 20; i += 2) {  // เริ่มที่ 1 เพิ่มทีละ 2
    Serial.print(i);
    if (i < 19) Serial.print(", ");
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 5: สร้างตารางสูตรคูณ =====
  Serial.println("----- ตัวอย่าง 5: ตารางสูตรคูณแม่ 5 -----");
  int multiplyBy = 5;
  for (int i = 1; i <= 12; i++) {
    int result = multiplyBy * i;
    Serial.print(multiplyBy);
    Serial.print(" x ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(result);
  }
  Serial.println();
  
  // ===== ตัวอย่าง 6: คำนวณผลรวม =====
  Serial.println("----- ตัวอย่าง 6: คำนวณผลรวม 1+2+...+100 -----");
  int sum = 0;
  for (int i = 1; i <= 100; i++) {
    sum += i;  // เทียบเท่ากับ sum = sum + i
  }
  Serial.print("ผลรวม 1 ถึง 100 = ");
  Serial.println(sum);
  Serial.println();
  
  // ===== ตัวอย่าง 7: คำนวณแฟกทอเรียล =====
  Serial.println("----- ตัวอย่าง 7: คำนวณ Factorial -----");
  int n = 7;
  long factorial = 1;
  for (int i = 1; i <= n; i++) {
    factorial *= i;  // factorial = factorial * i
  }
  Serial.print(n);
  Serial.print("! = ");
  Serial.println(factorial);
  Serial.println();
  
  // ===== ตัวอย่าง 8: แสดงอักขระ ASCII =====
  Serial.println("----- ตัวอย่าง 8: แสดงตัวอักษร A-Z -----");
  for (char c = 'A'; c <= 'Z'; c++) {
    Serial.print(c);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 9: วนลูปกับอาร์เรย์ =====
  Serial.println("----- ตัวอย่าง 9: วนลูปกับอาร์เรย์ -----");
  int temperatures[] = {25, 28, 30, 27, 26, 29, 31};
  int arraySize = 7;
  
  Serial.println("อุณหภูมิแต่ละวัน:");
  for (int i = 0; i < arraySize; i++) {
    Serial.print("วันที่ ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(temperatures[i]);
    Serial.println(" °C");
  }
  
  // หาค่าเฉลี่ย
  float avgTemp = 0;
  for (int i = 0; i < arraySize; i++) {
    avgTemp += temperatures[i];
  }
  avgTemp /= arraySize;
  Serial.print("อุณหภูมิเฉลี่ย: ");
  Serial.print(avgTemp, 1);
  Serial.println(" °C");
  Serial.println();
  
  // ===== ตัวอย่าง 10: Nested Loop (ลูปซ้อนลูป) =====
  Serial.println("----- ตัวอย่าง 10: Nested Loop - สร้างรูปแบบ -----");
  Serial.println("สร้างสามเหลี่ยม:");
  for (int row = 1; row <= 5; row++) {
    for (int col = 1; col <= row; col++) {
      Serial.print("* ");
    }
    Serial.println();
  }
  Serial.println();
  
  // ===== ตัวอย่าง 11: สร้างตารางสูตรคูณ (Nested Loop) =====
  Serial.println("----- ตัวอย่าง 11: ตารางสูตรคูณ 1-5 -----");
  for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= 5; j++) {
      int product = i * j;
      Serial.print(product);
      Serial.print("\t");  // Tab
    }
    Serial.println();
  }
  Serial.println();
  
  // ===== ตัวอย่าง 12: break - หยุดลูปก่อนเวลา =====
  Serial.println("----- ตัวอย่าง 12: break - หยุดลูปเมื่อเจอเลข 7 -----");
  for (int i = 1; i <= 10; i++) {
    if (i == 7) {
      Serial.println("เจอเลข 7 แล้ว! หยุดลูป");
      break;  // หยุดลูปทันที
    }
    Serial.print(i);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 13: continue - ข้ามรอบปัจจุบัน =====
  Serial.println("----- ตัวอย่าง 13: continue - ข้ามเลขคู่ -----");
  Serial.print("แสดงเฉพาะเลขคี่ 1-10: ");
  for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
      continue;  // ข้ามรอบนี้ไปรอบถัดไป
    }
    Serial.print(i);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 14: นับเวลาถอยหลัง (Simulated) =====
  Serial.println("----- ตัวอย่าง 14: Countdown Timer -----");
  for (int seconds = 5; seconds > 0; seconds--) {
    Serial.print("เหลือเวลา: ");
    Serial.print(seconds);
    Serial.println(" วินาที...");
    delay(1000);  // หน่วงเวลา 1 วินาที
  }
  Serial.println("⏰ หมดเวลา!");
  Serial.println();
  
  // ===== ตัวอย่าง 15: กระพริบ LED (Simulated) =====
  Serial.println("----- ตัวอย่าง 15: กระพริบ LED 5 ครั้ง -----");
  for (int blink = 1; blink <= 5; blink++) {
    Serial.print("LED ON  - รอบที่ ");
    Serial.println(blink);
    delay(200);
    Serial.print("LED OFF - รอบที่ ");
    Serial.println(blink);
    delay(200);
  }
  Serial.println("เสร็จสิ้นการกระพริบ");
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
}
