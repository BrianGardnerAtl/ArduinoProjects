# Underbed Lighting Project

This repo contains the code and instructions for a motion-activated lighting
system that activates at night.

## Components

* Motion sensor
* Ambient light sensor
* LED light strip
* Arduino nano

## Code Overview

Using the Adafruit NeoPixel library to control the LED strip.

Ambient light sensor sends input to digital pin 4 (D4).
Motion sensor sends input to digital pin 6.

The setup block sets up the light and motion sensor pins as input, enables
serial debugging, and initializes the light strip.

The loop function works via a state machine that has several different states:

* off
* fadeIn
* on
* fadeOut

The loop checks various combinations of the light and motion sensor to drive the
state machine.
