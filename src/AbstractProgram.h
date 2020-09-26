#ifndef AbstractProgram_H
#define AbstractProgram_H

#include "LedManager.h"
#include "LedStrip.h"
#include "Constants.h"

class LedManager;

class LedStrip;

class AbstractProgram {
  public:
    virtual ~AbstractProgram() {}
    void init(LedManager * ledManager);
    virtual void loop();
    virtual void doProgram(LedStrip * ledStrip);
    virtual void button(Button button);
  protected:
    bool doEvent(int delay);
    LedManager * ledManager;
    uint32_t timeout;
};

#endif
