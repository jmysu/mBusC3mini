/*
  Wokwi LED && Neopixel simulation, C3mBusMiniNeo3
  by Jimmy.Su
*/
#include <Adafruit_NeoPixel.h>
#define PIN        3
#define NUMPIXELS  16
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  delay(10);
  Serial.begin(115200);
  Serial.println("---C3mBusMini V2605 LED Blink & Neo3---");
  delay(100);
  //Serial.end();
  pinMode( 0, OUTPUT);
  //pinMode(20,OUTPUT);
  pixels.begin();
}
int r = 200; int g = 0; int b = 0;
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( 0, HIGH);
  //digitalWrite(20, LOW);
  delay(500);
  digitalWrite( 0, LOW);
  //digitalWrite(20, HIGH);
  
  pixels.clear();
  for (int i=0;i<NUMPIXELS;i++)
     pixels.setPixelColor(i, r, g, b);
  pixels.show();
  delay(500);
  
  int temp = b;
  b = g;
  g = r;
  r = temp;
}