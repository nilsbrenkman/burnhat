#ifndef Snake_H
#define Snake_H

#include <deque>
#include "AbstractProgram.h"
#include "Constants.h"

typedef struct Position {
  Position() {}
  Position(int a, int b, int c) {
    x = a;
    y = b;
    hue = c;
  }
  int x;
  int y;
  int hue;
} Position;

enum class Action {
  Move,
  Eat,
  Fail,
  Win
};

class Snake : public AbstractProgram {
  public:
    Snake();
    ~Snake() {}
    void loop();
    void doProgram(LedStrip * ledStrip);
    void button(Button button);
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
    void setHue();
    std::deque<Position> snake;
    Direction direction;
    Position food;
    Position head;
};

#endif
