#include "Randomised.h"

Randomised::Randomised() {
  if (debug) Serial.println("Randomised started");
  offset = 0;
}

void Randomised::loop() {
  ledManager->fadeToBlack();
  if (doEvent(50)) {
    ledManager->doProgram(this);
    offset++;
  }
}

void Randomised::doProgram(LedStrip * ledStrip) {
  int hue = (offset * 2 + (rand() % 10)) % 256;
  int led = rand() % ledStrip->getSize();
  ledStrip->setLedHue(led, hue);
}
