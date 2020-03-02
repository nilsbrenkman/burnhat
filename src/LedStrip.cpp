#include "LedStrip.h"

LedStrip::LedStrip(LedManager * lm, int pos, int st, int si, bool inv) {
  ledManager = lm;
  position = pos;
  start = st;
  size = si;
  inverse = inv;
  ledManager->setLedStrip(position, this);
}

int LedStrip::getSize() {
  return size;
}

void LedStrip::setLedColor(int led, CRGB color) {
  if (led < 0 || led >= size) return; // Don't change another strip's leds
  if (inverse) {
    ledManager->setLedColor(start + size - led - 1, color);
  } else {
    ledManager->setLedColor(start + led, color);
  }
}

void LedStrip::setLedHue(int led, int hue) {
  if (led < 0 || led >= size) return; // Don't change another strip's leds
  if (inverse) {
    ledManager->setLedHue(start + size - led - 1, hue);
  } else {
    ledManager->setLedHue(start + led, hue);
  }
}
