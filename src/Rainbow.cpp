#include "Rainbow.h"

Rainbow::Rainbow() {
  Serial.println("Rainbow started");
  offset = 0;
  speed = 2; // 0-4, 0 being fast
  direction = UP;
}

void Rainbow::loop() {
  if (doEvent(5 * pow(2, speed))) {
    ledManager->doProgram(this);
    direction == UP ? offset++ : offset--;
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
      if (direction == UP) {
        if (speed == 4) {
          Serial.println("Going DOWN");
          direction = DOWN;
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
      if (direction == DOWN) {
        if (speed == 4) {
          Serial.println("Going UP");
          direction = UP;
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
