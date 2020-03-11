#include "AbstractProgram.h"

void AbstractProgram::init(LedManager * lm) {
  ledManager = lm;
  timeout = 0;
}

void AbstractProgram::loop() {
  // do nothing
}

void AbstractProgram::doProgram(LedStrip * ledStrip) {
  // do nothing
}

void AbstractProgram::button(Button button) {
  // do nothing
}

bool AbstractProgram::doEvent(int delay) {
  if (timeout < millis()) {
    timeout = millis() + delay;
    return true;
  }
  return false;
}
