//DHT 
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

unsigned long prevtime_t1= millis();
//unsigned long prevtime_t2= millis();
unsigned long prevtime_t3= millis();
unsigned long prevtime_t4= millis();
//unsigned long prevtime_t5= millis();

long interval_t1 = 1000;
//long interval_t2 = 2000;
long interval_t3 = 2000;
long interval_t4 = 500;
//long interval_t5 = 1000;

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

   // SDA to A4 and SCL to A5
    lcd.setCursor(0, 0);
    lcd.print("Temperature ");
    lcd.print(DHT.temperature);
    lcd.setCursor(0, 1);
    lcd.print("Humidity ");
    lcd.print(DHT.humidity);
    //delay(1000);
    
    prevtime_t1 = currentTime;
    }

  //UV and Rain Sensor
  if (currentTime - prevtime_t3 > interval_t3)
    {
    int rainsensor = analogRead(A0);// print out the value you read:
   Serial.println("           ");
   Serial.print("rainsensor= ");
   Serial.print(rainsensor);
   //delay(200);        // delay in between reads for stability
    
    
  int uvsensor = analogRead(A1);// print out the value you read:
  Serial.println("           ");
  Serial.print("uvsensor=");
  Serial.print(uvsensor); // UV Sensor Value
  Serial.println("           ");
  Serial.println("           ");

    if(rainsensor < 700 || uvsensor > 250){
    servo1.write(0); 
    servo1.write(180);
    servo2.write(0); 
    servo2.write(180);
    }
    else {
    servo1.write(180); 
    servo1.write(0);
    servo2.write(180); 
    servo2.write(0);   
     }
    prevtime_t3 = currentTime;
    }
    }
