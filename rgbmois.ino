#include <Adafruit_NeoPixel.h>
#include <stdint.h>

////////////////////////////////////////////////////
//for the soil moistures sensor
uint32_t s_sig_a = A0;
uint32_t s_sig_b = A2;
uint32_t soil_sense = A1;


//thanks, adafruit!

uint32_t max_dry = 600;
uint32_t medium_dry = 300;
uint32_t medium_wet = 100;
uint32_t very_wet = 0;

int r_value;
int g_value;
int b_value;

uint32_t reading;


#define PIN 6
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_RGB + NEO_KHZ400);


void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //color(strip.Color(255, 0, 0), 50); // blue
  //color(strip.Color(0, 255, 0), 50); // red
  //color(strip.Color(0, 0, 255), 50); // green
  Serial.println(soil_moisture());
  /*
  if (soil_moisture() >=450){color(strip.Color(0,255,0), 50);} // red -- dry
  else if (soil_moisture() <450 && soil_moisture() >=400) {  color(strip.Color(0,255,50), 50); // orange -- pretty dry 
  else if (soil_moisture() <400 && soil_moisture() >=350) {  color(strip.Color(0,255,150), 50); // yellow -- not too dry
  else if (soil_moisture() <350 && soil_moisture() >300) {  color(strip.Color(0,255,255), 50); // light green -- pretty good 
  else if (soil_moisture() <=300 && soil_moisture() >200) {color(strip.Color(0,0,255), 50);} // green good
  else if (soil_moisture() >150 && soil_moisture() <=200) {color(strip.Color(155,0,255), 50);} //a little wet-- light green/blue
  else if (soil_moisture() >100 && soil_moisture() <=150) {color(strip.Color(255,0,255), 50);} //a little too wet -- turquise
  else if (soil_moisture() >50 && soil_moisture() <=100) {color(strip.Color(255,0,0), 50);} //blue -- too wet
  else if (soil_moisture() <=50) {color(strip.Color(255,255,0), 10);} //purple -- soaking*
*/    


reading = soil_moisture();
Serial.println(reading);
if ( reading > max_dry) {
  r_value =  255;
  g_value =  0;
  b_value =  0; // no blue in the dry region  
} else if  ( reading > medium_dry ) {
  r_value =  0  + 255*(reading - medium_dry)/(max_dry - medium_dry);
  g_value =  255 - 255*(reading - medium_dry)/(max_dry - medium_dry);
  b_value =  0; // no blue in the dry region
} else if ( medium_dry > reading && reading > medium_wet ){
  r_value =  0; // no red in the wet region
  g_value =  255 - 255*(medium_dry - reading)/(medium_dry - medium_wet);
  b_value =  0  + 255*(medium_dry - reading)/(medium_dry - medium_wet);
} else if ( medium_wet > reading && reading >= very_wet)  {
  r_value =  0  + 255*(medium_wet - reading)/(medium_wet - very_wet);
  g_value =  0; // no green in the very_wet region
  b_value =  255; // for style keep blue, just add purple
}
color(strip.Color(b_value, r_value, g_value),10);
//green in the middle
//subtract from green add to red
//subtract from blue add to green
//add red to blue

 }


  
// Fill the dots one after the other with a color
void color(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

uint32_t soil_moisture() {

pinMode(s_sig_a, OUTPUT);
digitalWrite(s_sig_a, LOW);
pinMode(soil_sense, OUTPUT);
digitalWrite(soil_sense, LOW);
pinMode(s_sig_a, OUTPUT);
digitalWrite(s_sig_b, LOW);
delay(10); //200
//next we make the voltage divider
pinMode(soil_sense, INPUT); //reads the voltage divider
// A0 and A4 to outputs
pinMode(s_sig_a, OUTPUT);
digitalWrite(s_sig_a,HIGH);
pinMode(s_sig_b, OUTPUT);
digitalWrite(s_sig_b,LOW);
//finally we poll for voltage reading
delay(25); //was 500
return(analogRead(soil_sense));

}



