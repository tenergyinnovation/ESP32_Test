/*
 * ตัวอย่างโปรแกรม: WiFi PM2.5 API Display on TM1638
 * =====================================================
 * โปรแกรมนี้สาธิตการดึงข้อมูล PM2.5 จาก API server (AQICN - World Air Quality Index)
 * ของจังหวัดเชียงใหม่ แล้วนำมาแสดงผลบนจอ TM1638 module
 * 
 * การทำงาน:
 * 1. เชื่อมต่อกับ WiFi network (SSID: TENERGYINNOVATION)
 * 2. ดึงข้อมูล PM2.5 จาก AQICN API สำหรับเชียงใหม่
 * 3. แสดงค่า PM2.5 (µg/m³) บนจอ TM1638
 * 4. แสดงสถานะคุณภาพอากาศด้วย LED (เขียว/เหลือง/แดง)
 * 5. อัพเดทข้อมูลทุกๆ 5 นาที (API มีข้อจำกัดการเรียกใช้)
 * 
 * คุณภาพอากาศตาม PM2.5:
 * - 0-25   µg/m³ : ดีมาก (สีเขียว)
 * - 26-37  µg/m³ : ดี
 * - 38-50  µg/m³ : ปานกลาง (สีเหลือง)
 * - 51-90  µg/m³ : เริ่มมีผลกระทบต่อสุขภาพ
 * - 91+    µg/m³ : มีผลกระทบต่อสุขภาพ (สีแดง)
 * 
 * API ที่ใช้:
 * - AQICN (World Air Quality Index Project)
 * - URL: http://api.waqi.info/feed/chiang-mai/
 * - สมัคร API Token ฟรีได้ที่: https://aqicn.org/data-platform/token/
 * 
 * อุปกรณ์ที่ใช้:
 * - ESP32 Development Board
 * - ESP32_IOT Board (Blue LED Module)
 * - TM1638 Module (7-Segment Display และ LED)
 * 
 * ไลบรารีที่ใช้:
 * - WiFi.h          : สำหรับเชื่อมต่อ WiFi
 * - HTTPClient.h    : สำหรับ HTTP request
 * - ArduinoJson.h   : สำหรับ parse JSON response
 * - esp32_iot.h     : สำหรับควบคุม TM1638 และ LED
 * 
 * หมายเหตุ:
 * - ต้องติดตั้ง library "ArduinoJson" โดย Benoit Blanchon
 * - กรุณาสมัคร API Token ของคุณเองและแทนที่ใน API_TOKEN
 * - API มีข้อจำกัด 1000 requests/วัน สำหรับ token ฟรี
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "esp32_iot.h"

// ========================================
// WiFi Configuration
// ========================================
const char* ssid = "TENERGYINNOVATION";          // ชื่อ WiFi network
const char* password = "L0vemel0vemydog";        // รหัสผ่าน WiFi

// ========================================
// API Configuration
// ========================================
// ⚠️ กรุณาสมัคร API Token ของคุณเองที่ https://aqicn.org/data-platform/token/
const char* API_TOKEN = "demo";                  // แทนที่ด้วย token ของคุณเอง
const char* API_URL = "http://api.waqi.info/feed/chiang-mai/?token=";

// ========================================
// Timing Variables
// ========================================
unsigned long previousMillis = 0;                // เก็บเวลาล่าสุดที่อัพเดทข้อมูล
const long updateInterval = 300000;              // อัพเดททุกๆ 5 นาที (300000ms)
// const long updateInterval = 60000;            // ทดสอบ: อัพเดททุกๆ 1 นาที

// ========================================
// PM2.5 Data Variables
// ========================================
float pm25Value = 0.0;                           // ค่า PM2.5 ปัจจุบัน (µg/m³)
int aqiValue = 0;                                // ค่า AQI (Air Quality Index)
String lastUpdate = "";                          // เวลาอัพเดทล่าสุด
bool dataValid = false;                          // สถานะความถูกต้องของข้อมูล

// ========================================
// ESP32_IOT Object
// ========================================
ESP32_IOT board;

// ========================================
// Function: Connect to WiFi
// ========================================
void connectWiFi() {
  Serial.println("\n========================================");
  Serial.println("กำลังเชื่อมต่อ WiFi...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.println("========================================");
  
  // เริ่มต้นการเชื่อมต่อ WiFi
  WiFi.begin(ssid, password);
  
  // ตั้งค่า Blue LED ให้กระพริบเร็วระหว่างเชื่อมต่อ (100ms)
  board.tickBlueLED(100);
  
  int attempts = 0;
  
  // รอจนกว่าจะเชื่อมต่อสำเร็จ
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    
    // แสดงคำเตือนทุกๆ 30 ครั้ง (ประมาณ 15 วินาที)
    if (attempts % 30 == 0) {
      Serial.println();
      Serial.print("กำลังพยายามเชื่อมต่อ... (");
      Serial.print(attempts);
      Serial.println(" ครั้ง)");
    }
    
    // ถ้าเชื่อมต่อไม่สำเร็จหลังจาก 60 ครั้ง (30 วินาที)
    if (attempts >= 60) {
      Serial.println("\n❌ ไม่สามารถเชื่อมต่อ WiFi ได้");
      Serial.println("กรุณาตรวจสอบ SSID และ Password");
      return;
    }
  }
  
  // เชื่อมต่อสำเร็จ
  Serial.println("\n========================================");
  Serial.println("✓ เชื่อมต่อ WiFi สำเร็จ!");
  Serial.println("========================================");
  
  // แสดงข้อมูลการเชื่อมต่อ
  Serial.print("IP Address    : ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address   : ");
  Serial.println(WiFi.macAddress());
  Serial.print("RSSI          : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  Serial.println("========================================\n");
  
  // เปลี่ยน Blue LED ให้กระพริบช้า (1 วินาที)
  board.tickBlueLED(1000);
}

// ========================================
// Function: Get PM2.5 Level Description
// ========================================
String getPM25Level(float pm25) {
  if (pm25 <= 25) {
    return "ดีมาก";
  } else if (pm25 <= 37) {
    return "ดี";
  } else if (pm25 <= 50) {
    return "ปานกลาง";
  } else if (pm25 <= 90) {
    return "เริ่มมีผลกระทบ";
  } else {
    return "มีผลกระทบ";
  }
}

// ========================================
// Function: Update LED Status Based on PM2.5
// ========================================
void updateLEDStatus(float pm25) {
  // ปิด LED ทั้งหมดก่อน
  for (int i = 1; i <= 8; i++) {
    board.tm1638_led(i, false);
  }
  
  // แสดงสถานะด้วย LED bar graph
  int numLEDs = 0;
  
  if (pm25 <= 25) {
    // ดีมาก: LED 1-2 (สีเขียว)
    numLEDs = 2;
  } else if (pm25 <= 37) {
    // ดี: LED 1-3
    numLEDs = 3;
  } else if (pm25 <= 50) {
    // ปานกลาง: LED 1-4 (สีเหลือง)
    numLEDs = 4;
  } else if (pm25 <= 90) {
    // เริ่มมีผลกระทบ: LED 1-6
    numLEDs = 6;
  } else {
    // มีผลกระทบ: LED 1-8 (สีแดง)
    numLEDs = 8;
  }
  
  // เปิด LED ตามจำนวนที่คำนวณได้
  for (int i = 1; i <= numLEDs; i++) {
    board.tm1638_led(i, true);
  }
}

// ========================================
// Function: Fetch PM2.5 Data from API
// ========================================
bool fetchPM25Data() {
  // ตรวจสอบการเชื่อมต่อ WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ ไม่มีการเชื่อมต่อ WiFi");
    return false;
  }
  
  Serial.println("\n========================================");
  Serial.println("กำลังดึงข้อมูล PM2.5 จาก API...");
  Serial.println("========================================");
  
  // สร้าง URL สมบูรณ์
  String url = String(API_URL) + String(API_TOKEN);
  Serial.print("API URL: ");
  Serial.println(url);
  
  HTTPClient http;
  http.begin(url);
  
  // ส่ง HTTP GET request
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
    
    if (httpResponseCode == 200) {
      // อ่าน response body
      String payload = http.getString();
      Serial.println("\nJSON Response:");
      Serial.println(payload);
      
      // Parse JSON
      DynamicJsonDocument doc(2048);
      DeserializationError error = deserializeJson(doc, payload);
      
      if (error) {
        Serial.print("❌ JSON parsing failed: ");
        Serial.println(error.c_str());
        http.end();
        return false;
      }
      
      // ตรวจสอบสถานะ API
      String status = doc["status"];
      if (status != "ok") {
        Serial.println("❌ API returned error status");
        http.end();
        return false;
      }
      
      // ดึงข้อมูล PM2.5
      JsonObject data = doc["data"];
      
      // ดึงค่า AQI
      aqiValue = data["aqi"];
      
      // ดึงค่า PM2.5 จาก iaqi object
      if (data["iaqi"]["pm25"].isNull()) {
        Serial.println("⚠ ไม่พบข้อมูล PM2.5");
        // ใช้ค่า AQI แทน (โดยประมาณ)
        pm25Value = aqiValue * 0.5;  // ค่าประมาณจาก AQI
      } else {
        float pm25_v = data["iaqi"]["pm25"]["v"];
        // แปลงค่า AQI เป็น µg/m³ (โดยประมาณ)
        // สูตรนี้เป็นการประมาณค่าอย่างง่าย
        if (pm25_v <= 50) {
          pm25Value = pm25_v * 0.5;  // 0-50 AQI ≈ 0-25 µg/m³
        } else if (pm25_v <= 100) {
          pm25Value = 25 + (pm25_v - 50) * 0.26;  // 51-100 AQI ≈ 25-38 µg/m³
        } else if (pm25_v <= 150) {
          pm25Value = 38 + (pm25_v - 100) * 0.24;  // 101-150 AQI ≈ 38-50 µg/m³
        } else {
          pm25Value = 50 + (pm25_v - 150) * 0.4;  // 150+ AQI ≈ 50+ µg/m³
        }
      }
      
      // ดึงเวลาอัพเดทล่าสุด
      lastUpdate = data["time"]["s"].as<String>();
      
      // ดึงชื่อสถานี
      String cityName = data["city"]["name"];
      
      // แสดงข้อมูลที่ได้
      Serial.println("\n========================================");
      Serial.println("✓ ดึงข้อมูลสำเร็จ!");
      Serial.println("========================================");
      Serial.print("สถานี          : ");
      Serial.println(cityName);
      Serial.print("AQI            : ");
      Serial.println(aqiValue);
      Serial.print("PM2.5          : ");
      Serial.print(pm25Value, 1);
      Serial.println(" µg/m³");
      Serial.print("คุณภาพอากาศ   : ");
      Serial.println(getPM25Level(pm25Value));
      Serial.print("อัพเดทล่าสุด   : ");
      Serial.println(lastUpdate);
      Serial.println("========================================\n");
      
      dataValid = true;
      http.end();
      return true;
      
    } else {
      Serial.print("❌ HTTP Error: ");
      Serial.println(httpResponseCode);
    }
  } else {
    Serial.print("❌ Connection Error: ");
    Serial.println(httpResponseCode);
  }
  
  http.end();
  return false;
}

// ========================================
// Function: Display PM2.5 on TM1638
// ========================================
void displayPM25() {
  if (dataValid) {
    // แสดงค่า PM2.5 (ตัวเลข 4 หลักแรก)
    // รูปแบบ: XXXX (เช่น 35.2 แสดงเป็น 35)
    int displayValue = (int)pm25Value;
    board.tm1638_number(displayValue);
    
    // อัพเดทสถานะ LED ตามระดับ PM2.5
    updateLEDStatus(pm25Value);
    
    // แสดงข้อมูลใน Serial Monitor
    Serial.print("จอแสดงผล: PM2.5 = ");
    Serial.print(displayValue);
    Serial.print(" µg/m³ (");
    Serial.print(getPM25Level(pm25Value));
    Serial.println(")");
    
  } else {
    // แสดงข้อความ error
    board.tm1638_number(8888);  // แสดง "----" หรือ "8888" เพื่อบ่งบอกข้อผิดพลาด
    Serial.println("⚠ ไม่มีข้อมูล PM2.5");
  }
}

// ========================================
// Setup Function
// ========================================
void setup() {
  // เริ่มต้น Serial communication
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n");
  Serial.println("========================================");
  Serial.println("  WiFi PM2.5 API Display on TM1638");
  Serial.println("  Chiang Mai Air Quality Monitor");
  Serial.println("  ESP32 IoT Board");
  Serial.println("========================================\n");
  
  // เริ่มต้น ESP32_IOT board
  board.begin();
  Serial.println("✓ เริ่มต้น ESP32_IOT board สำเร็จ");
  
  // เริ่มต้น TM1638
  board.tm1638_begin();
  Serial.println("✓ เริ่มต้น TM1638 module สำเร็จ");
  
  // แสดงข้อความเริ่มต้นบนจอ
  board.tm1638_number(0);
  
  // เชื่อมต่อ WiFi
  connectWiFi();
  
  // ตรวจสอบว่าเชื่อมต่อ WiFi สำเร็จหรือไม่
  if (WiFi.status() == WL_CONNECTED) {
    // ดึงข้อมูล PM2.5 ครั้งแรก
    Serial.println("\n========================================");
    Serial.println("กำลังดึงข้อมูล PM2.5 ครั้งแรก...");
    Serial.println("========================================");
    
    if (fetchPM25Data()) {
      displayPM25();
    } else {
      Serial.println("❌ ไม่สามารถดึงข้อมูลได้");
      Serial.println("กรุณาตรวจสอบ:");
      Serial.println("1. การเชื่อมต่ออินเทอร์เน็ต");
      Serial.println("2. API Token (สมัครได้ที่ https://aqicn.org/data-platform/token/)");
      Serial.println("3. ชื่อเมืองในประเทศไทย (chiang-mai)");
    }
  }
  
  Serial.println("\n========================================");
  Serial.println("โปรแกรมพร้อมทำงาน");
  Serial.print("อัพเดทข้อมูลทุกๆ ");
  Serial.print(updateInterval / 60000);
  Serial.println(" นาที");
  Serial.println("========================================\n");
}

// ========================================
// Loop Function
// ========================================
void loop() {
  // ตรวจสอบการเชื่อมต่อ WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\n========================================");
    Serial.println("⚠ สัญญาณ WiFi ขาดหาย!");
    Serial.println("กำลังพยายามเชื่อมต่อใหม่...");
    Serial.println("========================================");
    
    // แสดง error บนจอ
    board.tm1638_number(8888);
    
    // เปลี่ยน LED ให้กระพริบเร็ว
    board.tickBlueLED(100);
    
    // พยายามเชื่อมต่อใหม่
    connectWiFi();
    
    // ถ้าเชื่อมต่อสำเร็จ ดึงข้อมูลใหม่
    if (WiFi.status() == WL_CONNECTED) {
      fetchPM25Data();
      displayPM25();
    }
  }
  
  // อ่านเวลาปัจจุบัน
  unsigned long currentMillis = millis();
  
  // ตรวจสอบว่าครบเวลาอัพเดทข้อมูลหรือยัง
  if (currentMillis - previousMillis >= updateInterval) {
    // บันทึกเวลาล่าสุด
    previousMillis = currentMillis;
    
    // ดึงข้อมูล PM2.5 ใหม่
    if (fetchPM25Data()) {
      displayPM25();
    }
  }
  
  // แสดงข้อมูลปัจจุบันทุกๆ 10 วินาที
  static unsigned long lastDisplayTime = 0;
  if (currentMillis - lastDisplayTime >= 10000) {
    lastDisplayTime = currentMillis;
    
    Serial.println("----------------------------------------");
    Serial.print("เวลาปัจจุบัน: ");
    Serial.print(currentMillis / 1000);
    Serial.println(" วินาที");
    
    if (dataValid) {
      Serial.print("PM2.5 ปัจจุบัน: ");
      Serial.print(pm25Value, 1);
      Serial.print(" µg/m³ (");
      Serial.print(getPM25Level(pm25Value));
      Serial.println(")");
    }
    
    // แสดงเวลาที่เหลือจนกว่าจะอัพเดทครั้งถัดไป
    unsigned long timeLeft = (updateInterval - (currentMillis - previousMillis)) / 1000;
    Serial.print("อัพเดทครั้งถัดไปใน: ");
    Serial.print(timeLeft / 60);
    Serial.print(" นาที ");
    Serial.print(timeLeft % 60);
    Serial.println(" วินาที");
    Serial.println("----------------------------------------");
  }
  
  delay(1000);  // หน่วงเวลา 1 วินาที
}
