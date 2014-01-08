int led_1 = 3; //an LED is is a "lght emitting diode"
int led_2 = 5;  //when we give it current, it makes light
int ldr = A0;
void setup(){  /* this runs once */
pinMode(led_1, OUTPUT);
pinMode(led_2, OUTPUT);
Serial.begin(9600);
}

void loop(){

a_debug();
echo();

}

void alarm(int value){
  int light_level  = analogRead(ldr);
  if(value >= light_level){digitalWrite(led_1, HIGH);}
  else{digitalWrite(led_1, LOW);}
}

void echo(){
  int light_level = analogRead(ldr);
  analogWrite(led_2, light_level);
}

void a_debug(){Serial.println(analogRead(ldr));}
