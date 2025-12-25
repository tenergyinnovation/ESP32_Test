/*
 * ตัวอย่างโปรแกรม: ESP32 Web Server with DHT22 & Relay Control
 * =====================================================
 * โปรแกรมนี้สาธิตการสร้าง Web Server บน ESP32 ที่แสดงผลอุณหภูมิและความชื้น
 * จาก DHT22 sensor พร้อมควบคุม Relay 1 และ Relay 2 ผ่านหน้าเว็บ
 * 
 * การทำงาน:
 * 1. เชื่อมต่อกับ WiFi network
 * 2. สร้าง Web Server บน ESP32
 * 3. อ่านค่าอุณหภูมิและความชื้นจาก DHT22
 * 4. แสดงผลบนหน้าเว็บที่ออกแบบสวยงาม
 * 5. ควบคุม Relay 1 และ Relay 2 ผ่านปุ่มบนหน้าเว็บ
 * 6. แสดงสถานะ Relay แบบ real-time
 * 7. อัพเดทค่าอัตโนมัติทุกๆ 2 วินาทีด้วย AJAX
 * 8. แสดงผลพร้อมกันที่ Serial Monitor และจอ TM1638
 * 
 * หน้าเว็บประกอบด้วย:
 * - การ์ดแสดงอุณหภูมิและความชื้น
 * - การ์ดควบคุม Relay 1 และ Relay 2
 * - ปุ่มเปิด-ปิด Relay พร้อมแสดงสถานะ
 * - Gradient background สวยงาม
 * - Responsive design รองรับทุกขนาดหน้าจอ
 * 
 * อุปกรณ์ที่ใช้:
 * - ESP32 Development Board
 * - DHT22 Temperature & Humidity Sensor (GPIO 14)
 * - Relay Module 1 (GPIO 25)
 * - Relay Module 2 (GPIO 26)
 * - TM1638 Display Module
 * - ESP32_IOT Board
 * 
 * ไลบรารีที่ใช้:
 * - WiFi.h          : สำหรับเชื่อมต่อ WiFi
 * - WebServer.h     : สำหรับสร้าง Web Server
 * - DHT.h           : สำหรับอ่านค่า DHT22
 * - esp32_iot.h     : สำหรับควบคุม TM1638 และ Relay
 */

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <esp32_iot.h>

// ========================================
// WiFi Configuration
// ========================================
const char* ssid = "TENERGYINNOVATION";          // ชื่อ WiFi network
const char* password = "L0vemel0vemydog";        // รหัสผ่าน WiFi

// ========================================
// DHT22 Sensor Configuration
// ========================================
#define DHTPIN 14                                 // GPIO สำหรับ DHT22 (ตาม diagram.json)
#define DHTTYPE DHT22                             // ชนิดของเซ็นเซอร์ DHT22
DHT dht(DHTPIN, DHTTYPE);                        // สร้าง object DHT

// ========================================
// Web Server Configuration
// ========================================
WebServer server(80);                            // สร้าง Web Server บน port 80

// ========================================
// Sensor Data Variables
// ========================================
float temperature = 0.0;                         // ตัวแปรเก็บค่าอุณหภูมิ (°C)
float humidity = 0.0;                            // ตัวแปรเก็บค่าความชื้น (%)
unsigned long lastReadTime = 0;                  // เวลาล่าสุดที่อ่านค่าเซ็นเซอร์
const long readInterval = 2000;                  // อ่านค่าทุกๆ 2 วินาที

// ========================================
// Relay Status Variables
// ========================================
bool relay1Status = false;                       // สถานะ Relay 1 (false = ปิด, true = เปิด)
bool relay2Status = false;                       // สถานะ Relay 2 (false = ปิด, true = เปิด)

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
    
    // แสดงคำเตือนทุกๆ 30 ครั้ง
    if (attempts % 30 == 0) {
      Serial.println();
      Serial.print("กำลังพยายามเชื่อมต่อ... (");
      Serial.print(attempts);
      Serial.println(" ครั้ง)");
    }
    
    // หากเชื่อมต่อไม่สำเร็จหลังจาก 60 ครั้ง
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
  Serial.print("IP Address    : ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address   : ");
  Serial.println(WiFi.macAddress());
  Serial.print("RSSI          : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  Serial.println("========================================\n");
  
  // เปลี่ยน Blue LED ให้กระพริบช้า (1 วินาที)
  board.tickBlueLED(1.0);
}

// ========================================
// Function: Read DHT22 Sensor
// ========================================
void readDHT22() {
  // อ่านค่าความชื้น
  float h = dht.readHumidity();
  
  // อ่านค่าอุณหภูมิ (Celsius)
  float t = dht.readTemperature();
  
  // ตรวจสอบว่าอ่านค่าสำเร็จหรือไม่
  if (isnan(h) || isnan(t)) {
    Serial.println("❌ ไม่สามารถอ่านค่าจาก DHT22 ได้");
    return;
  }
  
  // บันทึกค่าลงตัวแปร global
  temperature = t;
  humidity = h;
  
  // แสดงผลใน Serial Monitor
  Serial.println("========================================");
  Serial.println("DHT22 Sensor Data");
  Serial.println("========================================");
  Serial.print("อุณหภูมิ: ");
  Serial.print(temperature, 1);
  Serial.println(" °C");
  Serial.print("ความชื้น: ");
  Serial.print(humidity, 1);
  Serial.println(" %");
  Serial.println("========================================\n");
  
  // แสดงผลบนจอ TM1638
  board.tm1638_number(temperature, humidity);
}

// ========================================
// Function: Control Relay
// ========================================
void controlRelay(int relayNum, bool state) {
  if (relayNum == 1) {
    relay1Status = state;
    if (state) {
      board.relay1_On();
      Serial.println("Relay 1: เปิด");
    } else {
      board.relay1_Off();
      Serial.println("Relay 1: ปิด");
    }
  } else if (relayNum == 2) {
    relay2Status = state;
    if (state) {
      board.relay2_On();
      Serial.println("Relay 2: เปิด");
    } else {
      board.relay2_Off();
      Serial.println("Relay 2: ปิด");
    }
  }
}

// ========================================
// Function: HTML Page - Main Dashboard
// ========================================
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="th">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 DHT22 & Relay Control</title>
    <style>
        /* ========================================
           Global Styles - การตั้งค่าทั่วไป
           ======================================== */
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            padding: 20px;
        }
        
        /* ========================================
           Container - กล่องหลักที่บรรจุเนื้อหา
           ======================================== */
        .container {
            max-width: 1000px;
            width: 100%;
        }
        
        /* ========================================
           Header - หัวเรื่องหน้าเว็บ
           ======================================== */
        .header {
            text-align: center;
            color: white;
            margin-bottom: 30px;
            animation: fadeIn 1s ease-in;
        }
        
        .header h1 {
            font-size: 2.5em;
            margin-bottom: 10px;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
        }
        
        .header p {
            font-size: 1.1em;
            opacity: 0.9;
        }
        
        /* ========================================
           Dashboard - พื้นที่แสดงการ์ด
           ======================================== */
        .dashboard {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
            gap: 20px;
            margin-bottom: 20px;
        }
        
        /* ========================================
           Card - การ์ดแสดงข้อมูล
           ======================================== */
        .card {
            background: white;
            border-radius: 20px;
            padding: 30px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
            transition: transform 0.3s ease, box-shadow 0.3s ease;
            animation: slideUp 0.5s ease-out;
        }
        
        .card:hover {
            transform: translateY(-5px);
            box-shadow: 0 15px 40px rgba(0,0,0,0.3);
        }
        
        /* ========================================
           Card Header - หัวเรื่องของการ์ด
           ======================================== */
        .card-header {
            display: flex;
            align-items: center;
            margin-bottom: 20px;
            gap: 15px;
        }
        
        .icon {
            width: 50px;
            height: 50px;
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 24px;
        }
        
        /* ไอคอนอุณหภูมิ - สีส้มแดง */
        .icon-temp {
            background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
        }
        
        /* ไอคอนความชื้น - สีฟ้า */
        .icon-humidity {
            background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%);
        }
        
        /* ไอคอน Relay - สีเขียว */
        .icon-relay {
            background: linear-gradient(135deg, #43e97b 0%, #38f9d7 100%);
        }
        
        .card-title {
            font-size: 1.2em;
            color: #333;
            font-weight: 600;
        }
        
        /* ========================================
           Card Value - ค่าที่แสดงในการ์ด
           ======================================== */
        .card-value {
            font-size: 3em;
            font-weight: bold;
            color: #2d3748;
            text-align: center;
            margin: 20px 0;
        }
        
        .card-unit {
            font-size: 0.4em;
            color: #718096;
            margin-left: 5px;
        }
        
        /* ========================================
           Relay Control - ส่วนควบคุม Relay
           ======================================== */
        .relay-control {
            display: flex;
            flex-direction: column;
            gap: 15px;
        }
        
        .relay-item {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 15px;
            background: #f7fafc;
            border-radius: 10px;
            transition: background 0.3s;
        }
        
        .relay-item:hover {
            background: #edf2f7;
        }
        
        .relay-label {
            font-size: 1.1em;
            font-weight: 600;
            color: #2d3748;
        }
        
        .relay-status {
            font-size: 0.9em;
            padding: 5px 15px;
            border-radius: 20px;
            font-weight: 600;
            margin: 0 10px;
        }
        
        .status-on {
            background: #48bb78;
            color: white;
        }
        
        .status-off {
            background: #cbd5e0;
            color: #4a5568;
        }
        
        /* ========================================
           Button - ปุ่มควบคุม
           ======================================== */
        .btn {
            padding: 10px 25px;
            border: none;
            border-radius: 8px;
            font-size: 1em;
            font-weight: 600;
            cursor: pointer;
            transition: all 0.3s ease;
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        
        .btn-on {
            background: linear-gradient(135deg, #48bb78 0%, #38a169 100%);
            color: white;
        }
        
        .btn-on:hover {
            transform: scale(1.05);
            box-shadow: 0 5px 15px rgba(72, 187, 120, 0.4);
        }
        
        .btn-off {
            background: linear-gradient(135deg, #fc8181 0%, #f56565 100%);
            color: white;
        }
        
        .btn-off:hover {
            transform: scale(1.05);
            box-shadow: 0 5px 15px rgba(245, 101, 101, 0.4);
        }
        
        /* ========================================
           Footer - ส่วนท้ายแสดงเวลาอัพเดท
           ======================================== */
        .footer {
            background: rgba(255,255,255,0.1);
            color: white;
            text-align: center;
            padding: 15px;
            border-radius: 10px;
            backdrop-filter: blur(10px);
        }
        
        .update-time {
            font-size: 0.9em;
            opacity: 0.9;
        }
        
        /* ========================================
           Status Indicator - สัญญาณสถานะการเชื่อมต่อ
           ======================================== */
        .status {
            display: inline-block;
            width: 10px;
            height: 10px;
            border-radius: 50%;
            background: #48bb78;
            margin-right: 5px;
            animation: blink 2s ease-in-out infinite;
        }
        
        /* ========================================
           Animations - เอฟเฟกต์การเคลื่อนไหว
           ======================================== */
        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(-20px); }
            to { opacity: 1; transform: translateY(0); }
        }
        
        @keyframes slideUp {
            from { opacity: 0; transform: translateY(30px); }
            to { opacity: 1; transform: translateY(0); }
        }
        
        @keyframes blink {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.3; }
        }
        
        /* ========================================
           Responsive Design - รองรับหน้าจอเล็ก
           ======================================== */
        @media (max-width: 600px) {
            .header h1 {
                font-size: 1.8em;
            }
            
            .card-value {
                font-size: 2.5em;
            }
            
            .relay-item {
                flex-direction: column;
                gap: 10px;
            }
        }
    </style>
</head>
<body>
    <!-- ========================================
         Header Section - หัวเรื่องหน้าเว็บ
         ======================================== -->
    <div class="container">
        <div class="header">
            <h1>🌡️ ESP32 Control Center</h1>
            <p>ระบบตรวจวัดและควบคุมอัจฉริยะ</p>
        </div>
        
        <!-- ========================================
             Dashboard Section - การ์ดแสดงข้อมูล
             ======================================== -->
        <div class="dashboard">
            <!-- การ์ดอุณหภูมิ -->
            <div class="card">
                <div class="card-header">
                    <div class="icon icon-temp">🌡️</div>
                    <div class="card-title">อุณหภูมิ</div>
                </div>
                <div class="card-value" id="temperature">
                    --<span class="card-unit">°C</span>
                </div>
            </div>
            
            <!-- การ์ดความชื้น -->
            <div class="card">
                <div class="card-header">
                    <div class="icon icon-humidity">💧</div>
                    <div class="card-title">ความชื้น</div>
                </div>
                <div class="card-value" id="humidity">
                    --<span class="card-unit">%</span>
                </div>
            </div>
            
            <!-- การ์ดควบคุม Relay -->
            <div class="card" style="grid-column: span 2;">
                <div class="card-header">
                    <div class="icon icon-relay">⚡</div>
                    <div class="card-title">ควบคุม Relay</div>
                </div>
                <div class="relay-control">
                    <!-- Relay 1 Control -->
                    <div class="relay-item">
                        <div>
                            <span class="relay-label">Relay 1</span>
                            <span class="relay-status status-off" id="relay1-status">ปิด</span>
                        </div>
                        <div>
                            <button class="btn btn-on" onclick="controlRelay(1, true)">เปิด</button>
                            <button class="btn btn-off" onclick="controlRelay(1, false)">ปิด</button>
                        </div>
                    </div>
                    
                    <!-- Relay 2 Control -->
                    <div class="relay-item">
                        <div>
                            <span class="relay-label">Relay 2</span>
                            <span class="relay-status status-off" id="relay2-status">ปิด</span>
                        </div>
                        <div>
                            <button class="btn btn-on" onclick="controlRelay(2, true)">เปิด</button>
                            <button class="btn btn-off" onclick="controlRelay(2, false)">ปิด</button>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        
        <!-- ========================================
             Footer Section - เวลาอัพเดทล่าสุด
             ======================================== -->
        <div class="footer">
            <div class="update-time">
                <span class="status"></span>
                อัพเดทล่าสุด: <span id="lastUpdate">--:--:--</span>
            </div>
        </div>
    </div>
    
    <!-- ========================================
         JavaScript - สคริปต์อัพเดทข้อมูล
         ======================================== -->
    <script>
        // ฟังก์ชันอัพเดทข้อมูลจาก API
        function updateData() {
            // ส่ง HTTP request ไปยัง /data endpoint
            fetch('/data')
                .then(response => response.json())
                .then(data => {
                    // อัพเดทค่าอุณหภูมิ
                    document.getElementById('temperature').innerHTML = 
                        data.temperature.toFixed(1) + '<span class="card-unit">°C</span>';
                    
                    // อัพเดทค่าความชื้น
                    document.getElementById('humidity').innerHTML = 
                        data.humidity.toFixed(1) + '<span class="card-unit">%</span>';
                    
                    // อัพเดทสถานะ Relay 1
                    const relay1Status = document.getElementById('relay1-status');
                    if (data.relay1) {
                        relay1Status.textContent = 'เปิด';
                        relay1Status.className = 'relay-status status-on';
                    } else {
                        relay1Status.textContent = 'ปิด';
                        relay1Status.className = 'relay-status status-off';
                    }
                    
                    // อัพเดทสถานะ Relay 2
                    const relay2Status = document.getElementById('relay2-status');
                    if (data.relay2) {
                        relay2Status.textContent = 'เปิด';
                        relay2Status.className = 'relay-status status-on';
                    } else {
                        relay2Status.textContent = 'ปิด';
                        relay2Status.className = 'relay-status status-off';
                    }
                    
                    // อัพเดทเวลา
                    const now = new Date();
                    const timeString = now.toLocaleTimeString('th-TH');
                    document.getElementById('lastUpdate').textContent = timeString;
                })
                .catch(error => {
                    console.error('Error fetching data:', error);
                });
        }
        
        // ฟังก์ชันควบคุม Relay
        function controlRelay(relayNum, state) {
            const url = `/relay?num=${relayNum}&state=${state ? 1 : 0}`;
            
            fetch(url)
                .then(response => response.json())
                .then(data => {
                    console.log('Relay control:', data);
                    // อัพเดทข้อมูลทันที
                    updateData();
                })
                .catch(error => {
                    console.error('Error controlling relay:', error);
                    alert('เกิดข้อผิดพลาดในการควบคุม Relay');
                });
        }
        
        // อัพเดทข้อมูลทันทีเมื่อโหลดหน้าเว็บ
        updateData();
        
        // ตั้งเวลาอัพเดทข้อมูลทุกๆ 2 วินาที (2000 milliseconds)
        setInterval(updateData, 2000);
    </script>
</body>
</html>
)rawliteral";
  
  // ส่ง HTML กลับไปยัง client
  server.send(200, "text/html", html);
}

// ========================================
// Function: JSON API - Data Endpoint
// ========================================
void handleData() {
  // สร้าง JSON response พร้อมสถานะ Relay
  String json = "{";
  json += "\"temperature\":" + String(temperature, 1) + ",";
  json += "\"humidity\":" + String(humidity, 1) + ",";
  json += "\"relay1\":" + String(relay1Status ? "true" : "false") + ",";
  json += "\"relay2\":" + String(relay2Status ? "true" : "false");
  json += "}";
  
  // ส่ง JSON กลับไปยัง client
  server.send(200, "application/json", json);
}

// ========================================
// Function: Relay Control Endpoint
// ========================================
void handleRelayControl() {
  // รับพารามิเตอร์จาก URL
  if (server.hasArg("num") && server.hasArg("state")) {
    int relayNum = server.arg("num").toInt();
    int relayState = server.arg("state").toInt();
    
    // ควบคุม Relay
    controlRelay(relayNum, relayState == 1);
    
    // สร้าง JSON response
    String json = "{";
    json += "\"success\":true,";
    json += "\"relay\":" + String(relayNum) + ",";
    json += "\"state\":" + String(relayState == 1 ? "true" : "false");
    json += "}";
    
    // ส่ง JSON กลับไปยัง client
    server.send(200, "application/json", json);
    
    Serial.println("API Request: /relay");
    Serial.print("Relay ");
    Serial.print(relayNum);
    Serial.print(": ");
    Serial.println(relayState == 1 ? "เปิด" : "ปิด");
  } else {
    // ส่ง error response
    String json = "{\"success\":false,\"message\":\"Invalid parameters\"}";
    server.send(400, "application/json", json);
  }
}

// ========================================
// Function: 404 Not Found Handler
// ========================================
void handleNotFound() {
  String message = "404: Page Not Found\n\n";
  message += "URI: " + server.uri() + "\n";
  message += "Method: " + String((server.method() == HTTP_GET) ? "GET" : "POST") + "\n";
  
  server.send(404, "text/plain", message);
  
  Serial.println("404 Not Found: " + server.uri());
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
  Serial.println("  ESP32 DHT22 & Relay Web Server");
  Serial.println("  Temperature & Humidity Monitor");
  Serial.println("  with Relay Control");
  Serial.println("========================================\n");
  
  // เริ่มต้น ESP32_IOT board
  board.begin();
  Serial.println("✓ เริ่มต้น ESP32_IOT board สำเร็จ");
  
  // เริ่มต้น TM1638
  board.tm1638_begin();
  Serial.println("✓ เริ่มต้น TM1638 module สำเร็จ");
  
  // แสดงข้อความเริ่มต้นบนจอ TM1638
  board.tm1638_number(0);
  
  // เริ่มต้น DHT22 sensor
  dht.begin();
  Serial.println("✓ เริ่มต้น DHT22 sensor สำเร็จ");
  
  // เริ่มต้น Relay (ปิดทั้งหมด)
  board.relay1_Off();
  board.relay2_Off();
  relay1Status = false;
  relay2Status = false;
  Serial.println("✓ เริ่มต้น Relay module สำเร็จ (ปิดทั้งหมด)");
  
  // เชื่อมต่อ WiFi
  connectWiFi();
  
  // ตรวจสอบว่าเชื่อมต่อ WiFi สำเร็จหรือไม่
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ ไม่สามารถเริ่มต้น Web Server ได้");
    Serial.println("กรุณาตรวจสอบการเชื่อมต่อ WiFi");
    return;
  }
  
  // ตั้งค่า Web Server routes
  Serial.println("\n========================================");
  Serial.println("กำลังตั้งค่า Web Server...");
  Serial.println("========================================");
  
  // Route สำหรับหน้าหลัก
  server.on("/", handleRoot);
  Serial.println("✓ Route: / (หน้าหลัก)");
  
  // Route สำหรับ API ข้อมูล
  server.on("/data", handleData);
  Serial.println("✓ Route: /data (JSON API)");
  
  // Route สำหรับควบคุม Relay
  server.on("/relay", handleRelayControl);
  Serial.println("✓ Route: /relay (Relay Control API)");
  
  // Route สำหรับ 404 Not Found
  server.onNotFound(handleNotFound);
  Serial.println("✓ Handler: 404 Not Found");
  
  // เริ่มต้น Web Server
  server.begin();
  Serial.println("\n========================================");
  Serial.println("✓ Web Server เริ่มทำงานแล้ว!");
  Serial.println("========================================");
  Serial.print("เข้าถึงหน้าเว็บได้ที่: http://");
  Serial.println(WiFi.localIP());
  Serial.println("========================================\n");
  
  // อ่านค่าเซ็นเซอร์ครั้งแรก
  readDHT22();
}

// ========================================
// Loop Function
// ========================================
void loop() {
  // จัดการ HTTP requests
  server.handleClient();
  
  // ตรวจสอบเวลาสำหรับการอ่านค่าเซ็นเซอร์
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastReadTime >= readInterval) {
    // บันทึกเวลาล่าสุด
    lastReadTime = currentMillis;
    
    // อ่านค่าจากเซ็นเซอร์
    readDHT22();
    
    // แสดงสถานะ Relay
    Serial.print("Relay 1: ");
    Serial.print(relay1Status ? "เปิด" : "ปิด");
    Serial.print(" | Relay 2: ");
    Serial.println(relay2Status ? "เปิด" : "ปิด");
  }
  
  // ตรวจสอบการเชื่อมต่อ WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\n========================================");
    Serial.println("⚠ สัญญาณ WiFi ขาดหาย!");
    Serial.println("กำลังพยายามเชื่อมต่อใหม่...");
    Serial.println("========================================");
    
    // แสดง error บนจอ TM1638
    board.tm1638_number(88888888);
    
    // เปลี่ยน LED ให้กระพริบเร็ว
    board.tickBlueLED(0.1);
    
    // พยายามเชื่อมต่อใหม่
    connectWiFi();
  }
}
