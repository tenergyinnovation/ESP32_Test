/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Bitwise และ Compound Operators
 * ===================================================================
 * 
 * Bitwise Operators (ตัวดำเนินการระดับบิท):
 * &  : AND - เปรียบเทียบแต่ละบิท ผลลัพธ์เป็น 1 เมื่อทั้งสองบิทเป็น 1
 * |  : OR - เปรียบเทียบแต่ละบิท ผลลัพธ์เป็น 1 เมื่ออย่างน้อยหนึ่งบิทเป็น 1
 * ^  : XOR - ผลลัพธ์เป็น 1 เมื่อบิทต่างกัน
 * ~  : NOT - กลับค่าบิททั้งหมด (0->1, 1->0)
 * << : Shift Left - เลื่อนบิทไปทางซ้าย
 * >> : Shift Right - เลื่อนบิทไปทางขวา
 * 
 * Compound Assignment Operators (ตัวดำเนินการเชิงประกอบ):
 * &=  : Bitwise AND assignment
 * |=  : Bitwise OR assignment
 * ^=  : Bitwise XOR assignment
 * <<= : Left shift assignment
 * >>= : Right shift assignment
 * +=  : Addition assignment
 * -=  : Subtraction assignment
 * *=  : Multiplication assignment
 * /=  : Division assignment
 * %=  : Modulus assignment
 * ===================================================================
 */

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("Bitwise & Compound Operators Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== Bitwise AND (&) =====
  Serial.println("----- Bitwise AND (&) -----");
  byte a = 0b00001111;  // 15 ในเลขฐาน 10
  byte b = 0b00110011;  // 51 ในเลขฐาน 10
  byte result = a & b;
  
  Serial.print("a = ");
  Serial.print(a, BIN);
  Serial.print(" (");
  Serial.print(a);
  Serial.println(")");
  Serial.print("b = ");
  Serial.print(b, BIN);
  Serial.print(" (");
  Serial.print(b);
  Serial.println(")");
  Serial.print("a & b = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(")");
  Serial.println();
  
  // ===== Bitwise OR (|) =====
  Serial.println("----- Bitwise OR (|) -----");
  result = a | b;
  Serial.print("a | b = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(")");
  Serial.println();
  
  // ===== Bitwise XOR (^) =====
  Serial.println("----- Bitwise XOR (^) -----");
  result = a ^ b;
  Serial.print("a ^ b = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(")");
  Serial.println();
  
  // ===== Bitwise NOT (~) =====
  Serial.println("----- Bitwise NOT (~) -----");
  result = ~a;
  Serial.print("~a = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(")");
  Serial.println();
  
  // ===== Bit Shift Left (<<) =====
  Serial.println("----- Bit Shift Left (<<) -----");
  byte num = 0b00000001;  // 1
  Serial.print("เริ่มต้น: ");
  Serial.print(num, BIN);
  Serial.print(" (");
  Serial.print(num);
  Serial.println(")");
  
  result = num << 1;
  Serial.print("num << 1 = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(") // เลื่อนซ้าย 1 บิท");
  
  result = num << 2;
  Serial.print("num << 2 = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(") // เลื่อนซ้าย 2 บิท");
  
  result = num << 3;
  Serial.print("num << 3 = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(") // เลื่อนซ้าย 3 บิท");
  Serial.println("หมายเหตุ: << 1 เท่ากับคูณด้วย 2, << 2 เท่ากับคูณด้วย 4");
  Serial.println();
  
  // ===== Bit Shift Right (>>) =====
  Serial.println("----- Bit Shift Right (>>) -----");
  num = 0b00001000;  // 8
  Serial.print("เริ่มต้น: ");
  Serial.print(num, BIN);
  Serial.print(" (");
  Serial.print(num);
  Serial.println(")");
  
  result = num >> 1;
  Serial.print("num >> 1 = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(") // เลื่อนขวา 1 บิท");
  
  result = num >> 2;
  Serial.print("num >> 2 = ");
  Serial.print(result, BIN);
  Serial.print(" (");
  Serial.print(result);
  Serial.println(") // เลื่อนขวา 2 บิท");
  Serial.println("หมายเหตุ: >> 1 เท่ากับหารด้วย 2, >> 2 เท่ากับหารด้วย 4");
  Serial.println();
  
  // ===== Compound Assignment Operators =====
  Serial.println("===================================");
  Serial.println("Compound Assignment Operators");
  Serial.println("===================================");
  Serial.println();
  
  // &= (Bitwise AND assignment)
  Serial.println("----- Bitwise AND Assignment (&=) -----");
  byte x = 0b11110000;
  Serial.print("x = ");
  Serial.print(x, BIN);
  Serial.print(" (");
  Serial.print(x);
  Serial.println(")");
  x &= 0b00111100;
  Serial.print("x &= 00111100 -> x = ");
  Serial.print(x, BIN);
  Serial.print(" (");
  Serial.print(x);
  Serial.println(")");
  Serial.println();
  
  // |= (Bitwise OR assignment)
  Serial.println("----- Bitwise OR Assignment (|=) -----");
  x = 0b00001111;
  Serial.print("x = ");
  Serial.print(x, BIN);
  Serial.print(" (");
  Serial.print(x);
  Serial.println(")");
  x |= 0b11110000;
  Serial.print("x |= 11110000 -> x = ");
  Serial.print(x, BIN);
  Serial.print(" (");
  Serial.print(x);
  Serial.println(")");
  Serial.println();
  
  // <<= (Left shift assignment)
  Serial.println("----- Left Shift Assignment (<<=) -----");
  x = 4;
  Serial.print("x = ");
  Serial.println(x);
  x <<= 2;  // เทียบเท่ากับ x = x << 2
  Serial.print("x <<= 2 -> x = ");
  Serial.print(x);
  Serial.println(" (คูณด้วย 4)");
  Serial.println();
  
  // >>= (Right shift assignment)
  Serial.println("----- Right Shift Assignment (>>=) -----");
  x = 32;
  Serial.print("x = ");
  Serial.println(x);
  x >>= 3;  // เทียบเท่ากับ x = x >> 3
  Serial.print("x >>= 3 -> x = ");
  Serial.print(x);
  Serial.println(" (หารด้วย 8)");
  Serial.println();
  
  // Compound Arithmetic Operators
  Serial.println("----- Arithmetic Compound Operators -----");
  int value = 10;
  Serial.print("เริ่มต้น: value = ");
  Serial.println(value);
  
  value += 5;  // เทียบเท่ากับ value = value + 5
  Serial.print("value += 5 -> value = ");
  Serial.println(value);
  
  value -= 3;  // เทียบเท่ากับ value = value - 3
  Serial.print("value -= 3 -> value = ");
  Serial.println(value);
  
  value *= 2;  // เทียบเท่ากับ value = value * 2
  Serial.print("value *= 2 -> value = ");
  Serial.println(value);
  
  value /= 4;  // เทียบเท่ากับ value = value / 4
  Serial.print("value /= 4 -> value = ");
  Serial.println(value);
  
  value %= 5;  // เทียบเท่ากับ value = value % 5
  Serial.print("value %= 5 -> value = ");
  Serial.println(value);
  Serial.println();
  
  // ===== ตัวอย่างการใช้งานจริง =====
  Serial.println("===================================");
  Serial.println("ตัวอย่างการใช้งานจริง");
  Serial.println("===================================");
  Serial.println();
  
  // ตัวอย่าง: ใช้ Bitwise สำหรับจัดการ LED หลายดวง
  Serial.println("ตัวอย่าง: จัดการสถานะ LED 8 ดวงด้วย 1 byte");
  byte ledStatus = 0b00000000;  // LED ทั้งหมดดับ
  Serial.print("เริ่มต้น (LED ดับทั้งหมด): ");
  Serial.println(ledStatus, BIN);
  
  // เปิด LED ตัวที่ 0 และ 2 และ 4
  ledStatus |= (1 << 0);  // เปิด LED 0
  ledStatus |= (1 << 2);  // เปิด LED 2
  ledStatus |= (1 << 4);  // เปิด LED 4
  Serial.print("เปิด LED 0, 2, 4: ");
  Serial.println(ledStatus, BIN);
  
  // ตรวจสอบสถานะ LED ตัวที่ 2
  bool led2Status = (ledStatus & (1 << 2)) != 0;
  Serial.print("สถานะ LED 2: ");
  Serial.println(led2Status ? "ON" : "OFF");
  
  // ปิด LED ตัวที่ 2
  ledStatus &= ~(1 << 2);
  Serial.print("ปิด LED 2: ");
  Serial.println(ledStatus, BIN);
  
  // สลับสถานะ LED ตัวที่ 4
  ledStatus ^= (1 << 4);
  Serial.print("Toggle LED 4: ");
  Serial.println(ledStatus, BIN);
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
}
