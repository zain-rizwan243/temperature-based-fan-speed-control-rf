//library for interfacing rf module
#include <VirtualWire.h>

//library for 16x2 LCD
#include<LiquidCrystal.h>

//defining digital pin 3 to be used for PWM(0-255)
int Trigger_Pin=3;
int SensorData; // Sensors
char SensorCharMsg[5]; // RF Transmission container

//defing pins for 16x2 LCD 
const int rs=12;
const int en=10;
const int d4=7;
const int d5=6;
const int d6=5;
const int d7=4;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7); //function for accessing LCD

void setup()
{
  Serial.begin(9600);
  // VirtualWire
  // Initialise the IO and ISR
  // Bits per sec
  vw_setup(2000); 
  // Start the receiver PLL running
  vw_rx_start();
  lcd.begin(16,2); //initializing LCD
} // END void setup

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  // Non-blocking
  if (vw_get_message(buf, &buflen))
  {
    int i;
    // Message with a good checksum received, dump it.
    for (i = 0; i < buflen; i++)
    {
      // Fill SensorCharMsg Char array with corresponding
      // chars from buffer.
      SensorCharMsg[i] = char(buf[i]);
    }
    // Null terminate the char array
    // This needs to be done otherwise problems will occur
    // when the incoming messages has less digits than the
    // one before.
    SensorCharMsg[buflen] = '\0';
    // Convert Sensor1CharMsg Char array to integer
    SensorData = atoi(SensorCharMsg);
    // Printing Sensor data on Serial Monitor
    Serial.print("Sensor  ");
    Serial.println(SensorData);
    lcd.setCursor(1,0); //set cursor to 1st column and zeroth row
    
    //conditions based on Temperature to control FAN speed accordingly
    if(SensorData<=15){
  analogWrite(Trigger_Pin,0); //sending PWM signal to the Gate of nMOSFET
  lcd.clear(); //clearing LCD to print new message
  lcd.print("Fan OFF");
}
else if (SensorData<=20){
  analogWrite(Trigger_Pin,40);
  lcd.clear();
  lcd.print("Fan speed 15%");
  lcd.setCursor(0,1); //setting cursor to zeroth column and 1st row
  lcd.print("T= ");
  lcd.print(SensorData);
  lcd.setCursor(8,1); //setting cursor to 8th columnn and 1st row
  lcd.print("PWM: 40");
  
}
else if(SensorData<=25){
  analogWrite(Trigger_Pin,70);
  lcd.clear();
  lcd.print("Fan speed 30%");
  lcd.setCursor(0,1);
  lcd.print("T= ");
  lcd.print(SensorData);
  lcd.setCursor(8,1);
  lcd.print("PWM: 70");
}
else if(SensorData<=30){
  analogWrite(Trigger_Pin,110);
  lcd.clear();
  lcd.print("Fan speed 40%");
  lcd.setCursor(0,1);
  lcd.print("T= ");
  lcd.print(SensorData);
  lcd.setCursor(8,1);
  lcd.print("PWM: 110");
}
else if(SensorData<=35){
  analogWrite(Trigger_Pin,150);
  lcd.clear();
  lcd.print("Fan speed 55%");
  lcd.setCursor(0,1);
  lcd.print("T= ");
  lcd.print(SensorData);
  lcd.setCursor(8,1);
  lcd.print("PWM: 150");
}
else if(SensorData<=40){
  analogWrite(Trigger_Pin,190);
  lcd.clear();
  lcd.print("Fan speed 75%");
  lcd.setCursor(0,1);
  lcd.print("T= ");
  lcd.print(SensorData);
  lcd.setCursor(8,1);
  lcd.print("PWM: 190");
}
else if(SensorData<=45){
  analogWrite(Trigger_Pin,220);
  lcd.clear();
  lcd.print("Fan speed 75%");
  lcd.setCursor(0,1);
  lcd.print("T= ");
  lcd.print(SensorData);
  lcd.setCursor(8,1);
  lcd.print("PWM: 220");
  }
else if(SensorData<=50){
  analogWrite(Trigger_Pin,255);
  lcd.clear();
  lcd.print("Fan speed 100%");
  lcd.setCursor(0,1);
  lcd.print("T= ");
  lcd.print(SensorData);
  lcd.setCursor(8,1);
  lcd.print("PWM: 255");    
}
else{
  analogWrite(Trigger_Pin,255);
  lcd.setCursor(1,0);
  lcd.clear();
  lcd.print("   Maxed Out!");
  lcd.setCursor(0,1);
  lcd.print("T= ");
  lcd.print(SensorData);
  lcd.setCursor(8,1);
  lcd.print("PWM: 255");
}
  }
  delay(1000); //check temp every second and adjust FAN Speed accordingly
}
