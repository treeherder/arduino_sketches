int co_sensor = A0;

void setup(){
  pinMode(co_sensor, INPUT);
  /*set the sensor to be input*/
  Serial.begin(9600);
  /*beign serial @ baudrate of 9600 */
}
void loop(){
  Serial.println(analogRead(co_sensor));
}
