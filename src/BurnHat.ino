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

#include "afrored.h"

const int IR_MSG_LENGTH   = 8;
const int IR_CARRIER_FREQ = 38000;
const int ir_cooldown     = 100;
const int PIN_IR_LED      = D2;
const int PIN_IR_RECEIVER = D7;

afrored infrared(IR_MSG_LENGTH, IR_CARRIER_FREQ);
void ISR_infrared() { infrared.ISR(); }

int time_last_irmsg = 0;

#define BUTTON_PIN D2
#define ROTARY_PIN A0
#define IR_RECEIVE_PIN D7

LedManager * ledManager;
AbstractProgram * program;

// IRrecv irrecv(IR_RECEIVE_PIN);
// decode_results results;

int programid = 0;
int buttonid = 0;
boolean buttonPressed = false;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);

  attachInterrupt(PIN_IR_RECEIVER, ISR_infrared, CHANGE);
  infrared.attachreceiver(PIN_IR_RECEIVER, ISR_infrared);

  // irrecv.enableIRIn(); // Start the receiver

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
  // readInfrared();
  doInfraredReceive();
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

// void readInfrared() {
//   if (irrecv.decode(&results)) {
//     Serial.println(results.value, HEX);
//     irrecv.resume(); // Receive the next value
//   }
// }

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

void doInfraredReceive() {
  if (infrared.isnewmsg) {
    if (infrared.checkmsg()) {
      int data = infrared.getmsg();
      Serial.print("Infrared in: ");
      Serial.println(data);
      time_last_irmsg = millis();
    }
  }
  if (millis() > time_last_irmsg + ir_cooldown) {
    attachInterrupt(PIN_IR_RECEIVER, ISR_infrared, CHANGE);
  }
}
