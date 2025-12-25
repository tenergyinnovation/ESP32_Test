/***********************************************************************
 * โปรแกรมตัวอย่าง: BH1750 Light Sensor + TM1638 + Relay with Adjustable Threshold
 * 
 * รายละเอียด:
 * - อ่านค่าความเข้มแสงจาก BH1750 sensor module (I2C)
 * - แสดงผลค่าความเข้มแสง (Lux) บนจอ TM1638 (8 หลัก)
 * - อัพเดทค่าทุกๆ 2 วินาที
 * - ควบคุม Relay1 ตามค่าความเข้มแสง:
 *   * ถ้าความเข้มแสง < Threshold ให้เปิด Relay1 (เปิดไฟเสริม)
 *   * ถ้าความเข้มแสง >= Threshold ให้ปิด Relay1
 * - สามารถปรับค่า Threshold ได้ผ่านปุ่ม TM1638:
 *   * S1: เพิ่มค่า Threshold +10 lux
 *   * S2: ลดค่า Threshold -10 lux
 * - มีเสียงบี๊บเมื่อกดปุ่ม S1 หรือ S2
 * - แสดงค่า Threshold บนจอเมื่อปรับค่า
 * - แสดงค่าผ่าน Serial Monitor พร้อมกัน
 * 
 * การต่อฮาร์ดแวร์:
 * - BH1750 VCC -> 3.3V
 * - BH1750 GND -> GND
 * - BH1750 SDA -> GPIO 21 (I2C SDA)
 * - BH1750 SCL -> GPIO 22 (I2C SCL)
 * - BH1750 ADDR -> GND (I2C address 0x23)
 * - TM1638 CLK -> GPIO 19
 * - TM1638 DIO -> GPIO 18
 * - TM1638 STB -> GPIO 23
 * - Relay1 IN -> GPIO 25
 * - Relay1 VCC -> 5V
 * - Relay1 GND -> GND
 * 
 * การทำงาน:
 * - ระบบควบคุมแสงอัตโนมัติ
 * - เมื่อมืด (< Threshold) จะเปิด Relay1 เพื่อเปิดไฟเสริม
 * - เมื่อสว่างพอ (>= Threshold) จะปิด Relay1
 * - สามารถปรับค่า Threshold แบบ Real-time
 * - เหมาะสำหรับควบคุมไฟแสงสว่างอัตโนมัติ
 * 
 * Author: Tenergy Innovation Co., Ltd.
 * Date: 25 Dec 2025
 ***********************************************************************/

#include <Wire.h>            // ไลบรารีสำหรับ I2C communication
#include <ErriezBH1750.h>    // ไลบรารีสำหรับ BH1750 light sensor
#include <esp32_iot.h>       // ไลบรารีสำหรับควบคุมบอร์ด ESP32 IoT

// สร้าง object สำหรับควบคุมบอร์ด ESP32 IoT
esp32_iot board;

// สร้าง object สำหรับควบคุม BH1750 sensor
// ADDR line LOW/open: I2C address 0x23 (default)
BH1750 sensor(LOW);

// ตัวแปรสำหรับเก็บสถานะ Relay
bool relay1Status = false;

// ตัวแปรสำหรับเก็บค่า Threshold (เริ่มต้นที่ 100 lux)
int lightThreshold = 100;

// ตัวแปรสำหรับเก็บสถานะการกดปุ่ม
uint8_t lastButtonPressed = 0;
bool buttonPressed = false;

void setup()
{
  // เริ่มต้น Serial สำหรับแสดงผลข้อมูลทาง Serial Monitor
  Serial.begin(115200);
  delay(100);
  Serial.println("=====================================");
  Serial.println(" BH1750 + TM1638 + Relay Control");
  Serial.println(" Light Control System");
  Serial.println(" with Adjustable Threshold");
  Serial.println("=====================================");

  // เริ่มต้นบอร์ด ESP32 IoT (ตั้งค่าพินต่างๆ)
  board.begin();

  // เริ่มต้น I2C bus (SDA: GPIO21, SCL: GPIO22)
  Wire.begin();
  Serial.println("I2C Bus เริ่มต้นแล้ว");

  // เริ่มต้น BH1750 sensor
  sensor.begin(ModeOneTime, ResolutionMid);
  Serial.println("BH1750 Sensor เริ่มต้นแล้ว");
  Serial.println("I2C Address: 0x23");

  // เริ่มต้น TM1638 module
  board.tm1638_begin();
  Serial.println("TM1638 Module เริ่มต้นแล้ว");

  // ตั้งความสว่างของจอ TM1638 (0-7)
  board.tm1638_setBrightness(5);

  // ล้างหน้าจอ TM1638
  board.tm1638_clear();

  // ปิด Relay1 เริ่มต้น
  board.relay1_Off();
  relay1Status = false;
  Serial.println("Relay1 เริ่มต้น: ปิด");

  Serial.println("");
  Serial.println("กำลังอ่านค่าความเข้มแสง...");
  Serial.print("เกณฑ์การควบคุม: ");
  Serial.print(lightThreshold);
  Serial.println(" lux");
  Serial.println("- ความเข้มแสง < Threshold: เปิด Relay1");
  Serial.println("- ความเข้มแสง >= Threshold: ปิด Relay1");
  Serial.println("");
  Serial.println("การปรับค่า Threshold:");
  Serial.println("- S1: เพิ่ม Threshold +10 lux");
  Serial.println("- S2: ลด Threshold -10 lux");
  Serial.println("=====================================");
  Serial.println("");
}

void loop()
{
  // ตรวจสอบปุ่มกดบน TM1638 module
  uint8_t button = board.tm1638_button();

  // ถ้ามีปุ่มถูกกด
  if (button != 0) 
  {
    // ตรวจสอบว่าเป็นปุ่มใหม่หรือไม่ (เพื่อป้องกันการกดค้าง)
    if (button != lastButtonPressed) 
    {
      lastButtonPressed = button;
      buttonPressed = true;

      // ส่งเสียงบี๊บ 1 ครั้ง
      board.buzzer_beep(1, 100);

      // ปรับค่า Threshold ตามปุ่มที่กด
      if (button == 1) 
      {
        // S1: เพิ่ม Threshold
        lightThreshold += 10;
        // จำกัดค่าสูงสุดไม่เกิน 10000 lux
        if (lightThreshold > 10000) {
          lightThreshold = 10000;
        }
        Serial.print(">> S1 กด: Light Threshold = ");
        Serial.print(lightThreshold);
        Serial.println(" lux");
      }
      else if (button == 2) 
      {
        // S2: ลด Threshold
        lightThreshold -= 10;
        // จำกัดค่าต่ำสุดไม่ต่ำกว่า 0 lux
        if (lightThreshold < 0) {
          lightThreshold = 0;
        }
        Serial.print(">> S2 กด: Light Threshold = ");
        Serial.print(lightThreshold);
        Serial.println(" lux");
      }

      // แสดงค่า Threshold ปัจจุบันบนจอ TM1638
      board.tm1638_clear();
      board.tm1638_number((long)lightThreshold);

      // หน่วงเวลาเพื่อให้เห็นค่าที่จอ
      delay(1500);
    }
  }
  else 
  {
    // ถ้าไม่มีปุ่มถูกกด รีเซ็ตสถานะ
    lastButtonPressed = 0;
    buttonPressed = false;
  }

  // ถ้ามีปุ่มกดอยู่ ให้ข้ามการอ่านค่า BH1750 และการควบคุม Relay
  if (buttonPressed) {
    return;
  }

  // เริ่มการแปลงค่า (conversion) จาก BH1750
  sensor.startConversion();

  // รอให้การแปลงค่าเสร็จสมบูรณ์ (blocking mode)
  if (sensor.waitForCompletion()) 
  {
    // อ่านค่าความเข้มแสงจากเซ็นเซอร์ (หน่วย: lux)
    uint16_t lux = sensor.read();

    // แสดงผลค่าที่อ่านได้ทาง Serial Monitor
    Serial.print("ความเข้มแสง: ");
    Serial.print(lux);
    Serial.print(" lux  |  ");

    // แสดงสถานะ Relay1
    Serial.print("Relay1: ");
    if (relay1Status) {
      Serial.println("เปิด (ไฟเสริม)");
    } else {
      Serial.println("ปิด");
    }

    // แสดงผลค่าความเข้มแสงบนจอ TM1638 (8 หลัก)
    board.tm1638_number((long)lux);

    // ควบคุม Relay1 ตามความเข้มแสง
    if (lux < lightThreshold) 
    {
      // ถ้าความเข้มแสงต่ำกว่า Threshold ให้เปิด Relay1 (เปิดไฟเสริม)
      if (!relay1Status) 
      {
        board.relay1_On();
        relay1Status = true;
        Serial.print(">> Relay1: เปิด (มืด < ");
        Serial.print(lightThreshold);
        Serial.println(" lux)");
        Serial.println("=====================================");
      }
    }
    else 
    {
      // ถ้าความเข้มแสงสูงกว่าหรือเท่ากับ Threshold ให้ปิด Relay1
      if (relay1Status) 
      {
        board.relay1_Off();
        relay1Status = false;
        Serial.print(">> Relay1: ปิด (สว่างพอ >= ");
        Serial.print(lightThreshold);
        Serial.println(" lux)");
        Serial.println("=====================================");
      }
    }

    // แสดง LED บาร์กราฟบน TM1638 ตามระดับความเข้มแสง
    // ปิด LED ทั้งหมดก่อน
    for (int i = 1; i <= 8; i++) {
      board.tm1638_led(i, false);
    }

    // เปิด LED ตามระดับความเข้มแสง
    if (lux < 10) {
      board.tm1638_led(1, true);
    }
    else if (lux < 50) {
      for (int i = 1; i <= 2; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 100) {
      for (int i = 1; i <= 3; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 500) {
      for (int i = 1; i <= 4; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 1000) {
      for (int i = 1; i <= 5; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 5000) {
      for (int i = 1; i <= 6; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 10000) {
      for (int i = 1; i <= 7; i++) {
        board.tm1638_led(i, true);
      }
    }
    else {
      for (int i = 1; i <= 8; i++) {
        board.tm1638_led(i, true);
      }
    }
  }
  else 
  {
    // ถ้าอ่านค่าไม่ได้ แสดงข้อความ Error
    Serial.println("Error: ไม่สามารถอ่านค่าจาก BH1750 sensor!");
    board.tm1638_clear();
  }

  // หน่วงเวลา 2 วินาทีก่อนอ่านค่าใหม่
  delay(2000);
}
