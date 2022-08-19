// Include library
// Cai dat thu vien
#include "UltraSonicDistanceSensor.h"
#include "LiquidCrystal_I2C.h"

// Declare variables 
// Khai bao bien
int distance_value;
int Range_Danger;
int Range_Warning;
int Range_Close_2;
int Range_Safe;
UltraSonicDistanceSensor distanceSensor(13, 12);

LiquidCrystal_I2C LCD(39, 20, 04);

void setup() {
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  LCD.init();
  // Turn on LCD backlight   
  // Bat den nen LCD 1602
  LCD.backlight();
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(9, OUTPUT);
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
    digitalWrite(A1, 0);
    // yellow
    digitalWrite(A2, 0);
    // green
    digitalWrite(A3, 0);
    // buzzer
    digitalWrite(9, 0);
  } else {
    if ((distance_value < Range_Safe)  &&  (distance_value > Range_Warning)) {
      LCD.setCursor(2, 0);
      LCD.print("Warning :(   ");
      digitalWrite(A1, 0);
      digitalWrite(A2, 0);
      digitalWrite(A3, 1);
      digitalWrite(9, 1);
      delay(300);
      digitalWrite(A3, 0);
      digitalWrite(9, 0);
    }
    if ((distance_value < Range_Warning)  &&  (distance_value > Range_Danger)) {
      LCD.setCursor(2, 0);
      LCD.print("Dangerous >.<");
      digitalWrite(A1, 0);
      digitalWrite(A2, 1);
      digitalWrite(A3, 1);
      digitalWrite(9, 1);
      delay(100);
      digitalWrite(A2, 0);
      digitalWrite(A3, 0);
      digitalWrite(9, 0);
    }
    if (distance_value < Range_Danger) {
      LCD.setCursor(2, 0);
      LCD.print("Crash T.T    ");
      digitalWrite(A1, 1);
      digitalWrite(A2, 1);
      digitalWrite(A3, 1);
      digitalWrite(9, 1);
    }
  }
}
