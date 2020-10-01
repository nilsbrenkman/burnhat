#ifndef Equalizer_H
#define Equalizer_H

#define NUMBER_OF_FREQ 7
#define RESET_DELAY    72
#define STROBE_PULSE   36
#define HISTORY_SIZE   1000
#define RANGE_MINIMUM  1500

#include <math.h>
#include "AbstractProgram.h"
#include "Constants.h"

class Equalizer : public AbstractProgram {
  public:
    Equalizer();
    ~Equalizer();
    void loop();
    void doProgram(LedStrip * ledStrip);
    void button(Button button);
  private:
    void read();
    void transform();
    int frequency[NUMBER_OF_FREQ];
    int history[HISTORY_SIZE][NUMBER_OF_FREQ];
    int volume[NUMBER_OF_FREQ];
    int strobeRead = 18;
    int counter = 0;
};

#endif
