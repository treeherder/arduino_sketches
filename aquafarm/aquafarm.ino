

#include <Wire.h>
#include <math.h> 
#include "MS561101BA.h"
MS561101BA baro = MS561101BA();
int BH1750address = 0x23; //setting i2c address
int light = 8;
int ph_probe = A0;
int pump = 7;
int heat =6;
int water_temp = 13;
byte buff[2];


void setup () {
    Serial.begin(57600);
    pinMode(light, OUTPUT);
    Wire.begin();
    // You'll have to check this on your breakout schematics
    baro.init(MS561101BA_ADDR_CSB_LOW);
    digitalWrite(light, LOW); //turn the light on 

}

void loop()
{
  if (Serial.available() > 0){
    int key = Serial.read();
    switch(key){
    case 'a':
      report_lux();
      break;
    case 'b':
      temp();
      break;
    case 'c':
      pres();
      break;
    /*case 'd':
      water_ph();
      break;
    case 'e':
      water_temp();
      break;
    case 'f':
      dh_m();
      break;
    case'g':
      pump_on();
      break;
    case 'h'
      pump_off();
      break;
    case'i':
      heat_on();
      break;
    case 'j'
      heat_off();
      break;    
    case 'y':
      light_on();
      break;
    case 'z':
      light_off();
      break;*/
    
    default:
     Serial.println();
     break;
  }
}  
     
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
    Serial.println(val,DEC);     
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
int temp()
{
  float temperature = NULL, pression = NULL;
  while(temperature == NULL) {
    temperature = baro.getTemperature(MS561101BA_OSR_4096);
  }
  Serial.println(temperature);
  
  return 1;
}
int pres()
{
  float temperature = NULL, pression = NULL;
  while(pression == NULL) {
    pression = baro.getPressure(MS561101BA_OSR_4096);
  }
  Serial.println(pression);
  return 1;
}


