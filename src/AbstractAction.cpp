#include "AbstractAction.h"

void AbstractAction::init(LedManager * lm) {
  ledManager = lm;
}

boolean AbstractAction::run() {
  return false;
}

void AbstractAction::doAction(LedStrip * ledStrip) {
  // do nothing
}
