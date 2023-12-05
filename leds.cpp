#include <Arduino.h>
#include <FastLED.h>

#include "leds.h"

Leds::Leds() {
  // out pin for led strip
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOUR_ORDER>(leds, NUM_LEDS);
}

CRGB* Leds::all() {
  return leds;
}
CRGB Leds::get(int index) {
  return leds[index];
}
void Leds::set(int index, CRGB val) {
  leds[index] = val;
}
void Leds::add(int index, CRGB val) {
  leds[index] += val;
}
void Leds::toggle(int index, CRGB val) {
  leds[index] |= val;
}
