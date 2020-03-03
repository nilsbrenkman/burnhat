#include "AbstractProgram.h"

void AbstractProgram::init(LedManager * lm) {
  ledManager = lm;
}

void AbstractProgram::loop() {
  // do nothing
}

void AbstractProgram::doProgram(LedStrip * ledStrip) {
  // do nothing
}

void AbstractProgram::clear() {
  ledManager->clearAll();
}

void AbstractProgram::button(Button button) {
  // do nothing
}

bool AbstractProgram::doEvent(int delay) {
  long now = millis();
  if (timeout < now) {
    timeout = millis() + delay;
    return true;
  }
  return false;
}
