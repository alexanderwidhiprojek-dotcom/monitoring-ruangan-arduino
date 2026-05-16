#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ========== DHT11 ==========
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ========== RGB LED (mapping final) ==========
#define RED_PIN 9      // MERAH
#define GREEN_PIN 10   // HIJAU
#define BLUE_PIN 11    // BIRU

// ========== BUZZER AKTIF ==========
#define BUZZER 3

// ========== LDR ==========
#define LDR_PIN A0

// ========== LCD I2C ==========
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ========== Timer ==========
unsigned long lastBuzz = 0;
unsigned long lastLCD = 0;

const unsigned long buzzInterval = 30000;  // 30 detik
const unsigned long lcdInterval  = 5000;   // 5 detik

// =======================
void setup() {
  Serial.begin(9600);
  dht.begin();

  // LCD
  lcd.init();
  lcd.backlight();

  // RGB LED
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("System Starting");
  lcd.setCursor(0, 1);
  lcd.print("Please wait...");
  delay(1500);
}

// =======================
// Fungsi RGB
void setRGB(bool r, bool g, bool b) {
  digitalWrite(RED_PIN,   r ? HIGH : LOW);
  digitalWrite(GREEN_PIN, g ? HIGH : LOW);
  digitalWrite(BLUE_PIN,  b ? HIGH : LOW);
}

// =======================
// Beep buzzer aktif
void beep(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(200);
  }
}

// =======================
void loop() {

  // ====== Baca sensor ======
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int rawLDR = analogRead(LDR_PIN);

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca DHT!");
    return;
  }

  // ====== Konversi cahaya 0–1023 → level 1–10 ======
  int lightLevel = map(rawLDR, 0, 1023, 1, 10);

  // ====== LED RGB berdasarkan suhu ======
  if (t < 20) {
    setRGB(0, 0, 1);   // biru
  } else if (t <= 30) {
    setRGB(0, 1, 0);   // hijau
  } else {
    setRGB(1, 0, 0);   // merah
  }

  // ====== Buzzer berdasarkan kelembapan (tiap 30 detik) ======
  unsigned long now = millis();
  if (now - lastBuzz >= buzzInterval) {
    lastBuzz = now;

    if (h < 40) {
      beep(3);  // kelembapan rendah
    } else if (h > 60) {
      beep(5);  // kelembapan tinggi
    }
  }

  // ====== Update LCD tiap 5 detik ======
  if (now - lastLCD >= lcdInterval) {
    lastLCD = now;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(t, 1);
    lcd.print("C H:");
    lcd.print(h, 0);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("Cahaya:");
    lcd.print(lightLevel);
    lcd.print("/10");
  }

  // Debug Serial
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print("C | Kelembapan: ");
  Serial.print(h);
  Serial.print("% | Cahaya: ");
  Serial.println(lightLevel);

  delay(200);
}
