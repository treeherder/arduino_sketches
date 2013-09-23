#include <SPI.h>
#include <SD.h>
#include <TFT.h>  // Arduino LCD library

#include <Wire.h>
#include "RTClib.h"
#include <DHT11.h>

#define DHTPIN 11
#define DHTTYPE DHT11
#define sd_cs  12
#define lcd_cs 6
#define dc     7
#define rst    8  
TFT TFTscreen = TFT(lcd_cs, dc, rst);

DHT dht(DHTPIN, DHTTYPE);
/*it's important that we set these variable per DHT sensor on our project*/

RTC_Millis rtc;

void setup () {
    Serial.begin(57600);
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.begin(DateTime(__DATE__, __TIME__));
    TFTscreen.begin();
    TFTscreen.background(0, 0, 0);
    TFTscreen.stroke(100, 200, 255);
    TFTscreen.println("welcome to the growbot");
     delay(1000);
}

void loop () {
    DateTime now = rtc.now();
    
    TFTscreen.print(now.year(), DEC);
    TFTscreen.print('/');
    TFTscreen.print(now.month(), DEC);
    TFTscreen.print('/');
    TFTscreen.print(now.day(), DEC);
    TFTscreen.print(' ');
    TFTscreen.print(now.hour(), DEC);
    TFTscreen.print(':');
    TFTscreen.print(now.minute(), DEC);
    TFTscreen.print(':');
    TFTscreen.print(now.second(), DEC);
    TFTscreen.println();
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    TFTscreen.println("Failed to read from DHT");
  } 
  else {
    TFTscreen.print("Humidity: "); 
    TFTscreen.print(h);
    TFTscreen.print(" %\t");
    TFTscreen.print("Temperature: "); 
    TFTscreen.print(t);
    TFTscreen.println(" *C");
  }
    delay(3000);
}
