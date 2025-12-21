/*
 * ===================================================================
 * ตัวอย่างการใช้งาน do-while Loop
 * ===================================================================
 * 
 * do-while loop คล้ายกับ while loop แต่มีความแตกต่างสำคัญคือ:
 * - do-while จะทำงานในบล็อก {} อย่างน้อย 1 ครั้งเสมอ
 * - จากนั้นจึงตรวจสอบเงื่อนไข ถ้าเป็นจริงจะทำซ้ำต่อ
 * - while loop อาจไม่ทำงานเลยถ้าเงื่อนไขเป็นเท็จตั้งแต่แรก
 * 
 * รูปแบบ:
 * do {
 *   // code to execute at least once
 * } while (condition);
 * 
 * ใช้เมื่อ: ต้องการให้โค้ดทำงานอย่างน้อย 1 ครั้ง 
 * แล้วจึงตรวจสอบเงื่อนไขว่าจะทำซ้ำหรือไม่
 * ===================================================================
 */

void setup() {
  // เริ่มต้น Serial Communication ที่ baud rate 115200
  Serial.begin(115200);
  
  // รอให้ Serial Port พร้อมใช้งาน
  delay(1000);
  
  Serial.println("===================================");
  Serial.println("do-while Loop Demo");
  Serial.println("===================================");
  Serial.println();
  
  // ===== ตัวอย่าง 1: เปรียบเทียบ while vs do-while =====
  Serial.println("----- ตัวอย่าง 1: เปรียบเทียบ while vs do-while -----");
  
  // while loop - ไม่ทำงานเลยถ้าเงื่อนไขเป็นเท็จตั้งแต่แรก
  Serial.println("while loop (เงื่อนไขเป็นเท็จตั้งแต่แรก):");
  int count1 = 10;
  while (count1 < 5) {
    Serial.println("ทำงานใน while");  // จะไม่ทำงาน
    count1++;
  }
  Serial.println("while loop ไม่ทำงานเลย");
  Serial.println();
  
  // do-while loop - ทำงานอย่างน้อย 1 ครั้ง ถึงแม้เงื่อนไขจะเป็นเท็จ
  Serial.println("do-while loop (เงื่อนไขเป็นเท็จตั้งแต่แรก):");
  int count2 = 10;
  do {
    Serial.println("ทำงานใน do-while");  // จะทำงาน 1 ครั้ง
    count2++;
  } while (count2 < 5);
  Serial.println("do-while ทำงาน 1 ครั้ง แล้วหยุด");
  Serial.println();
  
  // ===== ตัวอย่าง 2: นับเลข 1-5 =====
  Serial.println("----- ตัวอย่าง 2: นับเลข 1-5 ด้วย do-while -----");
  int counter = 1;
  do {
    Serial.print("Counter: ");
    Serial.println(counter);
    counter++;
  } while (counter <= 5);
  Serial.println();
  
  // ===== ตัวอย่าง 3: เมนูตัวเลือก (จำลอง) =====
  Serial.println("----- ตัวอย่าง 3: แสดงเมนู (จำลอง) -----");
  int menuChoice;
  int loopCount = 0;
  
  do {
    Serial.println("=== เมนู ===");
    Serial.println("1. เปิดไฟ");
    Serial.println("2. ปิดไฟ");
    Serial.println("3. ตั้งค่า");
    Serial.println("4. ออก");
    
    // จำลองการเลือก (ในการใช้งานจริงจะรอรับค่าจากผู้ใช้)
    menuChoice = loopCount + 1;
    loopCount++;
    
    Serial.print("เลือก: ");
    Serial.println(menuChoice);
    
    if (menuChoice == 1) {
      Serial.println("→ เปิดไฟแล้ว");
    } else if (menuChoice == 2) {
      Serial.println("→ ปิดไฟแล้ว");
    } else if (menuChoice == 3) {
      Serial.println("→ เข้าสู่โหมดตั้งค่า");
    }
    
    Serial.println();
    delay(500);
    
  } while (menuChoice != 4 && loopCount < 4);
  
  Serial.println("ออกจากโปรแกรม");
  Serial.println();
  
  // ===== ตัวอย่าง 4: ตรวจสอบค่าที่ป้อน (Validation) =====
  Serial.println("----- ตัวอย่าง 4: Validation ตรวจสอบค่า -----");
  int inputValue;
  int attempts = 0;
  
  do {
    // จำลองการรับค่าจากผู้ใช้
    inputValue = random(0, 15);
    attempts++;
    
    Serial.print("ครั้งที่ ");
    Serial.print(attempts);
    Serial.print(": ค่าที่ได้ = ");
    Serial.print(inputValue);
    
    if (inputValue < 1 || inputValue > 10) {
      Serial.println(" ❌ ค่าไม่ถูกต้อง! กรุณาป้อนค่า 1-10");
    } else {
      Serial.println(" ✅ ค่าถูกต้อง");
    }
    
  } while ((inputValue < 1 || inputValue > 10) && attempts < 5);
  
  Serial.println();
  
  // ===== ตัวอย่าง 5: อ่านเซ็นเซอร์จนได้ค่าที่ต้องการ =====
  Serial.println("----- ตัวอย่าง 5: อ่านเซ็นเซอร์อุณหภูมิ -----");
  float temperature;
  int readAttempts = 0;
  
  Serial.println("กำลังอ่านค่าอุณหภูมิ...");
  do {
    // จำลองการอ่านเซ็นเซอร์
    temperature = 15.0 + random(0, 200) / 10.0;  // สุ่มอุณหภูมิ 15-35 องศา
    readAttempts++;
    
    Serial.print("การอ่านครั้งที่ ");
    Serial.print(readAttempts);
    Serial.print(": ");
    Serial.print(temperature, 1);
    Serial.println(" °C");
    
    if (temperature < 20.0 || temperature > 30.0) {
      Serial.println("  ⚠️ อุณหภูมินอกช่วง กำลังอ่านใหม่...");
    }
    
    delay(300);
    
  } while ((temperature < 20.0 || temperature > 30.0) && readAttempts < 10);
  
  if (temperature >= 20.0 && temperature <= 30.0) {
    Serial.println("✅ ได้ค่าอุณหภูมิที่เหมาะสมแล้ว");
  } else {
    Serial.println("⏱️ หมดเวลาพยายาม ใช้ค่าสุดท้าย");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 6: นับถอยหลัง =====
  Serial.println("----- ตัวอย่าง 6: นับถอยหลัง 5-1 -----");
  int countdown = 5;
  do {
    Serial.print("⏰ ");
    Serial.println(countdown);
    countdown--;
    delay(500);
  } while (countdown > 0);
  Serial.println("🚀 Start!");
  Serial.println();
  
  // ===== ตัวอย่าง 7: คำนวณผลรวม =====
  Serial.println("----- ตัวอย่าง 7: บวกเลข 1+2+...+n -----");
  int n = 10;
  int sum = 0;
  int i = 1;
  
  Serial.print("คำนวณ 1+2+...+");
  Serial.println(n);
  
  do {
    sum += i;
    Serial.print(i);
    if (i < n) Serial.print(" + ");
    i++;
  } while (i <= n);
  
  Serial.print(" = ");
  Serial.println(sum);
  Serial.println();
  
  // ===== ตัวอย่าง 8: หาร GCD (Greatest Common Divisor) =====
  Serial.println("----- ตัวอย่าง 8: หา GCD ของ 48 และ 18 -----");
  int a = 48;
  int b = 18;
  int tempA = a;
  int tempB = b;
  
  Serial.print("หา GCD ของ ");
  Serial.print(a);
  Serial.print(" และ ");
  Serial.println(b);
  
  do {
    int remainder = tempA % tempB;
    Serial.print(tempA);
    Serial.print(" = ");
    Serial.print(tempB);
    Serial.print(" × ");
    Serial.print(tempA / tempB);
    Serial.print(" + ");
    Serial.println(remainder);
    
    tempA = tempB;
    tempB = remainder;
  } while (tempB != 0);
  
  Serial.print("GCD = ");
  Serial.println(tempA);
  Serial.println();
  
  // ===== ตัวอย่าง 9: เกมทายตัวเลข (จำลอง) =====
  Serial.println("----- ตัวอย่าง 9: เกมทายตัวเลข -----");
  int secretNumber = 7;
  int guess;
  int tries = 0;
  
  Serial.println("ทายตัวเลข 1-10");
  do {
    guess = random(1, 11);  // จำลองการทาย
    tries++;
    
    Serial.print("ครั้งที่ ");
    Serial.print(tries);
    Serial.print(": ทาย ");
    Serial.print(guess);
    
    if (guess < secretNumber) {
      Serial.println(" → น้อยเกินไป!");
    } else if (guess > secretNumber) {
      Serial.println(" → มากเกินไป!");
    } else {
      Serial.println(" → 🎉 ถูกต้อง!");
    }
    
    delay(400);
    
  } while (guess != secretNumber && tries < 10);
  
  if (guess == secretNumber) {
    Serial.print("ทายถูกใน ");
    Serial.print(tries);
    Serial.println(" ครั้ง");
  }
  Serial.println();
  
  // ===== ตัวอย่าง 10: ตรวจสอบรหัสผ่าน (จำลอง) =====
  Serial.println("----- ตัวอย่าง 10: ระบบตรวจสอบรหัสผ่าน -----");
  int correctPassword = 1234;
  int enteredPassword;
  int passwordAttempts = 0;
  int maxAttempts = 3;
  
  do {
    passwordAttempts++;
    enteredPassword = random(1000, 9999);  // จำลองการป้อนรหัส
    
    Serial.print("ครั้งที่ ");
    Serial.print(passwordAttempts);
    Serial.print(": ป้อนรหัส ");
    Serial.println(enteredPassword);
    
    if (enteredPassword == correctPassword) {
      Serial.println("✅ รหัสผ่านถูกต้อง - ยินดีต้อนรับ!");
      break;
    } else {
      Serial.print("❌ รหัสผ่านไม่ถูกต้อง ");
      if (passwordAttempts < maxAttempts) {
        Serial.print("(เหลืออีก ");
        Serial.print(maxAttempts - passwordAttempts);
        Serial.println(" ครั้ง)");
      }
    }
    
    delay(500);
    
  } while (passwordAttempts < maxAttempts);
  
  if (enteredPassword != correctPassword) {
    Serial.println("🔒 ระบบล็อค - พยายามเกินกำหนด");
  }
  Serial.println();
  
  Serial.println("===================================");
  Serial.println("จบการแสดงผล");
  Serial.println("===================================");
}

void loop() {
  // ไม่มีการทำงานใน loop()
  // เพราะเราแสดงผลครั้งเดียวใน setup() แล้ว
  
  // หมายเหตุ: do-while มักใช้เมื่อ:
  // - ต้องการให้โค้ดทำงานอย่างน้อย 1 ครั้งก่อนตรวจสอบเงื่อนไข
  // - รับค่าจากผู้ใช้และตรวจสอบความถูกต้อง (validation)
  // - แสดงเมนูและรอการเลือก
  // - ทำงานซ้ำจนกว่าจะได้ผลลัพธ์ที่ต้องการ
}
