/*
 * Project BurnHat
 * Description:
 * Author:
 * Date:
 */

#include "application.h"
#include "afrored.h"
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

#define BUTTON_PIN D2
#define ROTARY_PIN A0
#define IR_RECEIVE_PIN D7

const int IR_MSG_LENGTH   = 8;
const int IR_CARRIER_FREQ = 38000;
const int IR_COOLDOWN     = 100;
const int ACTION_COOLDOWN = 2000;

LedManager * ledManager;
AbstractProgram * program;
// afrored infrared(IR_MSG_LENGTH, IR_CARRIER_FREQ);
// void ISR_infrared() { infrared.ISR(); }

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

system_tick_t timeLastIrMsg    = 0;
system_tick_t timeButtonAction = 0;
Button actionButton;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);

  // attachInterrupt(IR_RECEIVE_PIN, ISR_infrared, CHANGE);
  // infrared.attachreceiver(IR_RECEIVE_PIN, ISR_infrared);
  irrecv.enableIRIn();

  ledManager = new LedManager();

  bool reverse = true;
  for (int i = 0; i < 8; i++) {
    new LedStrip(ledManager, i, i * 8, 8, reverse);
    reverse = ! reverse;
  }

  loadProgram(Button::NUM_4);
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
  action->clear();
}

void readInfrared() {
  // if (infrared.isnewmsg) {
  //   if (infrared.checkmsg()) {
  //     int data = infrared.getmsg();
  //     Serial.print("Infrared in: ");
  //     Serial.println(data);
  //     Button button = getButton(data);
  //     if (button == Button::POUND || button == Button::STAR) {
  //       timeButtonAction = millis();
  //       actionButton = button;
  //     } else if (millis() < timeButtonAction + ACTION_COOLDOWN) {
  //       if (actionButton == Button::POUND) {
  //         loadProgram(button);
  //       } else if (actionButton == Button::STAR) {
  //         runAction(button);
  //       }
  //     } else {
  //       if (program != NULL) {
  //         program->button(button);
  //       }
  //     }
  //     timeLastIrMsg = millis();
  //   }
  // }
  // if (millis() > timeLastIrMsg + IR_COOLDOWN) {
  //   attachInterrupt(IR_RECEIVE_PIN, ISR_infrared, CHANGE);
  // }

  if (irrecv.decode(&results)) {
    Button button = getButton(results.value);
    if (button == Button::NONE) {
      irrecv.resume(); // Receive the next value
      return;
    }
    if (button == Button::POUND || button == Button::STAR) {
      timeButtonAction = millis();
      actionButton = button;
    } else if (millis() < timeButtonAction + ACTION_COOLDOWN) {
      if (actionButton == Button::POUND) {
        loadProgram(button);
      } else if (actionButton == Button::STAR) {
        runAction(button);
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
  switch (infrared) {
    case 16728765: return Button::STAR;
    case 16732845: return Button::POUND;

    case 16738455: return Button::NUM_1;
    case 16750695: return Button::NUM_2;
    case 16756815: return Button::NUM_3;
    case 16724175: return Button::NUM_4;
    case 16718055: return Button::NUM_5;
    case 16743045: return Button::NUM_6;
    case 16716015: return Button::NUM_7;
    case 16726215: return Button::NUM_8;
    case 16734885: return Button::NUM_9;
    case 16730805: return Button::NUM_0;

    case 16736925: return Button::UP;
    case 16754775: return Button::DOWN;
    case 16720605: return Button::LEFT;
    case 16761405: return Button::RIGHT;
    case 16712445: return Button::OK;
    default:
      return Button::NONE;
  }
}
