#ifndef Random_H
#define Random_H

#include "AbstractProgram.h"

class Randomised : public AbstractProgram {
  public:
    Randomised();
    void loop();
    void doProgram(LedStrip * ledStrip);
    void clear();
  private:
    int offset;
};

#endif
