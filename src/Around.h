#ifndef Around_H
#define Around_H

#include <math.h>
#include "AbstractAction.h"

class Around : public AbstractAction {
  public:
    Around();
    ~Around() {}
    boolean run();
    void doAction(LedStrip * ledStrip);
  private:
    int position;
    int hue;
    static const int hueDiff = 5;
};

#endif
