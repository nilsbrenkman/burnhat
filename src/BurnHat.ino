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
#include "Snake.h"
#include "Explosion.h"

void setup();
void loop();
void loadProgram(Button button);
void runAction(Button button);
void readInfrared();
Button getButton(long infrared);

#define BUTTON_PIN D2
#define ROTARY_PIN A0
#define IR_RECEIVE_PIN D7

const int IR_MSG_LENGTH   = 8;
const int IR_CARRIER_FREQ = 38000;
const int IR_COOLDOWN     = 100;
const int ACTION_COOLDOWN = 2000;

LedManager * ledManager;
AbstractProgram * program;

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

system_tick_t timeLastIrMsg    = 0;
system_tick_t timeButtonAction = 0;
Button actionButton;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);

  irrecv.enableIRIn();

  ledManager = new LedManager();

  bool reverse = true;
  for (int i = 0; i < 8; i++) {
    new LedStrip(ledManager, i, i * 8, 8, reverse);
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
    ledManager->clearAll();
    delete program;
    program = NULL;
  }
  switch (button) {
    case Button::NUM_1: program = new Rainbow();    break;
    case Button::NUM_2: program = new Sparkle();    break;
    case Button::NUM_3: program = new Randomised(); break;
    case Button::NUM_4: program = new Snake();      break;
    default: break;
  }
  if (program != NULL) {
    program->init(ledManager);
  }
}

void runAction(Button button) {
  AbstractAction * action = NULL;
  switch (button) {
    case Button::NUM_1: action = new Explosion();   break;
    default: return;
  }
  action->init(ledManager);
  ledManager->clearAll();
  while (action->run()) {
    // keep going
  }
  ledManager->clearAll();
  delete action;
}

void readInfrared() {
  if (irrecv.decode(&results)) {
    Button button = getButton(results.value);
    if (button == Button::NONE) {
      if (debug) {
        Serial.print("Unknown IR: ");
        Serial.println(results.value, HEX);
      }
      irrecv.resume(); // Receive the next value
      return;
    }
    if (debug) {
      Serial.print("Button IR: ");
      Serial.println(results.value, HEX);
    }
    if (button == Button::POUND || button == Button::STAR || button == Button::OK) {
      timeButtonAction = millis();
      actionButton = button;
    } else if (millis() < timeButtonAction + ACTION_COOLDOWN) {
      if (actionButton == Button::POUND) {
        loadProgram(button);
      } else if (actionButton == Button::STAR) {
        runAction(button);
      } else if (actionButton == Button::OK) {
        if (button == Button::DOWN) {
          ledManager->setBrightnessPersistent(-1, true);
          timeButtonAction = millis();
        } else if (button == Button::UP) {
          ledManager->setBrightnessPersistent(1, true);
          timeButtonAction = millis();
        }
      }
    } else {
      if (program != NULL) {
        program->button(button);
      }
    }
    irrecv.resume(); // Receive the next value
  }
}

Button getButton(long infrared) {
  for (const auto button : BUTTONS) {
    if (infrared == (long) button) {
      return button;
    }
  }
  return Button::NONE;
}
