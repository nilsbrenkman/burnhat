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
#include "TM1637.h"

void setup();
void loop();
#line 11 "/Users/nils/Projects/Git/BurnHat/src/BurnHat.ino"
#define ROTARYPIN A0
#define CLK A4
#define DIO A5

void displayNumber(unsigned int number);

TM1637 display(CLK, DIO);
int8_t digits[] = {0x00, 0x00, 0x00, 0x00};

void setup() {
  Serial.begin(9600);
  display.set();
  display.init();
}

void loop() {
  int analogValue = analogRead(ROTARYPIN);
  int voltage = 3300 * analogValue / 4096;
  displayNumber(voltage);
  Serial.println(voltage);
  delay(1000);
}

void displayNumber(unsigned int number) {
  if (number > 9999) {
    number = 9999;
  }
  
  digits[0] = number / 1000;
  digits[1] = number % 1000 / 100;
  digits[2] = number % 100 / 10;
  digits[3] = number % 10;
  display.display(digits);
}
