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
#include "afrored.h"
#include "LedManager.h"
#include "AbstractProgram.h"
#include "AbstractAction.h"
#include "Constants.h"
#include "Rainbow.h"
#include "Sparkle.h"
#include "Randomised.h"
#include "Explosion.h"

void ISR_infrared();
void setup();
void loop();
void loadProgram(Button button);
void readInfrared();
Button getButton(int infrared);
#line 19 "/Users/nils/Projects/Git/BurnHat/src/BurnHat.ino"
#define BUTTON_PIN D2
#define ROTARY_PIN A0
#define IR_RECEIVE_PIN D7

const int IR_MSG_LENGTH   = 8;
const int IR_CARRIER_FREQ = 38000;
const int IR_COOLDOWN     = 100;
const int POUND_COOLDOWN  = 2000;

LedManager * ledManager;
AbstractProgram * program;
afrored infrared(IR_MSG_LENGTH, IR_CARRIER_FREQ);
void ISR_infrared() { infrared.ISR(); }

system_tick_t timeLastIrMsg = 0;
system_tick_t timeButtonPound = 0;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);

  attachInterrupt(IR_RECEIVE_PIN, ISR_infrared, CHANGE);
  infrared.attachreceiver(IR_RECEIVE_PIN, ISR_infrared);

  ledManager = new LedManager();
  LedStrip * ledStrip;

  bool reverse = true;
  for (int i = 0; i < 8; i++) {
    ledStrip = new LedStrip(ledManager, i, i * 8, 8, reverse);
    reverse = ! reverse;
  }

  loadProgram(Button::NUM_1);
}

void loop() {
  readInfrared();
  if (program != NULL) {
    program->loop();
  }
}

void loadProgram(Button button) {
  if (program != NULL) {
    program->clear();
    delete program;
  }
  switch (button) {
    case Button::NUM_1: program = new Rainbow();    break;
    case Button::NUM_2: program = new Sparkle();    break;
    case Button::NUM_3: program = new Randomised(); break;
    default: break;
  }
  if (program != NULL) {
    program->init(ledManager);
  }
}

void readInfrared() {
  if (infrared.isnewmsg) {
    if (infrared.checkmsg()) {
      int data = infrared.getmsg();
      Serial.print("Infrared in: ");
      Serial.println(data);
      Button button = getButton(data);
      if (button == Button::POUND) {
        timeButtonPound = millis();
      } else if (millis() < timeButtonPound + POUND_COOLDOWN) {
        loadProgram(button);
      } else {
        if (program != NULL) {
          program->button(button);
        }
      }
      timeLastIrMsg = millis();
    }
  }
  if (millis() > timeLastIrMsg + IR_COOLDOWN) {
    attachInterrupt(IR_RECEIVE_PIN, ISR_infrared, CHANGE);
  }
}

Button getButton(int infrared) {
  switch (infrared) {
    case 5: return Button::STAR;
    case 0: return Button::POUND;
    case 6: return Button::NUM_1;
    case 3: return Button::NUM_2;
    case 7: return Button::NUM_3;
    case 4: return Button::NUM_4;
    case 1: return Button::UP;
    case 2: return Button::DOWN;
    default:
      return Button::NUM_0;
  }
}
