#include <Servo.h>

Servo grab;
Servo pan_arm;
Servo tilt_arm;
int cmd; //the switch variable
void setup(){
  Serial.begin(9600);
  grab.attach(3);
  tilt_arm.attach(2);
  pan_arm.attach(4);
}

void loop(){
   if(Serial.available() > 0){
      cmd = Serial.read();  // acceept a command
       switch (cmd) {
       case 'demo':
        grab.write(180);
        break;
       default: 
         Serial.println("defaulting");
       }                                                     
   }
}
