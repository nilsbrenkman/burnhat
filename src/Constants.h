#ifndef Constants_H
#define Constants_H

#include "FastLED.h"

static const bool debug = true;

FASTLED_USING_NAMESPACE;

enum class Button {
  NUM_0 = 0xFF4AB5,
  NUM_1 = 0xFF6897,
  NUM_2 = 0xFF9867,
  NUM_3 = 0xFFB04F,
  NUM_4 = 0xFF30CF,
  NUM_5 = 0xFF18E7,
  NUM_6 = 0xFF7A85,
  NUM_7 = 0xFF10EF,
  NUM_8 = 0xFF38C7,
  NUM_9 = 0xFF5AA5,
  STAR  = 0xFF42BD,
  POUND = 0xFF52AD,
  UP    = 0xFF629D,
  DOWN  = 0xFFA857,
  LEFT  = 0xFF22DD,
  RIGHT = 0xFFC23D,
  OK    = 0xFF02FD,
  NONE  = 0xFFFFFF
};

static const Button BUTTONS[] = { Button::NUM_0, Button::NUM_1, Button::NUM_2, Button::NUM_3, Button::NUM_4, Button::NUM_5, Button::NUM_6, Button::NUM_7, Button::NUM_8, Button::NUM_9, Button::STAR, Button::POUND, Button::UP, Button::DOWN, Button::LEFT, Button::RIGHT, Button::OK };

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

static const CRGB myOrange = blend(CRGB::Orange, CRGB::Red, 100);

static const CRGB COLOR_SCHEME_RED[3] =  {CRGB::Red, myOrange, CRGB::Yellow};
static const CRGB COLOR_SCHEME_BLUE[3] = {CRGB::Green, CRGB::Blue, CRGB::Purple};

#endif
