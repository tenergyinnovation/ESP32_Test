/*
 * ===================================================================
 * ตัวอย่างการใช้งาน switch-case Statement
 * ===================================================================
 * 
 * switch-case ใช้สำหรับตรวจสอบค่าของตัวแปรและเลือกทำงานตามกรณีต่างๆ
 * เหมาะสำหรับกรณีที่มีหลายทางเลือกที่ชัดเจน (แทนการใช้ if-else if ซ้อนกันเยอะ)
 * 
 * รูปแบบ:
 * switch (variable) {
 *   case value1:
 *     // code for case 1
 *     break;
 *   case value2:
 *     // code for case 2
 *     break;
 *   default:
 *     // code if no case matches
 * }
 * 
 * คำสำคัญ:
 * - case: กำหนดกรณีที่ต้องการตรวจสอบ
 * - break: หยุดการทำงานและออกจาก switch (ถ้าไม่มี break จะทำงานต่อไปยัง case ถัดไป)
 * - default: กรณีที่ไม่ตรงกับ case ใดๆ (เหมือน else)
 * ===================================================================
 */

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("switch-case Statement Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== ตัวอย่าง 1: เลือกวันในสัปดาห์ =====
  Serial.println("----- ตัวอย่าง 1: แสดงวันในสัปดาห์ -----");
  int dayOfWeek = 3;
  Serial.print("dayOfWeek = ");
  Serial.println(dayOfWeek);
  Serial.print("วัน: ");
  
  switch (dayOfWeek) {
    case 1:
      Serial.println("วันจันทร์");
      break;
    case 2:
      Serial.println("วันอังคาร");
      break;
    case 3:
      Serial.println("วันพุธ");
      break;
    case 4:
      Serial.println("วันพฤหัสบดี");
      break;
    case 5:
      Serial.println("วันศุกร์");
      break;
    case 6:
      Serial.println("วันเสาร์");
      break;
    case 7:
      Serial.println("วันอาทิตย์");
      break;
    default:
      Serial.println("ไม่ถูกต้อง (ต้องเป็น 1-7)");
      break;
  }
  Serial.println();
  
  // ===== ตัวอย่าง 2: เมนูตัวเลือก =====
  Serial.println("----- ตัวอย่าง 2: เมนูควบคุมอุปกรณ์ -----");
  int menuOption = 2;
  
  Serial.println("=== เมนู ===");
  Serial.println("1. เปิดไฟ LED");
  Serial.println("2. ปิดไฟ LED");
  Serial.println("3. กระพริบ LED");
  Serial.println("4. ตั้งค่าความสว่าง");
  Serial.print("\nเลือก: ");
  Serial.println(menuOption);
  Serial.print("ผลลัพธ์: ");
  
  switch (menuOption) {
    case 1:
      Serial.println("💡 เปิดไฟ LED แล้ว");
      break;
    case 2:
      Serial.println("⚫ ปิดไฟ LED แล้ว");
      break;
    case 3:
      Serial.println("✨ กระพริบ LED");
      break;
    case 4:
      Serial.println("🔆 เข้าสู่โหมดตั้งค่าความสว่าง");
      break;
    default:
      Serial.println("❌ ตัวเลือกไม่ถูกต้อง");
      break;
  }
  Serial.println();
  
  // ===== ตัวอย่าง 3: แปลงเกรดเป็นคะแนน =====
  Serial.println("----- ตัวอย่าง 3: แปลงเกรดเป็นคะแนน -----");
  char grade = 'B';
  Serial.print("เกรด: ");
  Serial.println(grade);
  Serial.print("ช่วงคะแนน: ");
  
  switch (grade) {
    case 'A':
      Serial.println("80-100");
      Serial.println("ระดับ: ดีเยี่ยม");
      break;
    case 'B':
      Serial.println("70-79");
      Serial.println("ระดับ: ดี");
      break;
    case 'C':
      Serial.println("60-69");
      Serial.println("ระดับ: ปานกลาง");
      break;
    case 'D':
      Serial.println("50-59");
      Serial.println("ระดับ: พอใช้");
      break;
    case 'F':
      Serial.println("0-49");
      Serial.println("ระดับ: ตก");
      break;
    default:
      Serial.println("เกรดไม่ถูกต้อง");
      break;
  }
  Serial.println();
  
  // ===== ตัวอย่าง 4: ควบคุมมอเตอร์ =====
  Serial.println("----- ตัวอย่าง 4: ควบคุมทิศทางมอเตอร์ -----");
  char direction = 'F';
  Serial.print("คำสั่ง: ");
  Serial.println(direction);
  Serial.print("การทำงาน: ");
  
  switch (direction) {
    case 'F':
    case 'f':
      Serial.println("⬆️ มอเตอร์เดินหน้า");
      break;
    case 'B':
    case 'b':
      Serial.println("⬇️ มอเตอร์ถอยหลัง");
      break;
    case 'L':
    case 'l':
      Serial.println("⬅️ มอเตอร์เลี้ยวซ้าย");
      break;
    case 'R':
    case 'r':
      Serial.println("➡️ มอเตอร์เลี้ยวขวา");
      break;
    case 'S':
    case 's':
      Serial.println("⏹️ มอเตอร์หยุด");
      break;
    default:
      Serial.println("❌ คำสั่งไม่ถูกต้อง");
      break;
  }
  Serial.println();
  
  // ===== ตัวอย่าง 5: จำแนกเดือน (กรณีหลาย case ทำงานเหมือนกัน) =====
  Serial.println("----- ตัวอย่าง 5: จำนวนวันในเดือน -----");
  int month = 2;
  int daysInMonth;
  Serial.print("เดือนที่ ");
  Serial.println(month);
  
  switch (month) {
    case 1:   // มกราคม
    case 3:   // มีนาคม
    case 5:   // พฤษภาคม
    case 7:   // กรกฎาคม
    case 8:   // สิงหาคม
    case 10:  // ตุลาคม
    case 12:  // ธันวาคม
      daysInMonth = 31;
      break;
    case 4:   // เมษายน
    case 6:   // มิถุนายน
    case 9:   // กันยายน
    case 11:  // พฤศจิกายน
      daysInMonth = 30;
      break;
    case 2:   // กุมภาพันธ์
      daysInMonth = 28;  // ไม่นับปีอธิกสุรทิน
      break;
    default:
      daysInMonth = 0;
      Serial.println("เดือนไม่ถูกต้อง");
      break;
  }
  
  if (daysInMonth > 0) {
    Serial.print("จำนวนวัน: ");
    Serial.println(daysInMonth);
  }
  Serial.println();
  
  // ===== ตัวอย่าง 6: ระดับเสียง =====
  Serial.println("----- ตัวอย่าง 6: ปรับระดับเสียง -----");
  int volumeLevel = 3;
  Serial.print("ระดับเสียง: ");
  Serial.println(volumeLevel);
  
  switch (volumeLevel) {
    case 0:
      Serial.println("🔇 เงียบ (Mute)");
      break;
    case 1:
      Serial.println("🔈 เบา (25%)");
      break;
    case 2:
      Serial.println("🔉 ปานกลาง (50%)");
      break;
    case 3:
      Serial.println("🔊 ดัง (75%)");
      break;
    case 4:
      Serial.println("📢 ดังมาก (100%)");
      break;
    default:
      Serial.println("❌ ระดับไม่ถูกต้อง (0-4)");
      break;
  }
  Serial.println();
  
  // ===== ตัวอย่าง 7: โหมดการทำงาน =====
  Serial.println("----- ตัวอย่าง 7: โหมดเซ็นเซอร์ -----");
  int sensorMode = 1;
  Serial.print("โหมด: ");
  Serial.println(sensorMode);
  
  switch (sensorMode) {
    case 0:
      Serial.println("โหมด: ปิดการทำงาน");
      Serial.println("อัตราการอ่าน: ไม่อ่าน");
      break;
    case 1:
      Serial.println("โหมด: อ่านช้า");
      Serial.println("อัตราการอ่าน: ทุก 5 วินาที");
      break;
    case 2:
      Serial.println("โหมด: อ่านปกติ");
      Serial.println("อัตราการอ่าน: ทุก 1 วินาที");
      break;
    case 3:
      Serial.println("โหมด: อ่านเร็ว");
      Serial.println("อัตราการอ่าน: ทุก 100 มิลลิวินาที");
      break;
    default:
      Serial.println("โหมดไม่รู้จัก");
      break;
  }
  Serial.println();
  
  // ===== ตัวอย่าง 8: ไม่มี break (Fall-through) =====
  Serial.println("----- ตัวอย่าง 8: Fall-through (ไม่มี break) -----");
  int number = 2;
  Serial.print("ตัวเลข: ");
  Serial.println(number);
  Serial.println("ข้อความที่แสดง:");
  
  switch (number) {
    case 1:
      Serial.println("  - หนึ่ง");
      // ไม่มี break จะทำต่อไปยัง case ถัดไป
    case 2:
      Serial.println("  - สอง (หรือมากกว่า)");
      // ไม่มี break
    case 3:
      Serial.println("  - สาม (หรือมากกว่า)");
      break;  // หยุดที่นี่
    default:
      Serial.println("  - อื่นๆ");
  }
  Serial.println("(หมายเหตุ: เนื่องจากไม่มี break ที่ case 1 และ 2)");
  Serial.println();
  
  // ===== ตัวอย่าง 9: เปรียบเทียบ switch vs if-else =====
  Serial.println("----- ตัวอย่าง 9: เปรียบเทียบ switch vs if-else -----");
  int value = 3;
  
  // ใช้ switch-case
  Serial.println("ใช้ switch-case:");
  switch (value) {
    case 1: Serial.println("  ค่าเท่ากับ 1"); break;
    case 2: Serial.println("  ค่าเท่ากับ 2"); break;
    case 3: Serial.println("  ค่าเท่ากับ 3"); break;
    default: Serial.println("  ค่าอื่นๆ"); break;
  }
  
  // ใช้ if-else (ทำงานเหมือนกัน แต่ยาวกว่า)
  Serial.println("ใช้ if-else (ผลเหมือนกัน):");
  if (value == 1) {
    Serial.println("  ค่าเท่ากับ 1");
  } else if (value == 2) {
    Serial.println("  ค่าเท่ากับ 2");
  } else if (value == 3) {
    Serial.println("  ค่าเท่ากับ 3");
  } else {
    Serial.println("  ค่าอื่นๆ");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 10: State Machine (เครื่องสถานะ) =====
  Serial.println("----- ตัวอย่าง 10: State Machine -----");
  enum State { IDLE, RUNNING, PAUSED, STOPPED };
  State currentState = RUNNING;
  
  Serial.print("สถานะปัจจุบัน: ");
  Serial.println(currentState);
  
  switch (currentState) {
    case IDLE:
      Serial.println("→ พร้อมใช้งาน (Idle)");
      Serial.println("   รอคำสั่งเริ่มทำงาน");
      break;
    case RUNNING:
      Serial.println("→ กำลังทำงาน (Running)");
      Serial.println("   ระบบกำลังประมวลผล");
      break;
    case PAUSED:
      Serial.println("→ หยุดชั่วคราว (Paused)");
      Serial.println("   สามารถกลับมาทำงานต่อได้");
      break;
    case STOPPED:
      Serial.println("→ หยุดทำงาน (Stopped)");
      Serial.println("   ต้องเริ่มใหม่");
      break;
    default:
      Serial.println("→ สถานะไม่ทราบ");
      break;
  }
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
  Serial.println();
  Serial.println("สรุป:");
  Serial.println("- switch-case เหมาะสำหรับตรวจสอบค่าที่เป็นตัวเลขหรืออักขระ");
  Serial.println("- ใช้ break เพื่อหยุดการทำงานและออกจาก switch");
  Serial.println("- ถ้าไม่มี break จะทำงานต่อไปยัง case ถัดไป (fall-through)");
  Serial.println("- default คือกรณีที่ไม่ตรงกับ case ใดๆ");
  Serial.println("- อ่านง่ายกว่า if-else ซ้อนหลายชั้น");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
  
  // หมายเหตุ: switch-case มักใช้ใน loop() สำหรับ:
  // - State Machine (เครื่องสถานะ)
  // - จัดการคำสั่งจาก Serial
  // - ควบคุมโหมดการทำงานต่างๆ
  // - เมนูเลือกฟังก์ชัน
}
