/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Arithmetic Operators (ตัวดำเนินการทางคณิตศาสตร์)
 * ===================================================================
 * 
 * ตัวดำเนินการทางคณิตศาสตร์ที่ใช้ใน Arduino:
 * + : บวก (Addition)
 * - : ลบ (Subtraction)
 * * : คูณ (Multiplication)
 * / : หาร (Division)
 * % : โมดูลัส (Modulus) - เอาเศษจากการหาร
 * 
 * โค้ดนี้จะแสดงการใช้งานตัวดำเนินการทางคณิตศาสตร์ต่างๆ
 * และแสดงผลลัพธ์ผ่าน Serial Monitor
 * ===================================================================
 */

// ประกาศตัวแปรสำหรับการคำนวณ
int a = 20;
int b = 7;
int result;

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("Arithmetic Operators Demo");
  Serial.println("===================================");
  Serial.println();
  
  // แสดงค่าตัวแปรเริ่มต้น
  Serial.print("a = ");
  Serial.println(a);
  Serial.print("b = ");
  Serial.println(b);
  Serial.println();
  
  // ===== การบวก (Addition) =====
  result = a + b;
  Serial.println("----- การบวก (Addition) -----");
  Serial.print("a + b = ");
  Serial.print(a);
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(result);
  Serial.println();
  
  // ===== การลบ (Subtraction) =====
  result = a - b;
  Serial.println("----- การลบ (Subtraction) -----");
  Serial.print("a - b = ");
  Serial.print(a);
  Serial.print(" - ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(result);
  Serial.println();
  
  // ===== การคูณ (Multiplication) =====
  result = a * b;
  Serial.println("----- การคูณ (Multiplication) -----");
  Serial.print("a * b = ");
  Serial.print(a);
  Serial.print(" * ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(result);
  Serial.println();
  
  // ===== การหาร (Division) =====
  result = a / b;  // ผลลัพธ์จะเป็นเลขจำนวนเต็ม (ไม่มีทศนิยม)
  Serial.println("----- การหาร (Division) -----");
  Serial.print("a / b = ");
  Serial.print(a);
  Serial.print(" / ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(result);
  Serial.println("(หมายเหตุ: การหารเลขจำนวนเต็มจะได้ผลลัพธ์เป็นจำนวนเต็ม)");
  Serial.println();
  
  // ===== การหารแบบ Float (Division with Float) =====
  float floatResult = (float)a / (float)b;  // แปลงเป็น float เพื่อให้ได้ทศนิยม
  Serial.println("----- การหารแบบทศนิยม (Division with Float) -----");
  Serial.print("(float)a / (float)b = ");
  Serial.print(a);
  Serial.print(" / ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(floatResult, 2);  // แสดง 2 ตำแหน่งทศนิยม
  Serial.println();
  
  // ===== โมดูลัส (Modulus) - หาเศษจากการหาร =====
  result = a % b;
  Serial.println("----- โมดูลัส (Modulus) - หาเศษจากการหาร -----");
  Serial.print("a % b = ");
  Serial.print(a);
  Serial.print(" % ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(result);
  Serial.println("(หมายเหตุ: โมดูลัสคือเศษที่เหลือจากการหาร)");
  Serial.println();
  
  // ===== ตัวอย่างการใช้งานในชีวิตจริง =====
  Serial.println("===================================");
  Serial.println("ตัวอย่างการใช้งานจริง");
  Serial.println("===================================");
  
  // ตัวอย่าง: คำนวณค่าเฉลี่ย
  int score1 = 85;
  int score2 = 92;
  int score3 = 78;
  float average = (score1 + score2 + score3) / 3.0;
  Serial.println("คำนวณคะแนนเฉลี่ย:");
  Serial.print("คะแนน: ");
  Serial.print(score1);
  Serial.print(", ");
  Serial.print(score2);
  Serial.print(", ");
  Serial.println(score3);
  Serial.print("คะแนนเฉลี่ย = ");
  Serial.println(average, 2);
  Serial.println();
  
  // ตัวอย่าง: แปลงวินาทีเป็นนาทีและวินาที
  int totalSeconds = 125;
  int minutes = totalSeconds / 60;
  int seconds = totalSeconds % 60;
  Serial.println("แปลงวินาทีเป็นนาที:วินาที:");
  Serial.print(totalSeconds);
  Serial.print(" วินาที = ");
  Serial.print(minutes);
  Serial.print(" นาที ");
  Serial.print(seconds);
  Serial.println(" วินาที");
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop() 
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
}
