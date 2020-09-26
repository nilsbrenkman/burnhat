#ifndef AbstractAction_H
#define AbstractAction_H

#include "LedManager.h"
#include "LedStrip.h"
#include "Constants.h"

class LedManager;

class LedStrip;

class AbstractAction {
  public:
    virtual ~AbstractAction() {}
    void init(LedManager * ledManager);
    virtual boolean run();
    virtual void doAction(LedStrip * ledStrip);
  protected:
    LedManager * ledManager;
};

#endif
