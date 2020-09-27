#ifndef SingleColor_H
#define SingleColor_H

#include <math.h>
#include "AbstractProgram.h"
#include "Constants.h"

class SingleColor : public AbstractProgram {
  public:
    SingleColor();
    ~SingleColor() {}
    void afterInit();
    void button(Button button);
  private:
    void setHue();
    void addHue(int diff);
    void numericButton(int button);
    int hue = Hue::RED;
    int input[3] = { 0, 0, 0 };
    system_tick_t lastButtonTime = 0;
    int currentInput = 0;
    static const int BUTTON_COOLDOWN = 2000;
};

#endif
