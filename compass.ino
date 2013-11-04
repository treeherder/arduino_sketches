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
void loop(){Serial.println(compass());}

float compass() {
  int x, y, z;

  // Initiate communications with compass
  Wire.beginTransmission(compass);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(compass, 6);    // Request 6 bytes; 2 bytes per axis
  if(Wire.available() <=6) {    // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();

  }
   // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(x, y);
   
  // Correct for when signs are reversed.
  /*if(heading < 0)
    heading += 2*PI;
   
  // Convert radians to degrees for readability.
  float h_deg = heading * 180/M_PI; 
  */return (heading);
}
