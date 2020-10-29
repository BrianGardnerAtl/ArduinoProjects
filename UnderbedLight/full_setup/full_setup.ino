#include <Adafruit_NeoPixel.h>

#define LED_PIN   13
#define LED_COUNT 60

// TODO figure out good max brightness for lights
#define MAX_BRIGHTNESS 255
#define FADE_IN_DURATION 2000
#define ON_DURATION 5000

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define LIGHT 4 // digital read from D4
int lightSensorValue;
int previousLightValue;

#define MOTION 6 // digital read from D2
int motionSensorValue;

int fadeDelay = FADE_IN_DURATION / MAX_BRIGHTNESS;

void setup() {
  // Send debug info through Serial
  Serial.begin(9600);
  Serial.println("Setup");
  // Input pins
  pinMode(LIGHT, INPUT);
  pinMode(MOTION, INPUT);
  // setup led strip
  strip.begin();
  strip.show();
  strip.setBrightness(255);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lightSensorValue = digitalRead(LIGHT);
  Serial.print("Light sensor reading = ");
  Serial.println(lightSensorValue);


  if (lightSensorValue == LOW) {
    if (lightSensorValue != previousLightValue) {
      Serial.println("turn light off");
      turnOutLight();
    }
  } else {
    Serial.println("Check motion value");
    motionSensorValue = digitalRead(MOTION);
    if (motionSensorValue == HIGH) {
      Serial.println("Motion, turn on light");
      fadeIn();
      delay(ON_DURATION);
      fadeOut();
    } else {
      Serial.println("No motion, don't turn on light");
    }
  }
  
  previousLightValue = lightSensorValue;
  delay(1000);
}

void fullColor(uint32_t color) {
  strip.fill(color);
  strip.show();
}

void turnOutLight() {
  fullColor(strip.Color(0, 0, 0));
}

void fadeIn() {
  uint32_t currentColor = strip.getPixelColor(0); 
  // This gets just the red value from the color. The others aren't needed since
  // all RGB values are the same
  uint8_t index = currentColor >> 16;
  for(int i=index; i<MAX_BRIGHTNESS; i++) {
    strip.fill(strip.Color(i, i, i));
    strip.show();
    delay(fadeDelay);
  }
}

void fadeOut() {
  uint32_t currentColor = strip.getPixelColor(0);
  // This gets just the red value from the color. The others aren't needed since
  // all RGB values are the same
  uint8_t index = currentColor >> 16;
  for(int i=index; i>=0; i--) {
    strip.fill(strip.Color(i, i, i));
    strip.show();
    delay(fadeDelay);
  }
}
