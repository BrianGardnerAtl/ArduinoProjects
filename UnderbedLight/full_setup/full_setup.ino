#include <Adafruit_NeoPixel.h>

#define LED_PIN   13
#define LED_COUNT 60

// TODO figure out good max brightness for lights
#define MAX_BRIGHTNESS 255
#define FADE_IN_DURATION 2000
#define ON_DURATION 5000
#define elapsedTime millis() - timerMillis

unsigned long timerMillis; // For setting time to check when to transition to fade out state.

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define LIGHT 4 // digital read from D4.
int lightSensorValue; // for collecting the current light reading.

#define MOTION 6 // digital read from D6
int motionSensorValue; // for collecting the current motion sensor reading.

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

// Possible state values the lights can be in
enum { off, fadeIn, on, fadeOut };
byte currentState;

void loop() {
  switch (currentState) {
    off:
      if (detectBrightLight()) {
        break;
      }
      // Check for motion to determine if the lights should be turned on.
      if (detectMotion()) {
        // detected motion, move to the fade in state
        currentState = fadeIn;
      }
      break;
    fadeIn:
      fadeInLights();
      // mark the time we hit full brightness and set the state to on.
      timerMillis = millis();
      currentState = on;
      break;
    on:
      if (elapsedTime > ON_DURATION) {
        // Time has expired with no addition motion, fade out the lights
        currentState = fadeOut;
      } else {
        // check if there's bright light and fade out
        if (detectBrightLight()) {
          currentState = fadeOut;
          break;
        }
        // check if there's motion and reset the timer
        if (detectMotion()) {
          timerMillis = millis();
        }
      }
      break;
    fadeOut:
      for(int i=getCurrentColor(); i>=0; i--) {
        strip.fill(strip.Color(i, i, i));
        strip.show();
        // if we detect motion and no bright light then fade the lights back in.
        if (detectMotion() && detectLowLight()) {
          // detected motion in low light, move to the fade in state and exit.
          currentState = fadeIn;
          break;
        }
        delay(fadeDelay);
      }
      if (currentState == fadeOut) {
        currentState = off;
      }
      break;
    default:
      // If we have not yet set up the current state then default to off
      currentState = off;
      break;
  }
}

bool detectMotion() {
  motionSensorValue = digitalRead(MOTION);
  if (motionSensorValue == HIGH) {
    return true;
  } else {
    return false;
  }
}

bool detectLowLight() {
  lightSensorValue = digitalRead(LIGHT);
  if (lightSensorValue == LOW) {
    return true;
  } else {
    return false;
  }
}

bool detectBrightLight() {
  lightSensorValue = digitalRead(LIGHT);
  if (lightSensorValue == HIGH) {
    return true;
  } else {
    return false;
  }
}

byte getCurrentColor() {
  unsigned long currentColor = strip.getPixelColor(0); 
  // This gets just the red value from the color since they're all the same.
  byte color = currentColor >> 16;
  return color;
}

void fadeInLights() {
  for(int i=getCurrentColor(); i<MAX_BRIGHTNESS; i++) {
    strip.fill(strip.Color(i, i, i));
    strip.show();
    delay(fadeDelay);
  }
}
