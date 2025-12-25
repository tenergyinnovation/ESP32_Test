/***********************************************************************
 * โปรแกรมตัวอย่าง: ESP32 WiFi Connection with LED Indicator
 * 
 * รายละเอียด:
 * - เชื่อมต่อ ESP32 กับ WiFi Network
 * - แสดงสถานะการเชื่อมต่อผ่าน Serial Monitor
 * - แสดงค่า IP Address ที่ได้รับ
 * - แสดงค่า RSSI (ความแรงของสัญญาณ WiFi)
 * - ใช้ Blue LED เป็นตัวบ่งชี้สถานะ:
 *   * ระหว่างเชื่อมต่อ: กระพริบเร็ว (100ms)
 *   * เชื่อมต่อสำเร็จ: กระพริบช้า (1 วินาที)
 * 
 * การทำงาน:
 * - ใน setup() จะเริ่มต้นการเชื่อมต่อ WiFi
 * - Blue LED กระพริบเร็วระหว่างรอเชื่อมต่อ
 * - เมื่อเชื่อมต่อสำเร็จ Blue LED กระพริบช้าลง
 * - ใน loop() แสดงข้อมูล IP และ RSSI ทุกๆ 5 วินาที
 * 
 * การต่อฮาร์ดแวร์:
 * - Blue LED: GPIO 2 (ในบอร์ด ESP32 IoT)
 * 
 * หมายเหตุ:
 * - ตรวจสอบให้แน่ใจว่า WiFi network มีสัญญาณที่ดี
 * - ค่า RSSI ที่ดี: > -70 dBm
 * - ค่า RSSI ปานกลาง: -70 ถึง -85 dBm
 * - ค่า RSSI อ่อน: < -85 dBm
 * 
 * Author: Tenergy Innovation Co., Ltd.
 * Date: 25 Dec 2025
 ***********************************************************************/

#include <WiFi.h>        // ไลบรารีสำหรับ WiFi
#include <esp32_iot.h>   // ไลบรารีสำหรับควบคุมบอร์ด ESP32 IoT

// กำหนดค่า WiFi
const char* ssid = "TENERGYINNOVATION";          // ชื่อ WiFi Network
const char* password = "L0vemel0vemydog";        // รหัสผ่าน WiFi

// สร้าง object สำหรับควบคุมบอร์ด ESP32 IoT
esp32_iot board;

// ตัวแปรสำหรับจับเวลา
unsigned long previousMillis = 0;
const long interval = 5000;  // แสดงข้อมูลทุกๆ 5 วินาที (5000 มิลลิวินาที)

void setup()
{
  // เริ่มต้น Serial สำหรับแสดงผลข้อมูลทาง Serial Monitor
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  Serial.println("=====================================");
  Serial.println("  ESP32 WiFi Connection Example");
  Serial.println("=====================================");

  // เริ่มต้นบอร์ด ESP32 IoT (ตั้งค่าพินต่างๆ)
  board.begin();

  // เริ่มต้นการเชื่อมต่อ WiFi
  Serial.println("");
  Serial.print("กำลังเชื่อมต่อกับ WiFi: ");
  Serial.println(ssid);

  // ตั้งค่า Blue LED ให้กระพริบเร็วระหว่างเชื่อมต่อ (100ms = 0.1 วินาที)
  board.tickBlueLED(0.1);

  // เริ่มเชื่อมต่อ WiFi
  WiFi.begin(ssid, password);

  // รอจนกว่าจะเชื่อมต่อสำเร็จ
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
    attempts++;

    // ถ้าพยายามเชื่อมต่อเกิน 30 ครั้ง (15 วินาที) ให้แสดงข้อความเตือน
    if (attempts > 30) 
    {
      Serial.println("");
      Serial.println("การเชื่อมต่อใช้เวลานาน กรุณาตรวจสอบ:");
      Serial.println("- ชื่อ WiFi (SSID) ถูกต้องหรือไม่");
      Serial.println("- รหัสผ่านถูกต้องหรือไม่");
      Serial.println("- WiFi มีสัญญาณที่ดีหรือไม่");
      attempts = 0;
    }
  }

  // เชื่อมต่อสำเร็จ
  Serial.println("");
  Serial.println("=====================================");
  Serial.println("✓ เชื่อมต่อ WiFi สำเร็จ!");
  Serial.println("=====================================");

  // แสดงข้อมูล WiFi
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());

  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());

  Serial.print("DNS Server: ");
  Serial.println(WiFi.dnsIP());

  // แสดงค่า RSSI (ความแรงของสัญญาณ)
  int rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(rssi);
  Serial.print(" dBm");

  // ประเมินคุณภาพสัญญาณ
  if (rssi > -50) {
    Serial.println(" (ดีเยี่ยม)");
  } else if (rssi > -60) {
    Serial.println(" (ดีมาก)");
  } else if (rssi > -70) {
    Serial.println(" (ดี)");
  } else if (rssi > -80) {
    Serial.println(" (ปานกลาง)");
  } else if (rssi > -90) {
    Serial.println(" (อ่อน)");
  } else {
    Serial.println(" (อ่อนมาก)");
  }

  Serial.println("=====================================");
  Serial.println("");

  // เปลี่ยนให้ Blue LED กระพริบช้าลง (1 วินาที)
  board.tickBlueLED(1.0);

  Serial.println("กำลังแสดงข้อมูล WiFi ทุกๆ 5 วินาที...");
  Serial.println("");
}

void loop()
{
  // ตรวจสอบสถานะการเชื่อมต่อ WiFi
  if (WiFi.status() != WL_CONNECTED) 
  {
    // ถ้าหลุดการเชื่อมต่อ
    Serial.println("=====================================");
    Serial.println("✗ การเชื่อมต่อ WiFi ขาดหาย!");
    Serial.println("กำลังพยายามเชื่อมต่อใหม่...");
    Serial.println("=====================================");

    // เปลี่ยน LED กระพริบเร็ว
    board.tickBlueLED(0.1);

    // พยายามเชื่อมต่อใหม่
    WiFi.begin(ssid, password);

    // รอจนกว่าจะเชื่อมต่อสำเร็จ
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("✓ เชื่อมต่อ WiFi สำเร็จอีกครั้ง!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // เปลี่ยน LED กระพริบช้า
    board.tickBlueLED(1.0);
  }

  // จับเวลาแสดงข้อมูลทุกๆ 5 วินาที
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) 
  {
    // บันทึกเวลาล่าสุด
    previousMillis = currentMillis;

    // แสดงข้อมูล WiFi
    Serial.println("-----------------------------------");
    Serial.print("เวลา: ");
    Serial.print(millis() / 1000);
    Serial.println(" วินาที");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // แสดงค่า RSSI
    int rssi = WiFi.RSSI();
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.print(" dBm");

    // ประเมินคุณภาพสัญญาณ
    if (rssi > -50) {
      Serial.print(" (ดีเยี่ยม)");
    } else if (rssi > -60) {
      Serial.print(" (ดีมาก)");
    } else if (rssi > -70) {
      Serial.print(" (ดี)");
    } else if (rssi > -80) {
      Serial.print(" (ปานกลาง)");
    } else if (rssi > -90) {
      Serial.print(" (อ่อน)");
    } else {
      Serial.print(" (อ่อนมาก)");
    }

    // แสดงเปอร์เซ็นต์คุณภาพสัญญาณโดยประมาณ
    int quality = 0;
    if (rssi <= -100) {
      quality = 0;
    } else if (rssi >= -50) {
      quality = 100;
    } else {
      quality = 2 * (rssi + 100);
    }

    Serial.print(" [");
    Serial.print(quality);
    Serial.println("%]");

    Serial.print("Status: ");
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("เชื่อมต่อ");
    } else {
      Serial.println("ไม่ได้เชื่อมต่อ");
    }

    Serial.println("-----------------------------------");
    Serial.println("");
  }
}
