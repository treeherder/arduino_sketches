
#include <Wire.h>
#include "RTClib.h"
#include <math.h> 
int BH1750address = 0x23; //setting i2c address
int light = 5;
int ph_probe = A0;

int water_temp = 13
byte buff[2];
RTC_Millis rtc;

void setup () {
    Serial.begin(57600);
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.begin(DateTime(__DATE__, __TIME__));
    pinMode(light, OUTPUT);
    Wire.begin();

}

void loop()
{
     digitalWrite(light, LOW); //turn the light on 
     
}


void report_lux()
{
  int i;
  uint16_t val=0;
  BH1750_Init(BH1750address);
  delay(200);

  if(2==BH1750_Read(BH1750address))
  {
    val=((buff[0]<<8)|buff[1])/1.2;
    Serial.print(val,DEC);     
    Serial.println("[lx]"); 
  }
  delay(150);
}


int BH1750_Read(int address) //
{
  int i=0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while(Wire.available()) //
  {
    buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();  
  return i;
}

void BH1750_Init(int address) 
{
  Wire.beginTransmission(address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();
}
