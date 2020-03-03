#include "Sparkle.h"

Sparkle::Sparkle() {
  Serial.println("Sparkle started");
  state = 0; // waiting for next Sparkle
  mode = 0;
  timeout = 0;
}

void Sparkle::loop() {
  long now = millis();
  if (doEvent(0)) {
    switch (state) {
      case 0:
        state = 1;
        led = rand() % NUMBER_OF_LEDS;
        switch (mode) {
          case 0:
            ledManager->setLedColor(led, CRGB::White);
            break;
          case 1:
            int c = rand() % 6;
            // ledManager->setLed(led, c + 2);
            break;
        }
        timeout = now + 100;
        break;
      case 1:
        state = 0;
        ledManager->setLedColor(led, CRGB::Black);
        ledManager->show();
        timeout = now + (rand() % 500);
        break;
    }
  }
  if (state == 1) {
    int t = timeout - now;
    if (t < 50) {
      ledManager->setBrightness(255 * t / 100);
    } else {
      t = 100 - t;
      ledManager->setBrightness(255 * t / 100);
    }
    ledManager->show();
  }
}

void Sparkle::button(Button button) {
  switch (button) {
    case Button::UP:   mode = 0; break;
    case Button::DOWN: mode = 1; break;
    default: break;
  }
}
