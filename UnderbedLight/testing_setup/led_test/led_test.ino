#include <Adafruit_NeoPixel.h>

#define LED_PIN   13
#define LED_COUNT 60

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(20); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  fullColor(strip.Color(255, 0, 0), 1000);
  fullColor(strip.Color(0, 255, 0), 1000);
  fullColor(strip.Color(0, 0, 255), 1000);
  fullColor(strip.Color(255, 255, 0), 1000);
  fullColor(strip.Color(0, 255, 255), 1000);
  fullColor(strip.Color(255, 0, 255), 1000);
  fullColor(strip.Color(255, 255, 255), 1000);
}

void fullColor(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(wait);
}
