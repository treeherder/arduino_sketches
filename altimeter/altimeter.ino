#include <Servo.h>

Servo grab;
Servo pan_arm;
Servo tilt_arm;
int cmd; //the switch variable
void setup(){
  Serial.begin(9600);
  grab.attach(2);
  tilt_arm.attach(3);
  pan_arm.attach(4);
}

void loop(){
   if(Serial.available() > 0){
      cmd = Serial.read();  // acceept a command
       switch (cmd) {
       case 'o': //open
        grab.write(175);
        break;
       case 'c': //close
        grab.write(5);
        break;
       case 'k': //close
        pan_arm.write(5);
        break;
        case 'l': //close
        pan_arm.write(170);
        break;
        case 'i': //close
        tilt_arm.write(5);
        break;
        case 'u': //close
        tilt_arm.write(170);
        break;
       }                                                     
   }
}
