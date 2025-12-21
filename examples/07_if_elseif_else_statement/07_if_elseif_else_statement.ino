/*
 * ===================================================================
 * ตัวอย่างการใช้งาน if-else if-else Statement
 * ===================================================================
 * 
 * if-else if-else statement ใช้สำหรับตรวจสอบหลายเงื่อนไขตามลำดับ:
 * - ตรวจสอบเงื่อนไข if แรก ถ้าเป็นจริงจะทำงานแล้วข้ามส่วนอื่น
 * - ถ้าเงื่อนไข if เป็นเท็จ จะตรวจสอบ else if ถัดไป
 * - ถ้าทุกเงื่อนไขเป็นเท็จ จะทำงานในส่วน else สุดท้าย
 * 
 * รูปแบบ:
 * if (condition1) {
 *   // code if condition1 is true
 * } else if (condition2) {
 *   // code if condition2 is true
 * } else if (condition3) {
 *   // code if condition3 is true
 * } else {
 *   // code if all conditions are false
 * }
 * ===================================================================
 */

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("if-else if-else Statement Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== ตัวอย่าง 1: แปลงคะแนนเป็นเกรด =====
  Serial.println("----- ตัวอย่าง 1: แปลงคะแนนเป็นเกรด -----");
  int score = 75;
  char grade;
  Serial.print("คะแนน: ");
  Serial.println(score);
  
  if (score >= 80) {
    grade = 'A';
    Serial.println("เกรด: A (ดีเยี่ยม)");
  } else if (score >= 70) {
    grade = 'B';
    Serial.println("เกรด: B (ดี)");
  } else if (score >= 60) {
    grade = 'C';
    Serial.println("เกรด: C (ปานกลาง)");
  } else if (score >= 50) {
    grade = 'D';
    Serial.println("เกรด: D (พอใช้)");
  } else {
    grade = 'F';
    Serial.println("เกรด: F (ตก)");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 2: จำแนกช่วงอุณหภูมิ =====
  Serial.println("----- ตัวอย่าง 2: จำแนกช่วงอุณหภูมิ -----");
  int temperature = 28;
  Serial.print("อุณหภูมิ: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  if (temperature > 35) {
    Serial.println("🔥 ร้อนมาก - อันตราย!");
  } else if (temperature > 30) {
    Serial.println("🌡️ ร้อน - เปิดแอร์เต็มกำลัง");
  } else if (temperature > 25) {
    Serial.println("☀️ ค่อนข้างร้อน - เปิดพัดลม");
  } else if (temperature > 20) {
    Serial.println("😊 สบาย - อากาศดี");
  } else if (temperature > 15) {
    Serial.println("🍃 เย็น - สวมเสื้อแจ็คเก็ต");
  } else {
    Serial.println("🥶 หนาวมาก - เปิดฮีตเตอร์");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 3: ระบบควบคุมไฟ LED ตามความสว่าง =====
  Serial.println("----- ตัวอย่าง 3: ควบคุมไฟตามความสว่าง -----");
  int lightLevel = 650;  // ค่า 0-1023
  Serial.print("ระดับแสง: ");
  Serial.println(lightLevel);
  
  if (lightLevel > 800) {
    Serial.println("💡 สว่างมาก - ปิดไฟทั้งหมด");
  } else if (lightLevel > 600) {
    Serial.println("🔆 สว่างปานกลาง - เปิดไฟ 25%");
  } else if (lightLevel > 400) {
    Serial.println("🌤️ ค่อนข้างมืด - เปิดไฟ 50%");
  } else if (lightLevel > 200) {
    Serial.println("🌥️ มืด - เปิดไฟ 75%");
  } else {
    Serial.println("🌑 มืดมาก - เปิดไฟ 100%");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 4: ระดับแบตเตอรี่ =====
  Serial.println("----- ตัวอย่าง 4: ระดับแบตเตอรี่ -----");
  int batteryLevel = 45;  // เปอร์เซ็นต์
  Serial.print("แบตเตอรี่: ");
  Serial.print(batteryLevel);
  Serial.println(" %");
  
  if (batteryLevel > 80) {
    Serial.println("🔋🔋🔋 แบตเต็ม - สถานะดีมาก");
  } else if (batteryLevel > 60) {
    Serial.println("🔋🔋 แบตเพียงพอ");
  } else if (batteryLevel > 40) {
    Serial.println("🔋 แบตปานกลาง");
  } else if (batteryLevel > 20) {
    Serial.println("🪫 แบตต่ำ - ควรชาร์จ");
  } else if (batteryLevel > 10) {
    Serial.println("⚠️ แบตเตอรี่เหลือน้อย - ชาร์จด่วน!");
  } else {
    Serial.println("🚨 แบตเตอรี่ใกล้หมด - ชาร์จทันที!");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 5: จำแนกอายุ =====
  Serial.println("----- ตัวอย่าง 5: จำแนกกลุ่มอายุ -----");
  int age = 35;
  Serial.print("อายุ: ");
  Serial.print(age);
  Serial.println(" ปี");
  
  if (age < 0) {
    Serial.println("❌ อายุไม่ถูกต้อง");
  } else if (age < 13) {
    Serial.println("👶 เด็ก (Child)");
  } else if (age < 20) {
    Serial.println("🧑 วัยรุ่น (Teenager)");
  } else if (age < 40) {
    Serial.println("👨 วัยผู้ใหญ่ตอนต้น (Young Adult)");
  } else if (age < 60) {
    Serial.println("👴 วัยผู้ใหญ่ตอนปลาย (Middle Age)");
  } else if (age < 100) {
    Serial.println("👵 วัยสูงอายุ (Senior)");
  } else {
    Serial.println("⚠️ อายุมากผิดปกติ");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 6: ความเร็วลม =====
  Serial.println("----- ตัวอย่าง 6: ระดับความเร็วลม -----");
  int windSpeed = 55;  // km/h
  Serial.print("ความเร็วลม: ");
  Serial.print(windSpeed);
  Serial.println(" km/h");
  
  if (windSpeed < 12) {
    Serial.println("🍃 ลมสงบ (Calm)");
  } else if (windSpeed < 29) {
    Serial.println("🌬️ ลมเบา (Light breeze)");
  } else if (windSpeed < 39) {
    Serial.println("💨 ลมแรง (Strong breeze)");
  } else if (windSpeed < 50) {
    Serial.println("🌪️ ลมแรงมาก (Near gale)");
  } else if (windSpeed < 62) {
    Serial.println("⚠️ พายุ (Gale)");
  } else if (windSpeed < 75) {
    Serial.println("🌀 พายุรุนแรง (Storm)");
  } else {
    Serial.println("🌀🌀 พายุไต้ฝุ่น (Hurricane)");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 7: ระดับน้ำในถัง =====
  Serial.println("----- ตัวอย่าง 7: ระดับน้ำในถัง -----");
  int waterLevel = 30;  // เปอร์เซ็นต์
  Serial.print("ระดับน้ำ: ");
  Serial.print(waterLevel);
  Serial.println(" %");
  
  if (waterLevel >= 90) {
    Serial.println("🚰 น้ำเต็มเกือบล้น - ปิดวาล์ว");
  } else if (waterLevel >= 70) {
    Serial.println("💧 น้ำเกือบเต็ม - ปกติ");
  } else if (waterLevel >= 50) {
    Serial.println("💦 น้ำปานกลาง - ปกติ");
  } else if (waterLevel >= 30) {
    Serial.println("⚠️ น้ำต่ำ - พิจารณาเติม");
  } else if (waterLevel >= 10) {
    Serial.println("🚨 น้ำต่ำมาก - เติมด่วน");
  } else {
    Serial.println("❌ น้ำใกล้หมด - เติมทันที!");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 8: ระดับมลพิษในอากาศ (PM2.5) =====
  Serial.println("----- ตัวอย่าง 8: ระดับมลพิษ PM2.5 -----");
  int pm25 = 65;  // µg/m³
  Serial.print("PM2.5: ");
  Serial.print(pm25);
  Serial.println(" µg/m³");
  
  if (pm25 <= 25) {
    Serial.println("😊 อากาศดีมาก (Good)");
  } else if (pm25 <= 37) {
    Serial.println("🙂 อากาศดีปานกลาง (Moderate)");
  } else if (pm25 <= 50) {
    Serial.println("😐 เริ่มมีผลกระทบต่อสุขภาพ");
  } else if (pm25 <= 90) {
    Serial.println("😷 มีผลกระทบต่อสุขภาพ - สวมหน้ากาก");
  } else {
    Serial.println("☠️ อันตรายต่อสุขภาพ - หลีกเลี่ยงกิจกรรมกลางแจ้ง");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 9: ระบบชั่งน้ำหนัก =====
  Serial.println("----- ตัวอย่าง 9: จำแนกสินค้าตามน้ำหนัก -----");
  float weight = 2.5;  // kg
  float shippingCost;
  Serial.print("น้ำหนัก: ");
  Serial.print(weight);
  Serial.println(" kg");
  
  if (weight <= 0) {
    Serial.println("❌ น้ำหนักไม่ถูกต้อง");
    shippingCost = 0;
  } else if (weight <= 1.0) {
    Serial.println("📦 ขนาดเล็ก");
    shippingCost = 50;
  } else if (weight <= 3.0) {
    Serial.println("📦📦 ขนาดกลาง");
    shippingCost = 80;
  } else if (weight <= 5.0) {
    Serial.println("📦📦📦 ขนาดใหญ่");
    shippingCost = 120;
  } else {
    Serial.println("📦📦📦📦 ขนาดใหญ่พิเศษ");
    shippingCost = 200;
  }
  Serial.print("ค่าจัดส่ง: ");
  Serial.print(shippingCost);
  Serial.println(" บาท");
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
}
