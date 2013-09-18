#include <Wire.h>

#define Addr 0x1E               //  i2c address

void setup() {
  Serial.begin(9600);
  delay(100);                   // if you forget this step, your results will be muddled
  Wire.begin();
  
  // Set operating mode to continuous
  Wire.beginTransmission(Addr); 
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
}
int compass() {
  int x, y, z;

  // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x03));       // most significant byte first
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // request two bytes per axis
  if(Wire.available() <=6) {    // need  6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
return(x,y,z);  
}
