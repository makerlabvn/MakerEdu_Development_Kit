// Include library
// Cai dat thu vien
#include "LiquidCrystal_I2C.h"
#include "IRremote.h"

// set the LCD address to 0x27 for a 16 chars and 2 line display
// Thiet lap dia chi LCD 0x27 de hien thi ky tu LCD 16 ky tu và 2 dong
LiquidCrystal_I2C LCD(0x27, 16, 2);  

// Define connected pin
// Dat ten cong ket noi chan LED va BUZZER
#define LED_RED_PIN       A1
#define LED_YELLOW_PIN    A2
#define LED_GREEN_PIN     A3
#define FAN_PIN           9
#define IR_RECEIVE_PIN    10

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
  // Set connected pin as output pin
  // Thiet lap cong ket noi la chan tin hieu ra
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  
  // Start the receiver
  // Thiet lap chan tin hieu nhan hong ngoai
  IrReceiver.begin(IR_RECEIVE_PIN);
  
  //Display Remote button selection
  //Hien thi man hinh lua chon nut nhan
  LCD.setCursor(0, 0);
  LCD.print("Remote button");
  LCD.setCursor(0, 1);
  LCD.print("0  1  2  3");
}

void loop()
{
    if (IrReceiver.decode()){
        Serial.println(IrReceiver.decodedIRData.command);
        if (IrReceiver.decodedIRData.command == 12){
        // Set PWM 25%
        // Dat gia tri PWM de dieu chinh toc do quat la 25%
        analogWrite(FAN_PIN, 64);
        digitalWrite(LED_GREEN_PIN, HIGH);
        digitalWrite(LED_YELLOW_PIN, LOW);
        digitalWrite(LED_RED_PIN, LOW);
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Level 1 ^^");
        LCD.setCursor(0, 1);
        LCD.print("~~ Mat khong?~~");
        }
    
        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value

        delay(100);

        if (IrReceiver.decodedIRData.command == 0x18){
        // Set PWM 50%
        // Dat gia tri PWM de dieu chinh toc do quat la 50%
        analogWrite(FAN_PIN, 123);
        digitalWrite(LED_GREEN_PIN, LOW);
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_YELLOW_PIN, HIGH);
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Level 2 :)");
        LCD.setCursor(0, 1);
        LCD.print("~~ Mat khong?~~");
        }
        if (IrReceiver.decodedIRData.command == 0x5e){
        // Set PWM 100%
        // Dat gia tri PWM de dieu chinh toc do quat la 100%
        analogWrite(FAN_PIN, 255); 
        digitalWrite(LED_GREEN_PIN, LOW);
        digitalWrite(LED_YELLOW_PIN, LOW);
        digitalWrite(LED_RED_PIN, HIGH);
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Level 3 :)");
        LCD.setCursor(0, 1);
        LCD.print("Cho tui nghi diiii");
        }
        if (IrReceiver.decodedIRData.command == 0x16){
        // Set PWM 0% to turn off fan
        // Tat quat
        analogWrite(FAN_PIN, 0); 
        digitalWrite(LED_GREEN_PIN, LOW);
        digitalWrite(LED_YELLOW_PIN, LOW);
        digitalWrite(LED_RED_PIN, LOW);
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Cam on ban ^^");
        LCD.setCursor(0, 1);
        LCD.print(":>>>>");
        }
    }
}
