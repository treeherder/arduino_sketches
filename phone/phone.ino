#include "TinyGPS.h"
#include <Wire.h>
#include <IntersemaBaro.h>
#define compass 0x1E
#include <SoftwareSerial.h>
SoftwareSerial nss(6, 255);            // Yellow wire to pin 6
SoftwareSerial phone (7,8);
unsigned char buff[512]; /* buffer */
int index=0;
Intersema::BaroPressure_MS5607B baro(true);
TinyGPS gps;

void setup() {
 
  phone.begin(19200); /* baud rate */ 
  nss.begin(4800);
  Serial.begin(9600); 
  baro.init();
  // Set operating mode to continuous
  Wire.beginTransmission(compass); 
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  power_state();
}

void loop(){
phone_interface();

}


float get_bearing() {
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
int get_height() {
  int alt = baro.getHeightCentiMeters();
  Serial.println(alt);
  delay(400);
  return alt;
}

void phone_interface(){
phone.listen();
if (phone.available())              /* wait for data */
  {
    while(phone.available())  
    {
      buff[index++]=phone.read();     /* writing data into buff*/
      if(index == 256)break;
  }
    Serial.write(buff,index);         /*tx*/
    clr_buff_arr();              /*zero buffer array and index*/
    index = 0;           
 
  }
  if (Serial.available())            /*wait*/
    phone.write(Serial.read());       /* rx*/
}
void clr_buff_arr()
{
  for (int i=0; i<index;i++)
    { buff[i]=NULL;}                  /* clear each index */
}


void print_gps(){
  bool newdata = false;
  unsigned long start = millis();
  while (millis() - start < 5000) {  // Update every 5 seconds
    if (feedgps())
      newdata = true;
  }
  if (newdata) {
    gpsdump(gps);
  }
}

// Get and process GPS data
void gpsdump(TinyGPS &gps) {
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  Serial.print(flat, 4); Serial.print(", "); 
  Serial.println(flon, 4);
}

// Feed data as it becomes available 
bool feedgps() {
  nss.listen();
  while (nss.available()) {
    if (gps.encode(nss.read()))
      return true;
  }
  return false;
}

void power_state()
{
  pinMode(9, OUTPUT); 
  digitalWrite(9,LOW);
  delay(1000);
  digitalWrite(9,HIGH);
  delay(2000);
  digitalWrite(9,LOW);
  delay(3000);
}
