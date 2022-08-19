// Include library
// Cai dat thu vien
#include "DHT.h"
#include "LiquidCrystal_I2C.h"

// Define connected pin
// Cai dat cong ket noi
#define SOIL_SENSOR_PIN   A3
#define MOTOR_PIN         11
#define LED_PIN           9

//Setup DHT11 Pin to D10
//Cai dat chan ket noi DHT11 voi D10
DHT dht(10, DHT11);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Thiet lap dia chi LCD 0x27 de hien thi 16 ky tu tren hai dong
LiquidCrystal_I2C lcd(0x27, 20, 4); 

// Declare variables 
// Khai bao bien
float analogValue;
float Temp;
float Humidity;
int Soil_Value;
int Soid_Limit = 350;

void setup() {
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  lcd.init(); 
  // Turn on LCD backlight   
  // Bat den nen LCD 1602  
  lcd.backlight();   
  // Start DHT11         
  dht.begin();         
  // Thiet lap chan ket noi o trang thai OUTPUT      
  pinMode(LED_PIN, OUTPUT);   // Pinmode led as output pin
  pinMode(MOTOR_PIN, OUTPUT); // Pinmode motor as output pin
}

void loop(){
    //Count 5 times to actived PUMP not run for long time
    //Tao bo dem 5 lan de bom khong hoat dong lien tuc
    int countTime = 5;
        for(int count = 0; count <  5 ; count++){
          countTime += -1;
        //Averaging 10 samples to prevent noise
        //Lay trung binh 10 mau de chong nhieu
         analogValue = 0;
         for(int count1 = 0; count1 <  10 ; count1++){
          analogValue = (analogValue + analogRead(SOIL_SENSOR_PIN));
          delay(100);
         }
         analogValue = analogValue / 10;
         Soil_Value = round(analogValue);
         Temp = dht.readTemperature(0);
         Humidity = dht.readHumidity();
         //Display temperature, humidity and soil moisture value
         //Hien thi thong so nhiet do, do am khong khi DHT11 va thong so do am dat
         lcd.setCursor(0, 0);
         lcd.print(String(String(String("Air: ") + String(Temp)) + String(char(223))) + String(String(" ") + String(String(Humidity) + String("%     "))));
         lcd.setCursor(0, 1);
         lcd.print(String("Soil: ") + String(String(Soil_Value) + String("  ")));
         lcd.setCursor(0, 2);
         lcd.print(String("Soil Limit: ") + String(Soid_Limit));
         if(Soil_Value > Soid_Limit)  {
             lcd.setCursor(0, 3);
             lcd.print("Pump Actived");
             //Active Pump if countTime = 1 and Soil_Value > Soid_Limit
             //Kich hoat bom khi counttime =1 va Soil_Value > Soid_Limit
             if(countTime == 1) {
                digitalWrite(MOTOR_PIN, HIGH);
                delay(200);
                digitalWrite(MOTOR_PIN, LOW);
             }
         }
         else{
             lcd.setCursor(0, 3);
             lcd.print("              ");
             digitalWrite(MOTOR_PIN, LOW);
         }
         //Turn on alarm Led when Temp > 29 and Humidity > 65
         //Kich hoat led bao dong khi nhiet do > 29 va do am >65
         if((Temp > 29)  ||  (Humidity > 65)){
             digitalWrite(LED_PIN, HIGH);
             delay(100);
             digitalWrite(LED_PIN, LOW);
         }
        }
}
