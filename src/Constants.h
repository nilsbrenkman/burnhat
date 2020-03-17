#ifndef Constants_H
#define Constants_H

#include "FastLED.h"

FASTLED_USING_NAMESPACE;

enum class Button {
  NUM_0,
  NUM_1,
  NUM_2,
  NUM_3,
  NUM_4,
  NUM_5,
  NUM_6,
  NUM_7,
  NUM_8,
  NUM_9,
  STAR,
  POUND,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  OK,
  NONE
};

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

const CRGB myOrange = blend(CRGB::Orange, CRGB::Red, 100);

const CRGB COLOR_SCHEME_RED[3] =  {CRGB::Red, myOrange, CRGB::Yellow};
const CRGB COLOR_SCHEME_BLUE[3] = {CRGB::Green, CRGB::Blue, CRGB::Purple};

#endif
