/***********************************************************************
 * โปรแกรมตัวอย่าง: BH1750 Light Sensor + TM1638 Display
 * 
 * รายละเอียด:
 * - อ่านค่าความเข้มแสงจาก BH1750 sensor module (I2C)
 * - แสดงผลค่าความเข้มแสง (Lux) บนจอ TM1638 (8 หลัก)
 * - อัพเดทค่าทุกๆ 2 วินาที
 * - แสดงค่าผ่าน Serial Monitor พร้อมกัน
 * 
 * การต่อฮาร์ดแวร์:
 * - BH1750 VCC -> 3.3V
 * - BH1750 GND -> GND
 * - BH1750 SDA -> GPIO 21 (I2C SDA)
 * - BH1750 SCL -> GPIO 22 (I2C SCL)
 * - BH1750 ADDR -> GND (I2C address 0x23) หรือ 3.3V (address 0x5C)
 * - TM1638 CLK -> GPIO 19
 * - TM1638 DIO -> GPIO 18
 * - TM1638 STB -> GPIO 23
 * 
 * หมายเหตุ:
 * - BH1750 เป็นเซ็นเซอร์วัดความเข้มแสงดิจิทัล
 * - ช่วงการวัด: 1 - 65535 lux
 * - ความละเอียด: ± 20%
 * - I2C address เริ่มต้น: 0x23 (ADDR pin ต่อ GND)
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
// ADDR line HIGH:     I2C address 0x5C
BH1750 sensor(LOW);

void setup()
{
  // เริ่มต้น Serial สำหรับแสดงผลข้อมูลทาง Serial Monitor
  Serial.begin(115200);
  delay(100);
  Serial.println("=====================================");
  Serial.println(" BH1750 + TM1638 Light Sensor");
  Serial.println(" Light Intensity Measurement");
  Serial.println("=====================================");

  // เริ่มต้นบอร์ด ESP32 IoT (ตั้งค่าพินต่างๆ)
  board.begin();

  // เริ่มต้น I2C bus (SDA: GPIO21, SCL: GPIO22)
  Wire.begin();
  Serial.println("I2C Bus เริ่มต้นแล้ว");

  // เริ่มต้น BH1750 sensor
  // ModeOneTime: วัดค่าครั้งละครั้ง (ประหยัดพลังงาน)
  // ResolutionMid: ความละเอียดปานกลาง (1 lx)
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

  Serial.println("");
  Serial.println("กำลังอ่านค่าความเข้มแสง...");
  Serial.println("อัพเดทค่าทุกๆ 2 วินาที");
  Serial.println("=====================================");
  Serial.println("");
}

void loop()
{
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
    Serial.println(" lux");

    // แสดงผลค่าความเข้มแสงบนจอ TM1638 (8 หลัก)
    // ใช้ฟังก์ชัน tm1638_number() แสดงตัวเลข
    board.tm1638_number((long)lux);

    // ตรวจสอบระดับความเข้มแสงและแสดง LED บน TM1638 (LED 1-8)
    // ปิด LED ทั้งหมดก่อน
    for (int i = 1; i <= 8; i++) {
      board.tm1638_led(i, false);
    }

    // เปิด LED ตามระดับความเข้มแสง
    if (lux < 10) {
      // ความเข้มแสงต่ำมาก (< 10 lux): เปิด LED 1
      board.tm1638_led(1, true);
    }
    else if (lux < 50) {
      // ความเข้มแสงต่ำ (< 50 lux): เปิด LED 1-2
      for (int i = 1; i <= 2; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 100) {
      // ความเข้มแสงปานกลาง (< 100 lux): เปิด LED 1-3
      for (int i = 1; i <= 3; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 500) {
      // ความเข้มแสงค่อนข้างสว่าง (< 500 lux): เปิด LED 1-4
      for (int i = 1; i <= 4; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 1000) {
      // ความเข้มแสงสว่าง (< 1000 lux): เปิด LED 1-5
      for (int i = 1; i <= 5; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 5000) {
      // ความเข้มแสงสว่างมาก (< 5000 lux): เปิด LED 1-6
      for (int i = 1; i <= 6; i++) {
        board.tm1638_led(i, true);
      }
    }
    else if (lux < 10000) {
      // ความเข้มแสงสว่างมากๆ (< 10000 lux): เปิด LED 1-7
      for (int i = 1; i <= 7; i++) {
        board.tm1638_led(i, true);
      }
    }
    else {
      // ความเข้มแสงสว่างสุด (>= 10000 lux): เปิด LED 1-8
      for (int i = 1; i <= 8; i++) {
        board.tm1638_led(i, true);
      }
    }
  }
  else 
  {
    // ถ้าอ่านค่าไม่ได้ แสดงข้อความ Error
    Serial.println("Error: ไม่สามารถอ่านค่าจาก BH1750 sensor!");

    // แสดงข้อความ Error บนจอ TM1638 (ล้างจอ)
    board.tm1638_clear();
  }

  // หน่วงเวลา 2 วินาทีก่อนอ่านค่าใหม่
  delay(2000);
}
