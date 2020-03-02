#ifndef Rainbow_H
#define Rainbow_H

#include <math.h>
#include "AbstractProgram.h"

class Rainbow : public AbstractProgram {
  public:
    Rainbow();
    void loop();
    void doProgram(LedStrip * ledStrip);
    void sleeve(int buttonid);
};

#endif
