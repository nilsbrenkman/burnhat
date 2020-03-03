#ifndef Sparkle_H
#define Sparkle_H

#include "AbstractProgram.h"
#include "application.h"

class Sparkle : public AbstractProgram {
  public:
    Sparkle();
    void loop();
    void button(Button button);
  private:
    int led;
    int mode;
};

#endif
