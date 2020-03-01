#include "LedManager.h"

#define CHIPSET APA102
#define DATA_PIN RX
#define CLOCK_PIN TX
#define COLOR_ORDER BGR

LedManager::LedManager() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER, DATA_RATE_MHZ(2)>(leds, 20)
         .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(5);
  
  myOrange = blend(CRGB::Orange, CRGB::Red, 100);
}

void LedManager::setLedStrip(int i, LedStrip * ls) {
  ledStrip[i] = ls;
}

void LedManager::show() {
  FastLED.show();
}

void LedManager::setLed(int led, int color) {
  switch (color) {
    case 0: setLedWithColor(led, CRGB::Black);  break;
    case 1: setLedWithColor(led, CRGB::White);  break;
    case 2: setLedWithColor(led, CRGB::Red);    break;
    case 3: setLedWithColor(led, myOrange);     break;
    case 4: setLedWithColor(led, CRGB::Yellow); break;
    case 5: setLedWithColor(led, CRGB::Green);  break;
    case 6: setLedWithColor(led, CRGB::Blue);   break;
    case 7: setLedWithColor(led, CRGB::Purple); break;
    default: break;
  }
}

void LedManager::setLedWithColor(int i, CRGB color) {
  leds[i] = color;
}

void LedManager::setLedWithHue(int led, int hue) {
  CHSV hsv;
  hsv.hue = hue % 256;
  hsv.val = 255;
  hsv.sat = 240;
  leds[led] = hsv;
}

void LedManager::setBrightness(int b) {
  FastLED.setBrightness(b);
}

void LedManager::setBrightnessPersistent(int b, bool relative) {
  int newBrightness = b;
  if (relative) {
    newBrightness = brightness + b;
  }
  if (newBrightness < 1 || newBrightness > 5) {
    return;
  }
  brightness = newBrightness;
  Serial.print("brightness: ");
  Serial.println(brightness);
  setBrightness( pow((brightness / 5.0), 2) * 255 );
  FastLED.show();
}

void LedManager::setAllLeds(int color) {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    setLed(i, color);
  }
}

void LedManager::clearAll() {
  setBrightness( pow((brightness / 5.0), 2) * 255 );
  setAllLeds(0);
  FastLED.show();
}

bool LedManager::doProgramWithOffset(int program, int offset, bool andOr) {
  return doProgramWithColorAndOffset(program, 0, offset, andOr);
}

bool LedManager::doProgramWithColorAndOffset(int program, int color, int offset, bool andOr) {
  int const *colorScheme;
  switch (color) {
    case 0:  colorScheme = COLOR_SCHEME_RED;     break;
    case 1:  colorScheme = COLOR_SCHEME_BLUE;    break;
    case 2:  colorScheme = COLOR_SCHEME_RAINBOW; break;
    default: colorScheme = COLOR_SCHEME_BLUE;    break;
  }
  bool done = andOr;
  for (int i = 0; i < NUMBER_OF_LEDSTRIPS; i++) {
    switch (program) {
      case 1: ledStrip[i]->doRainbow(offset);                        break;
      case 2: ledStrip[i]->doGradient(offset);                       break;
      case 3: done &= ledStrip[i]->doExplosion(offset, colorScheme); break;
      case 4: done &= ledStrip[i]->doImplosion(offset, colorScheme); break;
      case 5: ledStrip[i]->doTrace(offset, colorScheme);             break;
      case 6: ledStrip[i]->doRandom(offset);                         break;
      default: break;
    }
  }
  FastLED.show();
  return done;
}

bool LedManager::doTraceWithTrail(int strip, int offset, int hue, bool inverse) {
  return ledStrip[strip]->doTraceWithTrail(offset, hue, inverse);
}

void LedManager::fadeToBlack() {
  fadeToBlackBy(leds, NUMBER_OF_LEDS, 5);
  FastLED.show();
}
