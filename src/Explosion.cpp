#include "Explosion.h"

Explosion::Explosion() {
  if (debug) Serial.println("Explosion started");
  originX = rand() % NUMBER_OF_LEDSTRIPS;
  originY = rand() % (MAX_LEDS_PER_LEDSTRIP - 4) + 2;
  offset = 0;
}

boolean Explosion::run() {
  active = false;
  ledManager->doAction(this);
  offset++;
  delay(25);
  return active;
}

void Explosion::doAction(LedStrip * ledStrip) {
  int position = ledStrip->getPosition();
  for (int i = 0; i < ledStrip->getSize(); i++) {
    int tempX = (originX + NUMBER_OF_LEDSTRIPS - position) % NUMBER_OF_LEDSTRIPS;
    int diffX = 2 * min(tempX, NUMBER_OF_LEDSTRIPS - tempX);
    int diffY = abs(originY - i);
    double distance = sqrt(pow(diffX, 2) + pow(diffY, 2)) * 5;
    int hue = (offset - distance) * 3;
    if (distance <= offset && hue < 60) {
      ledStrip->setLedHue(i, hue);
      active = true;
    } else {
      ledStrip->setLedColor(i, CRGB::Black);
    }
  }
}
