// Include library
// Cai dat thu vien
#include <SoftwareSerial.h>
#include "LiquidCrystal_I2C.h"
#include "MKL_DFRobotDFPlayerMini.h"

// Define connected sensor pin
// Dat ten cong ket noi cho cam bien
#define  SENSOR1_PIN    11
#define  SENSOR2_PIN    10

// Initialize DFPlayer Mini on the second serial port on RX and TX pins 
// Khoi tao DFPlayer Mini qua cong ket noi noi tiep tren hai chan RX va TX
SoftwareSerial mySoftwareSerial(13, 12); 
DFRobotDFPlayerMini myDFPlayer; 
// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Thiet lap dia chi LCD 0x27 de hien thi 16 ky tu tren hai dong
LiquidCrystal_I2C LCD(0x27, 16, 2);  

// Declare variables 
// Khai bao bien
int soKhach = 0;
int checkin = 0;

void setup(){
// Initialize LCD 1602 to display
// Khoi tao LCD 1602 de hien thi
  LCD.init();  
// Turn on LCD backlight   
// Bat den nen LCD 1602    
  LCD.backlight();
// We initialize software serial connection 
// Khoi tao cong ket noi software serial   
  mySoftwareSerial.begin(9600);
//Use softwareSerial to communicate with mp3 module.
//Sử dụng software serial ket noi voi module mp3.
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.setTimeOut(500);
// Set Sensor Pin as Input
// Thiet lap chan SENSOR la Input
  pinMode(SENSOR1_PIN, INPUT); 
  pinMode(SENSOR2_PIN, INPUT); 
}

void loop() {
  // Setting LCD Display
  // Thiet lap hien thi tren LCD
    LCD.setCursor(0, 0);
    LCD.print("Capacity");
    LCD.setCursor(9, 0);
    LCD.print("Checkin");
    LCD.setCursor(0, 1);
    LCD.print(soKhach);
    LCD.print("/40");
    LCD.print("   ");
    LCD.setCursor(10, 1);
    LCD.print(checkin);
// If SENSOR1 be Actived
// Nếu SENSOR1 duoc kich hoat
    if (digitalRead(SENSOR1_PIN) == 0) {
// Wait until SENSOR2 be Actived and SENSOR1 be Inactived
// Doi den khi SENSOR2 kich hoat va SENSOR1 ngung kich hoat
     while (!((digitalRead(SENSOR2_PIN) == 0)&&(digitalRead(SENSOR1_PIN) == 1))) {}
// Play Welcome sound and prin on LCD
// Phat tieng noi xin chao va hien thi len LCD
        myDFPlayer.playMp3Folder(1);  
        soKhach += 1;
        checkin += 1;
        LCD.setCursor(0, 0);
        LCD.print("MakerLab Welcome");
        delay(1000);
    }
// If SENSOR2 be Actived
// Nếu SENSOR2 duoc kich hoat
    if (digitalRead(SENSOR2_PIN) == 0) {
// Wait until SENSOR1 be Actived and SENSOR2 be Inactived
// Doi den khi SENSOR1 kich hoat va SENSOR2 ngung kich hoat
    while (!((digitalRead(SENSOR1_PIN) == 0)&&(digitalRead(SENSOR2_PIN) == 1))) {}
        myDFPlayer.playMp3Folder(2); 
        if (soKhach > 0) 
        {
            soKhach -= 1;
         }
      LCD.setCursor(0, 0);
      LCD.print("MakerLab Goodbye"); 
      delay(1000);  
    } 
}
