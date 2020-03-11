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
#include "IRremote.h"
#include "LedManager.h"
#include "AbstractProgram.h"
#include "AbstractAction.h"
#include "Constants.h"
#include "Rainbow.h"
#include "Sparkle.h"
#include "Randomised.h"
#include "Explosion.h"

void setup();
void loop();
void loadProgram();
void readInfrared();
void readInput();
#line 19 "/Users/nils/Projects/Git/BurnHat/src/BurnHat.ino"
#define BUTTON_PIN D2
#define ROTARY_PIN A0
#define IR_RECEIVE_PIN D7

LedManager * ledManager;
AbstractProgram * program;

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

int programid = 0;
int buttonid = 0;
boolean buttonPressed = false;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);

  irrecv.enableIRIn(); // Start the receiver

  ledManager = new LedManager();
  LedStrip * ledStrip;

  bool reverse = true;
  for (int i = 0; i < 8; i++) {
    ledStrip = new LedStrip(ledManager, i, i * 8, 8, reverse);
    reverse = ! reverse;
  }

  loadProgram();
  program = new Rainbow();
  program->init(ledManager);
}

void loop() {
  readInput();
  readInfrared();
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

void readInfrared() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}

void readInput() {
  int analogValue = analogRead(ROTARY_PIN);
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

  if (digitalRead(BUTTON_PIN) == 1) {
    buttonPressed = true;
  } else if (buttonPressed) {
    buttonPressed = false;
    programid = (programid + 1) % 3;
    loadProgram();
    
    // AbstractAction * action = new Explosion();
    // action->init(ledManager);
    // ledManager->clearAll();
    // while (action->run()) {
    //   delay(25);
    // }
    // action->clear();
    // delete action;
    
  }
}
