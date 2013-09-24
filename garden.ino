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
TFT screen = TFT(lcd_cs, dc, rst);

DHT dht(DHTPIN, DHTTYPE);
/*it's important that we set these variable per DHT sensor on our project*/

RTC_Millis rtc;

void setup () {
    Serial.begin(57600);
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.begin(DateTime(__DATE__, __TIME__));
    screen.begin();
    screen.background(0, 0, 0);
    screen.stroke(100, 200, 255);
    screen.println("welcome to the growbot");
     delay(1000);
}

void loop () {
    
    DateTime now = rtc.now();
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    screen.text("temperature    humidity", 0,10);
    screen.println("");
    screen.print("");
    screen.print(t);
    screen.print("           ");
    screen.println(h);
    screen.print(now.year(), DEC);
    screen.print('/');
    screen.print(now.month(), DEC);
    screen.print('/');
    screen.print(now.day(), DEC);
    screen.print(' ');
    screen.print(now.hour(), DEC);
    screen.print(':');
    screen.print(now.minute(), DEC);
    screen.print(':');
    screen.print(now.second(), DEC);
    screen.println();
    delay(3000);
    screen.background(0, 0, 0);

}
