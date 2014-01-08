int trigPin = 6;
int echoPin = 7;
long cm;
long duration;
long distance;

void setup()
{
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);   
 Serial.begin(9600);
}


void loop()
{
 Serial.println(get_distance());
}

long get_distance()
{
  delay(10);  
  //trigger the device
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  

//how long it has been since we sent the ping  
  duration = pulseIn(echoPin, HIGH);

//convert the duration to centimeters ( div by 2 because to and frro)
  cm = duration/27/2;
  return cm;
}
