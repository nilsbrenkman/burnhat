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
#include "Sparkle.h"

#define BUTTONPIN D2
#define ROTARYPIN A0

LedManager * ledManager;
AbstractProgram * program;

int programid = 0;
int buttonid = 0;
boolean buttonPressed = false;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTONPIN, INPUT);

  ledManager = new LedManager();
  LedStrip * ledStrip;

  ledStrip = new LedStrip(ledManager, 0, 0, 10, false);
  ledStrip = new LedStrip(ledManager, 1, 10, 10, true);

  loadProgram();
  program = new Rainbow();
  program->init(ledManager);
}

void loop() {
  readInput();
  if (program != NULL) {
    program->loop();
  }
}

void loadProgram() {
  if (program != NULL) {
    program->clear();
    delete program;
  }
  Serial.print("Loading program: ");
  Serial.println(programid);
  switch (programid) {
    case 0: program = new Rainbow();      break;
    case 1: program = new Sparkle();      break;
    default: break;
  }
  if (program != NULL) {
    program->init(ledManager);
  }
}

void readInput() {
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

  if (digitalRead(BUTTONPIN) == 1) {
    buttonPressed = true;
  } else if (buttonPressed) {
    buttonPressed = false;
    programid = (programid + 1) % 2;
    loadProgram();
  }
}
