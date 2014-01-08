#include <Servo.h>

Servo claw, tilt, pan;

char cmd_byte;
int potpin1 (A0);
int potpin2 (A1);
int potpin3 (A2);

void setup(){
  Serial.begin(9600);
  claw.attach(8);
  tilt.attach(7);
  pan.attach(6);
}
  
void loop(){
  int val1 = analogRead(potpin1);      
  int val2 = analogRead(potpin2);            
  int val3 = analogRead(potpin3);        

  val1 = map(val1, 0, 1023, 0, 179);     
 
  claw.write(val1);  
  delay(50);
  val2 = map(val2, 0, 1023, 0, 179);   
  tilt.write(val2);                   
  delay(50);
  val3 = map(val3, 0, 1023, 0, 179); 
  pan.write(val3);  
  Serial.println(val1)  
  delay(50);                          
}
