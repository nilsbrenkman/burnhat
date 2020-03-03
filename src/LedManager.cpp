#include "LedManager.h"

#define CHIPSET APA102
#define DATA_PIN RX
#define CLOCK_PIN TX
#define COLOR_ORDER BGR

LedManager::LedManager() {
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER, DATA_RATE_MHZ(2)>(leds, 20)
         .setCorrection(TypicalLEDStrip);
  setBrightnessPersistent(1, false);

  for (int i = 0; i < 20; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();

}

void LedManager::setLedStrip(int i, LedStrip * ls) {
  ledStrip[i] = ls;
}

void LedManager::show() {
  FastLED.show();
}

void LedManager::setLedColor(int i, CRGB color) {
  leds[i] = color;
}

void LedManager::setLedHue(int led, int hue) {
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

void LedManager::setAllLeds(CRGB color) {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    setLedColor(i, color);
  }
}

void LedManager::clearAll() {
  setBrightness( pow((brightness / 5.0), 2) * 255 );
  setAllLeds(CRGB::Black);
  FastLED.show();
}

void LedManager::doProgram(AbstractProgram * program) {
  for (int i = 0; i < NUMBER_OF_LEDSTRIPS; i++) {
    program->doProgram(ledStrip[i]);
  }
  FastLED.show();
}

void LedManager::doAction(AbstractAction * action) {
  for (int i = 0; i < NUMBER_OF_LEDSTRIPS; i++) {
    action->doAction(ledStrip[i]);
  }
  FastLED.show();
}

void LedManager::fadeToBlack() {
  fadeToBlackBy(leds, NUMBER_OF_LEDS, 5);
  FastLED.show();
}
