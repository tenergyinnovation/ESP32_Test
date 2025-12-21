/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Comments (คอมเมนต์)
 * ===================================================================
 * 
 * Comments คือข้อความอธิบายในโค้ดที่คอมไพเลอร์จะไม่นำไปประมวลผล
 * ใช้สำหรับ:
 * - อธิบายการทำงานของโค้ด
 * - จดบันทึกสำหรับตัวเองหรือผู้อื่นที่จะอ่านโค้ด
 * - ปิดการทำงานของโค้ดชั่วคราว (เพื่อทดสอบ)
 * - เขียนเอกสารประกอบ
 * 
 * ประเภทของ Comments:
 * 1. Single-line Comment (คอมเมนต์บรรทัดเดียว): //
 * 2. Multi-line Comment (คอมเมนต์หลายบรรทัด): /* ... */
/*
 * ===================================================================
 */

// ===================================================================
// นี่คือ Single-line Comment (คอมเมนต์บรรทัดเดียว)
// ใช้เครื่องหมาย // นำหน้า
// ทุกอย่างหลัง // ในบรรทัดเดียวกันจะถูกมองเป็นคอมเมนต์
// ===================================================================

/*
  ===================================================================
  นี่คือ Multi-line Comment (คอมเมนต์หลายบรรทัด)
  ใช้ /* เปิด และ */ ปิด (สามารถครอบคลุมหลายบรรทัดได้)
  เหมาะสำหรับเขียนคำอธิบายยาวๆ หรือหัวข้อโค้ด
  ===================================================================
*/

// ประกาศตัวแปรพร้อมคอมเมนต์อธิบาย
int ledPin = 13;        // หมายเลขพินของ LED
int buttonPin = 2;      // หมายเลขพินของปุ่มกด
int sensorValue = 0;    // ค่าที่อ่านได้จากเซ็นเซอร์
bool isRunning = true;  // สถานะการทำงาน

/*
  ฟังก์ชัน setup()
  - ทำงานครั้งเดียวตอนเริ่มโปรแกรม
  - ใช้สำหรับตั้งค่าเริ่มต้น
*/
void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  // แสดงหัวข้อโปรแกรม
  Serial.println("===================================");
  Serial.println("Comments Demo");
  Serial.println("===================================");
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 1: Single-line Comments =====
   * คอมเมนต์บรรทัดเดียวใช้เครื่องหมาย //
   */
  Serial.println("----- Single-line Comments -----");
  
  // ประกาศตัวแปร
  int number = 42;  // เก็บค่าตัวเลข
  
  // แสดงค่าตัวแปร
  Serial.print("Number: ");
  Serial.println(number);  // พิมพ์ค่าและขึ้นบรรทัดใหม่
  
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 2: Multi-line Comments =====
   * คอมเมนต์หลายบรรทัดใช้ /* ... */
   */
  Serial.println("----- Multi-line Comments -----");
  
  /*
    คำนวณพื้นที่สี่เหลี่ยม
    สูตร: พื้นที่ = ความกว้าง × ความยาว
    
    ตัวอย่าง:
    - ความกว้าง = 5 เมตร
    - ความยาว = 10 เมตร
    - พื้นที่ = 50 ตารางเมตร
  */
  int width = 5;   // ความกว้าง (เมตร)
  int length = 10; // ความยาว (เมตร)
  int area = width * length;  // คำนวณพื้นที่
  
  Serial.print("พื้นที่สี่เหลี่ยม: ");
  Serial.print(area);
  Serial.println(" ตร.ม.");
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 3: คอมเมนต์เพื่ออธิบายโค้ด =====
   */
  Serial.println("----- อธิบายโค้ดด้วย Comments -----");
  
  // ตรวจสอบว่าเลขเป็นคู่หรือคี่
  int testNumber = 17;
  
  if (testNumber % 2 == 0) {
    // ถ้าหารด้วย 2 ลงตัว แสดงว่าเป็นเลขคู่
    Serial.print(testNumber);
    Serial.println(" เป็นเลขคู่");
  } else {
    // ถ้าหารด้วย 2 ไม่ลงตัว แสดงว่าเป็นเลขคี่
    Serial.print(testNumber);
    Serial.println(" เป็นเลขคี่");
  }
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 4: ปิดการทำงานของโค้ดชั่วคราว =====
   * ใช้คอมเมนต์เพื่อ "ปิด" โค้ดบางส่วนโดยไม่ลบทิ้ง
   */
  Serial.println("----- ปิดโค้ดชั่วคราว -----");
  
  Serial.println("บรรทัดนี้จะทำงาน");
  
  // Serial.println("บรรทัดนี้ถูกปิดด้วย //");
  
  /*
  Serial.println("บรรทัดนี้ถูกปิดด้วย /* */");
  Serial.println("บรรทัดนี้ก็ถูกปิดเช่นกัน");
  */
  
  Serial.println("บรรทัดนี้จะทำงานอีกครั้ง");
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 5: TODO Comments =====
   * ใช้สำหรับจดสิ่งที่ต้องทำในอนาคต
   */
  Serial.println("----- TODO Comments -----");
  
  // TODO: เพิ่มฟังก์ชันตรวจสอบอุณหภูมิ
  // TODO: เชื่อมต่อ WiFi
  // FIXME: แก้ไขบั๊กการอ่านเซ็นเซอร์
  // NOTE: อย่าลืมทดสอบกับฮาร์ดแวร์จริง
  
  Serial.println("ดู TODO ในโค้ดสำหรับงานที่ค้างอยู่");
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 6: คอมเมนต์สำหรับเอกสาร =====
   */
  Serial.println("----- Documentation Comments -----");
  
  /**
   * คำนวณค่าเฉลี่ย
   * 
   * @param values อาร์เรย์ของตัวเลข
   * @param size ขนาดของอาร์เรย์
   * @return ค่าเฉลี่ยของตัวเลขในอาร์เรย์
   */
  int values[] = {10, 20, 30, 40, 50};
  int size = 5;
  float average = 0;
  
  // คำนวณผลรวม
  for (int i = 0; i < size; i++) {
    average += values[i];
  }
  
  // หาค่าเฉลี่ย
  average /= size;
  
  Serial.print("ค่าเฉลี่ย: ");
  Serial.println(average);
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 7: คอมเมนต์แบบหลายรูปแบบ =====
   */
  Serial.println("----- รูปแบบต่างๆ ของ Comments -----");
  
  int a = 10;  // คอมเมนต์ท้ายบรรทัด
  
  // คอมเมนต์เหนือโค้ด
  int b = 20;
  
  /*
    คอมเมนต์
    หลาย
    บรรทัด
  */
  int c = a + b;
  
  Serial.print("ผลรวม: ");
  Serial.println(c);
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 8: Best Practices =====
   */
  Serial.println("----- แนวทางที่ดีในการใช้ Comments -----");
  Serial.println();
  Serial.println("✓ ใช้คอมเมนต์อธิบายโค้ดที่ซับซ้อน");
  Serial.println("✓ อธิบาย 'ทำไม' มากกว่า 'อะไร'");
  Serial.println("✓ อัปเดตคอมเมนต์เมื่อแก้ไขโค้ด");
  Serial.println("✓ ใช้ TODO, FIXME, NOTE สำหรับจดบันทึก");
  Serial.println();
  Serial.println("✗ อย่าใช้คอมเมนต์อธิบายสิ่งที่ชัดเจนแล้ว");
  Serial.println("✗ อย่าปล่อยคอมเมนต์ที่ล้าสมัย");
  Serial.println("✗ อย่าใช้คอมเมนต์แทนการเขียนโค้ดที่ดี");
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 9: คอมเมนต์กับฟังก์ชัน =====
   */
  Serial.println("----- คอมเมนต์สำหรับฟังก์ชัน -----");
  
  // เรียกใช้ฟังก์ชันคำนวณพื้นที่วงกลม
  float radius = 5.0;  // รัศมี 5 หน่วย
  float circleArea = calculateCircleArea(radius);
  
  Serial.print("พื้นที่วงกลม (รัศมี ");
  Serial.print(radius);
  Serial.print("): ");
  Serial.println(circleArea);
  Serial.println();
  
  /*
   * ===== ตัวอย่างที่ 10: Header Comments =====
   */
  Serial.println("----- Header Comments (หัวไฟล์) -----");
  Serial.println("ดูตัวอย่างที่ด้านบนของไฟล์นี้");
  Serial.println("Header comment ควรมี:");
  Serial.println("- ชื่อโปรแกรม/ไฟล์");
  Serial.println("- คำอธิบายสั้นๆ");
  Serial.println("- ผู้เขียน (ถ้าต้องการ)");
  Serial.println("- วันที่ (ถ้าต้องการ)");
  Serial.println("- License (ถ้าต้องการ)");
  Serial.println();
  
  // แสดงตัวอย่างโค้ดที่มีและไม่มีคอมเมนต์
  Serial.println("----- เปรียบเทียบโค้ดมี/ไม่มี Comments -----");
  Serial.println();
  
  // โค้ดไม่มีคอมเมนต์ (อ่านยาก)
  Serial.println("โค้ดไม่มีคอมเมนต์:");
  Serial.println("int x=analogRead(A0);");
  Serial.println("if(x>500){digitalWrite(13,HIGH);}");
  Serial.println();
  
  // โค้ดมีคอมเมนต์ (อ่านง่าย)
  Serial.println("โค้ดมีคอมเมนต์:");
  Serial.println("// อ่านค่าแสงจากเซ็นเซอร์");
  Serial.println("int lightLevel = analogRead(A0);");
  Serial.println();
  Serial.println("// ถ้าแสงน้อย เปิด LED");
  Serial.println("if (lightLevel > 500) {");
  Serial.println("  digitalWrite(LED_PIN, HIGH);");
  Serial.println("}");
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
  Serial.println();
  
  // สรุป
  Serial.println("สรุป:");
  Serial.println("- Comments ช่วยให้โค้ดอ่านและเข้าใจง่ายขึ้น");
  Serial.println("- Single-line: // (บรรทัดเดียว)");
  Serial.println("- Multi-line: /* ... */ (หลายบรรทัด)");
  Serial.println("- ใช้อธิบายโค้ดที่ซับซ้อน ไม่ใช่อธิบายทุกบรรทัด");
  Serial.println("- อัปเดตคอมเมนต์ให้ตรงกับโค้ดเสมอ");
}

/*
 * ฟังก์ชันคำนวณพื้นที่วงกลม
 * 
 * พารามิเตอร์:
 *   r - รัศมีของวงกลม
 * 
 * คืนค่า:
 *   พื้นที่ของวงกลม (πr²)
 */
float calculateCircleArea(float r) {
  // สูตร: พื้นที่ = π × รัศมี²
  // ใช้ค่า π ≈ 3.14159
  const float PI = 3.14159;
  return PI * r * r;
}

/*
 * ฟังก์ชัน loop()
 * - ทำงานซ้ำไปเรื่อยๆ หลัง setup() เสร็จ
 * - ในตัวอย่างนี้ไม่ได้ใช้งาน
 */
void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
  
  /*
    หมายเหตุ: ในโปรเจคจริง loop() จะมีการทำงานอย่างต่อเนื่อง
    เช่น อ่านเซ็นเซอร์, ควบคุม LED, รับคำสั่งจาก Serial ฯลฯ
  */
  
  // TODO: เพิ่มโค้ดใน loop() ตามที่ต้องการ
}

// ===================================================================
// สิ้นสุดโปรแกรม
// ===================================================================
