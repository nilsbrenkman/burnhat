#include "Snake.h"

#define HUE_START 160
#define HUE_END   128
#define HUE_FOOD  64
#define HUE_FAIL  0
#define HUE_WIN   96

Snake::Snake() {
  if (debug) {
    Serial.println("Snake started");
  }
  reset();
}

void Snake::loop() {
  if (doEvent(500)) {
    switch (calculateAction()) {
      case Action::Move: move(); break;
      case Action::Eat:  eat();  break;
      case Action::Fail: fail(); break;
      case Action::Win:  win();  break;
    }
  }
}

void Snake::doProgram(LedStrip * ledStrip) {
  for (auto it = snake.begin(); it != snake.end(); it++) {
    if (it->x == ledStrip->getPosition()) {
      ledStrip->setLedHue(it->y, it->hue);
    }
  }
  if (food.x == ledStrip->getPosition()) {
    ledStrip->setLedHue(food.y, food.hue);
  }
}

void Snake::button(Button button) {
  switch (button) {
    case Button::UP:    direction = Direction::UP;    break;
    case Button::DOWN:  direction = Direction::DOWN;  break;
    case Button::LEFT:  direction = Direction::LEFT;  break;
    case Button::RIGHT: direction = Direction::RIGHT; break;
    default: break;
  }
}

Action Snake::calculateAction() {
  calculateHead();
  if (head.y == MAX_LEDS_PER_LEDSTRIP) {
    return Action::Fail;
  }
  if (head.y < 0) {
    return Action::Fail;
  }
  if (collision(&food, &head)) {
    if (snake.size() == NUMBER_OF_LEDS - 1) {
      return Action::Win;
    }
    return Action::Eat;
  }
  if (collisionWithSnake(&head)) {
    return Action::Fail;
  }
  return Action::Move;
}

void Snake::move() {
  if (debug) {
    Serial.println("Move");
  }
  snake.pop_front();
  pushHead();
  snake.shrink_to_fit();
  setHue();

  ledManager->clearAll();
  ledManager->doProgram(this);
}

void Snake::eat() {
  if (debug) {
    Serial.println("Eat");
  }
  pushHead();
  setHue();

  food.x = rand() % NUMBER_OF_LEDSTRIPS;
  food.y = rand() % MAX_LEDS_PER_LEDSTRIP;

  ledManager->clearAll();
  ledManager->doProgram(this);
}

void Snake::fail() {
  if (debug) {
    Serial.println("Fail");
  }
  for (auto it = snake.begin(); it != snake.end(); it++) {
    it->hue = HUE_FAIL;
  }
  ledManager->clearAll();
  ledManager->doProgram(this);
  delay(5000);
  reset();
}

void Snake::win() {
  if (debug) {
    Serial.println("Win");
  }
  for (auto it = snake.begin(); it != snake.end(); it++) {
    it->hue = HUE_WIN;
  }
  ledManager->clearAll();
  ledManager->doProgram(this);
  delay(5000);
  reset();
}

void Snake::reset() {
  if (debug) {
    Serial.println("Reset");
  }
  ledManager->clearAll();
  snake.clear();

  food.x = rand() % NUMBER_OF_LEDSTRIPS;
  food.y = rand() % MAX_LEDS_PER_LEDSTRIP;
  food.hue = HUE_YELLOW;

  head.x = 0;
  head.y = MAX_LEDS_PER_LEDSTRIP / 2;
  head.hue = HUE_START;
  pushHead();
  snake.shrink_to_fit();

  direction = Direction::RIGHT;
}

void Snake::calculateHead() {
  switch (direction) {
    case Direction::UP:
      head.y++;
      break;
    case Direction::DOWN:
      head.y--;
      break;
    case Direction::LEFT:
      head.x = (head.x - 1 + NUMBER_OF_LEDSTRIPS) % NUMBER_OF_LEDSTRIPS;
      break;
    case Direction::RIGHT:
      head.x = (head.x + 1) % NUMBER_OF_LEDSTRIPS;
      break;
  }
}

void Snake::pushHead() {
  snake.push_back({head.x, head.y, HUE_START});
}

bool Snake::collision(Position * a, Position * b) {
  return a->x == b->x && a->y == b->y;
}

bool Snake::collisionWithSnake(Position * p) {
  for (auto it = snake.begin(); it != snake.end(); it++) {
    if (p->x == it->x && p->y == it->y) {
      return true;
    }
  }
  return false;
}

void Snake::setHue() {
  int hue = HUE_START;
  for (auto it = snake.rbegin(); it != snake.rend(); it++) {
    it->hue = hue;
    if (hue > HUE_END) {
      hue = hue - 4;
    }
  }
}