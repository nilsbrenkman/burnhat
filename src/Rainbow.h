#ifndef Rainbow_H
#define Rainbow_H

#include <math.h>
#include "AbstractProgram.h"

enum Direction {
  UP,
  DOWN
};

class Rainbow : public AbstractProgram {
  public:
    Rainbow();
    void loop();
    void doProgram(LedStrip * ledStrip);
    void button(Button button);
  private:
    Direction direction;
};

#endif
