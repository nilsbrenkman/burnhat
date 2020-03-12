#include "Snake.h"

#define HUE_START 200
#define HUE_FOOD  63
#define HUE_FAIL  0
#define HUE_WIN   127

Snake::Snake() {
  Serial.println("Snake started");
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
    case Button::NUM_3: direction = Direction::LEFT;  break;
    case Button::NUM_4: direction = Direction::RIGHT; break;
    default: break;
  }
}

void Snake::clear() {
  ledManager->clearAll();
  delete this;
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
  Serial.println("Move");
  snake.pop_front();
  pushHead();
  ledManager->clearAll();
  ledManager->doProgram(this);
}

void Snake::eat() {
  Serial.println("Eat");
  pushHead();

  food.x = rand() % NUMBER_OF_LEDSTRIPS;
  food.y = rand() % MAX_LEDS_PER_LEDSTRIP;

  ledManager->clearAll();
  ledManager->doProgram(this);
}

void Snake::fail() {
  Serial.println("Fail");
  for (auto it = snake.begin(); it != snake.end(); it++) {
    it->hue = HUE_FAIL;
  }
  ledManager->clearAll();
  ledManager->doProgram(this);
  delay(5000);
  reset();
}

void Snake::win() {
  Serial.println("Win");
  for (auto it = snake.begin(); it != snake.end(); it++) {
    it->hue = HUE_WIN;
  }
  ledManager->clearAll();
  ledManager->doProgram(this);
  delay(5000);
  reset();
}

void Snake::reset() {
  Serial.println("Reset");
  ledManager->clearAll();
  snake.clear();

  food.x = rand() % NUMBER_OF_LEDSTRIPS;
  food.y = rand() % MAX_LEDS_PER_LEDSTRIP;
  food.hue = HUE_FOOD;

  Position start;
  head.x = 0;
  head.y = MAX_LEDS_PER_LEDSTRIP / 2;
  head.hue = HUE_START;
  pushHead();

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
      head.x = (head.x - 1) % NUMBER_OF_LEDSTRIPS;
      break;
    case Direction::RIGHT:
      head.x = (head.x + 1) % NUMBER_OF_LEDSTRIPS;
      break;
  }
}

void Snake::pushHead() {
  Position push;
  push.x = head.x;
  push.y = head.y;
  push.hue = HUE_START;
  snake.push_back(push);
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
