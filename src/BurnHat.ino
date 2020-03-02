/*
 * Project BurnHat
 * Description:
 * Author:
 * Date:
 */

#include "application.h"
#include "LedManager.h"
#include "AbstractProgram.h"
#include "Rainbow.h"

#define ROTARYPIN A0

LedManager * ledManager;
AbstractProgram * program;

int programid = 0;
int buttonid = 0;

void setup() {
  Serial.begin(9600);

  ledManager = new LedManager();
  LedStrip * ledStrip;

  ledStrip = new LedStrip(ledManager, 0, 0, 10, false);
  ledStrip = new LedStrip(ledManager, 1, 10, 10, true);

  program = new Rainbow();
  program->init(ledManager);
}

void loop() {
  int analogValue = analogRead(ROTARYPIN);
  int newbutton = 10 * analogValue / 4096;
  if (newbutton != buttonid) {
    Serial.print("Button: ");
    Serial.println(newbutton);
    buttonid = newbutton;
    if (program != NULL) {
      program->sleeve(buttonid);
    }
  }
  if (program != NULL) {
    program->loop();
  }
}

