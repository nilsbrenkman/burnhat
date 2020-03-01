/*
 * Project BurnHat
 * Description:
 * Author:
 * Date:
 */

#include "application.h"
#include "LedManager.h"

#define ROTARYPIN A0

LedManager * ledManager;
int offset;

void setup() {
  Serial.begin(9600);

  offset = 0;

  ledManager = new LedManager();
  LedStrip * ledStrip;

  ledStrip = new LedStrip(0, 10, false, false, 0);
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(0, ledStrip);
  ledStrip = new LedStrip(10, 10, true, false, 0);
  ledStrip->setLedManager(ledManager);
  ledManager->setLedStrip(1, ledStrip);

}

void loop() {
  int analogValue = analogRead(ROTARYPIN);
  int voltage = 3300 * analogValue / 4096;
  Serial.print("Voltage: ");
  Serial.println(voltage);

  ledManager->doProgramWithOffset(2, offset, false);
  offset = offset + 1;

  delay(25);
}

