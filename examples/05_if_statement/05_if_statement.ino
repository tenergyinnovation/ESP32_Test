/*
 * ===================================================================
 * ตัวอย่างการใช้งาน if Statement
 * ===================================================================
 * 
 * if statement ใช้สำหรับตรวจสอบเงื่อนไข
 * ถ้าเงื่อนไขเป็นจริง (true) จะทำงานในบล็อก { } ที่อยู่ภายใน if
 * ถ้าเงื่อนไขเป็นเท็จ (false) จะข้ามบล็อกนั้นไป
 * 
 * รูปแบบ:
 * if (condition) {
 *   // code to execute if condition is true
 * }
 * ===================================================================
 */

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("if Statement Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== ตัวอย่าง 1: ตรวจสอบค่าตัวเลข =====
  Serial.println("----- ตัวอย่าง 1: ตรวจสอบค่าตัวเลข -----");
  int number = 15;
  Serial.print("number = ");
  Serial.println(number);
  
  // ตรวจสอบว่า number มากกว่า 10 หรือไม่
  if (number > 10) {
    Serial.println("number มากกว่า 10");
  }
  
  // ตรวจสอบว่า number เป็นเลขคู่หรือไม่
  if (number % 2 == 0) {
    Serial.println("number เป็นเลขคู่");
  }
  
  // ตรวจสอบว่า number เป็นเลขคี่หรือไม่
  if (number % 2 != 0) {
    Serial.println("number เป็นเลขคี่");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 2: ตรวจสอบอุณหภูมิ =====
  Serial.println("----- ตัวอย่าง 2: ตรวจสอบอุณหภูมิ -----");
  int temperature = 35;
  Serial.print("อุณหภูมิปัจจุบัน: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  // แจ้งเตือนถ้าอุณหภูมิสูงเกิน
  if (temperature > 30) {
    Serial.println("⚠️ เตือน: อุณหภูมิสูงเกินไป!");
  }
  
  // แจ้งเตือนถ้าอุณหภูมิสูงมาก
  if (temperature > 40) {
    Serial.println("🚨 อันตราย: อุณหภูมิสูงมาก!");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 3: ตรวจสอบความชื้น =====
  Serial.println("----- ตัวอย่าง 3: ตรวจสอบความชื้น -----");
  int humidity = 25;
  Serial.print("ความชื้น: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  // แจ้งเตือนถ้าความชื้นต่ำเกิน
  if (humidity < 30) {
    Serial.println("💧 อากาศแห้งเกินไป ควรเพิ่มความชื้น");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 4: ตรวจสอบคะแนนสอบ =====
  Serial.println("----- ตัวอย่าง 4: ตรวจสอบคะแนนสอบ -----");
  int examScore = 75;
  int passingScore = 60;
  Serial.print("คะแนนสอบ: ");
  Serial.println(examScore);
  Serial.print("คะแนนผ่าน: ");
  Serial.println(passingScore);
  
  // ตรวจสอบว่าสอบผ่านหรือไม่
  if (examScore >= passingScore) {
    Serial.println("✅ ยินดีด้วย! สอบผ่าน");
  }
  
  // ตรวจสอบว่าได้เกรด A หรือไม่
  if (examScore >= 80) {
    Serial.println("🌟 ได้เกรด A!");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 5: ตรวจสอบหลายเงื่อนไขด้วย AND (&&) =====
  Serial.println("----- ตัวอย่าง 5: ตรวจสอบหลายเงื่อนไข (AND) -----");
  int age = 25;
  bool hasLicense = true;
  Serial.print("อายุ: ");
  Serial.println(age);
  Serial.print("มีใบขับขี่: ");
  Serial.println(hasLicense ? "มี" : "ไม่มี");
  
  // ตรวจสอบว่าสามารถขับรถได้หรือไม่ (ต้องอายุ >= 18 และมีใบขับขี่)
  if (age >= 18 && hasLicense) {
    Serial.println("🚗 สามารถขับรถได้");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 6: ตรวจสอบหลายเงื่อนไขด้วย OR (||) =====
  Serial.println("----- ตัวอย่าง 6: ตรวจสอบหลายเงื่อนไข (OR) -----");
  int sensorValue = 850;
  int threshold1 = 800;
  int threshold2 = 200;
  Serial.print("ค่าเซ็นเซอร์: ");
  Serial.println(sensorValue);
  
  // แจ้งเตือนถ้าค่าเซ็นเซอร์สูงเกินหรือต่ำเกิน
  if (sensorValue > threshold1 || sensorValue < threshold2) {
    Serial.println("⚠️ ค่าเซ็นเซอร์ผิดปกติ!");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 7: if ซ้อน if (Nested if) =====
  Serial.println("----- ตัวอย่าง 7: Nested if -----");
  int waterLevel = 75;
  bool pumpEnabled = true;
  Serial.print("ระดับน้ำ: ");
  Serial.print(waterLevel);
  Serial.println(" %");
  Serial.print("ปั๊มเปิดใช้งาน: ");
  Serial.println(pumpEnabled ? "Yes" : "No");
  
  // ตรวจสอบระดับน้ำ ถ้าน้ำเยอะและปั๊มเปิดอยู่ ให้แจ้งเตือน
  if (waterLevel > 70) {
    Serial.println("ระดับน้ำสูง");
    
    if (pumpEnabled) {
      Serial.println("→ ควรปิดปั๊ม");
    }
  }
  Serial.println();
  
  // ===== ตัวอย่าง 8: ตรวจสอบค่าในช่วง (Range) =====
  Serial.println("----- ตัวอย่าง 8: ตรวจสอบค่าในช่วง -----");
  int voltage = 3.3 * 1000;  // 3300 mV
  int minVoltage = 3000;     // 3000 mV
  int maxVoltage = 3600;     // 3600 mV
  Serial.print("แรงดันไฟ: ");
  Serial.print(voltage);
  Serial.println(" mV");
  
  // ตรวจสอบว่าแรงดันอยู่ในช่วงปกติ
  if (voltage >= minVoltage && voltage <= maxVoltage) {
    Serial.println("✅ แรงดันไฟอยู่ในเกณฑ์ปกติ");
  }
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
}
