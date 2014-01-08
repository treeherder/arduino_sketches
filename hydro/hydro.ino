#include <DHT11.h>
#define DHTPIN 7  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
/*it's important that we set these variable per DHT sensor on our project*/


int hydro_1 = A0;
int hydro_2 = A1;
int hydro_3 = A2;
int hydro_4 = A3;
int hydro_5 = A4;
int key;


void moisture()
{
  Serial.println("1    2    3    4    5");
  Serial.print(analogRead(hydro_1), DEC);
  Serial.print("  ");
  Serial.print(analogRead(hydro_2), DEC);
  Serial.print("  ");
  Serial.print(analogRead(hydro_3), DEC);
  Serial.print("  ");
  Serial.print(analogRead(hydro_4), DEC);
  Serial.print("  ");
  Serial.println(analogRead(hydro_5), DEC);
}

void temp_hum(){

/*reading the sensor will be slow, (about 1.4 of a second, and the data might be old
 (up to 8x that time)*/ 
 delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  t = t * 9/5  + 32;

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *F");
  }
  delay(1000);
}

void setup(){
  pinMode(hydro_1, OUTPUT);
  pinMode(hydro_2, OUTPUT);
  pinMode(hydro_3, OUTPUT);
  pinMode(hydro_4, OUTPUT);
  pinMode(hydro_5, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  
}

void loop(){
  if (Serial.available() > 0){
    key = Serial.read();
    switch(key){
    case 'a':
      moisture();
      break;
    case 'b':
      temp_hum();
      break;
    default:
     Serial.println();
     break;
  }
}
}

