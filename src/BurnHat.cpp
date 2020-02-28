/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/nils/Projects/Git/BurnHat/src/BurnHat.ino"
/*
 * Project BurnHat
 * Description:
 * Author:
 * Date:
 */

#include "application.h"

void setup();
void loop();
#line 10 "/Users/nils/Projects/Git/BurnHat/src/BurnHat.ino"
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


