
#include <Wire.h>

#include <math.h> 
int BH1750address = 0x23; //setting i2c address
int light = 8;
int ph_probe = A0;

int water_temp = 13;
byte buff[2];
char cmd;
int toggle_flag = 0;

void setup () {
    Serial.begin(57600);
    pinMode(light, OUTPUT);
    Wire.begin();
    digitalWrite(light, LOW); //turn the light on
    toggle_flag= 1;
}

void loop()
{
  if(Serial.available() > 0){
    cmd = Serial.read();
    switch(cmd){
     case 'a':    
       report_lux();
       break;

     default:
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

