#ifndef Rainbow_H
#define Rainbow_H

#include <math.h>
#include "AbstractProgram.h"
#include "Constants.h"

class Rainbow : public AbstractProgram {
  public:
    Rainbow();
    ~Rainbow() {}
    void loop();
    void doProgram(LedStrip * ledStrip);
    void button(Button button);
  private:
    Direction direction;
    int offset;
    int speed;
};

#endif
