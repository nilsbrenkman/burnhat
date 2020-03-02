#include "LedStrip.h"

LedStrip::LedStrip(LedManager * lm, int pos, int st, int si, bool inv) {
  ledManager = lm;
  position = pos;
  start = st;
  size = si;
  inverse = inv;
  left = false;
  ledManager->setLedStrip(position, this);
  ledStripOffset = 0;
  ledStripInverse = false;
}

int LedStrip::getSize() {
  return size;
}

void LedStrip::setLedHue(int led, int hue) {
  if (led < 0 || led >= size) return; // Don't change another strip's leds
  if (inverse) {
    ledManager->setLedWithHue(start + size - led - 1, hue);
  } else {
    ledManager->setLedWithHue(start + led, hue);
  }
}

void LedStrip::setLed(int led, int color) {
  if (led < 0 || led >= size) return; // Don't change another strip's leds
  if (inverse) {
    ledManager->setLed(start + size - led - 1, color);
  } else {
    ledManager->setLed(start + led, color);
  }
}

void LedStrip::doRainbow(int offset) {
  for (int i = 0; i < size; i++) {
    int color = (6 - (i % 6) + offset) % 6;
    setLed(i, color + 2);
  }
}

void LedStrip::doGradient(int offset) {
  int hue = offset;
  if (left) hue -= 5;
  for (int i = 0; i < size; i++) {
    if (inverse) {
      ledManager->setLedWithHue(start + size - i - 1, hue);
    } else {
      ledManager->setLedWithHue(start + i, hue);
    }
    left ? hue -= 5 : hue += 5;
  }
}

bool LedStrip::doExplosion(int offset, int const *colorScheme) {
  int colorSchemeSize = colorScheme[0];
  for (int i = 0; i < size; i++) {
    bool notSet = true;
    for (int j = 0; j < colorSchemeSize; j++) {
      if (offset == j + i) {
        setLed(i, colorScheme[j+1]);
        notSet = false;
      }
    }
    if (notSet) setLed(i, 0);
  }
  return (offset > size + colorSchemeSize);
}

bool LedStrip::doImplosion(int offset, int const *colorScheme) {
  int colorSchemeSize = colorScheme[0];
  for (int i = 0; i < size; i++) {
    bool notSet = true;
    for (int j = 0; j < colorSchemeSize; j++) {
      if (j == offset - MAX_LEDS_PER_LEDSTRIP + i + 1) {
        setLed(i, colorScheme[j+1]);
        notSet = false;
      }
    }
    if (notSet) setLed(i, 0);
  }
  return (offset > MAX_LEDS_PER_LEDSTRIP + colorSchemeSize - 2);
}

void LedStrip::doTrace(int offset, int const *colorScheme) {
  int colorSchemeSize = colorScheme[0];
  for (int i = 0; i < size; i++) {
    bool notSet = true;
    for (int j = 0; j < colorSchemeSize; j++) {
      if ((offset - ledStripOffset + 116) % 116 == i + j) {
        ledStripInverse ? setLed(size - i - 1, colorScheme[j+1]) : setLed(i, colorScheme[j+1]);
        notSet = false;
      }
    }
    if (notSet) ledStripInverse ? setLed(size - i - 1, 0) : setLed(i, 0);
  }
}

bool LedStrip::doTraceWithTrail(int offset, int hue, bool programInverse) {
  bool finalInverse = inverse ^ programInverse;
  if (finalInverse) {
    ledManager->setLedWithHue(start + size - offset - 1, hue);
  } else {
    ledManager->setLedWithHue(start + offset, hue);
  }
  return offset >= size - 1;
}

void LedStrip::doRandom(int offset) {
  int hue = (offset * 2 + (rand() % 10)) % 256;
  int led = rand() % size;
  ledManager->setLedWithHue(start + led, hue);
}
