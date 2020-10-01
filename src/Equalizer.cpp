#include "Equalizer.h"

Equalizer::Equalizer() {
  if (debug) Serial.println("Equalizer started");

  pinMode(EQ_STROBE_PIN, OUTPUT);
  pinMode(EQ_RESET_PIN, OUTPUT);
  pinMode(EQ_ANALOG_PIN, INPUT);

  digitalWrite(EQ_RESET_PIN, LOW);
  digitalWrite(EQ_STROBE_PIN, LOW);
  delay(1);

  // Reset the MSGEQ7 as per the datasheet timing diagram
  digitalWrite (EQ_RESET_PIN,  HIGH);
  delay        (1);
  digitalWrite (EQ_RESET_PIN,  LOW);
  digitalWrite (EQ_STROBE_PIN, HIGH);
  delay        (1);

    for (int f = 0; f < NUMBER_OF_FREQ; f++) {
      volume[f] = 1;
    }
}

void Equalizer::loop() {
  read();
  transform();
  if (debug) {
      Serial.print("Frequency: [ ");
      for (int i = 0; i < NUMBER_OF_FREQ; i++) {
        Serial.print(frequency[i]);
        Serial.print(" ");
      }
      Serial.println("]");
  }
  ledManager->doProgram(this);
  delay(20);
}

void Equalizer::doProgram(LedStrip * ledStrip) {
  int freq = (ledStrip->getPosition() + 3) % NUMBER_OF_LEDSTRIPS;
  if (freq > NUMBER_OF_FREQ - 1) return;

  int vol = volume[freq];
  for (int led = 0; led < ledStrip->getSize(); led++) {
    if (led < vol) {
      if (led < 4) {
        ledStrip->setLedHue(led, Hue::GREEN);
      } else if (led < 6) {
        ledStrip->setLedHue(led, Hue::ORANGE);
      } else {
        ledStrip->setLedHue(led, Hue::RED);
      }
    } else {
      ledStrip->setLedColor(led, CRGB::Black);
    }
  }
}

void Equalizer::button(Button button) {

}

void Equalizer::read() {
  digitalWrite(EQ_RESET_PIN, HIGH);
  digitalWrite(EQ_STROBE_PIN, LOW);
  delayMicroseconds(1);
  digitalWrite(EQ_RESET_PIN, LOW);
  delayMicroseconds(RESET_DELAY);

  // Cycle through each frequency band by pulsing the strobe.
  for (int i = 0; i < NUMBER_OF_FREQ; i++) {
    digitalWrite(EQ_STROBE_PIN, HIGH);
    delayMicroseconds(STROBE_PULSE);
    digitalWrite(EQ_STROBE_PIN, LOW);
    delayMicroseconds(STROBE_PULSE);
    int value = analogRead(EQ_ANALOG_PIN);
    frequency[i] = value;
    history[counter % HISTORY_SIZE][i] = value;
  }
  counter++;
}

void Equalizer::transform() {
  int historySize = std::min(counter, HISTORY_SIZE);
  for (int f = 0; f < NUMBER_OF_FREQ; f++) {
    int min = 4095;
    int max = 0;
    long total = 0;
    for (int i = 0; i < historySize; i++) {
      int val = history[i][f];
      min = std::min(min, val);
      max = std::max(max, val);
      total += val;
    }
    int avg = total / historySize;
    int floor = ((3 * min) + avg) / 4;
    int ceil = ((3 * max) + avg) / 4;
    int range = ceil - floor;

    int full = std::max(range, RANGE_MINIMUM);
    int scaled = std::max(frequency[f] - floor, 0);
    int vol = (int) ((double) scaled / (double) full * (MAX_LEDS_PER_LEDSTRIP + 1));

    if (vol > volume[f] ) {
      volume[f]++;
    } else if (vol < volume[f] && volume[f] > 1) {
      volume[f]--;
    }
  }
}

Equalizer::~Equalizer() {
  pinMode(EQ_STROBE_PIN, INPUT);
  pinMode(EQ_RESET_PIN, INPUT);
}
