/*
 * ===================================================================
 * ตัวอย่างการใช้งาน Logical Operators (ตัวดำเนินการเชิงตรรกะ)
 * ===================================================================
 * 
 * ตัวดำเนินการเชิงตรรกะที่ใช้ใน Arduino:
 * && : AND (และ) - เป็นจริงเมื่อทั้งสองเงื่อนไขเป็นจริง
 * || : OR (หรือ) - เป็นจริงเมื่ออย่างน้อยหนึ่งเงื่อนไขเป็นจริง
 * !  : NOT (ไม่) - กลับค่าความจริง (true เป็น false, false เป็น true)
 * 
 * ผลลัพธ์ของ Logical Operators จะเป็นค่า Boolean (true หรือ false)
 * ===================================================================
 */

// ประกาศตัวแปร Boolean สำหรับทดสอบ
bool condition1 = true;
bool condition2 = false;
bool condition3 = true;
bool result;

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("Logical Operators Demo");
  Serial.println("===================================");
  Serial.println();
  
  // แสดงค่าตัวแปรเริ่มต้น
  Serial.println("ค่าเริ่มต้นของตัวแปร:");
  Serial.print("condition1 = ");
  Serial.println(condition1 ? "true" : "false");
  Serial.print("condition2 = ");
  Serial.println(condition2 ? "true" : "false");
  Serial.print("condition3 = ");
  Serial.println(condition3 ? "true" : "false");
  Serial.println();
  
  // ===== ตัวดำเนินการ && (AND) =====
  Serial.println("----- AND Operator (&&) -----");
  Serial.println("AND เป็นจริงเมื่อทั้งสองเงื่อนไขเป็นจริง");
  Serial.println();
  
  result = condition1 && condition3;
  Serial.print("condition1 && condition3 : ");
  Serial.print("true && true = ");
  Serial.println(result ? "true" : "false");
  
  result = condition1 && condition2;
  Serial.print("condition1 && condition2 : ");
  Serial.print("true && false = ");
  Serial.println(result ? "true" : "false");
  
  result = condition2 && condition2;
  Serial.print("condition2 && condition2 : ");
  Serial.print("false && false = ");
  Serial.println(result ? "true" : "false");
  Serial.println();
  
  // ===== ตัวดำเนินการ || (OR) =====
  Serial.println("----- OR Operator (||) -----");
  Serial.println("OR เป็นจริงเมื่ออย่างน้อยหนึ่งเงื่อนไขเป็นจริง");
  Serial.println();
  
  result = condition1 || condition2;
  Serial.print("condition1 || condition2 : ");
  Serial.print("true || false = ");
  Serial.println(result ? "true" : "false");
  
  result = condition2 || condition3;
  Serial.print("condition2 || condition3 : ");
  Serial.print("false || true = ");
  Serial.println(result ? "true" : "false");
  
  result = condition2 || condition2;
  Serial.print("condition2 || condition2 : ");
  Serial.print("false || false = ");
  Serial.println(result ? "true" : "false");
  Serial.println();
  
  // ===== ตัวดำเนินการ ! (NOT) =====
  Serial.println("----- NOT Operator (!) -----");
  Serial.println("NOT กลับค่าความจริง (true -> false, false -> true)");
  Serial.println();
  
  result = !condition1;
  Serial.print("!condition1 : ");
  Serial.print("!true = ");
  Serial.println(result ? "true" : "false");
  
  result = !condition2;
  Serial.print("!condition2 : ");
  Serial.print("!false = ");
  Serial.println(result ? "true" : "false");
  Serial.println();
  
  // ===== การผสมตัวดำเนินการ (Combined Operators) =====
  Serial.println("----- Combined Logical Operators -----");
  Serial.println();
  
  result = (condition1 && condition3) || condition2;
  Serial.print("(condition1 && condition3) || condition2 : ");
  Serial.print("(true && true) || false = ");
  Serial.println(result ? "true" : "false");
  
  result = condition1 && (condition2 || condition3);
  Serial.print("condition1 && (condition2 || condition3) : ");
  Serial.print("true && (false || true) = ");
  Serial.println(result ? "true" : "false");
  
  result = !(condition1 && condition2);
  Serial.print("!(condition1 && condition2) : ");
  Serial.print("!(true && false) = ");
  Serial.println(result ? "true" : "false");
  Serial.println();
  
  // ===== ตัวอย่างการใช้งานจริง =====
  Serial.println("===================================");
  Serial.println("ตัวอย่างการใช้งานจริง");
  Serial.println("===================================");
  Serial.println();
  
  // ตัวอย่าง 1: ระบบเข้าสู่ห้อง (ต้องมีบัตรและรหัสถูกต้อง)
  bool hasCard = true;
  bool correctPassword = true;
  bool canEnter = hasCard && correctPassword;
  
  Serial.println("ตัวอย่าง 1: ระบบเข้าสู่ห้อง");
  Serial.print("มีบัตร: ");
  Serial.println(hasCard ? "Yes" : "No");
  Serial.print("รหัสถูกต้อง: ");
  Serial.println(correctPassword ? "Yes" : "No");
  Serial.print("สามารถเข้าได้: ");
  Serial.println(canEnter ? "Yes" : "No");
  Serial.println();
  
  // ตัวอย่าง 2: ระบบแจ้งเตือนอุณหภูมิ (แจ้งเตือนเมื่อสูงเกินหรือต่ำเกิน)
  int temp = 35;
  bool tooHot = (temp > 30);
  bool tooCold = (temp < 15);
  bool needAlert = tooHot || tooCold;
  
  Serial.println("ตัวอย่าง 2: ระบบแจ้งเตือนอุณหภูมิ");
  Serial.print("อุณหภูมิ: ");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.print("ร้อนเกินไป (>30): ");
  Serial.println(tooHot ? "Yes" : "No");
  Serial.print("เย็นเกินไป (<15): ");
  Serial.println(tooCold ? "Yes" : "No");
  Serial.print("ต้องแจ้งเตือน: ");
  Serial.println(needAlert ? "Yes" : "No");
  Serial.println();
  
  // ตัวอย่าง 3: เช็คเวลาทำงาน (9:00-17:00 และไม่ใช่วันหยุด)
  int currentHour = 14;
  bool isWeekday = true;
  bool isWorkingHour = (currentHour >= 9) && (currentHour <= 17);
  bool canWork = isWorkingHour && isWeekday;
  
  Serial.println("ตัวอย่าง 3: เช็คเวลาทำงาน");
  Serial.print("เวลาปัจจุบัน: ");
  Serial.print(currentHour);
  Serial.println(":00");
  Serial.print("เป็นวันทำงาน: ");
  Serial.println(isWeekday ? "Yes" : "No");
  Serial.print("อยู่ในช่วงเวลาทำงาน (9-17): ");
  Serial.println(isWorkingHour ? "Yes" : "No");
  Serial.print("สามารถทำงานได้: ");
  Serial.println(canWork ? "Yes" : "No");
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
}
