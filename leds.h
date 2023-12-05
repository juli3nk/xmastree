#ifndef LEDS_H
#define LEDS_H

#include <FastLED.h>

#define LED_PIN 19
#define NUM_LEDS 100
#define LED_TYPE WS2811
#define COLOUR_ORDER RGB

class Leds {
private:
    CRGB leds[NUM_LEDS];

public:
    Leds();

    //static Led& all();
    CRGB* all();
    CRGB get(int index);
    void set(int index, CRGB val);
    void add(int index, CRGB val);
    void toggle(int index, CRGB val);
};

#endif
