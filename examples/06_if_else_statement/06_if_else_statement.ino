/*
 * ===================================================================
 * ตัวอย่างการใช้งาน if-else Statement
 * ===================================================================
 * 
 * if-else statement ใช้สำหรับตรวจสอบเงื่อนไขและมี 2 ทางเลือก:
 * - ถ้าเงื่อนไขเป็นจริง (true) จะทำงานในบล็อก if { }
 * - ถ้าเงื่อนไขเป็นเท็จ (false) จะทำงานในบล็อก else { }
 * 
 * รูปแบบ:
 * if (condition) {
 *   // code to execute if condition is true
 * } else {
 *   // code to execute if condition is false
 * }
 * ===================================================================
 */

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("if-else Statement Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== ตัวอย่าง 1: ตรวจสอบเลขคู่-คี่ =====
  Serial.println("----- ตัวอย่าง 1: ตรวจสอบเลขคู่-คี่ -----");
  int number = 17;
  Serial.print("number = ");
  Serial.println(number);
  
  if (number % 2 == 0) {
    Serial.println("→ number เป็นเลขคู่");
  } else {
    Serial.println("→ number เป็นเลขคี่");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 2: ตรวจสอบอุณหภูมิ =====
  Serial.println("----- ตัวอย่าง 2: ตรวจสอบอุณหภูมิ -----");
  int temperature = 18;
  int comfortTemp = 25;
  Serial.print("อุณหภูมิปัจจุบัน: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("อุณหภูมิที่สบาย: ");
  Serial.print(comfortTemp);
  Serial.println(" °C");
  
  if (temperature >= comfortTemp) {
    Serial.println("→ อุณหภูมิพอดีหรือร้อน ไม่ต้องเปิดฮีตเตอร์");
  } else {
    Serial.println("→ อุณหภูมิเย็น ควรเปิดฮีตเตอร์");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 3: ตรวจสอบคะแนนสอบ =====
  Serial.println("----- ตัวอย่าง 3: ตรวจสอบคะแนนสอบ -----");
  int examScore = 55;
  int passingScore = 60;
  Serial.print("คะแนนสอบ: ");
  Serial.println(examScore);
  Serial.print("คะแนนผ่าน: ");
  Serial.println(passingScore);
  
  if (examScore >= passingScore) {
    Serial.println("✅ ยินดีด้วย! สอบผ่าน");
  } else {
    Serial.println("❌ เสียใจด้วย สอบไม่ผ่าน");
    int needMore = passingScore - examScore;
    Serial.print("   ต้องการอีก ");
    Serial.print(needMore);
    Serial.println(" คะแนน");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 4: ตรวจสอบสิทธิ์การเข้าใช้ =====
  Serial.println("----- ตัวอย่าง 4: ตรวจสอบสิทธิ์การเข้าใช้ -----");
  int age = 16;
  int minimumAge = 18;
  Serial.print("อายุ: ");
  Serial.println(age);
  Serial.print("อายุขั้นต่ำ: ");
  Serial.println(minimumAge);
  
  if (age >= minimumAge) {
    Serial.println("✅ อนุญาตให้เข้าใช้งาน");
  } else {
    Serial.println("⛔ ไม่อนุญาตให้เข้าใช้งาน (อายุไม่ถึง)");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 5: ตรวจสอบระดับแบตเตอรี่ =====
  Serial.println("----- ตัวอย่าง 5: ตรวจสอบระดับแบตเตอรี่ -----");
  int batteryLevel = 15;  // เปอร์เซ็นต์
  int lowBatteryThreshold = 20;
  Serial.print("ระดับแบตเตอรี่: ");
  Serial.print(batteryLevel);
  Serial.println(" %");
  
  if (batteryLevel >= lowBatteryThreshold) {
    Serial.println("🔋 แบตเตอรี่เพียงพอ");
  } else {
    Serial.println("🪫 แบตเตอรี่ต่ำ! กรุณาชาร์จ");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 6: ตรวจสอบการเชื่อมต่อ WiFi =====
  Serial.println("----- ตัวอย่าง 6: ตรวจสอบการเชื่อมต่อ WiFi -----");
  bool isConnected = false;
  Serial.print("สถานะ WiFi: ");
  Serial.println(isConnected ? "Connected" : "Disconnected");
  
  if (isConnected) {
    Serial.println("✅ เชื่อมต่อ WiFi แล้ว");
    Serial.println("   สามารถส่งข้อมูลไปยัง Cloud ได้");
  } else {
    Serial.println("❌ ไม่ได้เชื่อมต่อ WiFi");
    Serial.println("   จะบันทึกข้อมูลไว้ใน Local Storage");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 7: ควบคุมพัดลมตามอุณหภูมิ =====
  Serial.println("----- ตัวอย่าง 7: ควบคุมพัดลมตามอุณหภูมิ -----");
  int roomTemp = 32;
  int fanTriggerTemp = 28;
  Serial.print("อุณหภูมิห้อง: ");
  Serial.print(roomTemp);
  Serial.println(" °C");
  Serial.print("อุณหภูมิที่เปิดพัดลม: ");
  Serial.print(fanTriggerTemp);
  Serial.println(" °C");
  
  if (roomTemp > fanTriggerTemp) {
    Serial.println("💨 เปิดพัดลม (อากาศร้อน)");
  } else {
    Serial.println("⏹️  ปิดพัดลม (อากาศเย็นสบาย)");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 8: ตรวจสอบเซ็นเซอร์ความชื้นในดิน =====
  Serial.println("----- ตัวอย่าง 8: ตรวจสอบความชื้นในดิน -----");
  int soilMoisture = 35;  // เปอร์เซ็นต์
  int dryThreshold = 40;
  Serial.print("ความชื้นในดิน: ");
  Serial.print(soilMoisture);
  Serial.println(" %");
  Serial.print("ค่าขั้นต่ำ: ");
  Serial.print(dryThreshold);
  Serial.println(" %");
  
  if (soilMoisture < dryThreshold) {
    Serial.println("💧 ดินแห้ง! เปิดระบบรดน้ำ");
  } else {
    Serial.println("✅ ดินมีความชื้นเพียงพอ");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 9: ตรวจสอบสถานะประตู =====
  Serial.println("----- ตัวอย่าง 9: ตรวจสอบสถานะประตู -----");
  bool doorOpen = true;
  Serial.print("สถานะประตู: ");
  Serial.println(doorOpen ? "เปิด" : "ปิด");
  
  if (doorOpen) {
    Serial.println("🚪 ประตูเปิดอยู่");
    Serial.println("   ⚠️ แจ้งเตือนระบบรักษาความปลอดภัย");
  } else {
    Serial.println("🔒 ประตูปิด - ปลอดภัย");
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
