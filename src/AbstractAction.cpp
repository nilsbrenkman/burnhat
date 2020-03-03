#include "AbstractAction.h"

void AbstractAction::init(LedManager * lm) {
  ledManager = lm;
}

boolean AbstractAction::run() {
  // do nothing
}

void AbstractAction::doAction(LedStrip * ledStrip) {
  // do nothing
}

void AbstractAction::clear() {
  ledManager->clearAll();
}
