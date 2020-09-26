#include "UpDown.h"

UpDown::UpDown() {
  if (debug) Serial.println("UpDown started");
  direction = Direction::UP;
  position = 0;
  hue = 0;
}

boolean UpDown::run() {
  ledManager->doAction(this);
  if (direction == Direction::UP) {
      if (position < MAX_LEDS_PER_LEDSTRIP - 1) {
        position++;
      } else {
        direction = Direction::DOWN;
        position--;
      }
  } else { // direction = Direction::DOWN
      if (position > 0) {
        position--;
      } else {
        direction = Direction::UP;
        position++;
      }
  }
  hue = hue + hueDiff;
  boolean done = position == 0 && hue > 213 - (MAX_LEDS_PER_LEDSTRIP * 2 * hueDiff);
  delay(25);
  return ! done;
}

void UpDown::doAction(LedStrip * ledStrip) {
  for (int i = 0; i < ledStrip->getSize(); i++) {
    if (i == position) {
      ledStrip->setLedHue(i, hue);
    } else {
      ledStrip->setLedColor(i, CRGB::Black);
    }
  }
}
