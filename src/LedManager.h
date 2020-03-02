#ifndef LedManager_H
#define LedManager_H

#include <math.h>
#include "LedStrip.h"
#include "AbstractProgram.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

const int NUMBER_OF_LEDS        = 20;
const int NUMBER_OF_LEDSTRIPS   = 2;
const int MAX_LEDS_PER_LEDSTRIP = 10;

const int COLOR_SCHEME_RED[7] =     {6, 2, 2, 3, 3, 4, 4}; // first integer is size
const int COLOR_SCHEME_BLUE[5] =    {4, 6, 6, 7, 7};
const int COLOR_SCHEME_RAINBOW[7] = {6, 2, 3, 4, 5, 6, 7};
const int COLOR_SCHEME_BLUE_2[13] = {12, 6, 7, 6, 7, 6, 7, 6, 7, 6, 7, 6, 7};

class LedStrip;

class AbstractProgram;

class LedManager {
  public:
    LedManager();
    void setLedStrip(int i, LedStrip * ledStrip);
    void show();
    void setLedColor(int led, CRGB color);
    void setLedHue(int led, int hue);
    void setBrightness(int b);
    void setBrightnessPersistent(int b, bool relative);
    void setAllLeds(CRGB color);
    void clearAll();
    void doProgram(AbstractProgram * program);
    void fadeToBlack();
  private:
    unsigned long combineDataFields(int data1, int data2, int data3);
    CRGB leds[NUMBER_OF_LEDS];
    CRGB myOrange;
    LedStrip * ledStrip[NUMBER_OF_LEDSTRIPS];
    int brightness;
};

#endif
