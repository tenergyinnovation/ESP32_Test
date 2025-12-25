/***********************************************************************
 * โปรแกรมตัวอย่าง: ESP32 IoT with Blynk - DHT22 & BH1750 Sensor Monitoring
 * 
 * คำอธิบาย:
 * - อ่านค่าอุณหภูมิและความชื้นจาก DHT22 Temperature & Humidity Sensor
 * - อ่านค่าความเข้มแสงจาก BH1750 Light Intensity Sensor
 * - แสดงผลบนจอ TM1638 Display Module (อุณหภูมิ-ความชื้น)
 * - แสดงผลใน Serial Monitor
 * - ส่งข้อมูลไปยัง Blynk Cloud Platform ผ่าน WiFi
 * 
 * Blynk Virtual Pins:
 *   V0 = อุณหภูมิจาก DHT22 (°C)
 *   V1 = ความชื้นจาก DHT22 (%)
 *   V2 = ความเข้มแสงจาก BH1750 (lux)
 * 
 * การต่อฮาร์ดแวร์:
 * - ESP32 DevKit V1
 * - DHT22 VCC -> 3.3V, GND -> GND, DATA -> GPIO 14 (Pull-up 4.7K ohm)
 * - BH1750 VCC -> 3.3V, GND -> GND, SDA -> GPIO 21, SCL -> GPIO 22, ADDR -> GND
 * - TM1638 CLK -> GPIO 19, DIO -> GPIO 18, STB -> GPIO 23
 * - Buzzer (ควบคุมผ่าน esp32_iot library)
 * 
 * การตั้งค่า:
 * - WiFi SSID: "TENERGYINNOVATION"
 * - WiFi Password: "L0vemel0vemydog"
 * - Blynk Template ID: "TMPL6Pj2mIt_U"
 * - Blynk Auth Token: ตั้งค่าในโค้ด
 * 
 * การทำงาน:
 * 1. เชื่อมต่อ WiFi Network
 * 2. เชื่อมต่อ Blynk Cloud Platform
 * 3. อ่านค่าเซ็นเซอร์ทุกๆ 2 วินาที (DHT22, BH1750)
 * 4. แสดงผลบนจอ TM1638: อุณหภูมิ (หลัก 1-4), ความชื้น (หลัก 5-8)
 * 5. แสดงผลใน Serial Monitor
 * 6. ส่งข้อมูลไปยัง Blynk App
 * 
 * หมายเหตุ:
 * - ต้องสร้าง Device Template ใน Blynk Console ก่อน
 * - ตั้งค่า Virtual Pins ใน Blynk App: V0 (Temperature), V1 (Humidity), V2 (Light)
 * - ใช้ Gauge หรือ Chart Widget สำหรับแสดงผล
 * 
 * Author: Tenergy Innovation Co., Ltd.
 * Date: 26 Dec 2025
 ***********************************************************************/

// ===== การตั้งค่า Blynk Template & Authentication =====
// ข้อมูลเหล่านี้ได้จาก Blynk Console (https://blynk.cloud)
// *** สำคัญ: ต้อง define ก่อน #include <BlynkSimpleEsp32.h> ***
#define BLYNK_TEMPLATE_ID "TMPL6Pj2mIt_U"
#define BLYNK_TEMPLATE_NAME "ESP32Test"
#define BLYNK_AUTH_TOKEN "_ffS4_-MtMKDK0LfTj3qq__7MQ7lvWtd"

// ปิดการแสดง debug message ของ Blynk (ถ้าไม่ต้องการ)
// #define BLYNK_PRINT Serial

#include <esp32_iot.h>          // ไลบรารี ESP32 IoT สำหรับควบคุม ESP32 board
#include <DHT.h>                // ไลบรารี DHT สำหรับอ่านค่า DHT22 sensor
#include <WiFi.h>               // ไลบรารี WiFi สำหรับเชื่อมต่อ WiFi
#include <BlynkSimpleEsp32.h>   // ไลบรารี Blynk สำหรับ ESP32
#include <Wire.h>               // ไลบรารี I2C communication
#include <ErriezBH1750.h>       // ไลบรารีสำหรับ BH1750 Light Sensor
#include <esp_task_wdt.h>       // ไลบรารี Watchdog Timer

// ===== การตั้งค่า WiFi =====
#define WIFI_SSID "TENERGYINNOVATION"    // ชื่อ WiFi Network
#define WIFI_PASS "L0vemel0vemydog"      // รหัสผ่าน WiFi

// ===== การตั้งค่า DHT22 Sensor =====
#define DHT_PIN 14                       // พินที่ต่อกับ DHT22 (ตาม diagram.json)
#define DHT_TYPE DHT22                   // ประเภทเซ็นเซอร์ DHT22 (AM2302)

// ===== การประกาศ Object =====
esp32_iot board;                // Object สำหรับควบคุม ESP32 IoT board
DHT dht(DHT_PIN, DHT_TYPE);     // Object สำหรับควบคุม DHT22 sensor
BH1750 bh1750(LOW);             // Object สำหรับ BH1750 sensor (ADDR pin LOW = I2C address 0x23)

// ===== ฟังก์ชัน setup() - ทำงานครั้งเดียวตอนเริ่มต้น =====
void setup()
{
    // เริ่มต้น Serial communication ที่ความเร็ว 115200 baud
    Serial.begin(115200);
    Serial.println("\n===== ESP32 IoT with Blynk - Sensor Monitoring =====");

    // เริ่มต้น esp32_iot board (Buzzer, TM1638, ฯลฯ)
    board.begin();
    Serial.println("[OK] ESP32 IoT Board initialized");

    // เริ่มต้น DHT22 sensor
    dht.begin();
    Serial.println("[OK] DHT22 Sensor initialized (GPIO 14)");

    // เริ่มต้น I2C bus (SDA: GPIO 21, SCL: GPIO 22)
    Wire.begin();
    Serial.println("[OK] I2C Bus initialized");

    // เริ่มต้น BH1750 Light Sensor
    // ModeOneTime: วัดค่าทีละครั้ง (ประหยัดพลังงาน)
    // ResolutionMid: ความละเอียดปานกลาง (1 lux)
    bh1750.begin(ModeOneTime, ResolutionMid);
    Serial.println("[OK] BH1750 Light Sensor initialized (Address: 0x23)");

    // เริ่มต้น TM1638 Display Module
    board.tm1638_begin();
    Serial.println("[OK] TM1638 Display initialized");
    
    // ตั้งความสว่างของจอ TM1638 (0-7)
    board.tm1638_setBrightness(5);
    
    // ล้างหน้าจอ TM1638
    board.tm1638_clear();

    // ===== เชื่อมต่อ WiFi Network =====
    Serial.println("\n--- Connecting to WiFi ---");
    Serial.print("SSID: ");
    Serial.println(WIFI_SSID);
    
    WiFi.begin(WIFI_SSID, WIFI_PASS);  // เริ่มเชื่อมต่อ WiFi
    
    int wifi_retry = 0;
    // รอการเชื่อมต่อ WiFi สูงสุด 20 วินาที
    while (WiFi.status() != WL_CONNECTED && wifi_retry < 20)
    {
        delay(1000);
        Serial.print(".");
        wifi_retry++;
    }
    
    // ตรวจสอบสถานะการเชื่อมต่อ WiFi
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\n[OK] WiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());  // แสดง IP address
        Serial.print("RSSI: ");
        Serial.print(WiFi.RSSI());       // แสดงความแรงสัญญาณ
        Serial.println(" dBm");

        board.buzzer_beep(2, 100);       // Beep 2 ครั้ง เมื่อเชื่อมต่อสำเร็จ
        delay(1000);
    }
    else
    {
        Serial.println("\n[ERROR] WiFi Connection FAILED!");
        while (1);  // หยุดทำงานถ้าเชื่อมต่อ WiFi ไม่สำเร็จ
    }

    // ===== เชื่อมต่อ Blynk Cloud Platform =====
    Serial.println("\n--- Connecting to Blynk Cloud ---");
    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

    int blynk_retry = 0;
    // รอการเชื่อมต่อ Blynk สูงสุด 20 วินาที
    while (!Blynk.connected() && blynk_retry < 20)
    {
        delay(1000);
        Serial.print(".");
        blynk_retry++;
    }

    // ตรวจสอบสถานะการเชื่อมต่อ Blynk
    if (Blynk.connected())
    {
        Serial.println("\n[OK] Blynk Connected!");
        board.buzzer_beep(1, 200);  // Beep 1 ครั้ง เมื่อเชื่อมต่อ Blynk สำเร็จ
    }
    else
    {
        Serial.println("\n[ERROR] Blynk Connection FAILED!");
        while (1);  // หยุดทำงานถ้าเชื่อมต่อ Blynk ไม่สำเร็จ
    }

    // เริ่มต้น Watchdog Timer (กำหนดเวลา timeout 10 วินาที)
    esp_task_wdt_init(10, true);
    esp_task_wdt_add(NULL);

    Serial.println("\n===== System Ready! =====\n");
    delay(1000);
}

// ===== ฟังก์ชัน loop() - ทำงานซ้ำไปเรื่อยๆ =====
void loop()
{
    // รัน Blynk service (จำเป็นต้องเรียกทุกครั้งใน loop)
    Blynk.run();
    
    // Reset Watchdog Timer เพื่อป้องกันการ reset อัตโนมัติ
    esp_task_wdt_reset();

    // ===== อ่านค่าอุณหภูมิและความชื้นจาก DHT22 =====
    // อ่านค่าความชื้นจาก DHT22 (%)
    float humidity = dht.readHumidity();
    
    // อ่านค่าอุณหภูมิจาก DHT22 (°C)
    float temperature = dht.readTemperature();
    
    // ตรวจสอบว่าอ่านค่าได้หรือไม่
    if (isnan(humidity) || isnan(temperature)) {
        // ถ้าอ่านค่าไม่ได้ แสดงข้อความ Error
        Serial.println("[ERROR] ไม่สามารถอ่านค่าจาก DHT22 sensor!");
        
        // ส่งค่า 0 ไปยัง Blynk และข้ามการส่งค่า BH1750
        Blynk.virtualWrite(V0, 0);
        Blynk.virtualWrite(V1, 0);
        
        // ล้างหน้าจอ TM1638
        board.tm1638_clear();
        
        // หน่วงเวลา 2 วินาทีก่อนอ่านค่าใหม่
        delay(2000);
        return;  // กลับไปเริ่ม loop ใหม่
    }

    // ===== อ่านค่าความเข้มแสงจาก BH1750 =====
    uint16_t lightIntensity = 0;
    
    // เริ่มการแปลงค่า (conversion) จาก BH1750
    bh1750.startConversion();
    
    // รอให้การแปลงค่าเสร็จสมบูรณ์ (blocking mode)
    if (bh1750.waitForCompletion()) {
        // อ่านค่าความเข้มแสงจากเซ็นเซอร์ (หน่วย: lux)
        lightIntensity = bh1750.read();
    } else {
        // ถ้าอ่านค่าไม่ได้ ให้ค่าเป็น 0
        Serial.println("[WARNING] BH1750 reading failed, using 0 lux");
        lightIntensity = 0;
    }

    // ===== แสดงผลค่าที่อ่านได้ใน Serial Monitor =====
    Serial.println("===== Sensor Reading =====");
    Serial.print("Temperature: ");
    Serial.print(temperature, 1);  // แสดงทศนิยม 1 ตำแหน่ง
    Serial.println(" °C");
    
    Serial.print("Humidity: ");
    Serial.print(humidity, 1);     // แสดงทศนิยม 1 ตำแหน่ง
    Serial.println(" %");
    
    Serial.print("Light Intensity: ");
    Serial.print(lightIntensity);
    Serial.println(" lux");
    Serial.println();

    // ===== แสดงผลค่าบนจอ TM1638 =====
    // แสดงผลอุณหภูมิที่หลัก 1-4 และความชื้นที่หลัก 5-8
    // ตัวอย่าง: [28.5][65.2] แสดงอุณหภูมิ 28.5°C และความชื้น 65.2%
    board.tm1638_number(temperature, humidity);

    // ===== ส่งข้อมูลไปยัง Blynk Cloud Platform =====
    // V0 = อุณหภูมิจาก DHT22 (°C)
    Blynk.virtualWrite(V0, temperature);
    
    // V1 = ความชื้นจาก DHT22 (%)
    Blynk.virtualWrite(V1, humidity);
    
    // V2 = ความเข้มแสงจาก BH1750 (lux)
    Blynk.virtualWrite(V2, lightIntensity);

    // หน่วงเวลา 2 วินาที ก่อนอ่านค่าครั้งถัดไป
    delay(2000);
}
