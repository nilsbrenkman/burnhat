#include "SingleColor.h"

SingleColor::SingleColor() {
  if (debug) Serial.println("SingleColor started");
}

void SingleColor::afterInit() {
  setHue();
}

void SingleColor::button(Button button) {
  switch (button) {
    case Button::DOWN:  addHue(-10);      break;
    case Button::UP:    addHue(10);       break;
    case Button::LEFT:  addHue(-1);       break;
    case Button::RIGHT: addHue(1);        break;
    case Button::NUM_0: numericButton(0); break;
    case Button::NUM_1: numericButton(1); break;
    case Button::NUM_2: numericButton(2); break;
    case Button::NUM_3: numericButton(3); break;
    case Button::NUM_4: numericButton(4); break;
    case Button::NUM_5: numericButton(5); break;
    case Button::NUM_6: numericButton(6); break;
    case Button::NUM_7: numericButton(7); break;
    case Button::NUM_8: numericButton(8); break;
    case Button::NUM_9: numericButton(9); break;
    default:
      break;
  }
}

void SingleColor::setHue() {
  if (debug) {
    Serial.print("Setting hue: ");
    Serial.println(hue);
  }
  ledManager->setAllHue(hue);
}

void SingleColor::addHue(int diff) {
  hue = HueTool::add(hue, diff);
  setHue();
}

void SingleColor::numericButton(int button) {
  if (lastButtonTime < millis() - BUTTON_COOLDOWN) {
    currentInput = 0;
  }
  lastButtonTime = millis();
  input[currentInput] = button;
  if (currentInput < 2) {
    currentInput++;
    return;
  }
  int newHue = 100 * input[0] + 10 * input[1] + input[2];
  if (newHue > 255) {
    if (debug) {
      Serial.print("Invalid hue: ");
      Serial.println(newHue);
    }
    currentInput = 0;
    return;
  }
  hue = newHue;
  setHue();
}
