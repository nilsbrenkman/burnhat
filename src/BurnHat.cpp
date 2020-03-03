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
#include "LedManager.h"
#include "AbstractProgram.h"
#include "Constants.h"
#include "Rainbow.h"
#include "Sparkle.h"
#include "Randomised.h"

void setup();
void loop();
void loadProgram();
void readInput();
#line 16 "/Users/nils/Projects/Git/BurnHat/src/BurnHat.ino"
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
  switch (programid) {
    case 0: program = new Rainbow();    break;
    case 1: program = new Sparkle();    break;
    case 2: program = new Randomised(); break;
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
    if (program != NULL) {
      if (newbutton > buttonid) {
        Serial.println("Button: LEFT");
        program->button(Button::LEFT);
      } else {
        Serial.println("Button: RIGHT");
        program->button(Button::RIGHT);
      }
    }
    buttonid = newbutton;
  }

  if (digitalRead(BUTTONPIN) == 1) {
    buttonPressed = true;
  } else if (buttonPressed) {
    buttonPressed = false;
    programid = (programid + 1) % 3;
    loadProgram();
  }
}
