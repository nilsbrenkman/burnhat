
 * Project LedCube
 * Description:
 * Author:
 * Date:
 */

#include "application.h"

#define LED_DATA_PIN   RX
#define LED_CLOCK_PIN  TX
#define LED_LATCH_PIN  A7

const int LED_REFRESH_RATE = 10;
const int LED_CUBE_SIZE = 2;

void setup();
void loop();

system_tick_t timeLastLedRefresh = 0;
int activeLedLayer = -1;

byte led_cube[LED_CUBE_SIZE][LED_CUBE_SIZE]; // x[y][z]

void setup() {
  Serial.begin(9600);

  pinMode(LED_DATA_PIN,  OUTPUT);
  pinMode(LED_CLOCK_PIN, OUTPUT);
  pinMode(LED_LATCH_PIN, OUTPUT);

  delay(500);
}

void loop() {

  system_tick_t now = millis();
  if (now - timeLastLedRefresh > LED_REFRESH_RATE) {
    timeLastLedRefresh = now;
    activeLedLayer = (activeLedLayer + 1) % LED_CUBE_SIZE;

    writeDigital(LED_LATCH_PIN, LOW);

    byte data = 0xF0;
    byte layer = 0x08 >> activeLedLayer;

    shiftOut(LED_DATA_PIN, LED_CLOCK_PIN, LSBFIRST, data ^ layer);

    writeDigital(LED_LATCH_PIN, HIGH);
  }
  
}
