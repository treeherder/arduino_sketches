#include <DHT11.h>
#define DHTPIN 7 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
/*it's important that we set these variable per DHT sensor on our project*/

void setup() {
  Serial.begin(9600); 
 
  dht.begin();
}

void loop() {
  /*reading the sensor will be slow, (about 1.4 of a second, and the data might be old
 (up to 8x that time)*/ 
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
}
