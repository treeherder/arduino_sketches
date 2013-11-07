#include <Servo.h>

Servo claw;
Servo tilt;
Servo pan;

char cmd_byte;


void setup(){
  claw.attach(13);
  tilt.attach(12);
  pan.attach(11);
}
  
  
void loop(){
swing_tilt(90);
swing_pan(20);
delay(10000);
}
  
void grab(int i){ 
  claw.write(i); //closed
}
void swing_tilt(int i){ 
  tilt.write(i); //closed
}
void swing_pan(int i, int ii){
  tilt.write(90) 
  pan.write(i); //closed
  tilt.write(ii);
}
