#include <SoftwareSerial.h>
 
SoftwareSerial serial_device(7, 8);
unsigned char buff[512]; /* buffer */
int index=0;    
void setup()
{
  serial_device.begin(9600);               /* baud rate */  
  Serial.begin(9600);             /* works better when they match*/
 
}
 
void loop()
{
  if (serial_device.available())              /* wait for data */
  {
    while(serial_device.available())  
    {
      buff[index++]=serial_device.read();     /* writing data into buff*/
      if(index == 64)break;
  }
    Serial.write(buff,index);         /*tx*/
    clr_buff_arr();              /*zero buffer array and index*/
    index = 0;           
 
 
  }
  if (Serial.available())            /*wait*/
    serial_device.write(Serial.read());       /* rx*/
}
void clr_buff_arr()
{
  for (int i=0; i<index;i++)
    { buff[i]=NULL;}                  /* clear each index */
}

