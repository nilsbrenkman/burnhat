#include "Rainbow.h"

Rainbow::Rainbow() {
  Serial.println("Rainbow started");
  speed = 2; // 0-4, 0 being fast
  timeout = 0;
  offset = 0;
  state = 0;
}

void Rainbow::loop() {
  if (doEvent(5 * pow(2, speed))) {
    // ledManager->doProgramWithOffset(2, offset, false);
    ledManager->doProgram(this);
    state == 0 ? offset++ : offset--;
  }
}

void Rainbow::doProgram(LedStrip * ledStrip) {
  int hue = offset;
  for (int i = 0; i < ledStrip->getSize(); i++) {
    ledStrip->setLedHue(i, hue);
    hue += 5;
  }
}

void Rainbow::sleeve(int buttonid) {
  if (buttonid < 5) {
    speed = buttonid;
    state = -1;
  } else {
    speed = 9 - buttonid;
    state = 0;
  }
}
