#include "Rainbow.h"

Rainbow::Rainbow() {
  Serial.println("Rainbow started");
  offset = 0;
  speed = 2; // 0-4, 0 being fast
  direction = Direction::UP;
}

void Rainbow::loop() {
  if (doEvent(5 * pow(2, speed))) {
    ledManager->doProgram(this);
    direction == Direction::UP ? offset++ : offset--;
  }
}

void Rainbow::doProgram(LedStrip * ledStrip) {
  int hue = offset;
  for (int i = 0; i < ledStrip->getSize(); i++) {
    ledStrip->setLedHue(i, hue);
    hue -= 5;
  }
}

void Rainbow::button(Button button) {
  switch (button) {
    case Button::DOWN:
      if (direction == Direction::UP) {
        if (speed == 4) {
          Serial.println("Going DOWN");
          direction = Direction::DOWN;
        } else {
          speed++;
        }
      } else {
        if (speed > 0) {
          speed--;
        }
      }
      break;
    case Button::UP:
      if (direction == Direction::DOWN) {
        if (speed == 4) {
          Serial.println("Going UP");
          direction = Direction::UP;
        } else {
          speed++;
        }
      } else {
        if (speed > 0) {
          speed--;
        }
      }
      break;
  }
}

void Rainbow::clear() {
  ledManager->clearAll();
  delete this;
}
