#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <Arduino.h>

class Debouncer {
  private:
    pin_size_t pin;
    int period;
    unsigned long last;
    bool prev; 
  public:
  Debouncer(pin_size_t pin, int period);
  void setup();
  void loop();
  bool state();
  bool ready();
};

#endif