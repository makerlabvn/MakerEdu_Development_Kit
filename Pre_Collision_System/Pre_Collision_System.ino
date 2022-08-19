// Include library
// Cai dat thu vien
#include "UltraSonicDistanceSensor.h"
#include "LiquidCrystal_I2C.h"

// Define connected sensor pin
// Dat ten cong ket noi cho cam bien
#define  LED_R_PIN    A1
#define  LED_Y_PIN    A2
#define  LED_G_PIN    A3
#define  BUZZER_PIN   9
#define  TRIG_PIN     13
#define  ECHO_PIN     12

// Declare variables 
// Khai bao bien
int distance_value;
int Range_Danger;
int Range_Warning;
int Range_Close_2;
int Range_Safe;
UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);

LiquidCrystal_I2C LCD(39, 20, 04);

void setup() {
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  LCD.init();
  // Turn on LCD backlight   
  // Bat den nen LCD 1602
  LCD.backlight();
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_Y_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Range_Safe = 45;
  Range_Warning = 35;
  Range_Danger = 15;
}

void loop() {
  distance_value = distanceSensor.measureDistanceCm();
  // Setting LCD Display
  // Thiet lap hien thi tren LCD
  LCD.setCursor(0, 1);
  LCD.print("Distance: ");
  LCD.print(distance_value);
  LCD.print("cm   ");
  delay(500);

  if (distance_value > Range_Safe) {
    LCD.setCursor(2, 0);
    LCD.print("Safe ^^      ");
    // red
    digitalWrite(LED_R_PIN, 0);
    // yellow
    digitalWrite(LED_Y_PIN, 0);
    // green
    digitalWrite(LED_G_PIN, 0);
    // buzzer
    digitalWrite(BUZZER_PIN, 0);
  } else {
    if ((distance_value < Range_Safe)  &&  (distance_value > Range_Warning)) {
      LCD.setCursor(2, 0);
      LCD.print("Warning :(   ");
      digitalWrite(LED_R_PIN, 0);
      digitalWrite(LED_Y_PIN, 0);
      digitalWrite(LED_G_PIN, 1);
      digitalWrite(BUZZER_PIN, 1);
      delay(300);
      digitalWrite(LED_G_PIN, 0);
      digitalWrite(BUZZER_PIN, 0);
    }
    if ((distance_value < Range_Warning)  &&  (distance_value > Range_Danger)) {
      LCD.setCursor(2, 0);
      LCD.print("Dangerous >.<");
      digitalWrite(LED_R_PIN, 0);
      digitalWrite(LED_Y_PIN, 1);
      digitalWrite(LED_G_PIN, 1);
      digitalWrite(BUZZER_PIN, 1);
      delay(100);
      digitalWrite(LED_Y_PIN, 0);
      digitalWrite(LED_G_PIN, 0);
      digitalWrite(BUZZER_PIN, 0);
    }
    if (distance_value < Range_Danger) {
      LCD.setCursor(2, 0);
      LCD.print("Crash T.T    ");
      digitalWrite(LED_R_PIN, 1);
      digitalWrite(LED_Y_PIN, 1);
      digitalWrite(LED_G_PIN, 1);
      digitalWrite(BUZZER_PIN, 1);
    }
  }
}
