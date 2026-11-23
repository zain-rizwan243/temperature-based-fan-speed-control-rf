//Libraries for interfacing DS18B20 sensor
#include <OneWire.h>
#include <DallasTemperature.h>

//Library for interafcing rf module
#include <VirtualWire.h>

//library for interfacing 16x2 LCD
#include <LiquidCrystal.h>


//defining pin to receive data from temperature sensor
#define ONE_WIRE_BUS 8

//creating object to communicate with DS18B20 sensor
OneWire oneWire(ONE_WIRE_BUS);

//object to access the temperature sensor
DallasTemperature sensors(&oneWire);
char SensorCharMsg[5]; //char array to store sensor data


//defining pins for 16x2 LCD
const int rs=10;
const int en=11;
const int d4=5;
const int d5=4;
const int d6=3;
const int d7=2;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7); //fucntion for accessing LCD

void setup(){ 
 // for debugging
 Serial.begin(9600);
 
 sensors.begin();
 // VirtualWire setup
 vw_setup(2000);     // Bits per sec

 lcd.begin(16,2); //initializing LCD
}

void loop() {
  //requesting sensor to send temperature data
  sensors.requestTemperatures();
  //Current temperature being stored into float varable.
  float tempC = sensors.getTempCByIndex(0);


  //Printing temperature on Serial monitor
  Serial.print("Temperature ");
  Serial.print(tempC);
  Serial.println("C");

  //printing temperature data on LCD screen
  lcd.setCursor(1,0);
  lcd.print("Temp = ");
  lcd.print(tempC);
  lcd.println(" C ");
  lcd.setCursor(0,1);
  lcd.print("RF Temp Cont FAN");
  
  // Convert integer data to Char array directly 
  itoa(tempC,SensorCharMsg,10);
  delay(500);
  
 vw_send((uint8_t *)SensorCharMsg, strlen(SensorCharMsg));  // send the message
 vw_wait_tx(); // Wait until the whole message is gone
 delay(1000);// repeat every second
 
}
