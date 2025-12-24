/*
 * ตัวอย่าง: เล่นเพลง Happy Birthday ด้วย ESP32
 * 
 * คำอธิบาย:
 * - โปรแกรมนี้ใช้ library esp32_iot ในการเล่นเพลง Happy Birthday ผ่าน Buzzer
 * - ใช้ LEDC (LED Control) PWM เพื่อสร้างเสียงจากความถี่ต่างๆ
 * - แสดงสถานะการเล่นเพลงผ่าน Serial Monitor
 * - LED สีน้ำเงินจะกระพริบตามจังหวะเพลง
 * 
 * พินที่ใช้งาน:
 * - Buzzer: GPIO 13
 * - LED3 (Blue): GPIO 2
 */

#include <Arduino.h>
#include <esp32_iot.h>

// สร้าง object สำหรับใช้งาน library esp32_iot
esp32_iot board;

// กำหนดโน้ตเสียง (ความถี่ใน Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define REST     0

// เพลง Happy Birthday
// โครงสร้าง: {ความถี่, ระยะเวลา (ms)}
int happyBirthdayMelody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,  // Happy birthday to you
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,  // Happy birthday to you
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,  // Happy birthday dear...
  NOTE_B4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4   // Happy birthday to you
};

int happyBirthdayDurations[] = {
  250, 250, 500, 500, 500, 1000,  // Happy birthday to you
  250, 250, 500, 500, 500, 1000,  // Happy birthday to you
  250, 250, 500, 500, 500, 500, 1000,  // Happy birthday dear...
  250, 250, 500, 500, 500, 1000   // Happy birthday to you
};

const int numNotes = sizeof(happyBirthdayMelody) / sizeof(happyBirthdayMelody[0]);

// ฟังก์ชันเล่นเพลง Happy Birthday
void playHappyBirthday() {
  const uint8_t channel = 0;      // LEDC channel
  const uint8_t resolution = 8;   // LEDC resolution
  
  // ตั้งค่า LEDC สำหรับ buzzer
  ledcSetup(channel, 2000, resolution);
  ledcAttachPin(13, channel);  // BUZZER_PIN = 13
  
  Serial.println("🎵 กำลังเล่นเพลง Happy Birthday... 🎵\n");
  
  // เล่นแต่ละโน้ต
  for (int i = 0; i < numNotes; i++) {
    int noteDuration = happyBirthdayDurations[i];
    
    if (happyBirthdayMelody[i] == REST) {
      // พักเสียง
      ledcWriteTone(channel, 0);
      board.blueLED(false);
      delay(noteDuration);
    } else {
      // เล่นโน้ต
      Serial.print("โน้ตที่ ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(happyBirthdayMelody[i]);
      Serial.print(" Hz, ระยะเวลา ");
      Serial.print(noteDuration);
      Serial.println(" ms");
      
      ledcWriteTone(channel, happyBirthdayMelody[i]);
      board.blueLED(true);  // เปิด LED สีน้ำเงินตามจังหวะ
      delay(noteDuration * 0.9);  // เล่นโน้ต 90% ของระยะเวลา
      
      // หยุดเสียงสั้นๆ ระหว่างโน้ต
      ledcWriteTone(channel, 0);
      board.blueLED(false);
      delay(noteDuration * 0.1);  // พัก 10%
    }
  }
  
  // ปิดเสียงและ LED
  ledcWriteTone(channel, 0);
  board.blueLED(false);
  
  Serial.println("\n✅ เล่นเพลงเสร็จสิ้น!\n");
}

void setup() {
  // เริ่มต้น Serial communication ที่ baud rate 115200
  Serial.begin(115200);
  delay(1000);
  
  // เริ่มต้นการทำงานของ esp32_iot library
  board.begin();
  
  // แสดงข้อความเริ่มต้นโปรแกรม
  Serial.println("\n=================================");
  Serial.println("🎂 Happy Birthday Music Player 🎂");
  Serial.println("ESP32 IOT Board");
  Serial.println("=================================");
  Serial.println("กด RESET เพื่อเล่นเพลงอีกครั้ง\n");
  
  // หน่วงเวลาก่อนเริ่มเล่น
  delay(1000);
}

void loop() {
  // เล่นเพลง Happy Birthday
  playHappyBirthday();
  
  // แสดงเอฟเฟกต์ LED หลังเล่นเพลงเสร็จ
  Serial.println("🎉 ฉลองวันเกิด! 🎉\n");
  for (int i = 0; i < 3; i++) {
    board.allLeds_On();
    delay(200);
    board.allLeds_Off();
    delay(200);
  }
  
  // รอ 5 วินาทีก่อนเล่นซ้ำ
  Serial.println("รอ 5 วินาที ก่อนเล่นซ้ำ...\n");
  delay(5000);
}
