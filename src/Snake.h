#ifndef Snake_H
#define Snake_H

#include <deque>
#include "AbstractProgram.h"
#include "Constants.h"

struct Position {
  int x;
  int y;
  int hue;
};

enum class Action {
  Move,
  Eat,
  Fail,
  Win
};

class Snake : public AbstractProgram {
  public:
    Snake();
    void loop();
    void doProgram(LedStrip * ledStrip);
    void button(Button button);
    void clear();
  private:
    Action calculateAction();
    void move();
    void eat();
    void fail();
    void win();
    void reset();
    void calculateHead();
    void pushHead();
    bool collision(Position * a, Position * b);
    bool collisionWithSnake(Position * p);
    std::deque<Position> snake;
    Direction direction;
    Position food;
    Position head;
};

#endif
