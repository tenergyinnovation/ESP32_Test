/***********************************************************************
 * โปรแกรมตัวอย่าง: อ่านค่าอุณหภูมิและความชื้นจาก DHT22 แล้วแสดงผลบนจอ TM1638
 * 
 * รายละเอียด:
 * - อ่านค่าอุณหภูมิและความชื้นจาก DHT22 sensor module (GPIO 14)
 * - แสดงผลอุณหภูมิที่หลัก 1-4 ของจอ TM1638 (ตัวเลข 4 หลักแรก)
 * - แสดงผลความชื้นที่หลัก 5-8 ของจอ TM1638 (ตัวเลข 4 หลักหลัง)
 * - อัพเดทค่าทุกๆ 2 วินาที
 * 
 * การต่อฮาร์ดแวร์:
 * - DHT22 VCC -> 3.3V
 * - DHT22 GND -> GND
 * - DHT22 DATA -> GPIO 14 (ต่อ Pull-up resistor 4.7K ohm ไปยัง VCC)
 * - TM1638 CLK -> GPIO 19
 * - TM1638 DIO -> GPIO 18
 * - TM1638 STB -> GPIO 23
 * 
 * ตัวอย่างการแสดงผลบนจอ: [28.5][65.2]
 * หลัก 1-4 แสดงอุณหภูมิ: 28.5°C
 * หลัก 5-8 แสดงความชื้น: 65.2%
 * 
 * Author: Tenergy Innovation Co., Ltd.
 * Date: 25 Dec 2025
 ***********************************************************************/

#include <esp32_iot.h>  // ไลบรารีสำหรับควบคุมบอร์ด ESP32 IoT
#include <DHT.h>         // ไลบรารีสำหรับอ่านค่า DHT sensor

// กำหนดพินและประเภทของ DHT sensor
#define DHT_PIN 14       // พินที่ต่อกับ DHT22 (ตาม diagram.json)
#define DHT_TYPE DHT22   // ประเภทเซ็นเซอร์ DHT22 (AM2302)

// สร้าง object สำหรับควบคุมบอร์ด ESP32 IoT
esp32_iot board;

// สร้าง object สำหรับควบคุม DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// ตัวแปรสำหรับจับเวลา
unsigned long previousMillis = 0;  // เก็บเวลาที่อ่านค่าครั้งล่าสุด
const long interval = 2000;         // ช่วงเวลาในการอัพเดท (2000 ms = 2 วินาที)

// ฟังก์ชันสำหรับแสดงผลบนจอ TM1638 (อุณหภูมิ 4 หลักแรก + ความชื้น 4 หลักหลัง)
void displayTempHumidity(float temperature, float humidity) {
  // แปลงค่าอุณหภูมิและความชื้นเป็น integer เพื่อแสดงผล
  int temp_int = (int)(temperature * 10);  // คูณ 10 เพื่อให้มีทศนิยม 1 ตำแหน่ง เช่น 28.5 -> 285
  int humid_int = (int)(humidity * 10);     // คูณ 10 เพื่อให้มีทศนิยม 1 ตำแหน่ง เช่น 65.2 -> 652
  
  // แสดงผลบนจอ TM1638 โดยใช้ฟังก์ชัน tm1638_number(หลัก5-8, หลัก1-4)
  // หลัก 1-4: อุณหภูมิ, หลัก 5-8: ความชื้น
  board.tm1638_number(humid_int, temp_int);
}

void setup() {
  // เริ่มต้น Serial สำหรับแสดงผลข้อมูลทาง Serial Monitor
  Serial.begin(115200);
  Serial.println("===================================");
  Serial.println("DHT22 + TM1638 Display Example");
  Serial.println("===================================");
  
  // เริ่มต้นบอร์ด ESP32 IoT (ตั้งค่าพินต่างๆ)
  board.begin();
  
  // เริ่มต้น DHT sensor
  dht.begin();
  Serial.println("DHT22 Sensor เริ่มต้นแล้ว");
  
  // เริ่มต้น TM1638 module
  board.tm1638_begin();
  Serial.println("TM1638 Module เริ่มต้นแล้ว");
  
  // ตั้งความสว่างของจอ TM1638 (0-7)
  board.tm1638_setBrightness(5);
  
  // ล้างหน้าจอ TM1638
  board.tm1638_clear();
  
  Serial.println("กำลังอ่านค่าจาก DHT22...");
  Serial.println("");
}

void loop() {
  // ตรวจสอบว่าถึงเวลาอัพเดทค่าหรือยัง (ทุกๆ 2 วินาที)
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // บันทึกเวลาปัจจุบัน
    
    // อ่านค่าความชื้นจาก DHT22
    float humidity = dht.readHumidity();
    
    // อ่านค่าอุณหภูมิจาก DHT22 (°C)
    float temperature = dht.readTemperature();
    
    // ตรวจสอบว่าอ่านค่าได้หรือไม่
    if (isnan(humidity) || isnan(temperature)) {
      // ถ้าอ่านค่าไม่ได้ แสดงข้อความ Error
      Serial.println("Error: ไม่สามารถอ่านค่าจาก DHT sensor!");
      
      // แสดงข้อความ Error บนจอ TM1638 (แสดง "----")
      board.tm1638_clear();
      return;
    }
    
    // แสดงผลค่าที่อ่านได้ทาง Serial Monitor
    Serial.print("อุณหภูมิ: ");
    Serial.print(temperature, 1);  // แสดงทศนิยม 1 ตำแหน่ง
    Serial.print(" °C  |  ");
    Serial.print("ความชื้น: ");
    Serial.print(humidity, 1);     // แสดงทศนิยม 1 ตำแหน่ง
    Serial.println(" %");
    
    // แสดงผลบนจอ TM1638
    displayTempHumidity(temperature, humidity);
  }
}
