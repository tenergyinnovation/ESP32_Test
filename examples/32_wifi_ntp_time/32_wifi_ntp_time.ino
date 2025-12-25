/*
 * ตัวอย่างโปรแกรม: WiFi Connection with NTP Time
 * =====================================================
 * โปรแกรมนี้สาธิตการเชื่อมต่อ WiFi network และดึงค่าเวลาปัจจุบันจาก NTP server
 * พร้อมแสดงผลเวลาในประเทศไทย (UTC+7) ทุกๆ 5 วินาที
 * 
 * การทำงาน:
 * 1. เชื่อมต่อกับ WiFi network (SSID: TENERGYINNOVATION)
 * 2. ระหว่างการเชื่อมต่อ LED สีน้ำเงินจะกระพริบเร็ว (100ms)
 * 3. หลังเชื่อมต่อสำเร็จ LED สีน้ำเงินจะกระพริบช้า (1 วินาที)
 * 4. ดึงค่าเวลาจาก NTP server "pool.ntp.org"
 * 5. แสดงผลเวลาปัจจุบันในประเทศไทย (UTC+7) ทุกๆ 5 วินาที
 * 6. รูปแบบการแสดงผล: "YYYY-MM-DD HH:MM:SS"
 * 
 * อุปกรณ์ที่ใช้:
 * - ESP32 Development Board
 * - ESP32_IOT Board (Blue LED Module)
 * 
 * ไลบรารีที่ใช้:
 * - WiFi.h          : สำหรับเชื่อมต่อ WiFi
 * - time.h          : สำหรับจัดการเวลาและ NTP
 * - esp32_iot.h     : สำหรับควบคุม Blue LED
 */

#include <WiFi.h>
#include <time.h>
#include <esp32_iot.h>

// ========================================
// WiFi Configuration
// ========================================
const char* ssid = "TENERGYINNOVATION";          // ชื่อ WiFi network
const char* password = "L0vemel0vemydog";        // รหัสผ่าน WiFi

// ========================================
// NTP Configuration
// ========================================
const char* ntpServer = "pool.ntp.org";          // NTP server address
const long gmtOffset_sec = 7 * 3600;             // UTC+7 สำหรับประเทศไทย (7 ชั่วโมง * 3600 วินาที)
const int daylightOffset_sec = 0;                // ไม่มี daylight saving time

// ========================================
// Timing Variables
// ========================================
unsigned long previousMillis = 0;                // เก็บเวลาล่าสุดที่แสดงผล
const long interval = 5000;                      // แสดงผลทุกๆ 5 วินาที (5000ms)

// ========================================
// ESP32_IOT Object
// ========================================
esp32_iot board;

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
  board.tickBlueLED(0.1);
  
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
  Serial.print("Subnet Mask   : ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP    : ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS Server    : ");
  Serial.println(WiFi.dnsIP());
  Serial.println("========================================\n");
  
  // เปลี่ยน Blue LED ให้กระพริบช้า (1 วินาที)
  board.tickBlueLED(1.0);
}

// ========================================
// Function: Initialize NTP Time
// ========================================
void initNTPTime() {
  Serial.println("========================================");
  Serial.println("กำลังดึงเวลาจาก NTP Server...");
  Serial.print("NTP Server: ");
  Serial.println(ntpServer);
  Serial.println("========================================");
  
  // กำหนดค่า NTP server และ timezone
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  // รอให้ได้เวลาจาก NTP server
  struct tm timeinfo;
  int attempts = 0;
  while (!getLocalTime(&timeinfo)) {
    Serial.print(".");
    delay(1000);
    attempts++;
    
    if (attempts >= 10) {
      Serial.println("\nไม่สามารถดึงเวลาจาก NTP Server ได้");
      Serial.println("กรุณาตรวจสอบการเชื่อมต่ออินเทอร์เน็ต");
      return;
    }
  }
  
  Serial.println("\n✓ ดึงเวลาจาก NTP Server สำเร็จ!");
  Serial.println("========================================\n");
}

// ========================================
// Function: Display Current Time
// ========================================
void displayTime() {
  struct tm timeinfo;
  
  // ดึงเวลาปัจจุบัน
  if (!getLocalTime(&timeinfo)) {
    Serial.println("ไม่สามารถอ่านค่าเวลาได้");
    return;
  }
  
  // จัดรูปแบบเวลาเป็น "YYYY-MM-DD HH:MM:SS"
  char timeString[25];
  strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &timeinfo);
  
  // แสดงผลเวลาปัจจุบัน
  Serial.print("เวลาปัจจุบัน (UTC+7): ");
  Serial.println(timeString);
  
  // แสดงข้อมูลเพิ่มเติม
  Serial.print("วันที่: ");
  Serial.print(timeinfo.tm_mday);
  Serial.print("/");
  Serial.print(timeinfo.tm_mon + 1);  // เดือนเริ่มจาก 0
  Serial.print("/");
  Serial.print(timeinfo.tm_year + 1900);  // ปี เริ่มจาก 1900
  
  Serial.print(" | เวลา: ");
  Serial.print(timeinfo.tm_hour);
  Serial.print(":");
  Serial.print(timeinfo.tm_min);
  Serial.print(":");
  Serial.println(timeinfo.tm_sec);
  
  // แสดงข้อมูล WiFi
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.print(" | RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.print(" dBm");
  
  // แสดงคุณภาพสัญญาณ
  int rssi = WiFi.RSSI();
  if (rssi > -50) {
    Serial.println(" (สัญญาณดีเยี่ยม)");
  } else if (rssi > -60) {
    Serial.println(" (สัญญาณดี)");
  } else if (rssi > -70) {
    Serial.println(" (สัญญาณปานกลาง)");
  } else if (rssi > -80) {
    Serial.println(" (สัญญาณอ่อน)");
  } else {
    Serial.println(" (สัญญาณอ่อนมาก)");
  }
  
  Serial.println("----------------------------------------");
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
  Serial.println("  WiFi NTP Time Example");
  Serial.println("  ESP32 IoT Board");
  Serial.println("========================================\n");
  
  // เริ่มต้น ESP32_IOT board
  board.begin();
  Serial.println("✓ เริ่มต้น ESP32_IOT board สำเร็จ");
  
  // เชื่อมต่อ WiFi
  connectWiFi();
  
  // เริ่มต้น NTP time
  initNTPTime();
  
  // แสดงเวลาครั้งแรก
  displayTime();
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
    
    // เปลี่ยน LED ให้กระพริบเร็ว
    board.tickBlueLED(0.1);
    
    // พยายามเชื่อมต่อใหม่
    connectWiFi();
    
    // เริ่มต้น NTP time ใหม่
    initNTPTime();
  }
  
  // อ่านเวลาปัจจุบัน
  unsigned long currentMillis = millis();
  
  // ตรวจสอบว่าครบ 5 วินาทีหรือยัง
  if (currentMillis - previousMillis >= interval) {
    // บันทึกเวลาล่าสุด
    previousMillis = currentMillis;
    
    // แสดงผลเวลาปัจจุบัน
    displayTime();
  }
}
