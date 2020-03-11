#ifndef Explosion_H
#define Explosion_H

#include <math.h>
#include "AbstractAction.h"

class Explosion : public AbstractAction {
  public:
    Explosion();
    boolean run();
    void doAction(LedStrip * ledStrip);
    void clear();
  private:
    int originX;
    int originY;
    int offset;
    bool active;
};

#endif
