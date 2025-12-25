/***********************************************************************
 * โปรแกรมตัวอย่าง: DHT22 + TM1638 + Relay Temperature Control with Adjustable Threshold
 * 
 * รายละเอียด:
 * - อ่านค่าอุณหภูมิและความชื้นจาก DHT22 sensor module (GPIO 14)
 * - แสดงผลอุณหภูมิที่หลัก 1-4 ของจอ TM1638
 * - แสดงผลความชื้นที่หลัก 5-8 ของจอ TM1638
 * - อัพเดทค่าทุกๆ 1 วินาที
 * - ควบคุม Relay1 ตามอุณหภูมิ:
 *   * ถ้าอุณหภูมิ > High Threshold ให้เปิด Relay1 (เปิดพัดลม/เครื่องปรับอากาศ)
 *   * ถ้าอุณหภูมิ < Low Threshold ให้ปิด Relay1
 *   * ระหว่าง Low-High Threshold คงสถานะเดิม (Hysteresis)
 * - สามารถปรับค่า Threshold ได้ผ่านปุ่ม TM1638:
 *   * S1: เพิ่ม High Threshold +1°C
 *   * S2: ลด High Threshold -1°C
 *   * S3: เพิ่ม Low Threshold +1°C
 *   * S4: ลด Low Threshold -1°C
 * - มีเสียงบี๊บเมื่อกดปุ่ม
 * - แสดงค่า Threshold บนจอเมื่อปรับค่า
 * - แสดงผลสถานะการเปิด-ปิด Relay1 ผ่านทาง Serial Monitor
 * 
 * การต่อฮาร์ดแวร์:
 * - DHT22 VCC -> 3.3V
 * - DHT22 GND -> GND
 * - DHT22 DATA -> GPIO 14 (ต่อ Pull-up resistor 4.7K ohm ไปยัง VCC)
 * - TM1638 CLK -> GPIO 19
 * - TM1638 DIO -> GPIO 18
 * - TM1638 STB -> GPIO 23
 * - Relay1 IN -> GPIO 25
 * - Relay1 VCC -> 5V
 * - Relay1 GND -> GND
 * 
 * การทำงาน:
 * - ระบบควบคุมอุณหภูมิแบบ Hysteresis
 * - ป้องกันการเปิด-ปิด relay บ่อยเกินไป
 * - สามารถปรับค่า Threshold แบบ Real-time
 * - เหมาะสำหรับควบคุมพัดลมหรือเครื่องปรับอากาศ
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

// ตัวแปรสำหรับเก็บสถานะ Relay
bool relay1Status = false;

// ตัวแปรสำหรับเก็บค่า Threshold (ใช้ตัวแปรแทน #define เพื่อให้สามารถปรับค่าได้)
float tempHighThreshold = 30.0;  // อุณหภูมิที่เปิด Relay (องศาเซลเซียส)
float tempLowThreshold = 25.0;   // อุณหภูมิที่ปิด Relay (องศาเซลเซียส)

// ตัวแปรสำหรับเก็บสถานะการกดปุ่ม
uint8_t lastButtonPressed = 0;   // เก็บปุ่มที่ถูกกดล่าสุด
bool buttonPressed = false;       // สถานะว่ามีปุ่มถูกกดอยู่หรือไม่

void setup() {
  // เริ่มต้น Serial สำหรับแสดงผลข้อมูลทาง Serial Monitor
  Serial.begin(115200);
  Serial.println("=====================================");
  Serial.println(" DHT22 + TM1638 + Relay Control");
  Serial.println(" Temperature Control System");
  Serial.println(" with Adjustable Threshold");
  Serial.println("=====================================");
  
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
  
  // ปิด Relay1 เริ่มต้น
  board.relay1_Off();
  relay1Status = false;
  Serial.println("Relay1 เริ่มต้น: ปิด");
  
  Serial.println("");
  Serial.println("กำลังอ่านค่าจาก DHT22...");
  Serial.println("เกณฑ์การควบคุม:");
  Serial.print("- อุณหภูมิ > ");
  Serial.print(tempHighThreshold, 0);
  Serial.println("°C : เปิด Relay1");
  Serial.print("- อุณหภูมิ < ");
  Serial.print(tempLowThreshold, 0);
  Serial.println("°C : ปิด Relay1");
  Serial.println("");
  Serial.println("การปรับค่า Threshold:");
  Serial.println("- S1: เพิ่ม High Threshold +1°C");
  Serial.println("- S2: ลด High Threshold -1°C");
  Serial.println("- S3: เพิ่ม Low Threshold +1°C");
  Serial.println("- S4: ลด Low Threshold -1°C");
  Serial.println("=====================================");
  Serial.println("");
}

void loop() {
  // ตรวจสอบปุ่มกดบน TM1638 module
  uint8_t button = board.tm1638_button();
  
  // ถ้ามีปุ่มถูกกด
  if (button != 0) {
    // ตรวจสอบว่าเป็นปุ่มใหม่หรือไม่ (เพื่อป้องกันการกดค้าง)
    if (button != lastButtonPressed) {
      lastButtonPressed = button;
      buttonPressed = true;
      
      // ส่งเสียงบี๊บ 1 ครั้ง
      board.buzzer_beep(1, 100);
      
      // ปรับค่า Threshold ตามปุ่มที่กด
      if (button == 1) {
        // S1: เพิ่ม High Threshold
        tempHighThreshold += 1.0;
        Serial.print(">> S1 กด: High Threshold = ");
        Serial.print(tempHighThreshold, 0);
        Serial.println("°C");
      }
      else if (button == 2) {
        // S2: ลด High Threshold
        tempHighThreshold -= 1.0;
        // ป้องกันไม่ให้ต่ำกว่า Low Threshold
        if (tempHighThreshold < tempLowThreshold) {
          tempHighThreshold = tempLowThreshold;
        }
        Serial.print(">> S2 กด: High Threshold = ");
        Serial.print(tempHighThreshold, 0);
        Serial.println("°C");
      }
      else if (button == 3) {
        // S3: เพิ่ม Low Threshold
        tempLowThreshold += 1.0;
        // ป้องกันไม่ให้สูงกว่า High Threshold
        if (tempLowThreshold > tempHighThreshold) {
          tempLowThreshold = tempHighThreshold;
        }
        Serial.print(">> S3 กด: Low Threshold = ");
        Serial.print(tempLowThreshold, 0);
        Serial.println("°C");
      }
      else if (button == 4) {
        // S4: ลด Low Threshold
        tempLowThreshold -= 1.0;
        Serial.print(">> S4 กด: Low Threshold = ");
        Serial.print(tempLowThreshold, 0);
        Serial.println("°C");
      }
      
      // แสดงค่า Threshold ปัจจุบันบนจอ TM1638
      // หลัก 1-4: Low Threshold, หลัก 5-8: High Threshold
      board.tm1638_clear();
      board.tm1638_number(tempHighThreshold, tempLowThreshold);
      
      // หน่วงเวลาเพื่อให้เห็นค่าที่จอ
      delay(1500);
    }
  }
  else {
    // ถ้าไม่มีปุ่มถูกกด รีเซ็ตสถานะ
    lastButtonPressed = 0;
    buttonPressed = false;
  }
  
  // ถ้ามีปุ่มกดอยู่ ให้ข้ามการอ่านค่า DHT22 และการควบคุม Relay
  if (buttonPressed) {
    return;
  }
  
  // อ่านค่าความชื้นจาก DHT22
  float humidity = dht.readHumidity();
  
  // อ่านค่าอุณหภูมิจาก DHT22 (°C)
  float temperature = dht.readTemperature();
  
  // ตรวจสอบว่าอ่านค่าได้หรือไม่
  if (isnan(humidity) || isnan(temperature)) {
    // ถ้าอ่านค่าไม่ได้ แสดงข้อความ Error
    Serial.println("Error: ไม่สามารถอ่านค่าจาก DHT sensor!");
    
    // แสดงข้อความ Error บนจอ TM1638 (ล้างจอ)
    board.tm1638_clear();
    
    // หน่วงเวลา 2 วินาทีก่อนอ่านค่าใหม่
    delay(2000);
    return;
  }
  
  // แสดงผลค่าที่อ่านได้ทาง Serial Monitor
  Serial.print("อุณหภูมิ: ");
  Serial.print(temperature, 1);  // แสดงทศนิยม 1 ตำแหน่ง
  Serial.print(" °C  |  ");
  Serial.print("ความชื้น: ");
  Serial.print(humidity, 1);     // แสดงทศนิยม 1 ตำแหน่ง
  Serial.print(" %  |  ");
  
  // แสดงสถานะ Relay1
  Serial.print("Relay1: ");
  if (relay1Status) {
    Serial.println("เปิด");
  } else {
    Serial.println("ปิด");
  }
  
  
  // แสดงผลบนจอ TM1638 โดยใช้ฟังก์ชัน tm1638_number(หลัก5-8, หลัก1-4)
  // หลัก 1-4: อุณหภูมิ, หลัก 5-8: ความชื้น
  board.tm1638_number(humidity, temperature);
  
  // ควบคุม Relay1 ตามอุณหภูมิ
  // ตรวจสอบอุณหภูมิและควบคุม Relay1
  if (temperature > tempHighThreshold) {
    // ถ้าอุณหภูมิสูงกว่า High Threshold ให้เปิด Relay1
    if (!relay1Status) {  // ถ้า Relay ยังไม่เปิด
      board.relay1_On();
      relay1Status = true;
      Serial.print(">> Relay1: เปิด (อุณหภูมิสูงกว่า ");
      Serial.print(tempHighThreshold, 0);
      Serial.println("°C)");
      Serial.println("=====================================");
    }
  } 
  else if (temperature < tempLowThreshold) {
    // ถ้าอุณหภูมิต่ำกว่า Low Threshold ให้ปิด Relay1
    if (relay1Status) {  // ถ้า Relay ยังเปิดอยู่
      board.relay1_Off();
      relay1Status = false;
      Serial.print(">> Relay1: ปิด (อุณหภูมิต่ำกว่า ");
      Serial.print(tempLowThreshold, 0);
      Serial.println("°C)");
      Serial.println("=====================================");
    }
  }
  // ถ้าอุณหภูมิอยู่ระหว่าง Low และ High Threshold ให้คงสถานะเดิม (Hysteresis)
  // ไม่ทำอะไร เพื่อป้องกันการเปิด-ปิด relay บ่อยเกินไป
  
  // หน่วงเวลา 1 วินาทีก่อนอ่านค่าใหม่
  delay(1000);
}
