#ifndef AbstractLedStrip_H
#define AbstractLedStrip_H

#include <memory>
#include "LedManager.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE;

class LedManager;

class LedStrip {
  public:
    LedStrip(LedManager * ledManager, int position, int start, int size, bool inverse);
    int getSize();
    void setLedColor(int led, CRGB color);
    void setLedHue(int led, int hue);
  protected:
    LedManager * ledManager;
    int position;
    int start;
    int size;
    int inverse;
};

#endif
