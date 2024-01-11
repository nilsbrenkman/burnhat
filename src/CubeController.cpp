#include "CubeController.h"

CubeController::CubeController() {
  
}

CubeController::refresh() {
  system_tick_t now = millis();
  if (now - timeLastRefresh > LED_REFRESH_RATE) {
    timeLastRefresh = now;
    activeLayer = (activeLayer + 1) % LED_CUBE_SIZE;

    writeDigital(LED_LATCH_PIN, LOW);

    byte data = 0xF0;
    byte layer = 0x08 >> activeLayer;

    shiftOut(LED_DATA_PIN, LED_CLOCK_PIN, LSBFIRST, data ^ layer);

    writeDigital(LED_LATCH_PIN, HIGH);
  }
}