int trig_pin = 6;
int echo_pin = 7;
long cm;
long duration;
long distance;
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 8;
int led6 = 9;

void setup()  /*this runs once after power-on */
{
 pinMode(trig_pin, OUTPUT);
 pinMode(echo_pin, INPUT);   
 Serial.begin(9600);
}


void loop() /*this runs after setup() and keeps running until powerdown or completion conditions are met */ 
{
 if (get_distance() > 10 && get_distance() <= 200)
{
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      delay(100);
} //then some thing is really close, light  up a bunch of LEDS

if (get_distance() > 200 && get_distance() <= 400)
 {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);  // light up a moderate number of LED
      delay(100);
 }
if (get_distance() > 400)
{
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, HIGH);  // light up a moderate number of LED
      delay(100);} // that stuff is really far away
}

long get_distance()
{
  delay(10);  
  /*trigger the device*/
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);  

/*count the time between sending and receiving becasue this is going to be the basis for our conversion to distance */  
  duration = pulseIn(echo_pin, HIGH);

/*convert the time in milliseconds to distance in centimeters */
  cm = duration/27/2; /*we devide the result by two to because the observed length of the ping actually represents
  the distance to and from the sensed object*/ 
  return cm;
}

