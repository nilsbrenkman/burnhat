#include "Explosion.h"

Explosion::Explosion() {
  Serial.println("Explosion started");
  originX = rand() % NUMBER_OF_LEDSTRIPS;
  originY = rand() % (MAX_LEDS_PER_LEDSTRIP - 4) + 2;
  offset = 0;
}

boolean Explosion::run() {
  active = false;
  ledManager->doAction(this);
  offset++;
  return active;
}

void Explosion::doAction(LedStrip * ledStrip) {
  int position = ledStrip->getPosition();
  for (int i = 0; i < ledStrip->getSize(); i++) {
    int diffX = abs(originX - position);
    int diffY = abs(originY - i);
    double distance = sqrt(pow(diffX, 2) + pow(diffY, 2)) * 5;
    int hue = (offset - distance) * 3;
    if (distance <= offset && hue < 72) {
      ledStrip->setLedHue(i, hue);
      active = true;
    } else {
      ledStrip->setLedColor(i, CRGB::Black);
    }
  }
}

void Explosion::clear() {
  ledManager->clearAll();
  delete this;
}
