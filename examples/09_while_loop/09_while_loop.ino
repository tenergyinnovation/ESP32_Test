/*
 * ===================================================================
 * ตัวอย่างการใช้งาน while Loop
 * ===================================================================
 * 
 * while loop ใช้สำหรับทำซ้ำคำสั่งตราบเท่าที่เงื่อนไขยังเป็นจริง
 * ต่างจาก for loop คือไม่มีการกำหนดจำนวนรอบที่แน่นอน
 * 
 * รูปแบบ:
 * while (condition) {
 *   // code to repeat while condition is true
 * }
 * 
 * คำเตือน: ต้องระวังไม่ให้เกิด infinite loop (วนลูปไม่สิ้นสุด)
 * ต้องมีการเปลี่ยนแปลงค่าภายในลูปเพื่อให้เงื่อนไขเป็น false ได้
 * ===================================================================
 */

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("while Loop Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== ตัวอย่าง 1: นับเลข 1-10 =====
  Serial.println("----- ตัวอย่าง 1: นับเลข 1-10 ด้วย while -----");
  int counter = 1;
  while (counter <= 10) {
    Serial.print("Counter: ");
    Serial.println(counter);
    counter++;  // เพิ่มค่าทีละ 1 (สำคัญ! ไม่งั้นจะวนลูปไม่รู้จบ)
  }
  Serial.println();
  
  // ===== ตัวอย่าง 2: นับถอยหลัง =====
  Serial.println("----- ตัวอย่าง 2: นับถอยหลัง 5-1 -----");
  int countdown = 5;
  while (countdown > 0) {
    Serial.print("Countdown: ");
    Serial.println(countdown);
    countdown--;  // ลดค่าทีละ 1
  }
  Serial.println("🚀 Blast off!");
  Serial.println();
  
  // ===== ตัวอย่าง 3: คำนวณผลรวมจนถึงเป้าหมาย =====
  Serial.println("----- ตัวอย่าง 3: บวกเลขจนผลรวม >= 100 -----");
  int sum = 0;
  int number = 1;
  while (sum < 100) {
    sum += number;
    Serial.print("เพิ่ม ");
    Serial.print(number);
    Serial.print(" -> ผลรวม = ");
    Serial.println(sum);
    number++;
  }
  Serial.print("ผลรวมสุดท้าย: ");
  Serial.println(sum);
  Serial.println();
  
  // ===== ตัวอย่าง 4: หาเลขยกกำลัง 2 ที่น้อยกว่า 1000 =====
  Serial.println("----- ตัวอย่าง 4: เลขยกกำลัง 2 (< 1000) -----");
  int powerOf2 = 1;
  int exponent = 0;
  while (powerOf2 < 1000) {
    Serial.print("2^");
    Serial.print(exponent);
    Serial.print(" = ");
    Serial.println(powerOf2);
    exponent++;
    powerOf2 = powerOf2 * 2;  // หรือ powerOf2 *= 2
  }
  Serial.println();
  
  // ===== ตัวอย่าง 5: อ่านค่าเซ็นเซอร์จนเข้าเงื่อนไข =====
  Serial.println("----- ตัวอย่าง 5: รอค่าเซ็นเซอร์ถึงค่าที่กำหนด -----");
  int sensorValue = 0;
  int targetValue = 100;
  int readCount = 0;
  
  Serial.println("รอค่าเซ็นเซอร์ถึง 100...");
  while (sensorValue < targetValue) {
    sensorValue += random(5, 15);  // จำลองการอ่านค่าเซ็นเซอร์
    readCount++;
    
    Serial.print("การอ่านครั้งที่ ");
    Serial.print(readCount);
    Serial.print(": ");
    Serial.println(sensorValue);
    
    delay(200);  // หน่วงเวลาจำลองการอ่านเซ็นเซอร์
  }
  Serial.println("✅ ค่าเซ็นเซอร์ถึงเป้าหมายแล้ว!");
  Serial.println();
  
  // ===== ตัวอย่าง 6: หาตัวหารของเลข =====
  Serial.println("----- ตัวอย่าง 6: หาตัวหารของเลข 36 -----");
  int num = 36;
  int divisor = 1;
  Serial.print("ตัวหารของ ");
  Serial.print(num);
  Serial.print(": ");
  
  while (divisor <= num) {
    if (num % divisor == 0) {
      Serial.print(divisor);
      Serial.print(" ");
    }
    divisor++;
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 7: แสดงเลขฟีโบนัชชี =====
  Serial.println("----- ตัวอย่าง 7: ลำดับ Fibonacci (< 200) -----");
  int fib1 = 0;
  int fib2 = 1;
  int fibNext;
  
  Serial.print(fib1);
  Serial.print(", ");
  Serial.print(fib2);
  
  while (true) {
    fibNext = fib1 + fib2;
    if (fibNext >= 200) {
      break;  // หยุดลูปเมื่อเกิน 200
    }
    Serial.print(", ");
    Serial.print(fibNext);
    
    fib1 = fib2;
    fib2 = fibNext;
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 8: รอจนแบตเตอรี่เต็ม (จำลอง) =====
  Serial.println("----- ตัวอย่าง 8: ชาร์จแบตเตอรี่ -----");
  int batteryLevel = 20;
  Serial.print("ระดับแบตเริ่มต้น: ");
  Serial.print(batteryLevel);
  Serial.println("%");
  Serial.println("กำลังชาร์จ...");
  
  while (batteryLevel < 100) {
    batteryLevel += random(3, 8);  // จำลองการชาร์จ
    if (batteryLevel > 100) {
      batteryLevel = 100;  // จำกัดไม่เกิน 100%
    }
    
    Serial.print("🔋 แบตเตอรี่: ");
    Serial.print(batteryLevel);
    Serial.println("%");
    
    delay(300);
  }
  Serial.println("✅ ชาร์จเต็มแล้ว!");
  Serial.println();
  
  // ===== ตัวอย่าง 9: ประมวลผลข้อมูลในอาร์เรย์ =====
  Serial.println("----- ตัวอย่าง 9: หาค่าสูงสุดในอาร์เรย์ -----");
  int temperatures[] = {22, 25, 28, 24, 30, 27, 26};
  int arraySize = 7;
  int maxTemp = temperatures[0];
  int index = 1;
  
  while (index < arraySize) {
    if (temperatures[index] > maxTemp) {
      maxTemp = temperatures[index];
    }
    index++;
  }
  
  Serial.print("อุณหภูมิสูงสุด: ");
  Serial.print(maxTemp);
  Serial.println(" °C");
  Serial.println();
  
  // ===== ตัวอย่าง 10: แยกตัวเลขในจำนวนเต็ม =====
  Serial.println("----- ตัวอย่าง 10: แยกหลักของเลข 12345 -----");
  int number10 = 12345;
  Serial.print("ตัวเลข: ");
  Serial.println(number10);
  Serial.print("แยกหลัก: ");
  
  while (number10 > 0) {
    int digit = number10 % 10;  // เอาหลักสุดท้าย
    Serial.print(digit);
    Serial.print(" ");
    number10 = number10 / 10;  // ตัดหลักสุดท้ายออก
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 11: ใช้ while กับ continue =====
  Serial.println("----- ตัวอย่าง 11: ข้ามเลขที่หาร 3 ลงตัว -----");
  Serial.print("แสดงเลข 1-15 (ข้ามเลขหาร 3 ลงตัว): ");
  int n = 1;
  while (n <= 15) {
    if (n % 3 == 0) {
      n++;
      continue;  // ข้ามไปรอบถัดไป
    }
    Serial.print(n);
    Serial.print(" ");
    n++;
  }
  Serial.println();
  Serial.println();
  
  // ===== ตัวอย่าง 12: นับจำนวนบิทที่เป็น 1 =====
  Serial.println("----- ตัวอย่าง 12: นับบิทที่เป็น 1 ในเลข 45 -----");
  byte value = 45;  // 00101101 ในเลขฐานสอง
  int bitCount = 0;
  byte tempValue = value;
  
  Serial.print("เลข ");
  Serial.print(value);
  Serial.print(" = ");
  Serial.print(value, BIN);
  Serial.println(" (binary)");
  
  while (tempValue > 0) {
    if (tempValue & 1) {  // ตรวจสอบบิทสุดท้าย
      bitCount++;
    }
    tempValue >>= 1;  // เลื่อนบิทขวา 1 ตำแหน่ง
  }
  
  Serial.print("จำนวนบิทที่เป็น 1: ");
  Serial.println(bitCount);
  Serial.println();
  
  // ===== ตัวอย่าง 13: เปรียบเทียบ while กับ for =====
  Serial.println("----- ตัวอย่าง 13: เปรียบเทียบ while vs for -----");
  
  Serial.println("while loop:");
  int i = 0;
  while (i < 5) {
    Serial.print(i);
    Serial.print(" ");
    i++;
  }
  Serial.println();
  
  Serial.println("for loop (ทำงานเหมือนกัน):");
  for (int j = 0; j < 5; j++) {
    Serial.print(j);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
  
  // หมายเหตุ: ใน loop() จริงๆ while loop มักใช้สำหรับ:
  // - รอให้เงื่อนไขเป็นจริง (เช่น รอปุ่มกด)
  // - อ่านข้อมูลจาก Serial จนครบ
  // - ประมวลผลข้อมูลแบบไม่รู้จำนวนล่วงหน้า
}
