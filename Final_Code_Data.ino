//DHT 
// Arduino with PCF8574T I2C LCD example
#include <dht.h>
dht DHT;
#define DHT11_PIN 7
//DHT 

//LCD
#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 
 LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//LCD

//Servo library 
#include <Servo.h> // Declare the Servo pin 
Servo servo1;
Servo servo2;
const int servo1Pin = 9;// Create a servo object 
const int servo2Pin = 3;
//Servo Library

// Bluetooth Control
char Text;
String Spilt;
String angle;
int pos = 0;    // variable to store the servo position
int k1;
// Bluetooth Control

unsigned long prevtime_t1= millis();
unsigned long prevtime_t4= millis();


long interval_t1 = 1000;
long interval_t4 = 500;

void setup() {
    Serial.begin(9600);
    lcd.init();                        // Initialize I2C LCD module
    lcd.backlight();                   // Turn backlight ON
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
    
}

void loop() {

  unsigned long currentTime = millis();
  //DHT
  if (currentTime - prevtime_t1 > interval_t1)
    {
    int chk = DHT.read11(DHT11_PIN);
   
    Serial.print("Temperature =");
    Serial.print(DHT.temperature);
    Serial.print("Humidity =");
    Serial.print(DHT.humidity);
  
    lcd.setCursor(0, 0);
    lcd.print("Temperature ");
    lcd.print(DHT.temperature);
    lcd.setCursor(0, 1);
    lcd.print("Humidity ");
    lcd.print(DHT.humidity);
    //delay(1000);
    
    prevtime_t1 = currentTime;
    }

  //Bluetooth
  if (currentTime - prevtime_t4 > interval_t4)
    {
  if(Serial.available())
  { 
    Text = Serial.read();  

    Spilt = Spilt + Text; 
    if (Text == '*') {

      Serial.println(Spilt);
      Spilt = Spilt.substring(0, Spilt.length() - 1); // Delete last char *
      k1 = Spilt.indexOf('*');
      angle = Spilt.substring(0, k1);
      servo1.write(angle.toInt());
      servo2.write(angle.toInt());
      //delay(10);  
      Spilt = "";
    }
    prevtime_t4 = currentTime;
    }
    }
}
