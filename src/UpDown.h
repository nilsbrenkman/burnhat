#ifndef UpDown_H
#define UpDown_H

#include <math.h>
#include "AbstractAction.h"

class UpDown : public AbstractAction {
  public:
    UpDown();
    ~UpDown() {}
    boolean run();
    void doAction(LedStrip * ledStrip);
  private:
    Direction direction;
    int position;
    int hue;
    static const int hueDiff = 3;
};

#endif
