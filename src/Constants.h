#ifndef Constants_H
#define Constants_H

#include "FastLED.h"

#define BUZZER_PIN     D6
#define IR_RECEIVE_PIN D7
#define LED_DATA_PIN   RX
#define LED_CLOCK_PIN  TX
#define EQ_RESET_PIN   D1
#define EQ_STROBE_PIN  D0
#define EQ_ANALOG_PIN  A0

const int IR_MSG_LENGTH   = 8;
const int IR_CARRIER_FREQ = 38000;
const int IR_COOLDOWN     = 100;
const int ACTION_COOLDOWN = 2000;

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

enum Hue : int {
  RED    =   0,
  ORANGE =  32,
  YELLOW =  72,
  GREEN  =  96,
  BLUE   = 164,
  PURPLE = 192
};

static const int HUE_MOD = 256;

class HueTool {
  public:
    static int add(int hue, int diff) {
      int i = hue + diff;
      while (i < 0) {
        i = i + HUE_MOD;
      }
      return i % HUE_MOD;
    }
};


static const CRGB myOrange = blend(CRGB::Orange, CRGB::Red, 100);

static const CRGB COLOR_SCHEME_RED[3] =  {CRGB::Red, myOrange, CRGB::Yellow};
static const CRGB COLOR_SCHEME_BLUE[3] = {CRGB::Green, CRGB::Blue, CRGB::Purple};

#endif
