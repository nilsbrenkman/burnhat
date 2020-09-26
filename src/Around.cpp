#include "Around.h"

Around::Around() {
  if (debug) Serial.println("Around started");
  position = 0;
  hue = 0;
}

boolean Around::run() {
  ledManager->doAction(this);
  position = (position + 1) % NUMBER_OF_LEDSTRIPS;
  hue = hue + hueDiff;
  delay(25);
  boolean done = position == 0 && hue > 213 - (NUMBER_OF_LEDSTRIPS * hueDiff);
  return ! done;
}

void Around::doAction(LedStrip * ledStrip) {
  boolean on = position == ledStrip->getPosition();
  for (int i = 0; i < ledStrip->getSize(); i++) {
    if (on) {
      ledStrip->setLedHue(i, hue);
    } else {
      ledStrip->setLedColor(i, CRGB::Black);
    }
  }
}
