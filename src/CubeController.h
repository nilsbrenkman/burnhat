#ifndef CubeController_H
#define CubeController_H

#define LED_DATA_PIN   RX
#define LED_CLOCK_PIN  TX
#define LED_LATCH_PIN  A7

const int LED_REFRESH_RATE = 10;
const int LED_CUBE_SIZE    = 2;

class CubeController {
  public:
    CubeController();
    refresh();
  private:
    system_tick_t timeLastRefresh = 0;
    int activeLayer = -1;
    byte led_cube[LED_CUBE_SIZE][LED_CUBE_SIZE]; // x[y][z]

};

#endif