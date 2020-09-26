#ifndef Random_H
#define Random_H

#include "AbstractProgram.h"

class Randomised : public AbstractProgram {
  public:
    Randomised();
    ~Randomised() {}
    void loop();
    void doProgram(LedStrip * ledStrip);
  private:
    int offset;
};

#endif
