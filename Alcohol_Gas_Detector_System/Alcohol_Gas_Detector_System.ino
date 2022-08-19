// Include library
// Cai dat thu vien
#include "LiquidCrystal_I2C.h"

// Define connected pin
// Dat ten chan cong ket noi
#define   GAS_PIN           A1
#define   ALCOHOL_PIN       A2
#define   BUZZER_PIN        A3
#define   LED_RED_PIN       9
#define   LED_YELLOW_PIN    10
#define   LED_GREEN_PIN     11
// Set gas and alcohol limt
// Dat cac gia tri nguong
#define   ALCOL_LIMIT1      100
#define   GAS_LIMIT1        400
#define   ALCOL_LIMIT2      50
#define   GAS_LIMIT2        120
// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Thiet lap dia chi LCD 0x27 de hien thi ky tu LCD 16 ky tu và 2 dong
LiquidCrystal_I2C LCD(0x27, 16, 2);

void setup() {
  // We initialize serial connection so that we could print values from sensor
  // Khoi tao cong ket noi noi tiep
  Serial.begin(9600);
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  LCD.init();
  // Turn on LCD backlight
  // Bat den nen LCD 1602
  LCD.backlight();
  // Thiet lap LED va BUZZER o trang thai OUTPUT
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  //PreHeating Sensor on 60s
  //Khoi dong lam nong cam bien trong 60s
  for (int i = 60; i >= 0; i--) {
    LCD.setCursor(0, 0);
    LCD.print("PreHeatingSensor");
    LCD.setCursor(7, 1);
    LCD.print(i);
    LCD.print("s  ");
    delay(1000);
    LCD.clear();
  }
}

void loop() {
  // Read gas and alcohol value
  // Doc gia tri cam bien khi gas va nong do con
  int gasValue = analogRead(GAS_PIN);
  int alcoValue = analogRead(ALCOHOL_PIN);
  // Print gas and alcohol value on LCD at column 1 and row 1
  // Hien thi gia tri khi gas va nong do con
  LCD.setCursor(0, 0);
  LCD.print("Gas ");
  LCD.setCursor(0, 1);
  LCD.print(gasValue);
  LCD.print("  ");
  LCD.setCursor(9, 0);
  LCD.print("Alcohol ");
  LCD.setCursor(9, 1);
  LCD.print(alcoValue);
  LCD.print("  ");
  delay(100);
  // Compare current gas and alcohol value to their limitt
  // So sanh cac gia tri nguong
  if ((alcoValue < ALCOL_LIMIT2) && (gasValue < GAS_LIMIT2)) {
    // Safe
    // An toan
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_YELLOW_PIN, LOW);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
  if (((alcoValue <= ALCOL_LIMIT1) && (alcoValue > ALCOL_LIMIT2)) || ((gasValue <= GAS_LIMIT1) && (gasValue > GAS_LIMIT2))) {
    // Turn on warning Led Level 1 and Alarm
    // Bat canh bao Led muc 1 va coi bao dong
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_YELLOW_PIN, HIGH);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_YELLOW_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
  if ((alcoValue > ALCOL_LIMIT1) || (gasValue > GAS_LIMIT1)) {
    // Turn on warning Led level 2 and Alarm
    // Bat canh bao led muc 2 va coi hoat dong lien tuc
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_YELLOW_PIN, HIGH);
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    //Tat cac canh bao
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_YELLOW_PIN, LOW);
    digitalWrite(LED_RED_PIN, LOW);
  }
}
