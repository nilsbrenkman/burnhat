/*
 * Project BurnHat
 * Description:
 * Author:
 * Date:
 */

#include "application.h"

#define ROTARYPIN A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(ROTARYPIN);
  int voltage = 3300 * analogValue / 4096;
  Serial.println(voltage);
  delay(1000);
}


