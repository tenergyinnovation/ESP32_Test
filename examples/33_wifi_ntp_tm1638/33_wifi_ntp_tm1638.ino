/*
 * ตัวอย่างโปรแกรม: WiFi NTP Time Display on TM1638
 * =====================================================
 * โปรแกรมนี้สาธิตการเชื่อมต่อ WiFi network และดึงค่าเวลาปัจจุบันจาก NTP server
 * พร้อมแสดงผลเวลาและวันที่บนจอ TM1638 module สลับกันทุกๆ 5 วินาที
 * 
 * การทำงาน:
 * 1. เชื่อมต่อกับ WiFi network (SSID: TENERGYINNOVATION)
 * 2. ระหว่างการเชื่อมต่อ LED สีน้ำเงินจะกระพริบเร็ว (100ms)
 * 3. หลังเชื่อมต่อสำเร็จ LED สีน้ำเงินจะกระพริบช้า (1 วินาที)
 * 4. ดึงค่าเวลาจาก NTP server "pool.ntp.org"
 * 5. แสดงผลเวลา (HH:MM:SS) บนจอ TM1638 เป็นเวลา 10 วินาที
 * 6. แสดงผลวันที่ (DD-MM-YY) บนจอ TM1638 เป็นเวลา 10 วินาที
 * 7. สลับการแสดงผลระหว่างเวลาและวันที่ต่อไปเรื่อยๆ
 * 8. เวลาที่แสดงเป็นเวลาในประเทศไทย (UTC+7)
 * 
 * อุปกรณ์ที่ใช้:
 * - ESP32 Development Board
 * - ESP32_IOT Board (Blue LED Module)
 * - TM1638 Module (7-Segment Display)
 * 
 * ไลบรารีที่ใช้:
 * - WiFi.h          : สำหรับเชื่อมต่อ WiFi
 * - time.h          : สำหรับจัดการเวลาและ NTP
 * - esp32_iot.h     : สำหรับควบคุม Blue LED และ TM1638
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
// Display Mode Variables
// ========================================
bool displayMode = true;                         // true = แสดงเวลา, false = แสดงวันที่
unsigned long previousMillis = 0;                // เก็บเวลาล่าสุดที่สลับโหมด
const long switchInterval = 10000;                // สลับโหมดทุกๆ 10 วินาที (10000ms)

unsigned long previousUpdateMillis = 0;          // เก็บเวลาล่าสุดที่อัพเดทข้อมูล
const long updateInterval = 1000;                // อัพเดทข้อมูลทุกๆ 1 วินาที

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
// Function: Update Display
// ========================================
void updateDisplay() {
  struct tm timeinfo;
  
  // ดึงเวลาปัจจุบัน
  if (!getLocalTime(&timeinfo)) {
    Serial.println("ไม่สามารถอ่านค่าเวลาได้");
    board.tm1638_number(88888888);  // แสดง "88888888" เมื่อเกิดข้อผิดพลาด
    return;
  }
  
  if (displayMode) {
    // โหมดแสดงเวลา (HH:MM:SS)
    int hour = timeinfo.tm_hour;
    int minute = timeinfo.tm_min;
    int second = timeinfo.tm_sec;
    
    // แสดงเวลาบนจอ TM1638
    board.tm1638_time(hour, minute, second);
    
    // แสดงผลใน Serial Monitor
    Serial.print("เวลา: ");
    if (hour < 10) Serial.print("0");
    Serial.print(hour);
    Serial.print(":");
    if (minute < 10) Serial.print("0");
    Serial.print(minute);
    Serial.print(":");
    if (second < 10) Serial.print("0");
    Serial.println(second);
    
  } else {
    // โหมดแสดงวันที่ (DD-MM-YY)
    int day = timeinfo.tm_mday;
    int month = timeinfo.tm_mon + 1;  // เดือนเริ่มจาก 0
    int year = (timeinfo.tm_year + 1900) % 100;  // แสดง 2 หลักสุดท้ายของปี
    
    // แสดงวันที่บนจอ TM1638
    board.tm1638_date(day, month, year);
    
    // แสดงผลใน Serial Monitor
    Serial.print("วันที่: ");
    if (day < 10) Serial.print("0");
    Serial.print(day);
    Serial.print("-");
    if (month < 10) Serial.print("0");
    Serial.print(month);
    Serial.print("-");
    if (year < 10) Serial.print("0");
    Serial.println(year);
  }
  
  // แสดงข้อมูล WiFi
  Serial.print("IP: ");
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
  Serial.println("  WiFi NTP Time Display on TM1638");
  Serial.println("  ESP32 IoT Board");
  Serial.println("========================================\n");
  
  // เริ่มต้น ESP32_IOT board
  board.begin();
  Serial.println("✓ เริ่มต้น ESP32_IOT board สำเร็จ");
  
  // เริ่มต้น TM1638
  board.tm1638_begin();
  Serial.println("✓ เริ่มต้น TM1638 module สำเร็จ");
  
  // แสดงข้อความ "Connecting..." บนจอ
  board.tm1638_number(0);
  
  // เชื่อมต่อ WiFi
  connectWiFi();
  
  // เริ่มต้น NTP time
  initNTPTime();
  
  // แสดงข้อมูลครั้งแรก
  Serial.println("\n========================================");
  Serial.println("เริ่มแสดงผลเวลาและวันที่");
  Serial.println("สลับโหมดทุกๆ 10 วินาที");
  Serial.println("========================================\n");
  
  updateDisplay();
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
    
    // แสดง "no conn" บนจอ
    board.tm1638_number(0);
    
    // เปลี่ยน LED ให้กระพริบเร็ว
    board.tickBlueLED(0.1);
    
    // พยายามเชื่อมต่อใหม่
    connectWiFi();
    
    // เริ่มต้น NTP time ใหม่
    initNTPTime();
  }
  
  // อ่านเวลาปัจจุบัน
  unsigned long currentMillis = millis();
  
  // ตรวจสอบว่าครบ 10 วินาทีหรือยัง (สลับโหมดแสดงผล)
  if (currentMillis - previousMillis >= switchInterval) {
    // บันทึกเวลาล่าสุด
    previousMillis = currentMillis;
    
    // สลับโหมดแสดงผล
    displayMode = !displayMode;
    
    // แสดงข้อความเมื่อสลับโหมด
    Serial.println("\n========================================");
    if (displayMode) {
      Serial.println("โหมด: แสดงเวลา (HH:MM:SS)");
    } else {
      Serial.println("โหมด: แสดงวันที่ (DD-MM-YY)");
    }
    Serial.println("========================================");
    
    // อัพเดทการแสดงผล
    updateDisplay();
  }
  
  // ตรวจสอบว่าครบ 1 วินาทีหรือยัง (อัพเดทข้อมูล)
  if (currentMillis - previousUpdateMillis >= updateInterval) {
    // บันทึกเวลาล่าสุด
    previousUpdateMillis = currentMillis;
    
    // อัพเดทการแสดงผล
    updateDisplay();
  }
}
